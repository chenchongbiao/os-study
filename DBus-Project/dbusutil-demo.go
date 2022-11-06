package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"os"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
	"github.com/godbus/dbus"
	"github.com/linuxdeepin/go-lib/dbusutil"
)

/*
str="/usr/bin/dockerd -H tcp://localhost:2375 -H unix:///var/run/docker.sock "
sudo sed -i "s@/usr/bin/dockerd@$str@" /usr/lib/systemd/system/docker.service
systemctl daemon-reload
systemctl restart docker
*/

var (
	cli, err = client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost("tcp://localhost:2375"))

	imageName     = "docker.io/busybox"
	containerID   = ""
	containerName = "busybox-test"
)

type Obj struct {
	methods *struct {
		GetString func(str string) `in:"str" out:"result"`
	}
}

func (o *Obj) GetString(str string) (string, *dbus.Error) {
	pullPrivateImage()
	return str, nil
}

func (o *Obj) GetInterfaceName() string {
	return "p1.p2.p3"
}

func main() {
	service, err := dbusutil.NewSessionService()
	obj := &Obj{}
	err = service.Export("/p1/p2/p3", obj)
	err = service.RequestName("p1.p2.p3")
	fmt.Println(err)
	service.Wait()
}

func pullPrivateImage() {
	ctx := context.Background()
	// authConfig := types.AuthConfig{
	// 	Username: "",
	// 	Password: "",
	// }
	// encodeJson, _ := json.Marshal(authConfig)
	// authStr := base64.StdEncoding.EncodeToString(encodeJson)
	// out, err := cli.ImagePull(ctx, imageName, types.ImagePullOptions{RegistryAuth: authStr})
	out, err := cli.ImagePull(ctx, imageName, types.ImagePullOptions{})
	if err != nil {
		log.Fatal("image pull error ", err.Error())
	}
	defer out.Close()
	io.Copy(os.Stdout, out)
}
