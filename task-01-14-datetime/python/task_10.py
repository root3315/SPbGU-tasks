import calendar
from datetime import date, datetime

LINE = "=" * 56
WEEKDAYS = ["понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"]


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


def now():
    return datetime.now().replace(microsecond=0)


def read_text(prompt):
    return input(prompt).strip(" \t\r\n")


def is_number(text):
    return 0 < len(text) <= 9 and all("0" <= char <= "9" for char in text)


def parse_parts(text, separator, count):
    """Делит строку на count целых неотрицательных чисел; None, если не получилось."""
    parts = text.split(separator)
    if len(parts) != count or not all(is_number(part) for part in parts):
        return None
    return [int(part) for part in parts]


def days_in_month(year, month):
    return calendar.monthrange(year, month)[1]


def parse_date(text, min_year=1, max_year=9999):
    parts = parse_parts(text, ".", 3)
    if parts is None:
        return None
    day, month, year = parts
    if not (min_year <= year <= max_year and 1 <= month <= 12):
        return None
    if not 1 <= day <= days_in_month(year, month):
        return None
    return date(year, month, day)


def read_date(prompt, min_year=1, max_year=9999):
    value = parse_date(read_text(prompt), min_year, max_year)
    if value is None:
        print(f"Ошибка! Нужна дата в виде ДД.ММ.ГГГГ, год от {min_year} до {max_year}")
    return value


def weekday_text(day):
    number = day.isoweekday()
    return f"{number} ({WEEKDAYS[number - 1]})"


def same_day_in_year(day, year):
    """Тот же день и месяц в другом году; 29 февраля в невисокосном году — 28 февраля."""
    return date(year, day.month, min(day.day, days_in_month(year, day.month)))


# Вариант 10
def task_10_1():
    print_title("Вариант 10. Задача 1: номер дня недели")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    print(f"День недели: {weekday_text(day)}")


def task_10_2():
    print_title("Вариант 10. Задача 2: дни до дня рождения")
    birth = read_date("Дата рождения (ДД.ММ.ГГГГ): ", 1900, 2100)
    if birth is None:
        return

    today = now().date()
    if birth > today:
        print("Ошибка! Дата рождения ещё не наступила")
        return

    birthday = same_day_in_year(birth, today.year)
    if birthday == today:
        print("День рождения сегодня!")
    elif birthday > today:
        print(f"До дня рождения осталось дней: {(birthday - today).days}")
    else:
        print(f"День рождения в этом году уже прошёл, прошло дней: {(today - birthday).days}")


def task_10():
    task_10_1()
    task_10_2()


if __name__ == "__main__":
    task_10()
