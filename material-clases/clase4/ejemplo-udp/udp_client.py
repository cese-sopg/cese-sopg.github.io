import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.sendto("Mensaje desde cliente", ("127.0.0.1",4096))

sock.close()

