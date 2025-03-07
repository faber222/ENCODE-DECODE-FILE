## Como executar

```cpp
// No diretório raiz, execute o seguinte comando
// 1 Gerar os arquivos do CMake:
cmake -S . -B build

// É importante que tenha o opencv-devel

// 2 Compilar:
cmake --build build

// O executável estará em build/encoderDecoder
// 3 Executar:
./build/encoderDecoder 

```