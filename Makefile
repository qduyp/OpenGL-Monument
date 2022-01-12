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
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(CXX) $(OBJECTS) $(FLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@$(CXX) $(FLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	$(RM) $(OBJECTS)
	@echo "Cleanup complete"

.PHONY: remove
remove: clean
	$(RM) $(BINDIR)/$(TARGET)
	@echo "Remove complete"
