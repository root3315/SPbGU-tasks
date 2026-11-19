# Задача 8. Имя, отчество и фамилия
print("Введите в одной строке имя, отчество и фамилию")
words = input("-> ").split()

if len(words) != 3:
    print("Ошибка! Нужно ввести три слова: имя, отчество и фамилию")
else:
    name, patronymic, surname = words
    print(f"Имя: {name}")
    print(f"Отчество: {patronymic}")
    print(f"Фамилия: {surname}")

input("Для завершения нажмите Enter")
