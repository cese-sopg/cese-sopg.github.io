import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("localhost",4096))

data, address = sock.recvfrom(1024)
print(data)

sock.close()
