/*
================================================================================
  Problem  : CF 190C — STL
  Platform : Codeforces
  Topic    : STL / Sorting
  Verdict  : Accepted | 92 ms | 13200 KB
  Date     : Apr 24, 2026
  Profile  : muskanrathee725
================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    for(int i = 0; i < n; i++){
        cout << a[i];
        if(i < n-1) cout << " ";
    }
    cout << "\n";
    return 0;
}
