/*
 * tree_manipulate.h
 *
 *  Created on: Oct 23, 2017
 *      Author: soierr
 */

#ifndef TREE_MANIPULATE_H_
#define TREE_MANIPULATE_H_

#include <stdlib.h>
#include <stdio.h>

#include <tree_init.h>

void create_root(unsigned int ip);

struct TreeNode * get_root();

void set_root(struct TreeNode * root_in);

void insert_node(unsigned int ip);

unsigned int get_count(unsigned int ip);

struct TreeStats * get_stats();

#endif /* TREE_MANIPULATE_H_ */
