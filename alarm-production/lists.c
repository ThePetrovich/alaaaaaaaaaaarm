/*
 * lists.c
 * 
 * Created: 14.02.2021 09:10:04
 * Author: ThePetrovich
 */


#include "lists.h"
#include <stddef.h>

void sched_listAddBack(sLinkedList_t* list, sLinkedListItem_t* item)
{
	if (list != NULL && item != NULL) {
		item->next = NULL;
		item->prev = list->tail;

		if (list->tail != NULL) {
			list->tail->next = item;
		}

		list->tail = item;

		if (list->head == NULL) {
			list->head = item;
		}

		item->list = list;
	}
	return;
}

void sched_listDropBack(sLinkedList_t* list)
{
	if (list != NULL) {
		if (list->tail != NULL) {
			sLinkedListItem_t* next;

			next = list->tail;
			list->tail = list->tail->prev;

			if (list->tail != NULL) {
				list->tail->next = NULL;
			}

			if (next == list->head) {
				list->head = NULL;
			}

			next->list = NULL;
		}
	}
	return;
}

void sched_listAddFront(sLinkedList_t* list, sLinkedListItem_t* item)
{
	if (list != NULL && item != NULL) {
		item->next = list->head;
		item->prev = NULL;

		if (list->head != NULL) {
			list->head->prev = item;
		}

		list->head = item;

		if (list->tail == NULL) {
			list->tail = item;
		}

		item->list = list;
	}
	return;
}

void sched_listDropFront(sLinkedList_t* list)
{
	if (list != NULL) {
		if (list->head != NULL) {
			sLinkedListItem_t* prev;

			prev = list->head;
			list->head = list->head->next;

			if (list->head != NULL) {
				list->head->prev = NULL;
			}

			if (prev == list->tail) {
				list->tail = NULL;
			}

			prev->list = NULL;
		}
	}
	return;
}

void sched_listDeleteAny(sLinkedList_t* list, sLinkedListItem_t* item)
{
	if (list != NULL && item != NULL) {
		if (list->head == item) {
			sched_listDropFront(list);
		}
		else {
			if (list->tail == item) {
				sched_listDropBack(list);
			}
			else {
				if (item->next != NULL) {
					item->next->prev = item->prev;
				}

				if (item->prev != NULL) {
					item->prev->next = item->next;
				}
			}
		}
		item->list = NULL;
	}

	return;
}