/*
 * tree_save.c
 *
 *  Created on: Oct 26, 2017
 *      Author: soierr
 */
#include "tree_save.h"

static TreeArrayed tree_arrayed = TREE_ARRAYED__INIT;
static Node ** nodes;
static unsigned int inx;

static void fill_array(struct TreeNode * node);

enum RESULT_TREE tree_save(char ** result_desc){

	FILE * file = NULL;
	struct TreeNode * root;
	struct TreeStats * ts;

	void * buf;
	unsigned int length;

	/*w+ -option description
	 write/update: Create an empty file and open it for update (both for input and output).
	 If a file with the same name already exists its contents are discarded and the file
	 is treated as a new empty file.*/
	if((file = fopen (FILE_STATS_BIN, "w+")) == NULL) {

		*result_desc = "Can not create file";
		return T_SAVING_FAILED;

	}

	fclose(file);

	ts = get_stats();

	root = get_root();

	nodes = malloc(ts->total_ip * sizeof(Node*));

	inx = 0;
	fill_array(root);

	tree_arrayed.n_nodes = inx;
	tree_arrayed.nodes = nodes;

	length = tree_arrayed__get_packed_size(&tree_arrayed);
	buf = malloc(length);
	tree_arrayed__pack(&tree_arrayed, buf);

	file = fopen (FILE_STATS_BIN, "w+");
	fwrite(buf,length,1,file);


	fclose(file);

	free(nodes);
	free(buf);

	return T_OK;

}

static void fill_array(struct TreeNode * node){

	/*inorder_traversal*/

	if(node->left){
		fill_array(node->left);
	}

	nodes[inx] = malloc(sizeof(Node));
	node__init(nodes[inx]);

	nodes[inx]->ip = node->ip;
	nodes[inx]->count = node->count;

	inx++;

	if(node->right){
		fill_array(node->right);
	}
}


