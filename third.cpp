#include <random>  // Библиотека для генерации случайных чисел
#include <fstream>  // Для записи данных в файл
#include <iostream>  // Для вывода результатов в консоль

// Абстрактный базовый класс, представляющий интерфейс для кубиков
struct AbstractDice {
    virtual ~AbstractDice() {}  // Виртуальный деструктор для корректного удаления объектов
    virtual unsigned roll() = 0;  // Чисто виртуальный метод для выполнения броска кубика
};

// Класс Dice моделирует кубик с заданным количеством граней (max)
class Dice : public AbstractDice {
public:
    // Конструктор принимает максимальное значение (граней) и seed для генерации случайных чисел
    Dice(unsigned max, unsigned seed):
        max(max), dstr(1, max), reng(seed) {}
    
    // Метод roll возвращает случайное число от 1 до max
    unsigned roll() override {
        return dstr(reng);  // Генерация случайного числа
    }

private:
    unsigned max;  // Количество граней кубика
    std::uniform_int_distribution<unsigned> dstr;  // Равномерное распределение для чисел от 1 до max
    std::default_random_engine reng;  // Генератор случайных чисел
};

// Класс PenaltyDice моделирует кубик со штрафом (выбирает минимальный результат из двух бросков)
// Используем виртуальное наследование от AbstractDice для решения проблемы ромбовидного наследования
class PenaltyDice : virtual public AbstractDice {
public:
    // Конструктор принимает ссылку на объект кубика для выполнения бросков
    PenaltyDice(AbstractDice &dice) :
        dice(dice) {}
    
    // Метод roll возвращает наименьший результат из двух бросков
    unsigned roll() override {
        auto first = dice.roll(), second = dice.roll();  // Выполняем два броска
        return first <= second ? first : second;  // Возвращаем меньший результат
    }

private:
    AbstractDice &dice;  // Ссылка на объект кубика
};

// Класс BonusDice моделирует кубик с преимуществом (выбирает максимальный результат из двух бросков)
// Виртуальное наследование для совместимости с другими классами, которые наследуют от AbstractDice
class BonusDice : virtual public AbstractDice {
public:
    // Конструктор принимает ссылку на объект кубика для выполнения бросков
    BonusDice(AbstractDice &dice) :
        dice(dice) {}
    
    // Метод roll возвращает наибольший результат из двух бросков
    unsigned roll() override {
        auto first = dice.roll(), second = dice.roll();  // Выполняем два броска
        return first >= second ? first : second;  // Возвращаем больший результат
    }

private:
    AbstractDice &dice;  // Ссылка на объект кубика
};

// Класс DoubleDice наследует как PenaltyDice, так и BonusDice, что позволяет комбинировать обе стратегии
class DoubleDice : public PenaltyDice, public BonusDice {
public:
    // Конструктор принимает объект кубика и передаёт его в конструкторы PenaltyDice и BonusDice
    DoubleDice(AbstractDice& dice) : 
        PenaltyDice(dice), BonusDice(dice) {}
    
    // Метод roll возвращает среднее значение между результатами штрафа и преимущества
    unsigned roll() override {
        return (PenaltyDice::roll() + BonusDice::roll()) / 2;  // Возвращаем среднее между минимальным и максимальным результатом
    }
};

// Функция для вычисления математического ожидания для любого объекта, реализующего AbstractDice
double expected_value(AbstractDice &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;  // Счётчик для суммы всех бросков
    // Выполняем number_of_rolls бросков кубика и суммируем их результаты
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    // Возвращаем среднее значение всех бросков (математическое ожидание)
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

// Функция для вычисления вероятности выпадения конкретного значения value
double value_probabilty(AbstractDice &d, unsigned value, unsigned number_of_rolls = 1) {
    unsigned accum = 0;  // Переменная для подсчёта попаданий
    // Выполняем number_of_rolls бросков и считаем, сколько раз выпало значение value
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        if (d.roll() == value) accum += 1;  // Увеличиваем счётчик при совпадении
    }
    return static_cast<double>(accum) / number_of_rolls;  // Возвращаем вероятность как долю попаданий от общего числа бросков
}

int main() {

    // Инициализируем кубик с 100 гранями и начальным seed для генерации случайных чисел
    int max = 100, number_of_rolls = 1000000;  // max — количество граней кубика, number_of_rolls — количество бросков
    Dice base(max, 1123);  // Обычный кубик с 100 гранями

    // Создаём объект DoubleDice, который использует как PenaltyDice, так и BonusDice
    DoubleDice child(base);

    // Вычисляем и выводим математическое ожидание для DoubleDice
    std::cout << "Expected value: " << expected_value(child, number_of_rolls) << std::endl;

    // Открываем файл для записи результатов
    std::ofstream data("third.csv");
    
    // Записываем заголовки для данных
    data << "Target\tDouble" << std::endl;

    // Рассчитываем вероятность выпадения каждого значения для DoubleDice и записываем в файл
    for (int target = 1; target < max; target++) {
        data << target << "\t" << value_probabilty(child, target, number_of_rolls) << std::endl;  // Вычисляем вероятность для каждого значения
    }
    data.close();  // Закрываем файл после завершения записи

    return 0;
}
