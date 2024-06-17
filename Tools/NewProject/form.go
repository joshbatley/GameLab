package main

import (
	"errors"
	"github.com/charmbracelet/huh"
)

func (l *LibraryConfig) toHuhOption() huh.Option[string] {
	return huh.NewOption(l.Name, l.Name)
}

func libraryToOptions(libs []LibraryConfig) []huh.Option[string] {
	var libOption []huh.Option[string]
	for _, lib := range libs {
		libOption = append(libOption, lib.toHuhOption())
	}
	return libOption
}

func stringToLibrary(s []string, libs []LibraryConfig) []LibraryConfig {
	var selectLibs []LibraryConfig
	for _, selected := range s {
		for _, lib := range libs {
			if selected == lib.Name {
				selectLibs = append(selectLibs, lib)
			}
		}
	}
	return selectLibs
}

func getUserValues(options []huh.Option[string], namesTaken []string) ([]string, string, ProjectType) {
	var selectLibraries []string
	var projectName string
	var projectType ProjectType
	form := huh.NewForm(
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
					huh.NewOption("Library", Library),
					huh.NewOption("Tool", Tool),
				).
				Value(&projectType),
		),
	)
	form.Run()
	if projectType != Library {
		form = huh.NewForm(huh.NewGroup(
			huh.NewMultiSelect[string]().
				Title("Which libraries do you want to use?").
				Options(options...).
				Value(&selectLibraries),
		))
		form.Run()
	}

	return selectLibraries, projectName, projectType
}
