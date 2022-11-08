package image

import (
	"database/sql"
	"fmt"
)

type ImageMapper struct {
	db *sql.DB
}

func InitDB(db *sql.DB) (*ImageMapper, error) {
	image := ImageMapper{
		db: db,
	}
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
	}
	return &image, err
}

func NewImageItem(img_id, tags, author, create_time string, size float32) *ImageModel {
	tb := ImageModel{
		ImgId:      img_id,
		Tags:       tags,
		Author:     author,
		Size:       size,
		CreateTime: create_time,
	}
	return &tb
}

func (imgMapper *ImageMapper) Insert(imgModel *ImageModel) {
	stmt, _ := imgMapper.db.Prepare("INSERT INTO image (img_id,tags,author,size,create_time) values(?,?,?,?,?)")
	res, err := stmt.Exec(imgModel.ImgId, imgModel.Tags, imgModel.Author, imgModel.Size, imgModel.CreateTime)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(res)
}
