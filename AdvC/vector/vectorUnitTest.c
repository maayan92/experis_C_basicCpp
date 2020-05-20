#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "sortVector.h"

#define INI_SIZE 3
#define BLK_SIZE 2

typedef enum 
{
	SUCCESS,
	FAILED,
	LENGTH = 200
}Result;

typedef enum
{
	INT,
	CHAR,
	STRING
}Type;

union value
{
	int i_data;
	char c_data;
	char* s_data;
};

typedef struct Data
{
	Type m_type;
	union value m_val;
}Data;

static void DestroyElementsData(void* _data)
{
	free((Data *)_data);
}

void PrintElementsInt(void* _data)
{
	printf("%d \t", *(int*)_data);
}

static void PrintElementsData(void* _data)
{
	switch(((Data*)_data)->m_type)
	{
		case INT:
		
			printf("%d \t", ((Data*)_data)->m_val.i_data);
			break;
			
		case CHAR:
		
			printf("%c \t", ((Data*)_data)->m_val.c_data);
			break;
		
		default:
		
			printf("%s \t", ((Data*)_data)->m_val.s_data);
			break;
	}
}

static Bool IfToSwap(void* _a, void* _b)
{
	if(*(int*)_a > *(int*)_b)
	{
		return true;
	}
	
	return false;
}

/* CREATE VECTOR */

Result TestCreateVec_Nsize_Nblock()
{
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);

	if(vec)
	{
		VectorDestroy(vec,DestroyElementsData);
		return SUCCESS;
	}

	return FAILED;
}

Result TestCreateVec_size0_block0()
{
	Vector *vec = VectorCreate(0,0);

	if(!vec)
	{
		return SUCCESS;
	}

	VectorDestroy(vec,DestroyElementsData);
	return FAILED;
}

/* DESTROY VECTOR */

/*int values*/
Result TestDestroyVec_ValidInt()
{
	Data *data;
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	data = (Data*)malloc(sizeof(Data));
	if(!data)
	{
		return FAILED;
	}
	
	data->m_type = INT;
	data->m_val.i_data = 3;
	
	if(SUCCEEDED != VectorAddTail(vec,data))
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}
	
	VectorDestroy(vec,DestroyElementsData);
	return SUCCESS;
}

/*char values*/
Result TestDestroyVec_ValidChar()
{
	Data *data;
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	data = (Data*)malloc(sizeof(Data));
	if(!data)
	{
		return FAILED;
	}
	
	data->m_type = CHAR;
	data->m_val.c_data = 'a';
	
	if(SUCCEEDED != VectorAddTail(vec,data))
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}
	
	VectorDestroy(vec,DestroyElementsData);
	return SUCCESS;
}

/*string values*/
Result TestDestroyVec_ValidString()
{
	Data *data;
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	data = (Data*)malloc(sizeof(Data));
	if(!data)
	{
		return FAILED;
	}

	data->m_type = STRING;
	data->m_val.s_data = "abc";
	
	if(SUCCEEDED != VectorAddTail(vec,data))
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}
	
	VectorDestroy(vec,DestroyElementsData);
	return SUCCESS;
}

Result TestDestroyVec_empty()
{
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	VectorDestroy(vec,DestroyElementsData);
	return SUCCESS;
}

Result TestDestroyVec_DoubleFree()
{
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	VectorDestroy(vec,DestroyElementsData);
	VectorDestroy(vec,DestroyElementsData);

	return SUCCESS;
}

Result TestDestroyVec_NULL()
{	
	VectorDestroy(NULL,DestroyElementsData);

	return SUCCESS;
}

/* INSERT TO TAIL */

/*int values*/
Result TestAddToTail_ValidInt()
{
	Data data[INI_SIZE+2*BLK_SIZE], *rData;
	int indx =  INI_SIZE+2*BLK_SIZE;

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx--)
	{
		data[indx].m_type = INT;
		data[indx].m_val.i_data = indx;
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}
	
	VectorRemoveTail(vec,(void**)(&rData));

	if(data[++indx].m_val.i_data != (*rData).m_val.i_data)
	{
		VectorDestroy(vec,DestroyElementsData);
		return FAILED;
	}

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

/*neg*/
Result TestAddToTail_VecNULL()
{
	int data = rand()%100;

	if(ERR_NOT_INITIALIZE == VectorAddTail(NULL,&data))
	{
		return SUCCESS;
	}

	return FAILED;
}

Result TestAddToTail_DataNULL()
{
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == VectorAddTail(vec,NULL))
	{
		return SUCCESS;
	}

	return FAILED;
}

/* REMOVE FROM TAIL */

/*int values*/
Result TestRemoveFromTail_ValidInt()
{
	Data data[INI_SIZE+2*BLK_SIZE], *rData;
	int indx = 0, size = INI_SIZE+2*BLK_SIZE;
	
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx < size)
	{
		data[indx].m_type = INT;
		data[indx].m_val.i_data = indx;
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx++]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}
	
	while(indx--)
	{
		VectorRemoveTail(vec,(void**)(&rData));

		if(data[indx].m_val.i_data != (*rData).m_val.i_data)
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

/*neg*/
Result TestRemoveFromTail_VecNULL()
{
	int *rData;

	if(ERR_NOT_INITIALIZE == VectorRemoveTail(NULL,(void**)(&rData)))
	{
		return SUCCESS;
	}

	return FAILED;
}

Result TestRemoveFromTail_DataNULL()
{
	Data data;
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	data.m_type = INT;
	data.m_val.i_data = 3;
	
	if(SUCCEEDED != VectorAddTail(vec,&data))
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == VectorRemoveTail(vec,NULL))
	{
		VectorDestroy(vec,NULL);
		return SUCCESS;
	}

	VectorDestroy(vec,NULL);
	return FAILED;
}

/* SET DATA */

/*int values*/
Result TestVectorSet_ValidInt()
{
	Data data[INI_SIZE+2*BLK_SIZE], *rData, setData;
	int size, indx = size = INI_SIZE+2*BLK_SIZE;

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx--)
	{
		data[indx].m_type = INT;
		data[indx].m_val.i_data = indx;
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}
	indx = size;
	
	setData.m_type = INT;
	setData.m_val.i_data = 20;
	VectorSet(vec,indx /= 2,&setData);

	while(size > indx)
	{
		VectorRemoveTail(vec,(void**)(&rData));
		size--;
	}
	
	VectorRemoveTail(vec,(void**)(&rData));

	if(setData.m_val.i_data != (*rData).m_val.i_data)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

/*neg*/
Result TestVectorSet_VecNULL()
{
	int data = rand()%100;

	if(ERR_NOT_INITIALIZE == VectorSet(NULL,1,&data))
	{
		return SUCCESS;
	}

	return FAILED;
}

Result TestVectorSet_DataNULL()
{
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == VectorSet(vec,1,NULL))
	{
		VectorDestroy(vec,NULL);
		return SUCCESS;
	}

	VectorDestroy(vec,NULL);
	return FAILED;
}

/* GET DATA */

/*int values*/
Result TestVectorGet_ValidInt()
{
	Data data[INI_SIZE+2*BLK_SIZE], *rData;
	int indx = 0, size = INI_SIZE+2*BLK_SIZE;
	
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx < size)
	{
		data[indx].m_type = INT;
		data[indx].m_val.i_data = indx;
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx++]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}
	indx = size/2;
	VectorGet(vec,indx,(void**)(&rData));

	if(data[--indx].m_val.i_data != (*rData).m_val.i_data)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

/*neg*/
Result TestVectorGet_VecNULL()
{
	int *rData;

	if(ERR_NOT_INITIALIZE == VectorGet(NULL,1,(void**)(&rData)))
	{
		return SUCCESS;
	}

	return FAILED;
}

Result TestVectorGet_DataNULL()
{
	Data data;
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}
	
	data.m_type = INT;
	data.m_val.i_data = 3;
	
	if(SUCCEEDED != VectorAddTail(vec,&data))
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	if(ERR_ILLEGAL_INPUT == VectorGet(vec,1,NULL))
	{
		VectorDestroy(vec,NULL);
		return SUCCESS;
	}

	VectorDestroy(vec,NULL);
	return FAILED;
}

/* FIND DATA */

/*int values*/
Result TestVectorFind_ValidInt()
{
	Data data[INI_SIZE+2*BLK_SIZE];
	int ans, indx =  INI_SIZE+2*BLK_SIZE;

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx--)
	{
		data[indx].m_type = INT;
		data[indx].m_val.i_data = indx;
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}
	indx += 2;
	ans = VectorFind(vec,&data[indx]);

	if(ans != 6)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

Result TestVectorFind_VecNULL()
{
	int data = 5, ans = VectorFind(NULL,&data);

	if(ans == 0)
	{
		return SUCCESS;
	}

	return FAILED;
}

/* NUM OF ELEMENT */

/*int values*/
Result TestVectorNumOfelements_ValidInt()
{
	int data[INI_SIZE+2*BLK_SIZE];
	int size, indx = size = INI_SIZE+2*BLK_SIZE;

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx--)
	{
		data[indx] = indx;
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}

	if(VectorNumOfelements(vec) != size)
	{
		VectorDestroy(vec,NULL);
		return FAILED;
	}

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

Result TestVectorNumOfelements_VecNULL()
{
	if(VectorNumOfelements(NULL) == 0)
	{
		return SUCCESS;
	}

	return FAILED;
}

/* PRINT */

/*sort*/

Result TestBubbleSort()
{
	#define SIZE 5
	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	int i;
	int data[SIZE];
	
	if(!vec)
	{
		return FAILED;
	}
	
	for(i = 0;i < SIZE;++i)
	{
		data[i] = rand() % 50;
	
		if(SUCCEEDED != VectorAddTail(vec,&data[i]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}
	
	BubbleSort(vec,IfToSwap);
	
	printf("\nvalues: \n");
	PrintArray(vec,PrintElementsInt);
	printf("\n\n");
	VectorDestroy(vec,NULL);
	return SUCCESS;
}

/*int and char values*/
Result TestPrintAddToTail_ValidIntChar()
{
	Data data[INI_SIZE+2*BLK_SIZE];
	int indx =  INI_SIZE+2*BLK_SIZE;

	Vector *vec = VectorCreate(INI_SIZE,BLK_SIZE);
	if(!vec)
	{
		return FAILED;
	}

	while(indx--)
	{
		if(0 == indx % 2)
		{
			data[indx].m_type = INT;
			data[indx].m_val.i_data = indx;
		}
		else
		{
			data[indx].m_type = CHAR;
			data[indx].m_val.c_data = 'a'+indx;		
		}
		
		if(SUCCEEDED != VectorAddTail(vec,&data[indx]))
		{
			VectorDestroy(vec,NULL);
			return FAILED;
		}
	}

	printf("\nvalues: \n");
	PrintArray(vec,PrintElementsData);
	printf("\n\n");

	VectorDestroy(vec,NULL);
	return SUCCESS;
}

static void PrintResult(char *_str, Result(*ptrPrint)(void))
{
	printf("\n%s result: %s \n", _str, (SUCCESS == (*ptrPrint)()) ? "succedded" : "failed");
} 


int main()
{
	/*CreateVector:*/
	/*POS*/
	PrintResult("TestCreateVec_Nsize_Nblock",TestCreateVec_Nsize_Nblock);
	/*NEG*/
	PrintResult("TestCreateVec_size0_block0",TestCreateVec_size0_block0);
	
	/*DestroyVector:*/
	/*POS*/
	/*int*/
	PrintResult("TestDestroyVec_ValidInt",TestDestroyVec_ValidInt);
	/*char*/
	PrintResult("TestDestroyVec_ValidChar",TestDestroyVec_ValidChar);
	/*string*/
	PrintResult("TestDestroyVec_ValidString",TestDestroyVec_ValidString);
	/*NEG*/
	PrintResult("TestDestroyVec_empty",TestDestroyVec_empty);
	PrintResult("TestDestroyVec_DoubleFree",TestDestroyVec_DoubleFree);
	PrintResult("TestDestroyVec_NULL",TestDestroyVec_NULL);

	/*AddToTail:*/
	/*POS*/
	/*int*/
	PrintResult("TestAddToTail_ValidInt",TestAddToTail_ValidInt);
	/*NEG*/
	PrintResult("TestAddToTail_VecNULL",TestAddToTail_VecNULL);	
	PrintResult("TestAddToTail_DataNULL",TestAddToTail_DataNULL);	

	/*RemoveFromTail:*/
	/*POS*/
	/*int*/
	PrintResult("TestRemoveFromTail_ValidInt",TestRemoveFromTail_ValidInt);
	/*NEG*/
	PrintResult("TestRemoveFromTail_VecNULL",TestRemoveFromTail_VecNULL);	
	PrintResult("TestRemoveFromTail_DataNULL",TestRemoveFromTail_DataNULL);	
	
	/*SetData:*/
	/*POS*/
	/*int*/
	PrintResult("TestVectorSet_ValidInt",TestVectorSet_ValidInt);
	/*NEG*/
	PrintResult("TestVectorSet_VecNULL",TestVectorSet_VecNULL);	
	PrintResult("TestVectorSet_DataNULL",TestVectorSet_DataNULL);
	
	/*GetData:*/
	/*POS*/
	/*int*/
	PrintResult("TestVectorGet_ValidInt",TestVectorGet_ValidInt);
	/*NEG*/
	PrintResult("TestVectorGet_VecNULL",TestVectorGet_VecNULL);	
	PrintResult("TestVectorGet_DataNULL",TestVectorGet_DataNULL);
	
	/*FindData:*/
	/*POS*/
	/*int*/
	PrintResult("TestVectorFind_ValidInt",TestVectorFind_ValidInt);
	/*NEG*/
	PrintResult("TestVectorFind_VecNULL",TestVectorFind_VecNULL);	
	
	/*NumOfElemetns:*/
	/*POS*/
	/*int*/
	PrintResult("TestVectorNumOfelements_ValidInt",TestVectorNumOfelements_ValidInt);
	/*NEG*/
	PrintResult("TestVectorNumOfelements_VecNULL",TestVectorNumOfelements_VecNULL);	
	
	/*Print values:*/
	PrintResult("TestBubbleSort",TestBubbleSort);
	PrintResult("TestPrintAddToTail_ValidIntChar",TestPrintAddToTail_ValidIntChar);


	
	return 0;
}








