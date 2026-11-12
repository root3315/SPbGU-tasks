# Текущий контроль. Задание 6: класс «Кофейный автомат»

WATER_CAPACITY = 2000  # мл
BEANS_CAPACITY = 500   # г

# Название, вода (мл), зерна (г)
DRINKS = [
    ("Эспрессо", 30, 9),
    ("Двойной эспрессо", 60, 18),
    ("Американо", 150, 9),
]


class CoffeeMachine:
    def __init__(self, water_capacity, beans_capacity):
        self.water_capacity = water_capacity
        self.beans_capacity = beans_capacity
        self.water = water_capacity
        self.beans = beans_capacity

    def refill_water(self, amount):
        """Доливает воду, но не больше объема бака. Возвращает, сколько долито."""
        added = min(amount, self.water_capacity - self.water)
        self.water += added
        return added

    def refill_beans(self, amount):
        """Досыпает зерна, но не больше объема контейнера. Возвращает, сколько добавлено."""
        added = min(amount, self.beans_capacity - self.beans)
        self.beans += added
        return added

    def missing_for(self, water, beans):
        """Список ресурсов, которых не хватает на напиток."""
        missing = []
        if self.water < water:
            missing.append("воды")
        if self.beans < beans:
            missing.append("зерен")
        return missing

    def make_drink(self, water, beans):
        """Готовит напиток, если хватает ресурсов. Возвращает True при успехе."""
        if self.missing_for(water, beans):
            return False
        self.water -= water
        self.beans -= beans
        return True

    def remaining(self):
        return (f"Вода: {self.water} из {self.water_capacity} мл\n"
                f"Зерна: {self.beans} из {self.beans_capacity} г")


def make_drink_menu(machine):
    print("Напиток:")
    for number, (name, water, beans) in enumerate(DRINKS, start=1):
        print(f"{number} – {name} ({water} мл, {beans} г)")

    try:
        choice = int(input("Ваш выбор –> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
        return

    if not 1 <= choice <= len(DRINKS):
        print("Ошибка! Неверный выбор напитка")
        return

    name, water, beans = DRINKS[choice - 1]
    missing = machine.missing_for(water, beans)
    if missing:
        print(f"Не хватает {' и '.join(missing)}, заправьте автомат")
    else:
        machine.make_drink(water, beans)
        print(f"Готово: {name}")
    print(machine.remaining())


def refill_menu(machine):
    try:
        water = int(input("Сколько воды долить, мл –> "))
        beans = int(input("Сколько зерен досыпать, г –> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
        return

    if water < 0 or beans < 0:
        print("Ошибка! Количество не может быть отрицательным")
        return

    added_water = machine.refill_water(water)
    added_beans = machine.refill_beans(beans)
    print(f"Долито воды: {added_water} мл, досыпано зерен: {added_beans} г")
    print(machine.remaining())


def main():
    machine = CoffeeMachine(WATER_CAPACITY, BEANS_CAPACITY)
    print("Кофейный автомат")

    while True:
        print("-----------------------------")
        print("1 – Приготовить напиток")
        print("2 – Заправить")
        print("3 – Остаток")
        print("0 – Выход")
        choice = input("Ваш выбор –> ").strip()

        if choice == "0":
            break
        elif choice == "1":
            make_drink_menu(machine)
        elif choice == "2":
            refill_menu(machine)
        elif choice == "3":
            print(machine.remaining())
        else:
            print("Ошибка! Неверный выбор")


if __name__ == "__main__":
    main()
