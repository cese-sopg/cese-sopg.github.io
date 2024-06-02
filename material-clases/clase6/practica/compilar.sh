gcc -g -Wall -pedantic -std=gnu99 -c clientdata.c -o clientdata.o
gcc -g -Wall -pedantic -std=gnu99 server_tcp.c -pthread clientdata.o -o server
gcc -g -Wall -pedantic -std=gnu99 cliente_tcp.c -o client
