import numpy as np

# Take user input for plaintext and key matrix
pt = input("Enter plaintext: ")
n = int(input("Enter key size (2 or 3): "))

print(f"Enter the {n}x{n} key matrix row by row:")
k = []
for _ in range(n):
    k.append(list(map(int, input().split())))
k = np.array(k)

# --- Preprocess the plaintext ---
pos = []     # stores (index, is_uppercase) for each alphabet
clean = []   # stores only the uppercase letters from plaintext
for i, c in enumerate(pt):
    if c.isalpha():
        pos.append((i, c.isupper()))
        clean.append(c.upper())

# Pad with 'X' so that the length is divisible by matrix size
while len(clean) % n != 0:
    clean.append('X')

# --- Encrypt the cleaned text ---
enc = ""
for i in range(0, len(clean), n):
    block = [ord(c) - 65 for c in clean[i:i+n]]             # Convert chars to numbers (A=0)
    res = np.dot(k, block) % 26                             # Multiply with key matrix mod 26
    enc += ''.join(chr(r + 65) for r in res)                # Convert back to letters

# Rebuild the ciphertext with spaces and original casing
ct = list(pt)
j = 0
for i, up in pos:
    ch = enc[j]
    ct[i] = ch if up else ch.lower()
    j += 1
print("Encrypted:", ''.join(ct))

# === Decryption ===

# 1. Calculate det(K) and its modular inverse mod 26
det = int(round(np.linalg.det(k))) % 26
for i in range(1, 26):
    if (det * i) % 26 == 1:
        det_inv = i
        break

# 2. Get cofactor matrix
cof = np.zeros((n, n))
for r in range(n):
    for c in range(n):
        minor = np.delete(np.delete(k, r, axis=0), c, axis=1)
        cof[r][c] = ((-1) ** (r + c)) * round(np.linalg.det(minor))

# 3. Adjugate = transpose of cofactor
adj = cof.T

# 4. Compute inverse key matrix mod 26
k_inv = (det_inv * adj) % 26
k_inv = k_inv.astype(int)

# 5. Decrypt the ciphertext using inverse key
dec = ""
for i in range(0, len(enc), n):
    block = [ord(c) - 65 for c in enc[i:i+n]]
    res = np.dot(k_inv, block) % 26
    dec += ''.join(chr(r + 65) for r in res)

# Rebuild the original plaintext format (with cases & spaces)
pt2 = list(pt)
j = 0
for i, up in pos:
    ch = dec[j]
    pt2[i] = ch if up else ch.lower()
    j += 1
print("Decrypted:", ''.join(pt2))
