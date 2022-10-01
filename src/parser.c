/* parser.c -- Important parsing functions */

/*
 * Copyright (C) 2022 Dylan Middendorf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 2500

char *skip_whitespace(char *str)
{
    int len = strlen(str);
    int st = 0;

    // Find the skip size
    while (st < len && isspace(st))
        ++st;

    // Skip the whitespace
    return st + str;
}

int front_file_signature(char *str)
{
    str = skip_whitespace(str);

    if (strlen(str) < 2)
        return 1;
    if (str[0] == '!' && str[1] == '-')
        return 0;
    return 2;
}

int skip_file_signature(FILE *fp)
{
    /* Variable declaration/initialization */
    char buffer[MAX_LINE_LENGTH];

    if (fp == NULL)
        return 1;

    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        if (front_file_signature(buffer) == 0)
        {
            return 0;
        }
    }

    return 2;
}

char *replace_substring(char *str, char *find, char *replace)
{
    if (sizeof(find) > sizeof(replace))
    {
    }
    else
    {
    }
    char *current_pos = strchr(str, find);
    while (current_pos)
    {
        *current_pos = replace;
        current_pos = strchr(current_pos, find);
    }
    return str;
}

int print(char *str)
{
}

/*
 * Note: It is the responsibility of the caller to make
 * sure arguments are checked before the methods are called.
 */
int parse(FILE *fp)
{
    char buffer[MAX_LINE_LENGTH];

    /* Check front file signature (!-) */
    if (skip_file_signature(fp) != 0)
        return 1;

    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        switch (skip_whitespace(buffer)[0])
        {
        case '#':
            break;
        case '_':
            break;
        case '$':
            break;
        case '!':
            break;
        case '-':
        default:
            return 2;
        }
    }
}