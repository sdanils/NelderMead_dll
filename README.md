# NelderMead_dll
Проект динамической библиотеки с методом Нелдера-Мида. Собрать библиотеку возможно на любой системе. 

31.03.2025
Проект содержит реализацию динамической библиотеки NelderMead с функциями:
1. Парсинга арефмитического выражения. Строка типа C с инфиксной записью преобразовывается в дерево выражения.
2. Вычисления выражения. Выражение считается с учетом переданного вектора значений переменных.

Проет разделен на две части: wrapper_cli и dll. 
## DLL
Папка dll сожержит проект собирающийся в dll, с экспортом класса ExpressionTree. Он собирается для использования в С++ или написание аддонов для других языков и библиотек.
Папка wrapper_cli содержит проект обёртки классов для c# с использованием C++/CLI. Он собирается для простого использования в C#.

# Инструкции
## Сборка проекта.
Для сборки библиотеки dll используется cmake.
1. Зайдите в папку dll.
1. Создайте папку для сборки. ```mkdir build```
2. Перейдите в неё. ```cd build  ```        
3. Сгенерируйте файлы сборки. ```cmake ..```
4. Запустите сборку. ```cmake --build .```

Для сборки обёртки С++/CLI используется cmake с Visual Studio 16 2019(и выше) с MSVC последней версии и установленным дополнением C++/CLI. Все необходимое устанавливается через VS installer.
1. Зайдите в папку wrapper_dll.
2. Измените фаил wrapper_cli/CMakeLists.txt: Нужно указать ссылку на заголовочные файлы .NET. Пример ```target_include_directoriesNelderMid_cli PUBLIC "../dll/include" "C:/Program Files (x86)/Reference Assemblies/Microsoft/Framework/.NETFramework/v4.8``` 
3. Создайте папку для сборки. ```mkdir build```
4. Перейдите в неё. ```cd build  ```        
5. Сгенерируйте файлы сборки. ```cmake ..```
6. Запустите сборку. ```cmake --build .```

## Сборка документации.
Для сборки документации используется doxygen совместно с graphviz (пакеты необходимо установить).
1. Перейдите в папку проекта
2. Запустите сборку. ```doxygen Doxyfile```

Файлы документации появятся в папке docs/html. Запустит index.html для просмотра.

## Пример использования
Как начать использовать обёртку c++/cli в проекте dotnet.
1. Соберите wrapper_cli
2. Создайте проект dotnet и добавьте в файл проекта строчки: ``` <ItemGroup>
    <Reference Include="NelderMidCliLibrary">
        <HintPath>..\NelderMead_dll\wrapper_cli\build\Debug\NelderMid_cli.dll</HintPath>
    </Reference>
    <Content Include="..\NelderMead_dll\wrapper_cli\build\Debug\NelderMid_lib.dll">
        <CopyToOutputDirectory>Always</CopyToOutputDirectory>
    </Content>
    <Content Include="..\NelderMead_dll\wrapper_cli\build\Debug\NelderMid_lib.pdb">
        <CopyToOutputDirectory>Always</CopyToOutputDirectory>
    </Content>
</ItemGroup> ``` Это импортирует библиотеку в проект dotnet.
3. Измените пути до файлов в соответствии с вашей конфигурацией.
4. Соберите проект.
5. В коде подключите пространство имён ```using NelderMidDll;```  
6. Используйте обьекты dll как управляемые dotnet.

Код на C#: 
``` 
using NelderMidDll;

class Program
{
    static void Main()
    {
        var obj = new WExpressionTree("x1 + x2 * (x2 - x3)");
        Console.WriteLine(obj.Evaluate(3, new List<double> { 1, 2, 2 }));
        Console.WriteLine(obj.GetJsonTree());
    }
}
```