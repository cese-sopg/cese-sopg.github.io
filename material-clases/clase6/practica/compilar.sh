gcc -Wall -pedantic -std=gnu99 server_tcp.c clientdata.c -pthread -o server
gcc -Wall -pedantic -std=gnu99 cliente_tcp.c -o client
