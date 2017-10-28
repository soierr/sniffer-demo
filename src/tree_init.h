/*
 * tree_api.h
 *
 *  Created on: Oct 23, 2017
 *      Author: soierr
 */

#ifndef TREE_INIT_H_
#define TREE_INIT_H_

#include <stdlib.h>
#include <stdio.h>

#include "unistd.h"

#include "proto/node.pb-c.h"

#include "tree_manipulate.h"

#define FILE_STATS_BIN "stats.bin"

#define LENGTH_READ_BUFFER 1024

enum TREENODE_COLOR{
	RED,
	BLACK
};

struct TreeNode {

	int ip;
	unsigned int count;
	enum TREENODE_COLOR color;
	struct TreeNode * parent;
	struct TreeNode * left;
	struct TreeNode * right;
};

struct TreeStats{

	struct TreeNode * root;
	int max_count_ip;
	unsigned int max_count;
	int min_count_ip;
	unsigned int min_count;
	unsigned int total_ip;

};

enum RESULT_TREE{

	T_NOT_SET,
	T_OK,
	T_SAVING_FAILED,
	T_FAILED

};

enum RESULT_TREE tree_init(unsigned int default_root, char ** result_desc);

#endif /* TREE_INIT_H_ */
