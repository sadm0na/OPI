/**
 * \file utils.c
 * \brief Реализация функций для обработки строк и файлов.
 */

#include <stddef.h>
#include <string.h>
#include "utils.h"

char vowels[] = {'a', 'o', 'u', 'e', 'y', 'i', 'A', 'O', 'U', 'E', 'Y', 'I'};


/**
 * \brief Определяет, является ли буква гласной.
 * 
 * \param[in] c Символ, который будет проверяться.
 * \param[out] flag Флаг проверки, является ли символ гласной.
 * \return Код возврата:
 *         - 0 если не гласная буква
 *         - 1 если гласная буква
 */
int is_vowel(char c)
{
    int flag = 0;
    for (int i = 0; i < 12; i++)
        if (vowels[i] == c)
            flag = 1;
    return flag;
}

/**
 * \brief Удаляет символы новой строки (\n) из строки
 * 
 * \param[in,out] str Входная строка, в которой удаляются символы '\n'
 * \return Код возврата:
 *         - OK (0) в случае успеха
 *         - INVALID_PARAMETR если передан NULL-указатель
 */
int delete_slashn(char *str)
{
    if (str == NULL)
        return INVALID_PARAMETR;

    while (*str != '\0')
    {
        if (*str == '\n')
            *str = '\0';
        str++;
    }

    return OK;
}

/**
 * \brief Подсчитывает количество гласных букв в слове
 * 
 * \param[in] word Слово, в котором ищутся гласные
 * \param[in] len Длина слова
 * \return  Код возврата:
 *          - Количество гласных (число >= 0)
 *          - INVALID_PARAMETR, если параметры неверны
 */
int count_vowels(char *word, int len)
{
    if (word == NULL || len < 0)
        return INVALID_PARAMETR;

    int count = 0;
    for (int i = 0; i < len; i++)
        if (is_vowel(*(word+i)))
            ++count;

    return count;
}


/**
 * \brief Находит индексы слов с минимальным и максимальным количеством гласных
 * 
 * \param[in] words_array Массив слов
 * \param[in] word_count Количество слов в массиве
 * \param[out] min_vowel Указатель на слово с минимальным числом гласных
 * \param[out] max_vowel Указатель на слово с максимальным числом гласных
 * \return Код возврата:
 *         - OK (0) в случае успеха
 *         - INVALID_PARAMETR если один из указателей некорректен или индексы переданных слов вне допустимого диапазона
 */
int find_min_max_vowels(char *words_array[WORD_NUMBER], int word_count, int *min_vowel, int *max_vowel)
{
    if (words_array == NULL || min_vowel == NULL || max_vowel == NULL || word_count <= 0)
        return INVALID_PARAMETR;

    char *word = words_array[0];
    int min = count_vowels(word, strlen(word));
    int max = count_vowels(word, strlen(word));

    for (int i = 1; i < word_count; i++)
    {
        word = words_array[i];
        if (count_vowels(word, strlen(word)) > max)
        {
            max = count_vowels(word, strlen(word));
            *max_vowel = i;

        }
        else if (count_vowels(word, strlen(word)) < min)
        {
            min = count_vowels(word, strlen(word));
            *min_vowel = i;
        }
    }

    return OK;
}

/**
 * \brief Меняет местами слова с минимальным и максимальным количеством гласных в массиве
 * 
 * \param[in,out] words_array Массив слов
 * \param[in] arr_len Длина массива
 * \param[in] min_vowel Индекс слова с минимальным числом гласных
 * \param[in] max_vowel Индекс слова с максимальным числом гласных
 * \return Код возврата:
 *         - OK (0) в случае успеха
 *         - INVALID_PARAMETR если указатели некорректны или индексы вне диапазона
 */
int swap_min_max(char *words_array[WORD_NUMBER], int arr_len, int *min_vowel, int *max_vowel)
{
    if (words_array == NULL || min_vowel == NULL || max_vowel == NULL)
        return INVALID_PARAMETR;

    if (*min_vowel < 0 || *min_vowel >= arr_len ||
        *max_vowel < 0 || *max_vowel >= arr_len)
        return INVALID_PARAMETR;

    char *temp = words_array[*max_vowel];
    words_array[*max_vowel] = words_array[*min_vowel];
    words_array[*min_vowel] = temp;

    return OK;
}

/**
 * \brief Разбивает строку на отдельные слова, используя пробел как разделитель
 * 
 * \param[in] str Входная строка
 * \param[out] words_array Массив указателей, куда будут записаны слова
 * \return Код ошибки:
 *         - 0 если слово слишком длинное (> WORD_LEN)
 *         - INVALID_PARAMETR если один из аргументов равен NULL
 * 
 * \note Строка разбивается на слова с помощью функции strtok().
 */
int divide_string_into_words(char str[STR_LEN + 1], char *words_array[WORD_NUMBER])
{
    if (str == NULL || words_array == NULL)
        return INVALID_PARAMETR;

    int word_count = 0;
    char *word = strtok(str, " ");

    while (word != NULL) {
        if (strlen(word) > 16)
            return 0;

        words_array[word_count] = word;
        word_count++;
        word = strtok(NULL, " ");
    }
    
    return word_count;
}

/**
 * \brief Объединяет слова из массива обратно в одну строку через пробел
 * 
 * \param[out] new_str Результирующая строка
 * \param[in] words_array Массив слов
 * \param[in] word_count Количество слов в массиве
 * \return Код возврата:
 *         - OK (0) в случае успеха
 *         - INVALID_PARAMETR если переданы NULL указатели или передано неверное количество слов
 */
int concatenate_words(char new_str[STR_LEN + 1], char *words_array[WORD_NUMBER], int word_count)
{
    if (new_str == NULL || words_array == NULL || word_count <= 0)
        return INVALID_PARAMETR;

    int pos;
    char *move_new_str = new_str;
    for (int i = 0; i < word_count; i++)
    {
        pos = strlen(words_array[i]);
        strcpy(move_new_str, words_array[i]);
        move_new_str[pos] = ' ';
        move_new_str += (pos + 1);
    }

    return OK;
}