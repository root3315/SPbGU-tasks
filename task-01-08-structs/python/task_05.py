from dataclasses import dataclass

LINE = "=" * 56
SEPARATOR = "-" * 56


def print_title(title):
    print(LINE)
    print(title)
    print(LINE)


def print_not_found():
    print("Подходящих записей нет")


# Задача 5. Мультфильмы
@dataclass
class Cartoon:
    title: str
    studio: str
    director_surname: str
    director_name: str
    year: int
    country: str
    budget: float
    revenue: float

    def profit(self):
        return self.revenue - self.budget


def print_cartoon(number, cartoon):
    print(f"Мультфильм #{number}")
    print(f"  Название: {cartoon.title}")
    print(f"  Студия: {cartoon.studio}")
    print(f"  Режиссёр: {cartoon.director_surname} {cartoon.director_name}")
    print(f"  Год выхода: {cartoon.year}")
    print(f"  Страна: {cartoon.country}")
    print(f"  Стоимость: {cartoon.budget:.2f} млн долл.")
    print(f"  Доход: {cartoon.revenue:.2f} млн долл.")
    print(f"  Прибыль: {cartoon.profit():.2f} млн долл.")
    print(SEPARATOR)


def task_05():
    cartoons = [
        Cartoon("Король Лев", "Walt Disney", "Аллерс", "Роджер", 1994, "США", 45, 968.5),
        Cartoon("Шрек", "DreamWorks", "Адамсон", "Эндрю", 2001, "США", 60, 484.4),
        Cartoon("Холодное сердце", "Walt Disney", "Бак", "Крис", 2013, "США", 150, 1280.8),
        Cartoon("Как приручить дракона", "DreamWorks", "Деблуа", "Дин", 2010, "США", 165, 494.9),
    ]

    print_title('Мультфильмы компании "Walt Disney":')
    found = [cartoon for cartoon in cartoons if cartoon.studio == "Walt Disney"]
    for number, cartoon in enumerate(found, 1):
        print_cartoon(number, cartoon)
    if not found:
        print_not_found()


if __name__ == "__main__":
    task_05()
