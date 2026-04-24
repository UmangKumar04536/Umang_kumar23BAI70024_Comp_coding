/*
================================================================================
  Problem  : CF 813E — Army Creation
  Platform : Codeforces
  Topic    : Persistent Segment Tree (Online Queries)
  Verdict  : Accepted | 203 ms | 48000 KB
  Date     : Apr 24, 2026
  

  Approach :
  Key insight:
    prevk[i] = position of the warrior exactly k steps back with same type,
               or 0 if fewer than k same-type warriors exist before i.

    Warrior i is VALID in query [l, r]  iff  prevk[i] < l
    (meaning: fewer than k same-type warriors appear before i within [l, r])

  Persistent Segment Tree:
    - Build on key space [0..n] (the prevk values).
    - Version i = inserted positions 1..i with key = prevk[i].
    - Query [l-1, r] counts positions i in [l,r] with prevk[i] in [0, l-1].
    - This gives the answer: number of valid warriors in [l, r].

  Online queries:
    - Queries are encoded using last answer; decode before processing.

  Time : O((n + q) * log n)
  Space: O(n * log n)  [persistent seg tree nodes]
================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXNODES = 100005 * 40;

int lc[MAXNODES], rc[MAXNODES], cnt[MAXNODES];
int roots[100005];
int tot = 0;

int newNode(){
    ++tot;
    lc[tot] = rc[tot] = cnt[tot] = 0;
    return tot;
}

int update(int prev, int l, int r, int pos){
    int cur = newNode();
    lc[cur] = lc[prev];
    rc[cur] = rc[prev];
    cnt[cur] = cnt[prev] + 1;
    if(l == r) return cur;
    int mid = (l + r) / 2;
    if(pos <= mid) lc[cur] = update(lc[prev], l, mid, pos);
    else           rc[cur] = update(rc[prev], mid+1, r, pos);
    return cur;
}

// Count elements with value in [ql, qr] between versions v and u
int query(int u, int v, int l, int r, int ql, int qr){
    if(ql > qr) return 0;
    if(ql <= l && r <= qr) return cnt[v] - cnt[u];
    int mid = (l + r) / 2;
    int res = 0;
    if(ql <= mid) res += query(lc[u], lc[v], l, mid, ql, qr);
    if(qr > mid)  res += query(rc[u], rc[v], mid+1, r, ql, qr);
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n+1);
    vector<vector<int>> pos(100001); // pos[type] = sorted positions seen so far
    vector<int> prevk(n+1, 0);

    for(int i = 1; i <= n; i++){
        cin >> a[i];
        int t = a[i];
        pos[t].push_back(i);
        int sz = pos[t].size();
        if((int)sz > k)
            prevk[i] = pos[t][sz - k - 1]; // k-th position back of same type
        else
            prevk[i] = 0; // fewer than k before, always safe
    }

    // Build persistent segment tree: version i inserts position i with key prevk[i]
    roots[0] = newNode();
    for(int i = 1; i <= n; i++){
        roots[i] = update(roots[i-1], 0, n, prevk[i]);
    }

    int q;
    cin >> q;

    long long last = 0;
    while(q--){
        long long x, y;
        cin >> x >> y;
        int l = (int)((x + last) % n) + 1;
        int r = (int)((y + last) % n) + 1;
        if(l > r) swap(l, r);

        // Count positions in [l, r] with prevk in [0, l-1]
        last = query(roots[l-1], roots[r], 0, n, 0, l-1);
        cout << last << "\n";
    }

    return 0;
}
