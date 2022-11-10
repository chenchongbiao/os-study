package container

import (
	"database/sql"
	"fmt"
)

type ContainerMapper struct {
	db *sql.DB
}

func InitDB(db *sql.DB) (*ContainerMapper, error) {
	image := ContainerMapper{
		db: db,
	}
	sql_table := `
	CREATE TABLE IF NOT EXISTS container(
		name VARCHAR(100) NULL PRIMARY KEY,
		status int NULL,
		image VARCHAR(100) NULL,
		port  VARCHAR(100) NULL),
		ip  VARCHAR(100) NULL),;`
	_, err := db.Exec(sql_table)
	if err != nil {
		fmt.Println(err)
	}
	return &image, err
}

func NewContainerItem(name, image, port, ip string, status int) *ContainerModel {
	tb := ContainerModel{
		Name:   name,
		Status: status,
		Image:  image,
		Port:   port,
		Ip:     ip,
	}
	return &tb
}
