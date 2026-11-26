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


def print_not_found():
    print("Подходящих записей нет")


# Задача 1. Футболисты
@dataclass
class Footballer:
    surname: str
    name: str
    patronymic: str
    sex: str
    nationality: str
    height: int
    weight: int
    birth_date: Date
    phone: str
    team: str
    team_number: int
    position: str
    goals: int
    games: int


def print_footballer(number, player):
    print(f"Футболист #{number}")
    print(f"  Фамилия: {player.surname}")
    print(f"  Имя: {player.name}")
    print(f"  Отчество: {player.patronymic}")
    print(f"  Пол: {player.sex}")
    print(f"  Национальность: {player.nationality}")
    print(f"  Рост: {player.height} см")
    print(f"  Вес: {player.weight} кг")
    print(f"  Дата рождения: {format_date(player.birth_date)}")
    print(f"  Телефон: {player.phone}")
    print(f"  Команда: {player.team}")
    print(f"  Номер в команде: {player.team_number}")
    print(f"  Амплуа: {player.position}")
    print(f"  Голы: {player.goals}")
    print(f"  Игры: {player.games}")
    print(SEPARATOR)


def task_01():
    footballers = [
        Footballer("Смирнов", "Алексей", "Игоревич", "мужской", "русский", 182, 77,
                   Date(1998, 3, 14), "+7 911 100-20-30", "Зенит", 9, "нападающий", 41, 87),
        Footballer("Кузнецов", "Денис", "Олегович", "мужской", "русский", 188, 83,
                   Date(2003, 11, 2), "+7 921 200-30-40", "Зенит", 4, "защитник", 2, 34),
        Footballer("Алиев", "Руслан", "Тимурович", "мужской", "азербайджанец", 176, 70,
                   Date(1996, 7, 21), "+7 903 300-40-50", "Спартак", 10, "полузащитник", 18, 112),
        Footballer("Новиков", "Павел", "Андреевич", "мужской", "русский", 191, 86,
                   Date(2001, 1, 30), "+7 916 400-50-60", "ЦСКА", 1, "вратарь", 0, 50),
    ]

    print_title("Футболисты, которые провели за свою команду больше 50 матчей:")
    found = [player for player in footballers if player.games > 50]
    for number, player in enumerate(found, 1):
        print_footballer(number, player)
    if not found:
        print_not_found()


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


# Задача 5. Мультфильмы
@dataclass
class Cartoon:
    title: str
    studio: str
    director_surname: str
    director_name: str
    year: int
    country: str
    budget: float
    revenue: float

    def profit(self):
        return self.revenue - self.budget


def print_cartoon(number, cartoon):
    print(f"Мультфильм #{number}")
    print(f"  Название: {cartoon.title}")
    print(f"  Студия: {cartoon.studio}")
    print(f"  Режиссёр: {cartoon.director_surname} {cartoon.director_name}")
    print(f"  Год выхода: {cartoon.year}")
    print(f"  Страна: {cartoon.country}")
    print(f"  Стоимость: {cartoon.budget:.2f} млн долл.")
    print(f"  Доход: {cartoon.revenue:.2f} млн долл.")
    print(f"  Прибыль: {cartoon.profit():.2f} млн долл.")
    print(SEPARATOR)


def task_05():
    cartoons = [
        Cartoon("Король Лев", "Walt Disney", "Аллерс", "Роджер", 1994, "США", 45, 968.5),
        Cartoon("Шрек", "DreamWorks", "Адамсон", "Эндрю", 2001, "США", 60, 484.4),
        Cartoon("Холодное сердце", "Walt Disney", "Бак", "Крис", 2013, "США", 150, 1280.8),
        Cartoon("Как приручить дракона", "DreamWorks", "Деблуа", "Дин", 2010, "США", 165, 494.9),
    ]

    print_title('Мультфильмы компании "Walt Disney":')
    found = [cartoon for cartoon in cartoons if cartoon.studio == "Walt Disney"]
    for number, cartoon in enumerate(found, 1):
        print_cartoon(number, cartoon)
    if not found:
        print_not_found()


# Задача 6. Баскетболисты
@dataclass
class BasketballPlayer:
    surname: str
    name: str
    patronymic: str
    sex: str
    nationality: str
    height: int
    weight: int
    birth_date: Date
    phone: str
    team: str
    team_number: int
    position: str
    points: int
    games: int


def print_basketball_player(number, player):
    print(f"Баскетболист #{number}")
    print(f"  Фамилия: {player.surname}")
    print(f"  Имя: {player.name}")
    print(f"  Отчество: {player.patronymic}")
    print(f"  Пол: {player.sex}")
    print(f"  Национальность: {player.nationality}")
    print(f"  Рост: {player.height} см")
    print(f"  Вес: {player.weight} кг")
    print(f"  Дата рождения: {format_date(player.birth_date)}")
    print(f"  Телефон: {player.phone}")
    print(f"  Команда: {player.team}")
    print(f"  Номер в команде: {player.team_number}")
    print(f"  Амплуа: {player.position}")
    print(f"  Очки: {player.points}")
    print(f"  Игры: {player.games}")
    print(SEPARATOR)


def task_06():
    players = [
        BasketballPlayer("Морозов", "Артём", "Сергеевич", "мужской", "русский", 205, 102,
                         Date(1999, 6, 8), "+7 911 500-60-70", "Зенит", 23, "центровой", 412, 38),
        BasketballPlayer("Лебедев", "Никита", "Ильич", "мужской", "русский", 191, 85,
                         Date(2004, 2, 17), "+7 921 600-70-80", "Зенит", 7, "разыгрывающий", 96, 21),
        BasketballPlayer("Ахмедов", "Тимур", "Рустамович", "мужской", "татарин", 198, 94,
                         Date(2000, 10, 5), "+7 917 700-80-90", "УНИКС", 11, "форвард", 150, 30),
        BasketballPlayer("Григорьев", "Олег", "Петрович", "мужской", "русский", 201, 98,
                         Date(1997, 12, 19), "+7 926 800-90-00", "ЦСКА", 14, "форвард", 287, 42),
    ]

    print_title("Баскетболисты, которые набрали за свою команду больше 150 очков:")
    found = [player for player in players if player.points > 150]
    for number, player in enumerate(found, 1):
        print_basketball_player(number, player)
    if not found:
        print_not_found()


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


TASKS = {
    "1": ("Футболисты", task_01),
    "2": ("Студенты", task_02),
    "3": ("Международные компании", task_03),
    "4": ("Зоопарки", task_04),
    "5": ("Мультфильмы", task_05),
    "6": ("Баскетболисты", task_06),
    "7": ("Области", task_07),
    "8": ("Мотоциклы", task_08),
}


def main():
    while True:
        print("\n" + "=" * 45)
        for number, (title, _) in TASKS.items():
            print(f"{number:>2}. {title}")
        print(" 0. Выход")
        print("=" * 45)

        choice = input("Номер задачи -> ").strip()
        if choice == "0":
            break

        print()
        if choice in TASKS:
            TASKS[choice][1]()
        else:
            print("Нет такой задачи")


if __name__ == "__main__":
    try:
        main()
    except EOFError:
        pass  # ввод закрыт: просто завершаем программу
