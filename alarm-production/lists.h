/*
 * lists.h
 * 
 * Created: 02.01.2021 11:58:18
 * Author: ThePetrovich
 */


#ifndef SCHED_LISTS_H_
#define SCHED_LISTS_H_

#define sched_LISTITEM_STRUCT_SIZE (sizeof(struct sListItemStruct_t))

typedef struct sLinkedListStruct_t sLinkedList_t;
typedef struct sListItemStruct_t sLinkedListItem_t;

struct sJobStruct_t;

struct sLinkedListStruct_t
{
    sLinkedListItem_t* head;
    sLinkedListItem_t* tail;
};

struct sListItemStruct_t
{
    sLinkedList_t* list;
    sLinkedListItem_t* next;
    sLinkedListItem_t* prev;
    struct sJobStruct_t* data;
};

#ifdef __cplusplus
extern "C" {
#endif

void sched_listAddBack(sLinkedList_t* list, sLinkedListItem_t* item);
void sched_listAddFront(sLinkedList_t* list, sLinkedListItem_t* item);
void sched_listDropBack(sLinkedList_t* list);
void sched_listDropFront(sLinkedList_t* list);
void sched_listDeleteAny(sLinkedList_t* list, sLinkedListItem_t* item);

#ifdef __cplusplus
}
#endif

#endif
