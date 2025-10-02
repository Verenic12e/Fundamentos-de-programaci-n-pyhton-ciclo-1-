# Makefile para el proyecto BibliotecaDB en C++

CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS =
LDLIBS = -lstdc++fs
OBJ = main.o BibliotecaDB.o
TARGET = biblioteca

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ) $(LDLIBS)

main.o: main.cpp BibliotecaDB.h
	$(CXX) $(CXXFLAGS) -c main.cpp

BibliotecaDB.o: BibliotecaDB.cpp BibliotecaDB.h
	$(CXX) $(CXXFLAGS) -c BibliotecaDB.cpp

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
