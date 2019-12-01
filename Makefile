build:
	- g++ valkyrie.cpp -I libraries/*.cpp nodes/*.cpp core/*.cpp utils/*.cpp -o valkyrie

.PHONY: build

run:
	- g++ valkyrie.cpp -I libraries/*.cpp nodes/*.cpp core/*.cpp utils/*.cpp -o tmp && ./tmp && rm tmp

.PHONY: run