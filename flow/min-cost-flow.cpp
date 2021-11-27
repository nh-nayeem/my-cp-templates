
#include<bits/stdc++.h>
 
using namespace std;


struct Edge
{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}
void solve()
{
    //refference problem : https://codeforces.com/contest/1437/problem/C 
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &i: a) cin>>i;
    int tme=n+n/2+5;
    int s=0;
    int t=tme+n;
    vector<Edge> edges;
    for(int i=1;i<tme;i++)
    {
        Edge x;
        x.from=s;
        x.to=i;
        x.capacity=1;
        x.cost=0;
        edges.push_back(x);
    }
    for(int i=1;i<tme;i++)
    {
        for(int j=0;j<n;j++)
        {
            Edge x;
            x.from=i;
            x.to=j+tme;
            x.capacity=1;
            x.cost=abs(i-a[j]);
            edges.push_back(x);
        }
    }
    for(int j=0;j<n;j++)
    {
        Edge x;
        x.from=j+tme;
        x.to=t;
        x.capacity=1;
        x.cost=0;
        edges.push_back(x);
    }
    cout<<min_cost_flow(t+1,edges,n,s,t)<<'\n';
}
int main()
{
    
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int q=1;
    cin>>q;
   
    for(int kase=1;kase<=q;kase++)
    {
        solve();
    }
    
    return 0;
}
