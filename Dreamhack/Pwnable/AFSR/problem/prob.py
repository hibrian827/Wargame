from Crypto.Util.number import bytes_to_long
from AFSR import AFSR
from flag import FLAG

FLAG = bytes_to_long(FLAG)
afsr = AFSR(FLAG)

leaked_bytes = afsr.getNbytes(200)

# Here is hint for you :P
print(leaked_bytes.hex())