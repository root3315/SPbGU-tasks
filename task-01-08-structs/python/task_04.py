from dataclasses import dataclass

LINE = "=" * 56
SEPARATOR = "-" * 56


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


def format_address(address):
    return (f"{address.postal_code}, {address.country}, {address.region}, "
            f"{address.district}, {address.city}, {address.street}, "
            f"д. {address.house}, кв. {address.apartment}")


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


def print_not_found():
    print("Подходящих записей нет")


# Задача 4. Зоопарки
@dataclass
class Species:
    name: str
    count: int


@dataclass
class Zoo:
    name: str
    species: list
    address: Address
    total_animals: int
    workers: int


TIGER = "уссурийский тигр"


def print_zoo(number, zoo):
    print(f"Зоопарк #{number}")
    print(f"  Название: {zoo.name}")
    print("  Животные:")
    for animal in zoo.species:
        print(f"    {animal.name}: {animal.count}")
    print(f"  Адрес: {format_address(zoo.address)}")
    print(f"  Всего животных: {zoo.total_animals}")
    print(f"  Работников: {zoo.workers}")
    print(SEPARATOR)


def has_tigers(zoo):
    return any(animal.name == TIGER and animal.count > 0 for animal in zoo.species)


def task_04():
    zoos = [
        Zoo("Северный зоопарк",
            [Species("уссурийский тигр", 3), Species("бурый медведь", 2), Species("пингвин", 12)],
            Address("197198", "Россия", "Ленинградская область", "Петроградский район",
                    "Санкт-Петербург", "Александровский парк", "1", "1"), 1200, 210),
        Zoo("Южный зоопарк",
            [Species("жираф", 4), Species("зебра", 6), Species("лев", 2)],
            Address("344002", "Россия", "Ростовская область", "Ленинский район",
                    "Ростов-на-Дону", "ул. Зоологическая", "3", "1"), 850, 140),
        Zoo("Приморский сафари-парк",
            [Species("уссурийский тигр", 5), Species("дальневосточный леопард", 2)],
            Address("692481", "Россия", "Приморский край", "Шкотовский район",
                    "Шкотово", "ул. Лесная", "10", "1"), 400, 60),
        Zoo("Городской зоопарк",
            [Species("уссурийский тигр", 0), Species("волк", 5)],
            Address("620075", "Россия", "Свердловская область", "Кировский район",
                    "Екатеринбург", "ул. Мамина-Сибиряка", "189", "1"), 300, 45),
    ]

    print_title("Зоопарки, в которых есть уссурийские тигры:")
    found = [zoo for zoo in zoos if has_tigers(zoo)]
    for number, zoo in enumerate(found, 1):
        print_zoo(number, zoo)
    if not found:
        print_not_found()


if __name__ == "__main__":
    task_04()
