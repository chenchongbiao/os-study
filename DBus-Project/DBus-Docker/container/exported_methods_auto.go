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
	}
}
