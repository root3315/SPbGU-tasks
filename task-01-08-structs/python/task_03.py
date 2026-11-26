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


# Задача 3. Международные компании
@dataclass
class Company:
    name: str
    website: str
    head_office: Address
    years_on_market: int
    employees: int
    europe_branches: int


def print_company(number, company):
    print(f"Компания #{number}")
    print(f"  Название: {company.name}")
    print(f"  Сайт: {company.website}")
    print(f"  Адрес главного офиса: {format_address(company.head_office)}")
    print(f"  Лет на мировом рынке: {company.years_on_market}")
    print(f"  Сотрудников: {company.employees}")
    print(f"  Филиалов в Европе: {company.europe_branches}")
    print(SEPARATOR)


def task_03():
    companies = [
        Company("Nordic Logistics", "https://nordic-logistics.example",
                Address("10115", "Германия", "Берлин", "Митте", "Берлин",
                        "Friedrichstrasse", "120", "4"), 35, 24500, 18),
        Company("Volga Software", "https://volga-software.example",
                Address("420111", "Россия", "Республика Татарстан", "Вахитовский район",
                        "Казань", "ул. Баумана", "44", "3"), 12, 3200, 2),
        Company("Atlantic Foods", "https://atlantic-foods.example",
                Address("75008", "Франция", "Иль-де-Франс", "8-й округ", "Париж",
                        "Rue de Rivoli", "15", "2"), 58, 10000, 27),
        Company("Baltic Energy", "https://baltic-energy.example",
                Address("00100", "Финляндия", "Уусимаа", "Центр", "Хельсинки",
                        "Mannerheimintie", "8", "11"), 41, 15800, 9),
    ]

    print_title("Международные компании, в которых больше 10000 сотрудников:")
    found = [company for company in companies if company.employees > 10000]
    for number, company in enumerate(found, 1):
        print_company(number, company)
    if not found:
        print_not_found()


if __name__ == "__main__":
    task_03()
