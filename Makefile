all:
	g++ -g -std=c++11 *.cpp -o main -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lGLEW -lSOIL -lassimp