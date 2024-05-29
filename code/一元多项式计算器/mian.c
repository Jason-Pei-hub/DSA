#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node* LIST;
struct node
{
    int c;//系数
    int n;//指数
    LIST NEXT;
};
LIST input();
void insert(int c, int n, LIST head);//插入和维护升幂
void add(LIST A, LIST B);//A链节点和B链节点直接insert里面丢，进去就有序
void output(LIST head);//
LIST reversed(LIST head);//反转->降幂
void sub(LIST A, LIST B);//A链节点和B链负节点直接insert里面丢，进去就有序
void mul(LIST A, LIST B);//A链节点 * B链节点(for for)直接insert(c*c, n+n, head)里面丢，进去就有序
void uptate(LIST head);//A链节点B链节点删除c=0节点
void show(LIST head);//展示\t,switch,
void init();//初始化
int main(int argc, char const* argv[])
{
    init();
    return 0;
}
void init()//初始化
{
    printf("请先输入两个多项式\n");
    LIST A = input();
    LIST B = input();
    printf("A = "); output(A);
    printf("B = "); output(B);
    while (1) {
        int flag;
        printf("请选择操作命令-> \n \t1：加法；\n\t2：A - B；\n\t3：B - A；\n\t4：乘法；\n\t5：return\n");
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
    //头结点性质
    LIST tmp = (LIST)malloc(sizeof(struct node));
    tmp->n = n, tmp->c = c, tmp->NEXT = NULL;
    LIST P = head;
    while (P->NEXT)
    {
        //相等
        if (P->NEXT->n == tmp->n)
        {
            P->NEXT->c += tmp->c;
            return;
        }
        if (P->NEXT->n > tmp->n)
            break;
        P = P->NEXT;
    }
    //找到最后还没有找到
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
    printf("输入系数和指数，以0 0结束\n");
    //输入系数和指数
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
/*老版不能解决系数和指数 正负一 特殊情况
void output(LIST head)
{
    LIST P = head->NEXT;
    if(!P) return;
    //输出第一个
    if(P->c < 0)
        printf("-");
    if(P->n == 0)
        printf("%d", abs(P->c));
    else
        printf("%dx^%d", abs(P->c), P->n);
    P = P->NEXT;
    //继续输出
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
    //输出第一个
    if (P->c < 0)
        printf("-");
    if (P->n == 0)
        printf("%d", abs(P->c));
    else if (abs(P->c) == 1)//判断系数
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
    //继续输出
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
        printf("请问你想升幂输出还是降幂输出-> \n\t1：升幂；\n\t2：降幂；\n\t3：all；\n\t4：return\n");
        scanf("%d", &flag);
        switch (flag) {
        case 1:
            printf("升幂排列是\n");
            output(head);
            break;
        case 2:
            printf("降幂排列是\n");
            output(reversed(head));
            break;
        case 3:
            printf("升幂排列是\n");
            output(head);
            printf("降幂排列是\n");
            output(reversed(head));
            break;
        case 4:
            return;
        }
    }
}
