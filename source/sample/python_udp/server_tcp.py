##
# @file server_tcp.py
# @version 1.0.0
# @author nino-kin
# @brief TCP server
# @details Sample code with TCP socket communication

import socket

# Create a socket object
# AF_INET: Address family, specifying IPv4
# SOCK_STREAM: Specify the TCP protocol
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the IP address and port number to the created socket object
# 127.0.0.1: Specify the local host
# 60001: Specify port number 60001 (listening port)
s.bind(('127.0.0.1', 60001))

# Put the socket in listening mode
# 1: Specify the number of requests that can be processed in parallel as 1
s.listen(1)

count = 0
while count < 5:
    # Accept a connection from the client
    # conn: Newly created socket object
    # addr: Received IP address
    conn, addr = s.accept()

    # Print a string to the server's standard output
    # addr: (Client's IP address, Client's port number)
    print(f'Source IP Address: {addr}')

    # Send data to the client's socket
    conn.send(b'Hello World!')

    # Close the client's socket object
    conn.close()
    count += 1

# Close the server's socket
s.close()
