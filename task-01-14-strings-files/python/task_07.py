# Задача 7. Код символа
print("Введите символ и нажмите Enter.")
print("Для завершения введите точку.")
while True:
    symbol = input("-> ")
    if symbol == ".":
        break

    if len(symbol) == 1:
        print(f"Символ: {symbol} Код: {ord(symbol)}")
    else:
        print("Ошибка! Введите один символ")
