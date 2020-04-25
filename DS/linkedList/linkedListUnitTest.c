#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

typedef struct Details
{
	size_t m_id;
	size_t m_age;
	char m_name[50];

}Details;

/* CREATE PERSON */

Result TestCreatePerson()
{
	Person *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);
	if(NULL == newPerson)
	{
		return FAILED;
	}

	return SUCCEDD;
}

/* DESTROY PERSONS */

Result TestDestroyPerson()
{
	Person *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);
	if(NULL == newPerson)
	{
		return FAILED;
	}

	DestroyListR(newPerson);

	return SUCCEDD;
}

Result TestDestroy2Person()
{
	#define SIZE 2

	int i;
	Person *listHead = NULL, *newPerson;
	Details detailsArr[SIZE] = {{12,25,"may"},{23,5,"lia"}};

	for(i = 0;i < SIZE;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertHead(listHead,newPerson);
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	DestroyListR(listHead);

	return SUCCEDD;
}

Result TestDoubleDestroyPerson()
{
	Person *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);
	if(NULL == newPerson)
	{
		return FAILED;
	}

	DestroyListR(newPerson);
	DestroyListR(newPerson);

	return SUCCEDD;
}

/* INSERT PERSON */

Result TestInsertHead_CreatePers()
{
	#define SIZE 2

	int i;
	Person *listHead = NULL, *newPerson;
	Details detailsArr[SIZE] = {{12,25,"may"},{23,5,"lia"}};

	for(i = 0;i < SIZE;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertHead(listHead,newPerson);
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	if(newPerson != listHead)
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestInsertHeadNULL()
{
	Person *listHead = NULL, *checkPerson, *newPerson;
	
	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);
	if(NULL == newPerson)
	{
		return FAILED;
	}

	listHead = ListInsertHead(listHead,newPerson);
	if(NULL == listHead)
	{
			return FAILED;
	}

	checkPerson = ListInsertHead(listHead,NULL);
	if(checkPerson == listHead)
	{
		return SUCCEDD;
	}

	return FAILED;
}

/* REMOVE PERSON */

Result TestRemovetHead_CreatePers()
{
	#define SIZE 2

	int i;
	Person *listHead = NULL, *newPerson, *removePerson;
	Details detailsArr[SIZE] = {{12,25,"may"},{23,25,"mosh"}};

	for(i = 0;i < SIZE;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertHead(listHead,newPerson);
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	newPerson = RemoveHead(listHead,&removePerson);

	if(removePerson != listHead || newPerson == removePerson)
	{
		return FAILED;
	}

	return SUCCEDD;	
}

Result TestRemovetHeadNULL_CreatePers()
{
	Person *listHead, *removePerson;

	Details details = {12,25,"may"};

	listHead = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = RemoveHead(NULL,&removePerson);

	if(NULL == listHead)
	{
		return SUCCEDD;	
	}

	return FAILED;
}

/* INSERT BY KEY*/

Result TestInsertByKey_CreatePers()
{
	#define SIZE_K 4

	int i;
	Person *listHead = NULL, *newPerson, *removePerson;
	Person *listArr[SIZE_K];	
	Details detailsArr[SIZE_K] = {{1,25,"may"},{3,5,"lia"},{0,25,"yos"},{2,25,"mosh"}};

	for(i = 0;i < SIZE_K;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertByKey(listHead,detailsArr[i].m_id,newPerson);
		listArr[detailsArr[i].m_id] = newPerson;
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	for(i = 0;i < SIZE_K;++i)
	{
		listHead = RemoveHead(listHead,&removePerson);

		if(removePerson != listArr[i])
		{
			return FAILED;
		}	
	}
	
	return SUCCEDD;
}

Result TestInsertByKeyNULL()
{
	Person *listHead = NULL, *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListInsertByKey(newPerson,details.m_id,newPerson);

	listHead = ListInsertByKey(listHead,0,NULL);
	if(NULL == listHead)
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestInsertByKeyExist()
{
	Person *listHead = NULL, *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListInsertByKey(listHead,details.m_id,newPerson);
	if(NULL == listHead)
	{
		return FAILED;
	}
	
	listHead = ListInsertByKey(listHead,details.m_id,newPerson);
	
	if(listHead != newPerson)
	{
		return FAILED;
	}
	

	return SUCCEDD;
}

/* REMOVE BY KEY*/

Result TestRemoveByKey_CreatePer()
{
	#define SIZE_K 4

	int i;
	Person *listHead = NULL, *newPerson, *removePerson;
	Person *listArr[SIZE_K];	
	Details detailsArr[SIZE_K] = {{1,25,"may"},{3,5,"lia"},{0,25,"yos"},{2,25,"mosh"}};

	for(i = 0;i < SIZE_K;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertByKey(listHead,detailsArr[i].m_id,newPerson);
		listArr[detailsArr[i].m_id] = newPerson;
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	for(i = 0;i < SIZE_K;++i)
	{
		listHead = ListRemoveByKey(listHead,i,&removePerson);

		if(removePerson != listArr[i])
		{
			return FAILED;
		}	
	}
	
	return SUCCEDD;
}

Result TestRemoveByKeyNULL()
{
	Person *listHead, *removePerson;

	Details details = {12,25,"may"};

	listHead = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListRemoveByKey(NULL,0,&removePerson);

	if(NULL == listHead)
	{
		return SUCCEDD;	
	}

	return FAILED;
}

Result TestRemoveByKeyNotExist()
{
	Person *listHead = NULL, *newPerson, *removePerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListInsertByKey(listHead,details.m_id,newPerson);

	listHead = ListRemoveByKey(listHead,0,&removePerson);

	if(listHead == newPerson)
	{
		return SUCCEDD;
	}

	return FAILED;
}
/* INSERT BY KEY RECURSION */

Result TestInsertByKey_CreatePersR()
{
	#define SIZE_K 4

	int i;
	Person *listHead = NULL, *newPerson, *removePerson;
	Person *listArr[SIZE_K];	
	Details detailsArr[SIZE_K] = {{1,25,"may"},{3,5,"lia"},{0,25,"yos"},{2,25,"mosh"}};

	for(i = 0;i < SIZE_K;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertByKeyRec(listHead,detailsArr[i].m_id,newPerson);
		listArr[detailsArr[i].m_id] = newPerson;
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	for(i = 0;i < SIZE_K;++i)
	{
		listHead = RemoveHead(listHead,&removePerson);

		if(removePerson != listArr[i])
		{
			return FAILED;
		}	
	}
	
	return SUCCEDD;
}

Result TestInsertByKeyNULLR()
{
	Person *listHead = NULL, *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListInsertByKeyRec(newPerson,details.m_id,newPerson);

	listHead = ListInsertByKeyRec(listHead,0,NULL);
	if(NULL == listHead)
	{
		return FAILED;
	}

	return SUCCEDD;
}

Result TestInsertByKeyExistR()
{
	Person *listHead = NULL, *newPerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListInsertByKeyRec(listHead,details.m_id,newPerson);
	if(NULL == listHead)
	{
		return FAILED;
	}
	
	listHead = ListInsertByKeyRec(listHead,details.m_id,newPerson);
	
	if(listHead != newPerson)
	{
		return FAILED;
	}
	

	return SUCCEDD;
}

/* REMOVE BY KEY RECURSION */

Result TestRemoveByKey_CreatePerR()
{
	#define SIZE_K 4

	int i;
	Person *listHead = NULL, *newPerson, *removePerson;
	Person *listArr[SIZE_K];	
	Details detailsArr[SIZE_K] = {{1,25,"may"},{3,5,"lia"},{0,25,"yos"},{2,25,"mosh"}};

	for(i = 0;i < SIZE_K;++i)
	{
		newPerson = CreatePerson(detailsArr[i].m_id,detailsArr[i].m_name,detailsArr[i].m_age);
		if(NULL == newPerson)
		{
			return FAILED;
		}

		listHead = ListInsertByKeyRec(listHead,detailsArr[i].m_id,newPerson);
		listArr[detailsArr[i].m_id] = newPerson;
		if(NULL == listHead)
		{
			return FAILED;
		}
	}

	for(i = 0;i < SIZE_K;++i)
	{
		listHead = ListRemoveByKeyRec(listHead,i,&removePerson);

		if(removePerson != listArr[i])
		{
			return FAILED;
		}	
	}
	
	return SUCCEDD;
}

Result TestRemoveByKeyNULLR()
{
	Person *listHead, *removePerson;

	Details details = {12,25,"may"};

	listHead = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListRemoveByKeyRec(NULL,0,&removePerson);

	if(NULL == listHead)
	{
		return SUCCEDD;	
	}

	return FAILED;
}

Result TestRemoveByKeyNotExistR()
{
	Person *listHead = NULL, *newPerson, *removePerson;

	Details details = {12,25,"may"};

	newPerson = CreatePerson(details.m_id,details.m_name,details.m_age);

	listHead = ListInsertByKeyRec(listHead,details.m_id,newPerson);

	listHead = ListRemoveByKeyRec(listHead,0,&removePerson);

	if(listHead == newPerson)
	{
		return SUCCEDD;
	}

	return FAILED;
}

int main()
{
	Result res;
	
	/*Create person*/
	/*POS*/
	res = TestCreatePerson();
	printf("\nTestCreatePerson result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Destroy person*/
	/*POS*/
	res = TestDestroyPerson();
	printf("\nTestDestroyPerson result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestDestroy2Person();
	printf("\nTestDestroy2Person result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestDoubleDestroyPerson();
	printf("\nTestDoubleDestroyPerson result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Insert person*/
	/*POS*/
	res = TestInsertHead_CreatePers();
	printf("\nTestInsertHead_CreatePers result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestInsertHeadNULL();
	printf("\nTestInsertHeadNULL result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Remove person*/
	/*POS*/
	res = TestRemovetHead_CreatePers();
	printf("\nTestRemovetHead_CreatePers result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestRemovetHeadNULL_CreatePers();
	printf("\nTestRemovetHeadNULL_CreatePers result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Insert by key*/
	/*POS*/
	res = TestInsertByKey_CreatePers();
	printf("\nTestInsertByKey_CreatePers result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestInsertByKeyNULL();
	printf("\nTestInsertByKeyNULL result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestInsertByKeyExist();
	printf("\nTestInsertByKeyExist result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Insert by key*/
	/*POS*/
	res = TestRemoveByKey_CreatePer();
	printf("\nTestRemoveByKey_CreatePer result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestRemoveByKeyNULL();
	printf("\nTestRemoveByKeyNULL result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestRemoveByKeyNotExist();
	printf("\nTestRemoveByKeyNotExist result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Insert by key recursion*/
	/*POS*/
	res = TestInsertByKey_CreatePersR();
	printf("\nTestInsertByKey_CreatePers result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestInsertByKeyNULLR();
	printf("\nTestInsertByKeyNULL result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestInsertByKeyExistR();
	printf("\nTestInsertByKeyExist result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*Remove by key recurtion*/
	/*POS*/
	res = TestRemoveByKey_CreatePerR();
	printf("\nTestRemoveByKey_CreatePer result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	/*NEG*/
	res = TestRemoveByKeyNULLR();
	printf("\nTestRemoveByKeyNULL result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	res = TestRemoveByKeyNotExistR();
	printf("\nTestRemoveByKeyNotExist result: %s \n", (SUCCEDD == res) ? "succedded" : "failed");

	return 0;
}



