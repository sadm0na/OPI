#ifndef UTILS_H
#define UTILS_H

/**
 * \file utils.h
 * \brief Прототипы функций и констант для utils.c
 */

 /**
 * \def STR_LEN
 * \brief Максимально допустимая длина входной строки
 */
#define STR_LEN 256

/**
 * \def WORD_NUMBER
 * \brief Максимально допустимое количество слов в строке
 */
#define WORD_NUMBER 128

/**
 * \def WORD_LEN
 * \brief Максимально допустимая длина
 */
#define WORD_LEN 16

#define OK 0
#define EMPTY_FILE -1
#define STR_OVERFLOW -2
#define WORD_OVERFLOW -3
#define MISSING_ARGUMENT -4
#define FILE_NOT_FOUND -5
#define FILE_CREATION_ERROR -6
#define INVALID_PARAMETR -7

int is_vowel(char c);
int delete_slashn(char *str);
int count_vowels(char *word, int len);
int find_min_max_vowels(char *words_array[WORD_NUMBER], int word_count, int *min_vowel, int *max_vowel);
int swap_min_max(char *words_array[WORD_NUMBER], int arr_len, int *min_vowel, int *max_vowel);
int divide_string_into_words(char str[STR_LEN + 1], char *words_array[WORD_NUMBER]);
int concatenate_words(char new_str[STR_LEN + 1], char *words_array[WORD_NUMBER], int word_count);

#endif
