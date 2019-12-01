build:
	- g++ -Wall -std=c++0x -Llibraries -lspdlog valkyrie.cpp nodes/*.cpp core/*.cpp utils/*.cpp -Iincludes -o valkyrie

.PHONY: build

run:
	- g++ -Wall -std=c++0x -Llibraries -lspdlog valkyrie.cpp nodes/*.cpp core/*.cpp utils/*.cpp -Iincludes -o tmp && ./tmp && rm tmp

.PHONY: run