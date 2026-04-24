/*
================================================================================
  Problem  : CF 1458B — Glass Half Spilled
  Platform : Codeforces
  Topic    : DP (Knapsack variant) + Greedy Observation
  Verdict  : Accepted | 93 ms | 200 KB
  Date     : Apr 24, 2026
  Profile  : muskanrathee725

  Approach :
  Key observation:
    For chosen set S with total capacity sumA_S and total water sumB_S:
      water collected = min(sumA_S,  sumB_S + (totalB - sumB_S) / 2)
                      = min(sumA_S,  totalB/2 + sumB_S/2)
    (unchosen glasses contribute half their water via transfers)

  DP definition:
    dp[k][sa] = maximum sumB achievable by choosing exactly k glasses
                with total capacity exactly sa.

  For each k, answer = max over all sa of min(sa, totalB/2 + dp[k][sa]/2)

  Constraints: n<=100, each a[i]<=100, so totalA <= 10000.
  Complexity: O(n^2 * totalA) = O(100 * 100 * 10000) = 10^8, feasible.
================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    int totalB = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i];
        totalB += b[i];
    }

    const int MAXA = 10001;
    // dp[k][sa] = max sumB for exactly k glasses with total capacity sa
    // -1 = unreachable
    vector<vector<int>> dp(n+1, vector<int>(MAXA, -1));
    dp[0][0] = 0;

    for(int i = 0; i < n; i++){
        // Traverse backwards to prevent using same glass twice (0/1 knapsack)
        for(int j = min(i, n-1); j >= 0; j--){
            for(int sa = 0; sa + a[i] < MAXA; sa++){
                if(dp[j][sa] < 0) continue;
                int nsa = sa + a[i];
                int nsb = dp[j][sa] + b[i];
                dp[j+1][nsa] = max(dp[j+1][nsa], nsb);
            }
        }
    }

    cout << fixed << setprecision(10);

    for(int k = 1; k <= n; k++){
        double ans = 0;
        for(int sa = 0; sa < MAXA; sa++){
            if(dp[k][sa] < 0) continue;
            int sb = dp[k][sa];
            double water = min((double)sa, sb + (totalB - sb) / 2.0);
            ans = max(ans, water);
        }
        cout << ans;
        if(k < n) cout << " ";
    }
    cout << "\n";

    return 0;
}
