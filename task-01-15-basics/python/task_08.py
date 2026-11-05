# Задача 8. Печать фотографий
try:
    print("Фотографии")
    photo_format = int(input("Формат (1 – 9х12; 2 – 10х15) -> "))
    quantity = int(input("Количество, шт. -> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    price_9x12 = 2.50  # в условии цены нет, значение принято самостоятельно
    price_10x15 = 3.20

    if photo_format not in (1, 2):
        print("Ошибка! Неверный формат")
    elif quantity <= 0:
        print("Ошибка! Количество должно быть больше нуля")
    else:
        price = price_9x12 if photo_format == 1 else price_10x15
        total = price * quantity
        # Скидка 5% предоставляется, если фотографий больше 10
        discount = total * 0.05 if quantity > 10 else 0

        print("----------------------------")
        print(f"Цена: {price:.2f} руб.")
        print(f"Количество: {quantity} шт.")
        print(f"Сумма: {total:.2f} руб.")
        print(f"Скидка: {discount:.2f} руб.")
        print(f"К оплате: {total - discount:.2f} руб.")
