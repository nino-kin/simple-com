##
# @file client_tcp.py
# @version 1.0.0
# @author nino-kin
# @brief TCP client
# @details Sample code with TCP socket communication

import socket

PORT = 60001

# Create a socket object for the host
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Send a request to the server
# 127.0.0.1: Specify the server's IP address
# 60001: Specify the port on which the server is listening
host = socket.gethostname()
s.connect((socket.gethostbyname(host), PORT))

# Receive data from the server
data = s.recv(4096)

# Display the received data on the client's standard output
print(data)

# Close the client's socket
s.close()
