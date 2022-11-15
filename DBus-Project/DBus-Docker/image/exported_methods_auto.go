package image

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (image *Image) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:   "PullImage",
			Fn:     image.PullImage,
			InArgs: []string{"img"},
		},
		{
			Name:   "PullPrivateImage",
			Fn:     image.PullPrivateImage,
			InArgs: []string{"img", "user", "password"},
		},
		{
			Name:    "GetImageList",
			Fn:      image.GetImageList,
			OutArgs: []string{"result"},
		},
	}
}
