# Based from https://www.youtube.com/watch?v=VZK224Tj_4w

#image_name:tag
#sudo docker build . -t cpp_env:1

FROM gcc:latest

# copy src destination
COPY main.cpp /usr/src

#work directory
WORKDIR /usr/src

#compile 
RUN g++ -o Test main.cpp

#Run the binary
CMD ["./Test"]


###########################
#list images
#sudo docker images

#run container
#sudo docker run --rm -it REPOSITORY:TAG
#rm will remove the container if it already exist
#it means interactive
#instead of repo:tag, you can use IMAGE_ID instead  
