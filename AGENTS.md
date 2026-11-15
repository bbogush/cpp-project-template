# Agent guidance

This file is for AI coding agents working in this repository.

## Project overview

A minimal C++ project template: ISO C++26, CMake 3.25+, and an Ubuntu 26.04 Docker toolchain (GCC,
clang-tidy, cppcheck, CMake, Git, Node.js for prettier, shfmt). The sample program is
`cpp-project-template`.

## Repository structure

```text
.
|-- CMakeLists.txt            # Root project, warnings, and custom targets
|-- CMakePresets.json         # Configure, build, and test presets
|-- build/                    # Generated preset output (gitignored)
|-- src/                      # Application sources and component libraries
|   |-- main.cpp              # Program entry point
|   `-- <component>/          # One library per component (.h, .cpp, CMakeLists.txt)
|-- tests/                    # Google Test binaries, mirroring src/ components
|-- benchmarks/               # Google Benchmark binaries, same layout as tests/
|-- cmake/                    # format, coverage, clang-tidy, and cppcheck scripts
|-- docker/                   # Dockerfile and helper scripts
|-- .devcontainer/            # VS Code Dev Container config
|-- doc/design/               # Design docs; start from design_template.md
`-- .github/workflows/        # CI: build, tests, coverage, analysis, format, benchmarks
```

Style and process docs: `CODE_STYLE.md`, `CONTRIBUTING.md`, `README.md`.

## Development environment

Use the Docker image. From the repository root:

```bash
./docker/docker_run.sh
```

The tree is mounted at `/project`. `./docker/docker_build.sh` rebuilds the image.
`./docker/docker_clean.sh` stops containers and removes the image. VS Code can open the same image
with **Dev Containers: Reopen in Container** (`.devcontainer/devcontainer.json`).

Build outside Docker only when CMake 3.25+ and the same formatters and analyzers are already
installed. Do not invent a different toolchain.

## Build instructions

Use the presets in `CMakePresets.json`. Do not invent binary directories or extra compiler flags.
Every library, test, and benchmark links `project_options` (warnings as errors) and
`project_features` (`cxx_std_26`, extensions off).

```bash
cmake --preset release
cmake --build --preset release
./build/release/cpp-project-template
```

`build/<preset_name>` contains build result. Delete the directory to clean.

## Testing and validation

After a behavior change:

```bash
cmake --preset tests
cmake --build --preset tests
ctest --preset tests
cmake -P cmake/format.cmake
```

Before finishing a change that touches `src/`, also run:

- `tests-asan`, `tests-tsan`, and `tests-valgrind-memcheck`
- `clang-tidy` and `cppcheck` (both analyze `src/` only; findings fail the build)
- `tests-coverage`, then `cmake --build --preset coverage-report`. Coverage of `src/` stays at or
  above 90%.

`cmake -P cmake/format.cmake` checks formatting and does not rewrite files. It runs clang-format,
cmake-format, prettier, and shfmt. Fix violations in place. The line limit is 100. Markdown, JSON,
and YAML wrap with prettier (`proseWrap: always` in `.prettierrc.json`).

Tests use Google Test. Add `tests/<component>/<name>_test.cpp` and a `CMakeLists.txt` beside it,
then `add_subdirectory` from `tests/CMakeLists.txt`. Include project headers from
`${PROJECT_SOURCE_DIR}/src` and register the binary with `gtest_discover_tests`.

Benchmarks use Google Benchmark under `benchmarks/`. Append the executable to
`PROJECT_BENCHMARK_EXECUTABLES` so the `benchmarks-report` preset runs it.

## C++ coding conventions

Follow [CODE_STYLE.md](CODE_STYLE.md) and `.clang-format`. The project compiles as ISO C++26;

- Files are `snake_case.h` and `snake_case.cpp`. Types are `PascalCase`. Functions, variables,
  namespaces, and enumerators are `snake_case`.
- Headers use `#ifndef` / `#define` / `#endif` guards named from the path, as in
  `PROJECT_MY_COMPONENT_H`. A `.cpp` includes its own header first, then project headers,
  third-party headers, the C++ standard library, and C headers, each group separated by a blank
  line.
- New source files include the Apache 2.0 license header used in `src/main.cpp`.
- Do not use C++ exceptions. Report expected failures with `std::error_code` (success is `{}`),
  `std::optional`, or an `init()` / factory. Place inputs before outputs. Use output references for
  required results and pointers for optional ones.
- Prefer `std::unique_ptr` for ownership. Mark single-argument constructors `explicit`. Use `const`
  on member functions that do not change logical state. Do not put `using namespace` in headers.
- Indent with 4 spaces. Opening braces of functions go on the next line; braces of `if`, `for`,
  `while`, and `switch` stay on the same line. Always brace those bodies.

## Architecture guidelines

- One component is one directory, one CMake library, and one namespace: `project::<component>`.
- Keep the public API in the header. Keep implementation details in the `.cpp`.
- `src/main.cpp` is the entry point. It links component libraries; it does not absorb their logic.
- Tests and benchmarks mirror the component directories and link the library under test. They are
  not part of the installed program.
- Do not add a CMake option, preset, or workflow unless the task needs a new build mode.
- Non-trivial designs go in `doc/design/`, copied from `doc/design/design_template.md`. Design docs
  are ASCII only.

## Dependencies

Google Test and Google Benchmark are declared with `FetchContent` and pinned hashes in
`tests/CMakeLists.txt` and `benchmarks/CMakeLists.txt`. Do not vendor them, and do not change those
URLs or hashes unless asked.

Do not add another third-party library, package manager, or system dependency unless the task
requires it. Prefer the libraries already fetched by CMake.

## Git and commit conventions

Follow [CONTRIBUTING.md](CONTRIBUTING.md) when asked to commit or open a pull request.

- One logical change per commit.
- Subject: `<area>: <summary>`. The area is a lowercase component or tool (`my_component`, `build`,
  `ci`, `docker`). The summary is imperative, lowercase, and has no trailing period. Keep the
  subject within 72 characters.
- Leave one blank line, then a body wrapped at 72 characters that explains why. Reference issues as
  `Refs #123`.
- Branch names are `<area>/<short_description>`. Pull request titles use the commit subject format.
  Rebase onto `main`; do not merge `main` into the branch.

## Rules for AI agents

- Change only what the task needs. Match the surrounding files.
- Do not commit, push, or open pull requests unless asked.
- Do not add dependencies, CMake options, presets, workflows, or docs unless the task requires them.
- Use the CMake presets and the Docker toolchain. Do not hand-write compiler or linker flags.
- Run the tests and the format check for the code you change. Run the sanitizer, Valgrind,
  clang-tidy, cppcheck, and coverage steps when the change touches `src/`.
