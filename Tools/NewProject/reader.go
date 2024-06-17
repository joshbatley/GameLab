package main

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

type Reader struct {
	Libraries []LibraryConfig
	Games     []GameConfig
	Tools     []ToolConfig
}

func NewReader() *Reader {
	return &Reader{}
}

func (r *Reader) Run() *Reader {
	r.setup()
	return r
}

func (r *Reader) setup() {
	folders := getValidFolder()
	for _, file := range folders {
		r.setUpGames(file)
		r.setUpLibraries(file)
		r.setUpTool(file)
	}
}

func getValidFolder() []os.FileInfo {
	path := filepath.Join(getProjectRoot(), BaseFolder)
	f, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
	}
	defer f.Close()

	fileInfo, err := f.Readdir(-1)
	if err != nil {
		fmt.Println(err)
	}
	var validFolders []os.FileInfo
	for _, file := range fileInfo {
		if !file.IsDir() || !strings.HasPrefix(file.Name(), GamePrefix) || !strings.HasPrefix(file.Name(), LibraryPrefix) || strings.HasPrefix(file.Name(), ToolPrefix) {
			continue
		}
		validFolders = append(validFolders, file)
	}

	return fileInfo
}

func (r *Reader) setUpGames(folder os.FileInfo) {
	if !strings.HasPrefix(folder.Name(), GamePrefix) {
		return
	}
	s := strings.Split(folder.Name(), "_")
	incStr, name := s[1], s[2]
	inc, _ := strconv.Atoi(incStr)

	r.Games = append(r.Games, GameConfig{
		Name:      name,
		Increment: inc,
	})
}

func (r *Reader) setUpTool(folder os.FileInfo) {
	if !strings.HasPrefix(folder.Name(), ToolPrefix) {
		return
	}
	s := strings.Split(folder.Name(), "_")
	r.Tools = append(r.Tools, ToolConfig{
		Name: s[1],
	})
}

func (r *Reader) setUpLibraries(folder os.FileInfo) {
	if !strings.HasPrefix(folder.Name(), LibraryPrefix) {
		return
	}

	fullPath, _ := filepath.Abs(filepath.Join(getProjectRoot(), BaseFolder, folder.Name(), ConfigFile))
	cfg, err := readConfig(fullPath)
	if err != nil {
		fmt.Println("LibraryConfig found with no config", folder.Name())
		return
	}
	r.Libraries = append(r.Libraries, LibraryConfig{
		Name:        cfg.Name,
		OutLocation: cfg.OutLocation,
		Files:       cfg.Files,
		RootPath:    filepath.Join(getProjectRoot(), BaseFolder, folder.Name()),
	})
}

func (r *Reader) GetLatestGameIncrement() int {
	maxInc := 0
	for _, s := range r.Games {
		if s.Increment > maxInc {
			maxInc = s.Increment
		}
	}
	return maxInc + 1
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

func (r *Reader) GetAllNames() []string {
	var names []string
	for _, g := range r.Games {
		names = append(names, g.Name)
	}
	for _, t := range r.Tools {
		names = append(names, t.Name)
	}
	for _, l := range r.Libraries {
		names = append(names, l.Name)
	}
	return names
}
