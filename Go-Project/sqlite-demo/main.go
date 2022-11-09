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
	Host := "tcp://localhost:2375"
	cli, err := client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost(Host))
	printErr(err)

	// db := initDatabase()
	// fmt.Println("数据库初始化", db)
	// img, err := image.InitDB(db)
	// printErr(err)
	// imageItem := image.NewImageItem("f7b038b0b2", "busybox:latest", "python", "2022-11-08", 20.23)
	// img.Insert(imageItem)
	imgService := image.InitService(cli)
	result, err := imgService.PullImage("docker.io/busybox")
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(result)
}
func initDatabase() *sql.DB {
	u, err := user.Current()
	printErr(err)

	dbusDockerDir := u.HomeDir + "/.config/dbus-docker/data"

	if !isExist(dbusDockerDir) {
		err = os.Mkdir(dbusDockerDir, 0700)
		printErr(err)
	}

	//打开数据库，如果不存在，则创建
	dbPath := dbusDockerDir + "/db.sqlite"
	db, err := sql.Open("sqlite3", dbPath)
	printErr(err)
	return db
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
