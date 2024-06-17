package main

import (
	"os/exec"
	"strings"
)

const (
	BaseFolder    = "./"
	TemplatePath  = "./Tools/Template_Files"
	ConfigFile    = "config.json"
	GamePrefix    = "Game_"
	ToolPrefix    = "Tool_"
	LibraryPrefix = "Library_"
	NameReplace   = "#NAME#"
	GitAssetRepo  = "git@github.com:joshbatley/GameAssets.git"
)

type ProjectType int

const (
	Default ProjectType = iota
	Game
	Library
	Tool
)

func toPrefix(t ProjectType) string {
	switch t {
	case Tool:
		return "Tool"
	case Game:
		return "Game"
	case Library:
		return "Library"
	}
	return ""
}

type LibraryConfig struct {
	Name        string // ***.cpp.h
	OutLocation string // Engine/****
	Files       []string
	RootPath    string
}

type GameConfig struct {
	Name      string
	Increment int
}

type ToolConfig struct {
	Name string
}

func main() {
	getProjectRoot()
	r := NewReader().Run()
	options := libraryToOptions(r.Libraries)
	takenNames := r.GetAllNames()
	selectLibraries, projectName, projectType := getUserValues(options, takenNames)
	libs := stringToLibrary(selectLibraries, r.Libraries)
	if projectName == "" || projectType == Default {
		return
	}
	NewWriter(libs, projectName, projectType, r.GetLatestGameIncrement()).Run()
}

func getProjectRoot() string {
	cmd := exec.Command("git", "rev-parse", "--show-toplevel")
	output, _ := cmd.Output()
	return strings.TrimSpace(string(output))
}
