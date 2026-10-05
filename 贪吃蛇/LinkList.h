#ifndef LINK_LIST_H
#define LINK_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum State { LeftUp, LeftDown, RightUp, RightDown, xAxis, yAxis, air }State;
typedef enum Direction { Null,Up, Down, Left, Right }Direction;

typedef struct Node
{
	int Data[2];
	State state;
	struct Node* pNext;
}Node;

typedef struct LinkList
{
	Node* pHead;
	Node* pEnd;
	Direction direction;
	int len;
}LinkList;

Node* InitLinkListNode(int data[2], State state);
LinkList* InitList();
void FreeList(LinkList** pLinkList);

Node* jumpNode(LinkList* pLinkList, int index);
int findNode(LinkList* pLinkList, int val[2], int start_index);
void addHeadList(LinkList* pLinkList, int val[2], State state);
void DeleteList(LinkList* pLinkList, int index);
void printList(LinkList* pLinkList);


#ifdef __cplusplus
}
#endif

#endif