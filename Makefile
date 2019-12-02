build:
	- g++ -std=c++17 -Llibraries valkyrie.cpp nodes/*.cpp core/*.cpp utils/*.cpp -Iincludes -o valkyrie

.PHONY: build

run:
	- g++ -Wall -std=c++17 valkyrie.cpp nodes/*.cpp core/*.cpp utils/*.cpp -Iincludes -Llibraries -o tmp && ./tmp && rm tmp

.PHONY: run