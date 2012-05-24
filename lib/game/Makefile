CXX = g++
CXXFLAGS = -O3 -funroll-loops -fomit-frame-pointer
CPPFLAGS = -Wall -s
LIBS  = -lGL -lGLU -lglut
#LIBS = -lmingw32 -lglut32 -lopengl32 -lglu32

OBJS  = gl_viewer.o gl_camera.o main.o application.o timer.o lib/door.o lib/robot.o lib/input.o lib/mesh.o lib/weapon.o
SRCS = gl_viewer.cpp gl_camera.cpp main.cpp application.cpp timer.cpp lib/door.cpp lib/robot.cpp lib/input.cpp lib/mesh.cpp lib/weapon.cpp

TARGET = fight

a1l:	$(OBJS)
	$(CXX) $(CXXLFAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f *.o lib/*.o

main.o: application.h
gl_viewer.o: gl_viewer.h gl_camera.h

application.o: application.h gl_viewer.h timer.h lib/robot.h

timer.o: timer.h
lib/door.o: lib/door.h
lib/input.o: lib/input.h
lib/mesh.o: lib/mesh.h
lib/robot.o: lib/robot.h lib/door.h lib/weapon.h
lib/weapon.o: lib/weapon.h lib/mesh.h
