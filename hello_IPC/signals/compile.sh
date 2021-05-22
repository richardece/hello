mkdir -p build
gcc -g ctrl_c.c -o ctrl_c 
gcc -g kill_recv.c -o kill_recv 
gcc -g kill_sender.c -o kill_sender 
gcc -g raise.c -o raise 
mv ctrl_c kill_recv kill_sender raise build/
rm *.o


