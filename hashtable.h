/*
 * =====================================================================================
 *
 *       Filename:  hashtable.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2016 14:36:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  azalea, 
 *   Organization:  
 *
 * =====================================================================================
 */
#pragma once

#include "list.h"

struct hashtable_info {
	struct list_head *ptab;
	size_t nmemb;
	
	/*哈希函数, key --> val*/
	size_t (*hash)(const struct list_head *pnode);
	/*哈希值的对比函数*/
	int (*hash_cmp)(const struct list_head *a, 
			const struct list_head *b);
	/*根据hash函数向Hash表中存放数据*/
	void (*push)(struct list_head *pnode, struct hashtable_info *info);
	/*查找*/
	struct list_head *(*find)(const struct list_head *key, struct hashtable_info *info);
	/*删除*/
	int (*del)(struct list_head *pnode, 
			struct hashtable_info *info);
};

int hash_table_init(struct hashtable_info *info,
		size_t nmemb, 
		size_t (*hash)(const struct list_head *a), 
		int (*hash_cmp)(const struct list_head *a, 
				const struct list_head *b));

int hash_table_destroy(struct hashtable_info *info);

