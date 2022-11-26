/*............bismillahir rahmanir rahim...............*/

// author :  Muhammad Najmul Hasan Nayeem (SUST MATH 17)

#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
 
using namespace std;

#define ff first
#define ss second
#define getunique(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}

typedef long long ll;
typedef unsigned long long ull;

// typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());
const int N = 2e5 + 5;
struct nod{
    int l, r; 
    ll lazy, sum;
    bool lf, rf;
    nod() {
        l = -1, r = -1, lazy = 0, sum = 0, lf = 0, rf = 0;
    }
};
void _clone(nod &x, nod &y) {
    x.l = y.l;
    x.r = y.r;
    x.lazy = y.lazy;
    x.sum = y.sum;
}
nod st[N * 120];
ll a[N];
int sz, root[N]  , qt[N];
int new_nod() {
    assert(sz + 1 < (N * 120));
    return ++sz;
}
void push(int at, int l, int r) {
    if (st[at].lazy == 0) return;
    st[at].sum += st[at].lazy * (r - l + 1);
    if (l != r) {
        int lc = st[at].l, rc = st[at].r;
        if (!st[at].lf) {
            int cc = new_nod();
            _clone(st[cc], st[lc]);
            lc = cc, st[at].lf = 1, st[at].l = cc;
        }
        if (!st[at].rf) {
            int cc = new_nod();
            _clone(st[cc], st[rc]);
            rc = cc, st[at].rf = 1, st[at].r = cc;
        }
        st[lc].lazy += st[at].lazy;
        st[rc].lazy += st[at].lazy;
    }
    st[at].lazy = 0;
}
void Build(int at, int l, int r) {
    if (l == r) {
        return;
    }
    int m = (l + r) / 2;
    int lc = new_nod(), rc = new_nod();
    Build(lc, l, m);
    Build(rc, m + 1, r);
    st[at].l = lc, st[at].r = rc;
    st[at].lf = 1, st[at].rf = 1;
    st[at].sum = st[lc].sum + st[rc].sum;
}
pair<int, int>  upd(int at, int l, int r, int L, int R, ll val) {
    push(at, l, r);
    if (r < L || R < l) {
        return {at, 0};
    }
    int cur = new_nod();
    _clone(st[cur], st[at]);
    if (L <= l && r <= R) {
        st[cur].lazy += val;
        push(cur, l, r);
        return {cur, 1};
    }
    int m = (l + r) / 2;
    auto lc = upd(st[at].l, l, m, L, R, val);
    auto rc = upd(st[at].r, m + 1, r, L, R, val);
    st[cur].l = lc.ff, st[cur].r = rc.ff;
    st[cur].lf = lc.ss, st[cur].rf = rc.ss;
    st[cur].sum = st[lc.ff].sum + st[rc.ff].sum;
    return {cur, 1};
}
ll quer(int at, int l, int r, int p) {
    push(at, l, r);
    if (l == r) {
        return st[at].sum;
    }
    int m = (l + r) / 2;
    if (p <= m) return quer(st[at].l, l, m, p);
    return quer(st[at].r, m + 1, r, p);
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    root[0] = 0;
    Build(root[0], 1, m);
    for (int it = 1; it <= q; it++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            root[it] = upd(root[it - 1], 1, m, l, r, x).ff;
        } else if (t == 2) {
            int i, x;
            cin >> i >> x;
            root[it] = root[it - 1];
            a[i] = x;
            qt[i] = it;
        } else {
            int i, j;
            cin >> i >> j;
            root[it] = root[it - 1];
            ll res = a[i] + quer(root[it], 1, m, j);
            res -= quer(root[qt[i]], 1, m, j);
            cout << res << '\n';
        }
    }
}
// tested in https://atcoder.jp/contests/abc253/tasks/abc253_f
int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int q=1;
    //cin>>q;
    // SI(q);
    for(int kase=1; kase<=q; kase++)
    {
        // cout<<"Case "<<kase<<":\n";
        // printf("Case %d: ",kase );
        solve();
    }
    return 0;
}
