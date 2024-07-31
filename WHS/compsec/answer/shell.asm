global main

main:
  mov   rdi, 1
  mov   rsi, 0x68732f6e69622f
  mov   rax, 0x1
  syscall
  mov   rax, 0x68732f6e69622f
  push  rax
  mov   rdi, rsp
  xor   esi, esi
  xor   edx, edx
  mov   rax, 0x3b
  syscall
  ret