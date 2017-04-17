package main

import "fmt"
import "path/filepath"
import "os"
import "os/signal"
import "time"
import "encoding/json"
import "io/ioutil"
import "syscall"

type config struct {
	Scan_interval         int
	Scan_location         string
	Verbose_file_printing bool
	Exit_stats_display    bool
	Httptype              string
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

func scanloop(done chan bool, sig chan os.Signal, location string, interval int, verbose bool) {
Scanloop:
	for {
		m, err := scanfiles(location)
		if err != nil {
			panic(err)
		}
		if verbose != false {
			fmt.Println("\n\nNEXT SCAN\n\n")
			for key, _ := range m {
				fmt.Println(key, m[key])
			}
		}
		if interval != 0 {
			time.Sleep(time.Duration(interval) * time.Second)
		}
		select {
		case signal := <-sig:
			if signal == syscall.SIGINT {
				break Scanloop
			}
		default:
			continue
		}
	}
	done <- true
}

func main() {
	ossig := make(chan os.Signal, 1)
	done := make(chan bool, 1)
	configfile, err := ioutil.ReadFile("./config.json")
	if err != nil {
		panic(err)
	}

	var conf config
	err = fromjson(string(configfile), &conf)
	if err != nil {
		panic(err)
	}

	signal.Notify(ossig, syscall.SIGINT, syscall.SIGTERM)

	go scanloop(done, ossig, conf.Scan_location, conf.Scan_interval, conf.Verbose_file_printing)

	<-done
	fmt.Println("EXITING...")
}
