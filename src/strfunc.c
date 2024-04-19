#include "include/strfunc.h"
#include <stdio.h>

int strcount(char *haystack, char *needle)
{
    int needle_len = strlen(needle);
    int count = 0;

    if (needle_len)
    {
        char *str_str = strstr(haystack, needle);

        // will not run once if str_str returns (nil) -> substring not found
        while (str_str)
        {
            // substring was found at least once, increment count and search again
            count++;
            str_str += needle_len;
            str_str = strstr(str_str, needle);
        }
    }
    return count;
}

char *strreplace(char *haystack, char *needle, char *new_needle, int free_old_haystack)
{
    if (strcmp(needle, "") == 0)
        return haystack;

    int needle_len_diff = strlen(new_needle) - strlen(needle);
    long new_haystack_size = strlen(haystack) - (strcount(haystack, needle) * (-1 * needle_len_diff)) + 1;

    char *new_haystack = calloc(new_haystack_size, sizeof(char));

    char *last_strstr = strstr(haystack, needle);
    char *last_replacement_end = haystack;

    int repcount = 0;
    int addedchars = 0;
    while (last_strstr)
    {
        strncpy(&new_haystack[(last_strstr - haystack) + addedchars], new_needle, strlen(new_needle));
        strncpy(&new_haystack[last_replacement_end - haystack + addedchars], last_replacement_end, last_strstr - last_replacement_end);

        last_replacement_end = last_strstr + strlen(needle);
        last_strstr = strstr(last_replacement_end, needle);

        repcount++;
        addedchars = repcount * needle_len_diff;
    }
    strlcpy(&new_haystack[last_replacement_end - haystack + (repcount * needle_len_diff)], last_replacement_end, strlen(haystack) - (last_replacement_end - haystack));

    if (new_haystack[new_haystack_size - 1] != '\0')
        new_haystack[new_haystack_size - 1] = '\0';

    if (free_old_haystack)
        free(haystack);

    return new_haystack;
}

char *strafterlast(const char *haystack, const char *needle)
{
    char *ptr = strrchr(haystack, *needle);
    if (ptr == NULL)
    {
        free(ptr);
        return strdup("");
    }
    return ptr + 1;
}