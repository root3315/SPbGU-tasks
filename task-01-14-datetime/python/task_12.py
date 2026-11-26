import calendar
from datetime import date, datetime, timedelta

LINE = "=" * 56
WEEKDAYS = ["понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"]
WEEKDAYS_SHORT = ["пн", "вт", "ср", "чт", "пт", "сб", "вс"]


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


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


def parse_time(text, with_seconds):
    """Секунды от начала суток для ЧЧ:ММ:СС (или ЧЧ:ММ); None, если время неверное."""
    parts = parse_parts(text, ":", 3 if with_seconds else 2)
    if parts is None:
        return None
    hours, minutes = parts[0], parts[1]
    seconds = parts[2] if with_seconds else 0
    if hours > 23 or minutes > 59 or seconds > 59:
        return None
    return hours * 3600 + minutes * 60 + seconds


def parse_datetime(text, min_year, max_year):
    parts = text.split()
    if len(parts) != 2:
        return None
    day = parse_date(parts[0], min_year, max_year)
    seconds = parse_time(parts[1], False)
    if day is None or seconds is None:
        return None
    return make_datetime(day, seconds)


def read_date(prompt, min_year=1, max_year=9999):
    value = parse_date(read_text(prompt), min_year, max_year)
    if value is None:
        print(f"Ошибка! Нужна дата в виде ДД.ММ.ГГГГ, год от {min_year} до {max_year}")
    return value


def read_datetime(prompt, min_year, max_year):
    value = parse_datetime(read_text(prompt), min_year, max_year)
    if value is None:
        print(f"Ошибка! Нужны дата и время в виде ДД.ММ.ГГГГ ЧЧ:ММ, год от {min_year} до {max_year}")
    return value


def make_datetime(day, seconds):
    return datetime(day.year, day.month, day.day) + timedelta(seconds=seconds)


def seconds_between(start, end):
    return int((end - start).total_seconds())


def weekday_text(day):
    number = day.isoweekday()
    return f"{number} ({WEEKDAYS[number - 1]})"


# Вариант 12
def task_12_1():
    print_title("Вариант 12. Задача 1: форматирование даты")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    print(f"День (01-31): {day.day:02}")
    print(f"День недели (пн-вс): {WEEKDAYS_SHORT[day.isoweekday() - 1]}")
    print(f"Месяц (01-12): {day.month:02}")
    print(f"Год (0000-9999): {day.year:04}")


def task_12_2():
    print_title("Вариант 12. Задача 2: минута года исторического события")
    event = read_datetime("Дата и время события (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1, 9999)
    if event is None:
        return

    year_start = datetime(event.year, 1, 1)
    minute = seconds_between(year_start, event) // 60 + 1
    print(f"Событие произошло на {minute}-й минуте от начала года")
    print(f"День недели: {weekday_text(event.date())}")


def task_12():
    task_12_1()
    task_12_2()


if __name__ == "__main__":
    task_12()
