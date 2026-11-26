import calendar
from datetime import date, datetime, timedelta

LINE = "=" * 56
SECONDS_IN_DAY = 24 * 60 * 60
WEEKDAYS = ["понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"]
WEEKDAYS_SHORT = ["пн", "вт", "ср", "чт", "пт", "сб", "вс"]


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


def read_time(prompt, with_seconds):
    value = parse_time(read_text(prompt), with_seconds)
    if value is None:
        print("Ошибка! Нужно время в виде " + ("ЧЧ:ММ:СС" if with_seconds else "ЧЧ:ММ"))
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


# Вариант 1
def task_01_1():
    print_title("Вариант 1. Задача 1: более поздняя из двух дат")
    first = read_date("Первая дата (ДД.ММ.ГГГГ): ")
    if first is None:
        return
    second = read_date("Вторая дата (ДД.ММ.ГГГГ): ")
    if second is None:
        return

    if first > second:
        print(f"Более поздняя дата: {format_date(first)} (первая)")
    elif second > first:
        print(f"Более поздняя дата: {format_date(second)} (вторая)")
    else:
        print("Даты совпадают")


def task_01_2():
    print_title("Вариант 1. Задача 2: контроль батареи ноутбука")
    start = read_datetime("Дата и время включения от батареи (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1900, 2100)
    if start is None:
        return
    declared_hours = read_int("Заявленное время работы от батареи, ч: ", 1, 100)
    if declared_hours is None:
        return

    worked = seconds_between(start, now())
    if worked < 0:
        print("Ошибка! Время включения ещё не наступило")
        return

    print(f"Ноутбук работает от батареи: {worked // 3600} ч {worked % 3600 // 60} мин")
    left = declared_hours * 3600 - worked
    if left > 0:
        print(f"До полного разряда осталось: {left // 60} мин")
    else:
        print("Батарея полностью разряжена")


def task_01():
    task_01_1()
    task_01_2()


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


# Вариант 4
def task_04_1():
    print_title("Вариант 4. Задача 1: время из отдельных значений")
    hours = read_int("Часы (0-23): ", 0, 23)
    if hours is None:
        return
    minutes = read_int("Минуты (0-59): ", 0, 59)
    if minutes is None:
        return
    seconds = read_int("Секунды (0-59): ", 0, 59)
    if seconds is None:
        return
    milliseconds = read_int("Миллисекунды (0-999): ", 0, 999)
    if milliseconds is None:
        return

    total = hours * 3600 + minutes * 60 + seconds
    print(f"Время: {format_time(total)}.{milliseconds:03}")


def task_04_2():
    print_title("Вариант 4. Задача 2: високосный год")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    if calendar.isleap(day.year):
        print(f"{day.year} год високосный")
        return

    leap_year = day.year + 1
    while not calendar.isleap(leap_year):
        leap_year += 1
    print(f"{day.year} год не високосный")
    print(f"Ближайший високосный год: {leap_year}, до него лет: {leap_year - day.year}")


def task_04():
    task_04_1()
    task_04_2()


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


# Вариант 10
def task_10_1():
    print_title("Вариант 10. Задача 1: номер дня недели")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    print(f"День недели: {weekday_text(day)}")


def task_10_2():
    print_title("Вариант 10. Задача 2: дни до дня рождения")
    birth = read_date("Дата рождения (ДД.ММ.ГГГГ): ", 1900, 2100)
    if birth is None:
        return

    today = now().date()
    if birth > today:
        print("Ошибка! Дата рождения ещё не наступила")
        return

    birthday = same_day_in_year(birth, today.year)
    if birthday == today:
        print("День рождения сегодня!")
    elif birthday > today:
        print(f"До дня рождения осталось дней: {(birthday - today).days}")
    else:
        print(f"День рождения в этом году уже прошёл, прошло дней: {(today - birthday).days}")


def task_10():
    task_10_1()
    task_10_2()


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


# Вариант 12
def task_12_1():
    print_title("Вариант 12. Задача 1: форматирование даты")
    day = read_date("Дата (ДД.ММ.ГГГГ): ")
    if day is None:
        return

    print(f"День (01-31): {day.day:02}")
    print(f"День недели (пн-вс): {WEEKDAYS_SHORT[day.isoweekday() - 1]}")
    print(f"Месяц (01-12): {day.month:02}")
    print(f"Год (0000-9999): {day.year:04}")


def task_12_2():
    print_title("Вариант 12. Задача 2: минута года исторического события")
    event = read_datetime("Дата и время события (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1, 9999)
    if event is None:
        return

    year_start = datetime(event.year, 1, 1)
    minute = seconds_between(year_start, event) // 60 + 1
    print(f"Событие произошло на {minute}-й минуте от начала года")
    print(f"День недели: {weekday_text(event.date())}")


def task_12():
    task_12_1()
    task_12_2()


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


TASKS = {
    "1": ("Поздняя дата, батарея ноутбука", task_01),
    "2": ("Текущие дата и время, пакет связи", task_02),
    "3": ("Время без нулей, срок давности", task_03),
    "4": ("Время из частей, високосный год", task_04),
    "5": ("Проверка даты, расписание процедур", task_05),
    "6": ("Текущее время, стоимость звонка", task_06),
    "7": ("Части даты, срок годности", task_07),
    "8": ("Текущая дата, телепередача", task_08),
    "9": ("Проверка времени, посудомойка", task_09),
    "10": ("День недели, день рождения", task_10),
    "11": ("Секунды между временами, вокзал", task_11),
    "12": ("Формат даты, минута года", task_12),
    "13": ("Время с нулями, выборы", task_13),
    "14": ("Минуты между временами, праздник", task_14),
}


def main():
    while True:
        print("\n" + "=" * 45)
        for number, (title, _) in TASKS.items():
            print(f"{number:>2}. {title}")
        print(" 0. Выход")
        print("=" * 45)

        choice = input("Номер варианта -> ").strip()
        if choice == "0":
            break

        print()
        if choice in TASKS:
            TASKS[choice][1]()
        else:
            print("Нет такого варианта")


if __name__ == "__main__":
    try:
        main()
    except EOFError:
        pass  # ввод закрыт: просто завершаем программу
