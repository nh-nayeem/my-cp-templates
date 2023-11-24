/*............bismillahir rahmanir rahim...............*/

// author :  Muhammad Najmul Hasan Nayeem (SUST MATH 17)

#include<bits/stdc++.h>
using namespace std;
template<class T>
struct segtree {
    int n;
    vector<T> tree;
    segtree(int len) : n(len) {
        tree.resize(4 * len, 0);
    }
    // change combine function
    T combine(T x, T y) {
        return x + y;
    }
    void build(vector<T> &arr, int at, int l, int r) {
        if (l == r) return void(tree[at] = arr[l]);
        int m = (l + r) >> 1;
        build(arr, at << 1, l, m);
        build(arr, at << 1 | 1, m + 1, r);
        tree[at] = combine(tree[at << 1], tree[at << 1 | 1]);
    }
    void Build(vector<T> &arr){ build(arr, 1, 0, n - 1); } // Use this 

    void update(int at, int l, int r, int p, T val) {
        if (l == r) return void(tree[at] = val); // change the update type
        int m = (l + r) >> 1;
        if (p <= m) update(at << 1, l, m, p, val);
        else update(at << 1 | 1, m + 1, r, p, val);
        tree[at] = combine(tree[at << 1], tree[at << 1 | 1]);
    }
    void Update(int p, T val) { update(1, 0, n - 1, p, val); } // Use this

    T query(int at, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tree[at];
        int m = (l + r) >> 1;
        if (R <= m) return query(at << 1, l, m, L, R);
        if (m < L) return query(at << 1 | 1, m + 1, r, L, R); 
        return combine(query(at << 1, l, m, L, R), query(at << 1 | 1, m + 1, r, L, R));
    }
    T Query(int l, int r) { return query(1, 0, n - 1, l, r); } // Use this
};
int32_t main() {
    vector<int> a = {1, 2, 3, 4, 5};
    int n = a.size();
    segtree<int> st(n);
    st.Build(a);
    st.Update(2, 5);
    cout << st.Query(1, 2) << endl;
    return 0;
}
