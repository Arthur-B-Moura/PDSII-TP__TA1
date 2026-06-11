CXX = c++ # Especificação de compilador
CXXFLAGS = -Wall -Wextra
LDFLAGS = -L/usr/lib -lCatch2WithMain #-lCatch2 # Link bibliotecas Catch2

all: main.exe

main.exe: build/main.o build/pathfinder.o build/map_generator.o build/map.o build/grafo.o build/map_node.o
	$(CXX) $(CXXFLAGS) $^ $(shell pkg-config --cflags --libs libxml++-2.6) -o main.exe

test_pathfinder : build/pathfinder.o build/map_generator.o build/map.o build/grafo.o build/map_node.o
	$(CXX) $(CXXFLAGS) -g test/test_pathfinder.cpp build/*.o $(LDFLAGS) $(shell pkg-config --cflags --libs libxml++-2.6) -I include/ -o diagnosis.exe

test_map_generator : build/map_generator.o build/map_node.o build/grafo.o build/map.o
	$(CXX) $(CXXFLAGS) -g test/test_map_generator.cpp build/*.o $(LDFLAGS) $(shell pkg-config --cflags --libs libxml++-2.6) -I include/ -o diagnosis.exe

test_grafo : build/grafo.o build/map_node.o
	$(CXX) $(CXXFLAGS) -g test/test_grafo.cpp build/grafo.o build/map_node.o $(LDFLAGS) -I include/ -o diagnosis.exe

test_map_node : build/map_node.o
	$(CXX) $(CXXFLAGS) -g test/test_map_node.cpp build/map_node.o $(LDFLAGS) -I include/ -o diagnosis.exe

build/pathfinder.o : src/pathfinder.cpp
	$(CXX) $(CXXFLAGS) -c src/pathfinder.cpp -o build/pathfinder.o -I include/

build/map_generator.o : src/map_generator.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(shell pkg-config --cflags --libs libxml++-2.6) -w -c src/map_generator.cpp -o build/map_generator.o -I include/

build/map.o : src/map.cpp
	$(CXX) $(CXXFLAGS) -c src/map.cpp -o build/map.o -I include/

build/grafo.o : src/grafo.cpp 
	$(CXX) $(CXXFLAGS) -c src/grafo.cpp -o build/grafo.o -I include/

build/map_node.o : src/map_node.cpp
	$(CXX) $(CXXFLAGS) -c src/map_node.cpp -o build/map_node.o -I include/

build/main.o: src/main.cpp include/pathfinder.h include/map_generator.h include/map.h include/grafo.h include/map_node.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o -I include/

build/pathfinder.o: src/pathfinder.cpp include/pathfinder.h include/grafo.h include/map_node.h
	$(CXX) $(CXXFLAGS) -c src/pathfinder.cpp -o build/pathfinder.o -I include/
