package image

import (
	"database/sql"
	"fmt"
	"runtime"
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
		img_id VARCHAR(10) NULL PRIMARY KEY,
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
		fmt.Println("Image数据插入失败", err)
	}
}

func (imgMapper *ImageMapper) SelectImageByImgId(img_id string) bool {
	// 查询一条记录时, 不能使用类似if err := db.QueryRow().Scan(&...); err != nil {}的处理方式
	// 因为查询单条数据时, 可能返回var ErrNoRows = errors.New("sql: no rows in result set")该种错误信息
	// 而这属于正常错误
	var result string
	err := imgMapper.db.QueryRow("SELECT img_id FROM image WHERE img_id = ?", img_id).Scan(&result)
	switch {
	case err == sql.ErrNoRows:
	case err != nil:
		// 使用该方式可以打印出运行时的错误信息, 该种错误是编译时无法确定的
		if _, file, line, ok := runtime.Caller(0); ok {
			fmt.Println("SelectImageByImgId", err, file, line)
		}
		return false
	}
	if result == "" {
		return false
	} else {
		return true
	}
}
