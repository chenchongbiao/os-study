package container

import (
	"database/sql"

	"golang.org/x/vuln/client"
)

type ContainerService struct {
	cli             *client.Client
	containerMapper *ContainerMapper
}

func InitService(cli *client.Client, db *sql.DB) *ContainerMapper {
	containerMapper, _ := InitDB(db)
	containerService := ContainerService{
		cli:             cli,
		containerMapper: containerMapper,
	}
	return &containerService
}
