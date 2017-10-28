/*
 * tree_save.h
 *
 *  Created on: Oct 26, 2017
 *      Author: soierr
 */

#ifndef TREE_SAVE_H_
#define TREE_SAVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

#include <unistd.h>

#include "proto/node.pb-c.h"

#include "tree_init.h"

enum RESULT_TREE tree_save(char ** result_desc);

#endif /* TREE_SAVE_H_ */
