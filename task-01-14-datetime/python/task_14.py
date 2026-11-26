import calendar
from datetime import date, datetime, timedelta

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


def read_int(prompt, low, high):
    text = read_text(prompt)
    if not is_number(text) or not low <= int(text) <= high:
        print(f"Ошибка! Нужно целое число от {low} до {high}")
        return None
    return int(text)


def read_time(prompt, with_seconds):
    value = parse_time(read_text(prompt), with_seconds)
    if value is None:
        print("Ошибка! Нужно время в виде " + ("ЧЧ:ММ:СС" if with_seconds else "ЧЧ:ММ"))
    return value


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


def weekday_text(day):
    number = day.isoweekday()
    return f"{number} ({WEEKDAYS[number - 1]})"


# Вариант 14
def task_14_1():
    print_title("Вариант 14. Задача 1: минуты между двумя значениями времени")
    first = read_time("Первое время (ЧЧ:ММ): ", False)
    if first is None:
        return
    second = read_time("Второе время (ЧЧ:ММ): ", False)
    if second is None:
        return

    print(f"Между ними минут: {abs(second - first) // 60}")


def task_14_2():
    print_title("Вариант 14. Задача 2: перенос праздника с воскресенья")
    day = read_int("День праздника (1-31): ", 1, 31)
    if day is None:
        return
    month = read_int("Месяц праздника (1-12): ", 1, 12)
    if month is None:
        return

    year = now().year
    if day > days_in_month(year, month):
        print(f"Ошибка! В {year} году в этом месяце нет такого дня")
        return

    holiday = date(year, month, day)
    print(f"В {year} году праздник выпадает на день недели: {weekday_text(holiday)}")
    if holiday.isoweekday() == 7:
        monday = holiday + timedelta(days=1)
        print(f"Праздник в воскресенье, выходной переносится на понедельник {format_date(monday)}")
    else:
        print("Праздник не в воскресенье, переноса нет")


def task_14():
    task_14_1()
    task_14_2()


if __name__ == "__main__":
    task_14()
