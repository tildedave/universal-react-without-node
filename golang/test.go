package main

import (
	"fmt"
)

func main() {
	Initialize("../bundle.js")
	Render_element("Page")
	fmt.Println("Hi Go!")
}
