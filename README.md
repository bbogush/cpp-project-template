# cpp-project-template

C++ project template.

## Setup environment

Docker is used to provide the same environment for development.

```
./docker/docker_run.sh
```

## VSCode DevContainers

VSCode DevContainers can automatically start docker with development environment. It requires DevContainers extension. In order to start the container, you need to execute Ctrl+Shift+P > DevContainers: Rebuild container.

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
./cpp-project-template
```