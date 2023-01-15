package main

import (
	"log"
	"os"
)

// Go语言标准内置库
// log, 内置简单的日志库
func main() {
	// 设置前缀
	log.SetPrefix("Test: ")
	// 设置格式
	log.SetFlags(log.Ldate | log.Ltime | log.Lmicroseconds)

	file, err := os.OpenFile("./cli.log", os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0755)
	if err != nil {
		log.Fatalln(err)
	}
	// 日志的输出位置 这里传入文件，日志不会在终端输出，会输出到文件
	log.SetOutput(file)
	log.Print("日志")

	// // 基本用法
	// // 打印日志
	// log.Print("Hello")
	// // 格式化日志
	// log.Printf("Hello %s", "bluesky")
	// // 打印日志并换行
	// log.Println("Hello bluesky")

	// // 打印日志退出
	// log.Fatalln("Hello")
	// // 打印日志，及其详细信息，然后退出
	// log.Panicln()
}
