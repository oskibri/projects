package main

import (
	"example.com/greetings"
	"fmt"
	"log"
)

func main() {
	log.SetPrefix("greetings: ")
	log.SetFlags(0)

	names := []string{"Gladys", "Samantha", "Darrin", "Oskar", "Benedicte"}
	messages, err := greetings.Hellos(names)
	if err != nil {
		log.Fatal(err)
	}

	for name, message := range messages {
		padding := 20 - len(name)
		if padding < 0 {padding = 0}
		fmt.Printf("%s:%*s%s\n", name, padding, "", message)
	}
}
