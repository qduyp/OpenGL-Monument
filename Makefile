CXX = g++
INCLUDES = -I/usr/include/glm/ -I/usr/include/GL/ 
LIBS = -lGL -lglut -lGLEW -lfreeimage -lc
CFLAGS = -g -Wall
FLAGS = ${CFLAGS} ${LIBS} ${INCLUDES}
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = beleg

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CXX) $(OBJECTS) $(FLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(FLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	@echo "Cleanup complete"

.PHONY: remove
remove: clean
	$(RM) $(BINDIR)/$(TARGET)
	@echo "Cleanup complete"
