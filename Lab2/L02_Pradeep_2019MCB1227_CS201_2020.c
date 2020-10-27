#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct node
{
    int val;
    struct node* next;
}Node;

void free_list(Node** head)
{
    while(*head!=NULL)
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        ptr=*head;
        *head=(*head)->next;
        ptr->next=NULL;
        free(ptr);
    }
}

void push_stack(Node** head, int val)
{
    Node* newnode;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->val=val;
    newnode->next=(*head);
    (*head)=newnode;
}

void is_empty(Node** head)
{
    if(*head==NULL)
    {
        printf("E ");
    }
    else
    {
        printf("NE ");
    }
}

void pop_stack(Node** head)
{
    Node* ptr;
    int val;
    ptr=(Node*)malloc(sizeof(Node));
    if(*head==NULL)
    {
        printf("E ");
    }
    else
    {
        ptr=*head;
        val=ptr->val;
        *head=(*head)->next;
        ptr->next=NULL;
        free(ptr);
        printf("%d ",val);
    }
}

void size(Node** head)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=*head;
    if(*head==NULL)
    {
        printf("0 ");
    }
    else
    {
        int c=0;
        while(ptr!=NULL)
        {
            ptr=ptr->next;
            ++c;
        }
        printf("%d ",c);
    }
}

void enqueue_queue(Node** head,Node** tail,int val)
{
    Node* newnode;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->val=val;
    newnode->next=NULL;
    if(*head==NULL)
    {
        *head=newnode;
    }
    else
    {
        (*tail)->next=newnode;
    }
    *tail=newnode;
}

void dequeue_queue(Node** head,Node** tail)
{
    Node* ptr;
    int val;
    ptr=(Node*)malloc(sizeof(Node));
    if(*head==NULL)
    {
        printf("E ");
    }
    else
    {
        ptr=*head;
        val=ptr->val;
        *head=(*head)->next;
        ptr->next=NULL;
        free(ptr);
        printf("%d ",val);
    }
}

typedef struct stack
{
    int top;
    char op[30][3];
}Stack;

Stack* create_stack(Stack* ptr)
{
    ptr=(Stack*)malloc(sizeof(Stack));
    ptr->top=0;
    return ptr;
}

Stack* push_stack_arr(Stack* ptr,char c[])
{
    ++(ptr->top);
    strcpy(ptr->op[ptr->top],c);
    return ptr;
}

Stack* pop_stack_arr(Stack *ptr)
{
    printf("%s ",ptr->op[ptr->top]);
    --(ptr->top);
    return ptr;
}

typedef struct stackop
{
    int top;
    int val[50];
}Stackop;

void create_stack_3(Stackop** ptr)
{
    *ptr=(Stackop*)malloc(sizeof(Stackop));
    (*ptr)->top=-1;
}

void push_stack_arr_3(Stackop** ptr,int n)
{
    ++((*ptr)->top);
    (*ptr)->val[(*ptr)->top]=n;
}

int pop_stack_arr_3(Stackop** ptr)
{
    int value=(*ptr)->val[(*ptr)->top];
    --((*ptr)->top);
    return value;
}

int prec(char c[])
{
    if(strcmp(c,"*")==0||strcmp(c,"/")==0||strcmp(c,"%")==0)
    {
        return 8;
    }
    else if(strcmp(c,"+")==0||strcmp(c,"-")==0)
    {
        return 7;
    }
    else if(strcmp(c,"<<")==0||strcmp(c,">>")==0)
    {
        return 6;
    }
    else if(strcmp(c,"<=")==0||strcmp(c,">=")==0||strcmp(c,">")==0||strcmp(c,"<")==0)
    {
        return 5;
    }
    else if(strcmp(c,"==")==0||strcmp(c,"!=")==0)
    {
        return 4;
    }
    else if(strcmp(c,"&")==0)
    {
        return 3;
    }
    else if(strcmp(c,"^")==0)
    {
        return 2;
    }
    else if(strcmp(c,"|")==0)
    {
        return 1;
    }
}


void create_stack2(Stack** ptr)
{
    *ptr=(Stack*)malloc(sizeof(Stack));
    (*ptr)->top=0;
}

void push_stack_array_2(Stack** ptr,char c[])
{
    ++((*ptr)->top);
    strcpy((*ptr)->op[(*ptr)->top],c);
}

char* pop_stack_array_2(Stack** ptr)
{
    char* c=malloc(3);
    strcpy(c,(*ptr)->op[(*ptr)->top]);
    (*ptr)->top=(*ptr)->top-1;
    return c;
}

int evaluvate(char d[],int n1,int n2)
{
    if(strcmp(d,"*")==0)
    {
        return n1*n2;
    }
    else if(strcmp(d,"/")==0)
    {
        return n1/n2;
    }
    else if(strcmp(d,"%")==0)
    {
        return n1%n2;
    }
    else if(strcmp(d,"+")==0)
    {
        return n1+n2;
    }
    else if(strcmp(d,"-")==0)
    {
        return n1-n2;
    }
    else if(strcmp(d,">>")==0)
    {
        return n1>>n2;
    }
    else if(strcmp(d,"<<")==0)
    {
        return n1<<n2;
    }
    else if(strcmp(d,"<")==0)
    {
        return n1<n2;
    }
    else if(strcmp(d,"<=")==0)
    {
        return n1<=n2;
    }
    else if(strcmp(d,">")==0)
    {
        return n1>n2;
    }
    else if(strcmp(d,">=")==0)
    {
        return n1>=n2;
    }
    else if(strcmp(d,"==")==0)
    {
        return n1==n2;
    }
    else if(strcmp(d,"!=")==0)
    {
        return n1!=n2;
    }
    else if(strcmp(d,"&")==0)
    {
        return n1&n2;
    }
    else if(strcmp(d,"^")==0)
    {
        return n1^n2;
    }
    else if(strcmp(d,"|")==0)
    {
        return n1|n2;
    }
}

int operate(char s[])
{
    int i=0,f=0,n=0,n1=0,n2=0,n3=0,r=0;;
    char p[3];
    char *d;
    Stack* stack;
    create_stack2(&stack);
    Stackop* stackop;
    create_stack_3(&stackop);
    while(s[i]!='#')
    {
        if(s[i]=='-'&&s[i+1]>='0'&&s[i+1]<='9'&&f==0)
        {
            r=1;
            ++i;
        }
        if(s[i]>='0'&&s[i]<='9')
        {
            n=n*10;
            n+=(s[i]-'0');
            ++i;
        }
        else if(s[i]==' ')
        {
            if(f==1)
            {
                f=0;
            }
            else
            {
                if(r==1)
                {
                    push_stack_arr_3(&stackop,-n);
                }
                else
                {
                    push_stack_arr_3(&stackop,n);
                }
                r=0;
                n=0;
                f=1;
            }
            ++i;
        }
        else if(f==1)
        {
            char p[3];
            if(s[i+1]==' ')
            {
                p[0]=s[i];
                p[1]='\0';
                ++i;
            }
            else
            {
                p[0]=s[i];
                p[1]=s[i+1];
                p[2]='\0';
                i=i+2;
            }
            while((*stack).top!=0&&prec(p)<=prec((*stack).op[(*stack).top]))
            {
                d=pop_stack_array_2(&stack);
                n2=pop_stack_arr_3(&stackop);
                n1=pop_stack_arr_3(&stackop);
                n3=evaluvate(d,n1,n2);
                push_stack_arr_3(&stackop,n3);
            }
            push_stack_array_2(&stack,p);
        }
    }
    while((*stack).top!=0)
    {
        d=pop_stack_array_2(&stack);
        n2=pop_stack_arr_3(&stackop);
        n1=pop_stack_arr_3(&stackop);
        n3=evaluvate(d,n1,n2);
        push_stack_arr_3(&stackop,n3);
    }
    int y=(*stackop).val[0];
    free(stack);
    free(stackop);
    return y;
}

void in_to_post(char s[])
{
    int i=0,f=0,n=0;
    char p[3];
    Stack* stack;
    stack=create_stack(stack);
    while(s[i]!='#')
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            n=n*10;
            n+=(s[i]-'0');
            ++i;
        }
        else if(s[i]==' ')
        {
            if(f==1)
            {
                f=0;
            }
            else
            {
                printf("%d ",n);
                n=0;
                f=1;
            }
            ++i;
        }
        else if(f==1)
        {
            char p[3];
            if(s[i+1]==' ')
            {
                p[0]=s[i];
                p[1]='\0';
                ++i;
            }
            else
            {
                p[0]=s[i];
                p[1]=s[i+1];
                p[2]='\0';
                i=i+2;
            }
            while (stack->top!=0&&prec(p)<=prec(stack->op[stack->top]))
            {
                stack=pop_stack_arr(stack);
            }
            stack=push_stack_arr(stack,p);
        }
    }
    while(stack->top!=0)
    {
        stack=pop_stack_arr(stack);
    }
    free(stack);
}

int check_error(char s[])
{
    int f=0,i=0,n=0;
    while(s[i]!='#')
    {
        if(s[i]=='-'&&s[i+1]>='0'&&s[i+1]<='9'&&f==0)
        {
            ++i;
        }
        else if(s[i]>='0'&&s[i]<='9'&&f==0)
        {
            ++i;
        }
        else if(s[i]==' '&&f==0)
        {
            f=1;
            ++i;
        }
        else if(s[i]==' '&&f==1)
        {
            f=0;
            ++i;
        }
        else if(f==1)
        {
            char p[3];
            if(s[i+1]==' ')
            {
                p[0]=s[i];
                p[1]='\0';
                ++i;
            }
            else
            {
                p[0]=s[i];
                p[1]=s[i+1];
                p[2]='\0';
                i=i+2;
            }
            if(prec(p)==0)
            {
                n=1;
                break;
            }
        }
        else if(f==0)
        {
            n=1;
            break;
        }
    }
    if(f==0)
    {
        n=1;
    }
    return n;
}

unsigned long long int fact(int n)
{
    if(n==0)
    {
        return 1;
    }
    return n*fact(n - 1);
}

void swap_num(int a[],int i1,int i2)
{
    int t;
    t=a[i1];
    a[i1]=a[i2];
    a[i2]=t;
}

void kthpermutation(int a[],int n,unsigned long long int k)
{
    unsigned long long int c;
    for(int i=0;i<n-1;++i)
    {
        c=(k-1)/fact(n-i-1);
        if(c!=0)
        {
            swap_num(a,i,c+i);
            k=k-c*fact(n-i-1);
            int j=c+i;
            while(j>i+1)
            {
                if(a[j]>a[j-1])
                {
                    break;
                }
                else
                {
                    swap_num(a,j-1,j);
                }
            }
        }

    }
}

void enqueue_queue_2(Node** head,Node** tail,int val)
{
    Node* newnode;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->val=val;
    newnode->next=NULL;
    if(*head==NULL)
    {
        *head=newnode;
    }
    else
    {
        (*tail)->next=newnode;
    }
    *tail=newnode;
}

void dequeue_queue_2(Node** head,Node** tail)
{
    Node* ptr;
    int val;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=*head;
    val=ptr->val;
    *head=(*head)->next;
    ptr->next=NULL;
    free(ptr);
}

void push_stack_2(Node** head, int val)
{
    Node* newnode;
    newnode=(Node*)malloc(sizeof(Node));
    newnode->val=val;
    newnode->next=(*head);
    (*head)=newnode;
}

bool is_empty_2(Node** head)
{
    if(*head==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void pop_stack_2(Node** head)
{
    Node* ptr;
    int val;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=*head;
    val=ptr->val;
    *head=(*head)->next;
    ptr->next=NULL;
    free(ptr);
}

int checkstackpermutation(int a[],int b[],int n)
{
    Node* ih;
    Node* it;
    ih=NULL;
    it=NULL;
    for (int i=0;i<n;i++)
    {
        enqueue_queue_2(&ih,&it,a[i]);
    }
    Node* oh;
    Node* ot;
    oh=NULL;
    ot=NULL;
    for (int i=0;i<n;i++)
    {
        enqueue_queue_2(&oh,&ot,b[i]);
    }
    Node* st;
    st=NULL;
    while(!is_empty_2(&ih))
    {
        int ele=(*ih).val;
        dequeue_queue_2(&ih,&it);
        if (ele==(*oh).val)
        {
            dequeue_queue_2(&oh,&ot);
            while (!is_empty_2(&st))
            {
                if ((*st).val==(*oh).val)
                {
                    pop_stack_2(&st);
                    dequeue_queue_2(&oh,&ot);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            push_stack_2(&st,ele);
        }
    }
    int p=is_empty_2(&ih);
    int q=is_empty_2(&st);
    free_list(&ih);
    free_list(&it);
    free_list(&oh);
    free_list(&ot);
    free_list(&st);
    return p&&q;
}

unsigned long long int catalan(int n)
{
    unsigned long long int res=1;
    for (int i=0; i<n; ++i)
    {
        res*=((2*n) - i);
        res/=(i + 1);
    }
    res/=n+1;
    return res;
}

int main()
{
    int t,z;
    scanf("%d%d\n",&t,&z);
    while(t>0)
    {
        char q;
        scanf(" %c ",&q);
        if(q=='S')
        {
            int n;
            scanf("%d",&n);
            Node* head;
            head=NULL;
            while(n>(-4))
            {
                if(n>0)
                {
                    push_stack(&head,n);
                }
                else if(n==0)
                {
                    is_empty(&head);
                }
                else if(n==-1)
                {
                    pop_stack(&head);
                }
                else if(n==-2)
                {
                    printf("NF ");
                }
                else if(n==-3)
                {
                    size(&head);
                }
                scanf("%d",&n);
            }
            char c;
            scanf("%c",&c);
            while(c!='\n')
            {
                scanf("%c",&c);
            }
            printf("\n");
            free_list(&head);
        }
        else if(q=='Q')
        {
            int n;
            scanf("%d",&n);
            Node* head;
            Node* tail;
            head=NULL;
            tail=NULL;
            while(n>(-4))
            {
                if(n>0)
                {
                    enqueue_queue(&head,&tail,n);
                }
                else if(n==0)
                {
                    is_empty(&head);
                }
                else if(n==-1)
                {
                    dequeue_queue(&head,&tail);
                }
                else if(n==-2)
                {
                    printf("NF ");
                }
                else if(n==-3)
                {
                    size(&head);
                }
                scanf("%d",&n);
            }
            char c;
            scanf("%c",&c);
            while(c!='\n')
            {
                scanf("%c",&c);
            }
            printf("\n");
            free_list(&head);
        }
        else if(q=='I')
        {
            char s[100];
            scanf("%[^\n]%*c",s);
            if(check_error(s)==1)
            {
                printf("Error\n");
            }
            else
            {
                in_to_post(s);
                printf("\n");
            }
        }
        else if(q=='E')
        {
            char s[100];
            scanf("%[^\n]%*c",s);
            if(check_error(s)==1)
            {
                printf("Error\n");
            }
            else
            {
                printf("%d\n",operate(s));
            }
        }
        else if(q=='P')
        {
            int n;
            unsigned long long int k;
            scanf("%d%llu",&n,&k);
            printf("%llu ",catalan(n));
            int a[n],b[n];
            for(int i=0;i<n;++i)
            {
                a[i]=i+1;
            }
            unsigned long long int k1=1,k2=1;
            while(k1<=k)
            {
                for(int i=0;i<n;++i)
                {
                    b[i]=a[i];
                }
                kthpermutation(b,n,k2);
                if(checkstackpermutation(a,b,n)==1)
                {
                    ++k1;
                }
                ++k2;
            }
            for(int i=0;i<n;++i)
            {
                if(i==n-1)
                {
                    printf("%d\n",b[i]);
                }
                else
                {
                    printf("%d ",b[i]);
                }
            }
        }
        --t;
    }
}
