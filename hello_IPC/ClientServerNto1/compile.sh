mkdir -p build

gcc -g client.c -o client 
gcc -g server.c -o server
rm -R build/*
mv client server build/
rm *.o


