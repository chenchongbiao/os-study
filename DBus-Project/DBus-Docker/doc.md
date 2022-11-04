# 记录

使用go-lib库，无法通过github下载

通过下载源码重命名，~/go/pkg/mod/github.com/linuxdeepin/go-lib/go-lib@v5.8.7。

在go.mod下的require加入github.com/linuxdeepin/go-libv0.0.0-incompatible// indirect

在require之外加入

replace github.com/linuxdeepin/go-lib => /home/bluesky/go/pkg/mod/github.com/linuxdeepin/go-lib/go-lib@v5.8.7
