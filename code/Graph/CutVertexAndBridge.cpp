#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, ord[101010], ch[101010], iscut[101010];
vector<int> adj[101010];
 
int r = 0;
int solve(int v) {
    ord[v] = ++r;
    int fast = 1e9, child = 0;
 
    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i];
        if (ch[u] == 1) fast = min(fast, ord[u]);
        else {
            child++;
            ch[u] = 1;
            int prev = solve(u);
            if (v != 1 && prev >= ord[v]) iscut[v] = 1;
            fast = min(fast, prev);
        }
    }
 
    if (v == 1 && child >= 2) iscut[v] = 1;
 
    return fast;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    ch[1] = 1;
    solve(1);
 
    for (int i = 1; i <= n; i++) cout << iscut[i];
 
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, ord[101010], ch[101010], iscut[202020];
vector< pair<int, int> > adj[101010];
 
int r = 0;
int solve(int v, int p) {
    ord[v] = ++r;
    int fast = 1e9;
 
    for (int i = 0; i < adj[v].size(); i++) {
        int u = adj[v][i].first, j = adj[v][i].second;
        if (u == p) continue;
        if (ch[u] == 1) fast = min(fast, ord[u]);
        else {
            ch[u] = 1;
            int prev = solve(u, v);
            if (prev > ord[v]) iscut[j] = 1;
            fast = min(fast, prev);
        }
    }
 
    return fast;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
 
    ch[1] = 1;
    solve(1, 0);
 
    for (int i = 1; i <= m; i++) cout << iscut[i];
 
    return 0;
}