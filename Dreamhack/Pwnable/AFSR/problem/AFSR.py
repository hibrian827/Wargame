class AFSR:
    def __init__(self, base):
        self.state = 1
        self.base = base
    
    def shift(self):
        self.state <<= 1
        output = 0
        if self.state >= self.base:
            self.state -= self.base
            output = 1
        return str(output)
    
    def getNbits(self, num):
        output = ''
        for _ in range(num):
            output += self.shift()
        return output

    def getNbytes(self, num):
        output = b''
        for _ in range(num):
            o = self.getNbits(8)
            o = int(o, 2)
            output += bytes([o])
        return output