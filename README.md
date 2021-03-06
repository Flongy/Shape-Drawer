# Shape-Drawer

## Описание
Приложение для отрисовки простых геометрических фигур на экране, доступные фигуры: прямоугольники, квадраты, эллипсы, круги, полигоны (многоугольники), треугольники.

Является примером программы на C++ с использованием ООП парадигмы.

Для рендера используется OpenGL, в частности, "*fixed-function*" для упрощения отображения фигур на экране.

Управление окном производится через библиотеку [GLFW](https://www.glfw.org/), что допускает компиляцию программы под Linux и MacOS (однако, это не проверялось).

## Компиляция
Для компиляции проекта требуются:
- [conan](https://conan.io/) - пакетный менеджер для C++ (для скачивания GLFW);
- [premake5](https://premake.github.io/) - утилита для генерации файлов автоматизации сборки (Visual Studio, XCode проектов или Makefile конфигурации).

Для генерации проекта Visual Studio достаточно ввести в корневом каталоге репозитория следующие команды:
```
conan install .
premake5 vs2019
```

Также можно обойтись без `conan` и `premake`, но для этого понадобится скачать GLFW (или его [готовые бинарники](https://www.glfw.org/download.html)) и линковать с ним данный проект. Кроме этого, нужно линковать с файлом opengl32.lib, который идёт вместе с операционной системой (или драйверами).

## Возможности
Управление: 
- Цифры на клавиатуре (`1`, `2`) - смена сцены.
- Плюс (`+`) и минус (`-`) - изменение количества фигур (на второй сцене). 
- `Escape` - выход из приложения.

Программа предлагает две сцены:

### 1. Тестовая сцена

![Test Scene](https://user-images.githubusercontent.com/22942979/133000153-a6036ce7-5958-4edf-a0cb-b74d66933534.png)

На этой сцене представлены фиксированные фигуры. Используется для проверки всех функций в программе: корректная отрисовка каждой фигуры, изменение её позиции, цвета и поворота.

### 2. Случайная сцена

![Random Scene](https://user-images.githubusercontent.com/22942979/133000187-392412d6-4c6d-4b39-8905-ea44f875dbf9.png)

На этой сцене генерируются случайные фигуры: случаный размер, случайная позиция, случайный цвет, случайный поворот.

Количество фигур на экране можно изменять клавишами `+` и `-`, также можно сгенерировать новую случайную сцену нажатием на клавишу `2`.

Изначально их по 20 штук для каждого вида фигур. Изменение производится с шагом 10. Минимально возможно 20 фигур (каждого вида), максимально - 1 000.
