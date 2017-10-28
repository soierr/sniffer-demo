/*
 * tree-api.c
 *
 *  Created on: Oct 23, 2017
 *      Author: soierr
 */
#include <tree_init.h>

static size_t read_buffer(FILE * pFile, unsigned max_length, uint8_t * out);

static struct TreeNode* restore(TreeArrayed * ta);

static struct TreeNode* construct_left(Node** nodes_in, int min_index, int max_index, struct TreeNode* parent);

static struct TreeNode* construct_right(Node** nodes_in, int min_index, int max_index, struct TreeNode* parent);

enum RESULT_TREE tree_init(unsigned int default_root, char ** result_desc){

	uint8_t buffer[LENGTH_READ_BUFFER] = {0};

	size_t read_length;

	if( access(FILE_STATS_BIN, F_OK ) == -1 ) {
		create_root(default_root);
		*result_desc = "   Node tree. Successful initialization";
		return T_OK;

	}

	read_length = read_buffer(fopen (FILE_STATS_BIN, "r"), LENGTH_READ_BUFFER, buffer);

	TreeArrayed * tree_arrayed_out;

	tree_arrayed_out = tree_arrayed__unpack(NULL, read_length, buffer);

	set_root(restore(tree_arrayed_out));

	*result_desc = "   Node tree. Successful initialization";

	return T_OK;
}

static size_t read_buffer(FILE * pFile, unsigned int max_length, uint8_t * out){

	size_t cur_len = 0;
	size_t nread;

	while((nread = fread(out + cur_len, 1, max_length - cur_len, pFile))!=0){

		cur_len += nread;

		if (cur_len == max_length){

		  fprintf(stderr, "max message length exceeded\n");
		  exit(1);
		}
	}

	return cur_len;
}

static struct TreeNode* restore(TreeArrayed * ta){

	struct TreeNode * root = malloc(sizeof(struct TreeNode));

	root->parent = NULL;
	root->ip = ta->nodes[ta->n_nodes/2]->ip;
	root->count = ta->nodes[ta->n_nodes/2]->count;
	root->color = BLACK;
	root->left = NULL;
	root->right = NULL;

	root->left = construct_left(ta->nodes, 0, ta->n_nodes/2, root);

	root->right = construct_right(ta->nodes, (ta->n_nodes/2)+1, ta->n_nodes, root);

	return root;
}

static struct TreeNode* construct_left(Node** nodes_in, int min_index, int max_index, struct TreeNode* parent){

	int middle = 0;

	struct TreeNode * node = NULL;

	if(min_index == max_index){

		return NULL;
	}

	middle = min_index + ((max_index - min_index)/2);

	node = malloc(sizeof(struct TreeNode));
	node->ip = nodes_in[middle]->ip;
	node->count = nodes_in[middle]->count;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	node->color = (parent->color == BLACK) ? RED : BLACK;


	node->left = construct_left(nodes_in, min_index, middle, node);
	node->right = construct_right(nodes_in, middle + 1, max_index, node);

	return node;
}

static struct TreeNode* construct_right(Node** nodes_in, int min_index, int max_index, struct TreeNode* parent){

	int middle = 0;

	struct TreeNode * node = NULL;

	if(min_index == max_index){

		return NULL;
	}

	middle = min_index + ((max_index - min_index)/2);

	node = malloc(sizeof(struct TreeNode));
	node->ip = nodes_in[middle]->ip;
	node->count = nodes_in[middle]->count;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	node->color = (parent->color == BLACK) ? RED : BLACK;

	node->left = construct_left(nodes_in, min_index, middle, node);
	node->right = construct_right(nodes_in, middle + 1, max_index, node);

	return node;
}

