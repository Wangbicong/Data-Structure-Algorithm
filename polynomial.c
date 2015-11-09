#include <stdio.h>
#include <stdlib.h>
#define POLY_NUM 2

/*
 * ratio������ʽ��ϵ����index������ʽ��ָ��
 */
struct linkednode{
    int ratio;
    int index;
    struct linkednode* next;
};
typedef struct linkednode polynode;

polynode* create();
void insert(polynode* head,int ratio,int index);
void dele(polynode* head,int ratio,int index);
void addTwoPoly(polynode* head1,polynode* head2);
void printPoly(polynode* head);
void printEach(int ratio,int index,int first);

int main()
{
    int poly_num[2];
    int n;
    polynode* poly_list[2];
    char ques_str[2][7] = {"first","second"};
    for(n=0;n<POLY_NUM;n++){
        int i;
        int radio,index;
        printf("Please input the length of your %s polynomial : \n",ques_str[n]);
        scanf("%d",poly_num+n);
        poly_list[n] = create();
        for(i=0;i<poly_num[n];i++){
            printf("Please input %d radio and index : \n",i+1);
            scanf("%d %d",&radio,&index);
            insert(poly_list[n],radio,index);
        }
    }
    addTwoPoly(poly_list[0],poly_list[1]);
    printPoly(poly_list[0]);
    return 0;
}

/*
 * ����һ���µĶ���ʽ��������ͷ���
 */
polynode* create(){
    polynode* head = (polynode*)malloc(sizeof(polynode));
    head->index = 0;
    head->next = NULL;
    return head;
}

/*
 * ����ָ���Ӵ�С��˳�����
 */
void insert(polynode* head,int ratio,int index){
    polynode* p = head;
    polynode* add_node = (polynode*)malloc(sizeof(polynode));
    add_node->ratio = ratio;
    add_node->index = index;
    add_node->next = NULL;
    while(p->next!=NULL){
        if(index > (p->next)->index){
            break;
        }
        p = p->next;
    }
    add_node->next = p->next;
    p->next = add_node;
}

/*
 * ���Ҷ�Ӧ����ʽ��㣬����ɾ���ý�㣬�ͷ��ڴ�ռ䡣
 * �ô�ֻɾ����һ����ͬ���������Ҫ��
 */
void dele(polynode* head,int ratio,int index){
    polynode* p = head;
    polynode* del_node = NULL;
    while(p->next!=NULL){
        if((p->next)->ratio == ratio && (p->next)->index == index){
            del_node = p->next;
            p->next = del_node->next;
            free(del_node);
            return;
        }
        p = p->next;
    }
}

/*
 * ����������ʽ��ӣ����һ������Ϊ��ӵĽ�����ڶ�������Ϊ�գ���ʣͷ��㣩
 */
void addTwoPoly(polynode* head1,polynode* head2){
    polynode* p1 = head1;
    polynode* p2 = NULL;
    while(p1->next!=NULL){
        p1 = p1->next;
        p2 = head2;
        while(p2->next!=NULL){
            p2 = p2->next;
            if(p2->index == p1->index){
                p1->ratio += p2->ratio;
                if(p1->ratio == 0){
                    dele(head1,0,p1->index);
                }
                dele(head2,p2->ratio,p2->index);
            }
        }
    }
    p1 = head1;
    p2 = head2;
    while(p2->next!=NULL){
        p2 = p2->next;
        insert(head1,p2->ratio,p2->index);
        dele(head2,p2->ratio,p2->index);
    }
}

/*
 * �������ʽ
 */
void printPoly(polynode* head){
    polynode* p = head;
    if(!head->next){
        printf("0");
        return;
    }
    p = p->next;
    printEach(p->ratio,p->index,1);
    while(p->next!=NULL){
        p = p->next;
        printEach(p->ratio,p->index,0);
    }
    printf("\n");
}

/*
 * �������ʽʱ��ʽ��
 * ���Ǹ����������
 */
void printEach(int ratio,int index,int first){
    if((first || ratio < 0 ) && index == 0){
        printf("%d",ratio);
    }else if(index == 0 && ratio > 0){
        printf(" + %d",ratio);
    }else if(first || ratio < 0){
        printf("%d * X ^ %d",ratio,index);
    }else{
        printf(" + %d * X ^ %d",ratio,index);
    }
}

