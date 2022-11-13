package config

import (
	"database/sql"
	"fmt"
	"os"
	"os/user"
)

const (
	Success_code = 1
	Fail_code    = 0
)

func InitDatabase() (*sql.DB, error) {
	u, err := user.Current()
	if err != nil {
		fmt.Println("获取当前用户失败", err)
	}

	dbusDockerDir := u.HomeDir + "/.config/dbus-docker/data"

	if !IsExist(dbusDockerDir) {
		err = os.MkdirAll(dbusDockerDir, 0700)
		if err != nil {
			fmt.Println("文件创建失败", err)
		}
	}

	//打开数据库，如果不存在，则创建
	dbPath := dbusDockerDir + "/db.sqlite"
	db, err := sql.Open("sqlite3", dbPath)
	return db, err
}

func IsExist(path string) bool {
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
