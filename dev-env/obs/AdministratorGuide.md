# 安装和配置

## 规划

对于测试自己的OBS实例，或者对于小型设置，例如如果只想将一些脚本打包到RPMS中并从中创建适当的安装源，则现成的OBS服务器设备镜像是最简单的方法。您可以从下载http://openbuildservice.org/download/。

然而，要将OBS用于具有许多包、项目和用户的大型Linux软件开发，请考虑定期安装。根据用户、项目和体系结构的数量，可以拆分后端（称为分区），并为前端和数据库提供单独的主机。

对于大多数安装，如果有足够的资源，可以在一台主机上运行除辅助程序之外的所有程序。

## 资源规划

通常，对于小型或中型安装，在一台主机上设置所有设备（工人除外）就足够了。应该为后端数据提供一个单独的/srv卷。我们建议您使用XFS作为文件系统。

对于每个调度器体系结构，您应该添加4GB RAM和一个CPU核心。对于每个构建分发版，您应该为每个体系结构添加至少50GB的磁盘空间。

一个拥有大约50个用户的中型实例可以在一台16GB RAM、4核和1 TB存储空间的机器上轻松运行。当然，存储空间取决于项目的大小以及新版本的出现频率。

对于更大的安装，您可以使用独立的网络进行后端通信、工作者和前端。

- 数据库的mysql集群
- api服务器：16GB RAM，4核，50GB磁盘
- 独立的二进制后端（调度器、调度器、转发服务器、发布者、管理员）
- 源服务器：11 GB RAM，4核，3 TB磁盘。RAM主要用于缓存。
- 主后端：62 GB RAM（超大），16TB磁盘
- 许多工作节点（参见-https://build.opensuse.org/monitor)

对于构建时间和性能，可用工作主机的数量和性能比其他部分更重要。

## 简单安装

在本文档中，我们将“简单安装”称为OBS安装，其中所有OBS服务都在同一台机器上运行。

在开始安装OBS之前，您应该确保您的主机具有正确的完全限定主机名，并且DNS正在工作并且可以解析所有名称。

### 后端安装

后端托管所有源和构建的包。它还安排作业。要安装它，请安装“obs-server”软件包。您应该检查/usr/lib/obs/server/BSConfig.pm文件，尽管对于简单的情况，默认值应该足够好。

您可以通过systemctl控制不同的后端组件。基本上，您可以在引导系统期间启用/禁用服务，并在运行的系统中启动/停止/重新启动服务。有关更多信息，请参阅systemctl手册页。例如，要重新启动存储库服务器，请执行以下操作：

```bash
systemctl restart obsrepserver.service
```

表1.1：服务名称

| Component           | Service Name                 | Remarks                              |
| :------------------ | :--------------------------- | :----------------------------------- |
| Source Server       | obssrcserver.service         |                                      |
| Repository          | Server obsrepserver.service  |                                      |
| Source              | Services obsservice.service  |                                      |
| Download            | obsdodup.service             | since 2.7                            |
| Delta Storage       | obsdeltastore.service        | since 2.7                            |
| Scheduler           | obsscheduler.service         |                                      |
| Dispatcher          | obsdispatcher.service        |                                      |
| Publisher           | obspublisher.service         |                                      |
| Signer              | obssigner.service            |                                      |
| Warden              | obswarden.service            |                                      |
| Cloud upload worker | obsclouduploadworker.service | Only needed for cloud upload feature |
| Cloud upload server | obsclouduploadserve.service  | Only needed for cloud upload feature |

表中的序列反映了启动序列，您需要使用

```bash
systemctl enable <name>
```

你可以启动它们：

```bash
systemctl start obssrcserver.service
systemctl start obsrepserver.service
systemctl start obsservice.service
systemctl start obsdodup.service
systemctl start obsdeltastore.service
systemctl start obsscheduler.service
systemctl start obsdispatcher.service
systemctl start obspublisher.service
systemctl start obssigner.service
systemctl start obswarden.service
systemctl start obsclouduploadworker.service
systemctl start obsclouduploadserver.service
```

### 前端安装

需要安装“obs-api”包和 MySQL 服务器。

#### MySQL安装

确保每次系统重新启动时都启动mysql服务器（使用“insserv-mysql”进行永久启动）。您应该运行mysql_secure_installation并按照说明进行操作。

```bash
sudo zypper ref
sudo zypper in mariadb
```

创建空的生产数据库：

```bash
# mysql -u root -p
mysql> create database api_production;
mysql> quit
```

使用单独的MySQL用户（例如obs）进行obs访问：

```bash
# mysql -u root -p
mysql> create user 'obs'@'%' identified by 'TopSecretPassword';
mysql> create user 'obs'@'localhost' identified by 'TopSecretPassword';
mysql> GRANT all privileges ON api_production.*
      TO 'obs'@'%', 'obs'@'localhost';
mysql> FLUSH PRIVILEGES;
mysql> quit
```

在api配置的“生产”部分配置MySQL用户和密码：/srv/www/obs/api/config/database.yml

示例：

```bash
# MySQL (default setup).  Versions 4.1 and 5.0 are recommended.
#
# Get the fast C bindings:
#   gem install mysql
#   (on OS X: gem install mysql -- --include=/usr/local/lib)
# And be sure to use new-style password hashing:
#   http://dev.mysql.com/doc/refman/5.0/en/old-client.html

production:
  adapter: mysql2
  database: api_production
  username: obs
  password: TopSecretPassword
  encoding: utf8
  timeout: 15
  pool: 30
```

现在填充数据库

```bash
cd /srv/www/obs/api/
sudo RAILS_ENV="production" rake db:setup
sudo RAILS_ENV="production" rake writeconfiguration
sudo chown -R wwwrun.www log tmp
```

#### Apache 设置

现在我们需要配置Web服务器。默认情况下，您可以访问熟悉的web用户界面，也可以访问端口443上使用https的api。存储库可以通过端口82上的http访问（一旦构建了一些包）。有关OBS实例的概览页面可在“http://localhost”。

obs-api包附带一个Apache vhost文件，当您使用以下默认值时，不需要修改该文件：/etc/apache2/vhosts.d/obs.conf

通过安装所需的软件包

```bash
zypper in obs-api apache2 apache2-mod_xforward rubygem-passenger-apache2 memcached
```

在/etc/sysconfig/apache2中添加以下Apache模块：

```bash
APACHE_MODULES="... passenger rewrite proxy proxy_http xforward headers socache_shmcb"
```

通过在/etc/sysconfig/apache2中启用SSL

```bash
APACHE_SERVER_FLAGS="SSL"
```

对于生产系统，您应该订购官方SSL证书。对于测试，请按照说明创建自签名SSL证书：

```bash
mkdir /srv/obs/certs
openssl genrsa -out /srv/obs/certs/server.key 1024
openssl req -new -key /srv/obs/certs/server.key \
        -out /srv/obs/certs/server.csr
openssl x509 -req -days 365 -in /srv/obs/certs/server.csr \
        -signkey /srv/obs/certs/server.key -out /srv/obs/certs/server.crt
cat /srv/obs/certs/server.key /srv/obs/certs/server.crt \
      > /srv/obs/certs/server.pem
```

要允许在Web UI代码中使用https API，您还需要信任您的证书：

```bash
cp /srv/obs/certs/server.pem /etc/ssl/certs/
c_rehash /etc/ssl/certs/
```

#### API配置

检查并编辑/srv/www/obs/api/config/options.yml

如果更改api的主机名/ips，则需要相应地调整frontend_host。如果要使用LDAP，还需要更改LDAP设置。有关详细信息，请参阅“[管理用户和组](https://openbuildservice.org/help/manuals/obs-admin-guide/obs.cha.administration#_user_and_group_management)”。您可以在第“[配置文件](https://openbuildservice.org/help/manuals/obs-admin-guide/obs.cha.overview_filesystem#_configuration_files)”中找到示例和更多详细信息。

建议启用

```bash
use_xforward: true
```

可以启动OBS web api，并通过

```bash
systemctl enable apache2
systemctl start apache2

systemctl enable obsapidelayed.service
systemctl start obsapidelayed.service

systemctl enable memcached.service
systemctl start memcached.service
```

现在，您有自己的空实例在运行，您可以执行一些在线配置步骤。

### 在线配置

要自定义OBS实例，您可能需要通过OBS API和Web用户界面配置一些设置。

首先，您应该更改Admin帐户的密码，为此，您需要首先在Web UI中以用户Admin的身份登录，并使用默认密码“opensuse”。单击Admin链接（页面右上角），您可以在此处更改密码。

更改管理员密码后，将osc设置为使用管理员帐户进行更多更改。这里有一个例子：

```bash
osc -c ~/.obsadmin_osc.rc -A https://api.testobs.org
```

默认情况下，密码以明文形式存储在此文件中，因此您需要授予此文件限制性访问权限，只允许您的用户进行读/写访问。osc允许以其他方式存储密码（例如在钥匙圈中），请参阅osc文档。

现在您可以查看OBS的主要配置：

```bash
osc -c ~/.obsadmin_osc.rc api /configuration >/tmp/obs.config
cat /tmp/obs.config
<configuration>
  <title>Open Build Service</title>
  <description>
    <p class="description">
      The <a href="http://openbuildservice.org"> Open Build Service (OBS)</a>
      is an open and complete distribution development platform that provides a transparent
      infrastructure for development of Linux distributions, used by openSUSE, MeeGo
      and other distributions.
      Supporting also Fedora, Debian, Ubuntu, RedHat and other Linux distributions.
    </p>
    <p class="description">
      The OBS is developed under the umbrella of the <a href="http://www.opensuse.org">openSUSE project<
      /a>. Please find further informations on the <
      a href="http://wiki.opensuse.org/openSUSE:Build_Service">openSUSE Project wiki pages</a>.
    </p>

    <p class="description">
      The Open Build Service developer team is greeting you. In case you use your OBS productive
      in your facility, please do us a favor and add yourself at <
      a href="http://wiki.opensuse.org/openSUSE:Build_Service_installations">
      this wiki page</a>. Have fun and fast build times!
    </p>
  </description>
  <name>private</name>
  <download_on_demand>on</download_on_demand>
  <enforce_project_keys>off</enforce_project_keys>
  <anonymous>on</anonymous>
  <registration>allow</registration>
  <default_access_disabled>off</default_access_disabled>
  <allow_user_to_create_home_project>on</allow_user_to_create_home_project>
  <disallow_group_creation>off</disallow_group_creation>
  <change_password>on</change_password>
  <hide_private_options>off</hide_private_options>
  <gravatar>on</gravatar>
  <cleanup_empty_projects>on</cleanup_empty_projects>
  <disable_publish_for_branches>on</disable_publish_for_branches>
  <admin_email>unconfigured@openbuildservice.org</admin_email>
  <unlisted_projects_filter>^home:.+</unlisted_projects_filter>
  <unlisted_projects_filter_description>home projects</unlisted_projects_filter_description>
  <schedulers>
    <arch>armv7l</arch>
    <arch>i586</arch>
    <arch>x86_64</arch>
  </schedulers>
</configuration>
```

略


# 参考

[Administrator Guide](https://openbuildservice.org/help/manuals/obs-admin-guide/)

[openSUSE 下搭建 Open Build Service](https://www.bilibili.com/video/BV12x411K7WE/?spm_id_from=333.337.search-card.all.click&vd_source=ebf9103aa7bb680610fdd7124d317e9d)
