package main

import (
	"fmt"
	"time"
)

// https://www.bilibili.com/video/BV1gY4y177BX
// Go语言标准库
// time时间处理
func main() {
	// 获取当前时间
	now_date := time.Now()
	fmt.Println(now_date)
	// 时间格式化输出
	layout := "2006-01-02 15:04:05" // 时间格式化模板
	fmt.Println(now_date.Format(layout))

	// 将字符串解析为时间类型
	ts := "2023-01-15 18:09:01"
	t1, err := time.Parse(layout, ts)
	if err != nil {
		panic(err)
	}
	fmt.Println(t1)
	loc1, err := time.LoadLocation("Asia/Shanghai")
	fmt.Println(time.ParseInLocation(layout, ts, loc1))
	loc, err := time.LoadLocation("America/New_York")
	if err != nil {
		panic(err)
	}
	// 时区
	fmt.Println(now_date.In(loc))

	// 时间运算
	fmt.Println(now_date.Add(1 * time.Hour)) // 当前时间+1小时
	fmt.Println(now_date.AddDate(0, 1, 1))   // 年 月 日 这里加一个月零一天
}
