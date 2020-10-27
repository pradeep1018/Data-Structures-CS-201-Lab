#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

Node* calc1(Node* head,int n)
{
    Node* ptr;
    Node* temp;
    ptr=(Node*)malloc(sizeof(Node));
    temp=(Node*)malloc(sizeof(Node));
    int carry=0,m=0;
    ptr=head;
    while(ptr->next!=NULL)
    {
        m=n*(ptr->val)+carry;
        ptr->val=m%10;
        carry=m/10;
        ptr=ptr->next;
    }
    m=n*(ptr->val)+carry;
    ptr->val=m%10;
    carry=m/10;
    if(carry!=0)
    {
        while(carry>0)
        {
            temp->val=carry%10;
            temp->next=NULL;
            ptr->next=temp;
            ptr=ptr->next;
            carry=carry/10;
            temp=(Node*)malloc(sizeof(Node));
        }
    }
    return head;
}

Node* func(int n)
{
    Node* head;
    head=(Node*)malloc(sizeof(Node));
    head->val=1;
    head->next=NULL;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=i;++j)
        {
            head=calc1(head,i);
        }
    }
    return head;
}

Node* reverse_list(Node* head)
{
    Node* prev;
    Node* curr;
    Node* next;
    prev=(Node*)malloc(sizeof(Node));
    curr=(Node*)malloc(sizeof(Node));
    next=(Node*)malloc(sizeof(Node));
    prev=NULL;
    curr=head;
    next=NULL;
    while (curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    head=prev;
    return head;
}

int zero_count(Node* head)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head;
    int count=0;
    while(ptr!=NULL&&ptr->val==0)
    {
        ptr=ptr->next;
        ++count;
    }
    return count;
}

int pattern(Node* head,char k[3])
{
    if(strlen(k)==1)
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        ptr=head;
        int count=0;
        while(ptr!=NULL)
        {
            if(ptr->val==(k[0]-'0'))
            {
                ++count;
            }
            ptr=ptr->next;
        }
        return count;
    }
    else if(strlen(k)==2)
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        ptr=head;
        int count=0;
        while(ptr!=NULL)
        {
            if(ptr->val==(k[0]-'0')&&ptr->next!=NULL&&ptr->next->val==(k[1]-'0'))
            {
                ++count;
            }
            ptr=ptr->next;
        }
        return count;
    }
    else if(strlen(k)==3)
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        ptr=head;
        int count=0;
        while(ptr!=NULL)
        {
            if(ptr->val==(k[0]-'0')&&ptr->next!=NULL&&ptr->next->val==(k[1]-'0')&&ptr->next->next!=NULL&&ptr->next->next->val==(k[2]-'0'))
            {
                ++count;
            }
            ptr=ptr->next;
        }
        return count;
    }
}

Node* display(Node* head)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=head;
    while(ptr!=NULL)
    {
        printf("%d",ptr->val);
        ptr=ptr->next;
    }
    printf("\n");
    return head;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,z,p;
        char k[4];
        scanf("%d%s",&n,k);
        Node* head=NULL;
        head=func(n);
        z=zero_count(head);
        head=reverse_list(head);
        p=pattern(head,k);
        printf("%d ",z);
        printf("%d ",p);
        head=display(head);
        free_list(head);
    }
    return 0;
}
