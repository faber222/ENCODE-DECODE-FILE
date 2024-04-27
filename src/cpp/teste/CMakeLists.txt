cmake_minimum_required(VERSION 3.15)
project(teste)

# Encontre a biblioteca OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
# Adicione todos os arquivos fonte ao executável
add_executable(teste main.cpp)

# Vincule a biblioteca OpenCV ao executável
target_link_libraries(teste ${OpenCV_LIBS})
