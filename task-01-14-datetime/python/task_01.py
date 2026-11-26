import calendar
from datetime import date, datetime, timedelta

LINE = "=" * 56


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


def read_int(prompt, low, high):
    text = read_text(prompt)
    if not is_number(text) or not low <= int(text) <= high:
        print(f"Ошибка! Нужно целое число от {low} до {high}")
        return None
    return int(text)


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


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


# Вариант 1
def task_01_1():
    print_title("Вариант 1. Задача 1: более поздняя из двух дат")
    first = read_date("Первая дата (ДД.ММ.ГГГГ): ")
    if first is None:
        return
    second = read_date("Вторая дата (ДД.ММ.ГГГГ): ")
    if second is None:
        return

    if first > second:
        print(f"Более поздняя дата: {format_date(first)} (первая)")
    elif second > first:
        print(f"Более поздняя дата: {format_date(second)} (вторая)")
    else:
        print("Даты совпадают")


def task_01_2():
    print_title("Вариант 1. Задача 2: контроль батареи ноутбука")
    start = read_datetime("Дата и время включения от батареи (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1900, 2100)
    if start is None:
        return
    declared_hours = read_int("Заявленное время работы от батареи, ч: ", 1, 100)
    if declared_hours is None:
        return

    worked = seconds_between(start, now())
    if worked < 0:
        print("Ошибка! Время включения ещё не наступило")
        return

    print(f"Ноутбук работает от батареи: {worked // 3600} ч {worked % 3600 // 60} мин")
    left = declared_hours * 3600 - worked
    if left > 0:
        print(f"До полного разряда осталось: {left // 60} мин")
    else:
        print("Батарея полностью разряжена")


def task_01():
    task_01_1()
    task_01_2()


if __name__ == "__main__":
    task_01()
