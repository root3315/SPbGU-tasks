# Задача 9. Проверка целого числа
def is_integer(text):
    """Проверяет посимвольно: необязательный знак + или -, затем хотя бы одна цифра."""
    if text[:1] in ("+", "-"):
        text = text[1:]
    return text != "" and all("0" <= char <= "9" for char in text)


print("Введите число и нажмите Enter")
text = input("-> ").strip()

if is_integer(text):
    print("Введенная строка является целым числом.")
else:
    print("Введенная строка не является целым числом.")
