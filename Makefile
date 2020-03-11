#clang++ -Iinclude/GLFW main.cpp -Llibs  -lglfw.3.2 -o m
#excutable files has an installation path for dynamic libs by default
#if we need to link against a dinamic library into our project we need
#to:
# 1. check with otool the name of the dylib:
#  otool -D libs/libGlEW.2.1.0.dylib
#
# 2. change the install name of the dll or dylib :
#
# sudo install_name_tool -id libs/libGLEW.2.1.0.dylib libs/libGLEW.2.1.0.dylib
#
# 3. check with otool the excetubale path to load dylibs
#   
#    otool -L <binary excecutable>
#
# 3. change the excecutable path to load the dylibs
#
#  sudo install_name_tool -change <old name and path> <new name and path>  <excecutable file>
#

CC=g++
INCLUDE=-Iinclude/ 
TARGET_LIBS=-Wl,-rpath,'$$ORIGIN/../libs' -L./libs/ -lGL -lGLEW -lglfw
FLAGS=-std=c++11 -Wall -Wpedantic -W
MAIN=src/main.cpp
EXECUTABLE=bin/app


main.o:$(MAIN)
	$(CC) $(FLAGS) $(INCLUDE) $(MAIN) -o $(EXECUTABLE) $(TARGET_LIBS)

.PHONY: run clean

run:
	./$(EXECUTABLE)
	
clean:	
	rm $(OBJECT_FILE) $(EXECUTABLE)
