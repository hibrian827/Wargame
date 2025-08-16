#!/bin/python3
from string import ascii_lowercase, ascii_uppercase, digits
from random import choices
import os
import sys
import hashlib

def write(x):
    sys.stdout.write(x)
    sys.stdout.flush()

def readline():
    return sys.stdin.readline().rstrip("\n")

def PoW() -> bool:
    x: bytes = os.urandom(16)
    target: str = hashlib.md5(x).hexdigest()
    write(f"MD5(X = {x[:13].hex()}+{'?'*6}) = {target}\n")
    try:
        write("X : ")
        if bytes.fromhex(readline()) == x:
            return True
        else:
            write("[-] PoW failed!\n")
            return False
    except:
        write("[-] PoW failed!\n")
        return False

def randstr(k):
    return ''.join(choices(ascii_lowercase+ascii_uppercase+digits, k=k))

def run_vm():
    os.execvp("./exec-qemu.sh", ["./exec-qemu.sh"])

if __name__ == "__main__":
    if not PoW():
        exit(1)
    run_vm()
