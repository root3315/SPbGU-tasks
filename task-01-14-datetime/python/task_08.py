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


def format_date(day):
    return f"{day.day:02}.{day.month:02}.{day.year:04}"


def format_time(seconds):
    return f"{seconds // 3600:02}:{seconds % 3600 // 60:02}:{seconds % 60:02}"


# Вариант 8
def task_08_1():
    print_title("Вариант 8. Задача 1: текущая дата")
    print(f"Сегодня: {format_date(now().date())}")


def task_08_2():
    print_title("Вариант 8. Задача 2: расчёт телепередачи")
    start = read_time("Начало эфира (ЧЧ:ММ:СС): ", True)
    if start is None:
        return
    duration = read_int("Продолжительность, с: ", 1, SECONDS_IN_DAY)
    if duration is None:
        return

    end = start + duration
    line = f"Окончание: {format_time(end % SECONDS_IN_DAY)}"
    if end >= SECONDS_IN_DAY:
        line += " (на следующий день)"
    print(line)
    print(f"Продолжительность: {duration // 60} мин {duration % 60} с")
    # пауза ставится после каждых полных 5 минут, но не в самом конце передачи
    print(f"Рекламных пауз: {(duration - 1) // 300}")


def task_08():
    task_08_1()
    task_08_2()


if __name__ == "__main__":
    task_08()
