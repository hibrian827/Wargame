from pwn import remote
from Crypto.Util.Padding import unpad
from Crypto.Cipher import AES
import hashlib

port = 15246
p = remote('host1.dreamhack.games', port)
p.recvuntil(b'>> ')
p.sendline(b'1')
p.recvuntil(b'>> ')
p.sendline(b'1')
p.recvline()
alice = p.recvline().decode('utf-8')
bob = p.recvline().decode('utf-8')
alice_flag = alice[7 : len(alice) - 1]
bob_flag = bob[5 : len(bob) - 1]
print(alice_flag)
print(bob_flag)

sk = 1
aes_key = hashlib.md5(str(sk).encode()).digest()
cipher = AES.new(aes_key, AES.MODE_ECB)
print(unpad(cipher.decrypt(bytes.fromhex(alice_flag)), 16))
print(unpad(cipher.decrypt(bytes.fromhex(bob_flag)), 16))