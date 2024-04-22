# libbmp
A simple Bitmap (BMP) library written in C without dependencies.  
For a native C++ version look: [libbmp](https://github.com/marc-q/libbmp.git)

## Run
```shell
## Build core modules
$ sudo apt update
$ sudo apt install build-essential cmake unzip pkg-config
$ sudo apt install libjpeg-dev libpng-dev libtiff-dev ffmpeg
$ sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
$ sudo apt install libxvidcore-dev libx264-dev
$ sudo apt install libgtk-3-dev
$ sudo apt install libatlas-base-dev gfortran
## install opencv
$ git clone https://github.com/opencv/opencv.git
$ git clone https://github.com/opencv/opencv_contrib.git
$ cd opencv && git checkout 4.9.0 && cd ..
$ cd opencv_contrib && git checkout 4.9.0 && cd ..
#Repare que 4.9.0 é a versão da opencv que será utilizada. Você pode #escrever a versão que melhor te atender, mas lembre-se de que #opencv e opencv contrib devem estar na mesma versão :)
$ cd ~/opencv
$ mkdir build
$ cd buildcmake -D CMAKE_BUILD_TYPE=RELEASE \
 -D CMAKE_INSTALL_PREFIX=/usr/local \
 -D INSTALL_PYTHON_EXAMPLES=OFF \
 -D INSTALL_C_EXAMPLES=ON \
 -D OPENCV_ENABLE_NONFREE=ON \
 -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
 -D BUILD_EXAMPLES=ON ..
$ nproc
## o valor que retornar, coloque abaixo depois do -j, o meu deu 8
$ make -j8
$ sudo make install

## the program
$ git clone https://github.com/faber222/IMAGE-COPY.git
$ cd src/
$ cd cpp/
$ make
$ make run
```
