#include <stddef.h>
#include <string.h>
#include "utils.h"

char vowels[] = {'a', 'o', 'u', 'e', 'y', 'i', 'A', 'O', 'U', 'E', 'Y', 'I'};

int is_vowel(char c)
{
    int flag = 0;
    for (int i = 0; i < 12; i++)
        if (vowels[i] == c)
            flag = 1;
    return flag;
}

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