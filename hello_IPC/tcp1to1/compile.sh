mkdir -p build
gcc -g tcp_client.c -o tcp_client -lrt
gcc -g tcp_server.c -o tcp_server -lrt
rm -R build/*
mv tcp_client tcp_server build/
rm *.o


