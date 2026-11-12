# СПбГУ · Учебные задания

Личный архив учебных материалов и решений по дисциплинам СПбГУ. Здесь можно хранить условия, исходные файлы и варианты решения на разных языках, чтобы их было легко найти и продолжить позже.

## Навигация

- [Как устроен архив](#как-устроен-архив)
- [Текущие материалы](#текущие-материалы)
- [Запуск решений](#запуск-решений)

## Как устроен архив

Каждое задание лежит в отдельной папке в корне проекта. Внутри находятся условие, присланные материалы и решения на нужных языках. Дополнительные уровни папок добавляются только когда они действительно нужны.

```text
SPbGU-tasks/
├── task-01-08-records/
│   ├── assignment.md
│   ├── materials/
│   │   ├── assignment-source.docx
│   │   └── examples.docx
│   ├── python/
│   │   ├── solution.py
│   │   ├── task_01.py
│   │   └── ... task_08.py
│   └── cpp/
│       ├── solution.cpp
│       ├── task_01.cpp
│       └── ... task_08.cpp
├── task-01-15-basics/
│   ├── assignment.md
│   ├── materials/
│   ├── python/
│   └── cpp/
├── task-01-14-loops/
│   ├── assignment.md
│   ├── materials/
│   ├── python/
│   └── cpp/
├── control-06-time/
│   ├── assignment.md
│   ├── python/
│   └── cpp/
├── control-06-coffee-machine/
│   ├── assignment.md
│   ├── python/
│   └── cpp/
├── .gitignore
└── README.md
```

## Текущие материалы

### Программирование · описание объектов

В [условии](task-01-08-records/assignment.md) собраны восемь заданий на хранение и отбор записей: футболисты, манекенщицы, международные компании, зоопарки, мультфильмы, баскетболисты, области и мотоциклы.

- [Решение на Python](task-01-08-records/python/solution.py)
- [Решение на C++](task-01-08-records/cpp/solution.cpp)
- Отдельные решения `task_01`–`task_08` лежат в папках `python/` и `cpp/`.
- Исходное задание: [assignment-source.docx](task-01-08-records/materials/assignment-source.docx)
- [Примеры](task-01-08-records/materials/examples.docx)

### Программирование · линейные программы и ветвление

В [условии](task-01-15-basics/assignment.md) собраны пятнадцать небольших программ: вклады, перевод единиц, сопротивление и ток, площадь кольца, високосный год, квадратное уравнение и скидки. В конце условия перечислено, чем оно отличается от исходного файла.

- [Решение на Python](task-01-15-basics/python/solution.py)
- [Решение на C++](task-01-15-basics/cpp/solution.cpp)
- Отдельные решения `task_01`–`task_15` лежат в папках `python/` и `cpp/`. Файл `solution` открывает меню с выбором задачи.
- Исходное задание: [assignment-source.docx](task-01-15-basics/materials/assignment-source.docx)
- [Пример оформления](task-01-15-basics/materials/examples.docx)

### Программирование · выбор, циклы и таблицы

В [условии](task-01-14-loops/assignment.md) собраны четырнадцать программ: печать фото и заправка, таблицы квадратов, скорости, кредита, температур и степеней двойки, суммы рядов, факториал и обработка последовательностей. В конце условия перечислено, чем оно отличается от исходного файла.

- [Решение на Python](task-01-14-loops/python/solution.py)
- [Решение на C++](task-01-14-loops/cpp/solution.cpp)
- Отдельные решения `task_01`–`task_14` лежат в папках `python/` и `cpp/`. Файл `solution` открывает меню с выбором задачи.
- Исходное задание: [assignment-source.docx](task-01-14-loops/materials/assignment-source.docx)
- [Пример оформления](task-01-14-loops/materials/examples.docx)

### Текущий контроль · класс «Время»

В [условии](control-06-time/assignment.md) нужно описать класс с часами, минутами и секундами и методы добавления секунд и минут с переносом: 65 секунд дают 1 минуту и 5 секунд, после 23:59:59 время идёт с 00:00:00.

- [Решение на Python](control-06-time/python/solution.py)
- [Решение на C++](control-06-time/cpp/solution.cpp)

### Текущий контроль · класс «Кофейный автомат»

В [условии](control-06-coffee-machine/assignment.md) нужно описать кофемашину с запасом воды и зерен и методы заправки, приготовления напитка и проверки остатка. Если ресурсов не хватает, напиток не готовится, а при заправке лишнее сверх объема не добавляется.

- [Решение на Python](control-06-coffee-machine/python/solution.py)
- [Решение на C++](control-06-coffee-machine/cpp/solution.cpp)

## Запуск решений

### Python

Нужен установленный Python 3.

```powershell
python task-01-08-records/python/solution.py
```

Отдельную задачу можно запустить, например, так:

```powershell
python task-01-08-records/python/task_01.py
```

### C++

Для сборки нужен компилятор C++17, например `g++`.

```powershell
g++ -std=c++17 task-01-08-records/cpp/solution.cpp -o solution.exe
./solution.exe
```

Для отдельной задачи укажи ее файл, например `task_01.cpp`, вместо `solution.cpp`.

