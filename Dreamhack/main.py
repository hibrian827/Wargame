from pwn import remote

def messageToHex(m):
  return hex(bytes_to_long(m.encode("utf-8")))[2:].encode("utf-8")

port = 11526
rem = remote("host1.dreamhack.games", port)