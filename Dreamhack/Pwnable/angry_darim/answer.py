from pwn import *

print(f"\x5f\x75\x43\x30\x6e\x5f_{int(time.time())}") # actually this is the answer
# rem = process(['./Pwnable/angry_darim/problem/darim', f"\x5f\x75\x43\x30\x6e\x5f_{int(time.time())}"])
