##
# @file server_udp.py
# @version 1.0.0
# @author nino-kin
# @brief UDP server
# @details Sample code with UDP socket communication

import socket

# Specify UDP protocol using SOCK_DGRAM
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('127.0.0.1', 60002))

count = 0
while count < 5:
    # Receive data from the client
    data, addr = s.recvfrom(4096)
    # Display received data, client's IP address, and port number
    print(data, addr)
    count += 1

s.close()
