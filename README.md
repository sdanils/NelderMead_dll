# NelderMead_dll
Проект динамической библиотеки с методом Нелдера-Мида. Собрать библиотеку возможно на любой системе. 

31.03.2025
Проект содержит реализацию динамической библиотеки NelderMead с функциями:
1. Парсинга арефмитического выражения. Строка типа C с инфиксной записью преобразовывается в дерево выражения.
2. Вычисления выражения. Выражение считается с учетом переданного вектора значений переменных.

# Инструкции
## Сборка проекта.
Для сборки библиотеки используется cmake.
1. Создайте папку для сборки. ```mkdir build```
2. Перейдите в неё. ```cd build  ```        
3. Сгенерируйте файлы сборки. ```cmake ..```
4. Запустите сборку. ```cmake --build .```

## Сборка документации.
Для сборки документации используется doxygen совместно с graphviz (пакеты необходимо установить).
1. Перейдите в папку проекта
2. Запустите сборку. ```doxygen Doxyfile```

Файлы документации появятся в папке docs/html. Запустит index.html для просмотра.
