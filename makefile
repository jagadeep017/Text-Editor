CXX = g++

LDFLAGS = -lcurses

SOURCES = $(wildcard *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = a.out

DEPENDS = $(OBJECTS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

-include $(DEPENDS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

.PHONY: all clean