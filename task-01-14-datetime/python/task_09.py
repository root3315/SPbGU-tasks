from datetime import datetime, timedelta

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


def seconds_of_day(moment):
    return moment.hour * 3600 + moment.minute * 60 + moment.second


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


def format_datetime(moment):
    return f"{format_date(moment.date())} {format_time(seconds_of_day(moment))}"


# Вариант 9
def task_09_1():
    print_title("Вариант 9. Задача 1: проверка значения на время")
    text = read_text("Значение: ")
    if parse_time(text, True) is None and parse_time(text, False) is None:
        print(f'"{text}" не является временем вида ЧЧ:ММ или ЧЧ:ММ:СС')
    else:
        print(f'"{text}" является временем')


def task_09_2():
    print_title("Вариант 9. Задача 2: отложенный запуск посудомоечной машины")
    wash_minutes = read_int("Длительность мойки, мин: ", 1, 1440)
    if wash_minutes is None:
        return
    delay_hours = read_int("Отсрочка запуска, ч: ", 0, 24)
    if delay_hours is None:
        return

    pressed = now()
    start = pressed + timedelta(hours=delay_hours)
    end = start + timedelta(minutes=wash_minutes)
    print(f"Кнопка «Пуск» нажата: {format_datetime(pressed)}")
    print(f"Начало мойки: {format_datetime(start)}")
    print(f"Окончание мойки: {format_datetime(end)}")


def task_09():
    task_09_1()
    task_09_2()


if __name__ == "__main__":
    task_09()
