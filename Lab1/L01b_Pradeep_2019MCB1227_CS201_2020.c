#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ll long long

typedef struct node
{
    int coeff;
    int power;
    struct node* next;
}Node;

void free_list(Node* head)
{
    while(head!=NULL)
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        ptr=head;
        head=head->next;
        ptr->next=NULL;
        free(ptr);
    }
}

Node* insert(Node* head,int coeff,int power)
{
    Node* ptr;
    Node* trav;
    ptr=(Node*)malloc(sizeof(Node));
    trav=(Node*)malloc(sizeof(Node));
    ptr->coeff=coeff;
    ptr->power=power;
    ptr->next=NULL;
    if(head==NULL)
    {
        head=ptr;
    }
    else
    {
        trav=head;
        while(trav->next!=NULL)
        {
            trav=trav->next;
        }
        trav->next=ptr;
    }
    return head;
}

void print(Node* head1,Node* head2)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head1;
    printf("P1(x) : ");
    if(ptr==NULL)
    {
        printf("0\n");
    }
    else
    {
        if(ptr->coeff>0)
        {
            if(ptr->power==0)
            {
                printf("%d",ptr->coeff);
            }
            else
            {
                printf("%dx^%d",ptr->coeff,ptr->power);
            }
        }
        else
        {
            if(ptr->power==0)
            {
                printf("- %d",abs(ptr->coeff));
            }
            else
            {
                printf("- %dx^%d",abs(ptr->coeff),ptr->power);
            }
        }
        ptr=ptr->next;
        while(ptr!=NULL)
        {
            if(ptr->coeff>0)
            {
                if(ptr->power==0)
                {
                    printf(" + %d",ptr->coeff);
                }
                else
                {
                    printf(" + %dx^%d",ptr->coeff,ptr->power);
                }
            }
            else
            {
                if(ptr->power==0)
                {
                    printf(" - %d",abs(ptr->coeff));
                }
                else
                {
                    printf(" - %dx^%d",abs(ptr->coeff),ptr->power);
                }
            }
            ptr=ptr->next;
        }
        printf("\n");
    }
    ptr=head2;
    printf("P2(x) : ");
    if(ptr==NULL)
    {
        printf("0\n");
    }
    else
    {
        if(ptr->coeff>0)
        {
            if(ptr->power==0)
            {
                printf("%d",ptr->coeff);
            }
            else
            {
                printf("%dx^%d",ptr->coeff,ptr->power);
            }
        }
        else
        {
            if(ptr->power==0)
            {
                printf("- %d",abs(ptr->coeff));
            }
            else
            {
                printf("- %dx^%d",abs(ptr->coeff),ptr->power);
            }
        }
        ptr=ptr->next;
        while(ptr!=NULL)
        {
            if(ptr->coeff>0)
            {
                if(ptr->power==0)
                {
                    printf(" + %d",ptr->coeff);
                }
                else
                {
                    printf(" + %dx^%d",ptr->coeff,ptr->power);
                }
            }
            else
            {
                if(ptr->power==0)
                {
                    printf(" - %d",abs(ptr->coeff));
                }
                else
                {
                    printf(" - %dx^%d",abs(ptr->coeff),ptr->power);
                }
            }
            ptr=ptr->next;
        }
        printf("\n");
    }
}

void add(Node* head1,Node* head2)
{
    Node* ptr1;
    Node* ptr2;
    ptr1=(Node*)malloc(sizeof(Node));
    ptr2=(Node*)malloc(sizeof(Node));
    ptr1=head1;
    ptr2=head2;
    int p=0;
    printf("P3(x) = P1(x) + P2(x) : ");
    for(int i=9;i>=0;--i)
    {
        int c=0;
        if(ptr1!=NULL&&ptr1->power==i)
        {
            c+=ptr1->coeff;
            ptr1=ptr1->next;
        }
        if(ptr2!=NULL&&ptr2->power==i)
        {
            c+=ptr2->coeff;
            ptr2=ptr2->next;
        }
        if(c!=0&&p==0)
        {
            if(c>0)
            {
                if(i==0)
                {
                    printf("%d",c);
                }
                else
                {
                    printf("%dx^%d",c,i);
                }
            }
            else
            {
                if(i==0)
                {
                    printf("- %d",abs(c));
                }
                else
                {
                    printf("- %dx^%d",abs(c),i);
                }
            }
            p=1;
        }
        else if(c!=0&&p==1)
        {
            if(c>0)
            {
                if(i==0)
                {
                    printf(" + %d",c);
                }
                else
                {
                    printf(" + %dx^%d",c,i);
                }
            }
            else
            {
                if(i==0)
                {
                    printf(" - %d",abs(c));
                }
                else
                {
                    printf(" - %dx^%d",abs(c),i);
                }
            }
        }
    }
    if(p==0)
    {
        printf("%d",p);
    }
    printf("\n");
}

void subtract(Node* head1,Node* head2)
{
    Node* ptr1;
    Node* ptr2;
    ptr1=(Node*)malloc(sizeof(Node));
    ptr2=(Node*)malloc(sizeof(Node));
    ptr1=head1;
    ptr2=head2;
    int p=0;
    printf("P4(x) = P1(x) - P2(x) : ");
    for(int i=9;i>=0;--i)
    {
        int c=0;
        if(ptr1!=NULL&&ptr1->power==i)
        {
            c+=ptr1->coeff;
            ptr1=ptr1->next;
        }
        if(ptr2!=NULL&&ptr2->power==i)
        {
            c-=ptr2->coeff;
            ptr2=ptr2->next;
        }
        if(c!=0&&p==0)
        {
            if(c>0)
            {
                if(i==0)
                {
                    printf("%d",c);
                }
                else
                {
                    printf("%dx^%d",c,i);
                }
            }
            else
            {
                if(i==0)
                {
                    printf("- %d",abs(c));
                }
                else
                {
                    printf("- %dx^%d",abs(c),i);
                }
            }
            p=1;
        }
        else if(c!=0&&p==1)
        {
            if(c>0)
            {
                if(i==0)
                {
                    printf(" + %d",c);
                }
                else
                {
                    printf(" + %dx^%d",c,i);
                }
            }
            else
            {
                if(i==0)
                {
                    printf(" - %d",abs(c));
                }
                else
                {
                    printf(" - %dx^%d",abs(c),i);
                }
            }
        }
    }
    if(p==0)
    {
        printf("%d",p);
    }
    printf("\n");
}

Node* compute(Node* head1,Node* head2,int x)
{
    Node* ptr;
    int val1=0,val2=0;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head1;
    while(ptr!=NULL)
    {
        val1+=ptr->coeff*(int)pow(x,ptr->power);
        ptr=ptr->next;
    }
    printf("P1(%d) = %d\n",x,val1);
    ptr=head2;
    while(ptr!=NULL)
    {
        val2+=ptr->coeff*(int)pow(x,ptr->power);
        ptr=ptr->next;
    }
    printf("P2(%d) = %d\n",x,val2);
    printf("P3(%d) = %d\n",x,val1+val2);
    printf("P4(%d) = %d\n",x,val1-val2);
}

int main()
{
    int k;
    scanf("%d",&k);
    while(k--)
    {
        int n1,n2,x;
        Node* head1;
        Node* head2;
        head1=NULL;
        head2=NULL;
        scanf("%d",&n1);
        for(int power=n1;power>=0;--power)
        {
            int coeff;
            scanf("%d",&coeff);
            if(coeff!=0)
            {
                head1=insert(head1,coeff,power);
            }
        }
        scanf("%d",&n2);
        for(int power=n2;power>=0;--power)
        {
            int coeff;
            scanf("%d",&coeff);
            if(coeff!=0)
            {
                head2=insert(head2,coeff,power);
            }
        }
        print(head1,head2);
        add(head1,head2);
        subtract(head1,head2);
        scanf("%d",&x);
        compute(head1,head2,x);
        free_list(head1);
        free_list(head2);
    }
}
