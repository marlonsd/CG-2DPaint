UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    FLAGS += -lglut -lGLEW -lGL # maybe: -lglut -lGLU -lGL -L/usr/X11R6/lib/ -lXmu -lXi -lXext -lX11 -lXt
endif
ifeq ($(UNAME_S),Darwin)
    FLAGS += -framework OpenGL -framework GLUT
endif

as1: as1.cpp
	gcc as1.cpp $(FLAGS) -o as1