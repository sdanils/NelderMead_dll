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

- Response<T>.
    - Класс для представляет ответ экспонируемых функций(Api)
    - Содержит значение ответа и строку - статус ответа.
 
На данном этапе классы представляющие элементы дерева не доступны к эспортированию и не будут описаны.
## Функции
* Response<ExpressionTree*>* create_tree(const char* function_str);
    * @brief Создает дерево выражений из строки
    * @param function_str Строка с математическим выражением в инфиксной записи.
    * Переменные в выражении должны быть представлены в формате "xi". i принимает
    * значения от 1 (например, "x1 * (x3 - x2)")
    * @return Указатель объект Response, содержащий ссылка на созданныое дерево
    * @warning Строка должна содержать корректное математическое выражение
    * @warning После использования дерева нужно вызвать delete_tree для очистки
    * памяти. В ином случае память будет утеряна
    * @ingroup CoreAPI


* void delete_tree(ExpressionTree* tree);
    * @brief Очищает память выделенную под дерево выражения
    * @details Очищает обьект дерева, переданный в качестве параметра. Используется
    * после использования дерева
    * @warning Память занятую при вызове метода create_tree(...) обязательно нужно
    * очистить данным методом. Иначе произойдет утечка.
    * @warning Некоторые библиотеки используемы для импорта функций могут
    * самостоятельно очищать память. В этом случае очистка памяти через функцию
    * вызовет исклюяение.
    * @param tree Указатель на обьект очистки
    * @ingroup CoreAPI
 

* int get_number_variable(ExpressionTree* trее);
    * @brief Возвращает число переменных в переданном дереве выражения
    * @param tree Указатель на обьект выражения
    * @ingroup CoreAPI


* Response<double>* evaluate_tree(ExpressionTree* trее,
                                              const int number_variable,
                                              const double* variables);
    * @brief Вычисляет значение дерева выражений
    * @details Функция принимает ссылку на валидное дерево, число переменных и
    * вектор значений. В случае несоответствия числа переменных возвращает 0.
    * @param tree Указатель на валидное дерево выражений
    * @param num_variable Число передаваемых переменных в функцию
    * @param variables Указатель на массив переменных. Массив должен быть
    * отсортировон по номерам переменных. (например x1, x2, ..., xn)
    * @return Ссылку на объект Response, содержащий результат вычислений
    * @ingroup CoreAPI

* char* print_tree(ExpressionTree* trее);
    * @brief Создает строку в формате JSON, содержащую дерево выражения из обьекта
    * tree.
    * @param tree Указатель на валидное дерево выражений
    * @return Строка, результат парсинга
    * @ingroup CoreAPI

* void delete_string(char* tree_str);
    * @brief Очищает память со строкой, содержащей дерево выражения из обьекта
    * tree.
    * @details Очищает любую строку переданную в качестве параметра. Используется
    * после вызова метода print_tree() для очистки занятой памяти
    * @warning Память занятую при вызове метода print_tree() обязательно нужно
    * очистить данным методом. Иначе произойдет утечка.
    * @warning Некоторые библиотеки используемы для импорта функций могут
    * самостоятельно очищать память. В этом случае очистка памяти через функцию
    * вызовет исклюяение.
    * @param tree_str Указатель на строку
    * @ingroup CoreAPI

* double get_value_evaluate(Response<double>* obj);
    * @brief Возвращает значение из объекта ответа evaluate_tree()
    * @details Автоматически удаляет обьект ответа
    * @warning После вызова функции удалять обьект нельзя. Данный процесс остановит
    * программу
    * @param obj Ссылка на объект ответа Response<double>
    * @return Значение вычисления дерева

* char* get_error_evaluate(Response<double>* obj);
    * @brief Возвращает строку статуса из объекта ответа evaluate_tree()
    * @param obj Ссылка на объект ответа Response<double>*
    * @return Строка статуса вычисления

* bool has_error_evaluate(Response<double>* obj);
    * @brief Проверяет статус выполнения evaluate_tree()
    * @param obj Ссылка на объект ответа Response<double>*
    * @return true если при вычислениях произошла ошибка, false иначе

* void delete_response_evaluate(Response<double>* obj);
    * @brief Удаляет обьект ответа
    * @param obj Ссылка на объект ответа Response<double>*

* ExpressionTree* get_value_tree(Response<ExpressionTree*>* obj);
    * @brief Возвращает значение из объекта ответа create_tree()
    * @details Автоматически удаляет обьект ответа
    * @warning После вызова функции удалять обьект нельзя. Данный процесс остановит
    * программу
    * @param obj Ссылка на объект ответа Response<ExpressionTree*>
    * @return Ссылку на обьект дерева ExpressionTree*

* char* get_error_tree(Response<ExpressionTree*>* obj);
    * @brief Возвращает строку статуса из объекта ответа create_tree()
    * @param obj Ссылка на объект ответа Response<ExpressionTree*>*
    * @return Строка статуса построения

* bool has_error_tree(Response<ExpressionTree*>* obj);
    * @brief Проверяет статус выполнения create_tree()
    * @param obj Ссылка на объект ответа Response<ExpressionTree*>*
    * @return true если при построении произошла ошибка, false иначе

* void delete_response_tree(Response<ExpressionTree*>* obj);
    * @brief Удаляет обьект ответа
    * @param obj Ссылка на объект ответа Response<ExpressionTree*>*

# Использование 
1. Экспортируйте библиотеку в проект.
2. Используйте функцию create_tree(string), что бы создать дерево выражения. Передоваемая строка должна включать корректное инфиксное выражение с переменными. Переменные записываются в формате "xi". i принимает значения от 1.
3. Для проверки ответа create_tree() используйте функцию has_error_tree(). 
    1. Если результат положительный, объект ответа будет содержать пустой указатель и строку с описание ошибки. Удалите ответ с помошью функции delete_response_tree().
    2. Если ответ отрицательный, используйте get_value_tree() чтобы получить ссылку на объект дерева.
4. Результат выражения возвращает функция evaluate_tree(). 
5. Так же как и для ответа create_tree(), проверьте результат ответа функциями  has_error_evaluate().
6. Получите значение выражения используя get_value_evaluate().
7. Очистите память. Некоторые библиотеки для импорта делают это автоматически. Если используете библиотеку без данной фичи вызывайте функции delete_tree() и delete_string(). Для очистки строк используйте delete_string()

# Пример на Python
```python
import ctypes as c

dll = c.CDLL('test_NelderMead/libNelderMead.so')

dll.create_tree.argtypes = [c.c_char_p]
dll.create_tree.restype = c.c_void_p

dll.evaluate_tree.argtypes = [c.c_void_p]
dll.evaluate_tree.restype = c.c_void_p

dll.print_tree.argtypes = [c.c_void_p]
dll.print_tree.restype = c.c_void_p

dll.delete_tree.argtypes = [c.c_void_p]
dll.delete_tree.restype = None

dll.delete_string.argtypes = [c.c_void_p]
dll.delete_string.restype = None

dll.get_value_evaluate.argtypes = [c.c_void_p]
dll.get_value_evaluate.restype = c.c_double

dll.get_error_evaluate.argtypes = [c.c_void_p]
dll.get_error_evaluate.restype = c.c_void_p

dll.has_error_evaluate.argtypes = [c.c_void_p]
dll.has_error_evaluate.restype = c.c_bool

dll.delete_response_evaluate.argtypes = [c.c_void_p]
dll.delete_response_evaluate.restype = None

dll.get_value_tree.argtypes = [c.c_void_p]
dll.get_value_tree.restype = c.c_void_p

dll.get_error_tree.argtypes = [c.c_void_p]
dll.get_error_tree.restype = c.c_void_p

dll.has_error_tree.argtypes = [c.c_void_p]
dll.has_error_tree.restype = c.c_bool

dll.delete_response_tree.argtypes = [c.c_void_p]
dll.delete_response_tree.restype = None

if __name__ == "__main__":

    expr = "x1*(x2+x1)-18/(9*(2^x2))"
    expr_bytes = expr.encode('utf-8')
    response = dll.create_tree(expr_bytes)

    if dll.has_error_tree(response):
        result_bytes_error = dll.get_error_tree(response)
        result_str = c.cast(result_bytes_error, c.c_char_p).value.decode('utf-8')
        print(result_str)
        dll.delete_string(result_bytes_error)
    else:
        tree_ptr = dll.get_value_tree(response)
        result_bytes = dll.print_tree(tree_ptr)
        result_str = c.cast(result_bytes, c.c_char_p).value.decode('utf-8')
        print("Tree: " + result_str)
        dll.delete_string(result_bytes)

    variables = [3, 1]
    num_v = len(variables)
    c_array = (c.c_double * num_v)(*variables)

    #Неверный ввод
    response = dll.evaluate_tree(tree_ptr, num_v + 1, c_array)
    if dll.has_error_evaluate(response):
        result_bytes_error = dll.get_error_evaluate(response)
        result_str = c.cast(result_bytes_error, c.c_char_p).value.decode('utf-8')
        print(result_str)
        dll.delete_string(result_bytes_error)
    else:
        result = dll.get_value_evaluate(response)
        print(result)

    #Верный ввод
    response = dll.evaluate_tree(tree_ptr, num_v, c_array)
    if dll.has_error_evaluate(response):
        result_bytes_error = dll.get_error_evaluate(response)
        result_str = c.cast(result_bytes_error, c.c_char_p).value.decode('utf-8')
        print(result_str)
        dll.delete_string(result_bytes_error)
    else:
        result = dll.get_value_evaluate(response)
        print(result)
```
