# Build and run

To build and run this code (in Windows), useee thee following commands:

- Starting the build (run once)

```
cmake -S . -B build -G "Visual Studio 18 2026"
```

Replacing the version with your current version of Visual Studio. 

- Actually build the project

```
cmake --build build
```

- Run ```main.cpp```

```
build\Debug\FirstRayTracer.exe > image.ppm
```