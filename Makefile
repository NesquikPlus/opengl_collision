CPPFLAGS = -D AMD64 -std=c++17

ifeq ($(OS),Windows_NT)
	INC_PATH = -I"C:/opengl/include" 
	LIBS_PATH = -L"C:/opengl/lib/glfw" -L"C:/opengl/lib/assimp"
	LIBS = -lglfw3 -l:libassimp.a -lIrrXML -lz -lpthread
else
	INC_PATH = -I"/usr/local/include" 
	LIBS_PATH = -L"/usr/local/lib"
	LIBS = -lglfw3 -lX11 -lassimp -lIrrXML -lpthread -ldl
endif


SRC_FILES = $(shell find . -name "*.cpp" -or -name "*.c")
OBJ_FILES = *.o

all:
	g++ -c $(CPPFLAGS) $(SRC_FILES) $(INC_PATH)
	g++ $(LIBS_PATH) $(OBJ_FILES) $(LIBS) -o collision

clean:
	rm $(OBJ_FILES)
