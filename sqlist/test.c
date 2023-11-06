#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "malloc.h"
/*��������*/
#define TRUE   1
#define FALSE  0
#define OK  1
#define ERROR  0
#define OVERFLOW  -2
#define LIST_INIT_SIZE 100  /*�洢�ռ�ĳ�ʼ������*/
#define LISTINCREAMENT 10   /*�洢�ռ�ķ������� */
/*�Զ����������� */
typedef int Status;    /*�������ؽ������ */
typedef int ElemType;  /*Ԫ�����Ͷ��� */

typedef struct
{
	ElemType* elem;     /*���ַ(��ָ��elem��ʾ�� */
	int  length;        /*���ȣ������ж��ٸ�Ԫ�أ� */
	int  listsize;      /*��ǰ����ı�ߴ磨Ԫ�ص�λ��*/
}SqList;              /*˳�������      */
/*--------����ԭ������------*/
Status InitList(SqList* L);
Status ListInsert(SqList* L, int i, ElemType e);
Status ListDelete(SqList* L, int i, ElemType* e);
void ListOutput(SqList L);
Status  LocateElem(SqList L, ElemType e);
/* ������----------------*/
int main()
{
	SqList L;
	Status flag;
	int n, i, choose;
	ElemType e;
	/*��ʼ��˳���*/
	flag = InitList(&L);
	if (flag == OK)
		printf("��ʼ�����Ա�ɹ�������\n");
	else
		printf("Fail code is %d . ", flag);
	_getch();
	while (1)
	{
		system("cls");  
		printf("========================\n");
		printf("  1.  �������Ա�Ԫ��          \n");
		printf("  2.  �������Ա�Ԫ��          \n");
		printf("  3.  ��ѯ���Ա�Ԫ��          \n");
		printf("  4.  ɾ�����Ա�Ԫ��          \n");
		printf("  5.  ������Ա�Ԫ��          \n");
		printf("       0.  �˳�                  \n");
		printf("=========================\n");
		printf(" \n���������ѡ��(0-5)->");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("������Ԫ�ص�����->");
			scanf("%d", &n);
			printf("\n�밴˳������Ԫ��->\n", n);
			for (i = 1; i <= n; i++)
			{
				scanf("%d", &e);
				flag = ListInsert(&L, i, e); /*����*/
			}
			break;
		case 2:/*����*/
			printf("\n����������λ�ú�Ԫ��->");
			scanf("%d %d", &i, &e);
			flag = ListInsert(&L, i, e);
			break;
		case 3:/*����*/
			printf("\n������Ҫ��ѯ��Ԫ��->");
			scanf("%d", &e);
			i = 0;
			i = LocateElem(L, e);
			printf("����λ���ǣ�%d", i);
			break;
		case 4:/*ɾ��*/
			printf("\n������Ҫɾ����Ԫ�ص�����");
			scanf("%d", &i);
			flag = ListDelete(&L, i, &e);
			printf("Ҫɾ����Ԫ����%d:\n", e);
			break;
		case 5:  /*���˳���*/
			printf("\n���Ա����������->\n");
			ListOutput(L);
			break;
		case 0:
			printf("���ѳɹ��˳�ϵͳ������");
			exit(0);
			break;
		}/* end of switch*/
		system("pause");
	}/*end of while*/
	return 0;
}

/*---˳���Ĳ�����ʵ��----- */
Status InitList(SqList* L)
{/*��ʼ���յ�˳��� */
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem)
		exit(OVERFLOW);          /*����ʧ�ܣ��������� */
	L->length = 0;                 /*����Ԫ�ط��룬�ձ� */
	L->listsize = LIST_INIT_SIZE;  /*��ߴ�=��ʼ������*/
	return OK;
}/*InitList*/
Status  LocateElem(SqList L, ElemType e)
{ /*��˳���L�в���Ԫ��ֵΪe��Ԫ�أ����ҳɹ�����Ԫ�ص������±꣬���򷵻�-1*/
	int i = 0;
	while (i <= L.length - 1 && L.elem[i] != e)
		i++;
	if (i <= L.length - 1)
		return i;
	else
		return -1;
}/*LocateElem*/
Status ListInsert(SqList* L, int i, ElemType e)
{/*��˳���L�ĵ�i��Ԫ��ǰ������Ԫ��e*/
	ElemType* newbase, * q, * p;
	if (i<1 || i>L->length + 1) return ERROR;/*����i�ĺϷ��� */
	if (L->length >= L->listsize)/*�ռ䲻�������ӿռ� */
	{
		newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREAMENT) * sizeof(ElemType));
		if (newbase == NULL) exit(OVERFLOW);
		L->elem = newbase;
		L->listsize = L->listsize + LISTINCREAMENT;
	}
	/*����Ԫ��*/
	q = &(L->elem[i - 1]);  /*qָ�����λ�ã�����i��Ԫ�صĵ�ַ */
	for (p = &L->elem[L->length - 1]; p >= q; --p)
		*(p + 1) = *p;   /*�ӱ�����һ��Ԫ�ص���i��Ԫ�����κ���*/

	*q = e;            /*����e*/
	++L->length;     /*����1*/
	return OK;
}/*ListInsert*/

Status ListDelete(SqList* L, int i, ElemType* e)
{/*��˳���L��ɾ���� i ��Ԫ�أ��� e ������ֵ*/
	ElemType* p, * q;
	if (i<1 || i>L->length) exit(ERROR);   /* i ֵ���Ϸ������� */
	p = &L->elem[i - 1];            /* pָ��ɾ��Ԫ�صĵ�ַ*/
	*e = *p;
	q = L->elem + L->length - 1;       /* qָ���β��*/
	for (++p; p <= q; p++)
		*(p - 1) = *p;          /*��ɾԪ�غ��������ǰ�ƣ����ӵ�i+1�������һ������ǰ��*/
	--L->length;              /*��-1*/
	return OK;
}/*ListDelete*/

void ListOutput(SqList L)
{ /*���˳����е�Ԫ��*/
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