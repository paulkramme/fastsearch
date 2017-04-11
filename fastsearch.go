package main

import "fmt"
import "path/filepath"
import "os"
import "time"

func scanfiles(location string) (m map[string]string, err error) {
	m = make(map[string]string)
	var walkcallback = func(path string, fileinfo os.FileInfo, inputerror error) (err error) {
		_, filename := filepath.Split(path)
		m[path] = filename
		return
	}
	err = filepath.Walk(location, walkcallback)
	return
}

func main() {
	for {
		m, err := scanfiles(".")
		if err != nil {
			panic(err)
		}
		fmt.Println(m)
		time.Sleep(1 * time.Second)
	}
}
