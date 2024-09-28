from pwn import *

port = 10001
rem = remote("kayle.snu.ac.kr", port)

for i in range(20):
  rem.recvuntil(b'which produces ')
  target = int(rem.recvline().rstrip().decode())
  # print(target)

  rem.recvuntil(b'assembly below:\n\n')

  asm = f"""xorq  %r8, %r8
  .loop:
    cmpl  ${target}, %r8d
    je    .done
    addl  $1, %r8d
    jmp   .loop
  .done:
    xorl  %eax, %eax
    addl  %r8d, %eax
  """
  rem.sendline(asm.encode())
  rem.sendline(b'')

for i in range(20):
  rem.recvuntil(b'which produces ')
  target = int(rem.recvline().rstrip().decode())

  rem.recvuntil(b'assembly below:\n\n')

  asm = f"""movq ${target}, %rax"""
  rem.sendline(asm.encode())
  rem.sendline(b'')

# print(rem.recvuntil(b'which produces '))

for i in range(20):
  rem.recvuntil(b'which produces ')
  target = int(rem.recvline().rstrip().decode())
  target = "{0:b}".format(target)

  rem.recvuntil(b'assembly below:\n\n')

  asm =  "shl\t$64, %rax\n"
  asm += "incq\t%rax\n"
  for i in range(1, len(target)):
    digit  = target[i]
    asm += "shl\t$1, %rax\n"
    if digit == "1":
      asm += "incq\t%rax\n"

  rem.sendline(asm.encode())

rem.recvuntil("You passed all!\n")
print(rem.recvline())