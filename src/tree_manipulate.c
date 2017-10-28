/*
 * tree_mainpulate.c
 *
 *  Created on: Oct 23, 2017
 *      Author: soierr
 */
#include <tree_init.h>

static struct TreeNode * root;

static struct TreeNode * node_local;

static struct TreeNode * node_previous;

static struct TreeNode * node_created;

static struct TreeNode ** node_branch;

static void rotate_left(struct TreeNode * node);

static void rotate_right(struct TreeNode * node);

static void insert_fixup(struct TreeNode * node);

static void inorder_traversal(struct TreeNode * root, struct TreeStats * ts);

void create_root(unsigned int ip_in){

	root = malloc(sizeof(struct TreeNode));
	root->count = 1;
	root->color = BLACK;
	root->ip = ip_in;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;

}

void set_root(struct TreeNode * root_in){

	root = root_in;
}

struct TreeNode * get_root(){

	return root;
}

void insert_node(unsigned int ip_in){

	node_local = root;

	do{

		node_previous = node_local;

		if(ip_in > node_local->ip){

			node_branch = &(node_local->right);
			node_local = node_local->right;

		}else if(ip_in < node_local->ip){

			node_branch = &(node_local->left);
			node_local = node_local->left;

		}else{

			node_local->count++;
			return;
		}

	}while(node_local != NULL);

	node_created = malloc(sizeof(struct TreeNode));

	node_created->ip = ip_in;

	*node_branch = node_created;
	node_created->color = RED;
	node_created->parent = node_previous;
	node_created->left = NULL;
	node_created->right = NULL;
	node_created->count = 1;

	if(node_previous->color != BLACK){

		insert_fixup(node_created);
	}

}

unsigned int get_count(unsigned int ip_in){

	node_local = root;

	do{

		node_previous = node_local;

		if(ip_in > node_local->ip){

			node_branch = &(node_local->right);
			node_local = node_local->right;

		}else if(ip_in < node_local->ip){

			node_branch = &(node_local->left);
			node_local = node_local->left;

		}else{

			return node_local->count;
		}

	}while(node_local != NULL);

	return 0;
}

static void insert_fixup(struct TreeNode * node){

	struct TreeNode * parent = node->parent->parent;

	while(node->parent != NULL && node->parent->color == RED){

		if(parent->left == node->parent){

			if(parent->right != NULL && parent->right->color == RED){

				node->parent->color = BLACK;
				parent->right->color = BLACK;
				parent->color = RED;
				node = node->parent->parent;
				parent = (node->parent != NULL) ? node->parent->parent : parent;
				continue;

			}else if(node->parent->right == node){

				struct TreeNode * p = NULL;

				p = node->parent;

				rotate_left(node);

				node = p;
				parent = (node->parent != NULL) ? node->parent->parent : parent;

			}else if(node->parent->parent->right == NULL || node->parent->parent->right->color == BLACK){

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotate_right(node->parent);

			}else{

				printf("Inside while. Not defined else");
			}


		}else if(parent->right == node->parent){

			if(parent->left != NULL && parent->left->color == RED){

				node->parent->color = BLACK;
				parent->left->color = BLACK;
				parent->color = RED;
				node = node->parent->parent;
				parent = (node->parent != NULL) ? node->parent->parent : parent;
				continue;

			}else if(node->parent->left == node){

				struct TreeNode * p = NULL;

				p = node->parent;

				rotate_right(node);

				node = p;
				parent = (node->parent != NULL) ? node->parent->parent : parent;

			}else if(node->parent->parent->left == NULL || node->parent->parent->left->color == BLACK){

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotate_left(node->parent);

			}else{

				printf("Inside while. Not defined else");
			}


		}else{

			printf("Insert_fixup. Not defined if");
		}

	}

	root->color = BLACK;

}

struct TreeStats * get_stats(){

	static struct TreeStats ts;

	struct TreeNode * root = get_root();

	ts.min_count_ip = root->ip;
	ts.min_count = root->count;

	ts.total_ip = 0;

	inorder_traversal(root, &ts);

	return &ts;
}

static void inorder_traversal(struct TreeNode * node, struct TreeStats * ts){

	if(node->left){
		inorder_traversal(node->left, ts);
	}

	ts->total_ip++;

	if(ts->max_count < node->count){
		ts->max_count = node->count;
		ts->max_count_ip = node->ip;
	}else if(ts->min_count > node->count){
		ts->min_count = node->count;
		ts->min_count_ip = node->ip;
	}else if(ts->min_count == node->count){
		ts->min_count_ip = node->ip;
	}

	if(node->right){
		inorder_traversal(node->right, ts);
	}


}

/*Introduction to Algorithms. Second Edition. Example: Fig. 13.2, p. 278*/
/*Reference is for helping to visualize the process of rotation*/
/* Input y */
static void rotate_left(struct TreeNode * node){

	struct TreeNode * y = node;

	struct TreeNode * x = node->parent;

	struct TreeNode * parent;

	parent = (node->parent->parent == NULL) ? NULL : node->parent->parent;

	x->right = y->left;
	(y->left != NULL) ? y->left->parent = x : NULL;

	if(root != x){

		if(x == parent->left){

			 parent->left = y;

		}else{

			parent->right = y;
		}

	}else{

		root = y;
	}


	y->parent = x->parent;

	y->left = x;
	x->parent = y;

}

/*Introduction to Algorithms. Second Edition. Example: Fig. 13.2, p. 278*/
/*Reference is for helping to visualize the process of rotation*/
/* Input x */
static void rotate_right(struct TreeNode * node){

	struct TreeNode * x = node;

	struct TreeNode * y = node->parent;

	struct TreeNode * parent;

	parent = (node->parent->parent == NULL) ? NULL : node->parent->parent;

	y->left = x->right;
	(x->right != NULL) ? x->right->parent = y : NULL;

	if(root != y){

		if(y == parent->left){

			 parent->left = x;

		}else{

			parent->right = x;
		}

	}else{

		root = x;
	}

	x->parent = y->parent;

	x->right = y;
	y->parent = x;

}
