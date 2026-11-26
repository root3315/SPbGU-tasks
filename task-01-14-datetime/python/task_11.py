from datetime import datetime

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


def read_time(prompt, with_seconds):
    value = parse_time(read_text(prompt), with_seconds)
    if value is None:
        print("Ошибка! Нужно время в виде " + ("ЧЧ:ММ:СС" if with_seconds else "ЧЧ:ММ"))
    return value


def seconds_of_day(moment):
    return moment.hour * 3600 + moment.minute * 60 + moment.second


# Вариант 11
def task_11_1():
    print_title("Вариант 11. Задача 1: секунды между двумя значениями времени")
    first = read_time("Первое время (ЧЧ:ММ:СС): ", True)
    if first is None:
        return
    second = read_time("Второе время (ЧЧ:ММ:СС): ", True)
    if second is None:
        return

    print(f"Между ними секунд: {abs(second - first)}")


def task_11_2():
    print_title("Вариант 11. Задача 2: бегущая строка вокзала")
    direction = read_text("Направление поезда: ")
    if not direction:
        print("Ошибка! Направление не может быть пустым")
        return
    departure = read_time("Время отправления (ЧЧ:ММ): ", False)
    if departure is None:
        return
    platform = read_int("Номер платформы: ", 1, 99)
    if platform is None:
        return
    track = read_int("Номер пути: ", 1, 99)
    if track is None:
        return

    # если время отправления уже прошло, поезд уходит завтра
    current_minute = seconds_of_day(now()) // 60
    minutes_left = (departure // 60 - current_minute) % (24 * 60)
    print(f"«Поезд следованием {direction} отправляется от {platform} платформы "
          f"{track} пути через {minutes_left} мин»")


def task_11():
    task_11_1()
    task_11_2()


if __name__ == "__main__":
    task_11()
