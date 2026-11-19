# Задача 2. Слияние упорядоченных массивов
NUMBER_LIMIT = 1000000


def read_integers(prompt):
    """Читает целые числа, введённые в одной строке через пробел."""
    return [int(part) for part in input(prompt).split()]


def in_limit(numbers):
    """Проверяет, что все числа не больше NUMBER_LIMIT по модулю."""
    return all(abs(number) <= NUMBER_LIMIT for number in numbers)


def is_sorted(numbers):
    """Проверяет, что числа идут по неубыванию."""
    return all(numbers[i] <= numbers[i + 1] for i in range(len(numbers) - 1))


def merge_sorted(first, second):
    """Сливает два упорядоченных массива в один: каждый раз берём меньший из текущих элементов."""
    result = []
    i = j = 0
    while i < len(first) and j < len(second):
        if first[i] <= second[j]:
            result.append(first[i])
            i += 1
        else:
            result.append(second[j])
            j += 1
    # Один из массивов закончился: дописываем остаток другого
    result.extend(first[i:])
    result.extend(second[j:])
    return result


size = 5

try:
    print("Объединение двух массивов, упорядоченных по возрастанию")
    print("Введите в одной строке элементы первого массива,")
    first = read_integers(f"({size} целых чисел) -> ")
    print("Введите в одной строке элементы второго массива,")
    second = read_integers(f"({size} целых чисел) -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if len(first) != size or len(second) != size:
        print(f"Ошибка! В каждом массиве должно быть {size} чисел")
    elif not (in_limit(first) and in_limit(second)):
        print("Ошибка! Числа должны быть от -1000000 до 1000000")
    elif not (is_sorted(first) and is_sorted(second)):
        print("Ошибка! Массивы должны быть упорядочены по возрастанию")
    else:
        print("----------------------------------------")
        print("Массив - результат", *merge_sorted(first, second))

input("Для завершения нажмите Enter")
