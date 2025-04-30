# C++/CLI
Проект содержит обёртку с++/cli классов dll для .NET

# Инструкции
## Сборка проекта.

Для сборки обёртки С++/CLI используется cmake с Visual Studio 16 2019(и выше) с MSVC последней версии и установленным дополнением C++/CLI. Все необходимое устанавливается через VS installer.

1. Зайдите в папку wrapper_dll.
2. Измените фаил wrapper_cli/CMakeLists.txt: Нужно указать ссылку на заголовочные файлы .NET. Пример ```target_include_directoriesNelderMid_cli PUBLIC "../dll/include" "C:/Program Files (x86)/Reference Assemblies/Microsoft/Framework/.NETFramework/v4.8``` 
3. Создайте папку для сборки. ```mkdir build```
4. Перейдите в неё. ```cd build  ```        
5. Сгенерируйте файлы сборки. ```cmake ..```
6. Запустите сборку. ```cmake --build .```


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
        try
        {
            var obj = new WExpressionTree("x1  x2");
            Console.WriteLine(obj.Evaluate(new List<double> { 4, 7 }));
            Console.WriteLine(obj.GetJsonTree());
        }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.Message);
        }
        var obj2 = new WExpressionTree("x1 + x2 * (12 + 2 - x3)");
        try
        {
            Console.WriteLine(obj2.Evaluate(new List<double> { 4, 7, 2 }));
            Console.WriteLine(obj2.GetJsonTree());
        }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.Message);
        }
    }
}
```
