#!/usr/bin/env python3
from pwn import *
context.terminal = ['tmux', 'splitw', '-h']
context.buffer_size = 0x1000000
"""
    Basic Setup.
    We strongly recommend you to use the this setup without modification.
"""
# You may not need any other sender helper functions.
def send_packet(data):
    p.send(p64(len(data)) + data.encode())

# dummy example
def post_example():
    send_packet("\r\n".join([
        "POST / HTTP/1.1",
        "",
        "user=test&password=1234"
    ]))

if "REMOTE" in os.environ:
    # REMOTE=1 python3 ex.py
    # FLAG=1 REMOTE=1 python3 ex.py
    print("[*] Target: Remote")

    p = remote("kayle.snu.ac.kr", 10039)

else: # local testing
    # python3 ex.py
    # FLAG=1 python3 ex.py
    print("[*] Target: Local")

    # due to the limit of PTY/PIPE recv buffer size, redirect stdout to output.txt
    if "FLAG" in os.environ:
        f = open("output.txt", "wb")
        p = process("./public/prob", stdout=f, stderr=f)
    else:
        p = process("./public/prob")

#################################################

"""
    TODO: write exploit here.
"""

post_example()

#################################################

if "FLAG" in os.environ:
    """
        Flag Extractor.
    """
    print("[*] Flag Extraction")
    if "REMOTE" in os.environ:
        flag_count = 0
        while True:
            data = p.recv(4096, timeout=0.5)
            if not data:
                break
            if b"flag{" in data:
                flag_count += 1
                offset = data.find(b"flag{")
                print(data[offset:offset+0x100])

        print(f"[!] {flag_count} flags found.")
    else:
        p.close()
        f.close()
        with open("output.txt", "rb") as f:
            data = f.read()
            print(f"[!] {data.count(b"flag{")} flags found.")
            if b"flag{" in data:
                offset = data.find(b"flag{")
                print(data[offset:offset+0x100])
    

else:
    print("[*] Interactive")
    p.interactive()
