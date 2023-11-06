#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "malloc.h"
/*常量定义*/
#define TRUE   1
#define FALSE  0
#define OK  1
#define ERROR  0
#define OVERFLOW  -2
#define LIST_INIT_SIZE 100  /*存储空间的初始分配量*/
#define LISTINCREAMENT 10   /*存储空间的分配增量 */
/*自定义数据类型 */
typedef int Status;    /*函数返回结果类型 */
typedef int ElemType;  /*元素类型定义 */

typedef struct
{
	ElemType* elem;     /*表基址(用指针elem表示） */
	int  length;        /*表长度（表中有多少个元素） */
	int  listsize;      /*当前分配的表尺寸（元素单位）*/
}SqList;              /*顺序表类型      */
/*--------函数原型声明------*/
Status InitList(SqList* L);
Status ListInsert(SqList* L, int i, ElemType e);
Status ListDelete(SqList* L, int i, ElemType* e);
void ListOutput(SqList L);
Status  LocateElem(SqList L, ElemType e);
/* 主函数----------------*/
int main()
{
	SqList L;
	Status flag;
	int n, i, choose;
	ElemType e;
	/*初始化顺序表*/
	flag = InitList(&L);
	if (flag == OK)
		printf("初始化线性表成功！！！\n");
	else
		printf("Fail code is %d . ", flag);
	_getch();
	while (1)
	{
		system("cls");  
		printf("========================\n");
		printf("  1.  创建线性表元素          \n");
		printf("  2.  插入线性表元素          \n");
		printf("  3.  查询线性表元素          \n");
		printf("  4.  删除线性表元素          \n");
		printf("  5.  输出线性表元素          \n");
		printf("       0.  退出                  \n");
		printf("=========================\n");
		printf(" \n请输入操作选项(0-5)->");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("请输入元素的数量->");
			scanf("%d", &n);
			printf("\n请按顺序输入元素->\n", n);
			for (i = 1; i <= n; i++)
			{
				scanf("%d", &e);
				flag = ListInsert(&L, i, e); /*插入*/
			}
			break;
		case 2:/*插入*/
			printf("\n请输入插入的位置和元素->");
			scanf("%d %d", &i, &e);
			flag = ListInsert(&L, i, e);
			break;
		case 3:/*查找*/
			printf("\n请输入要查询的元素->");
			scanf("%d", &e);
			i = 0;
			i = LocateElem(L, e);
			printf("他的位置是：%d", i);
			break;
		case 4:/*删除*/
			printf("\n请输入要删除的元素的索引");
			scanf("%d", &i);
			flag = ListDelete(&L, i, &e);
			printf("要删除的元素是%d:\n", e);
			break;
		case 5:  /*输出顺序表*/
			printf("\n线性表的输出结果是->\n");
			ListOutput(L);
			break;
		case 0:
			printf("您已成功退出系统！！！");
			exit(0);
			break;
		}/* end of switch*/
		system("pause");
	}/*end of while*/
	return 0;
}

/*---顺序表的操作的实现----- */
Status InitList(SqList* L)
{/*初始化空的顺序表 */
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem)
		exit(OVERFLOW);          /*分配失败，结束程序 */
	L->length = 0;                 /*暂无元素放入，空表 */
	L->listsize = LIST_INIT_SIZE;  /*表尺寸=初始分配量*/
	return OK;
}/*InitList*/
Status  LocateElem(SqList L, ElemType e)
{ /*在顺序表L中查找元素值为e的元素，查找成功返回元素的数组下标，否则返回-1*/
	int i = 0;
	while (i <= L.length - 1 && L.elem[i] != e)
		i++;
	if (i <= L.length - 1)
		return i;
	else
		return -1;
}/*LocateElem*/
Status ListInsert(SqList* L, int i, ElemType e)
{/*在顺序表L的第i个元素前插入新元素e*/
	ElemType* newbase, * q, * p;
	if (i<1 || i>L->length + 1) return ERROR;/*检验i的合法性 */
	if (L->length >= L->listsize)/*空间不够，增加空间 */
	{
		newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREAMENT) * sizeof(ElemType));
		if (newbase == NULL) exit(OVERFLOW);
		L->elem = newbase;
		L->listsize = L->listsize + LISTINCREAMENT;
	}
	/*插入元素*/
	q = &(L->elem[i - 1]);  /*q指向插入位置，即第i个元素的地址 */
	for (p = &L->elem[L->length - 1]; p >= q; --p)
		*(p + 1) = *p;   /*从表的最后一个元素到第i个元素依次后移*/

	*q = e;            /*插入e*/
	++L->length;     /*表长加1*/
	return OK;
}/*ListInsert*/

Status ListDelete(SqList* L, int i, ElemType* e)
{/*在顺序表L中删除第 i 个元素，用 e 返回其值*/
	ElemType* p, * q;
	if (i<1 || i>L->length) exit(ERROR);   /* i 值不合法，返回 */
	p = &L->elem[i - 1];            /* p指向被删除元素的地址*/
	*e = *p;
	q = L->elem + L->length - 1;       /* q指向表尾的*/
	for (++p; p <= q; p++)
		*(p - 1) = *p;          /*待删元素后面的依次前移，即从第i+1个到最后一个依次前移*/
	--L->length;              /*表长-1*/
	return OK;
}/*ListDelete*/

void ListOutput(SqList L)
{ /*输出顺序表中的元素*/
	int i;
	if (L.length == 0)
		printf("List is NULL!\n");
	else
	{
		for (i = 0; i < L.length; i++)
			printf("%d ", L.elem[i]);
		printf("\n");
	}
}