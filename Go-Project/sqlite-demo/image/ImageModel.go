package image

type ImageModel struct {
	ImgId      string  // 镜像id
	Tags       string  // 镜像标签
	Author     string  // 镜像作者
	Size       float32 // 镜像尺寸
	CreateTime string  // 镜像创建时间
}
