# Введение

Библиотека для решения уравнений методом Нелдера - Мида.

## Ключевые возможности
1. Парсинг инфиксной записи уравнения в дерево выражения.
2. Вычисление значения выражения с определённым вектором переменных.

# Описание API
## Классы
- ExpressionTree.
    - Класс для представления и вычисления выражений.
    - Содержащий ссылку на корневой узел типа TreeNode.
    - Включает метод evaluate() для вычисления хранящегося выражения.

<big>На данном этапе классы представляющие элементы дерева не доступны к эспортированию и не будут описаны.</big>
## Функции

- double evaluate_tree(ExpressionTree* tree, const int number_variable,
                                   const double* variables)
    - Вычисляет значение выражения, хранящегося в в дереве.
    - Возвращает результат выражения.
    - Принимает указатель на дерево выражения, число перевенных и вектор значений.
    - Выбросит исключение в случае исключения.
- ExpressionTree* create_tree(const char* function_str)
    - Создает дерево выражения из строки в инфиксной записи.
    - Возвращает ссылку на созданный объект дерева.
    - Принимает строку типу С с инфиксным выражением.
- char* print_tree(ExpressionTree* trее)
    - Создает строку в формате JSON, содержащую дерева выражения из обьекта tree.
    - Возвращает строку - результат парсинга.
    - Принимает указатель на валидное дерево выражений.
- void delete_string(char* tree_str)
    - Очищает память со строкой, содержащей дерево выражения из обьекта tree.
    - Принимает указатель на строку.
- void delete_tree(ExpressionTree* tree)
    - Очищает память выделенную под дерево выражения.
    - Указатель на обьект очистки.
- int get_number_variable(ExpressionTree* tree)
    - Возвращает число переменных в дереве.
    - Указатель на обьект выражения.


# Использование 
1. Экспортируйте библиотеку в проект.
2. Используйте функцию create_tree(string), что бы создать дерево выражения. <BIG>Передоваемая строка должна включать корректное инфиксное выражение с переменными. Переменные записываются в формате "xi". i принимает значения от 1. </BIG>  
3. Результат выражения возвращает функция evaluate_tree(ExpressionTree* tree, const int number_variable,
                                   const double* variables).
4. После использования дерева выражения память должна бытиь очищена. Некоторые библиотеки для импорта делают это автоматически. Если используете библиотеку без данной фичи вызывайте функции delete_tree() и delete_string().

# Пример на Python
```python
import ctypes as c

culc_dll = c.CDLL('lib/NelderMead.dll')

culc_dll.create_tree.argtypes = [c.c_char_p]
culc_dll.create_tree.restype = c.c_void_p

culc_dll.evaluate_tree.argtypes = [c.c_void_p]
culc_dll.evaluate_tree.restype = c.c_double

culc_dll.print_tree.argtypes = [c.c_void_p]
culc_dll.print_tree.restype = c.c_void_p

culc_dll.delete_tree.argtypes = [c.c_void_p]
culc_dll.delete_tree.restype = None

culc_dll.delete_string.argtypes = [c.c_void_p]
culc_dll.delete_string.restype = None

expr = "x1*x2^x3+4"
expr_bytes = expr.encode('utf-8')
tree_ptr = culc_dll.create_tree(expr_bytes)

variables = [2, 3, 2]
num_v = len(variables)
c_array = (c.c_double * num_v)(*variables)

print(culc_dll.evaluate_tree(tree_ptr, num_v, c_array))

result_bytes = culc_dll.print_tree(tree_ptr)
result_str = c.cast(result_bytes, c.c_char_p).value.decode('utf-8')

print(result_str)
culc_dll.delete_string(result_bytes)
culc_dll.delete_tree(tree_ptr)
```

# UML дерева выражения
![UML диаграмма классов выражения](../uml.png)