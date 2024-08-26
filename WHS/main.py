def check(n):
  return n % 0x2 == 0 and (n + 0xff) % 0x3 == 0 and (n + 0xfd) % 0x5 == 0 and (n + 0xfc) % 0x49 == 0 and (n + 0x2) % 0xB == 0 and (n + 0x8) % 0x25 == 0

keys = []
for i in range(0x989681):
  if check(i):
    keys.append(i)

print(keys)

for key in keys:  
  result = [0] * 32

  # encoded = [
  #   0x7B, 0x48, 0x0F, 0x5F, 0x5F, 0x5D, 0x13, 0x4B, 0x6E, 0x51, 
  #   0x68, 0x74, 0x74, 0x51, 0x68, 0x7E, 0x6D, 0x3A, 0x33, 0x7F, 
  #   0x5F, 0x7A, 0x23, 0x2F
  #   ]
  
  encoded = [
    75,   19,   93,   95,   95,   15,   72,   123,  126,  104, 
    81,   116,  116,  104,  81,   110,  47,   35,   122,  95, 
    127,  51,   58,   109,  100,  0,    0,    0,    0
  ]
  
  for i in range(29):
    result[i] = ((key >> (8 * (i & 3))) ^ encoded[i]) % 0x100
  result[29] = 0

  print(list(map(chr, result)))
  # print(bytes.fromhex(hex(int(''.join(map(str, result)), 16))[2:]))