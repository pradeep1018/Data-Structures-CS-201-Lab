/*

Pradeep P
2019MCB1227
Minimum Cost Arborescence

*/
#include<bits/stdc++.h>
using namespace std;

// bfs performed to remove all unreachable nodes from the adjacency matrix
void bfs(int n, vector<int> al[],int vis[],int s)
{
    queue<int> q;
    q.push(s);
    vis[s]=1;
    while(!q.empty())
    {
        int a = q.front();
        q.pop();
        for(int i=0;i<n;++i)
        {
            if(al[a][i]!=-1&&vis[i]==0)
            {
                q.push(i);
                vis[i]=1;
            }
        }
    }
}

// calculates distance of each vertex from the source in final arborescence
void calcdist(int n, vector<int> al[],int dis[],int s,int &sum)
{
    queue<int> q;
    q.push(s);
    dis[s]=0;
    while(!q.empty())
    {
        int a = q.front();
        q.pop();
        for(int i=0;i<n;++i)
        {
            if(al[a][i]!=-1)
            {
                q.push(i);
                dis[i]=dis[a]+al[a][i];
                sum+=al[a][i];
            }
        }
    }
}

// to check if a number is present in a given vector
int checkno(int i,vector<int> s)
{
    int f=0;
    for(int j=0;j<s.size();++j)
    {
        if(s[j]==i)
        {
            f=1;
            break;
        }
    }
    return f;
}

// returns index of a number at which it is stored in a given vector
int findind(int i,vector<int> red)
{
    for(int j=0;j<red.size();++j)
    {
        if(red[j]==i)
        {
            return j;
        }
    }
}

// to check if any cycle is present in a given graph
int checkcycle(int v,int n,vector<int> al[],vector<int> &s,int vis[])
{
    s.push_back(v);
    vis[v]=1;
    int a=0;
    while(s.size()>0)
    {
        a=0;
        int top=s[s.size()-1];
        for(int i=0;i<n;++i)
        {
            if(al[top][i]==0&&vis[i]==0)
            {
                s.push_back(i);
                vis[i]=1;
                a=1;
                break;
            }
            else if(al[top][i]==0&&vis[i]==1&&checkno(i,s)==1)
            {
                a=2;
                break;
            }
        }
        if(a==0)
        {
            s.pop_back();
        }
        if(a==2)
        {
            break;
        }
    }
    if(a==2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// arborescence function to calculate arborescence of a given graph
void arbo(int n,vector<int> al[])
{
    // alc is the matrix containing reduced costs
    // ald stores all zero edges only
    // alf is used to store the resultant arborescence
    vector<int> alc[n],ald[n],alf[n];
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            alc[i].push_back(al[i][j]);
            ald[i].push_back(-1);
            alf[i].push_back(-1);
        }
    }
    // for loop to reduce costs
    for(int j=0;j<n;++j)
    {
        int mini=-1;
        for(int i=0;i<n;++i)
        {
            if(alc[i][j]>=0&&mini<0)
            {
                mini=alc[i][j];
            }
            else if(alc[i][j]>=0&&alc[i][j]<mini)
            {
                mini=alc[i][j];
            }
        }
        if(mini>0)
        {
            for(int i=0;i<n;++i)
            {
                if(alc[i][j]>0)
                {
                    alc[i][j]=alc[i][j]-mini;
                }
            }
        }
    }
    int vis[n];
    // storing at most one zero edge entering each vertex
    for(int j=0;j<n;++j)
    {
        vis[j]=0;
        for(int i=0;i<n;++i)
        {
            if(alc[i][j]==0)
            {
                ald[i][j]=0;
                break;
            }
        }
    }
    vector<int> s;
    int c=0;
    // checking for cycle
    for(int i=0;i<n;++i)
    {
        if(vis[i]==0)
        {
            if(checkcycle(i,n,ald,s,vis)==1)
            {
                c=1;
                break;
            }
        }
    }
    if(c==0)
    {
        // if there is no cycle the zero edges combine to form an arborescence with their original weights
        for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(ald[i][j]!=0)
				{
					al[i][j]=-1;
				}
            }
		}
		return;
    }
    // combining the vertices of the cycle into a single vertex
    int m=s.size();
    int r=n+1-m;
    vector<int> red;
    int sn=*min_element(s.begin(),s.end());
    c=0;
    // storing the vertex index of reduced graph corresponding to the vertex in present graph
    // here reduced graph means the graph containing supernode
    for(int i=0;i<n;i++)
	{
		if(c==sn)
        {
			++c;
        }
		if(checkno(i,s)==1)
		{
			red.push_back(sn);
		}
		else
		{
			red.push_back(c);
			++c;
		}
	}
	vector<int> aln[r];
	// creating a adjacency matrix for reduced graph
	for(int i=0;i<r;++i)
	{
		for(int j=0;j<r;++j)
		{
			aln[i].push_back(-1);
		}
	}
	// copying the elements of the graph to the reduced graph
	for(int j=0;j<n;++j)
	{
		for(int i=0;i<n;++i)
		{
			if(red[i]==red[j])
			{
			    continue;
			}
			else if(alc[i][j]!=-1)
			{
				if(aln[red[i]][red[j]]==-1)
                {
					aln[red[i]][red[j]]=alc[i][j];
                }
				else
                {
					aln[red[i]][red[j]]= min(aln[red[i]][red[j]],alc[i][j]);
                }
			}
		}
	}
	vector<int> inc;
	// storing the vertex index of present graph corresponding to the vertex in reduced graph
	for(int i=0;i<r;++i)
    {
        inc.push_back(findind(i,red));
    }
    // running arborescence function on reduced graph
	arbo(r,aln);
	int inn=0;
	// restoring the original weights to the arborescence obtained from the above function call
    for(int i=0;i<r;++i)
    {
        for(int j=0;j<r;++j)
        {
            if(aln[i][j]!=-1)
            {
                if(checkno(inc[i],s)==1)
                {
                    for(int k=0;k<s.size();++k)
                    {
                        if(aln[i][j]==alc[s[k]][inc[j]])
                        {
                            alf[s[k]][inc[j]]=al[s[k]][inc[j]];
                        }
                    }
                }
                else if(checkno(inc[j],s)==1)
                {
                    for(int k=0;k<s.size();++k)
                    {
                        if(aln[i][j]==alc[inc[i]][s[k]])
                        {
                            inn=k;
                            alf[inc[i]][s[k]]=al[inc[i]][s[k]];
                        }
                    }
                }
                else
                {
                    alf[inc[i]][inc[j]]=al[inc[i]][inc[j]];
                }
            }
        }
    }
    int a=0;
    // restoring all edges except the edge which directs towards a vertex having inendge one in the cycle corresponding to supernode
    while(a<s.size()-1)
    {
        if(inn!=s.size()-1)
        {
            alf[s[inn]][s[inn+1]]=al[s[inn]][s[inn+1]];
            ++inn;
        }
        else
        {
            alf[s[inn]][s[0]]=al[s[inn]][s[0]];
            ++inn;
        }
        ++a;
    }
    // copying the arborescence to original adjacency matrix
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            al[i][j]=alf[i][j];
        }
    }
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,s;
        cin>>n>>m>>s;
        vector<int> al[n];
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                al[i].push_back(-1);
            }
        }
        for(int i=0;i<m;++i)
        {
            int u,v,w;
            cin>>u>>v>>w;
            // excluding the edges satisfying any one of the conditions given below
            if(v==s||u==v||w==0)
            {
                continue;
            }
            else if(al[u-1][v-1]==-1)
            {
				al[u-1][v-1]=w;
            }
			else if(al[u-1][v-1]>w)
			{
					al[u-1][v-1]=w;
			}
        }
        int vis[n],dis[n];
        for(int i=0;i<n;++i)
        {
            vis[i]=0;
            dis[i]=-1;
        }
        // bfs to remove unreachable nodes from the source
        bfs(n,al,vis,s-1);
        for(int i=0;i<n;i++)
		{
			if(vis[i]==0)
			{
				for(int j=0;j<n;j++)
				{
					al[i][j]=-1;
					al[j][i]=-1;
				}
			}
		}
		// function to find arborescence of a given graph
        arbo(n,al);
        int sum=0;
        // function to calculate distance of all vertices from the source
        calcdist(n,al,dis,s-1,sum);
        cout<<sum<<" ";
        for(int i=0;i<n;++i)
        {
            cout<<dis[i]<<" ";
        }
        cout<<"# ";
        // function to calculate parent of each vertex
        for(int j=0;j<n;++j)
        {
            int p=0;
            for(int i=0;i<n;++i)
            {
                if(al[i][j]>-1)
                {
                    p=i+1;
                }
            }
            if(vis[j]==0)
            {
                cout<<-1<<" ";
            }
            else
            {
                cout<<p<<" ";
            }
        }
        cout<<endl;
    }
}
