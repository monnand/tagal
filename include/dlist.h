#ifndef __VOILA_DOUBLY_LINKED_LIST_H
#define __VOILA_DOUBLY_LINKED_LIST_H

#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif


/*!\file dlist.h
 * \brif Simple doubly linked list implementation
 *
 * Nearly an exactly copy from Linux kernel. 
 * Read Linux kernel's code: $KERNEL/include/linux/list.h for details
 */

typedef struct dlist_head {
	struct dlist_head *next, *prev;
}dlist_head_t;

/*!\fn dlist_head_init
 * Initialise a list head
 */
static inline void dlist_head_init(dlist_head_t *list)
{
	list->next = list;
	list->prev = list;
}

/*!\fn __dlist_add
 * Insert a new entry between two know consecutive entries.
 */
static inline void __dlist_add(dlist_head_t *item,
			dlist_head_t *prev,
			dlist_head_t *next)
{
	next->prev = item;
	item->next = next;
	item->prev = prev;
	prev->next = item;
}

/*!\fn dlist_add
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 * \param item entry to be added
 * \param head list head to add it after
 */
static inline void dlist_add(dlist_head_t *item,dlist_head_t *head)
{
	__dlist_add(item,head,head->next);
}

/*!\fn dlist_add_tail
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 * \param item new entry to be added
 * \param head list head to add it before
 */
static inline void dlist_add_tail(dlist_head_t *item,dlist_head_t *head)
{
	__dlist_add(item,head->prev,head);
}

/*!\fn __dlist_del
 * Delete a list entry by making the prev/next entries
 * point to each other.
 */
static inline void __dlist_del(dlist_head_t *prev,dlist_head_t *next)
{
	next->prev = prev;
	prev->next = next;
}

/*!\fn dlist_del
 * Deletes entry from list.
 * \param entry the element to delete from the list.
 */
static inline void dlist_del(dlist_head_t *entry)
{
	__dlist_del(entry->prev,entry->next);
	entry->next = entry->prev = NULL;
}

/*!\fn dlist_is_empty
 * \return true if the list is empty. 0 on otherwise
 */
static inline int dlist_is_empty(dlist_head_t *head)
{
	return head->next == head;
}

#ifndef dlist_entry
#define	dlist_entry(ptr,type,member)	\
	((type *)((char *)(ptr) - (char *)(&((type *)0)->member)))
#endif /* dlist_entry */

#ifndef dlist_for_each
#define	dlist_for_each(pos,head)	\
	for((pos)=((head)->next);(pos)!=(head);(pos)=((pos)->next))
#endif /* dlist_for_each */

#ifdef	__cplusplus
}
#endif

#endif /* __VOILA_DOUBLY_LINKED_LIST_H */

