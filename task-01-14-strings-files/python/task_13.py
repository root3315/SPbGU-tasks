# Задача 13. Телефонный справочник
CONTACTS_FILE = "contacts.txt"


def add_contact():
    """Запрашивает фамилию, имя и телефон и дописывает их в справочник."""
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


def find_contacts():
    """Ищет в справочнике абонентов с введённой фамилией."""
    print("Поиск в телефонном справочнике")
    surname = input("Фамилия -> ").strip()

    if not surname:
        print("Ошибка! Фамилия не введена")
        return

    try:
        with open(CONTACTS_FILE, encoding="utf-8") as file:
            lines = [line.strip() for line in file]
    except FileNotFoundError:
        print("Справочник пуст")
    else:
        found = 0
        # На каждого абонента в файле три строки: фамилия, имя, телефон
        for i in range(0, len(lines) - 2, 3):
            if lines[i] == surname:
                print(f"{lines[i]} {lines[i + 1]}: {lines[i + 2]}")
                found += 1

        if found == 0:
            print("Абонент не найден")


while True:
    print("*** Телефонный справочник ***")
    print("1 - Добавление")
    print("2 - Поиск")
    print("0 - Завершение работы")
    choice = input("Ваш выбор -> ").strip()
    if choice == "0":
        break

    if choice == "1":
        add_contact()
    elif choice == "2":
        find_contacts()
    else:
        print("Ошибка! Неверный выбор")
    print()
