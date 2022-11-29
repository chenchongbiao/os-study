package container

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (c *ContainerService) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "GetContainerList",
			Fn:      c.GetContainerList,
			OutArgs: []string{"result"},
		},
		{
			Name:   "StopContainer",
			Fn:     c.StopContainer,
			InArgs: []string{"containerID"},
		},
		{
			Name:   "StartContainer",
			Fn:     c.StartContainer,
			InArgs: []string{"containerID"},
		},
		{
			Name:   "RestartContainer",
			Fn:     c.RestartContainer,
			InArgs: []string{"containerID"},
		},
		{
			Name:    "SearchContainerListByName",
			Fn:      c.SearchContainerListByName,
			InArgs:  []string{"containerName"},
			OutArgs: []string{"result"},
		},
		{
			Name:    "SearchContainerById",
			Fn:      c.SearchContainerById,
			InArgs:  []string{"containerId"},
			OutArgs: []string{"result"},
		},
		{
			Name:   "CreateContainer",
			Fn:     c.CreateContainer,
			InArgs: []string{"name", "image", "cmd", "ports", "volume", "tty", "openStdin"},
		},
		{
			Name:   "RmContainerById",
			Fn:     c.RmContainerById,
			InArgs: []string{"containerId"},
		},
	}
}
