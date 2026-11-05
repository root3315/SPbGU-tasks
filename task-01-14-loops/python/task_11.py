# Задача 11. Таблица степеней двойки
print("Таблица степеней двойки")
print()
power = 1
for exponent in range(11):
    print(f"{exponent:3}{power:7}")
    power *= 2
