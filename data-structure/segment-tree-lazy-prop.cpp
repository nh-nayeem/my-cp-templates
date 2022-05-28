struct segtree
{
    struct nod
    {
        int one,zero,lazy;
        nod(int one,int zero) : one(one),zero(zero),lazy(-1) { }; //initialize the values
    };
    int n;
    vector<nod> tree;
    segtree(int len)
    {
        n=len;
        tree.resize(4*len,nod(0,0));
    }
    nod merge(nod x, nod y)    //........merge two nod of segment tree.....
    {
        nod ret(0,0);
        ret.one+=x.one+y.one;
        ret.zero+=x.zero+y.zero;
        return ret;
    }
    void push(int at,int l,int r)   //.........edit push function as lazy behave.....
    {
        if(tree[at].lazy==-1) return;
        if(tree[at].lazy==0) tree[at].zero=(r-l+1),tree[at].one=0;
        else tree[at].one=(r-l+1),tree[at].zero=0;
        if(l!=r) tree[at<<1].lazy=tree[at].lazy;
        if(l!=r) tree[at<<1|1].lazy=tree[at].lazy;
        tree[at].lazy=-1;
    }
    void upd(int at,int l,int r,int L,int R,int val)
    {
        push(at,l,r);
        if(r<L || R<l) return;
        if(L<=l && r<=R)
        {
            tree[at].lazy=val;
            push(at,l,r);
            return;
        }
        int m=(l+r)>>1;
        upd(at<<1,l,m,L,R,val);
        upd(at<<1|1,m+1,r,L,R,val);
        tree[at]=merge(tree[at<<1],tree[at<<1|1]);
    }
    nod quer(int at,int l,int r,int L,int R)
    {
        push(at,l,r);
        if(r<L || R<l) return nod(0,0);    //    ............check.......
        if(L<=l && r<=R) return tree[at];
        int m=(l+r)>>1;
        return merge(quer(at<<1,l,m,L,R),quer(at<<1|1,m+1,r,L,R));
    }
};
