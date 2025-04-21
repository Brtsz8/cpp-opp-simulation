# Nazwa pliku wynikowego
TARGET = sim

# Kompilator
CXX = g++

# Flagi kompilatora (opcjonalnie -Wall dla ostrzeżeń)
CXXFLAGS = -Wall -std=c++17

# Flagi linkera (tutaj ncurses)
LDFLAGS = -lncurses

# Pliki źródłowe
SRCS = main.cpp config.cpp $(wildcard classes/*.cpp)

# Pliki obiektowe (zmienia .cpp na .o)
OBJS = $(SRCS:.cpp=.o)

# Domyślna reguła
all: $(TARGET)

# Jak zbudować program
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Jak zbudować pliki .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Reguła czyszcząca pliki
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean