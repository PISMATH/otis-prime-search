n = int(input(f"What n to check for 2^n - 3: "))
a = 2
m = 2 ** (n - 2) - 1
p = 2 ** n - 3

print(f'a = {a}')
print(f'm = {m}\n')

b0 = (a ** m) % p
b = [b0]
i = 0
running = True
print(f'b0 = {b0}')
while running:
    new_b = (b[i] ** 2) % p
    print(f'b{i+1} = {new_b}')

    if (i == 0 and new_b in [p - 1, 1]) or (new_b == p - 1):
        print('Yay it\'s prime')
        running = False
        break

    if (new_b in b):
        print(f'Yay it\'s composite with a loop at {b.index(new_b)}')
        running = False
        break

    if new_b == 1:
        print('Yay it\'s composite')
    
    b.append(new_b)
    i += 1
