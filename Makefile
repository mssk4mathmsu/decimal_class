CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
TARGET = decimal_app
SOURCES = main.cpp decimal.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.cpp decimal.h
	$(CXX) $(CXXFLAGS) -c main.cpp

decimal.o: decimal.cpp decimal.h
	$(CXX) $(CXXFLAGS) -c decimal.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
