build:
	- g++ valkyrie.cpp -o valkyrie

.PHONY: build

run:
	- g++ valkyrie.cpp -I libraries/*.cpp nodes/*.cpp -o tmp && ./tmp && rm tmp

.PHONY: run