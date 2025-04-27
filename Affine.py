from math import gcd

pt = input("Enter plaintext: ")
a = int(input("Enter key 'a' (must be coprime with 26): "))
b = int(input("Enter key 'b': "))

# Find modular inverse of a
for x in range(1, 26):
    if (a * x) % 26 == 1:
        a_inv = x
        break

# Encrypt
enc = ""
for c in pt:
    if c.isalpha():
        up = c.isupper()
        val = ord(c.upper()) - 65
        code = (a * val + b) % 26
        ch = chr(code + 65)
        enc += ch if up else ch.lower()
    else:
        enc += c
print("Encrypted:", enc)

# Decrypt
dec = ""
for c in enc:
    if c.isalpha():
        up = c.isupper()
        val = ord(c.upper()) - 65
        code = (a_inv * (val - b)) % 26
        ch = chr(code + 65)
        dec += ch if up else ch.lower()
    else:
        dec += c
print("Decrypted:", dec)
