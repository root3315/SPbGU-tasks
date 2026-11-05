# Задача 8. Сумма первых n чисел
try:
    print("Сумма положительных чисел")
    count = int(input("Введите количество суммируемых чисел -> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if count <= 0:
        print("Ошибка! Количество должно быть больше нуля")
    elif count > 1000000:
        print("Ошибка! Слишком большое количество")
    else:
        total = 0
        for number in range(1, count + 1):
            total += number
        print(f"Сумма первых {count} положительных чисел равна {total}")
