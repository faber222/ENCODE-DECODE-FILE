# libbmp
A simple Bitmap (BMP) library written in C without dependencies.  
For a native C++ version look: [libbmp](https://github.com/marc-q/libbmp.git)

## Compile

### Ubuntu
```bash
## Build core modules for ubuntu
sudo apt update
sudo apt install build-essential cmake unzip pkg-config
sudo apt install libjpeg-dev libpng-dev libtiff-dev ffmpeg
sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt install libxvidcore-dev libx264-dev
sudo apt install libgtk-3-dev
sudo apt install libatlas-base-dev gfortran

## install opencv
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

cd opencv && git checkout 4.11.0 && cd ..
cd opencv_contrib && git checkout 4.11.0 && cd ..
# Repare que 4.11.0 é a versão da opencv que será utilizada. 
# Você pode escrever a versão que melhor te atender, mas lembre-se de que 
# opencv e opencv contrib devem estar na mesma versão :)
cd ~/opencv
mkdir build
cd build
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

### OpenSUSE
```bash
# Primeiro busque pela lib opencv
sudo zypper se opencv

S  | Name                             | Summary                                              | Type
---+----------------------------------+------------------------------------------------------+-------
i  | libopencv_videostab411           | Video stabilization libraries for OpenCV             | pacote
i  | libopencv_ximgproc411            | Image processing libraries for OpenCV                | pacote
i+ | opencv                           | Collection of algorithms for computer vision         | pacote
i+ | opencv-devel                     | Development files for using the OpenCV library       | pacote
i  | opencv4-cascades-data            | Classifier cascades for OpenCV                       | pacote

# Instale o opencv e o opencv-devel
sudo zypper in opencv
sudo zypper in opencv-devel
```

## RUN
```bash
## the program
git clone https://github.com/faber222/ENCODE-DECODE-FILE.git
cd src/
cd cpp/
# No diretório raiz, execute o seguinte comando
# 1 Gerar os arquivos do CMake:
cmake -S . -B build

# É importante que tenha o opencv-devel
# 2 Compilar:
cmake --build build

# O executável estará em build/encoderDecoder
# 3 Executar:
./build/encoderDecoder 
```