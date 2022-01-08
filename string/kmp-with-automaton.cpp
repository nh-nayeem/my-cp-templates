#include<bits/stdc++.h>

using namespace std;

 
/*............start.............*/
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
void compute_automaton(string s, vector<vector<int>>& aut) {
    s += '#';
    int n = s.size();
    vector<int> pi = prefix_function(s);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}

int main()
{
    string s="abcabzabc",pat="abc";
    //index = 012345678
    vector<vector<int> > aut;
    compute_automaton(pat,aut);
    int m=pat.size();
    for(int i=0,j=0;i<(int)s.size();i++)
    {
        j=aut[j][s[i]-'a'];
        if(j==m)
        {
            cout<<"pattern found on = "<<i-m+1<<endl;
        }
    }
    return 0;
}
