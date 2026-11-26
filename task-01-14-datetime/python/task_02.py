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


def seconds_of_day(moment):
    return moment.hour * 3600 + moment.minute * 60 + moment.second


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


def format_hm(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}"


def format_datetime(moment):
    return f"{format_date(moment.date())} {format_time(seconds_of_day(moment))}"


def weekday_text(day):
    number = day.isoweekday()
    return f"{number} ({WEEKDAYS[number - 1]})"


def same_day_in_year(day, year):
    """Тот же день и месяц в другом году; 29 февраля в невисокосном году — 28 февраля."""
    return date(year, day.month, min(day.day, days_in_month(year, day.month)))


# Вариант 2
def task_02_1():
    print_title("Вариант 2. Задача 1: текущие дата и время")
    print(f"Сейчас: {format_datetime(now())}")


def task_02_2():
    print_title("Вариант 2. Задача 2: срок действия пакета связи")
    call_date = read_date("Дата последнего исходящего звонка (ДД.ММ.ГГГГ): ", 1900, 2100)
    if call_date is None:
        return
    call_time = read_time("Время звонка (ЧЧ:ММ): ", False)
    if call_time is None:
        return

    end_date = same_day_in_year(call_date, call_date.year + 1)
    print(f"Пакет действует до: {format_date(end_date)} {format_hm(call_time)}")
    print(f"День недели: {weekday_text(end_date)}")


def task_02():
    task_02_1()
    task_02_2()


if __name__ == "__main__":
    task_02()
