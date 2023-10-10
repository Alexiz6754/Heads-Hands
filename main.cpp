/******************************************************************************

Седымов Алексей - Heads and Hands (Тестовое)

*******************************************************************************/

/*Алгоритм и требования
Ввод n
Создать массив всех массивов размером n (матрицу)
Инициализировать каждый массив в матрице
    -У каждого массива случайный размер
    -Массивы заполнены случайными числами
    -Размеры всех массивов не должны совпадать
Отсортировать все массивы в матрице
    - С четным номером в матрице по возрастанию
    - С нечетным номером в матрице по убыванию
На выходе функция возвращает матрицу с отсортированными массивами
*/

/*
Ограничения программы


Прим:
RAND_MAX может иметь разное значение 
в зависимости от системы, например 32767 (двухбайтовое целое) или 2147483647 (четырехбайтовое целое).
*/

#include <iostream>
#include <cstdlib>

using namespace std;

//Границы генерируемых случайных чисел 
#define MIN_BORDER -100 // Нижняя граница чисел в массивах
#define MAX_BORDER 100 // Верхняя граница чисел в массивах
#define MAX_SIZE 10000 // Максимальный размер массивов

//Сигнатуры функций (для отладки)
void swap(size_t* a, size_t* b);
void printArray(size_t* array, size_t size);
void printArray(double* array, size_t size);

//Возвращает случайное (отрицательное или положительное) число в диапазоне от min+1 до max+1
//С точностью до .0001
double generateRandomNumber(int min, int max){
    return (rand() % (max - min) + min) + (rand() % 10000)/10000.0;
}

//Возвращает массив случайных, несовпадающих размеров массивов в матрице
//Алгоритм генерации: используем псевдослучайную генерацию функции rand()
//Генерируем случайные числа в интервалах
//Кол-во интервалов = n
//числа в каждом интервале: диапазон от 0 до RAND_MAX / n (Целочисленные)
//Ограничения: n <= RAND_MAX
//После в случайном порядке перемешиваем все 
size_t* generateRandomArraySize(size_t size){
    size_t* randomSizeArr = new size_t[size];

    size_t interval = 0; //шаг интервала - MAX_SIZE / size; (RAND_MAX >= MAX_SIZE >= n )

    for (size_t i = 0;i < size;++i){
        randomSizeArr[i] = (int)generateRandomNumber(interval, interval + MAX_SIZE / size);
        interval += MAX_SIZE / size;
    }

    //перемешиваем элементы
    for (size_t i = 0;i < size;++i){
        swap(&randomSizeArr[rand() % (int)size], &randomSizeArr[rand() % (int)size]);
    }

    //printArray(randomSizeArr, size);//тест

    return randomSizeArr;
}

//поменять местами значения по указателям
void swap(size_t* a, size_t* b){
    size_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(double* a, double* b){
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

//Возвращает заполненный случайными числами (в диапазоне от MIN_BORDER до MAX_BORDER) массив определенной длины
double* generateRandomArray(size_t size){
    double* randomArr = new double[size];
    
    for (size_t i = 0;i < size;++i){
        randomArr[i] = generateRandomNumber(MIN_BORDER, MAX_BORDER);
    }
    
    return randomArr;
}

//Пузырьковая сортировка за O(n^2) - (Я понимаю, что это упадет на RAND_MAX, но это самая простая реализация с учетом ограничения)
//ascending = true : по возрастанию
void sort(double* array, size_t size, bool ascending){
    for (size_t i = 0;i < size;++i){
        for (size_t j = 0;j < size;++j){
            if (ascending){
                if (array[j] < array[j+1]){
                    swap(array[j],array[j+1]);
                }
            } else {
                if (array[j] > array[j+1]){
                    swap(array[j],array[j+1]);
                }
            }

        }
    }
}

//Реализуемая функция
//В функцию передается указатель на массив размеров, чтобы было удобнее работать с выводом в main
double** calculate(size_t n, size_t** main_sizes){
    double **matrix = new double*[n]; // создали матрицу
    
    size_t *sizes = generateRandomArraySize(n); // создали неповторяющиеся размеры массивов 
    *main_sizes = sizes;

    //Инициализация и сортировка матрицы
    for (size_t i = 0;i < n;++i){
        matrix[i] = generateRandomArray(sizes[i]);

        //сортировка массивов в зависимости от чётности их расположения в матрице
        if (i % 2 == 0){
            sort(matrix[i], sizes[i], true);
        } else {
            sort(matrix[i], sizes[i], false);
        }

    }

    return matrix;
}

//Выводит массив double на экран консоли
void printArray(double* array, size_t size){
    for (size_t i = 0;i < size;++i){
        cout << array[i] << " ";
    }
    cout << endl;
}

//Выводит массив size_t на экран консоли
void printArray(size_t* array, size_t size){
    for (size_t i = 0;i < size;++i){
        cout << array[i] << " ";
    }
    cout << endl;
}

//Выводит матрицу на экран
void printMatrix(double** matrix, size_t n, size_t* sizes){
    for (size_t i = 0;i < n;++i){
        printArray(matrix[i],sizes[i]);
    }
}

int main()
{
    //Настройка rand() для получения случайных чисел
    srand(time(NULL));
    
    //Объявление необходимых переменных
    size_t n; //Натуральное число подающееся на вход n >= 1
    size_t *sizes;//размеры массивов
    double **matrix;//Итоговая матрица
    
    //Ввод (без проверок на правильность введенного числа)
    cout << "Введите натуральное число n: ";
    cin >> n;
    
    //
    matrix = calculate(n, &sizes); 
    
    //вывод матрицы
    printMatrix(matrix, n, sizes);
    
    //очищение памяти
    for (size_t i = 0;i < n;++i){
        delete[] matrix[i];
    }
    delete[] matrix;
    
    delete[] sizes;
    

    return 0;
}
