CXX = c++ # Especificação de compilador
CXXFLAGS = -Wall -Wextra
LDFLAGS = -L/usr/lib -lCatch2WithMain #-lCatch2 # Link bibliotecas Catch2
LXMLFLAGS = pkg-config libxml++-2.6 --cflags --libs # Link bliblotecas libxml++

test_map_generator : build/map_generator.o
	$(CXX) $(CXXFLAGS) -g test/test_map_generator.cpp build/map_generator.o $(LDFLAGS) -I include/ -o diagnosis.exe

build/map_generator.o : src/map_generator.cpp
	$(CXX) $(CXXFLAGS) -c src/map_generator.cpp -o build/map_generator.o -I include/