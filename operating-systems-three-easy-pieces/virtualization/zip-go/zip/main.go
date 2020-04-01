package main

import (
	"os"
)

var result string = ""

func checkIfFilesExist(files []string) bool { // should maybe be a pointer dunno, investigate later.

}

func processFile(file string) {
	currentChar := ""
	currentCount := 0
	// open and read file
	// make sure we have the text representation of the file.
	// go through the string adding currentChar to above, iterating the count
	// when nextChar is diff from currentChar, convert number to binary and char and add it to result
}

func main() {
	files := os.Args[1:]
	doFilesExist := checkIfFilesExist(files)
	if !doFilesExist {
		os.Exit(1)
	}
	for _, file := range files {
		processFile(file)
	}
	// check that files are valid
}

// check for number of files, loop through each one.
// read in a file
// iterate through the string until you find a different character
// the whole time you're adding a number up with the current count and putting that into a string
// output to another file. ta-da.
