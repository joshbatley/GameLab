package main

import (
	"os"
	"path/filepath"
	"slices"
	"strconv"
	"strings"
)

type Reader struct {
	Games []GameConfig
	Tools []ToolConfig
}

func NewReader() *Reader {
	return &Reader{}
}

func (r *Reader) Run() *Reader {
	folders := getValidFolder()
	for _, file := range folders {
		r.setUpGames(file)
		r.setUpTools(file)
	}
	return r
}

func getValidFolder() []os.FileInfo {
	gameFolders := readFolders(filepath.Join(getProjectRoot(), BaseFolder, GamesPath))
	toolFolders := readFolders(filepath.Join(getProjectRoot(), BaseFolder, ToolsPath))
	folders := slices.Concat(gameFolders, toolFolders)
	var projects []os.FileInfo
	for _, folder := range folders {
		if strings.HasPrefix(folder.Name(), GamePrefix) || strings.HasPrefix(folder.Name(), ToolPrefix) {
			projects = append(projects, folder)
		}
	}
	return projects
}

func (r *Reader) setUpGames(folder os.FileInfo) {
	if !strings.HasPrefix(folder.Name(), GamePrefix) {
		return
	}

	s := strings.Split(folder.Name(), "-")
	incStr, name := s[1], s[2]
	inc, _ := strconv.Atoi(incStr)

	r.Games = append(r.Games, GameConfig{
		name:      name,
		increment: inc,
	})
}

func (r *Reader) setUpTools(folder os.FileInfo) {
	if !strings.HasPrefix(folder.Name(), ToolPrefix) {
		return
	}

	s := strings.Split(folder.Name(), "-")
	incStr, name := s[1], s[2]
	inc, _ := strconv.Atoi(incStr)

	r.Tools = append(r.Tools, ToolConfig{
		name:      name,
		increment: inc,
	})
}

func (r *Reader) getLatestIncrement() int {
	maxInc := 0
	for _, s := range r.Games {
		if s.increment > maxInc {
			maxInc = s.increment
		}
	}
	for _, s := range r.Tools {
		if s.increment > maxInc {
			maxInc = s.increment
		}
	}
	return maxInc + 1
}

func (r *Reader) getAllNames() []string {
	var names []string
	for _, g := range r.Games {
		names = append(names, g.name)
	}
	for _, t := range r.Tools {
		names = append(names, t.name)
	}
	return names
}
