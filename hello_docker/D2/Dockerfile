# Based from https://medium.com/@mfcollins3/shipping-c-programs-in-docker-1d79568f6f52


FROM ubuntu:latest

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
	apt-get install -y build-essential git cmake autoconf libtool pkg-config
#for GUI testing
RUN apt install -y x11-apps

#work directory
WORKDIR /usr/src

# copy src destination
COPY CMakeLists.txt main.cpp /usr/src
#COPY main.cpp /usr/src
#COPY CMakelists.txt  /usr/src


#compile 
RUN cmake . && make

#Run the binary
CMD ["./helloworld"]


###########################
#Build container
#sudo docker build . -t cpp_env:1
#image_name:tag

#list images
#sudo docker images

#run container
#sudo docker run --rm -it REPOSITORY:TAG
#rm will remove the container if it already exist
#it means interactive
#instead of repo:tag, you can use IMAGE_ID instead  

#docker run --rm -it -v ~/dev:/home/dev <image ID> bash
#-v will mount the ~/dev to docker internal /home/dev 

#how to display GUI
#1. socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"
#2. run XQuartz
#3. docker run --rm -e DISPLAY=<MAC IP addr>:0 \
#    -it -v ~/dev:/home/dev <container ID> bash
#example: 
#docker run --rm -e DISPLAY=192.168.0.105:0 -it -v ~/dev:/home/dev <container ID> bash
#docker exec  -e DISPLAY=192.168.0.105:0 -it  <container ID> bash