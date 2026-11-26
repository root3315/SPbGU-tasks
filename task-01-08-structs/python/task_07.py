from dataclasses import dataclass

LINE = "=" * 56
SEPARATOR = "-" * 56


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


def print_not_found():
    print("Подходящих записей нет")


# Задача 7. Области
@dataclass
class Region:
    name: str
    center: str
    population: int
    area: int
    governor: str


def print_region(number, region):
    print(f"Область #{number}")
    print(f"  Название: {region.name}")
    print(f"  Областной центр: {region.center}")
    print(f"  Население: {region.population} чел.")
    print(f"  Площадь: {region.area} кв. км")
    print(f"  Губернатор: {region.governor}")
    print(SEPARATOR)


def task_07():
    regions = [
        Region("Псковская область", "Псков", 570000, 55399, "Иванов Иван Иванович"),
        Region("Ленинградская область", "Гатчина", 2040000, 83908, "Петров Пётр Петрович"),
        Region("Новгородская область", "Великий Новгород", 580000, 54501, "Сидоров Сергей Олегович"),
        Region("Свердловская область", "Екатеринбург", 4240000, 194307, "Козлов Андрей Николаевич"),
        Region("Мурманская область", "Мурманск", 650000, 144902, "Фёдоров Михаил Юрьевич"),
    ]

    print_title("Области, население которых меньше 1 млн жителей:")
    found = [region for region in regions if region.population < 1000000]
    for number, region in enumerate(found, 1):
        print_region(number, region)
    if not found:
        print_not_found()


if __name__ == "__main__":
    task_07()
