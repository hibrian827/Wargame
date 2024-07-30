#!/usr/bin/env python3
from Crypto.Util.Padding import pad, unpad
from Crypto.Cipher import AES
import os

BLOCK_SIZE = 16
key = os.urandom(BLOCK_SIZE)

# perfecly protected!
iv = key
for _ in range(5):
  iv = AES.new(key, AES.MODE_CBC, b'\x00' * 16).encrypt(iv)

encrypt = lambda pt: AES.new(key, AES.MODE_CBC, iv).encrypt(pad(pt, BLOCK_SIZE))
decrypt = lambda ct: AES.new(key, AES.MODE_CBC, iv).decrypt(ct)

print(key)
print(iv)

p = bytes(16)
print(encrypt(p))
temp = p
for i in range(5):
  temp = decrypt(temp)
  print(i, temp)
i = decrypt(decrypt(decrypt(decrypt(decrypt(decrypt(p))))) + decrypt(decrypt(decrypt(decrypt(p)))) + decrypt(decrypt(decrypt(p))) + decrypt(decrypt(p)) + decrypt(p) + p + encrypt(p))
# print(i)
i_i = i[48:64]
print(i_i)
print(decrypt(p + decrypt(p + decrypt(p + decrypt(p + decrypt(p + i_i)[16:32])[16:32])[16:32])[16:32])[16:32])
