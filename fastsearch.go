package main

import "fmt"
import "path/filepath"
import "os"
import "time"
import "encoding/json"
import "io/ioutil"

type config struct {
	Scan_interval int
	Httptype      string
}

func fromjson(src string, v interface{}) error {
	return json.Unmarshal([]byte(src), v)
}

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
	configfile, err := ioutil.ReadFile("./config.json")
	if err != nil {
		panic(err)
	}
	var conf config
	err = fromjson(string(configfile), &conf)
	if err != nil {
		panic(err)
	}

	for {
		m, err := scanfiles(".")
		if err != nil {
			panic(err)
		}
		fmt.Println(m)
		time.Sleep(time.Duration(conf.Scan_interval) * time.Second)
	}
}
