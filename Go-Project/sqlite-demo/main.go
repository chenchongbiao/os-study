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

	// rows, err := db.Query("SELECT * FROM image")
	// printErr(err)
	// var uid int
	// var username string
	// var department string
	// var created time.Time

	// for rows.Next() {
	// 	err = rows.Scan(&uid, &username, &department, &created)
	// 	printErr(err)
	// 	fmt.Println(uid)
	// 	fmt.Println(username)
	// 	fmt.Println(department)
	// 	fmt.Println(created)
	// }
}
func initDatabase() (*sql.DB, error) {
	Host := "tcp://localhost:2375"
	_, err := client.NewClientWithOpts(client.WithAPIVersionNegotiation(), client.WithHost(Host))
	printErr(err)

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
