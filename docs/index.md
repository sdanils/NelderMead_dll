# Введение

Библиотека для решения уравнений методом Нелдера - Мида.

## Ключевые возможности
1. Парсинг инфиксной записи уравнения в дерево выражения.
2. Вычисление значения выражения с определённым вектором переменных.
3. Поиск симплекса, в окрестностях которого существует локальный минимум выражения.

## Классы
- ExpressionTree.
    - Класс для представления и вычисления выражений.
    - Содержит ссылку на корневой узел типа TreeNode.
    - Содержит методы для работы с выражением.
- NelderMeadMethod.
    - Класс для поиска локального минимума.
    - Содержит ссылку объект вырадения и коэффициенты.
    - Содержит методы для работы с алгоритмом.

## Описание класса ExpressionTree
 * brief Класс для представления и вычисления выражений
 * details Содержит ссылку на корень дерева выражения и число переменных в дереве. Так же методы для работы с выражение.
### Поля
  * TreeNode* root;       ///< Корень дерева выражений
  * int number_variable;  ///< Число переменных в дереве выражений
### Закрытые методы 
  ExpressionTree(TreeNode* root_, int number_variable_);
   * brief Конструктор дерева.
   * param root_ Корень дерева
   * param number_variable_ Число переменных в дереве
### Открытые методы. (APi приложения библиотеки)
~ExpressionTree();

   * brief Деструктор дерева
   * details Очищает память с узлами
static ExpressionTree* create_tree(const string function_str);
   * brief Фабричный метод создания обьекта дерева выражения
   * details Преобразует строку выражения, в дерево выражения
   * param function_str Строка представляющаяя выражение
   * warning Выбрасывает исключение std::invalid_argument с сообщение
   * описания ошибки
   * return Ссылку на созданный обьект дерева

double evaluate(const int number_variable, const vector<double>& variables);
   * brief Вычисляет значение дерева выражений
   * details Функция принимает список переменных и вычисляет значение дерева
   * использую переданные переменные. Выбросит исключение.
   * param num_variable Число передаваемых переменных в функцию
   * param variables Указатель на массив переменных. Массив должен быть
   * отсортировон по номерам переменных. (например x1, x2, ..., xn)
   * warning Выбрасывает исключение std::invalid_argument с сообщение описания
   * ошибки
   * return double значение вычислений, результат вычислений
   
bool check_number_variables(int number_variables);
   * brief Проверяет число переменных
   * details Проверяет переданное число на равенство хранящемуся числу
   * переменных в дереве
   * param number_variables Предпологаемое число переменных
   * return Результат проверки

string json_tree();
   * brief Создаёт строку представляющую дерево в формате JSON
   * return Строка с деревом в формате JSON

int get_number_variables();
   * brief Возвращает число переменных в переданном дереве выражения
   * return Число переменных

## Описание класса NelderMeadMethod
 * brief Класс для поиска минимума функции
 * details Выражение функции многих переменных, все коэффициенты метода Нелдера Мида и текущий симплекс
### Поля
  * ExpressionTree* expression_tree;  ///< Объект выражения
  * double reflection;                ///< Коэффициент отражения
  * double expansion;                 ///< Коэффициент растяжения
  * double contraction;               ///< Коэффициент сжатия
  * double homothety;   ///< Коэффициент гомотетии (глобальное сжатие)
  * double dispersion;  ///< Значение дисперсии, для условия остановки
  * vector<vector<double>> simplex;  ///< Текущий симплекс
### Закрытые методы 

void sort_simplex();
   * brief Метод для сортировки вершин симплекса по увеличению значения функции

vector<double> centroid(int exclude_index = -1);
   * brief Вычисляет координаты точки центра тяжести симплекса, без учета передаваемой вершины
   * param exclude_index Индекс вершины симплекса, которую нужно игнорировать
   * return vector<double> координаты центра тяжести

bool check_convergence();
   * brief Выполняет проверку условия остановки алгоритма
   * details Функция вычисляет дисперсию по каждой координате вершин симплекса. Если значения меньше dispersion, возвращает true
   * return true - если дисперсия между координатами вершин меньше заданной

bool step();
   * brief Выполняет шаг алгоритма Нелдера Мида
   * details При не выполнении условия остановки, делает шаг алгоритма, изменяя текущий simplex
   * return true - если выполнено условие остановки
### Открытые методы. (APi приложения библиотеки)
NelderMeadMethod(ExpressionTree* expression_tree_, double reflection_ = 1,
                   double expansion_ = 2, double contraction_ = 0.5,
                   double homothety_ = 0.5, double dispersion_ = 0.0001);
   * brief Конструктор создания обьекта алгоритма
   * details Создает алгоритм и автоматически генерирует симплекс в нулевой
   * точке
   * param expression_tree_ Ссылка на обьект дерева выражения
   * param reflection_ Коэффициент отражения
   * param expansion_ Коэффициент растяжения
   * param contraction_ Коэффициент сжатия
   * param homothety_ Коэффициент гомотетии (глобальное сжатие)
   * param dispersion_ ///< Значение дисперсии, для условия остановки

void generate_simplex(double step, const vector<double>& x0 = {});
   * brief Генерирует симплекс в окрестности точки x0
   * details генерирует симплекс с вершиной в x0. В случае пустого вектора, генерируется симплек в нулевой точки
   * param step Покоординатное растояние между вершинами симплекса
   * param x0 Вектор - вершина или пустой вектор
   * warning Выбрасывает исключение std::invalid_argument с сообщение об ошибки, если вектор принадлежит некорректному пространству

void set_simplex(const vector<vector<double>>& simplex_);
   * brief Задает симплекс алгоритма
   * details Записывает передоваемый симплекс в объект
   * param simplex_ Симплекс
   * warning Выбрасывает исключение std::invalid_argument с сообщение об ошибки, если симплекс имеет некорректную размерность

vector<vector<vector<double>>> minimum_search(int number_steps = 10000);
   * brief Выполняет поиск симплекса, в котором находится локальный минимум.
   * details Выполняет поиск, сохраняя промежуточные симплексы. В случае
   * отсутствия локального минимума, сделает number_steps шагов
   * param number_steps Максимальное число шагов алгоритма
   * return Вектор промежуточных симплексов

# Использование 
1. Экспортируйте библиотеку в проект.
2. Используйте функцию ExpressionTree::create_tree(string), что бы создать дерево выражения. Передоваемая строка должна включать корректное инфиксное выражение с переменными. Переменные записываются в формате "xi". i принимает значения от 1.
3. Результат выражения возвращает функция ExpressionTree::evaluate_tree(...). 
4. В случае возникноения ошибок будет выбрасывается исключение std::invalid_argument с сообщение ошибки.
5. Создайте объет алгоритма Нелдера-Мида NelderMeadMethod(tree)
6. Найдите локальный минимум с NelderMeadMethod::minimum_search()

# Пример на dotnet + SWIG обёртка
```
static void Main(){
            var expression = "3*x1^2*x2+x2^3-3*x1^2-3*x2^2+2";
            var tree = ExpressionTree.create_tree(expression);

            var g = new double[] {1.0, 2.0};
            Console.WriteLine(tree.evaluate( [.. g]));

            var method = new NelderMeadMethod(tree);
            var history = method.minimum_search(80);
            PrintFormatted(history);

            double[][] simplex = new double[][] 
            {
                new double[] {0.1, 2.2},
                new double[] {-0.1, 2.0},
                new double[] {0.0, 1.5}
            };

            DoubleVectorVector vector2D = new DoubleVectorVector();
            foreach (double[] innerArray in simplex)
            {
                DoubleVector innerVector = new DoubleVector(innerArray);
                vector2D.Add(innerVector);
            }

            var method_two= new NelderMeadMethod(tree);
            method_two.set_simplex(vector2D);
            history = method_two.minimum_search(100);
            PrintFormatted(history);
        }

        static void PrintFormatted(DoubleVectorVectorVector data)
        {
            for (int i = 0; i < data.Count; i++)
            {
                Console.WriteLine($"\nIteration {i + 1}:");
                for (int j = 0; j < data[i].Count; j++)
                {
                    Console.Write($"  Vertex {j + 1}: (");
                    for (int k = 0; k < data[i][j].Count; k++)
                    {
                        Console.Write($"{data[i][j][k]:F6}");
                        if (k < data[i][j].Count - 1) Console.Write("; ");
                    }
                    Console.WriteLine(")");
                }
            }
        }
   }
``` 
