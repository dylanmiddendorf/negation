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

#include "treemap.h"
#include <stdio.h>

void main()
{
    int values[] = {49, 11, 10, 95, 48, 91};
    struct tree_map *tree = new_tree();
    add_entry(tree, "alpha", (void *)&values[0]);
    add_entry(tree, "beta", (void *)&values[1]);
    add_entry(tree, "gamma", (void *)&values[2]);
    add_entry(tree, "delta", (void *)&values[3]);
    add_entry(tree, "epsilon", (void *)&values[4]);
    add_entry(tree, "zeta", (void *)&values[5]);
    
    printf("tree = {");
    struct list_node *list = entry_set(tree->root, NULL);
    while (list->next != NULL)
    {
        printf("\"%s\"=%d, ", list->key, *((int *)list->value));
        list = list->next;
    }
    printf("\"%s\"=%d}\n", list->key, *((int *)list->value));

    printf("Obtaining gamma: %d\n", *((int *)get_entry(tree, "gamma")->value));
    printf("Obtaining epsilon: %d\n", *((int *)get_entry(tree, "epsilon")->value));

}