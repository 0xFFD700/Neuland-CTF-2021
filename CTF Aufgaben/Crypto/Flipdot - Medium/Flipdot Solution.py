k = 'qoot + password123 ciphertext'

from binascii import unhexlify, hexlify

c = unhexlify(k)
cc = ord('r') ^ ord('q')
ccc = hexlify(bytearray([c[0] ^ cc]) + c[1:])
print(ccc)

# Flag: nland{810ck_c1ph325_423_fun}