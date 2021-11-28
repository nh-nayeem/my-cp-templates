
#include<bits/stdc++.h>
 
using namespace std;
#define nl '\n'

typedef long long LL;

/*............start.............*/
const int N=2e5+5;
const int LOG_A=30;
int base[LOG_A],sz;
bool checkXor(int mask) 
{
    for (int i = 0; i < LOG_A; i++) {
        if ((mask & 1 << i) == 0) continue;
 
        if (!base[i]) return false;
 
        mask ^= base[i];
    }
 
    return true;
}
void insertVector(int mask) 
{
    for (int i = 0; i < LOG_A; i++) {
        if ((mask & 1 << i) == 0) continue;
 
        if (!base[i]) {
            base[i] = mask;
            sz++;
 
            return;
        }
 
        mask ^= base[i];
    }
}
void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    for(auto &i: a) cin>>i;
    int xx=0;
    for(auto i: a)
    {
        insertVector(i); // inserting array element for query below
        xx^=i;
    }
    // chk(xx);
    while(q--)
    {
        int x;
        cin>>x;
        if(xx==0)
        {
            if(x==0) cout<<1<<nl;
            else if(checkXor(x)) cout<<2<<nl;// query :  check if there are a subset of array with xor x .
            else cout<<-1<<nl;
        }
        else
        {
            if( xx==x ) cout<<1<<nl;
            else cout<<-1<<nl;
        }
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
