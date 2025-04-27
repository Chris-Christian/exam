key = input("Enter numeric key (e.g. 4312567): ")
pt = input("Enter plaintext: ")

# Preprocess
pos, clean = [], []
for i, c in enumerate(pt):
    if c.isalpha():
        pos.append((i, c.isupper()))
        clean.append(c.upper())

cols = len(key)
while len(clean) % cols != 0:
    clean.append('X')

# Encrypt
rows = [clean[i:i+cols] for i in range(0, len(clean), cols)]
order = sorted([(int(k), i) for i, k in enumerate(key)])
enc = ''.join(row[i] for k, i in order for row in rows)

ct = list(pt)
j = 0
for i, up in pos:
    ct[i] = enc[j] if up else enc[j].lower()
    j += 1
print("\nEncrypted:", ''.join(ct))

# Decrypt
nrows = len(clean) // cols
cols_data = [''] * cols
i = 0
for k, col in order:
    for r in range(nrows):
        cols_data[col] += enc[i]
        i += 1

dec = ''.join(''.join(row) for row in zip(*cols_data))
pt2 = list(pt)
j = 0
for i, up in pos:
    pt2[i] = dec[j] if up else dec[j].lower()
    j += 1
print("Decrypted:", ''.join(pt2))
