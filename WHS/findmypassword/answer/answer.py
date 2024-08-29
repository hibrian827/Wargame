# -------------------------------------- 1st phase --------------------------------------

old_f = open('./findmypassword/problem/deploy/packed.bin', 'rb')
new_f = open('./findmypassword/answer/target.exe', 'wb')

old_txt = old_f.readline()
new_txt = b''
size = len(old_txt)

for b in old_txt:
  print(b)
  new_txt += bytes.fromhex(str(hex(b ^ 0xEF))[2:].zfill(2))

new_f.write(new_txt)

old_f.close()
new_f.close()

# -------------------------------------- 2nd phase --------------------------------------
import itertools


v3 = 0
v4 = 0
v6 = [204] * 13 + [0]
a1 = []

i = 0
while True:
  v5 = -1
  while a1[v5] != 0:
    v5 += 1
  if i >= v5:
    break
  
  if a1[i] != 45 or a1[i] != 115 or a1[i] != 77:
    if a1[i] == 74:
      a1[i] ^= 2
      # v6[i] ^= 2
      v3 += 1
    if  a1[i] == 102:
      a1[i] ^= 3
      # v6[i] &= 2
      a1[i] |= 5
      a1[i] ^= 0xA
      a1[i] ^= 0xA
      # v6[i] |= 2
      v3 += 1
    if  a1[i] == 105:
      # v6[i] ^= 4
      a1[i] ^= 5
      # v6[i] += 5
      v3 += 1
    if  a1[i] == 122:
      # v6[i] += 2
      a1[i] -= 10
      a1[i] ^= 0x1F
      v3 += 1
    if  a1[i] == 69:
      # v6[i] -= 3
      a1[i] += 12
      a1[i] ^= 0x18
      v3 += 1
    if  a1[i] == 120:
      # v6[i] -= 3
      a1[i] += 11
      a1[i] ^= 0xF7
      v3 += 1
    if  a1[i] == 81:
      # v6[i] -= 4
      a1[i] += 12
      a1[i] ^= 0x14
      v3 += 1
    v4 = v3
  i += 1

if v4 == 9:
  flag = "flag{"
  for i in range(14):
    flag += chr(a1[i])
  flag += "}"