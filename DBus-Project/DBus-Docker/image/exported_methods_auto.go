package image

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (image *Image) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "Pull",
			Fn:      image.Pull,
			InArgs:  []string{"img", "user", "password"},
			OutArgs: []string{"result"},
		},
	}
}
