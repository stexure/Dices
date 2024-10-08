# Dices

1. Абстрактный класс AbstractDice предоставляет базовый интерфейс для кубиков. Он содержит чисто виртуальный метод roll(), который должен быть реализован в любом классе-наследнике. Благодаря этому обеспечивается возможность полиморфной работы с разными типами кубиков (например, обычным кубиком или набором из нескольких кубиков).

Класс Dice представляет стандартный кубик с заданным количеством граней (max). Для генерации случайных чисел используется библиотека <random>. Метод roll() возвращает случайное число в диапазоне от 1 до max.

Класс ThreeDicePool описывает набор из трёх кубиков. В его конструкторе принимаются объекты, которые реализуют интерфейс AbstractDice (например, три объекта Dice). Метод roll() возвращает сумму результатов бросков этих трёх кубиков.

Функция expected_value() вычисляет математическое ожидание для любого объекта, который реализует метод roll(). В неё можно передать объект типа AbstractDice, что позволяет применять функцию как для одного кубика, так и для нескольких кубиков, таких как ThreeDicePool.

Главная функция main() показывает, как используются классы и функция для вычисления математического ожидания. Сначала создаются три кубика с различными начальными значениями генераторов случайных чисел. Затем эти кубики передаются в объект ThreeDicePool, который бросает их и вычисляет сумму результатов.

2. Класс PenaltyDice:

Этот класс моделирует кубик с "штрафом", где выбирается минимальное значение из двух бросков.

Класс BonusDice моделирует кубик с "преимуществом", где выбирается максимальное значение из двух бросков.

Функция value_probabilty() определяет вероятность того, что при броске кубика выпадет указанное значение value, используя многократные повторения бросков.

Функция expected_value() вычисляет среднее значение (математическое ожидание) для заданного кубика на основе определённого количества бросков.

В программе создаются несколько кубиков и применяются их вариации с использованием "штрафа" и "преимущества". Результаты расчётов математического ожидания и вероятностей сохраняются в файл second.csv для дальнейшего анализа.

3. Виртуальное наследование от AbstractDice:

Классы PenaltyDice и BonusDice используют виртуальное наследование от базового класса AbstractDice, что решает проблему ромбовидного наследования. В случае наследования классом DoubleDice, это предотвращает создание нескольких копий одного и того же базового класса. Благодаря виртуальному наследованию, существует только одна копия AbstractDice.

Класс DoubleDice одновременно наследуется от PenaltyDice и BonusDice и использует один и тот же объект кубика, который передаётся в конструктор. В методе roll() вычисляется среднее между минимальным значением (из PenaltyDice) и максимальным значением (из BonusDice). Таким образом, класс объединяет две стратегии: "штраф" и "преимущество".

Функция expected_value() вычисляет математическое ожидание для любого объекта, который реализует интерфейс AbstractDice, путём многократных бросков кубика.

Функция value_probabilty() вычисляет вероятность попадания в заданное значение на основе нескольких бросков кубика.

Создаётся объект обычного кубика (Dice), который затем передаётся в объект DoubleDice. DoubleDice применяет обе стратегии — минимум из двух бросков (штраф) и максимум (преимущество). Программа вычисляет математическое ожидание и записывает вероятности для различных значений в файл.
