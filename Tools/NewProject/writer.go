package main

import (
	"fmt"
	"io"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"
)

type Writer struct {
	Libraries     []LibraryConfig
	Name          string
	Type          ProjectType
	GameIncrement int
}

func NewWriter(libraries []LibraryConfig, name string, t ProjectType, inc int) *Writer {
	return &Writer{
		Libraries:     libraries,
		Name:          name,
		Type:          t,
		GameIncrement: inc,
	}
}

func (w *Writer) Run() {
	if w.Type == Game {
		w.generateGameProject()
	}
	if w.Type == Library {
		w.generateLibraryProject()
	}

	if w.Type == Tool {
		w.generateToolProject()
	}
}

func (w *Writer) generateGameProject() {
	folder := createFolder(w.getFullName())
	w.copyTemplateFiles(folder)
	w.updateTemplateFiles(folder)
	src := generateRootFolder(folder)
	w.generateGameMainFile(src)
	engineSrc := generateEngineFolder(src)
	generateEngineHeader(w.Libraries, engineSrc)
	w.generateEngineFiles(engineSrc)
	assetSrc := generateAssetFolder(folder)
	w.gitAddSubmodule(assetSrc)
	w.gitCommit()
}

func (w *Writer) generateLibraryProject() {
	folder := createFolder(w.getFullName())
	w.copyTemplateFiles(folder)
	w.updateTemplateFiles(folder)
	w.generateLibraryFiles(folder)
	w.gitCommit()
}

func (w *Writer) generateToolProject() {
	folder := createFolder(w.getFullName())
	w.copyTemplateFiles(folder)
	w.updateTemplateFiles(folder)
	src := generateRootFolder(folder)
	w.generateToolMainFile(src)
	engineSrc := generateEngineFolder(src)
	generateEngineHeader(w.Libraries, engineSrc)
	w.generateEngineFiles(engineSrc)
	assetSrc := generateAssetFolder(folder)
	w.gitAddSubmodule(assetSrc)
	w.gitCommit()
}

func (w *Writer) getFullName() string {
	switch w.Type {
	case Library:
		return LibraryPrefix + w.Name
	case Game:
		return GamePrefix + strconv.Itoa(w.GameIncrement) + "_" + w.Name
	case Tool:
		return ToolPrefix + w.Name
	}
	return ""
}

func (w *Writer) getGameTile() string {
	return "Game " + strconv.Itoa(w.GameIncrement) + " - " + w.Name
}

func (w *Writer) getToolTile() string {
	return "Tool - " + w.Name
}

func (w *Writer) copyTemplateFiles(folder string) {
	path := filepath.Join(getProjectRoot(), TemplatePath)
	fileInfos, _ := os.ReadDir(path)
	for _, file := range fileInfos {
		if !file.IsDir() {
			sourcePath := filepath.Join(path, file.Name())
			destinationPath := filepath.Join(folder, file.Name())
			copyFile(sourcePath, destinationPath)
		} else {
			nestedFileInfo, _ := os.ReadDir(filepath.Join(path, file.Name()))
			for _, nestedFile := range nestedFileInfo {
				sourcePath := filepath.Join(path, toPrefix(w.Type), nestedFile.Name())
				destinationPath := filepath.Join(folder, nestedFile.Name())
				copyFile(sourcePath, destinationPath)
			}

		}
	}
}

func copyFile(sourcePath, destinationPath string) error {
	sourceFile, err := os.Open(sourcePath)
	if err != nil {
		return err
	}
	defer sourceFile.Close()

	destFolder := filepath.Dir(destinationPath)
	if _, err := os.Stat(destFolder); os.IsNotExist(err) {
		err = os.MkdirAll(destFolder, 0755)
		if err != nil {
			return err
		}
	}

	destFile, err := os.Create(destinationPath)
	if err != nil {
		return err
	}
	defer destFile.Close()

	_, err = io.Copy(destFile, sourceFile)
	if err != nil {
		return err
	}

	return nil
}

func createFolder(name string) string {
	path := filepath.Join(getProjectRoot(), name)
	err := os.Mkdir(path, os.ModePerm)
	if err != nil {
		fmt.Println("Error creating directory:", err)
	}
	return path
}

func (w *Writer) updateTemplateFiles(folder string) {
	path := filepath.Join(folder)
	fileInfos, _ := os.ReadDir(path)
	for _, file := range fileInfos {
		content, err := os.ReadFile(filepath.Join(path, file.Name()))
		if err != nil {
			fmt.Println("Error reading file:", err)
			return
		}

		// Convert content to string
		fileContent := string(content)

		modifiedContent := strings.Replace(fileContent, NameReplace, w.Name, -1)

		// Write the modified content back to the file
		err = os.WriteFile(filepath.Join(path, file.Name()), []byte(modifiedContent), 0644)
		if err != nil {
			fmt.Println("Error writing file:", err)
			return
		}

	}

}

func generateRootFolder(folder string) string {
	err := os.Mkdir(filepath.Join(folder, "src"), os.ModePerm)
	if err != nil {
		fmt.Println("Error creating directory:", err)
	}
	return filepath.Join(folder, "src")
}

func generateEngineFolder(folder string) string {
	err := os.Mkdir(filepath.Join(folder, "Engine"), os.ModePerm)
	if err != nil {
		fmt.Println("Error creating directory:", err)
	}
	return filepath.Join(folder, "Engine")
}

func generateEngineHeader(libraries []LibraryConfig, folder string) {
	engineContents := "#pragma once\n\n"
	for _, lib := range libraries {
		for _, f := range lib.Files {
			if strings.HasSuffix(f, ".h") {
				engineContents += "#include \"" + lib.OutLocation + "/" + f + "\"\n"
			}
		}
	}
	engineContents += "\n#include \"./Alias.h\""
	aliasContent := `#pragma once

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <entt/entt.hpp>

namespace Engine {
    using World = entt::registry;
    using Entity = entt::entity;

    using Texture = SDL_Texture *;
    using Font = TTF_Font *;

    template<typename ResourceType>
    struct Resource {
        ResourceType &data;
        ResourceType &into()
        {
            return data;
        }
    };
}`
	os.WriteFile(filepath.Join(folder, "Engine.h"), []byte(engineContents), 0644)
	os.WriteFile(filepath.Join(folder, "Alias.h"), []byte(aliasContent), 0644)
}

func (w *Writer) generateGameMainFile(folder string) {
	mainContent := `#include "Engine/Engine.h"

int main()
{
  std::cout << "` + w.getGameTile() + `" << std::endl;
    return 0;
}
`
	os.WriteFile(filepath.Join(folder, "main.cpp"), []byte(mainContent), 0644)
}

func (w *Writer) generateToolMainFile(folder string) {
	mainContent := `#include "Engine/Engine.h"

int main()
{
  std::cout << "` + w.getToolTile() + `" << std::endl;
    return 0;
}
`
	os.WriteFile(filepath.Join(folder, "main.cpp"), []byte(mainContent), 0644)
}

func (w *Writer) generateEngineFiles(folder string) {
	for _, lib := range w.Libraries {
		for _, f := range lib.Files {
			sourcePath := filepath.Join(lib.RootPath, f)
			destinationPath := filepath.Join(folder, lib.OutLocation, f)
			copyFile(sourcePath, destinationPath)
		}
	}
}

func (w *Writer) generateLibraryFiles(folder string) {
	cppContent := `#include "` + w.Name + `.h"

`
	hContent := `#pragma once

class ` + w.Name + ` {

};`

	os.WriteFile(filepath.Join(folder, w.Name+".cpp"), []byte(cppContent), 0644)
	os.WriteFile(filepath.Join(folder, w.Name+".h"), []byte(hContent), 0644)
}

func generateAssetFolder(folder string) string {
	err := os.Mkdir(filepath.Join(folder, "assets"), os.ModePerm)
	if err != nil {
		fmt.Println("Error creating directory:", err)
	}
	return filepath.Join(folder, "assets")
}

func (w *Writer) gitAddSubmodule(folder string) {
	originalDir, _ := os.Getwd()
	defer os.Chdir(originalDir)
	os.Chdir(getProjectRoot())

	cmd := exec.Command("git", "submodule", "add", GitAssetRepo, filepath.Join(w.getFullName()+"/asset/private"))
	cmd.Run()
}

func (w *Writer) gitCommit() {
	originalDir, _ := os.Getwd()
	defer os.Chdir(originalDir)
	os.Chdir(getProjectRoot())
	cmd := exec.Command("git", "add", ".")
	cmd.Run()
	cmd = exec.Command("git", "commit", "-m", "Added new Project: "+w.getFullName())
	cmd.Run()
}
