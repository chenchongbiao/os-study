package main

import (
	"database/sql"
	"fmt"
	"os"
	"os/user"

	_ "github.com/mattn/go-sqlite3"
)

func main() {
	u, err := user.Current()
	if err != nil {
		fmt.Println(err)
	}

	dbusDockerDir := u.HomeDir + "/.config/dbus-docker"

	if !isExist(dbusDockerDir) {
		err = os.Mkdir(dbusDockerDir, 0700)
		if err != nil {
			fmt.Println(err)
		}
	}

	//打开数据库，如果不存在，则创建
	dbPath := dbusDockerDir + "/db.sqlite"
	db, err := sql.Open("sqlite3", dbPath)
	if err != nil {
		fmt.Println(err)
	}
	//创建表
	sql_table := `
	CREATE TABLE IF NOT EXISTS image(
		uid INTEGER PRIMARY KEY AUTOINCREMENT,
		username VARCHAR(64) NULL,
		departname VARCHAR(64) NULL,
		created DATE NULL);`
	db.Exec(sql_table)
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
		fmt.Println(err)
		return false
	}
	return true
}
