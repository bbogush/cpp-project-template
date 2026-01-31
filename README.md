# cpp-project-template

C++ project template.

## Setup environment

Docker used to have the same environment for development.

```
./docker/docker_run.sh
```

## Build

CMake is most popular build system for C++ projects.

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

Run the produced executable (name matches project):

```bash
./hello
```