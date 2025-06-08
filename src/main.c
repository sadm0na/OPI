/**
 * \mainpage Программа обработки строк, считанных из файла
 * \section purpose Назначение
 * Программа обрабатывает текстовый файл, находит в каждой строке слова с минимальным 
 * и максимальным количеством гласных, меняет их местами и сохраняет результат в текстовый файл.
 * \file main.c
 * \brief Главный модуль программы
 * 
 * Программа выполняет следующие действия для каждой строки входного файла:
 * - Считывает очередную строку файла
 * - Разбивает строку на слова
 * - Находит слова с минимальным и максимальным количеством гласных
 * - Меняет их местами
 * - Сохраняет результат в новый файл
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

/**
 * \brief Главная функция программы
 * \param argc Количество аргументов командной строки
 * \param argv Массив аргументов (ожидается имя входного файла)
 * \return Код возврата:
 *         - OK (0) в случае успеха,
 *         - Отрицательные значения при ошибках
 * 
 * \warning Ограничения:
 * - Максимальная длина строки: STR_LEN символов
 * - Максимальная длина слова: WORD_LEN символов
 * - Максимальное количество слов в строке: WORD_NUMBER
 * 
 * Пример использования:
 * \code
 * ./app.exe func_tests/data/pos_01_in.txt
 * \endcode
 * 
 * \note Результат сохраняется в файл func_tests/scripts/answer.txt
 */
int main(int argc, char *argv[])
{
    FILE *file, *out_file; 

    /* Проверка аргументов командной строки */
    if (argc != 2)
    {
        printf("You must input a filename!\n");
        return MISSING_ARGUMENT;
    }

    /* Инициализация буферов */
    char str[STR_LEN + 2];          
    char new_str[STR_LEN + 1];      
    int line_number = 0;            
    memset(str, '\0', sizeof(str));
    memset(new_str, '\0', sizeof(new_str));

    char *words_array[WORD_NUMBER]; 

    /* Открытие входного файла */
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File was not found!\n");
        return FILE_NOT_FOUND;
    }

    /* Создание выходного файла */
    out_file = fopen("func_tests/scripts/answer.txt", "w");
    if (out_file == NULL)
    {
        printf("Error: Cannot create output file!\n");
        fclose(file);
        return FILE_CREATION_ERROR;
    }

    /* Обработка каждой строки файла */
    while (fgets(str, sizeof(str), file) != NULL)
    {
        /* Пропуск пустых строк */
        if (str[0] == '\n' || str[0] == '\0')
            continue;

        /* Проверка на переполнение строки */
        else if (str[STR_LEN] != '\0')
        {
            printf("Error: String exceeds 256 characters!\n");
            return STR_OVERFLOW;
        }
    
        /* Основной процесс обработки строки */
        delete_slashn(str);
        int word_count = divide_string_into_words(str, words_array);
        if (!word_count || word_count == INVALID_PARAMETR)
        {
            printf("Error: Word exceeds 16 characters!\n");
            return WORD_OVERFLOW;
        }

        /* Поиск и замена слов */
        int min_vowel = 0, max_vowel = 0;
        if (find_min_max_vowels(words_array, word_count, &min_vowel, &max_vowel) == INVALID_PARAMETR)
            return INVALID_PARAMETR;
        if (swap_min_max(words_array, word_count, &min_vowel, &max_vowel) == INVALID_PARAMETR)
            return INVALID_PARAMETR;
        if (concatenate_words(new_str, words_array, word_count) == INVALID_PARAMETR)
            return INVALID_PARAMETR;

        ++line_number;

        /* Запись результата */
        fprintf(out_file, "%s\n", new_str);

        /* Очистка буферов для следующей строки */
        memset(str, '\0', sizeof(str));
        memset(new_str, '\0', sizeof(new_str));
    }

    /* Завершающие операции */
    fclose(file);
    fclose(out_file);

    /* Проверка на пустой файл */
    if (!line_number)
    {
        printf("Error: Empty file!\n");
        return EMPTY_FILE;
    }

    printf("Processing complete. Results saved to answer.txt\n");
    return OK;
}
