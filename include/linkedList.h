#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdio.h>
#include "ADTErrors.h"

#define LENGTH 128

typedef struct Person Person;

/*
	Description: create a new person.
	Input: _id , _name , _age - the person's details, _id and _age should be positive.
	Return value: return a pointer to the new person, or NULL if the allocation failed.
*/
Person* CreatePerson(size_t _id, char *_name, size_t _age);

/*
	Description: destroying all the persons in the list, in recursion,  after calling this function the head pointer should be reset with NULL.
	Input: _head - the head pointer of the list.
	Return value: nothing returns.

*/
void DestroyListR(Person *_head);

/*
	Description: insert a new person to the head of the list (can't be used with insert/remove by key).
	Input: _head - the head pointer of the list, _newPers - the new person that would be inserted, if its not NULL.
	Return value: return a pointer to the head of the list, or NULL if _newPers and the head are NULL.
*/
Person* ListInsertHead(Person *_head, Person *_newPers);

/*
	Description: remove the head of the list (can't be used with insert/remove by key).
	Input: _head - the head pointer of the list, _item - a pointer to the head that will be removed, NULL if the _head is NULL.
	Return value: return a pointer to the head of the list, or NULL if _head is NULL.
*/
Person* RemoveHead(Person *_head, Person **_item);

/*
	Description: insert new person by its key value, if the key is not in the list already, or if _p NULL (can't be used with insert/remove to head).
	Input: _head - the head pointer of the list, _key - the location where the new person will inserted to, should be positive.
		_p - the new person.
	Return value: return a pointer to the the head of the list.
*/
Person* ListInsertByKey(Person* _head, size_t _key, Person* _p);

/*
	Description: insert new person by its key value, in recursion, if the key is not in the list already, or if _p NULL (can't be used with insert/remove to head).
	Input: _head - the head pointer of the list, _key - the location where the new person will inserted to, should be positive.
		_p - the new person.
	Return value: return a pointer to the the head of the list.
*/
Person* ListInsertByKeyRec(Person* _head, size_t _key, Person* _p);

/*
	Description: remove person by a key (can't be used with insert/remove to head).
	Input: _head - the head pointer of the list, _key - the location of the person that would be removed,
		_p - pointer to the removed person, NULL if the key doesn't exist in the list, or if the _head is NULL.
	Return value: return a pointer to the head of the list, or NULL if _head is NULL.
*/
Person* ListRemoveByKey(Person* _head, size_t _key, Person* *_p);

/*
	Description: remove person by a key, in recursion (can't be used with insert/remove to head).
	Input: _head - the head pointer of the list, _key - the location of the person that would be removed,
		_p - pointer to the removed person, NULL if the key doesn't exist in the list, or if the _head is NULL.
	Return value: return a pointer to the head of the list, or NULL if _head is NULL.
*/
Person* ListRemoveByKeyRec(Person* _head, size_t _key, Person**_p);

/*
	Description: prints the persons list.
	Input: _head - the head pointer of the list.
	Return value: nothing returns.
*/
void PrintListR(Person *_head);

#endif
