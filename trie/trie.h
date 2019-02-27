#ifndef __H__TRIE__
#define __H__TRIE__



typedef struct trie_s trie_t;
typedef struct node_s node_t;

trie_t *TrieCreate(int host_size);
/********************************************************************
 * TrieCreate - creates trie_t
 *
 * host_size - the host size in bits.
 *
 * Returns - a pointer to the trie_t.
 *******************************************************************/
node_t *CreateNode(node_t *parent_node, node_t *left_child, node_t *right_child);
void TrieDestroy(trie_t *trie);
node_t *FindNode(trie_t *trie, ip_t ip_address);
int TrieCountUsedLeaves(node_t *node);
int TrieCountFree(trie_t *trie);
int GetPath(trie_t *trie, ip_t requested_ip_address);
node_t *GetNextFreeNode(trie_t *trie);
unsigned char *SetPath(trie_t *trie, node_t *node, ip_t ip_address);
void TrieUpdateUsedNodes(trie_t *trie, node_t *node, int is_used);
int IsTrieFull(trie_t *trie);

#endif