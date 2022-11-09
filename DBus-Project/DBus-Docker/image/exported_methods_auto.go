package image

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (image *Image) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "PullImage",
			Fn:      image.PullImage,
			InArgs:  []string{"img"},
			OutArgs: []string{"result"},
		},
		{
			Name:    "PullPrivateImage",
			Fn:      image.PullPrivateImage,
			InArgs:  []string{"img", "user", "password"},
			OutArgs: []string{"result"},
		},
		{
			Name:    "ImageList",
			Fn:      image.ImageList,
			OutArgs: []string{"result"},
		},
	}
}
