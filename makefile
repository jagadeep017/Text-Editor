CXX = g++

LDFLAGS = -lncursesw -ltinfo

SOURCES = $(wildcard *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = ./txtedit

DEPENDS = $(OBJECTS:.o=.d)

all: $(TARGET)

PKG_MGR := $(shell \
    if command -v apt-get >/dev/null 2>&1; then echo "apt"; \
    elif command -v dnf >/dev/null 2>&1; then echo "dnf"; \
    elif command -v pacman >/dev/null 2>&1; then echo "pacman"; \
    elif command -v zypper >/dev/null 2>&1; then echo "zypper"; \
    else echo "unknown"; fi)

ifeq ($(PKG_MGR),apt)
  NCURSES_PKG = libncursesw-dev
else ifeq ($(PKG_MGR),dnf)
  NCURSES_PKG = ncurses-devel
else ifeq ($(PKG_MGR),pacman)
  NCURSES_PKG = ncurses
else ifeq ($(PKG_MGR),zypper)
  NCURSES_PKG = ncurses-devel
endif

HAS_NCURSES := $(shell pkg-config --exists ncursesw 2>/dev/null && echo "yes")

check-deps:
ifneq ($(HAS_NCURSES),yes)
ifeq ($(PKG_MGR),unknown)
	$(error Cannot install ncurses automatically - please install ncurses development package manually)
else
	@echo "Installing ncurses using $(PKG_MGR)..."
	@if [ "$(PKG_MGR)" = "apt" ]; then sudo apt-get update && sudo apt-get install -y $(NCURSES_PKG); \
	elif [ "$(PKG_MGR)" = "dnf" ]; then sudo dnf install -y $(NCURSES_PKG); \
	elif [ "$(PKG_MGR)" = "pacman" ]; then sudo pacman -Sy --noconfirm $(NCURSES_PKG); \
	elif [ "$(PKG_MGR)" = "zypper" ]; then sudo zypper install -y $(NCURSES_PKG); fi
endif
endif

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