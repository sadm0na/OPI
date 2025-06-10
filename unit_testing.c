#include "src/utils.h"
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

void test_count_vowels(void) {
    int err_count = 0;
    
    // Тест с NULL
    if (count_vowels(NULL, 5) != INVALID_PARAMETR) err_count++;
    
    // Пустая строка
    char empty[STR_LEN] = "";
    if (count_vowels(empty, 0) != 0) err_count++;
    
    // Строка без гласных
    char no_vowels[STR_LEN] = "bcdfg";
    if (count_vowels(no_vowels, strlen(no_vowels)) != 0) err_count++;
    
    // Строка с гласными
    char with_vowels[STR_LEN] = "Hello";
    if (count_vowels(with_vowels, strlen(with_vowels)) != 2) err_count++;
    
    // Строка только с гласными
    char all_vowels[STR_LEN] = "AEIOU";
    if (count_vowels(all_vowels, strlen(all_vowels)) != 5) err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

void test_find_min_max_vowels(void) {
    int err_count = 0;
    int lol;
    int min, max;
    
    // Тест с NULL
    if (find_min_max_vowels(NULL, 3, &min, &max) != INVALID_PARAMETR) err_count++;
    char *words[WORD_NUMBER] = {"Test", "Hello", "Aeiou"};
    if (find_min_max_vowels(words, 3, NULL, &max) != INVALID_PARAMETR) err_count++;
    if (find_min_max_vowels(words, 3, &min, NULL) != INVALID_PARAMETR) err_count++;
    
    // Одно слово
    char *single_word[WORD_NUMBER] = {"Test"};
    lol = find_min_max_vowels(single_word, 1, &min, &max);
    if (lol == INVALID_PARAMETR) err_count++;
    else if (min != 0 || max != 0) err_count++;
    
    // // Несколько слов с разным количеством гласных
    char *words1[WORD_NUMBER] = {"Test", "Hello", "Aeiou"};
    lol = find_min_max_vowels(words1, 3, &min, &max);
    if (lol == INVALID_PARAMETR) err_count++;
    else if (min != 0 || max != 2) err_count++;
    
    // Несколько слов с одинаковым количеством гласных
    char *words2[WORD_NUMBER] = {"Test", "Best", "Rest"};
    lol = find_min_max_vowels(words2, 3, &min, &max);
    if (lol == INVALID_PARAMETR) err_count++;
    else if (min != 0 || max != 0) err_count++;
    
    // Слова без гласных
    char *words3[WORD_NUMBER] = {"xwz", "qwr", "pst"};
    lol = find_min_max_vowels(words3, 3, &min, &max);
    if (lol == INVALID_PARAMETR) err_count++;
    if (min != 0 || max != 0) err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

void test_swap_min_max(void) {
    int err_count = 0;
    int min = 0, max = 2;
    
    // Тест с NULL
    char *words[WORD_NUMBER] = {"Test", "Hello", "Aeiou"};
    if (swap_min_max(NULL, 3, &min, &max) != INVALID_PARAMETR) err_count++;
    if (swap_min_max(words, 3, NULL, &max) != INVALID_PARAMETR) err_count++;
    if (swap_min_max(words, 3, &min, NULL) != INVALID_PARAMETR) err_count++;
    
    // Обычный случай
    int lol = swap_min_max(words, 3, &min, &max);
    if (lol == INVALID_PARAMETR) err_count++;
    else if (strcmp(words[0], "Aeiou") != 0 || strcmp(words[1], "Hello") != 0 || strcmp(words[2], "Test") != 0)
        err_count++;
    
    // Минимум и максимум одинаковы
    char *words2[WORD_NUMBER] = {"Test", "Test", "Test"};
    int min2 = 0, max2 = 1;
    lol = swap_min_max(words2, 3, &min2, &max2);
    if (lol == INVALID_PARAMETR) err_count++;
    else if (strcmp(words2[0], "Test") != 0 || strcmp(words2[1], "Test") != 0)
        err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

void test_divide_string_into_words(void) {
    int err_count = 0;
    char *words[WORD_NUMBER];
    
    // Тест с NULL
    if (divide_string_into_words(NULL, words) != INVALID_PARAMETR) err_count++;
    char str[STR_LEN + 1] = "test";
    if (divide_string_into_words(str, NULL) != INVALID_PARAMETR) err_count++;
    
    // Пустая строка
    char empty[STR_LEN + 1] = "";  
    if (divide_string_into_words(empty, words) != 0) err_count++;
    
    // Одно слово
    char single[STR_LEN + 1] = "Hello";
    if (divide_string_into_words(single, words) != 1) err_count++;
    if (strcmp(words[0], "Hello") != 0) err_count++;
    
    // Несколько слов
    char multiple[STR_LEN + 1] = "Hello world test";
    if (divide_string_into_words(multiple, words) != 3) err_count++;
    if (strcmp(words[0], "Hello") != 0 || strcmp(words[1], "world") != 0 || strcmp(words[2], "test") != 0)
        err_count++;
    
    // Слово слишком длинное
    char long_word[STR_LEN + 2];
    memset(long_word, 'a', STR_LEN + 1);
    long_word[STR_LEN + 1] = '\0';
    if (divide_string_into_words(long_word, words) != 0) err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

void test_delete_slashn(void) {
    int err_count = 0;
    
    // Тест с NULL
    if (delete_slashn(NULL) != INVALID_PARAMETR) err_count++;
    
    // Строка без \n
    char no_newline[STR_LEN] = "Hello world";
    if (delete_slashn(no_newline) != OK) err_count++;
    
    // Строка с \n
    char with_newline[STR_LEN] = "Hello\nworld\n";
    if (delete_slashn(with_newline) != OK) err_count++;
    if (strcmp(with_newline, "Hello\0world\0") != 0) err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

void test_concatenate_words(void) {
    int err_count = 0;
    char new_str[STR_LEN + 1];
    
    // Тест с NULL
    char *words[WORD_NUMBER] = {"Hello", "world"};
    if (concatenate_words(NULL, words, 2) != INVALID_PARAMETR) err_count++;
    if (concatenate_words(new_str, NULL, 2) != INVALID_PARAMETR) err_count++;
    
    // Одно слово
    char *single_word[WORD_NUMBER] = {"Hello"};
    if (concatenate_words(new_str, single_word, 1) != OK) err_count++;
    if (strcmp(new_str, "Hello ") != 0) err_count++;
    
    // Несколько слов
    char *multiple_words[WORD_NUMBER] = {"Hello", "world", "test"};
    if (concatenate_words(new_str, multiple_words, 3) != OK) err_count++;
    if (strcmp(new_str, "Hello world test ") != 0) err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "FAILED" : "OK");
}

int main(void) {
    test_count_vowels();
    test_find_min_max_vowels();
    test_swap_min_max();
    test_divide_string_into_words();
    test_delete_slashn();
    test_concatenate_words();
    
    return 0;
}