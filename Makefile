# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -I lib

# Target executable
TARGET = prog

# Source files
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp) main.cpp

# Object files directory
OBJDIR := obj

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter-out main.cpp,$(SRCS))) $(OBJDIR)/main.o

# Rule to create object files directory
$(shell mkdir -p $(OBJDIR))

# Rule to compile a .cpp file into a .o object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile main.cpp into a .o object file
$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Phony target to build all
all: $(TARGET)

# Phony target to clean up
clean:
	rm -rf $(OBJDIR) $(TARGET)
