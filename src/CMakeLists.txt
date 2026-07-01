set(PROJECT_SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)