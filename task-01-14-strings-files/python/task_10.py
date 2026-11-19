# Задача 10. Двоичное в десятичное
print("Введите восьмиразрядное двоичное число и нажмите Enter")
binary = input("-> ").strip()

if len(binary) != 8 or any(digit not in ("0", "1") for digit in binary):
    print("Ошибка! Нужно ввести 8 цифр 0 или 1")
else:
    decimal = 0
    for digit in binary:
        decimal = decimal * 2 + (1 if digit == "1" else 0)
    print(f"Двоичному числу {binary} соответствует десятичное {decimal}")

input("Для завершения нажмите Enter")
