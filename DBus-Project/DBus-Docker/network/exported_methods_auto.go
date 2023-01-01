package network

import (
	"github.com/linuxdeepin/go-lib/dbusutil"
)

func (net *Network) GetExportedMethods() dbusutil.ExportedMethods {
	return dbusutil.ExportedMethods{
		{
			Name:    "GetNetworkList",
			Fn:      net.GetNetworkList,
			OutArgs: []string{"result"},
		},
	}
}
