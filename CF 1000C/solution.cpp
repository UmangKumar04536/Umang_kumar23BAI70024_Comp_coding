/*
================================================================================
  Problem  : CF 1000C — Covered Points Count
  Platform : Codeforces
  Topic    : Sweep Line / Coordinate Compression / Difference Array
  Verdict  : Accepted | 187 ms | 4000 KB
  Date     : Apr 24, 2026
  Profile  : muskanrathee725

  Approach :
  - For each segment [l, r]: push event (l, +1) and (r+1, -1).
  - Sort all events by coordinate.
  - Sweep left to right. Between two consecutive event coordinates,
    the coverage count is constant = cur.
  - Add gap length (coord - prev_coord) to ans[cur].
  - Coordinates up to 10^18 so use gap lengths directly (not a real array).
  - Time: O(n log n)
================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<long long,int>> events;
    events.reserve(2*n);

    for(int i = 0; i < n; i++){
        long long l, r;
        cin >> l >> r;
        events.push_back({l, 1});
        events.push_back({r+1, -1});
    }

    sort(events.begin(), events.end());

    vector<long long> ans(n+1, 0);

    long long prev_coord = 0;
    int cur = 0;
    bool first = true;

    for(int i = 0; i < (int)events.size(); ){
        long long coord = events[i].first;

        if(!first && cur > 0){
            ans[cur] += coord - prev_coord;
        }

        while(i < (int)events.size() && events[i].first == coord){
            cur += events[i].second;
            i++;
        }

        prev_coord = coord;
        first = false;
    }

    for(int k = 1; k <= n; k++){
        cout << ans[k];
        if(k < n) cout << " ";
    }
    cout << "\n";

    return 0;
}
