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

#ifndef TREEMAP_H
#define TREEMAP_H

/* A map entry (key-value pair) */
struct entry
{
    char *key;
    void *value;
    struct entry *left;
    struct entry *right;
    struct entry *parent;
    unsigned int color : 1;
};

/* A Red-Black tree */
struct tree_map
{
    struct entry *root;
    int size;
};

struct list_node
{
    char *key;
    char *value;
    struct list_node *next;
};

struct tree_map *new_tree();

struct entry *get_entry(struct tree_map *tree, char *key);

void add_entry(struct tree_map *tree, char *key, void *value);

struct list_node *entry_set(struct entry *entry, struct list_node *list);

#endif