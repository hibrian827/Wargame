from Crypto.Util.Padding import pad, unpad
from Crypto.Cipher import AES
import os

BLOCK_SIZE = 16
flag = open("flag", "rb").read()
key = os.urandom(BLOCK_SIZE)

# perfecly protected!
iv = key
for _ in range(5):
    iv = AES.new(key, AES.MODE_CBC, b'\x00' * 16).encrypt(iv)

encrypt = lambda pt: AES.new(key, AES.MODE_CBC, iv).encrypt(pad(pt, BLOCK_SIZE))
decrypt = lambda ct: AES.new(key, AES.MODE_CBC, iv).decrypt(ct)