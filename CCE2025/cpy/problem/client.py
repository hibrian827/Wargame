import base64
import sys
from pwn import remote, context

#context.log_level = 'debug'

if len(sys.argv) <= 1:
    print("Usage: python3 client.py <filepath>")
    exit()

try:
    elf = base64.b64encode(open(sys.argv[1], "rb").read())
except:
    print("[-] Error!")
    exit()


REMOTE_IP = "127.0.0.1"
REMOTE_PORT = 31337

r = remote(REMOTE_IP, REMOTE_PORT)
r.sendlineafter(b"> ", elf)

r.interactive()


