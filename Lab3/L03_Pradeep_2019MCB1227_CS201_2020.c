#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
}Node;

void free_tree(Node* root)
{
    if(root!=NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Node* createnode(int val)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr->val=val;
    ptr->left=NULL;
    ptr->right=NULL;
    return ptr;
}

Node* insert_bst(Node* root, int val)
{
    if(root==NULL)
    {
        return createnode(val);
    }
    if(val<root->val)
    {
        root->left=insert_bst(root->left,val);
    }
    else if(val>root->val)
    {
        root->right=insert_bst(root->right,val);
    }
    return root;
}

Node* maxval(Node* root)
{
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    ptr=root;
    while(ptr->right!=NULL)
    {
        ptr=ptr->right;
    }
    return ptr;
}

Node* delete_bst(Node* root, int val)
{
    if(root==NULL)
    {
        return root;
    }
    if(val<root->val)
    {
        root->left=delete_bst(root->left,val);
    }
    else if(val>root->val)
    {
        root->right=delete_bst(root->right,val);
    }
    else
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        if(root->right==NULL)
        {
            ptr=root->left;
            free(root);
            return ptr;
        }
        else if(root->left==NULL)
        {
            ptr=root->right;
            free(root);
            return ptr;
        }
        else
        {
            ptr=maxval(root->left);
            root->val=ptr->val;
            root->left=delete_bst(root->left,root->val);
        }
    }
}

int height(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int lh=height(root->left);
        int rh=height(root->right);
        if (lh>rh)
        {
           return lh+1;
        }
       else
       {
           return rh+1;
       }
   }
}

int heightdiff(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        return height(root->left)-height(root->right);
    }
}

Node* rotateleft(Node *x)
{
    Node* y;
    y=(Node*)malloc(sizeof(Node));
    Node* z;
    z=(Node*)malloc(sizeof(Node));
    y=x->right;
    z=y->left;
    y->left=x;
    x->right=z;
    return y;
}

Node* rotateright(Node *x)
{
    Node* y;
    y=(Node*)malloc(sizeof(Node));
    Node* z;
    z=(Node*)malloc(sizeof(Node));
    y=x->left;
    z=y->right;
    y->right=x;
    x->left=z;
    return y;
}

Node* insert_avl(Node* root,int val)
{
    if(root==NULL)
    {
        return createnode(val);
    }
    if(val<root->val)
    {
        root->left=insert_avl(root->left,val);
    }
    else if(val>root->val)
    {
        root->right=insert_avl(root->right,val);
    }
    else
    {
        return root;
    }
    int hdiff=heightdiff(root);
    if(hdiff>1&&(root->left)!=NULL&&val<(root->left->val))
    {
        return rotateright(root);
    }
    else if(hdiff<-1&&root->right!=NULL&&val>root->right->val)
    {
        return rotateleft(root);
    }
    else if(hdiff>1&&root->left!=NULL&&val>root->left->val)
    {
        root->left=rotateleft(root->left);
        return rotateright(root);
    }
    else if(hdiff<-1&&root->right!=NULL&&val<root->right->val)
    {
        root->right=rotateright(root->right);
        return rotateleft(root);
    }
    return root;
}

Node* delete_avl(Node* root,int val)
{
    if(root==NULL)
    {
        return root;
    }
    if(val<root->val)
    {
        root->left=delete_avl(root->left,val);
    }
    else if(val>root->val)
    {
        root->right=delete_avl(root->right,val);
    }
    else
    {
        Node* ptr;
        ptr=(Node*)malloc(sizeof(Node));
        if(root->right==NULL)
        {
            ptr=root->left;
            free(root);
            return ptr;
        }
        else if(root->left==NULL)
        {
            ptr=root->right;
            free(root);
            return ptr;
        }
        ptr=maxval(root->left);
        root->val=ptr->val;
        root->left=delete_avl(root->left,root->val);
    }
    int hdiff=heightdiff(root);
    if(hdiff>1&&heightdiff(root->left)>=0)
    {
        return rotateright(root);
    }
    else if(hdiff<-1&&heightdiff(root->right)<=0)
    {
        return rotateleft(root);
    }
    else if (hdiff>1&&heightdiff(root->left)<0)
    {
        root->left=rotateleft(root->left);
        return rotateright(root);
    }
    else if (hdiff<-1&&heightdiff(root->right)>0)
    {
        root->right=rotateright(root->right);
        return rotateleft(root);
    }
    return root;
}

int find_node(Node* root,int x)
{
    if(root==NULL)
    {
        return 0;
    }
    else if(x==root->val)
    {
        return 1;
    }
    else if(x<root->val)
    {
        return find_node(root->left,x);
    }
    else
    {
        return find_node(root->right,x);
    }
}

int leafcount(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else if(root->left==NULL&&root->right==NULL)
    {
        return 1;
    }
    else
    {
        return leafcount(root->left)+leafcount(root->right);
    }
}

int nodecount(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        return 1+nodecount(root->left)+nodecount(root->right);
    }
}

typedef struct stack
{
    int top;
    Node* nodes[5000];
}Stack;

void create_stack(Stack** ptr)
{
    *ptr=(Stack*)malloc(sizeof(Stack));
    (*ptr)->top=-1;
}

void push_stack(Stack** ptr,Node* root)
{
    ++((*ptr)->top);
    (*ptr)->nodes[(*ptr)->top]=root;
}

void pop_stack(Stack** ptr)
{
    --((*ptr)->top);
}

void preorder(Node* root)
{
    if (root!=NULL)
    {
        Stack* st;
        create_stack(&st);
        push_stack(&st,root);
        while((*st).top!=-1)
        {
            Node* nodet;
            nodet=NULL;
            nodet=(*st).nodes[(*st).top];
            printf("%d ", nodet->val);
            pop_stack(&st);
            if(nodet->right!=NULL)
            {
                push_stack(&st,nodet->right);
            }
            if(nodet->left!=NULL)
            {
                push_stack(&st,nodet->left);
            }
        }
    }
}

void inorder(Node* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->val);
        inorder(root->right);
    }
}

void postorder(Node* root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->val);
    }
}

void printlevel(Node* root, int i)
{
    if(root!=NULL)
    {
        if(i==1)
        {
            printf("%d ",root->val);
        }
        else if(i>1)
        {
            printlevel(root->left,i-1);
            printlevel(root->right,i-1);
        }
    }
}

void levelorder(Node* root)
{
    for (int i=1;i<=height(root);++i)
    {
        printlevel(root,i);
    }
}

int levelwidth(Node* root,int i)
{
    if(root==NULL)
    {
        return 0;
    }
    else if(i==1)
    {
        return 1;
    }
    else if (i>1)
    {
        return levelwidth(root->left,i-1)+levelwidth(root->right,i-1);
    }
}

int width(Node* root)
{
    int lw,w=0;
    for(int i=1;i<=height(root);i++)
    {
        lw=levelwidth(root, i);
        if(lw>w)
        {
            w=lw;
        }
    }
    return w;
}

int ancestor(Node* root,int i,int j)
{
    if(i<root->val&&j<root->val)
    {
        return ancestor(root->left,i,j);
    }
    else if(i>root->val&&j>root->val)
    {
        return ancestor(root->left,i,j);
    }
    else if(i<=(root->val)&&j>=(root->val))
    {
        return root->val;
    }
}

Node* reach(Node* root,int x)
{
    if(x==root->val)
    {
        return root;
    }
    else if(x<root->val)
    {
        return reach(root->left,x);
    }
    else
    {
        return reach(root->right,x);
    }
}

void printroute(Node* root,int j)
{
    if(j==root->val)
    {
        printf("%d",j);
    }
    else if(j<root->val)
    {
        printf("%d L ",root->val);
        printroute(root->left,j);
    }
    else
    {
        printf("%d R ",root->val);
        printroute(root->right,j);
    }
}

int diameter(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int lh=height(root->left);
        int rh=height(root->right);
        return max(lh+rh+1,max(diameter(root->left),diameter(root->right)));
    }
}

int sumrightboundary(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        if(root->right)
        {
            return root->val+sumrightboundary(root->right);
        }
        else if(root->left)
        {
            return root->val+sumrightboundary(root->left);
        }
    }
}

int sumleaves(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        if (root->left==NULL&&root->right==NULL)
        {
            return root->val;
        }
        return sumleaves(root->left)+sumleaves(root->right);
    }
}

int sumleftboundary(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        if(root->left)
        {
            return root->val+sumleftboundary(root->left);
        }
        else if(root->right)
        {
            return root->val+sumleftboundary(root->right);
        }
    }
}

int sumboundary(Node* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int a=root->val;
        int b=sumrightboundary(root->right);
        int c=sumleaves(root->right);
        int d=sumleaves(root->left);
        int e=sumleftboundary(root->left);
        return a+b+c+d+e;
    }
}

void printrightboundary(Node* root)
{
    if(root!=NULL)
    {
        if(root->right)
        {
            printf("%d ",root->val);
            printrightboundary(root->right);
        }
        else if(root->left)
        {
            printf("%d ",root->val);
            printrightboundary(root->left);
        }
    }
}

void printleaves(Node* root)
{
    if(root!=NULL)
    {
        printleaves(root->right);
        if (root->left==NULL&&root->right==NULL)
        {
            printf("%d ",root->val);
        }
        printleaves(root->left);
    }
}

void printleftboundary(Node* root)
{
    if(root!=NULL)
    {
        if(root->left)
        {
            printleftboundary(root->left);
            printf("%d ",root->val);
        }
        else if(root->right)
        {
            printf("%d ",root->val);
            printleftboundary(root->right);
        }
    }
}

void printboundary(Node* root)
{
    if(root!=NULL)
    {
        printf("%d ", root->val);
        printrightboundary(root->right);
        printleaves(root->right);
        printleaves(root->left);
        printleftboundary(root->left);
    }
}

int main()
{
    int z,f=1;
    Node* root;
    root=NULL;
    scanf("%d",&z);
    while(z--)
    {
        char c;
        scanf(" %c",&c);
        if(c=='T')
        {
            free_tree(root);
            f=1;
            root=NULL;
            int val;
            char temp,temp2;
            scanf("%c",&temp2);
            if(temp2==' ')
            {
                do
                {
                    scanf("%d%c",&val,&temp);
                    if(val>0)
                    {
                        root=insert_bst(root,val);
                    }
                    else if(val<0)
                    {
                        root=delete_bst(root,-val);
                    }
                }while(temp!='\n'&&temp!=EOF);
            }
        }
        else if(c=='H')
        {
            free_tree(root);
            f=2;
            root=NULL;
            int val;
            char temp,temp2;
            scanf("%c",&temp2);
            if(temp2==' ')
            {
                do
                {
                    scanf("%d%c",&val,&temp);
                    if(val>0)
                    {
                        root=insert_avl(root,val);
                    }
                    else if(val<0)
                    {
                        root=delete_avl(root,-val);
                    }
                }while(temp!='\n'&&temp!=EOF);
            }
        }
        else if(c=='A')
        {
            if(f==0)
            {
                f=1;
            }
            int val;
            char temp,temp2;
            scanf("%c",&temp2);
            if(temp2==' ')
            {
                do
                {
                    scanf("%d%c",&val,&temp);
                    if(val>0)
                    {
                        if(f==1)
                        {
                            root=insert_bst(root,val);
                        }
                        else
                        {
                            root=insert_avl(root,val);
                        }
                    }
                }while(temp!='\n'&&temp!=EOF);
            }
        }
        else if(c=='U')
        {
            int val;
            char temp,temp2;
            scanf("%c",&temp2);
            if(temp2==' ')
            {
                do
                {
                    scanf("%d%c",&val,&temp);
                    if(val>0)
                    {
                        if(f==1)
                        {
                            root=delete_bst(root,val);
                        }
                        else if(f==2)
                        {
                            root=delete_avl(root,val);
                        }
                    }
                }while(temp!='\n'&&temp!=EOF);
            }
        }
        else if(c=='F')
        {
            int x;
            scanf("%d",&x);
            if(find_node(root,x)==1)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
        else if(c=='Q')
        {
            printf("%d\n",leafcount(root));
        }
        else if(c=='N')
        {
            printf("%d\n",nodecount(root));
        }
        else if(c=='P')
        {
            preorder(root);
            printf("\n");
        }
        else if(c=='I')
        {
            inorder(root);
            printf("\n");
        }
        else if(c=='S')
        {
            postorder(root);
            printf("\n");
        }
        else if(c=='L')
        {
            levelorder(root);
            printf("\n");
        }
        else if(c=='D')
        {
            printf("%d\n",height(root)-1);
        }
        else if(c=='W')
        {
            printf("%d\n",width(root));
        }
        else if(c=='C')
        {
            int i,j;
            scanf("%d%d",&i,&j);
            if(find_node(root,i)==1&&find_node(root,j)==1)
            {
                if(i==j)
                {
                    printf("%d\n",i);
                }
                else
                {
                    if(i>j)
                    {
                        int temp=i;
                        i=j;
                        j=temp;
                    }
                    printf("%d\n",ancestor(root,i,j));
                }
            }
            else
            {
                printf("-1\n");
            }
        }
        else if(c=='R')
        {
            int i,j;
            scanf("%d%d",&i,&j);
            if(find_node(root,i)==0)
            {
                printf("Source does not exist\n");
            }
            else if(find_node(root,j)==0)
            {
                printf("Destination does not exist\n");
            }
            else
            {
                if(i==j)
                {
                    printf("%d\n",i);
                }
                else
                {
                    Node* rooti;
                    rooti=NULL;
                    rooti=reach(root,i);
                    if(find_node(rooti,j)==1)
                    {
                        printroute(rooti,j);
                        printf("\n");
                    }
                    else
                    {
                        printf("Unreachable\n");
                    }
                }
            }
        }
        else if(c=='X')
        {
            printf("%d\n",diameter(root));
        }
        else if(c=='Y')
        {
            printf("%d ",sumboundary(root));
            printboundary(root);
            printf("\n");
        }
    }
    return 0;
}
