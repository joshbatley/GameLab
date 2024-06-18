package main

import (
	"encoding/json"
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

func readFile(path string) string {
	content, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("Error reading file:", err)
	}
	return string(content)
}

func readConfig(path string) (LibraryConfig, error) {
	var val LibraryConfig
	data, err := os.ReadFile(path)
	if err != nil {
		return val, err
	}

	if err := json.Unmarshal(data, &val); err != nil {
		return val, err
	}
	return val, nil
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
