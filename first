#include <random>  // Библиотека для генерации случайных чисел
#include <iostream>  // Библиотека для вывода на консоль

// Абстрактный базовый класс для кубиков (или набора кубиков)
// Содержит чисто виртуальный метод roll, который должны реализовать наследники
struct AbstractDice {
    virtual ~AbstractDice() {}  // Виртуальный деструктор для корректного удаления наследников
    virtual unsigned roll() = 0;  // Чисто виртуальный метод для броска кубика, требующий реализации в производных классах
};

// Класс Dice реализует случайный бросок кубика с заданным количеством граней (max)
class Dice : public AbstractDice {
public:
    // Конструктор принимает максимальное значение кубика (max) и seed — начальное значение для генератора случайных чисел
    Dice(unsigned max, unsigned seed) :
        max(max), dstr(1, max), reng(seed) {}  // Инициализация максимального значения, распределения и генератора случайных чисел

    // Реализация метода roll, который возвращает случайное число от 1 до max
    unsigned roll() override {
        return dstr(reng);  // Генерируем случайное число
    }

private:
    unsigned max;  // Количество граней кубика
    std::uniform_int_distribution<unsigned> dstr;  // Равномерное распределение для чисел от 1 до max
    std::default_random_engine reng;  // Генератор случайных чисел
};

// Класс ThreeDicePool описывает набор из трёх кубиков (или других объектов, поддерживающих AbstractDice)
class ThreeDicePool : public AbstractDice {
public:
    // Конструктор принимает три объекта, реализующие интерфейс AbstractDice
    ThreeDicePool(AbstractDice &dice_1, AbstractDice &dice_2, AbstractDice &dice_3) :
        dice_1(dice_1), dice_2(dice_2), dice_3(dice_3) {}

    // Метод roll возвращает сумму бросков трёх кубиков
    unsigned roll() override {
        return dice_1.roll() + dice_2.roll() + dice_3.roll();  // Суммируем результаты бросков трёх кубиков
    }

private:
    // Ссылки на три кубика (или другие объекты с методом roll), переданные в конструктор
    AbstractDice &dice_1, &dice_2, &dice_3;
};

// Функция для вычисления математического ожидания для объекта AbstractDice
// Параметры: d — объект AbstractDice, number_of_rolls — количество бросков (по умолчанию 1)
double expected_value(AbstractDice &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;  // Переменная для накопления суммы бросков (unsigned long long предотвращает переполнение)
    // Выполняем number_of_rolls бросков
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();  // Добавляем результат каждого броска
    // Возвращаем среднее значение
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

int main() {
    // Инициализация трёх кубиков с одинаковым количеством граней (max = 6) и различными seed для генератора
    int max = 6, attempts = 1000000;  // max — количество граней кубика, attempts — количество бросков для вычисления среднего
    Dice alpha(max, 12414);  // Первый кубик
    Dice beta(max, 12423414);  // Второй кубик
    Dice gamma(max, 122414);  // Третий кубик

    // Создаем набор из трёх кубиков (alpha, beta, gamma)
    ThreeDicePool three(alpha, beta, gamma);

    // Демонстрация броска одного кубика
    std::cout << "Dice roll: " << alpha.roll() << std::endl;
    // Демонстрация броска трёх кубиков
    std::cout << "Three dice rolls: " << three.roll() << std::endl;

    // Вычисление математического ожидания для одного кубика
    std::cout << "Expected value for Dice: " << expected_value(alpha, attempts) << std::endl;
    // Вычисление математического ожидания для набора из трёх кубиков
    std::cout << "Expected value for ThreeDicePool: " << expected_value(three, attempts) << std::endl;

    return 0;
}
