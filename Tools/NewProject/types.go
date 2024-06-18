package main

type ProjectType int

const (
	Default ProjectType = iota
	Game
	Library
	Tool
)

func (t ProjectType) toPrefix() string {
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
	Name     string
	OutPath  string
	Files    []string
	RootPath string
}

type GameConfig struct {
	Name      string
	Increment int
}

type ToolConfig struct {
	Name string
}
