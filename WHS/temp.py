from pwn import *

port = 11288
rem = remote("srv1.kitriwhs.kr", port)
# rem = process("./2D Array/problem/deploy/chall")

ans = [
  [b"\x19",b"\xdf",b"\xf7",b"\xfd",b"\xc0",b"\xae",b"\x9b",b"\xc8"],
  [b"\xe4",b"\x5d",b"\x06",b"\xf5",b"\x1d",b"\x71",b"\x0e",b"\xee"],
  [b"\xc0",b"\x1c",b"\x3e",b"\x14",b"\x33",b"\x32",b"\x40",b"\x69"],
  [b"\x35",b"\x68",b"\x02",b"\xe2",b"\xb7",b"\x20",b"\x1f",b"\x3d"],
  [b"\xf5",b"\x19",b"\x57",b"\xd2",b"\x97",b"\xdd",b"\x30",b"\x90"],
  [b"\x43",b"\xbc",b"\x7b",b"\xa8",b"\x15",b"\x89",b"\xbd",b"\x53"],
  [b"\x40",b"\xcf",b"\x64",b"\x3d",b"\x8d",b"\x03",b"\xae",b"\x2e"],
  [b"\x08",b"\x5a",b"\xae",b"\x9a",b"\x11",b"\x9f",b"\xb7",b"\x65"],
]

# 1
for i in range(8):
  for j in range(i, 8):
    temp = ans[i][j]
    ans[i][j] = ans[j][i]
    ans[j][i] = temp
print(ans)
print()

# 2
nums = [b'\xbf',b'\xd6',b'\x62',b'\x87',b'\x08',b'\x62',b'\xf2',b'\x66']
for i in range(8):
  for j in range(8):
    res = hex((int.from_bytes(ans[i][j], 'big') - int.from_bytes(nums[(i + j) % 8], 'big')) % 0x100)
    res = res[2: ].zfill(2)
    ans[i][j] = bytes.fromhex(res)
print(ans)
print()

# 3
for i in range(8):
  for j in range(4):
    temp = ans[i][j]
    ans[i][j] = ans[i][7- j]
    ans[i][7- j] = temp
print(ans)
print()

# 4
nums = [b'\x15',b'\x55',b'\xc4',b'\x3b',b'\xb5',b'\xfc',b'\x35',b'\xd7']
for i in range(8):
  for j in range(8):
    res = hex(int.from_bytes(ans[i][j], 'big') ^ int.from_bytes(nums[(i + j) % 8], 'big'))
    res = res[res.index('0x') + 2: ].zfill(2)
    ans[i][j] = bytes.fromhex(res)
print(ans)
print()
  
# 5
for i in range(4):
  for j in range(8):
    temp = ans[i][j]
    ans[i][j] = ans[7 - i][j]
    ans[7 - i][j] = temp
print(ans)
print()

for i in range(8):
  for j in range(8):
    ans[i][j] = chr(int.from_bytes(ans[i][j], 'big')).encode('latin-1')
print(ans)

for i in range(8):
  for j in range(8):
    print(rem.recvuntil(b'? '))
    print(ans[i][j])
    rem.sendline(ans[i][j])
    
print(rem.recvall())
