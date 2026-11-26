from datetime import datetime

LINE = "=" * 56
SECONDS_IN_DAY = 24 * 60 * 60


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


def seconds_of_day(moment):
    return moment.hour * 3600 + moment.minute * 60 + moment.second


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


# Вариант 6
def task_06_1():
    print_title("Вариант 6. Задача 1: текущее время")
    print(f"Текущее время: {format_time(seconds_of_day(now()))}")


def task_06_2():
    print_title("Вариант 6. Задача 2: стоимость звонка")
    start = read_time("Начало звонка (ЧЧ:ММ:СС): ", True)
    if start is None:
        return
    end = read_time("Окончание звонка (ЧЧ:ММ:СС): ", True)
    if end is None:
        return
    price = read_int("Стоимость минуты, коп.: ", 0, 100000)
    if price is None:
        return

    duration = (end - start) % SECONDS_IN_DAY  # звонок мог перейти через полночь
    minutes = (duration + 59) // 60  # неполная минута оплачивается как полная
    cost = minutes * price
    print(f"Длительность звонка: {duration} с")
    print(f"Оплачено минут: {minutes}")
    print(f"Снято со счёта: {cost // 100}.{cost % 100:02} руб.")


def task_06():
    task_06_1()
    task_06_2()


if __name__ == "__main__":
    task_06()
