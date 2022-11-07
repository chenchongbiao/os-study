package container

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (container *Container) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "List",
			Fn:      container.List,
			OutArgs: []string{"result"},
		},
	}
}
