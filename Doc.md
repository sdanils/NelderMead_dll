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

- double evaluate_tree(ExpressionTree* tree).
    - Вычисляет значение выражения, хранящегося в в дереве.
    - Возвращает результат выражения.
    - Принимает указатель на дерево выражения.
- ExpressionTree* create_tree(const char* function_str).
    - Создает дерево выражения из строки в инфиксной записи.
    - Возвращает ссылку на созданный объект дерева.
    - Принимает строку типу С с инфиксным выражением.
- void create_solution(const int num_variable, const double* variables);
    - Сохраняет вектор переменных в статическую память для вычисления выражения.
    - Возвращает void. Операция всегда выполняетс успешно.
    - Принимает число переменных в дереве(num_variable) и вектор double в формете С массива. 

# Использование 
1. Экспортируйте библиотеку в проект.
2. Используйте функцию create_tree(string), что бы создать дерево выражения. <BIG>Передоваемая строка должна включать корректное инфиксное выражение с переменными. Переменные записываются в формате "x{i}". i принимает значения от 1. </BIG>  
3. Для задания вектора переменных используется функция create_solution(int, double*). 
4. Результат выражения возвращает функция evaluate_tree(ExpressionTree* tree).

<BIG>При вычислении выражения, используются переменные сохранённые функцией create_solution(). Если она не была вызвана, вычисление невозможно.</BIG>

# Пример на Python
```python
import ctypes as c

culc_dll = c.CDLL('lib/NelderMead.dll')

culc_dll.create_tree.argtypes = [c.c_char_p]
culc_dll.create_tree.restype = c.c_void_p

culc_dll.evaluate_tree.argtypes = [c.c_void_p]
culc_dll.evaluate_tree.restype = c.c_double

culc_dll.create_solution.argtypes = [c.c_int, c.POINTER(c.c_double)]
culc_dll.create_solution.restype = None

expr = "x1^2/2-9/x2 * ((2 + x3)*x4)"
expr_bytes = expr.encode('utf-8')
tree_ptr = culc_dll.create_tree(expr_bytes)

variables = [0.123213, 4, 3, 0.10]
num_v = len(variables)
c_array = (c.c_double * num_v)(*variables)
culc_dll.create_solution(num_v, c_array)

print(culc_dll.evaluate_tree(tree_ptr))
```

