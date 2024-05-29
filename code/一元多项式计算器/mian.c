#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node* LIST;
struct node
{
    int c;//ϵ��
    int n;//ָ��
    LIST NEXT;
};
LIST input();
void insert(int c, int n, LIST head);//�����ά������
void add(LIST A, LIST B);//A���ڵ��B���ڵ�ֱ��insert���涪����ȥ������
void output(LIST head);//
LIST reversed(LIST head);//��ת->����
void sub(LIST A, LIST B);//A���ڵ��B�����ڵ�ֱ��insert���涪����ȥ������
void mul(LIST A, LIST B);//A���ڵ� * B���ڵ�(for for)ֱ��insert(c*c, n+n, head)���涪����ȥ������
void uptate(LIST head);//A���ڵ�B���ڵ�ɾ��c=0�ڵ�
void show(LIST head);//չʾ\t,switch,
void init();//��ʼ��
int main(int argc, char const* argv[])
{
    init();
    return 0;
}
void init()//��ʼ��
{
    printf("����������������ʽ\n");
    LIST A = input();
    LIST B = input();
    printf("A = "); output(A);
    printf("B = "); output(B);
    while (1) {
        int flag;
        printf("��ѡ���������-> \n \t1���ӷ���\n\t2��A - B��\n\t3��B - A��\n\t4���˷���\n\t5��return\n");
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            add(A, B);
            break;
        case 2:
            sub(A, B);
            break;
        case 3:
            sub(B, A);
            break;
        case 4:
            mul(A, B);
            break;
        case 5:
            return;
        }
    }
}
void insert(int c, int n, LIST head)
{
    //ͷ�������
    LIST tmp = (LIST)malloc(sizeof(struct node));
    tmp->n = n, tmp->c = c, tmp->NEXT = NULL;
    LIST P = head;
    while (P->NEXT)
    {
        //���
        if (P->NEXT->n == tmp->n)
        {
            P->NEXT->c += tmp->c;
            return;
        }
        if (P->NEXT->n > tmp->n)
            break;
        P = P->NEXT;
    }
    //�ҵ����û���ҵ�
    if (!P->NEXT)
    {
        P->NEXT = tmp;
        return;
    }
    tmp->NEXT = P->NEXT;
    P->NEXT = tmp;
}
LIST input()
{
    printf("����ϵ����ָ������0 0����\n");
    //����ϵ����ָ��
    LIST head = (LIST)malloc(sizeof(struct node));
    head->NEXT = NULL;
    int n, c;
    while (scanf("%d%d", &c, &n), n || c)
        insert(c, n, head);
    return head;
}
void add(LIST A, LIST B)
{
    LIST head = (LIST)malloc(sizeof(struct node));
    head->NEXT = NULL;
    LIST P = A->NEXT;
    while (P)
        insert(P->c, P->n, head), P = P->NEXT;
    P = B->NEXT;
    while (P)
        insert(P->c, P->n, head), P = P->NEXT;
    uptate(head);
    show(head);
}
void sub(LIST A, LIST B)
{
    LIST head = (LIST)malloc(sizeof(struct node));
    head->NEXT = NULL;
    LIST P = A->NEXT;
    while (P)
        insert(P->c, P->n, head), P = P->NEXT;
    P = B->NEXT;
    while (P)
        insert(-P->c, P->n, head), P = P->NEXT;
    uptate(head);
    show(head);
}
void mul(LIST A, LIST B)
{
    LIST head = (LIST)malloc(sizeof(struct node));
    head->NEXT = NULL;
    LIST i = A->NEXT;
    //if A NULL
    LIST j = B->NEXT;
    if (!i)
    {
        while (j)
        {
            insert(j->c, j->n, head);
            j = j->NEXT;
        }
        uptate(head);
        show(head);
        return;
    }
    //if B NULL
    if (!j)
    {
        while (i)
        {
            insert(i->c, i->n, head);
            i = i->NEXT;
        }
        uptate(head);
        show(head);
        return;
    }
    while (i) {
        j = B->NEXT;
        while (j)
        {
            insert(i->c * j->c, i->n + j->n, head);
            j = j->NEXT;
        }
        i = i->NEXT;
    }
    uptate(head);
    show(head);
}
void uptate(LIST head)
{
    LIST P = head;
    while (P->NEXT)
    {
        if (P->NEXT->c == 0) {
            P->NEXT = P->NEXT->NEXT;
            continue;
        }
        P = P->NEXT;
    }
}
/*�ϰ治�ܽ��ϵ����ָ�� ����һ �������
void output(LIST head)
{
    LIST P = head->NEXT;
    if(!P) return;
    //�����һ��
    if(P->c < 0)
        printf("-");
    if(P->n == 0)
        printf("%d", abs(P->c));
    else
        printf("%dx^%d", abs(P->c), P->n);
    P = P->NEXT;
    //�������
    while(P)
    {
        if(P->n == 0)
            printf("%c%d", P->c > 0 ? '+' : '-',abs(P->c));
        else
            printf("%c%dx^%d", P->c > 0 ? '+' : '-', abs(P->c), P->n);
        P = P->NEXT;
    }
    printf("\n");
}
*/
void output(LIST head)
{

    LIST P = head->NEXT;
    if (!P) return;
    //�����һ��
    if (P->c < 0)
        printf("-");
    if (P->n == 0)
        printf("%d", abs(P->c));
    else if (abs(P->c) == 1)//�ж�ϵ��
    {
        if (P->n == 1)
            printf("x");
        else
            printf("x^%d", P->n);
    }
    else
    {
        if (P->n == 1)
            printf("%dx", abs(P->c));
        else
            printf("%dx^%d", abs(P->c), P->n);
    }
    P = P->NEXT;
    //�������
    while (P)
    {
        if (P->n == 0)
            printf("%c%d", P->c > 0 ? '+' : '-', abs(P->c));
        else if (abs(P->c) == 1)
        {
            if (P->n == 1)
                printf("%cx", P->c > 0 ? '+' : '-');
            else
                printf("%cx^%d", P->c > 0 ? '+' : '-', P->n);
        }
        else
        {
            if (P->n == 1)
                printf("%c%dx", P->c > 0 ? '+' : '-', abs(P->c));
            else
                printf("%c%dx^%d", P->c > 0 ? '+' : '-', abs(P->c), P->n);
        }
        P = P->NEXT;
    }
    printf("\n");
}


LIST reversed(LIST head)
{
    LIST rear, P = head->NEXT;
    rear = (LIST)malloc(sizeof(struct node));
    rear->NEXT = NULL;
    while (P)
    {
        LIST tmp = (LIST)malloc(sizeof(struct node));
        tmp->NEXT = NULL, tmp->c = P->c, tmp->n = P->n;
        tmp->NEXT = rear->NEXT;
        rear->NEXT = tmp;
        P = P->NEXT;
    }
    return rear;
}
void show(LIST head)
{
    while (1) {
        int flag;
        printf("������������������ǽ������-> \n\t1�����ݣ�\n\t2�����ݣ�\n\t3��all��\n\t4��return\n");
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            printf("����������\n");
            output(head);
            break;
        case 2:
            printf("����������\n");
            output(reversed(head));
            break;
        case 3:
            printf("����������\n");
            output(head);
            printf("����������\n");
            output(reversed(head));
            break;
        case 4:
            return;
        }
    }
}
