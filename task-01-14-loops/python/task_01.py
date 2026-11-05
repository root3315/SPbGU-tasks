# Задача 1. Печать фотографий
try:
    print("Фото")
    print("Размер:")
    print("1 – 9х12")
    print("2 – 10х15")
    print("3 – 18х24")
    choice = int(input("Ваш выбор –> "))
    quantity = int(input("Количество –> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    # Цены из присланного образца
    prices = {1: 3.50, 2: 5.00, 3: 10.00}

    if choice not in prices:
        print("Ошибка! Неверный выбор размера")
    elif quantity <= 0:
        print("Ошибка! Количество должно быть больше нуля")
    elif quantity > 1000000:
        print("Ошибка! Слишком большое количество")
    else:
        price = prices[choice]
        total = price * quantity
        # Скидка 10% предоставляется, если фотографий больше 10
        discount = total * 0.10 if quantity > 10 else 0

        print("-----------------------------")
        print(f"Цена: {price:.2f} руб.")
        print(f"Количество: {quantity} шт.")
        print(f"Сумма: {total:.2f} руб.")
        print(f"Скидка: {discount:.2f} руб.")
        print(f"К оплате: {total - discount:.2f} руб.")
