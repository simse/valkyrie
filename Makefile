build:
	- g++ -Wall -std=c++14 -Llibraries -lspdlog valkyrie.cpp nodes/*.cpp core/*.cpp utils/*.cpp -Iincludes -o valkyrie

.PHONY: build

run:
	- g++ -Wall -std=c++14 valkyrie.cpp nodes/*.cpp core/*.cpp utils/*.cpp -Iincludes -Llibraries -o tmp && ./tmp && rm tmp

.PHONY: run