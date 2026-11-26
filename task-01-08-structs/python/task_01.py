from dataclasses import dataclass

LINE = "=" * 56
SEPARATOR = "-" * 56


@dataclass
class Date:
    year: int
    month: int
    day: int


def format_date(date):
    return f"{date.day:02}.{date.month:02}.{date.year}"


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


if __name__ == "__main__":
    task_01()
