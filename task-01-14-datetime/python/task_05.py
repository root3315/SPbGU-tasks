import calendar
from datetime import date

LINE = "=" * 56
SECONDS_IN_DAY = 24 * 60 * 60


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


def format_hm(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}"


# Вариант 5
def task_05_1():
    print_title("Вариант 5. Задача 1: проверка значения на дату")
    text = read_text("Значение: ")
    if parse_date(text) is None:
        print(f'"{text}" не является датой вида ДД.ММ.ГГГГ')
    else:
        print(f'"{text}" является датой')


def task_05_2():
    print_title("Вариант 5. Задача 2: расписание процедур")
    first = read_time("Время первой процедуры (ЧЧ:ММ): ", False)
    if first is None:
        return
    second = read_time("Время следующей процедуры (ЧЧ:ММ): ", False)
    if second is None:
        return
    count = read_int("Количество процедур: ", 1, 100)
    if count is None:
        return

    interval = (second - first) % SECONDS_IN_DAY
    if interval == 0:
        print("Ошибка! Следующая процедура должна быть в другое время")
        return

    print("Время процедур:")
    for number in range(count):
        moment = first + number * interval
        line = f"{number + 1:3}. {format_hm(moment % SECONDS_IN_DAY)}"
        if moment >= SECONDS_IN_DAY:
            line += f" (+{moment // SECONDS_IN_DAY} дн.)"
        print(line)


def task_05():
    task_05_1()
    task_05_2()


if __name__ == "__main__":
    task_05()
