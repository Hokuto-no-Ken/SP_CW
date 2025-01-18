package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func main() {
	exeDir := `\\Mac\Home\Downloads\SPprj\cw_sp2__2024_2025\Release`

	if err := runExe(filepath.Join(exeDir, "cw_sp2__2024_2025.exe")); err != nil {
		fmt.Println("Помилка при запуску першої програми:", err)
		return
	}

	exeName, err := getExeName()
	if err != nil {
		fmt.Println("Помилка при отриманні назви файлу:", err)
		return
	}

	if err := runExe(filepath.Join(exeDir, exeName)); err != nil {
		fmt.Println("Помилка при запуску другої програми:", err)
		return
	}

	fmt.Println("Програма завершилася.")
}

func runExe(exePath string) error {

	if _, err := os.Stat(exePath); os.IsNotExist(err) {
		return fmt.Errorf("файл %s не знайдено", exePath)
	}

	fmt.Printf("Запуск %s...\n", exePath)

	cmd := exec.Command(exePath)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	if err := cmd.Run(); err != nil {
		return fmt.Errorf("помилка при запуску/виконанні програми %s: %w", exePath, err)
	}

	return nil
}

func getExeName() (string, error) {
	fmt.Print("Введіть назву .exe файлу для запуску: ")
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return "", scanner.Err()
	}

	exeName := scanner.Text()

	if exeName == "" {
		return "", fmt.Errorf("не було введено назви файлу")
	}

	if !strings.HasSuffix(exeName, ".exe") {
		exeName += ".exe"
	}

	return exeName, nil
}
