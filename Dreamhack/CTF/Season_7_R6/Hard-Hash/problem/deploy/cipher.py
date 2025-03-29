right_shift = lambda x, y: ((x >> y) ^ (x << (8 - y))) & 255


class DHHash:
    # from sage: n(bytes_to_long(b'DreamHack')^(1/2), 200).hex(). Don't care about it!
    k = bytes.fromhex("45f47adb8838181691b06cda6ce627c2d58e35767ba17829")

    # from sage: n(bytes_to_long(b'DreamHack')^(1/3), 200).hex(). Don't care about it!
    h = bytes.fromhex("4ebf4ee89a2173994cafe5dcdc2454ccb9992246c7ec2e4c")

    def __init__(self, msg):
        self.msg = msg + (6 - len(msg) % 6) * bytes([6 - len(msg) % 6])
        print(self.msg)

    def digest(self):
        h0, h1, h2, h3, h4, h5 = self.h[:6]
        for i in range(0, len(self.msg), 6):
            msg_chunk = self.msg[i : i + 6]
            w = list(msg_chunk + b"\x00" * 18)
            print(w)
            for i in range(6, 24):
                s0 = right_shift(w[i - 2], 1) ^ right_shift(w[i - 2], 3) ^ right_shift(w[i - 2], 6)
                s1 = right_shift(w[i - 5], 2) ^ right_shift(w[i - 5], 3) ^ right_shift(w[i - 5], 7)
                w[i] = (s0 + s1 + w[i - 3] + w[i - 6]) & 255

            print(w)
            a, b, c, d, e, f = 0, 0, 0, 0, 0, 0
            for i in range(24):
                s1 = right_shift(c, 2) ^ right_shift(c, 4) ^ right_shift(c, 7)
                ch = (c & a) ^ ((~c) & b)
                tmp1 = (f + s1 + ch + self.k[i] + w[i]) & 255
                s0 = right_shift(f, 1) ^ right_shift(f, 2) ^ right_shift(f, 6)
                maj = (d & e) ^ (d & f) ^ (e & f)
                tmp2 = (s0 + maj) & 255

                f = e
                e = d
                d = (c + tmp1) & 255
                c = b
                b = a
                a = (tmp1 + tmp2) & 255

            h0 = (h0 + a) & 255
            h1 = (h1 + b) & 255
            h2 = (h2 + c) & 255
            h3 = (h3 + d) & 255
            h4 = (h4 + e) & 255
            h5 = (h5 + f) & 255

        digest = bytes((h0, h1, h2, h3, h4, h5))
        return digest


if __name__ == "__main__":
    dreamhack = DHHash(b"DreamHack").digest()
    dreamh4ck = DHHash(b"reamHack\x03").digest()
    print(dreamhack.hex())
    # print(dreamh4ck.hex())