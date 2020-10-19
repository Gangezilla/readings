package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
	"strconv"
	"strings"
)

var unzippedString = ""

func fileExists(filename string) bool {
	_, err := os.Stat(filename)
	if os.IsNotExist(err) {
		return false
	}
	return true
}

func writeToFile() {
	err := ioutil.WriteFile("unzipped.zip", []byte(unzippedString), 0644)
	if err != nil {
		os.Exit(1)
	}
	os.Exit(0)
}

func processFile(filename string) {
	file, error := ioutil.ReadFile(filename)
	if error != nil {
		os.Exit(1)
	}

	blobs := strings.Split(string(file), " ")

	for _, blob := range blobs {
		r := regexp.MustCompile(`(\d+)(\w)`)
		submatches := r.FindStringSubmatch(blob)

		fmt.Println(submatches)
		strCount, char := submatches[1], submatches[2]
		binaryCount, err := strconv.ParseInt(strCount, 2, 64)
		if err != nil {
			os.Exit(1)
		}
		count, err := strconv.Atoi(strconv.FormatInt(binaryCount, 10))
		fmt.Println(count, char)

		unzippedString += strings.Repeat(char, count)
	}
}

func main() {
	file := os.Args[1]
	if !fileExists(file) {
		os.Exit(1)
	}
	processFile(file)
	writeToFile()
}

// lol, this is really buggy. but i'm getting the feel of putting together basic go programs, woo.
