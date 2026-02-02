# cpp-project-template

C++ project template.

## Setup environment

Docker used to have the same environment for development.

```
./docker/docker_run.sh
```

## VSCode DevContainers

VSCode DevContainers used to automatically start docker with development environment. It requires DevContainers extension. In order to start container need to execute Ctrl+Shft+P >DevContainers: Rebuild container.

## Build

CMake is used as build system for the project.

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