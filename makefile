# GNU Make
# C++ compiler
CXX = g++

# Linker flags to include the ncurses wide-character library
LDFLAGS = -lncursesw -ltinfo

# Source, Object, and Target files
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = ./txtedit

# Dependency files
DEPENDS = $(OBJECTS:.o=.d)

# Default target: check dependencies first, then build
all: deps $(TARGET)

# New target to check and install dependencies
deps:
	@if ! pkg-config --exists ncursesw; then \
		echo "-> Required library 'ncursesw' not found. Attempting installation..."; \
		if command -v apt-get >/dev/null; then \
			echo "--> Using apt-get (Debian/Ubuntu)..."; \
			sudo apt-get update && sudo apt-get install -y libncursesw5-dev; \
		elif command -v dnf >/dev/null; then \
			echo "--> Using dnf (Fedora/RHEL)..."; \
			sudo dnf install -y ncurses-devel; \
		elif command -v pacman >/dev/null; then \
			echo "--> Using pacman (Arch Linux)..."; \
			sudo pacman -S --noconfirm ncurses; \
		else \
			echo "ERROR: Could not find a supported package manager (apt, dnf, pacman)."; \
			echo "Please install the ncurses development library for your system manually."; \
			exit 1; \
		fi; \
	else \
		echo "-> Dependency 'ncursesw' is satisfied."; \
	fi

# Rule to link the object files into the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Include dependency files
-include $(DEPENDS)

# Debug build target
debug: CXX += -g
debug: all

# Clean target to remove generated files
clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

# Declare targets that are not files
.PHONY: all clean deps