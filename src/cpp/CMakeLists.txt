cmake_minimum_required(VERSION 3.15)
project(encoderDecoder)

# Encontre a biblioteca OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
# Adicione todos os arquivos fonte ao executável
add_executable(encoderDecoder ./libs/libbmp.cpp main.cpp function.cpp function.h)

# Vincule a biblioteca OpenCV ao executável
target_link_libraries(encoderDecoder ${OpenCV_LIBS})
