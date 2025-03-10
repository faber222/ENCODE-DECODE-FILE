# ENCODE-DECODE-FILE

Este projeto implementa um método para converter dados binários de arquivos em vídeos utilizando a biblioteca OpenCV. O objetivo principal é explorar a viabilidade do YouTube como um "Google Drive" ilimitado, aproveitando que a plataforma permite o upload de vídeos sem restrição de quantidade.

## 🔥 Motivação

A ideia surgiu da possibilidade de armazenar arquivos em vídeos e, posteriormente, recuperá-los. Como o YouTube não permite upload de arquivos diretamente, converter qualquer binário em uma sequência de imagens representando esses dados parece uma solução interessante.

Porém, durante os testes, a compressão dos vídeos no YouTube tem causado perda de dados, o que compromete a recuperação precisa da informação. O projeto ainda está em desenvolvimento para superar esse obstáculo.

## 🚀 Tecnologias Utilizadas

* OpenCV: para manipulação de imagens e geração dos vídeos.
* libbmp: biblioteca em C para manipulação de imagens BMP.
* C++: linguagem principal utilizada no desenvolvimento.

## 📦 Estrutura do Projeto

O projeto possui duas formas de codificação das imagens:
1. Usando a biblioteca libbmp: gera imagens BMP manualmente.
2. Usando OpenCV (cv::Mat): manipula diretamente as imagens sem precisar da libbmp.

## 🛠️ Compilação

### 📌 Ubuntu

```bash
# Instale pacotes essenciais
sudo apt update
sudo apt install build-essential cmake unzip pkg-config
sudo apt install libjpeg-dev libpng-dev libtiff-dev ffmpeg
sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt install libxvidcore-dev libx264-dev
sudo apt install libgtk-3-dev
sudo apt install libatlas-base-dev gfortran

# Instale OpenCV
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

cd opencv && git checkout 4.11.0 && cd ..
cd opencv_contrib && git checkout 4.11.0 && cd ..

mkdir -p opencv/build && cd opencv/build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_PYTHON_EXAMPLES=OFF \
      -D INSTALL_C_EXAMPLES=ON \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
      -D BUILD_EXAMPLES=ON ..

make -j$(nproc)
sudo make install
```
A instalação que usei como base e agradeço de coração, está descrita nesse link, e destino todo o crédito do sucesso desta instalação a Carvalho Natalia:
[OPEN_CV](https://medium.com/@carvalho.natalia03/instalando-a-opencv-c-no-linux-98d7fc71e996)

### 📌 OpenSUSE
```bash
# Busque pela biblioteca OpenCV disponível
sudo zypper se opencv

# Instale os pacotes necessários
sudo zypper in opencv opencv-devel
```

## 🏃‍♂️ Execução

### Clonando o repositório
```bash
git clone https://github.com/faber222/ENCODE-DECODE-FILE.git
cd ENCODE-DECODE-FILE/src/
```

### Compilando o projeto
```bash
cmake -S . -B build
cmake --build build
```

### Executando o programa
```bash
./build/encoderDecoder
```

## 🔎 Debugando a Geração de Imagens

#### Se quiser visualizar as imagens sendo geradas para testar a lógica, edite o CMakeLists.txt:
```bash
add_executable(encoderDecoder mainInMemory.cpp mem.cpp)  # COMENTE ESSA LINHA
# add_executable(encoderDecoder main.cpp function.cpp libs/libbmp.cpp)  # DESCOMENTE ESTA LINHA
```

### Agora, recompile e execute:
```bash
cmake -S . -B build
cmake --build build
./build/encoderDecoder
```