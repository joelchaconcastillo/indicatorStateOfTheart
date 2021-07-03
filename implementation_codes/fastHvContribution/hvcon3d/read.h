#ifndef _WFG_H_
#define _WFG_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* User supplied function to compare two items like strcmp() does.
 * For example: cmp(a,b) will return:
 *   -1  if a < b
 *    0  if a = b
 *    1  if a > b
 */
typedef int (*avl_compare_t)(const void *, const void *);

/* User supplied function to delete an item when a node is free()d.
 * If NULL, the item is not free()d.
 */
typedef void (*avl_freeitem_t)(void *);

typedef struct avl_node_t {
	struct avl_node_t *next;
	struct avl_node_t *prev;
	struct avl_node_t *parent;
	struct avl_node_t *left;
	struct avl_node_t *right;
	void *item;
	unsigned int count;
	unsigned char depth;
} avl_node_t;

typedef struct avl_tree_t {
	avl_node_t *head;
	avl_node_t *tail;
	avl_node_t *top;
	avl_compare_t cmp;
	avl_freeitem_t freeitem;
} avl_tree_t;


typedef double OBJECTIVE;

typedef struct
{
	OBJECTIVE *objectives;
        struct avl_node_t * tnode;
} POINT;

typedef struct
{
	int nPoints;
	int n;
	POINT *points;
} FRONT;

typedef struct
{
        FRONT sprime;   // reduced front 
        int id;         // index in the original list 
        int k;          // next segment to be evaluated 
        double partial; // volume so far 
        int left;       // left child in the heap 
        int right;      // right child in the heap 
} JOB;

typedef struct
{
	int nFronts;
	FRONT *fronts;
} FILECONTENTS;

FILECONTENTS *readFile(char[]);

extern void printContents(FILECONTENTS *);




#endif
