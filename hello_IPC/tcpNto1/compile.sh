mkdir -p build
gcc -g tcp_client.c -o tcp_client -lrt
gcc -g mx_tcp_server.c -o mx_tcp_server -lrt
rm -R build/*
mv tcp_client mx_tcp_server build/
rm *.o


