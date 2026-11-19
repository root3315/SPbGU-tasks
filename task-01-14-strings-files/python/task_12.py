# Задача 12. Добавление в справочник
CONTACTS_FILE = "contacts.txt"

print("Добавление информации в телефонный справочник")
surname = input("Фамилия -> ").strip()
name = input("Имя -> ").strip()
phone = input("Телефон -> ").strip()

if not (surname and name and phone):
    print("Ошибка! Все поля должны быть заполнены")
else:
    try:
        # Режим "a" дописывает в конец файла и создаёт файл, если его нет
        with open(CONTACTS_FILE, "a", encoding="utf-8") as file:
            file.write(f"{surname}\n{name}\n{phone}\n")
    except OSError:
        print("Ошибка! Не удалось записать файл")
    else:
        print("Информация добавлена")

input("Для завершения нажмите Enter")
