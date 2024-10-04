#include <random>  // Библиотека для генерации случайных чисел
#include <fstream>  // Для записи результатов в файл
#include <iostream>  // Для вывода результатов в консоль

// Абстрактный базовый класс для кубиков и их потомков
struct AbstractDice {
    virtual ~AbstractDice() {}  // Виртуальный деструктор для корректного удаления объектов через указатель базового класса
    virtual unsigned roll() = 0;  // Чисто виртуальный метод, который возвращает результат броска кубика
};

// Класс Dice моделирует кубик с заданным количеством граней (max)
class Dice : public AbstractDice {
public:
    // Конструктор принимает максимальное значение (количество граней кубика) и начальное значение для генератора случайных чисел
    Dice(unsigned max, unsigned seed) :
        max(max), dstr(1, max), reng(seed) {}
    
    // Реализация метода roll, который возвращает случайное значение от 1 до max
    unsigned roll() override {
        return dstr(reng);  // Генерация случайного значения
    }

private:
    unsigned max;  // Количество граней кубика
    std::uniform_int_distribution<unsigned> dstr;  // Равномерное распределение для случайных чисел от 1 до max
    std::default_random_engine reng;  // Генератор случайных чисел
};

// Класс PenaltyDice моделирует "штрафной" кубик — выбирает наименьший результат из двух бросков
class PenaltyDice : public AbstractDice {
public:
    // Конструктор принимает ссылку на другой кубик, который будет использоваться для бросков
    PenaltyDice(AbstractDice &dice) :
        dice(dice) {}
    
    // Метод roll возвращает наименьшее значение из двух бросков
    unsigned roll() override {
        auto first = dice.roll(), second = dice.roll();  // Выполняем два броска
        return first <= second ? first : second;  // Возвращаем меньшее значение
    }

private:
    AbstractDice &dice;  // Ссылка на кубик, который используется для бросков
};

// Класс BonusDice моделирует "бонусный" кубик — выбирает наибольший результат из двух бросков
class BonusDice : public AbstractDice {
public:
    // Конструктор принимает ссылку на кубик, который будет использоваться для бросков
    BonusDice(AbstractDice &dice) :
        dice(dice) {}
    
    // Метод roll возвращает наибольшее значение из двух бросков
    unsigned roll() override {
        auto first = dice.roll(), second = dice.roll();  // Выполняем два броска
        return first >= second ? first : second;  // Возвращаем большее значение
    }

private:
    AbstractDice &dice;  // Ссылка на кубик, который используется для бросков
};

// Класс ThreeDicePool моделирует набор из трёх кубиков, суммируя результаты их бросков
class ThreeDicePool : public AbstractDice {
public:
    // Конструктор принимает три кубика (или их потомков) для бросков
    ThreeDicePool(AbstractDice &dice_1, AbstractDice &dice_2, AbstractDice &dice_3) :
        dice_1(dice_1), dice_2(dice_2), dice_3(dice_3) {}

    // Метод roll возвращает сумму результатов трёх кубиков
    unsigned roll() override {
        return dice_1.roll() + dice_2.roll() + dice_3.roll();  // Суммируем результаты трёх бросков
    }

private:
    AbstractDice &dice_1, &dice_2, &dice_3;  // Ссылки на три кубика
};

// Функция для вычисления вероятности выпадения конкретного значения value за number_of_rolls попыток
double value_probabilty(AbstractDice &d, unsigned value, unsigned number_of_rolls = 1) {
    unsigned accum = 0;  // Счётчик для фиксации количества совпадений
    // Выполняем number_of_rolls бросков кубика
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        if (d.roll() == value) accum += 1;  // Если выпало нужное значение, увеличиваем счётчик
    }
    return static_cast<double>(accum) / number_of_rolls;  // Возвращаем вероятность как отношение количества совпадений к числу бросков
}

// Функция для вычисления математического ожидания (среднего значения) за number_of_rolls бросков
double expected_value(AbstractDice &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;  // Переменная для накопления суммы всех бросков
    // Выполняем number_of_rolls бросков и суммируем их результаты
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    // Возвращаем среднее значение как сумму всех бросков, делённую на количество бросков
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

int main() {
    // Инициализация кубиков с разным количеством граней
    int max = 100, three_max = 6, number_of_rolls = 1000000;  // max — количество граней кубика, number_of_rolls — количество бросков
    Dice alpha(max, 12414);  // Кубик с 100 гранями
    Dice beta(three_max, 12423414);  // Кубик с 6 гранями
    Dice gamma(three_max, 122414);  // Кубик с 6 гранями
    Dice theta(three_max, 213123);  // Ещё один кубик с 6 гранями

    // Создаём набор из трёх кубиков, который суммирует их значения
    ThreeDicePool three(beta, gamma, theta);

    // Создаём кубик с "штрафом" (выбирает минимальное значение из двух бросков)
    PenaltyDice penalty(alpha); 
    // Создаём кубик с "бонусом" (выбирает максимальное значение из двух бросков)
    BonusDice bonus(alpha);

    // Выводим математическое ожидание для каждого кубика
    std::cout << expected_value(alpha, number_of_rolls) << " ";  // Обычный кубик
    std::cout << expected_value(penalty, number_of_rolls) << " ";  // Кубик со штрафом
    std::cout << expected_value(bonus, number_of_rolls) << std::endl;  // Кубик с бонусом

    // Открываем файл для записи данных (в формате CSV)
    std::ofstream data("second.csv");
    data << "Target\tStandart\tThree\tPenalty\tBonus" << std::endl;

    // Рассчитываем вероятности выпадения каждого значения для всех типов кубиков и записываем в файл
    for (int target = 1; target < max; target++) {
        data << target << "\t" << value_probabilty(alpha, target, number_of_rolls) << "\t";  // Обычный кубик
        data << value_probabilty(three, target, number_of_rolls) << "\t";  // Набор из трёх кубиков
        data << value_probabilty(penalty, target, number_of_rolls) << "\t";  // Кубик со штрафом
        data << value_probabilty(bonus, target, number_of_rolls);  // Кубик с бонусом
        data << std::endl;
    }

    // Закрываем файл после завершения записи
    data.close();

    return 0;
}
