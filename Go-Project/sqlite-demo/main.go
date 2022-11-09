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

	fmt.Println("数据库初始化")
	image.InitDB(db)

	// stmt, err := db.Prepare("INSERT INTO image(username, departname, created) values(?,?,?)")
	// printErr(err)
	// res, err := stmt.Exec("wangshubo", "国务院", "2017-04-21")
	// printErr(err)
	// fmt.Println(res)
	imgService := image.InitService(cli, db)
	imgService.GetImageList()
	// rows, err := db.Query("SELECT * FROM image")
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
