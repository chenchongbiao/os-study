package main

import (
	"database/sql"
	"fmt"
	"os"
	"os/user"

	"sqlite-demo/image"

	"github.com/docker/docker/client"
	_ "github.com/mattn/go-sqlite3"
)

var ()

func main() {
	TcpUrl := "tcp://localhost:2375"
	cli, err := client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost(TcpUrl))
	if err != nil {
		fmt.Println("client初始化失败", err)
		return
	}

	db, err := initDatabase()
	if err != nil {
		fmt.Println("数据库初始化失败", err)
		return
	}

	var ch1 string

	for {
		fmt.Println("1. 拉取镜像")
		fmt.Println("2. 获取镜像列表")
		fmt.Println("请输入数字：")
		fmt.Scan(&ch1)
		switch ch1 {
		case "1":
			imgService := image.InitService(cli, db)
			result, _ := imgService.PullImage("docker.io/busybox")
			fmt.Println(result)
		case "2":
			imgService := image.InitService(cli, db)
			result, _ := imgService.GetImageList()
			fmt.Println(result)
		}
	}

	// result, err := imgService.PullImage("docker.io/busybox")
	// if err != nil {
	// 	fmt.Println(err)
	// }
	// fmt.Println(result)
	db.Close()
}

func initDatabase() (*sql.DB, error) {
	u, err := user.Current()
	printErr(err)

	dbusDockerDir := u.HomeDir + "/.config/dbus-docker/data"

	if !isExist(dbusDockerDir) {
		err = os.MkdirAll(dbusDockerDir, 0700)
		printErr(err)
	}

	//打开数据库，如果不存在，则创建
	dbPath := dbusDockerDir + "/db.sqlite"
	db, err := sql.Open("sqlite3", dbPath)
	return db, err
}

func isExist(path string) bool {
	_, err := os.Stat(path)
	if err != nil {
		if os.IsExist(err) {
			return true
		}
		if os.IsNotExist(err) {
			return false
		}
		return false
	}
	return true
}

func printErr(err error) {
	if err != nil {
		fmt.Println(err)
	}
}
