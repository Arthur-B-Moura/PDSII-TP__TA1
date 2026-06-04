CXX = c++ # Especificação de compilador
CXXFLAGS = -Wall -Wextra
LDFLAGS = -L/usr/lib -lCatch2WithMain #-lCatch2 # Link bibliotecas Catch2

test_map_generator : build/map_generator.o
	$(CXX) $(CXXFLAGS) -g test/test_map_generator.cpp build/map_generator.o $(LDFLAGS) $(shell pkg-config --cflags --libs libxml++-2.6) -I include/ -o diagnosis.exe

test_grafo : build/grafo.o build/map_node.o
	$(CXX) $(CXXFLAGS) -g test/test_grafo.cpp build/grafo.o build/map_node.o $(LDFLAGS) -I include/ -o diagnosis.exe

test_map_node : build/map_node.o
	$(CXX) $(CXXFLAGS) -g test/test_map_node.cpp build/map_node.o $(LDFLAGS) -I include/ -o diagnosis.exe

build/grafo.o : src/grafo.cpp 
	$(CXX) $(CXXFLAGS) -c src/grafo.cpp -o build/grafo.o -I include/

build/map_node.o : src/map_node.cpp
	$(CXX) $(CXXFLAGS) -c src/map_node.cpp -o build/map_node.o -I include/

build/map_generator.o : src/map_generator.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -w -c src/map_generator.cpp -o build/map