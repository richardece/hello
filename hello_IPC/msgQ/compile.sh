mkdir -p build

gcc -g recvr.c -o recvr -lrt
gcc -g sender.c -o sender -lrt
mv recvr build/
mv sender build/



