# Задача 2. Минуты в часы и минуты
try:
    interval = int(input("Введите временной интервал (в минутах) -> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if interval < 0:
        print("Ошибка! Интервал не может быть отрицательным")
    else:
        print(f"{interval} минут - это {interval // 60} ч. {interval % 60} мин.")
