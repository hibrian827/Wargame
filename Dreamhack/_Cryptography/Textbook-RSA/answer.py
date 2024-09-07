from pwn import remote
from Crypto.Util.number import inverse, long_to_bytes

port = 2077
r = remote("host1.dreamhack.games", port)
r.recvline()
for i in range(0, 3):
    r.recvline()
r.sendline(b"3")

n = r.recvline().decode("utf-8")
r.recvline()
c = r.recvline().decode("utf-8")

n = n[3 : len(n) - 1]
c = c[6 : len(c) - 1]
n = int(n)
c = int(c)

c_new = c * pow(2, 65537) % n
c_new = hex(c_new)[2:]
c_new = bytes(c_new, "utf-8")

for i in range(0, 3):
    r.recvline()
r.sendline(b"2")
r.recvuntil(b": ")
r.sendline(c_new)
m_new = int(r.recvline().decode("utf-8"))

m = m_new * inverse(2, n) % n
print(long_to_bytes(m))
