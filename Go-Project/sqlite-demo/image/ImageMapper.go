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
		tags VARCHAR(100) NULL,
		size VARCHAR(100) NULL,
		create_time DATE NULL);`
	_, err := db.Exec(sql_table)
	if err != nil {
		fmt.Println(err)
	}
	return &image, err
}

func NewImageItem(img_id, tags, size, create_time string) *ImageModel {
	tb := ImageModel{
		ImgId:      img_id,
		Tags:       tags,
		Size:       size,
		CreateTime: create_time,
	}
	return &tb
}

func (imgMapper *ImageMapper) Insert(imgModel *ImageModel) {
	stmt, _ := imgMapper.db.Prepare("INSERT INTO image (img_id,tags,size,create_time) values(?,?,?,?)")
	_, err := stmt.Exec(imgModel.ImgId, imgModel.Tags, imgModel.Size, imgModel.CreateTime)
	if err != nil {
		fmt.Println(err)
	}
}

func (imgMapper *ImageMapper) GetImageByImgId(img_id string) *sql.Rows {
	rows, _ := imgMapper.db.Query("SELECT * FROM image WHERE img_id='" + img_id + "'")
	return rows
}
