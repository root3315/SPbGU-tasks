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


def seconds_of_day(moment):
    return moment.hour * 3600 + moment.minute * 60 + moment.second


def seconds_between(start, end):
    return int((end - start).total_seconds())


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


def format_datetime(moment):
    return f"{format_date(moment.date())} {format_time(seconds_of_day(moment))}"


# Вариант 7
def task_07_1():
    print_title("Вариант 7. Задача 1: составляющие даты")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    print(f"День: {day.day}")
    print(f"Месяц: {day.month}")
    print(f"Год: {day.year}")


def task_07_2():
    print_title("Вариант 7. Задача 2: срок годности продукта")
    made = read_datetime("Дата и время производства (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1900, 2100)
    if made is None:
        return
    shelf_hours = read_int("Срок годности, ч: ", 1, 87600)
    if shelf_hours is None:
        return

    current = now()
    if made > current:
        print("Ошибка! Дата производства ещё не наступила")
        return

    expiry = made + timedelta(hours=shelf_hours)
    left = seconds_between(current, expiry)
    if left > 0:
        print(f"Годен до: {format_datetime(expiry)}")
        print(f"До истечения срока годности осталось: {left // 3600} ч")
    else:
        print(f"Внимание! Срок годности истёк {format_datetime(expiry)}")


def task_07():
    task_07_1()
    task_07_2()


if __name__ == "__main__":
    task_07()
