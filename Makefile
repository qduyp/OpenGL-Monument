CC = g++
INCLUDES = -I/usr/include/glm/ -I/usr/include/GL/ 
LIBS = -lGL -lglut -lGLEW -lfreeimage -lc
FLAG = -g -Wall ${LIBS} ${INCLUDES}
SRCS = beleg.cpp LoadShader.cpp
OBJS = $(subst .cpp,.o,$(SRCS))
all: beleg

beleg: $(OBJS)
	${CC} ${FLAG} -o beleg $(OBJS)

%.o: %.cpp
	${CC} ${FLAG} -c $<

clean:
	$(RM) $(OBJS)
