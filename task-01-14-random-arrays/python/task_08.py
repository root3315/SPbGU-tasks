# Задача 8. Простое число
try:
    print("Введите целое число и нажмите Enter")
    number = int(input("> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if abs(number) > 10**12:
        print("Ошибка! Слишком большое по модулю число")
    else:
        # Числа меньше 2 простыми не считаются; делители ищем до корня из числа
        is_prime = number >= 2
        divisor = 2
        while is_prime and divisor * divisor <= number:
            if number % divisor == 0:
                is_prime = False
            divisor += 1

        if is_prime:
            print(f"{number} - простое число.")
        else:
            print(f"{number} - не простое число.")
