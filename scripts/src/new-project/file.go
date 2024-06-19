package main

import (
	"fmt"
	"io"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func getProjectRoot() string {
	cmd := exec.Command("git", "rev-parse", "--show-toplevel")
	output, _ := cmd.Output()
	return strings.TrimSpace(string(output))
}

func readFolders(path string) []os.FileInfo {
	f, _ := os.Open(path)
	defer f.Close()

	fileInfo, _ := f.Readdir(-1)
	var validFolders []os.FileInfo
	for _, file := range fileInfo {
		if !file.IsDir() {
			continue
		}
		validFolders = append(validFolders, file)
	}

	return fileInfo
}

func readFile(path string) string {
	content, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("Error reading file:", err)
	}
	return string(content)
}

func createFolder(source, folder string) string {
	path := filepath.Join(source, folder)
	err := os.Mkdir(path, os.ModePerm)
	if err != nil {
		fmt.Println("Error creating directory:", err)
	}
	return path
}

func copyFile(sourcePath, destinationPath string) {
	sourceFile, err := os.Open(sourcePath)
	if err != nil {
		fmt.Println("Error opening file:", err)
	}
	defer sourceFile.Close()

	destFolder := filepath.Dir(destinationPath)
	if _, err := os.Stat(destFolder); os.IsNotExist(err) {
		err = os.MkdirAll(destFolder, 0755)
		if err != nil {
			fmt.Println("Error creating folder:", err)
		}
	}

	destFile, err := os.Create(destinationPath)
	if err != nil {
		fmt.Println("Error creating file:", err)
	}
	defer destFile.Close()

	_, err = io.Copy(destFile, sourceFile)
	if err != nil {
		fmt.Println("Error copying file:", err)
	}
}

func createFile(destination, name, contents string) {
	if err := os.WriteFile(filepath.Join(destination, name), []byte(contents), 0644); err != nil {
		fmt.Println("Error creating file:", err)
	}
}

func copyFolderContents(source, destination string) {
	originalDir, _ := os.Getwd()
	defer os.Chdir(originalDir)
	os.Chdir(getProjectRoot())

	cmd := exec.Command("cp", "-r", source+"/*", destination)
	if err := cmd.Run(); err != nil {
		fmt.Println("Error copying file:", err)
	}
}
