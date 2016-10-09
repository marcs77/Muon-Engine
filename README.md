# Muon Engine (WIP)
A C++ OpenGL engine, currently works in Windows and Linux.
### Dependencies
Dependencies included inside:
 - FreeImage (only for Windows)
 - FreeType
 - freetype-gl
 - glfw
 - glad

For linux builds, it needs the following packages:
```
libfreeimage3 libfreeimage-dev
```
To install them:
```sh
$ sudo apt-get install libfreeimage3 libfreeimage-dev
```
### Build Instructions (TODO)
 - Windows: Run CMakeBuild.bat, it will generate the Visual Studio files.
 - Linux: Run LinuxCMake.sh, it will generate the necessary Makefiles. 

### Notes
The CMakeLists.txt generates automatically a working directory (workingDir) inside the build folder, which contains the copied resources and dlls.
