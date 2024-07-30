#!/usr/bin/env python3
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

print("Welcome to YYY's AES server")
while True:
    print("[1] Encrypt")
    print("[2] Decrypt")
    print("[3] Get Flag")

    choice = input()

    if choice == "1":
        print("Input plaintext (hex): ", end="")
        pt = bytes.fromhex(input())
        print(encrypt(pt).hex())

    elif choice == "2":
        print("Input ciphertext (hex): ", end="")
        ct = bytes.fromhex(input())
        print(decrypt(ct).hex())

    elif choice == "3":
        print(f"flag = {encrypt(flag).hex()}")
        exit()

    else:
        print("Nope")
