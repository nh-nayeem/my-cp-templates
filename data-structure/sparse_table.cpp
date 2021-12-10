/*...................bismillahir rahmanir rahim.....................*/
/*
  author :
    Muhammad Najmul hasan Nayeem
    Sust Math 17
*/
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("unroll-loops")

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
 
using namespace std;

#define m_p make_pair
#define PB push_back
#define eb emplace_back
#define FF first
#define SS second
#define MX5 100005
#define MX6 1000006
#define MOD 1000000007
#define in()({int a;scanf("%d",&a);a;})
#define SI(a) scanf("%d",&a)
#define SII(a,b) scanf("%d%d",&a,&b)
#define SIII(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define SC()({char a;scanf("%c",&a);a;})
#define SL()({long long a;scanf("%lld",&a);a;})
#define SD()({double a;scanf("%f",&a);a;})
#define nl '\n'
#define For(_,n) for(int i=_;i<=n;i++)
#define once "once upon a time\n"
#define FI freopen("input.txt","r+",stdin);
#define FO freopen("output.txt","w+",stdout);
#define getunique(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef pair<string,string> PSS;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

template <class A, class B> ostream& operator << (ostream& out, const pair<A, B> &a) {
    return out << "(" << a.FF << ", " << a.SS << ")";
}
 
template <class A> ostream& operator << (ostream& out, const vector<A> &v) {
    out << "[";
    for(int i=0;i<(int)v.size();i++) {
        if(i) out << ", ";
        out << v[i];
    }
    return out << "]";
}
 
#define chk(a) cout<<(#a)<<" = "<<a<<endl;
#define chka(a,_) cout<<(#a)<<"["<<_<<"] = "<<a[_]<<"\n";
#define debug(args...)                           \
    {                                            \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        deb(_it, args);                          \
    }
void deb(istream_iterator<string> it)
{
}
template <typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args)
{
    cout << *it << " = " << a << endl;
    deb(++it, args...);
}
// int Set(int n,int pos){ return n | (1<<pos); }
// int Reset(int n,int pos){ return n=n & ~(1<<pos); }
// bool Check(int n,int pos){ return (bool)(n & (1<<pos)); }
  
struct GCD_type { long long x, y, d; };
GCD_type ex_GCD(long long a, long long b)
{
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}
mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
 
/*............start.............*/
const int N=100000+5;
const int K=21;
const int M=998244353;
int a[N];
int st[N][K];
int Log[N];
void Build(int n)
{
    for(int i=0;i<n;i++) st[i][0]=a[i];
    for(int j=1;j<K;j++)
    {
        for(int i=0;i<n;i++)
        {
            if( (i+(1<<(j-1)))>=n ) break;
            st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);// gcd,sum,min max
        }
    }
    for(int i=2;i<=n;i++)
    {
        Log[i]=Log[i/2]+1;
    }
}
int quer(int l,int r)
{
    int j=Log[r-l+1];
    return __gcd(st[l][j],st[r+1-(1<<j)][j]);//gcd,min, max in o(1)
}
//for sum query we can just use segment tree
void solve()
{
    int n,q;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    Build(n);
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        l--,r--;
        cout<<quer(l,r)<<nl;
    }
}
int main()
{
    // clock_t time_start=clock();
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int q=1;
    // cin>>q;
    // SI(q);
    for(int kase=1;kase<=q;kase++)
    {
        // cout<<"Case "<<kase<<": ";
        // printf("Case %d: ",kase );
        solve();
    }
    // clock_t time_end=clock();
    // cerr<<float((time_end-time_start)/CLOCKS_PER_SEC);
    return 0;
}
