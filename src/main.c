#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    FILE *file, *out_file; 

    if (argc != 2)
    {
        printf("You must input a filename!\n");
        return MISSING_ARGUMENT;
    }

    char str[STR_LEN + 2];
    char new_str[STR_LEN + 1];
    int line_number = 0;
    memset(str, '\0', sizeof(str));
    memset(new_str, '\0', sizeof(new_str));

    char *words_array[WORD_NUMBER];

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File was not found!\n");
        return FILE_NOT_FOUND;
    }

    out_file = fopen("../func_tests/scripts/answer.txt", "w");
    if (out_file == NULL)
    {
        printf("Error: Cannot create output file!\n");
        fclose(file);
        return FILE_CREATION_ERROR;
    }

    while (fgets(str, sizeof(str), file) != NULL)
    {
        if (str[0] == '\n' || str[0] == '\0')
            continue;

        else if (str[STR_LEN] != '\0')
        {
            printf("Error: String exceeds 256 characters!\n");
            return STRING_OVERFLOW;
        }
    
        delete_slashn(str);
        int word_count = divide_string_into_words(str, words_array);
        if (!word_count || word_count == INVALID_PARAMETR)
        {
            printf("Error: Word exceeds 16 characters!\n");
            return WORD_OVERFLOW;
        }

        int min_vowel = 0, max_vowel = 0;
        if (find_min_max_vowels(words_array, word_count, &min_vowel, &max_vowel) == INVALID_PARAMETR)
            return INVALID_PARAMETR;
        if (swap_min_max(words_array, word_count, &min_vowel, &max_vowel) == INVALID_PARAMETR)
            return INVALID_PARAMETR;
        if (concatenate_words(new_str, words_array, word_count) == INVALID_PARAMETR)
            return INVALID_PARAMETR;

        ++line_number;

        fprintf(out_file, "%s\n", new_str);

        memset(str, '\0', sizeof(str));
        memset(new_str, '\0', sizeof(new_str));
    }

    fclose(file);
    fclose(out_file);

    if (!line_number)
    {
        printf("Error: Empty file!\n");
        return EMPTY_FILE;
    }

    printf("Processing complete. Results saved to answer.txt\n");
    return OK;
}
