/*
================================================================================
  Problem  : CF 514C — Watto and Mechanism
  Platform : Codeforces
  Topic    : String Hashing (Double Hashing)
  Verdict  : Accepted | 234 ms | 16100 KB
  Date     : Apr 24, 2026
  

  Approach :
  - For each query string s, check if any stored string differs in exactly 1 position.
  - Use double hashing (two independent base/mod pairs) to avoid collisions.
  - Precompute prefix hashes for all stored strings; store full hash pairs in
    a set<pair<ll,ll>> bucketed by string length.
  - For each position i in query string s, try replacing s[i] with each of
    'a', 'b', 'c' (skip s[i] itself).
  - New hash computed in O(1):
      new_hash = prefix_hash * base^(L-i) + new_char * base^(L-1-i) + suffix_hash
  - Lookup new hash pair in the stored set -> O(log n) per check.
  - Total: O(L * log n) per query.
================================================================================
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const ll MOD1 = 1e9+7, MOD2 = 1e9+9;
const ll BASE1 = 131, BASE2 = 137;
const int MAXN = 6e5+5;

ll pw1[MAXN], pw2[MAXN];

void precompute(){
    pw1[0] = pw2[0] = 1;
    for(int i = 1; i < MAXN; i++){
        pw1[i] = pw1[i-1] * BASE1 % MOD1;
        pw2[i] = pw2[i-1] * BASE2 % MOD2;
    }
}

ll getHash1(const vector<ll>& h, int l, int r){
    return (h[r+1] - h[l] * pw1[r-l+1] % MOD1 + MOD1 * 2) % MOD1;
}
ll getHash2(const vector<ll>& h, int l, int r){
    return (h[r+1] - h[l] * pw2[r-l+1] % MOD2 + MOD2 * 2) % MOD2;
}

pair<vector<ll>, vector<ll>> buildPrefix(const string& s){
    int n = s.size();
    vector<ll> h1(n+1, 0), h2(n+1, 0);
    for(int i = 0; i < n; i++){
        h1[i+1] = (h1[i] * BASE1 + s[i]) % MOD1;
        h2[i+1] = (h2[i] * BASE2 + s[i]) % MOD2;
    }
    return {h1, h2};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int n, m;
    cin >> n >> m;

    map<int, set<pll>> stored;

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int L = s.size();
        auto p = buildPrefix(s);
        ll fh1 = p.first[L], fh2 = p.second[L];
        stored[L].insert({fh1, fh2});
    }

    for(int q = 0; q < m; q++){
        string s;
        cin >> s;
        int L = s.size();

        if(stored.find(L) == stored.end()){
            cout << "NO\n";
            continue;
        }

        auto p = buildPrefix(s);
        vector<ll>& h1 = p.first;
        vector<ll>& h2 = p.second;
        set<pll>& st = stored[L];

        bool found = false;
        for(int i = 0; i < L && !found; i++){
            ll pre1 = h1[i], pre2 = h2[i];
            ll suf1 = (i+1 <= L-1) ? getHash1(h1, i+1, L-1) : 0;
            ll suf2 = (i+1 <= L-1) ? getHash2(h2, i+1, L-1) : 0;

            for(char c = 'a'; c <= 'c'; c++){
                if(c == s[i]) continue;
                ll nh1 = (pre1 * pw1[L-i] % MOD1 + (ll)c * pw1[L-1-i] % MOD1 + suf1) % MOD1;
                ll nh2 = (pre2 * pw2[L-i] % MOD2 + (ll)c * pw2[L-1-i] % MOD2 + suf2) % MOD2;
                if(st.count({nh1, nh2})){
                    found = true;
                    break;
                }
            }
        }

        cout << (found ? "YES" : "NO") << "\n";
    }

    return 0;
}
