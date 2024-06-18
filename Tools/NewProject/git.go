package main

import (
	"os"
	"os/exec"
	"path/filepath"
)

func gitAddSubmodule(assetRoot string) {
	originalDir, _ := os.Getwd()
	defer os.Chdir(originalDir)
	os.Chdir(getProjectRoot())

	cmd := exec.Command("git", "submodule", "add", GitAssetRepo, filepath.Join(assetRoot, "private"))

	cmd.Run()
}

func gitCommit(projectName string) {
	originalDir, _ := os.Getwd()
	defer os.Chdir(originalDir)
	os.Chdir(getProjectRoot())

	gitAddCmd := exec.Command("git", "add", ".")
	gitCommitCmd := exec.Command("git", "commit", "-m", "Added new Project: "+projectName)

	gitAddCmd.Run()
	gitCommitCmd.Run()
}
