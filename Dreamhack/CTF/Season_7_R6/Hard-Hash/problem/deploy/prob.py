#!/usr/bin/env python3
from cipher import DHHash
import os


def give_flag():
    with open("flag", "rb") as f:
        flag = f.read()
    print(flag)
    

def xor_byte(m1, m2):
    return bytes((b1 ^ b2 for b1, b2 in zip(m1, m2)))


def main():
    print("IDEK how to protect my password. So I just decided to give up.")
    print("Now no one can take the flag, not even me!")
    _pw = os.urandom(16)
    print(f"Take my useless password : {_pw.hex()}")

    user_pw = bytes.fromhex(input("enter password (hex) > "))
    if user_pw == _pw:
        exit("Not this time~")

    if DHHash(user_pw).digest() == DHHash(_pw).digest():
        give_flag()
    else:
        print("Wrong password ¯\_(ツ)_/¯")


if __name__ == "__main__":
    main()
