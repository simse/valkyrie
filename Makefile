build:
	- g++ valkyrie.cpp -o valkyrie

.PHONY: build

run:
	- g++ valkyrie.cpp -o tmp && ./tmp && rm tmp

.PHONY: run