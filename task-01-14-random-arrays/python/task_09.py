# Задача 9. Угадай число
import random

secret = random.randint(1, 10)
attempts_left = 5
prompt = "> "
won = False

print('Игра "Угадай число".')
print('Компьютер "задумал" число от 1 до 10.')
print("Угадайте его за пять попыток.")
print("Введите число и нажмите Enter")
while attempts_left > 0:
    # Ошибка ввода попытку не тратит
    try:
        guess = int(input(prompt))
    except ValueError:
        print("Ошибка! Неверный формат числа")
        continue
    if guess < 1 or guess > 10:
        print("Ошибка! Число должно быть от 1 до 10")
        continue

    if guess == secret:
        won = True
        break
    attempts_left -= 1
    print("Нет.")
    prompt = "-> "

if won:
    print("Вы выиграли! Поздравляю!")
else:
    print(f"Вы проиграли. Компьютер задумал число {secret}.")
