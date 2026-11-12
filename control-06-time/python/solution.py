# Текущий контроль. Задание 6: класс «Время»

SECONDS_IN_MINUTE = 60
MINUTES_IN_HOUR = 60
HOURS_IN_DAY = 24


class Time:
    def __init__(self, hours=0, minutes=0, seconds=0):
        if not (0 <= hours < HOURS_IN_DAY
                and 0 <= minutes < MINUTES_IN_HOUR
                and 0 <= seconds < SECONDS_IN_MINUTE):
            raise ValueError("время вне допустимого диапазона")
        self.hours = hours
        self.minutes = minutes
        self.seconds = seconds

    def add_seconds(self, amount):
        total = self.seconds + amount
        self.seconds = total % SECONDS_IN_MINUTE
        # Лишние секунды переходят в минуты: 65 секунд = 1 минута и 5 секунд
        self.add_minutes(total // SECONDS_IN_MINUTE)

    def add_minutes(self, amount):
        total = self.minutes + amount
        self.minutes = total % MINUTES_IN_HOUR
        self.add_hours(total // MINUTES_IN_HOUR)

    def add_hours(self, amount):
        self.hours = (self.hours + amount) % HOURS_IN_DAY

    def __str__(self):
        return f"{self.hours:02}:{self.minutes:02}:{self.seconds:02}"


def read_start_time():
    print("Начальное время")
    hours = int(input("Часы –> "))
    minutes = int(input("Минуты –> "))
    seconds = int(input("Секунды –> "))
    return Time(hours, minutes, seconds)


def main():
    try:
        time = read_start_time()
    except ValueError:
        print("Ошибка! Неверное время")
        return

    print(f"Время: {time}")

    actions = {
        "1": ("Сколько секунд –> ", time.add_seconds),
        "2": ("Сколько минут –> ", time.add_minutes),
    }

    while True:
        print("-----------------------------")
        print("1 – Добавить секунды")
        print("2 – Добавить минуты")
        print("0 – Выход")
        choice = input("Ваш выбор –> ").strip()

        if choice == "0":
            break
        if choice not in actions:
            print("Ошибка! Неверный выбор")
            continue

        prompt, add = actions[choice]
        try:
            amount = int(input(prompt))
        except ValueError:
            print("Ошибка! Неверный формат числа")
            continue

        add(amount)
        print(f"Время: {time}")


if __name__ == "__main__":
    main()
