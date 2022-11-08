package image

import (
	"database/sql"
	"fmt"
)

type Image struct {
	ImgId      string // 镜像id
	Tags       string // 镜像标签
	Author     string // 镜像作者
	Size       int    // 镜像尺寸
	CreateTime string // 镜像创建时间
}

func InitDB(db *sql.DB) bool {
	sql_table := `
	CREATE TABLE IF NOT EXISTS image(
		id INTEGER PRIMARY KEY AUTOINCREMENT,
		img_id VARCHAR(10) NULL,
		tags VARCHAR(64) NULL,
		author VARCHAR(64) NULL,
		size FLOAT(2) NULL,
		create_time DATE NULL);`
	_, err := db.Exec(sql_table)
	if err != nil {
		fmt.Println(err)
		return false
	}
	return true
}
func NewImageItem(img_id, tags, author, create_time string, size int) *Image {
	image := Image{
		ImgId:      img_id,
		Tags:       tags,
		Author:     author,
		Size:       size,
		CreateTime: create_time,
	}
	return &image
}

func (img *Image) InsertImage() {

}
