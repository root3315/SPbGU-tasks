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


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


# Вариант 13
def task_13_1():
    print_title("Вариант 13. Задача 1: время с ведущими нулями")
    seconds = read_time("Время (ЧЧ:ММ:СС): ", True)
    if seconds is None:
        return

    print(f"Часы (00-23): {seconds // 3600:02}")
    print(f"Минуты (00-59): {seconds % 3600 // 60:02}")
    print(f"Секунды (00-59): {seconds % 60:02}")
    print(f"Время: {format_time(seconds)}")


def task_13_2():
    print_title("Вариант 13. Задача 2: предвыборная агитация")
    voting = read_date("Дата голосования (ДД.ММ.ГГГГ): ", 1900, 2100)
    if voting is None:
        return

    today = now().date()
    if voting > today:
        print(f"До голосования осталось дней: {(voting - today).days}")
    elif voting == today:
        print("Голосование проходит сегодня")
    else:
        print("Голосование уже прошло")
    agitation_end = voting - timedelta(days=1)
    print(f"Агитация прекращается {format_date(agitation_end)} в 00:00")


def task_13():
    task_13_1()
    task_13_2()


if __name__ == "__main__":
    task_13()
