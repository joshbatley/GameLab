package main

import "strconv"

type ProjectType int

const (
	Default ProjectType = iota
	Game
	Tool
)

func (t ProjectType) toPrefix() string {
	switch t {
	case Tool:
		return "Tool"
	case Game:
		return "Game"
	default:
		return ""
	}
}

type GameConfig struct {
	name      string
	increment int
}

type ToolConfig struct {
	name      string
	increment int
}

type Project interface {
	Name() string
	Type() ProjectType
	Title() string
}

func GenerateProject(name string, projectType ProjectType, increment int) Project {
	if name == "" || projectType == Default {
		panic("Project name or ProjectType is required")
	}

	if projectType == Game {
		return GameConfig{name: name, increment: increment}
	}
	if projectType == Tool {
		return ToolConfig{name: name, increment: increment}
	}

	panic("Invalid project type")
}

func (g GameConfig) Type() ProjectType {
	return Game
}

func (t ToolConfig) Type() ProjectType {
	return Tool
}

func (g GameConfig) Title() string {
	return "Game " + strconv.Itoa(g.increment) + " - " + g.name
}

func (t ToolConfig) Title() string {
	return "Tool " + strconv.Itoa(t.increment) + " - " + t.name
}

func (g GameConfig) Name() string {
	return GamePrefix + strconv.Itoa(g.increment) + "-" + g.name
}

func (t ToolConfig) Name() string {
	return ToolPrefix + strconv.Itoa(t.increment) + "-" + t.name
}
