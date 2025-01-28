package main

import (
	"encoding/hex"
	"fmt"
	"os"
)

func Reverse(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

func main() {
	var hex_code []string;
	var code string;

	if len(os.Args) < 2 {
		fmt.Println("Usage: programme <arg1> [...] <argn>")
		os.Exit(1)
	}

	for _, line := range os.Args[1:] {
		hex_code = append(hex_code, line[2:])
	}
	for _, line := range hex_code {
		bs, err := hex.DecodeString(line)
		if err != nil {
			panic(err)
		}
		code += Reverse(string(bs));

	}
	fmt.Println(string(code))
}
