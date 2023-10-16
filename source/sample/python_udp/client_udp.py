##
# @file client_udp.py
# @version 1.0.0
# @author nino-kin
# @brief UDP client
# @details Sample code with UDP socket communication

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Specify the server and send the string "Hello Server!"
s.sendto(b'Hello Server!', ('127.0.0.1', 60002))
