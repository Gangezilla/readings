package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strings"
)

func spawnNewProcess(args []string) {
	fmt.Println(args[0])
	fmt.Println(args[1:])

	cmd := exec.Command(args[0], args[1:]...)
	dateOut, err := cmd.Output()
	if err != nil {
		panic(err)
	}
	fmt.Println("> date")
	fmt.Println(string(dateOut))
}

func processCommand(command string) {
	commandWithoutNewLine := strings.TrimSuffix(command, "\n")
	args := strings.Split(commandWithoutNewLine, " ")
	if args[0] == "exit" {
		os.Exit(0)
	} else if args[0] == "cd" {
		os.Chdir(args[1])
	} else if args[0] == "path" {
		fmt.Println("path something")
	} else {
		spawnNewProcess(args)
	}
}

func main() {
	buf := bufio.NewReader(os.Stdin)

	for {
		fmt.Print("schell> ")
		command, err := buf.ReadBytes('\n')
		if err != nil {
			fmt.Println(err)
		} else {
			processCommand(string(command))
		}
	}
}
