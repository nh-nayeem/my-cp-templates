/*...................bismillahir rahmanir rahim.....................*/
/*
  author :
    Muhammad Najmul Hasan Nayeem
    Sust Math 17
*/

#include<bits/stdc++.h>

 
using namespace std;

#define eb emplace_back
#define ff first

#define nl '\n'

typedef long long ll;

mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());

/*............start.............*/
const int N=300002;

struct nod
{
    int key, prior,mx,mn,diff,size;
    nod *l,*r;
    nod(int key) : key(key),prior(mt_rand()),l(NULL),r(NULL),mx(key),mn(key),size(1),diff(INT_MAX) { };
    nod(int key,int prior) : key(key),prior(prior),l(NULL),r(NULL),mx(key),mn(key),size(1),diff(INT_MAX) { };
};
typedef nod* pnod;

void dfs(pnod t)
{
    if(!t) return;
    dfs(t->l);
    cout<<t->key<<' ';
    dfs(t->r);
}
void show(pnod t) { if(t)dfs(t);else cout<<-1; cout<<nl<<nl; }

void upd(pnod t)
{
    if(!t) return;
    t->size=1;
    t->mx=t->key;
    t->mn=t->key;
    t->diff=INT_MAX;

    if(t->l) t->mx=max(t->mx, t->l->mx ) , t->mn=min(t->mn,t->l->mn), t->size+=t->l->size; 
    if(t->r) t->mx=max(t->mx, t->r->mx ) , t->mn=min(t->mn,t->r->mn), t->size+=t->r->size;
    // cerr<<once<<nl;
    if(t->l) t->diff=min( t->diff,(t->key)-(t->l->mx) ),t->diff=min(t->diff,t->l->diff);
    if(t->r) t->diff=min( t->diff,(t->r->mn)-(t->key) ),t->diff=min(t->diff,t->r->diff);

    // chk(t->diff);
}

void split(pnod t, int key, pnod & l, pnod & r )
{
    if(!t) l = r = NULL;
    else if( t->key <= key ) split( t->r, key, t->r, r), l=t;
    else split(t->l, key , l, t->l), r=t;  
    upd(l);
    upd(r);
}

int sz(pnod t){ if(t) return t->size; return 0; }

void split_by_idx(pnod t, int idx, pnod & l, pnod & r) // when treap is a set and idx is the index of sorted list and key = value
{
    if(!t) l = r = NULL;
    else if( sz(t->l)+1 <= idx) split_by_idx( t->r, idx-sz(t->l)-1, t->r, r), l=t; 
    else split_by_idx(t->l, idx , l, t->l), r=t;
    upd(l);
    upd(r); 
}

void merge(pnod & t, pnod l, pnod r )
{
    if(!r || !l) t = l ? l : r;
    else if( l->prior > r->prior) merge(l->r,l->r,r), t=l;
    else merge(r->l,l,r->l), t=r;
    upd(t);
}
void insert(pnod & t, pnod it)
{
    if(!t) t=it;
    else if( it->prior > t->prior ) split(t,it->key,it->l,it->r), t=it;
    else insert( t->key <= it->key ? t->r : t->l ,it  );
    upd(t);
}
void erase(pnod & t, int key)
{
    if( t->key == key )
    {
        pnod th = t;
        merge( t, t->l, t->r);
        upd(t);
        // delete th;
    }
    else
    {
        erase( key < t->key ? t->l : t->r, key );
        upd(t);
    }
}
int querN(pnod t)
{
    if(!t || t->size==1 ) return -1;
    return t->diff;
}
int querD(pnod t)
{
    if(!t || t->size==1) return -1;
    return (t->mx)-(t->mn);
}


void solve()
{
    int q;
    cin>>q;
    pnod treap=NULL;
    set<int> st;
    for(int i=1;i<=q;i++)
    {
        // cout<<"\ncase :"<<i<<nl;
        char c; cin>>c;
        if(c=='I')
        {
            int x; cin>>x;
            if( st.find(x)==st.end() )
            {
                st.insert(x);
                pnod t = new nod(x);
                insert(treap,t);
            }
            // show(treap);
        }
        else if(c=='D')
        {
            int x; cin>>x;
            // cout<<"del 4: ";
            if( st.find(x)!=st.end() )
            {
                st.erase(x);

                pnod l=NULL,r=NULL,n=NULL,m=NULL;
                split(treap,x,l,r);
                split(l,x-1,n,m);
                delete m;
                merge(treap,n,r);
            }
            // show(treap);
        }
        else if(c=='N')
        {
            int x,y; cin>>x>>y;
            pnod n=NULL,m=NULL,l=NULL,r=NULL;
            // show(treap);
            split_by_idx(treap,y+1,l,r);
            split_by_idx(l,x,n,m);
            cout<<querN(m)<<nl;
            merge(l,n,m);
            merge(treap,l,r);
            // show(treap);
        }
        else
        {
            int x,y; cin>>x>>y;
            pnod n=NULL,m=NULL,l=NULL,r=NULL;
            // show(treap);
            split_by_idx(treap,y+1,l,r);
            split_by_idx(l,x,n,m);
            cout<<querD(m)<<nl;
            merge(l,n,m);
            merge(treap,l,r);
            // show(treap);
        }
    }    
}

//...........................https://www.spoj.com/problems/TREAP/ ........................

int main()
{
    ios_base::sync_with_stdio(false);//cin.tie(NULL);cout.tie(NULL);
    int q=1;
    for(int kase=1; kase<=q; kase++)
    {
        solve(); 
    }

    return 0;
}
