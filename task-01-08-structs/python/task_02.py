from dataclasses import dataclass

LINE = "=" * 56
SEPARATOR = "-" * 56


@dataclass
class Date:
    year: int
    month: int
    day: int


@dataclass
class Address:
    postal_code: str
    country: str
    region: str
    district: str
    city: str
    street: str
    house: str
    apartment: str


def format_date(date):
    return f"{date.day:02}.{date.month:02}.{date.year}"


def format_address(address):
    return (f"{address.postal_code}, {address.country}, {address.region}, "
            f"{address.district}, {address.city}, {address.street}, "
            f"д. {address.house}, кв. {address.apartment}")


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


# Задача 2. Студенты
@dataclass
class Student:
    surname: str
    name: str
    patronymic: str
    sex: str
    height: int
    weight: int
    birth_date: Date
    address: Address


def print_student(student):
    print(f"  Фамилия: {student.surname}")
    print(f"  Имя: {student.name}")
    print(f"  Отчество: {student.patronymic}")
    print(f"  Пол: {student.sex}")
    print(f"  Рост: {student.height} см")
    print(f"  Вес: {student.weight} кг")
    print(f"  Дата рождения: {format_date(student.birth_date)}")
    print(f"  Домашний адрес: {format_address(student.address)}")
    print(SEPARATOR)


def birth_key(student):
    date = student.birth_date
    return date.year, date.month, date.day


def task_02():
    students = [
        Student("Орлова", "Екатерина", "Сергеевна", "женский", 168, 55, Date(2005, 9, 12),
                Address("199034", "Россия", "Ленинградская область", "Василеостровский район",
                        "Санкт-Петербург", "Университетская наб.", "7", "12")),
        Student("Васильев", "Илья", "Дмитриевич", "мужской", 180, 72, Date(2006, 4, 3),
                Address("188300", "Россия", "Ленинградская область", "Гатчинский район",
                        "Гатчина", "ул. Чкалова", "15", "48")),
        Student("Ким", "Анна", "Викторовна", "женский", 162, 50, Date(2006, 4, 27),
                Address("690091", "Россия", "Приморский край", "Ленинский район",
                        "Владивосток", "ул. Светланская", "21", "5")),
        Student("Попов", "Максим", "Петрович", "мужской", 185, 80, Date(2004, 12, 30),
                Address("150000", "Россия", "Ярославская область", "Кировский район",
                        "Ярославль", "ул. Свободы", "3", "101")),
    ]

    youngest = max(students, key=birth_key)
    print_title("Самый молодой студент:")
    print_student(youngest)


if __name__ == "__main__":
    task_02()
