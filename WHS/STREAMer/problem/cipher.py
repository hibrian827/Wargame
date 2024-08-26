class STREAM:
    def __init__(self, seed, size):
        self.state = self.num2bits(seed, size)
        # x^16 + x^14 + x^13 + x^11 + 1
        self.taps = (16, 14, 13, 11)

    def num2bits(self, num, size):
        assert num < (1 << size)

        return bin(num)[2:].zfill(size)
    
    def bits2num(self, bits):
        return int('0b' + bits, 2)
    
    def shift(self):
        new_bit = 0
        for tap in self.taps:
            new_bit ^= int(self.state[tap - 1])
        new_bit = str(new_bit)
        self.state = new_bit + self.state[:-1]
        return new_bit
    
    def getNbits(self, num):
        sequence = ""
        for _ in range(num):
            sequence += self.shift()
        
        return sequence

    def encrypt(self, plaintext):
        ciphertext = b""
        for p in plaintext:
            stream = self.bits2num(self.getNbits(8))
            c = p ^ stream
            ciphertext += bytes([c])

        return ciphertext

    def decrypt(self, ciphertext):
        plaintext = b""
        for c in ciphertext:
            stream = self.bits2num(self.getNbits(8))
            p = c ^ stream
            plaintext += bytes([p])

        return plaintext


if __name__ == "__main__":
    import os

    for seed in range(0x100):
        Alice = STREAM(seed, 16)
        Bob = STREAM(seed, 16)
        plaintext = os.urandom(128)
        ciphertext = Alice.encrypt(plaintext)
        assert plaintext == Bob.decrypt(ciphertext)
