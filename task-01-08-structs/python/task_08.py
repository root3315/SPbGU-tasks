from dataclasses import dataclass

LINE = "=" * 56
SEPARATOR = "-" * 56


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


def print_not_found():
    print("Подходящих записей нет")


# Задача 8. Мотоциклы
@dataclass
class Motorcycle:
    brand: str
    color: str
    serial_number: str
    registration_number: str
    manufacture_year: int
    inspection_year: int
    price: float


def print_motorcycle(number, motorcycle):
    print(f"Мотоцикл #{number}")
    print(f"  Марка: {motorcycle.brand}")
    print(f"  Цвет: {motorcycle.color}")
    print(f"  Серийный номер: {motorcycle.serial_number}")
    print(f"  Регистрационный номер: {motorcycle.registration_number}")
    print(f"  Год выпуска: {motorcycle.manufacture_year}")
    print(f"  Год техосмотра: {motorcycle.inspection_year}")
    print(f"  Цена: {motorcycle.price:.2f} руб.")
    print(SEPARATOR)


def task_08():
    motorcycles = [
        Motorcycle("HarleyDavidson", "чёрный", "HD100234", "1234АВ78", 2021, 2025, 1850000),
        Motorcycle("Yamaha", "синий", "YM987654", "5678ВЕ78", 2020, 2024, 850000),
        Motorcycle("HarleyDavidson", "красный", "HD200567", "9012КМ78", 2023, 2026, 2150000),
        Motorcycle("Honda", "белый", "HN456789", "3456НО78", 2019, 2023, 720000),
        Motorcycle("HarleyDavidson", "серебристый", "HD300890", "7890РС78", 2022, 2026, 1950000),
    ]

    print_title('Мотоциклы марки "HarleyDavidson":')
    found = [motorcycle for motorcycle in motorcycles if motorcycle.brand == "HarleyDavidson"]
    for number, motorcycle in enumerate(found, 1):
        print_motorcycle(number, motorcycle)
    if not found:
        print_not_found()



if __name__ == "__main__":
    task_08()
