#include "src/utils.h"
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

void test_count_vowels(void) {
    int err_count = 0;
    
    // Тест с NULL
    if (count_vowels(NULL, 5) != 0 && count_vowels(NULL, 5) != INVALID_PARAMETR) err_count++;
    
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
    int min, max;
    
    // Одно слово
    char *single_word[WORD_NUMBER] = {"Test"};
    int lol = find_min_max_vowels(single_word, 1, &min, &max);
    if (lol == INVALID_PARAMETR) err_count++;
    else if (min != 0 || max != 0) err_count++;
    
    // Несколько слов с разным количеством гласных
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
    
    printf("%s: %s\n", __func__, err_count ? "OK" : "FAILED");
}

void test_swap_min_max(void) {
    int err_count = 0;
    int min = 0, max = 2;
    
    // Обычный случай
    char *words[WORD_NUMBER] = {"Test", "Hello", "Aeiou"};  
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
    if (divide_string_into_words(NULL, words) != 0 && divide_string_into_words(NULL, words) != INVALID_PARAMETR) err_count++;
    
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
    
    // Слова с разными разделителями
    char with_delims[STR_LEN + 1] = " Hello  world\ttest\n";
    if (divide_string_into_words(with_delims, words) != 3) err_count++;
    
    // Слово слишком длинное
    char long_word[STR_LEN + 2];
    memset(long_word, 'a', STR_LEN + 1);
    long_word[STR_LEN + 1] = '\0';
    if (divide_string_into_words(long_word, words) != 0) err_count++;
    
    // Много слов
    char max_words[STR_LEN + 1] = "a b c d e f g h i j k l m n o p";
    if (divide_string_into_words(max_words, words) != WORD_NUMBER) err_count++;
    
    printf("%s: %s\n", __func__, err_count ? "OK" : "FAILED");
}

int main(void) {
    test_count_vowels();
    test_find_min_max_vowels();
    test_swap_min_max();
    test_divide_string_into_words();
    
    return 0;
}
