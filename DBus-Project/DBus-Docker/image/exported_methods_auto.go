package image

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (image *Image) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "Pull",
			Fn:      image.Pull,
			OutArgs: []string{"result"},
		},
	}
}
