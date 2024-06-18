package main

const (
	BaseFolder       = "./"
	TemplatePath     = "./Tools/Template_Files"
	ConfigFile       = "config.json"
	GamePrefix       = "Game_"
	ToolPrefix       = "Tool_"
	LibraryPrefix    = "Library_"
	NameReplace      = "#NAME#"
	NameReplaceLower = "#NAME_L#"
	GitAssetRepo     = "git@github.com:joshbatley/GameAssets.git"
)

func main() {
	r := NewReader().Run()
	options := libraryToOptions(r.Libraries)
	takenNames := r.getAllNames()

	selectLibrariesNames, projectName, projectType := getUserValues(options, takenNames)
	selectedLibraries := stringToLibrary(selectLibrariesNames, r.Libraries)

	if projectName == "" || projectType == Default {
		return
	}

	NewWriter(selectedLibraries, projectName, projectType, r.getLatestGameIncrement()).Run()
}
