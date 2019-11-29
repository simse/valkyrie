build:
	- g++ valkyrie.cpp -llexbor -o valkyrie

.PHONY: build

run:
	- g++ valkyrie.cpp -llexbor -o tmp && ./tmp && rm tmp

.PHONY: run