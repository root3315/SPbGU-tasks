# Задача 6. Приветствие
print("Как Вас зовут?")
print("Введите свое имя и фамилию, затем нажмите Enter")
name = input("-> ").strip()

if not name:
    print("Ошибка! Имя не введено")
else:
    print(f"Здравствуйте, {name}!")
