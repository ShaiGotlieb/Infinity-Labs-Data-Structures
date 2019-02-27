#include <stdlib.h> /* free, malloc, size_t */

#include "ip.h"
#include "trie.h"

typedef enum{LEFT = 0, RIGHT = 1 } DIRECTION;

struct node_s 
{ 
    node_t *children[2]; 
    node_t *parent;
    int is_used;
}; 

struct trie_s
{
    node_t *root;
    int depth;

};

static int GetNextDirection(ip_t requested_ip_address, int bit_index);
static int IsRightChild(node_t *node);
static void Destroy(node_t *node);
static void DestroyNode(node_t *node);
static void InsertNetworkAndBroadcastIP(node_t *root, int host_size);

trie_t *TrieCreate(int host_size)
{
    trie_t *trie = NULL;

    trie = (trie_t*)malloc(sizeof(trie_t));
    if (NULL == trie)
    {
        return (NULL);
    }

    trie->root = CreateNode(NULL, NULL, NULL);
    if (NULL == trie->root)
    {
        free(trie);
        trie = NULL;

        return (NULL);
    }

    trie->depth = host_size;
    InsertNetworkAndBroadcastIP(trie->root, host_size);

    return (trie);
}

node_t *CreateNode(node_t *parent_node, node_t *left_child, node_t *right_child) 
{ 
    node_t *node = NULL; 
  
    node = (node_t *)malloc(sizeof(node_t)); 
    if (NULL == node) 
    { 
        return (NULL);
    } 

    node->parent = parent_node;
    node->children[LEFT] = left_child;
    node->children[RIGHT] = right_child;
    node->is_used = 0;

    return (node); 
} 

void TrieDestroy(trie_t *trie)
{
    Destroy(trie->root);
    
    free(trie);
    trie = NULL;
}

node_t *FindNode(trie_t *trie, ip_t ip_address)
{
    node_t *current_node = trie->root;
    int index = trie->depth - 1;
    DIRECTION direction = LEFT;

    while (index >= 0)
    {
        direction = GetNextDirection(ip_address, index);
        current_node = current_node->children[direction];
        index--;

        if (NULL == current_node)
        {
            return (NULL);
        }
    }

    return (current_node);
}

int TrieCountUsedLeaves(node_t *node)
{
    if (NULL == node)
    {
        return (0);
    }

    if (NULL == node->children[LEFT] && NULL == node->children[RIGHT] && node->is_used)
    {
        return (1);
    }
    else
    {
        return (TrieCountUsedLeaves(node->children[LEFT]) + TrieCountUsedLeaves(node->children[RIGHT]));
    }
}

static void Destroy(node_t *node)
{
    if (NULL != node)
    {
        Destroy(node->children[LEFT]);
        Destroy(node->children[RIGHT]);
        DestroyNode(node);
    }
}

static void DestroyNode(node_t *node)
{
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->parent = NULL;
    free(node);
    node = NULL;
}
  
static void InsertNetworkAndBroadcastIP(node_t *root, int host_size) 
{ 
    int level; 
  
    node_t *node_runner_left = root; 
    node_t *node_runner_right = root; 
  
    for (level = 0; level < host_size; level++) 
    { 
        node_runner_left->children[LEFT] = CreateNode(node_runner_left, NULL, NULL); 
        node_runner_left = node_runner_left->children[LEFT]; 
        node_runner_right->children[RIGHT] = CreateNode(node_runner_right, NULL, NULL); 
        node_runner_right = node_runner_right->children[RIGHT]; 
    } 
    
    node_runner_left->is_used = 1;
    node_runner_right->is_used = 1;
}  
  
int GetPath(trie_t *trie, ip_t requested_ip_address) 
{ 
    int level; 
    int depth = trie->depth; 
    int bit_index = depth - 1;
    node_t *current_node = trie->root;
    DIRECTION direction = GetNextDirection(requested_ip_address, bit_index);

    for (level = 0; level < depth; level++) 
    {      
        if (NULL == current_node->children[direction]) 
        {
            current_node->children[direction] = CreateNode(current_node, NULL, NULL);
        }
        else if (TRUE == current_node->children[direction]->is_used)
        {
            return (FAILURE); 
        }

        direction = GetNextDirection(requested_ip_address, bit_index); /* maybe unnecesarry */

        if (NULL == current_node->children[direction])
        {
            current_node->children[direction] = CreateNode(current_node, NULL, NULL);
        }

        current_node = current_node->children[direction];
        bit_index--;
        direction = GetNextDirection(requested_ip_address, bit_index);
    } 

    TrieUpdateUsedNodes(trie, current_node, TRUE);

    return (SUCCESS); 
}

node_t *GetNextFreeNode(trie_t *trie)
{
    node_t *current_node = trie->root;
    int i;
    int depth = trie->depth;
    int direction = LEFT;

    if (IsTrieFull(trie))
    {
        return (NULL);
    }

    for (i = 0; i < depth; ++i)
    {
        if (NULL == current_node->children[LEFT])
        {
            current_node->children[LEFT] = CreateNode(current_node, NULL, NULL);
            direction = LEFT;
        }
        else if(TRUE == current_node->children[LEFT]->is_used)
        {
             direction = RIGHT;
        }
        else
        {
            direction = LEFT;
        }

        if (NULL == current_node->children[direction])
        {
            current_node->children[direction] = CreateNode(current_node, NULL, NULL);
        }

        current_node = current_node->children[direction];
    }

    TrieUpdateUsedNodes(trie, current_node, TRUE);

    return (current_node);
}

int IsTrieFull(trie_t *trie)
{
    if (trie->root->children[LEFT]->is_used && trie->root->children[RIGHT]->is_used)
    {
        return (TRUE);
    }

    return (FALSE);
}

static int GetNextDirection(ip_t requested_ip_address, int bit_index)
{
    return (IpIsBitOn(requested_ip_address, bit_index));
} 

unsigned char *SetPath(trie_t *trie, node_t *node, ip_t ip_address)
{
    node_t *current_node = node;
    int index = 0;

    while (trie->root != current_node->parent)
    {
        if (IsRightChild(current_node))
        {
            ip_address = IpSetBitOn(ip_address, index);
        }
        else
        {
            ip_address = IpSetBitOff(ip_address, index);
        }

        index++;    
        current_node = current_node->parent;
    }

    return (ip_address);
}

static int IsRightChild(node_t *node)
{
    if (node->parent->children[RIGHT] == node)
    {
        return (TRUE);
    }

    return (FALSE);
}

void TrieUpdateUsedNodes(trie_t *trie, node_t *node, int is_used)
{
    node->is_used = is_used;

    while (node != trie->root)
    {
        if ((NULL != node->parent->children[LEFT])  && 
            (NULL != node->parent->children[RIGHT]) && 
            node->parent->children[LEFT]->is_used   && 
            node->parent->children[RIGHT]->is_used)
        {
            node->parent->is_used = TRUE;
        }
        else
        {
            node->parent->is_used = FALSE;
        }

        node = node->parent;
    }
}

int TrieCountFree(trie_t *trie)
{
    return (TrieCountUsedLeaves(trie->root));
} 