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


if __name__ == "__main__":
    task_06()
