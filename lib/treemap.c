/* treemap.c -- Simple red-black tree implementation */

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treemap.h"

#define RED 0
#define BLACK 1

void fix_insertion(struct tree_map *tree, struct entry *x);

struct entry *null_entry()
{
    /* Allocate memory for the null entry */
    struct entry *null_entry = (struct entry *)malloc(sizeof(struct entry));

    /* Zero unrelated fields */
    null_entry->key = NULL;
    null_entry->value = NULL;
    null_entry->left = NULL;
    null_entry->right = NULL;
    null_entry->parent = NULL;

    /* All null entries are black */
    null_entry->color = BLACK;

    /* Return the null entry pointer */
    return null_entry;
}

struct entry *new_entry(char *key, void *value, struct entry *parent)
{
    struct entry *new_entry = null_entry();

    new_entry->key = key;
    new_entry->value = value;
    new_entry->parent = parent;

    if (parent != NULL)
    {
        if (strcmp(key, parent->key) < 0)
        {
            parent->left = new_entry;
        }
        else
        {
            parent->right = new_entry;
        }
    }

    return new_entry;
}

struct tree_map *new_tree()
{
    struct tree_map *tree = (struct tree_map *)malloc(sizeof(struct tree_map));

    /* Zero all fields*/
    tree->root = NULL;
    tree->size = 0;

    /* Return the tree map pointer */
    return tree;
}

void set_color(struct entry *entry, int color)
{
    if (entry != NULL)
        entry->color = color;
}

int get_color(struct entry *entry)
{
    if (entry != NULL)
        return entry->color;
    return BLACK;
}

/* A red-black tree left rotation requires the following actions:
 * 1) Let pivot’s left child be entry’s right child.
 * 2) Let pivot be the parent and entry be its left child.
 */
void left_rotate(struct tree_map *tree, struct entry *p)
{
    if (p != NULL)
    {
        struct entry *r = p->right;
        p->right = r->left;
        if (r->left != NULL)
            r->left->parent = p;
        r->parent = p->parent;
        if (p->parent == NULL)
            tree->root = r;
        else if (p->parent->left == p)
            p->parent->left = r;
        else
            p->parent->right = r;
        r->left = p;
        p->parent = r;
    }
}

/* A red-black tree right rotation requires the following actions:
 * 1) Let c’s right child be p’s left child.
 * 2) Let c be the parent and p be its right child.
 */
void right_rotate(struct tree_map *tree, struct entry *p)
{
    if (p != NULL)
    {
        struct entry *l = p->left;
        p->left = l->right;
        if (l->right != NULL)
            l->right->parent = p;
        l->parent = p->parent;
        if (p->parent == NULL)
            tree->root = l;
        else if (p->parent->right == p)
            p->parent->right = l;
        else
            p->parent->left = l;
        l->right = p;
        p->parent = l;
    }
}

/* From java.util.TreeMap */
void fix_insertion(struct tree_map *tree, struct entry *x)
{
    set_color(x, RED);

    while (x != NULL && x != tree->root && x->parent->color == RED)
    {
        if (x->parent == x->parent->parent->left)
        {
            struct entry *y = x->parent->parent->right;
            if (get_color(y) == RED)
            {
                set_color(x->parent, BLACK);
                set_color(y, BLACK);
                set_color(x->parent->parent, RED);
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    left_rotate(tree, x);
                }
                set_color(x->parent, BLACK);
                set_color(x->parent->parent, RED);
                right_rotate(tree, x->parent->parent);
            }
        }
        else
        {
            struct entry *y = x->parent->parent->left;
            if (get_color(y) == RED)
            {
                set_color(x->parent, BLACK);
                set_color(y, BLACK);
                set_color(x->parent->parent, RED);
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    right_rotate(tree, x);
                }
                set_color(x->parent, BLACK);
                set_color(x->parent->parent, RED);
                left_rotate(tree, x->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}

struct entry *get_entry(struct tree_map *tree, char *key)
{
    struct entry *entry = tree->root;
    struct entry *parent;

    while (entry->left != NULL || entry->right != NULL)
    {
        int cmp = strcmp(key, entry->key);
                if (cmp < 0)
        {
            entry = entry->left;
        }
        else if (cmp > 0)
        {
            entry = entry->right;
        } else {
            return entry;
        }
    }

    return NULL;
}

void add_entry(struct tree_map *tree, char *key, void *value)
{
    if (tree->root == NULL)
    {
        tree->root = new_entry(key, value, NULL);
        return;
    }

    struct entry *entry = tree->root;
    struct entry *parent;

    while (entry != NULL)
    {
        parent = entry;
        int cmp = strcmp(key, entry->key);
        if (cmp < 0)
        {
            entry = entry->left;
        }
        else if (cmp > 0)
        {
            entry = entry->right;
        }
        else
        {
            entry->value = value;
            return;
        }
    }

    fix_insertion(tree, new_entry(key, value, parent));
    tree->size++;
    return;
}

/* ----------Tree to linked list---------- */

struct list_node *new_node(char *key, void *value, struct list_node *next)
{
    struct list_node *node = (struct list_node *)malloc(sizeof(struct list_node));

    node->key = key;
    node->value = value;
    node->next = next;

    return node;
}

struct list_node *entry_set(struct entry *entry, struct list_node *list)
{
    if (entry == NULL)
        return list;

    if (entry->left == NULL && entry->right == NULL)
    {
        return new_node(entry->key, entry->value, list);
    }

    if (entry->right != NULL)
    {
        list = entry_set(entry->right, list);
    }

    list = new_node(entry->key, entry->value, list);

    if (entry->left != NULL)
    {
        list = entry_set(entry->left, list);
    }

    return list;
}
