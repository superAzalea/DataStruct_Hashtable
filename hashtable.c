/*
 * =====================================================================================
 *
 *       Filename:  hashtable.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2016 14:47:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  azalea, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include <assert.h>

/*根据hash函数向Hash表中存放数据*/
void hashtable_push(struct list_head *pnode, 
			struct hashtable_info *info)
{
	assert(pnode != NULL);
	assert(info != NULL);

	size_t val = info->hash(pnode) % info->nmemb;

	list_add_tail(pnode, info->ptab + val);
}
/*查找*/
struct list_head *hashtable_find(const struct list_head *key, struct hashtable_info *info)
{
	assert(key != NULL);
	assert(info != NULL);

	size_t val = info->hash(key) % info->nmemb;
	
	/*static 局部变量初始化时需要一个常量*/
	static struct  list_head *cur = NULL;
	/*cur 只会被初始化一次，所以首次时，cur等于头结点*/
	if (cur == NULL || !info->hash_cmp(cur, key)) {
		cur = info->ptab + val;
	}

	list_for_each_continue(cur, info->ptab + val) {
		if (info->hash_cmp(cur, key)) {
			return cur;
		}
	}

	return NULL;
}
/*删除*/
int hashtable_del(struct list_head *pnode,
			struct hashtable_info *info)
{
	return 0;
}

int hash_table_init(struct hashtable_info *info,
			size_t nmemb,
		size_t (*hash)(const struct list_head *a),
		int (*hash_cmp)(const struct list_head *a,
			const struct list_head *b))
{
	assert(info != NULL);
	assert(hash != NULL);
	assert(hash_cmp != NULL);

	info->ptab = (struct list_head *)
		malloc(sizeof(struct list_head) * nmemb);

	assert(info->ptab != NULL);

	int i;
	for (i = 0; i < nmemb; ++i) {
		list_head_init(info->ptab + i);
	}
	
	info->nmemb = nmemb;
	info->hash = hash;
	info->hash_cmp = hash_cmp;
	info->push = hashtable_push;
	info->find = hashtable_find;
	info->del =  hashtable_del;

	return 0;
}

int hash_table_destroy(struct hashtable_info *info)
{

	int i;
	for (i = 0; i < info->nmemb; ++i) {
		struct list_head *cur = NULL;
		struct list_head *Next = NULL;

		list_for_each_safe(cur, Next, info->ptab + i) {
			list_del_init(cur); 

			//free(cur);
		}

	}

	free(info->ptab);

	return 0;
}



