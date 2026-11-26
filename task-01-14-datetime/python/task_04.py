import calendar
from datetime import date

LINE = "=" * 56


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


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


# Вариант 4
def task_04_1():
    print_title("Вариант 4. Задача 1: время из отдельных значений")
    hours = read_int("Часы (0-23): ", 0, 23)
    if hours is None:
        return
    minutes = read_int("Минуты (0-59): ", 0, 59)
    if minutes is None:
        return
    seconds = read_int("Секунды (0-59): ", 0, 59)
    if seconds is None:
        return
    milliseconds = read_int("Миллисекунды (0-999): ", 0, 999)
    if milliseconds is None:
        return

    total = hours * 3600 + minutes * 60 + seconds
    print(f"Время: {format_time(total)}.{milliseconds:03}")


def task_04_2():
    print_title("Вариант 4. Задача 2: високосный год")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    if calendar.isleap(day.year):
        print(f"{day.year} год високосный")
        return

    leap_year = day.year + 1
    while not calendar.isleap(leap_year):
        leap_year += 1
    print(f"{day.year} год не високосный")
    print(f"Ближайший високосный год: {leap_year}, до него лет: {leap_year - day.year}")


def task_04():
    task_04_1()
    task_04_2()


if __name__ == "__main__":
    task_04()
