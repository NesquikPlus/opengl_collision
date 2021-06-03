# Opengl_Collision:

Collision of spheres with momentum and angular velocity calculations. 

No gravity, no energy loss due to friction.

Multiple spheres can be added, initial positions, velocities, angular velocities, masses and model files of the spheres can be altered from main.cpp.

Demo: 

https://youtu.be/OtlB5nZVjQg

# Build for Linux:

Build and install glfw, glm, assimp libraries with cmake.

Download include files for glad and stb_image and copy to your include directory.

Place glad.c in the project directory.

Your include directory (usr/local/include by default) should contain the following folders with header files inside them:

  - assimp  
  - glad  
  - GLFW  
  - glm  
  - KHR  
  - stb_image

Your library directory (/usr/local/lib by default) should contain the following files:

- libassimp.so
- libassimp.so.5
- libassimp.so.5.0.0
- libglfw3.a
- libIrrXML.a
- libzlibstatic.a

Change the makefile if you plan to use a different include or library path.

make

./collision

# Build with MinGW for Windows:

Build and install glfw, glm, assimp libraries with cmake. 

(For assimp: Generate makefiles for MSYS2 as generating for MinGW was problematic in my case. You can use the resulting libraries with MinGW as well.)

Download include files for glad and stb_image and copy to your include directory.

Place glad.c in the project directory.

Your include directory (C:/opengl/include by default) should contain the following folders with header files inside them:

  - assimp  
  - glad  
  - GLFW  
  - glm  
  - KHR
  - stb_image

Your library directory (C:/opengl/lib by default) should contain the following files:

- glfw
    - glfw3.dll
- assimp
    - libassimp.a
    - libassimp.dll.a
    - libIrrXML.a

Your project directory should contain the following dynamic libraries:
  - assimp-vc142-mtd.dll
  - glfw3.dll

Change the makefile if you plan to use a different include or library path.

make

./collision


