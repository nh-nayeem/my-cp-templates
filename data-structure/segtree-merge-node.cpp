
#include<bits/stdc++.h>
 
using namespace std;
#define nl '\n'

typedef long long LL;

/*............start.............*/
const int N=100005;
const LL inf=1LL<<58;
LL a[N];
struct node 
{
    LL odd;
    LL even;
    node()
    {
        odd=0;
        even=0;
    }
    void Assign(LL val)
    {
        if(val%2==1) odd=1,even=0;
        else even=1,odd=0;
    }
    void merge(node x,node y)
    {
        odd  = ( (x.odd  +  y.odd)%MOD + (x.even*y.odd)%MOD + (x.odd*y.even)%MOD )%MOD ; 
        even = ( (x.even + y.even)%MOD + (x.even*y.even)%MOD + (x.odd*y.odd)%MOD )%MOD ;
    }
};
node seg[4*N];
void Upd(int at,int l,int r,int pos,LL val)
{
    if(l==r)
    {
        seg[at].Assign(val);
        return;
    }
    int m=(l+r)>>1;
    if(pos<=m) Upd(at<<1,l,m,pos,val);
    else Upd(at<<1|1,m+1,r,pos,val);
    seg[at].merge(seg[at<<1],seg[at<<1|1]);
}
void solve()
{
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        Upd(1,1,n,i,a[i]);
    }

    while(q--)
    {
        int x,v;
        cin>>x>>v;
        a[x]=v;
        Upd(1,1,n,x,v);
        cout<<seg[1].odd<<nl;
    }
}
int main()
{

    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int q=1;
    
    for(int kase=1;kase<=q;kase++)
    {
     
        solve();
    }
  
    return 0;
}
