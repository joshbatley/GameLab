package main

import (
	"os"
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
	projectFolder := createFolder(getProjectRoot(), w.getFullName())
	srcFolder := createFolder(projectFolder, "src")
	engineFolder := createFolder(srcFolder, "Engine")
	assetFolder := createFolder(projectFolder, "assets")

	w.copyTemplateRootFiles(projectFolder)
	w.copyTemplateTypeFiles(projectFolder)
	w.updateTemplateFiles(projectFolder)
	w.generateGameMainFile(srcFolder)
	w.generateEngineHeader(engineFolder)
	w.generateEngineFiles(engineFolder)

	gitAddSubmodule(assetFolder)
	gitCommit(w.getFullName())
}

func (w *Writer) generateLibraryProject() {
	folder := createFolder(getProjectRoot(), w.getFullName())

	w.copyTemplateRootFiles(folder)
	w.copyTemplateTypeFiles(folder)
	w.updateTemplateFiles(folder)
	w.generateLibraryFiles(folder)
	gitCommit(w.getFullName())
}

func (w *Writer) generateToolProject() {
	folder := createFolder(getProjectRoot(), w.getFullName())
	srcFolder := createFolder(folder, "src")
	engineFolder := createFolder(srcFolder, "Engine")
	assetFolder := createFolder(folder, "assets")

	w.copyTemplateRootFiles(folder)
	w.copyTemplateTypeFiles(folder)
	w.updateTemplateFiles(folder)
	w.generateToolMainFile(srcFolder)
	w.generateEngineHeader(engineFolder)
	w.generateEngineFiles(engineFolder)

	gitAddSubmodule(assetFolder)
	gitCommit(w.getFullName())
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
	path := filepath.Join(getProjectRoot(), TemplatePath, w.Type.toPrefix())
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
		modifiedContent := strings.Replace(content, NameReplace, w.Name, -1)
		createFile(path, file.Name(), modifiedContent)
	}
}

func (w *Writer) generateEngineHeader(folder string) {
	engineContents := "#pragma once\n\n"
	for _, lib := range w.Libraries {
		for _, f := range lib.Files {
			if strings.HasSuffix(f, ".h") {
				engineContents += "#include \"" + lib.OutPath + "/" + f + "\"\n"
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
	createFile(folder, "Engine.h", engineContents)
	createFile(folder, "Alias.h", aliasContent)
}

func (w *Writer) generateGameMainFile(folder string) {
	content := `#include "Engine/Engine.h"

int main()
{
  std::cout << "` + w.getGameTile() + `" << std::endl;
    return 0;
}
`
	createFile(folder, "main.cpp", content)
}

func (w *Writer) generateToolMainFile(folder string) {
	content := `#include "Engine/Engine.h"

int main()
{
  std::cout << "` + w.getToolTile() + `" << std::endl;
    return 0;
}
`
	createFile(folder, "main.cpp", content)
}

func (w *Writer) generateEngineFiles(folder string) {
	for _, lib := range w.Libraries {
		for _, f := range lib.Files {
			sourcePath := filepath.Join(lib.RootPath, f)
			destinationPath := filepath.Join(folder, lib.OutPath, f)
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
	createFile(folder, w.Name+".cpp", cppContent)
	createFile(folder, w.Name+".h", hContent)
}
