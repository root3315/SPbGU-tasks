# Задача 11. Перевод в другую систему
def to_base(number, base):
    """Переводит неотрицательное целое число в систему с основанием base делением."""
    if number == 0:
        return "0"

    digits = ""
    while number > 0:
        # Остатки от деления дают цифры с конца
        digits = str(number % base) + digits
        number //= base
    return digits


try:
    number = int(input("Введите целое число -> "))
    base = int(input("Введите основание системы счисления -> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if abs(number) > 1000000000:
        print("Ошибка! Число должно быть от -1000000000 до 1000000000")
    elif not 2 <= base <= 10:
        print("Ошибка! Основание должно быть от 2 до 10")
    else:
        sign = "-" if number < 0 else ""
        converted = sign + to_base(abs(number), base)
        print(f"Десятичному числу {number} соответствует число {converted} по основанию {base}")
