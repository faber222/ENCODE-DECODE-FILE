cmake_minimum_required(VERSION 3.15)
project(encoderDecoder)

# Definir padrão de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Encontrar OpenCV
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV não encontrado!")
endif()

# Incluir diretórios
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(libs)

# Adicionar arquivos fonte
add_executable(encoderDecoder mainInMemory.cpp mem.cpp)
# add_executable(encoderDecoder main.cpp function.cpp libs/libbmp.cpp)

# Vincular OpenCV
target_link_libraries(encoderDecoder ${OpenCV_LIBS})