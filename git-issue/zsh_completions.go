package main

import (
	"flag"
	"fmt"
	"strings"
)

func PrintCompletions(name string) {
	var cmpl []string
	flag.VisitAll(func(f *flag.Flag) {
		cmpl = append(
			cmpl, fmt.Sprintf("\t'-%s[%s]' \\\n", f.Name, f.Usage))
	})
	fmt.Print(
		fmt.Sprintf("#compdef %s\n\n_arguments -s \\\n%s\n\n",
			name, strings.Join(cmpl, " ")),
	)
}
