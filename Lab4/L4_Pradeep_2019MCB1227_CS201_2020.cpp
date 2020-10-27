#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

void bfs(vector<int> al[],int n,int d,int s,int edge[4],int dist[])
{
    int color[n],parent[n];
    for(int i=0;i<n;++i)
    {
        dist[i]=999999;
        color[i]=0;
        parent[i]=-1;
    }
    dist[s-1]=0;
    color[s-1]=1;
    queue<int> q;
    q.push(s-1);
    if(d==0)
    {
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            int te=0,ce=0,be;
            for (int i=0;i<al[u].size();i++)
            {
                int v=al[u][i];
                if(color[v]==0)
                {
                    color[v]=1;
                    dist[v]=dist[u]+1;
                    parent[v]=u;
                    ++te;
                    q.push(v);
                }
                else if(color[v]==1)
                {
                    ++ce;
                }
            }
            edge[0]+=te;
            edge[3]+=ce;
            color[u]=2;
        }
    }
    else
    {
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            int te=0,ce=0,be=0;
            for(int i=0;i<al[u].size();i++)
            {
                int v=al[u][i];
                if(color[v]==0)
                {
                    color[v]=1;
                    dist[v]=dist[u]+1;
                    parent[v]=u;
                    ++te;
                    q.push(v);
                }
                else if(color[v]==1)
                {
                    ++ce;
                }
                else if(color[v]==2)
                {
                    int x=parent[u],f=0;
                    while(x!=-1)
                    {
                        if(x==v)
                        {
                            f=1;
                            break;
                        }
                        else
                        {
                            x=parent[x];
                        }
                    }
                    if(f==0)
                    {
                        ++ce;
                    }
                    else
                    {
                        ++be;
                    }
                }
            }
            edge[0]+=te;
            edge[1]+=be;
            edge[3]+=ce;
            color[u]=2;
        }
    }
}

void dfs(vector<int> al[],int n,int d,int x,int edge[4],int ft[],int color[])
{
    int parent[n];
    for(int i=0;i<n;++i)
    {
        ft[i]=999999;
        parent[i]=-1;
    }
    stack<int> s;
    s.push(x);
    int time=1;
    if(d==0)
    {
        while(!s.empty())
        {
            int u=s.top();
            for(int i=0;i<al[u].size();i++)
            {
                int v=al[u][i];
                if(color[v]==0)
                {
                    parent[v]=u;
                    s.push(v);
                    color[v]=1;
                    ++time;
                    ++edge[0];
                    break;
                }
                else if(v!=parent[u]&&color[v]==1)
                {
                    ++edge[1];
                }
            }
            if(u==s.top())
            {
                color[u]=2;
                ++time;
                ft[u]=time;
                s.pop();
            }
        }
    }
    else
    {
        while(!s.empty())
        {
            int u=s.top();
            for(int i=0;i<al[u].size();i++)
            {
                int v=al[u][i];
                if(color[v]==0)
                {
                    parent[v]=u;
                    s.push(v);
                    color[v]=1;
                    ++time;
                    ++edge[0];
                    break;
                }
                else if(color[v]==1)
                {
                    ++edge[1];
                }
                else if(color[v]==2)
                {
                    int y=parent[v],f=0;
                    if(y!=u)
                    {
                        while(y!=-1)
                        {
                            if(y==u)
                            {
                                f=1;
                                break;
                            }
                            else
                            {
                                y=parent[y];
                            }
                        }
                        if(f==0)
                        {
                            ++edge[3];
                        }
                        else if(f==1)
                        {
                            ++edge[2];
                        }
                    }
                }
            }
            if(u==s.top())
            {
                color[u]=2;
                ++time;
                ft[u]=time;
                s.pop();
            }
        }
    }
}

int toposort(int n, vector<int> al[], int s[])
{
    vector<int> indeg(n);
    for(int i=0;i<n;++i)
    {
        indeg[i]=0;
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<al[i].size();j++)
        {
            ++indeg[al[i][j]];
        }
    }
    int c=0;
    int v=-1;
    for(int i=0;i<n;++i)
    {
        if(indeg[i]==0)
        {
            ++c;
            v=i;
            break;
        }
    }
    int ind=0;
    while(v!=-1)
    {
        int u=v;
        v=-1;
        indeg[u]=-1;
        for(int i=0;i<al[u].size();i++)
        {
            --indeg[al[u][i]];
        }
        for(int i=0;i<n;++i)
        {
            if(indeg[i]==0)
            {
                ++c;
                v=i;
                break;
            }
        }
        s[ind]=u+1;
        ++ind;
    }
    if(c==n)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int dijkstra(vector<pair<int,int>> al[],int n,int dist[],int s)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({dist[s-1],s-1});
    int f=1;
    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();
        int w,v;
        for(int i=0;i<al[u].size();++i)
        {
            v=al[u][i].first;
            w=al[u][i].second;
            if(w<0)
            {
                f=0;
                break;
            }
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
        if(f==0)
        {
            break;
        }
    }
    return f;
}

int bellman(vector<pair<int,int>> al[],int n,int dist[],int s,int &ro,int &rm)
{
    int f=1,c=0;
    ro=0;
    rm=0;
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
                    ++ro;
                    if(dist[v]>dist[u]+w)
                    {
                        dist[v]=dist[u]+w;
                        c=1;
                        ++rm;
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

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int q;
        cin>>q;
        if(q==1)
        {
            int n,d,s;
            cin>>n>>d>>s;
            int in;
            vector<int> al[n];
            int dist[n],edge[4],distc[n];
            edge[0]=0;
            edge[1]=0;
            edge[2]=0;
            edge[3]=0;
            for(int i=0;i<n;++i)
            {
                distc[i]=0;
                for(int j=0;j<n;++j)
                {
                    cin>>in;
                    if(in==1)
                    {
                        al[i].push_back(j);
                    }
                }
            }
            bfs(al,n,d,s,edge,dist);
            for(int i=0;i<n;++i)
            {
                if(dist[i]<n)
                {
                    ++distc[dist[i]];
                }
            }
            for(int i=1;i<n;++i)
            {
                cout<<distc[i]<<" ";
                if(distc[i]==0)
                {
                    break;
                }
                if(i==n-1)
                {
                    cout<<"0 ";
                }
            }
            if(d==0)
            {
                cout<<edge[0]<<" "<<edge[3];
            }
            else
            {
                cout<<edge[0]<<" "<<edge[1]<<" "<<edge[2]<<" "<<edge[3];
            }
            cout<<"\n";
        }
        else if(q==2)
        {
            int n,d,s;
            cin>>n>>d>>s;
            int in;
            vector<int> al[n];
            int ft[n],edge[4], color[n];
            edge[0]=0;
            edge[1]=0;
            edge[2]=0;
            edge[3]=0;
            for(int i=0;i<n;++i)
            {
                color[i]=0;
                for(int j=0;j<n;++j)
                {
                    cin>>in;
                    if(in==1)
                    {
                        al[i].push_back(j);
                    }
                }
            }
            color[s-1]=1;
            dfs(al,n,d,s-1,edge,ft,color);
            for(int i=0;i<n;++i)
            {
                if(color[i]==0)
                {
                    color[i]=1;
                    dfs(al,n,d,i,edge,ft,color);
                }
            }
            if(d==0)
            {
                cout<<ft[s-1]<<" "<<edge[0]<<" "<<edge[1];
            }
            else
            {
                cout<<ft[s-1]<<" "<<edge[0]<<" "<<edge[1]<<" "<<edge[2]<<" "<<edge[3];
            }
            cout<<endl;
        }
        else if(q==3)
        {
            int n,in;
            cin>>n;
            vector<int> al[n];
            int s[n];
            for(int i=0;i<n;++i)
            {
                for(int j=0;j<n;++j)
                {
                    cin>>in;
                    if(in==1)
                    {
                        al[i].push_back(j);
                    }
                }
            }
            if(toposort(n,al,s)==1)
            {
                for(int i=0;i<n;++i)
                {
                    cout<<s[i]<<" ";
                }
            }
            else
            {
                cout<<-1;
            }
            cout<<"\n";
        }
        else if(q==4)
        {
            int n,d,s;
            cin>>n>>d>>s;
            int in,dist[n];
            vector<pair<int,int>> al[n];
            for(int i=0;i<n;++i)
            {
                dist[i]=999999;
                for(int j=0;j<n;++j)
                {
                    cin>>in;
                    if(in!=0&&in!=999999)
                    {
                        al[i].push_back({j,in});
                    }
                }
            }
            dist[s-1]=0;
            if(dijkstra(al,n,dist,s)==1)
            {
                for(int i=0;i<n;++i)
                {
                    cout<<dist[i]<<" ";
                }
            }
            else
            {
                cout<<-1;
            }
            cout<<endl;
        }
        else if(q==5)
        {
            int n,d,s;
            cin>>n>>d>>s;
            int in,dist[n];
            vector<pair<int,int>> al[n];
            for(int i=0;i<n;++i)
            {
                dist[i]=999999;
                for(int j=0;j<n;++j)
                {
                    cin>>in;
                    if(in!=0&&in!=999999)
                    {
                        al[i].push_back({j,in});
                    }
                }
            }
            dist[s-1]=0;
            int ro,rm;
            if(bellman(al,n,dist,s,ro,rm)==1)
            {
                for(int i=0;i<n;++i)
                {
                    cout<<dist[i]<<" ";
                }
                cout<<ro<<" "<<rm;
            }
            else
            {
                cout<<-1;
            }
            cout<<endl;
        }
    }
}
