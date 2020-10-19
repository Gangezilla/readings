package main

import (
	"io/ioutil"
	"os"
	"strconv"
)

var zippedString string = ""

func fileExists(filename string) bool {
	_, err := os.Stat(filename)
	if os.IsNotExist(err) {
		return false
	}
	return true
}

func doFilesExist(filenames []string) bool { // should maybe be a pointer dunno, investigate later.
	overallResult := true
	for _, filename := range filenames {
		result := fileExists(filename)
		if !result {
			overallResult = false
			break
		}
	}
	return overallResult
}

func processFile(filename string) {
	// not v efficient, just pulling it all into memory.
	// if we wanted to expand on this we'd page through the file but lazy and I have a lot of RAM
	file, error := ioutil.ReadFile(filename)
	if error != nil {
		os.Exit(1)
	}

	lastChar := ""
	currentCount := int64(0)

	for _, char := range file {
		currentChar := string(char)

		if lastChar != currentChar {
			binaryNum := strconv.FormatInt(currentCount, 2)
			temp := string(binaryNum) + currentChar + " "
			zippedString = zippedString + temp
			lastChar = currentChar
			currentCount = 0
		} else {
			currentCount++
		}
	}
}

func writeToFile() {
	err := ioutil.WriteFile("newzip.zip", []byte(zippedString), 0644)
	if err != nil {
		os.Exit(1)
	}
	os.Exit(0)
}

func main() {
	files := os.Args[1:]
	if !doFilesExist(files) {
		os.Exit(1)
	}
	for _, file := range files {
		processFile(file)
	}
	writeToFile()
}
