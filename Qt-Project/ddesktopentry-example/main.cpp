#include <QDebug>
#include <QString>
#include <DDesktopEntry>
#include <QFile>

DCORE_USE_NAMESPACE // 使用Dtk Core命名空间

/*!
    使用 QStringLiteral 宏可以在编译期把代码里的常量字符串 str 直接构造为 QString 对象，
    于是运行时就不再需要额外的构造开销了。
    如果编译器支持，则 QStringLiteral 宏在编译时从 str 生成一个 QString 的数据。
    在这种情况下从 QStringLiteral 创建一个 QString 是自由的，生成的字符串数据存储在编译的目标文件的只读段中。
    对于不支持创建编译时字符串的编译器，QStringLiteral 的使用效果将与使用 QString::fromUtf8() 一样。
*/
const QString fileContent = { QStringLiteral(R"desktop(# A. Example Desktop Entry File
[Desktop Entry]
Version=1.0
Type=Application
Name=Foo Viewer
Name[zh_CN]=福查看器
Comment=The best viewer for Foo objects available!
# Next line have an extra " character
Comment[zh_CN]=最棒的 "福 查看器！
TryExec=fooview
Exec=fooview %F
Icon=fooview
MimeType=image/x-foo;
Actions=Gallery;Create;

[Desktop Action Gallery]
Exec=fooview --gallery
Name=Browse Gallery

[Desktop Action Create]
Exec=fooview --create-new
Name=Create a new Foo!
Icon=fooview-new
)desktop") };

int main(int argc, char *argv[])
{
    QFile file("example1.desktop");
    // 尝试打开文件
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    const QString fileName = file.fileName();
    QTextStream ts(&file);
    ts << fileContent;
    file.close();
    QFile::exists(fileName);

    /*
        QScopedPointer 类似于 C++ 11 中的 unique_ptr。
        当我们的内存数据只在一处被使用，用完就可以安全的释放时就可以使用 QScopedPointer。
    */
    // 打开一个fileName为example1.desktop的文件
    QScopedPointer<DDesktopEntry> desktopFile(new DDesktopEntry(fileName));

    // 获取desktop中所有组并返回列表，对应"Desktop Entry"、"Desktop Action Gallery"、"Desktop Action Create"三组
    QStringList allGroups = desktopFile->allGroups();                   
    
    qDebug() << QString("Desktop 文件共有%1组").arg(allGroups.count()); 

    // 调用allGroups函数，传入true，保持读取desktop文件时的顺序不变，获取第0组
    qDebug() << QString("Desktop 文件第0组为: %1").arg(desktopFile->allGroups(true)[0]);                       

    // 获取key=Name，localeKey=zh_CN的值，即Name[zh_CN]=福查看器
    qDebug() << QString("Name[zh_CN]=%1") \
                .arg(desktopFile->localizedValue("Name", "zh_CN"));     

    // 获取key为Nam，,localeKey为empty的值，empty表示没有localeKey，即Name=Foo Viewer
    qDebug() << QString("Name=%1") \
                .arg(desktopFile->localizedValue("Name", "empty"));     

    // 获取Desktop Entry组下的所有key，即"Actions", "Comment", "Comment[zh_CN]", "Exec", "Icon", "MimeType", "Name", "Name[zh_CN]", "TryExec", "Type", "Version"
    qDebug() << QString("Desktop Entry组下的所有key: ") \                
                << desktopFile->keys("Desktop Entry");                 

    // 设置 key 为 Name的值为"Bar Viewer"，默认组是"Desktop Entry"
    desktopFile->setRawValue("Bar Viewer", "Name");   

    // 设置 key 为 Name，localeKey为zh_CN的值为霸查看器，默认组是"Desktop Entry"
    desktopFile->setLocalizedValue("霸查看器", "zh_CN", "Name");

    // 检查 section 中是否包 key 为 Semicolon 的值，包含 key 返回true; 否则返回false，默认组是Desktop Entry
    qDebug() << QString("Desktop Entry组是否包key是Semicolon: ") \
                << desktopFile->contains("Semicolon", "Desktop Entry");  
    
    // 设置key为Semicolon的值为";grp\\;2;grp3;"，默认组是"Desktop Entry"
    desktopFile->setRawValue(";grp\\;2;grp3;", "Semicolon");

    // 返回给定 section 中与给定 key 关联的字符串的列表。如果destkop不包含为该键的项,则函数返回一个空字符串列表。 默认组是Desktop Entry
    qDebug() << QString("Desktop Entry组中Semicolon对应值的字符串列表: ") \
                << desktopFile->stringListValue("Semicolon");

    // 再次检查 section 中是否包 key 为 Semicolon 的值，此时为true
    qDebug() << QString("Desktop Entry组是否包key是Semicolon: ") \
            << desktopFile->contains("Semicolon", "Desktop Entry");   

    // 删除desktop中 section 中 key 对应的值，默认组是"Desktop Entry"
    desktopFile->removeEntry("Semicolon", "Desktop Entry");

    // 再次检查 section 中是否包 key 为 Semicolon 的值，此时为false
    qDebug() << QString("Desktop Entry组是否包key是Semicolon: ") \
            << desktopFile->contains("Semicolon", "Desktop Entry");

    // 将数据回写到desktop文件。 true表示写成功; 否则返回false 
    if (desktopFile->save())
    {
        qDebug() << "文件保存成功";
    } else {
        qDebug() << "文件保存失败";
    }

    return 0;
}