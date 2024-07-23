
/**
 *
 * @mainpage Простая хеш-таблица с двумя методами рехеширования.
 * @section Описание
 * Пример использования рехэширования с использованием псевдослучайных чисел и простого списка для разрешения коллизий в хэш-таблице
 *
 * @section Требования
 * 1. CMake 3.16 или выше
 * 2. Компилятор, поддерживающий стандарт C++17
 * 3. Рекомендуется использовать среду разработки CLion
 *
 * @author
 * Ващенко Лев Сергеевич
 *
 * @version 1.6
 *
 * @date 06.2023
 *
 */



#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <ctime>
#include <chrono>

/** @brief Размер таблицы */
const int TABLE_SIZE = 200;

/** @class HashTable
 *  @brief Класс, реализующий простую хеш-таблицу.
 *
 *  Хеш-таблица использует список для разрешения коллизий.
 */
class HashTable {
private:
    /** @brief Массив списков для хранения элементов */
    std::list<std::string> table[TABLE_SIZE];

    /** @brief Хеш-функция
     *
     *  @param key Ключ для хеширования
     *  @return Индекс в таблице
     */
    int hash(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % TABLE_SIZE;
    }

public:
    /** @brief Вставка элемента в таблицу
     *
     *  @param key Ключ для вставки
     */
    void insert(std::string key) {
        int index = hash(key);
        table[index].push_back(key);
    }

    /** @brief Рехеширование с использованием случайных чисел
     *
     *  Элементы перемещаются в случайные индексы в таблице.
     */
    void rehash_random() {
        std::srand(std::time(nullptr));
        std::list<std::string> new_table[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (std::string key : table[i]) {
                int new_index = std::rand() % TABLE_SIZE;
                new_table[new_index].push_back(key);
            }
        }
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = new_table[i];
        }
    }

    /** @brief Рехеширование с использованием списка
     *
     *  Элементы перемещаются на следующий индекс в таблице.
     */
    void rehash_list() {
        std::list<std::string> new_table[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (std::string key : table[i]) {
                int new_index = (i + 1) % TABLE_SIZE;
                new_table[new_index].push_back(key);
            }
        }
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = new_table[i];
        }
    }

    /** @brief Вывод содержимого таблицы на экран */
    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {

            for (std::string key : table[i]) {
                std::cout << "Index " << i << ": "<<  key << ", \n";
            }

        }
        std::cout << "\n\n";
    }
};

/** @brief Главная функция */
int main() {
    HashTable ht;
    ht.insert("apple");
    ht.insert("banana");
    ht.insert("orange");
    ht.insert("grape");
    ht.insert("watermelon");
    std::cout << "Rehashing randomly..." << std::endl;
    ht.rehash_random();
    ht.print();
    std::cout << "Rehashing by list..." << std::endl;
    ht.rehash_list();
    ht.print();

    auto start = std::chrono::high_resolution_clock::now();
    ht.rehash_random();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Время выполнения rehash_random(): " << duration.count() << " микросекунд" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    ht.rehash_list();
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Время выполнения rehash_list(): " << duration.count() << " микросекунд" << std::endl;

}
