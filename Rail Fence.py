pt = input("Enter plaintext: ")
rails = int(input("Enter number of rails: "))

# Track alpha chars and their positions
pos, clean = [], []
for i, c in enumerate(pt):
    if c.isalpha():
        pos.append((i, c.isupper()))
        clean.append(c.upper())

# Zig-zag pattern
rail = ['' for _ in range(rails)]
pattern = []
row, dir = 0, 1
for c in clean:
    rail[row] += c
    pattern.append(row)
    row += dir
    if row == 0 or row == rails - 1: dir *= -1

# Encrypted text
enc = ''.join(rail)
ct = list(pt)
j = 0
for i, up in pos:
    ch = enc[j]
    ct[i] = ch if up else ch.lower()
    j += 1
print("\nEncrypted:", ''.join(ct))

# Rail display
print("\nZig-Zag Rails:")
disp = [[' ']*len(clean) for _ in range(rails)]
row, dir = 0, 1
for i, c in enumerate(clean):
    disp[row][i] = c
    row += dir
    if row == 0 or row == rails - 1: dir *= -1
for line in disp:
    print(''.join(line))

# Decryption
counts = [pattern.count(i) for i in range(rails)]
split = []
i = 0
for c in counts:
    split.append(list(enc[i:i+c]))
    i += c

dec = []
for r in pattern:
    dec.append(split[r].pop(0))

pt2 = list(pt)
j = 0
for i, up in pos:
    ch = dec[j]
    pt2[i] = ch if up else ch.lower()
    j += 1
print("\nDecrypted:", ''.join(pt2))
