package main

import (
	"os"
	"path/filepath"
	"strings"
)

type Writer struct {
	Project Project
}

func NewWriter(project Project) *Writer {
	return &Writer{
		Project: project,
	}
}

func (w *Writer) Run() {
	if w.Project.Type() == Game {
		w.generateGameProject()
	}
	if w.Project.Type() == Tool {
		w.generateToolProject()
	}
}

func (w *Writer) generateGameProject() {
	projectFolder := createFolder(filepath.Join(getProjectRoot(), GamesPath), w.Project.Name())
	srcFolder := createFolder(projectFolder, "src")
	engineFolder := createFolder(projectFolder, "Engine")
	createFolder(projectFolder, "assets")

	w.copyTemplateRootFiles(projectFolder)
	w.copyTemplateTypeFiles(projectFolder)
	w.updateTemplateFiles(projectFolder)
	w.generateMainFile(srcFolder)
	copyFolderContents(filepath.Join(getProjectRoot(), EnginePath), engineFolder)

	addSubmoduleAndCommit(filepath.Join(w.Project.Name(), "assets"), w.Project.Name())
}

func (w *Writer) generateToolProject() {
	projectFolder := createFolder(filepath.Join(getProjectRoot(), ToolsPath), w.Project.Name())
	srcFolder := createFolder(projectFolder, "src")
	engineFolder := createFolder(projectFolder, "Engine")
	createFolder(projectFolder, "assets")

	w.copyTemplateRootFiles(projectFolder)
	w.copyTemplateTypeFiles(projectFolder)
	w.updateTemplateFiles(projectFolder)
	w.generateMainFile(srcFolder)
	copyFolderContents(filepath.Join(getProjectRoot(), EnginePath), engineFolder)

	addSubmoduleAndCommit(filepath.Join(w.Project.Name(), "assets"), w.Project.Name())
}

func (w *Writer) copyTemplateRootFiles(folder string) {
	path := filepath.Join(getProjectRoot(), TemplatePath)
	fileInfos, _ := os.ReadDir(path)
	for _, file := range fileInfos {
		if !file.IsDir() {
			sourcePath := filepath.Join(path, file.Name())
			destinationPath := filepath.Join(folder, file.Name())
			copyFile(sourcePath, destinationPath)
		}
	}
}

func (w *Writer) copyTemplateTypeFiles(folder string) {
	path := filepath.Join(getProjectRoot(), TemplatePath, w.Project.Type().toPrefix())
	fileInfos, _ := os.ReadDir(path)
	for _, file := range fileInfos {
		sourcePath := filepath.Join(path, file.Name())
		destinationPath := filepath.Join(folder, file.Name())
		copyFile(sourcePath, destinationPath)
	}
}

func (w *Writer) updateTemplateFiles(folder string) {
	path := filepath.Join(folder)
	fileInfos, _ := os.ReadDir(path)
	for _, file := range fileInfos {
		if file.IsDir() {
			continue
		}
		content := readFile(filepath.Join(path, file.Name()))
		modifiedContent := strings.Replace(content, NameReplace, w.Project.Name(), -1)
		createFile(path, file.Name(), modifiedContent)
	}
}

func (w *Writer) generateMainFile(folder string) {
	content := `#include "Engine.h"

int main()
{
  std::cout << "` + w.Project.Title() + `" << std::endl;
    return 0;
}
`
	createFile(folder, "main.cpp", content)
}
