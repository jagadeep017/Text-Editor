CXX = g++

LDFLAGS = -lcurses

SOURCES = $(wildcard *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = ./txtedit

DEPENDS = $(OBJECTS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

-include $(DEPENDS)

debug: CXX += -g
debug: all


clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

.PHONY: all clean