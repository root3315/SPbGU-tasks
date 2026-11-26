import calendar
from datetime import date, datetime

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


def read_date(prompt, min_year=1, max_year=9999):
    value = parse_date(read_text(prompt), min_year, max_year)
    if value is None:
        print(f"Ошибка! Нужна дата в виде ДД.ММ.ГГГГ, год от {min_year} до {max_year}")
    return value


def read_time(prompt, with_seconds):
    value = parse_time(read_text(prompt), with_seconds)
    if value is None:
        print("Ошибка! Нужно время в виде " + ("ЧЧ:ММ:СС" if with_seconds else "ЧЧ:ММ"))
    return value


# Вариант 3
def task_03_1():
    print_title("Вариант 3. Задача 1: время без ведущих нулей")
    seconds = read_time("Время (ЧЧ:ММ:СС): ", True)
    if seconds is None:
        return

    hours, minutes, rest = seconds // 3600, seconds % 3600 // 60, seconds % 60
    print(f"Часы (0-23): {hours}")
    print(f"Минуты (0-59): {minutes}")
    print(f"Секунды (0-59): {rest}")
    print(f"Время: {hours}:{minutes}:{rest}")


def task_03_2():
    print_title("Вариант 3. Задача 2: срок давности правонарушения")
    offence = read_date("Дата правонарушения (ДД.ММ.ГГГГ): ", 1900, 2100)
    if offence is None:
        return

    today = now().date()
    if offence > today:
        print("Ошибка! Дата правонарушения ещё не наступила")
        return

    months = (today.year - offence.year) * 12 + today.month - offence.month
    if today.day < offence.day:
        months -= 1
    print(f"Прошло полных дней: {(today - offence).days}")
    print(f"Прошло полных месяцев: {months}")
    print(f"Прошло полных лет: {months // 12}")


def task_03():
    task_03_1()
    task_03_2()


if __name__ == "__main__":
    task_03()
