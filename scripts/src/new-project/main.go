package main

const (
	BaseFolder   = "./"
	TemplatePath = "scripts/src/static-files"
	GamePrefix   = "Game-"
	ToolPrefix   = "Tool-"
	GamesPath    = "Games"
	ToolsPath    = "Tools"
	EnginePath   = "Engine"
	NameReplace  = "#NAME#"
	GitAssetRepo = "git@github.com:joshbatley/GameAssets.git"
)

func main() {
	r := NewReader().Run()
	projectName, projectType := runForm(r.getAllNames())
	project := GenerateProject(projectName, projectType, r.getLatestIncrement())
	NewWriter(project).Run()
}
