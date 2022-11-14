package container

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (c *ContainerService) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "GetContainerList",
			Fn:      c.GetContainerList,
			OutArgs: []string{"result", "code"},
		},
		{
			Name:    "StopContainer",
			Fn:      c.StopContainer,
			InArgs:  []string{"containerID"},
			OutArgs: []string{"code"},
		},
		{
			Name:    "StartContainer",
			Fn:      c.StartContainer,
			InArgs:  []string{"containerID"},
			OutArgs: []string{"code"},
		},
	}
}
