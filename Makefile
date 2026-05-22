CXX = c++ # Especificação de compilador
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lCatch2Main -lCatch2 # Link bibliotecas Catch2

test_map_node : build/map_node.o
	$(CXX) $(CXXFLAGS) -g $(LDFLAGS) test/test_map_node.cpp build/map_node.o -I include/ -o diagnosis.exe

build/map_node.o : src/map_node.cpp
	$(CXX) $(CXXFLAGS) -c src/map_node.cpp -o build/map_node.o -I include/