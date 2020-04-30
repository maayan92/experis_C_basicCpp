#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

#define IS_NOT_EXIST(_pers) (NULL == _pers || (*_pers).m_MagicNumber != MAGIC_NUMBER)

struct Person
{
	size_t m_MagicNumber;
	size_t m_id;
	char m_name[LENGTH];
	size_t m_age;
	Person *m_next; 
};

Person* CreatePerson(size_t _id, char *_name, size_t _age)
{
	Person *newPers;

	if(NULL == _name)
	{
		return NULL;
	}

	newPers = (Person *)malloc(sizeof(Person));

	if(NULL == newPers)
	{
		return NULL;
	}

	newPers->m_id = _id;
	strcpy(newPers->m_name,_name);
	newPers->m_age = _age;
	newPers->m_next = NULL;
	newPers->m_MagicNumber = MAGIC_NUMBER;
	
	return newPers;
}

static void DestroyPerson(Person *_head)
{
	_head->m_MagicNumber = NO_MAGIC_NUMBER;
	free(_head);
	_head = NULL;
}

void DestroyListR(Person *_head)
{
	if(IS_NOT_EXIST(_head))
	{
		return;	
	}

	DestroyListR(_head->m_next);
	DestroyPerson(_head);
}

Person* ListInsertHead(Person *_head, Person *_newPers)
{
	if(IS_NOT_EXIST(_newPers))
	{
		return _head;
	}

	_newPers->m_next = _head;

	return _newPers;
}

Person* RemoveHead(Person *_head, Person **_item)
{
	if(IS_NOT_EXIST(_head))
	{
		return NULL;
	}

	if(NULL == _item)
	{
		return _head;
	}

	*_item = _head;
	_head = _head->m_next;
	(*_item)->m_next = NULL;

	return _head;
}

static Person* FindPosition(Person* _head, size_t _key, Person* _p)
{
	Person *temp = _head;
	
	while(!IS_NOT_EXIST(temp->m_next) && temp->m_next->m_id < _key)
	{
		temp = temp->m_next;
	}

	if(IS_NOT_EXIST(temp->m_next) && temp->m_id < _key)
	{
		temp->m_next = _p;
		return _head;
	}

	return temp;
}

Person* ListInsertByKey(Person* _head, size_t _key, Person* _p)
{
	Person *temp;

	if(IS_NOT_EXIST(_p))
	{
		return _head;
	}

	if(IS_NOT_EXIST(_head) || _head->m_id > _key)
	{
		return ListInsertHead(_head,_p);
	}

	if((temp = FindPosition(_head,_key,_p)) == _head)
	{
		return _head;
	}

	if(temp->m_next->m_id != _key)
	{
		_p->m_next = temp->m_next;
		temp->m_next = _p;
	}

	return _head;
}

Person* ListInsertByKeyRec(Person* _head, size_t _key, Person* _p)
{
	Person *temp;

	if(IS_NOT_EXIST(_head) || _head->m_id > _key)
	{
		return ListInsertHead(_head,_p);
	}
	
	if(_key == _head->m_id)
	{
		return _head;
	}

	temp = ListInsertByKeyRec(_head->m_next,_key,_p);

	if(temp->m_next == _head->m_next)
	{
		_head->m_next = _p;
	}

	return _head;
}

Person* ListRemoveByKey(Person* _head, size_t _key, Person* *_p)
{
	Person *temp;

	if(IS_NOT_EXIST(_head))
	{
		return _head;
	}

	if(_head->m_id == _key)
	{
		return RemoveHead(_head,_p);
	}

	temp = _head;

	while(!IS_NOT_EXIST(temp->m_next) && temp->m_next->m_id < _key)
	{
		temp = temp->m_next;
	}

	if(!IS_NOT_EXIST(temp->m_next) && temp->m_next->m_id == _key)
	{
		*_p = temp->m_next;
		temp->m_next = (*_p)->m_next;
		(*_p)->m_next = NULL;
	}

	return _head;
}

Person* ListRemoveByKeyRec(Person* _head, size_t _key, Person**_p)
{
	Person *temp;

	if(IS_NOT_EXIST(_head))
	{
		return _head;
	}
	
	if(_head->m_id == _key)
	{
		return RemoveHead(_head,_p);
	}

	temp = ListRemoveByKeyRec(_head->m_next,_key,_p);

	if(!IS_NOT_EXIST(*_p) && (*_p)->m_id == _key && (IS_NOT_EXIST(temp) || temp->m_id > _key))
	{
		_head->m_next = temp;
	}

	return _head;
}

void PrintListR(Person *_head)
{
	if(IS_NOT_EXIST(_head))
	{
		return;
	}

	printf("\nperson: \n");
	printf("name: %s \nage: %ld \nid: %ld \n",_head->m_name, _head->m_age,_head->m_id);

	PrintListR(_head->m_next);
}

