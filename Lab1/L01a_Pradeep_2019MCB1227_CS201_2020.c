#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int val;
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

Node* insert_beg(Node* head,int val)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr->val=val;
    ptr->next=head;
    head=ptr;
    return head;
}

Node* insert_end(Node* head,int val)
{
    Node* ptr;
    Node* trav;
    ptr=(Node*)malloc(sizeof(Node));
    trav=(Node*)malloc(sizeof(Node));
    ptr->val=val;
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

Node* delete_beg(Node* head)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    if(head==NULL)
    {
        printf("\tCannot delete as NO nodes in the linked-list\n");
    }
    else
    {
        ptr=head;
        head=head->next;
        ptr->next=NULL;
        free(ptr);
    }
    return head;
}

Node* delete_end(Node* head)
{
    Node* ptr1;
    Node* ptr2;
    ptr1=(Node*)malloc(sizeof(Node));
    ptr2=(Node*)malloc(sizeof(Node));
    if(head==NULL)
    {
        printf("\tCannot delete as NO nodes in the linked-list\n");
    }
    else if(head->next==NULL)
    {
        ptr1=head;
        head=NULL;
        free(ptr1);
    }
    else
    {
        ptr1=head;
        ptr2=ptr1->next;
        while(ptr2->next!=NULL)
        {
            ptr1=ptr2;
            ptr2=ptr2->next;
        }
        ptr1->next=NULL;
        free(ptr2);
    }
    return head;
}

Node* delete_spec(Node* head,int val)
{
    Node* ptr1;
    Node* ptr2;
    ptr1=(Node*)malloc(sizeof(Node));
    ptr2=(Node*)malloc(sizeof(Node));
    if(head==NULL)
    {
        printf("\tCannot delete as no such node in the linked-list\n");
    }
    else if(head->val==val)
    {
        ptr1=head;
        head=head->next;
        ptr1->next=NULL;
        free(ptr1);
    }
    else
    {
        ptr1=head;
        ptr2=ptr1->next;
        while(ptr2!=NULL&&ptr2->val!=val)
        {
            ptr1=ptr2;
            ptr2=ptr2->next;
        }
        if (ptr2==NULL) {
            printf("\tCannot delete as no such node in the linked-list\n");
        }
        else
        {
            ptr1->next=ptr2->next;
            ptr2->next=NULL;
            free(ptr2);
        }
    }
    return head;
}

Node* find(Node* head,int val)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head;
    int pos=1;
    while(ptr!=NULL&&ptr->val!=val)
    {
        ptr=ptr->next;
        ++pos;
    }
    if(ptr==NULL)
    {
        printf("\tCannot find any such node in the linked-list\n");
    }
    else
    {
        printf("\tValue %d node is at position %d in the linked list.\n",val,pos);
        printf("\tDifference in its allocated memory to that of current head : %d\n",ptr-head);
    }
    return head;
}

Node* size(Node* head)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head;
    if(head==NULL)
    {
        printf("\tSize of the linked list = 0\n");
    }
    else
    {
        int c=0;
        while(ptr!=NULL)
        {
            ptr=ptr->next;
            ++c;
        }
        printf("\tSize of the linked list = %d\n",c);
    }
    return head;
}

Node* display(Node* head)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head;
    if(head==NULL)
    {
        printf("\tEmpty\n");
    }
    else
    {
        printf("\tLinked list: ");
        while(ptr->next!=NULL)
        {
            printf("%d => ",ptr->val);
            ptr=ptr->next;
        }
        printf("%d",ptr->val);
        printf("\n");
    }
    return head;
}

int main()
{
    int choice;
    Node* head;
    head=NULL;
    printf("Enter the choice:\n");
    scanf("%d",&choice);
    while(choice!=0)
    {
        if(choice==0)
        {
            free_list(head);
            free(head);
            break;
        }
        else if(choice==1)
        {
            int val;
            printf("Enter the data value:\n");
            scanf("%d",&val);
            head=insert_beg(head,val);
            //printf("head value %d",head->val);
        }
        else if(choice==2)
        {
            int val;
            printf("Enter the data value:\n");
            scanf("%d",&val);
            head=insert_end(head,val);
        }
        else if(choice==3)
        {
            head=delete_beg(head);
        }
        else if(choice==4)
        {
            head=delete_end(head);
        }
        else if(choice==5)
        {
            int val;
            printf("Enter the data value:\n");
            scanf("%d",&val);
            head=delete_spec(head,val);
        }
        else if(choice==6)
        {
            int val;
            printf("Enter the data value:\n");
            scanf("%d",&val);
            head=find(head,val);
        }
        else if(choice==7)
        {
            head=size(head);
        }
        else if(choice==8)
        {
            head=display(head);
        }
        else
        {
            printf("\tWrong Input.\n");
        }
        if(choice>=0&&choice<=8)
        {
            printf("Enter the choice:\n");
            scanf("%d",&choice);
        }
        else
        {
            printf("Enter your choice again:\n");
            scanf("%d",&choice);
        }
    }
}
