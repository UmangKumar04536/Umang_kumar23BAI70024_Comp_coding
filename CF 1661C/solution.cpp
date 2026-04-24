/*
================================================================================
  Problem  : CF 1661C — Water the Trees
  Platform : Codeforces
  Topic    : Binary Search + Greedy
  Verdict  : Accepted | 109 ms | 100 KB
  Date     : Apr 24, 2026
  

  Approach :
  In d days: ceil(d/2) odd days (+1 each), floor(d/2) even days (+2 each).

  For a fixed target height H and d days:
    - Each tree i needs diff_i = H - h_i water units.
    - Optimally: use as many +2 days as possible per tree.
    - need2 = sum(diff_i / 2),  need1 = sum(diff_i % 2)
    - If need2 > available twos: convert excess to pairs of ones
        need1 += 2 * (need2 - twos);  need2 = twos
    - Feasible iff need1 <= ones (ceil(d/2)) and need2 <= twos (floor(d/2))

  Binary search on d for each candidate target H.

  Why only H = max and H = max+1?
    - Going to max+2 adds 2 units to every tree — always worse than max or max+1
      because it flips parities without benefit.
    - One of {max, max+1} is always optimal.

  Time: O(n * log(3e14)) per test case.
================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

bool check(long long d, long long H, vector<int>& h){
    long long ones = (d+1)/2;
    long long twos = d/2;
    long long need1 = 0, need2 = 0;
    for(int x : h){
        long long diff = H - x;
        if(diff < 0) return false;
        need2 += diff/2;
        need1 += diff%2;
    }
    if(need2 > twos){
        need1 += 2*(need2 - twos);
        need2 = twos;
    }
    return need1 <= ones;
}

long long solve(long long H, vector<int>& h){
    long long lo = 0, hi = 3e14;
    while(lo < hi){
        long long mid = lo + (hi-lo)/2;
        if(check(mid, H, h)) hi = mid;
        else lo = mid+1;
    }
    return lo;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> h(n);
        int mx = 0;
        for(int i = 0; i < n; i++){
            cin >> h[i];
            mx = max(mx, h[i]);
        }
        long long ans = min(solve(mx, h), solve(mx+1, h));
        cout << ans << "\n";
    }
    return 0;
}
