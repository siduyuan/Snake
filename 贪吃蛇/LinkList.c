#include <stdio.h>
#include <stdlib.h>

#include "LinkList.h"

Node* InitLinkListNode(int Data[2], State state)
{
	Node* pTempNode = (Node*)malloc(sizeof(Node));
	if (pTempNode == NULL)
	{
		printf("创建节点失败\n");
		return NULL;
	}
	pTempNode->Data[0] = Data[0];
	pTempNode->Data[1] = Data[1];
	pTempNode->state = state;
	pTempNode->pNext = NULL;
	return pTempNode;
}

LinkList* InitList()
{
	LinkList* pTemp = (LinkList*)malloc(sizeof(LinkList));
	if (pTemp == NULL)
	{
		printf("创建链表失败\n");
		return NULL;
	}
	pTemp->pHead = NULL;
	pTemp->pEnd = NULL;
	pTemp->len = 0;
	pTemp->direction = Right;
	return pTemp;
}

void FreeList(LinkList** pLinkList)
{
	if (*pLinkList == NULL)
	{
		printf("链表不存在\n");
		return;
	}
	Node* pTemp = NULL;
	while ((*pLinkList)->pHead)
	{
		pTemp = (*pLinkList)->pHead;
		(*pLinkList)->pHead = (*pLinkList)->pHead->pNext;
		free(pTemp);
	}
	free(*pLinkList);
	return;
}

Node* jumpNode(LinkList* pLinkList, int index)
{
	if (index<0 || index>pLinkList->len - 1)
	{
		printf("索引错误\n");
		return NULL;
	}
	Node* pNode = pLinkList->pHead;
	for (int i = 1; i < index+1; i++)
	{
		pNode = pNode->pNext;
	}
	return pNode;
}

int findNode(LinkList* pLinkList, int val[2],int start_index)
{
	if (pLinkList == NULL)
	{
		//printf("链表不存在\n");
		return -1;
	}
	else if (pLinkList->pHead == NULL)
	{
		//printf("链表为空\n");
		return -1;
	}
	else
	{
		Node* pTemp = pLinkList->pHead;
		for (int i = start_index; i < pLinkList->len; i++)
		{
			if ((pTemp->Data[0] == val[0]) && (pTemp->Data[1] == val[1]))
				return i;
			if(i< pLinkList->len-1)
				pTemp = pTemp->pNext;
		}
		return -1;
	}
}

void addHeadList(LinkList* pLinkList, int val[2], State state)
{
	if (pLinkList == NULL)
	{
		printf("链表不存在\n");
		return;
	}
	Node* pTemp = InitLinkListNode(val,state);
	if (pLinkList->pHead == NULL)
	{
		pLinkList->pHead = pLinkList->pEnd = pTemp;
	}
	else
	{
		pTemp->pNext = pLinkList->pHead;
		pLinkList->pHead = pTemp;
	}
	pLinkList->len++;
	return;
}

void DeleteList(LinkList* pLinkList, int index)
{
	if (pLinkList == NULL)
	{
		printf("链表不存在\n");
		return;
	}
	if (index<0 || index>pLinkList->len - 1)
	{
		printf("索引错误\n");
		return;
	}
	Node* pDel = NULL;
	if (index == 0)
	{
		pDel = pLinkList->pHead;
		pLinkList->pHead = pLinkList->pHead->pNext;
	}
	else 
	{
		Node* pTemp = jumpNode(pLinkList, index - 1);
		pDel = pTemp->pNext;
		if (index == pLinkList->len - 1)
		{
			pTemp->pNext = NULL;
			pLinkList->pEnd = pTemp;
		}
		else
		{
			pTemp->pNext = pTemp->pNext->pNext;
		}
	}
	free(pDel);
	pLinkList->len--;
	return;
}

void printList(LinkList* pLinkList)
{
	if (pLinkList == NULL)
	{
		printf("链表不存在\n");
		return;
	}
	else if (pLinkList->pHead == NULL)
	{
		printf("链表为空\n");
		return;
	}
	else
	{
		Node* pTemp = pLinkList->pHead;
		for (int i = 0; i < pLinkList->len; i++)
		{
			printf("%d\t", pTemp->Data[0]);//此处有问题，为了适配二维数据的贪吃蛇
			pTemp = pTemp->pNext;
		}
	}
	printf("\n");
	return;
}

