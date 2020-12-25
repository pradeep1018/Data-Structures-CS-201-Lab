#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int bellman(vector<pair<int,int>> al[],int n,int dist[])
{
    int f=1,c=0;
    for(int i=0;i<n-1;++i)
    {
        c=0;
        for(int u=0;u<n;++u)
        {
            if(dist[u]!=999999)
            {
                int w,v;
                for(int j=0;j<al[u].size();++j)
                {
                    v=al[u][j].first;
                    w=al[u][j].second;
                    if(dist[v]>dist[u]+w)
                    {
                        dist[v]=dist[u]+w;
                        c=1;
                    }
                }
            }
        }
        if(c==0)
        {
            break;
        }
    }
    if(c==1)
    {
        for(int u=0;u<n;++u)
        {
            int w,v;
            for(int j=0;j<al[u].size();++j)
            {
                v=al[u][j].first;
                w=al[u][j].second;
                if(dist[v]>dist[u]+w&&dist[u]!=999999)
                {
                    f=0;
                    break;
                }
            }
            if(f==0)
            {
                break;
            }
        }
    }
    return f;
}

/* array based implementation starts */

/* function to find the vertex with minimum distance */
int arrayfindmin(int pq[][2],int n)
{
    int mi=0;
    for(int i=1;i<n;++i)
    {
        if(pq[i][0]<pq[mi][0])
        {
            mi=i;
        }
    }
    return mi;
}

void arraydijkstra(vector<pair<int,int>> al[],int n,int dist[],int s)
{
    dist[s]=0;
    int pq[n][2],in[n],si=n; /* array pq is a priority queue storing dist of a vertex from the source and vertex */
    for(int i=0;i<n;++i)
    {
        pq[i][0]=dist[i];
        pq[i][1]=i;
        in[i]=i; /* stores the position of vertex in array pq */
    }
    int mi;
    while(si>0)
    {
        /* extractmin operation */
        mi=arrayfindmin(pq,si);
        int u=pq[mi][1];
        pq[mi][0]=pq[si-1][0];
        pq[mi][1]=pq[si-1][1];
        in[pq[mi][1]]=mi;
        --si;
        int w,v;
        for(int i=0;i<al[u].size();++i)
        {
            v=al[u][i].first;
            w=al[u][i].second;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                pq[in[v]][0]=dist[v]; /* decreasekey operation */
            }
        }
    }
}

/* array based implementation ends */

/* binary heap based implementation starts */

void binaryinsertval(vector<pair<int,int>> &pq,int pos[],int v1,int v2)
{
    pq.push_back({v1,v2});
    int i=pq.size()-1;
    /* updating the heap to maintain the property of binary heap */
    while(i>0&&pq[(i-1)/2].first>pq[i].first)
    {
        pair<int,int> temp=pq[i];
        pq[i]=pq[(i-1)/2];
        pq[(i-1)/2]=temp;
        pos[pq[i].second]=i;
        pos[pq[(i-1)/2].second]=(i-1)/2;
        i=(i-1)/2;
    }
}

/* heapify operation performed while extractmin */
void binaryminheapify(vector<pair<int,int>> &pq,int pos[],int i)
{
    int l=2*i+1,r=2*i+2;
    int s=i;
    if(l<pq.size()&&pq[l].first<pq[i].first)
    {
        s=l;
    }
    if(r<pq.size()&&pq[r].first<pq[s].first)
    {
        s=r;
    }
    if(s!=i)
    {
        pair<int,int> temp=pq[i];
        pq[i]=pq[s];
        pq[s]=temp;
        pos[pq[i].second]=i;
        pos[pq[s].second]=s;
        binaryminheapify(pq,pos,s);
    }
}

int binaryextractmin(vector<pair<int,int>> &pq,int pos[])
{
    int rv=pq[0].second;
    pq[0]=pq[pq.size()-1];
    pos[pq[0].second]=0;
    pq.pop_back();
    binaryminheapify(pq,pos,0);
    return rv;
}

void binarydecreasekey(vector<pair<int,int>> &pq,int pos[],int v1,int v2)
{
    int i=pos[v2];
    pq[i].first=v1;
    while(i>0&&pq[(i-1)/2].first>pq[i].first)
    {
        pair<int,int> temp=pq[i];
        pq[i]=pq[(i-1)/2];
        pq[(i-1)/2]=temp;
        pos[pq[i].second]=i;
        pos[pq[(i-1)/2].second]=(i-1)/2;
        i=(i-1)/2;
    }
}

void binarydijkstra(vector<pair<int,int>> al[],int n,int dist[],int s)
{
    dist[s]=0;
    vector<pair<int,int>> pq;
    int pos[n]; /* stores index of each vertex in the heap for efficient decreasekey */
    for(int i=0;i<n;++i)
    {
        pos[i]=i;
        binaryinsertval(pq,pos,dist[i],i);
    }
    while(pq.size()>0)
    {
        int u=binaryextractmin(pq,pos);
        int w,v;
        for(int i=0;i<al[u].size();++i)
        {
            v=al[u][i].first;
            w=al[u][i].second;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                binarydecreasekey(pq,pos,dist[v],v);
            }
        }
    }
}

/* binary heap based implementation ends */

/* binomial heap based implementation starts */


struct binomialnode
{
    pair<int,int> val;
    int degree;
    binomialnode *child, *sibling, *parent;
};

binomialnode* binomialnewnode(pair<int,int> val)
{
    binomialnode *temp=new binomialnode;
    temp->val=val;
    temp->degree=0;
    temp->child=NULL;
    temp->parent=NULL;
    temp->sibling=NULL;
    return temp;
}

/* joining two binomial heaps */
list<binomialnode*> binomialunionheap(list<binomialnode*> l1,list<binomialnode*> l2)
{
    list<binomialnode*>::iterator i1=l1.begin();
    list<binomialnode*>::iterator i2=l2.begin();
    list<binomialnode*> l3;
    while(i1!=l1.end()&&i2!=l2.end())
    {
        if((*i1)->degree<(*i2)->degree)
        {
            l3.push_back(*i1);
            ++i1;
        }
        else
        {
            l3.push_back(*i2);
            ++i2;
        }
    }
    while(i1!=l1.end())
    {
        l3.push_back(*i1);
        ++i1;
    }
    while(i2!=l2.end())
    {
        l3.push_back(*i2);
        ++i2;
    }
    return l3;
}

/* merging two trees */
binomialnode* binomialmergetrees(binomialnode *t1, binomialnode *t2)
{
    if((t1->val).first>(t2->val).first)
    {
        binomialnode *a;
        a=t1;
        t1=t2;
        t2=a;
    }
    t2->parent=t1;
    t2->sibling=t1->child;
    t1->child=t2;
    ++t1->degree;
    return t1;
}

/* restructuring heap to maintain the property of binomial heap */
void binomialadjust(list<binomialnode*> &pq)
{
    list<binomialnode*>::iterator i1=pq.begin();
    list<binomialnode*>::iterator i2=pq.begin();
    list<binomialnode*>::iterator i3=pq.begin();
    if (pq.size()==2)
    {
        i2=i1;
        ++i2;
        i3=pq.end();
    }
    else
    {
        ++i2;
        i3=i2;
        ++i3;
    }
    while(i1!=pq.end())
    {
        if(i2==pq.end())
        {
            ++i1;
        }
        else if((*i1)->degree<(*i2)->degree)
        {
            ++i1;
            ++i2;
            if(i3!=pq.end())
            {
                ++i3;
            }
        }
        else if(i3!=pq.end()&&(*i1)->degree==(*i2)->degree&&(*i1)->degree==(*i3)->degree)
        {
            ++i1;
            ++i2;
            ++i3;
        }
        else if((*i1)->degree==(*i2)->degree)
        {
            *i1=binomialmergetrees(*i1,*i2);
            i2=pq.erase(i2);
            if(i3!=pq.end())
            {
                ++i3;
            }
        }
    }
}

void binomialinserttreeinheap(list<binomialnode*> &pq,binomialnode *tree)
{
    list<binomialnode*> temp;
    temp.push_back(tree);
    pq=binomialunionheap(pq,temp);
    binomialadjust(pq);
}

void binomialinsertval(list<binomialnode*> &pq,binomialnode** nds,int v1,int v2)
{
    pair<int,int> val={v1,v2};
    binomialnode *temp=binomialnewnode(val);
    nds[v2]=temp;
    binomialinserttreeinheap(pq,temp);
}

/* gets the node with min distance in the list */
binomialnode* binomialgetmin(list<binomialnode*> &pq)
{
    list<binomialnode*>::iterator i=pq.begin();
    binomialnode *temp=*i;
    while (i!=pq.end())
    {
        if (((*i)->val).first<(temp->val).first)
        {
            temp=*i;
        }
        ++i;
    }
    return temp;
}

/* removes minimum node from the list and returns a list with the child of minimum node as head */
list<binomialnode*> binomialremovemin(binomialnode *t)
{
    list<binomialnode*> th;
    binomialnode *temp1=t->child;
    binomialnode *temp2;
    while(temp1!=NULL)
    {
        temp2=temp1;
        temp1=temp1->sibling;
        temp2->sibling=NULL;
        th.push_front(temp2);
    }
    return th;
}

int binomialextractmin(list<binomialnode*> &pq)
{
    list<binomialnode*> h1,h2;
    binomialnode *temp;
    temp=binomialgetmin(pq);
    list<binomialnode*>::iterator i;
    i=pq.begin();
    /* loop to append all the trees except the tree having minimum node as head into a new list */
    while (i!=pq.end())
    {
        if (*i!=temp)
        {
            h1.push_back(*i);
        }
        ++i;
    }
    h2=binomialremovemin(temp); /* h2 is a list of size 1 having the child of minimum node as head */
    pq=binomialunionheap(h1,h2);
    binomialadjust(pq);
    int u=(temp->val).second;
    temp=NULL;
    delete temp;
    return u; /* returns the vertex that got removed from the heap */
}

void binomialdecreasekey(binomialnode** nds,int v,int dist)
{
    binomialnode* x=nds[v];
    (x->val).first=dist;
    binomialnode* y=x->parent;
    while(y!=NULL&&(x->val).first<(y->val).first)
    {
        pair<int,int> temp=x->val;
        x->val=y->val;
        y->val=temp;
        nds[(x->val).second]=x;
        nds[(y->val).second]=y;
        x=y;
        y=x->parent;
    }
}

void binomialdijkstra(vector<pair<int,int>> al[],int n,int dist[],int s)
{
    dist[s]=0;
    list<binomialnode*> pq; /* list maintaining the roots of all binomial trees */
    binomialnode** nds=new binomialnode*[n]; /* array of pointers where ith pointer points to vertex i in binomial heap */
    for(int i=0;i<n;++i)
    {
        nds[i]=NULL;
        binomialinsertval(pq,nds,dist[i],i);
    }
    while(pq.size()>0)
    {
        int u=binomialextractmin(pq);
        nds[u]=NULL;
        int w,v;
        for(int i=0;i<al[u].size();++i)
        {
            v=al[u][i].first;
            w=al[u][i].second;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                binomialdecreasekey(nds,v,dist[v]);
            }
        }
    }
    delete []nds;
}

/* binomial heap based implementation ends */

/* fibonacci heap based implementation starts */

struct fibonaccinode
{
    pair<int,int> val;
    int degree;
    fibonaccinode *parent;
    fibonaccinode *child;
    fibonaccinode *left;
    fibonaccinode *right;
    bool mark;
};

fibonaccinode* newnode(pair<int,int> val)
{
    fibonaccinode *temp=new fibonaccinode;
    temp->val=val;
    temp->degree=0;
    temp->child=NULL;
    temp->parent=NULL;
    temp->left=temp;
    temp->right=temp;
    temp->mark=false;
    return temp;
}

fibonaccinode* fibonaccimergetrees(fibonaccinode* x,fibonaccinode *y)
{
    if(x==NULL)
    {
        return y;
    }
    if(y==NULL)
    {
        return x;
    }
    if((x->val).first>(y->val).first)
	{
		fibonaccinode* temp=x;
		x=y;
		y=temp;
	}
    fibonaccinode* xr=x->right;
	fibonaccinode* yl=y->left;
	x->right=y;
	y->left=x;
	xr->left=yl;
	yl->right=xr;
	return x;
}

fibonaccinode* fibonacciinsertval(fibonaccinode** pq,fibonaccinode* head,int &num,int v1,int v2)
{
    pair<int,int> val={v1,v2};
    fibonaccinode *temp=newnode(val);
    pq[v2]=temp;
    ++num;
    head=fibonaccimergetrees(head,temp);
    return head;
}

void fibonacciunparent(fibonaccinode* x)
{
	if(x==NULL)
    {
		return;
    }
	fibonaccinode* y = x;
	do{
		y->parent=NULL;
		y=y->right;
	}while(y!=x);
}

void fibonacciremove(fibonaccinode* x)
{
	if(x->right==x)
	{
		return;
	}
	fibonaccinode* ls=x->left;
	fibonaccinode* rs=x->right;
	ls->right=rs;
	rs->left=ls;
}

void fibonaccimakechild(fibonaccinode *child,fibonaccinode *parent)
{
	fibonacciremove(child);
	child->left=child;
	child->right=child;
	child->parent=parent;
	parent->child=fibonaccimergetrees(parent->child,child);
	++parent->degree;
	child->mark=false;
}

/* consolidate the roots such that no two trees have same rank */
fibonaccinode* fibonacciconsolidate(fibonaccinode* head,int num)
{
	int d=(int)(log2(num)/log2(1.618034));
	fibonaccinode** a=new fibonaccinode*[d+1];
	for (int i=0;i<d+1;++i)
    {
        a[i]=NULL;
    }
	fibonaccinode* x=head;
	bool flag=false;
	while(true)
	{
		int deg=x->degree;
		while(a[deg]!=NULL)
		{
			fibonaccinode* y=a[deg];
			if(y==x)
			{
				flag=true;
				break;
			}
			if((x->val).first>(y->val).first)
			{
				fibonaccinode* temp=x;
				x=y;
				y=temp;
			}
			fibonaccimakechild(y,x);
			a[deg]=NULL;
			++deg;
		}
		if(flag)
        {
            break;
        }
		a[x->degree]=x;
		x=x->right;
	}
	head=x;
	fibonaccinode* temp=x;
	do{
		if((temp->val).first<(head->val).first)
        {
            head=temp;
        }
		temp=temp->right;
	}while(temp!=x);
	delete []a;
	return head;
}

fibonaccinode* fibonacciextractmin(fibonaccinode* head,int &num,int &u)
{
    fibonaccinode* minnode=head;
    fibonacciunparent(minnode->child);
    minnode=fibonaccimergetrees(minnode,minnode->child);
    fibonacciremove(minnode);
    if(minnode==minnode->right)
    {
        head=NULL;
    }
    else
    {
        head=minnode->right;
        head=fibonacciconsolidate(head,num);
    }
    --num;
    u=(minnode->val).second;
    minnode=NULL;
    delete minnode;
    return head;
}

void fibonaccicut(fibonaccinode* head,fibonaccinode* x,fibonaccinode* y)
{
	fibonacciremove(x);
	if(x->right==x)
	{
		y->child=NULL;
	}
	else
	{
		y->child=x->right;
	}
	--y->degree;
	x->parent=NULL;
	x->right=x;
	x->left=x;
	x->mark=false;
	head=fibonaccimergetrees(head,x);
}

void fibonaccicascadingcut(fibonaccinode* head,fibonaccinode* y)
{
	fibonaccinode* x=y->parent;
	if(x!=NULL)
	{
		if(y->mark==false)
        {
            y->mark=true;
        }
		else
		{
			fibonaccicut(head,y,x);
			fibonaccicascadingcut(head,x);
		}
	}
}

fibonaccinode* fibonaccidecreasekey(fibonaccinode* head,fibonaccinode* x, int dist)
{
	(x->val).first=dist;
	fibonaccinode* y=x->parent;
	if(y!=NULL&&(x->val).first<(y->val).first)
	{
		fibonaccicut(head,x,y);
		fibonaccicascadingcut(head,y);
	}
	if((x->val).first<(head->val).first)
    {
        head=x;
    }
    return head;
}

void fibonaccidijkstra(vector<pair<int,int>> al[],int n,int dist[],int s)
{
    dist[s]=0;
    fibonaccinode* head=NULL; /* head pointer of doubly circular linked list that always points to the minimum node */
    fibonaccinode** pq=new fibonaccinode*[n]; /* array of pointers where ith pointer points to vertex i in binomial heap */
    int num=0,u;
    for(int i=0;i<n;++i)
    {
        pq[i]=NULL;
        head=fibonacciinsertval(pq,head,num,dist[i],i);
    }
    while(num>0)
    {
        head=fibonacciextractmin(head,num,u);
        pq[u]=NULL;
        int w,v;
        for(int i=0;i<al[u].size();++i)
        {
            v=al[u][i].first;
            w=al[u][i].second;
            if(dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                head=fibonaccidecreasekey(head,pq[v],dist[v]);
            }
        }
    }
    delete head;
    delete []pq;
}

/* fibonacci heap based implementation ends */

int main(int argc, char** argv)
{
    int t;
    cin>>t;
    double timetaken[t];
    clock_t a,b;
    int z=0;
    while(t--)
    {
        int n,d;
        cin>>n>>d;
        int in,dist[n][n],distc[n+1];
        vector<pair<int,int>> al[n],alb[n+1];
        for(int i=0;i<n;++i)
        {
            distc[i]=999999;
            alb[n].push_back({i,0});
            for(int j=0;j<n;++j)
            {
                dist[i][j]=999999;
                cin>>in;
                if(i!=j&&in!=999999)
                {
                    al[i].push_back({j,in});
                    alb[i].push_back({j,in});
                }
            }
        }
        distc[n]=0;
        a=clock();
        if(bellman(alb,n+1,distc)==1)
        {
            for(int u=0;u<n;++u)
            {
                for(int i=0;i<al[u].size();++i)
                {
                    int v=al[u][i].first;
                    al[u][i].second=al[u][i].second+distc[u]-distc[v];
                }
            }
            for(int i=0;i<n;++i)
            {
                if(argc==1) /* default case */
                {
                    fibonaccidijkstra(al,n,dist[i],i);
                }
                else
                {
                    if(strcmp(argv[1],"1")==0)
                    {
                        arraydijkstra(al,n,dist[i],i);
                    }
                    else if(strcmp(argv[1],"2")==0)
                    {
                        binarydijkstra(al,n,dist[i],i);
                    }
                    else if(strcmp(argv[1],"3")==0)
                    {
                        binomialdijkstra(al,n,dist[i],i);
                    }
                    else if(strcmp(argv[1],"4")==0)
                    {
                        fibonaccidijkstra(al,n,dist[i],i);
                    }
                    else /* default case */
                    {
                        fibonaccidijkstra(al,n,dist[i],i);
                    }
                }
            }
            for(int i=0;i<n;++i)
            {
                for(int j=0;j<n;++j)
                {
                    if(dist[i][j]!=999999)
                    {
                        cout<<dist[i][j]+distc[j]-distc[i]<<" ";
                    }
                    else
                    {
                        cout<<dist[i][j]<<" ";
                    }
                }
                cout<<endl;
            }
        }
        else
        {
            cout<<-1<<endl;
        }
        b=clock();
        timetaken[z]=double(b-a)/double(CLOCKS_PER_SEC);
        ++z;
    }
    for(int i=0;i<z;++i)
    {
        cout<<timetaken[i]<<fixed<<setprecision(5)<<" "; /* prints time taken in each test case */
    }
}
