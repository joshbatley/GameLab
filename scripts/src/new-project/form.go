package main

import (
	"errors"
	"github.com/charmbracelet/huh"
)

func runForm(namesTaken []string) (string, ProjectType) {
	var projectName string
	var projectType ProjectType
	huh.NewForm(
		huh.NewGroup(
			huh.NewInput().
				Title("What the projects name? (in PascalCase)").
				Value(&projectName).
				Validate(func(s string) error {
					if len(s) == 0 {
						return errors.New("project name cannot be blank")
					}
					for _, name := range namesTaken {
						if name == s {
							return errors.New("project name already taken")
						}
					}
					return nil
				}),
		),
		huh.NewGroup(
			huh.NewSelect[ProjectType]().
				Title("Project Type:").
				Options(
					huh.NewOption("Game", Game),
					huh.NewOption("Tool", Tool),
				).
				Value(&projectType),
		),
	).Run()
	return projectName, projectType
}
