from pwn import *
from Crypto.Util.Padding import unpad
from Crypto.Cipher import AES


# 서버 연결
# host = "srv1.kitriwhs.kr"
# port = 21640
host = "host1.dreamhack.games"
port = 21581
r = remote(host, port)

BLOCK_SIZE = 16

# 16-byte의 0 암호화해서 E(k, k) 구하기
p = bytes(16).hex().encode()

r.sendlineafter(b"[3] Get Flag\n", b"1")
r.sendlineafter(b"(hex): ", p)

enc_iv = r.recvline().decode()
enc_iv = bytes.fromhex(enc_iv)


# 키 구하기
r.sendlineafter(b"[3] Get Flag\n", b"2")
r.sendlineafter(b"(hex): ", p * 4 + enc_iv.hex().encode())

iv = r.recvline().decode()
iv = (bytes.fromhex(iv)[16:32]).hex()

for i in range(5):
  r.sendlineafter(b"[3] Get Flag\n", b"2")
  r.sendlineafter(b"(hex): ", iv)
  iv = r.recvline().decode()

key = iv
print("key: ", key)


# 암호화된 flag 값 받아오기
r.sendlineafter(b"[3] Get Flag\n", b"3")
r.recvuntil(b"flag = ")

enc_flag = r.recvline().decode()
enc_flag = bytes.fromhex(enc_flag)


# flag 복호화

flag = unpad(AES.new(key, AES.MODE_CBC, key).decrypt(enc_flag), BLOCK_SIZE)

print(flag)
