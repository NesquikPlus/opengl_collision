# Opengl_Collision:

Collision of spheres with momentum and angular velocity calculations. 

No gravity, no energy loss due to friction.

Multiple spheres can be added, initial positions, velocities, angular velocities, masses and model files of the spheres can be altered from main.cpp.

# Build for Linux:

Install glfw, glm, assimp libraries with cmake.

Download include files for glad and stb_image.

Put glad.c and stb_image.h in project directory.

Your include directory(usr/local/include by default) should contain the following folders with header files inside them:

assimp  glad  GLFW  glm  KHR  stb_image

Your library directory(/usr/local/lib by default) should contain the following files:

├── cmake
│   ├── assimp-5.0
│   │   ├── assimp-config.cmake
│   │   ├── assimp-config-version.cmake
│   │   ├── assimpTargets.cmake
│   │   └── assimpTargets-release.cmake
│   ├── glfw3
│   │   ├── glfw3Config.cmake
│   │   ├── glfw3ConfigVersion.cmake
│   │   ├── glfw3Targets.cmake
│   │   └── glfw3Targets-noconfig.cmake
│   └── glm
│       ├── glmConfig.cmake
│       └── glmConfigVersion.cmake
├── libassimp.so -> libassimp.so.5
├── libassimp.so.5 -> libassimp.so.5.0.0
├── libassimp.so.5.0.0
├── libglfw3.a
├── libIrrXML.a
├── libzlibstatic.a
├── pkgconfig
│   ├── assimp.pc
│   └── glfw3.pc

Change the makefile if you plan to use a different include or library path.

make

./collision

Demo: 

https://youtu.be/OtlB5nZVjQg

