package container

import (
	"database/sql"
	"fmt"
	"runtime"
)

type ContainerMapper struct {
	db *sql.DB
}

func InitDB(db *sql.DB) (*ContainerMapper, error) {
	contaier := ContainerMapper{
		db: db,
	}
	sql_table := `
	CREATE TABLE IF NOT EXISTS container(
		container_id VARCHAR(100) NULL PRIMARY KEY,
		name VARCHAR(100) NULL,
		state VARCHAR(10) NULL,
		image VARCHAR(100) NULL,
		port  VARCHAR(100) NULL,
		command  VARCHAR(100) NULL);`
	_, err := db.Exec(sql_table)
	if err != nil {
		fmt.Println(err)
	}
	return &contaier, err
}

func NewContainerItem(container_id, name, state, image, port, command string) *ContainerModel {
	tb := ContainerModel{
		ContaierID: container_id,
		Name:       name,
		State:      state,
		Image:      image,
		Port:       port,
		Command:    command,
	}
	return &tb
}

func (conMapper *ContainerMapper) Insert(conModel *ContainerModel) {
	stmt, _ := conMapper.db.Prepare("INSERT INTO container (container_id,name,image,state,port,command) values(?,?,?,?,?,?)")
	_, err := stmt.Exec(conModel.ContaierID, conModel.Name, conModel.Image, conModel.State, conModel.Port, conModel.Command)
	if err != nil {
		fmt.Println("Container数据插入失败", err)
	}
}

func (conMapper *ContainerMapper) SelectContainerByImgId(container_id string) bool {
	var result string
	err := conMapper.db.QueryRow("SELECT container_id FROM container WHERE container_id = ?", container_id).Scan(&result)
	switch {
	case err == sql.ErrNoRows:
	case err != nil:
		// 使用该方式可以打印出运行时的错误信息, 该种错误是编译时无法确定的
		if _, file, line, ok := runtime.Caller(0); ok {
			fmt.Println("SelectContainerByImgId", err, file, line)
		}
		return false
	}
	if result == "" {
		return false
	} else {
		return true
	}
}
