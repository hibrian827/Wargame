from pwn import remote
from Crypto.Util.number import bytes_to_long, long_to_bytes, inverse
from hashlib import sha1

# -------------------------------- method --------------------------------


def messageToHex(m):
    return hex(bytes_to_long(m.encode("utf-8")))[2:].encode("utf-8")


def h(m):
    return bytes_to_long(sha1(m.encode("utf-8")).digest())


def remoteInput(r, n):
    r.recvuntil(b"Info\n")
    r.sendline(str(n).encode("utf-8"))
    if n == 1 or n == 2:
        rem.recvuntil(b": ")


# ------------------------------ main  code ------------------------------

port = 23038
rem = remote("host1.dreamhack.games", port)

remoteInput(rem, 1)
m1 = "hello"
rem.sendline(messageToHex(m1))
sign1 = rem.recvline().decode("utf-8")
sign1 = map(int, sign1[1 : len(sign1) - 2].split(", "))

remoteInput(rem, 1)
m2 = "world"
rem.sendline(messageToHex(m2))
sign2 = rem.recvline().decode("utf-8")
sign2 = map(int, sign2[1 : len(sign2) - 2].split(", "))

r1, d1 = sign1
r2, d2 = sign2

remoteInput(rem, 3)
p = rem.recvline().decode("utf-8")
p = p[4 : len(p) - 1]
p = int(p)
q = rem.recvline().decode("utf-8")
q = q[4 : len(q) - 1]
q = int(q)
g = rem.recvline().decode("utf-8")
g = g[4 : len(g) - 1]
g = int(g)
y = rem.recvline().decode("utf-8")
y = y[4 : len(y) - 1]
y = int(y)
m = rem.recvline().decode("utf-8")
m = bytes_to_long((m[10 : len(m) - 2]).encode("utf-8"))

h_m1 = h(m1)
h_m2 = h(m2)
k = (h_m1 - h_m2) * inverse(d1 - d2, q) % q
x = (d1 * k - h_m1) * inverse(r1, q) % q
r = pow(g, k, p) % q
d = (h(long_to_bytes(m).decode("utf-8")) + x * r) * inverse(k, q) % q

remoteInput(rem, 2)
rem.sendline(hex(m)[2:].encode("utf-8"))
rem.recvuntil(b": ")
rem.sendline((str(r) + ", " + str(d)).encode("utf-8"))
print(rem.recvline())
print(rem.recvline())
