int N, M, C[10101]; // C[i] = i번 정점이 속한 SCC 번호
vector<int> G[10101], R[10101], V;
vector<vector<int>> S; // 각 SCC에 속한 정점 목록
void AddEdge(int s, int e){
    G[s].push_back(e);
    R[e].push_back(s);
}
void DFS1(int v){
    C[v] = -1;
    for(auto i : G[v]) if(!C[i]) DFS1(i);
    V.push_back(v);
}
void DFS2(int v, int c){
    C[v] = c; S.back().push_back(v);
    for(auto i : R[v]) if(C[i] == -1) DFS2(i, c);
}
int GetSCC(){ // SCC 개수 반환
    for(int i=1; i<=N; i++) if(!C[i]) DFS1(i);
    reverse(V.begin(), V.end());
    int cnt = 0;
    for(auto i : V) if(C[i] == -1) S.emplace_back(), DFS2(i, cnt++);
    return cnt;
} // 각 SCC는 위상 정렬 순서대로 번호 매겨져 있음

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
vector<int> adj1[202020], adj2[202020];
 
int ch[202020];
stack<int> stk;
vector< vector<int> > scc;
void dfs1(int v) {
    ch[v] = 1;
    for (int i = 0; i < adj1[v].size(); i++) {
        int u = adj1[v][i];
        if (ch[u]) continue;
        dfs1(u);
    }
    stk.push(v);
}
 
void dfs2(int v) {
    ch[v] = 1;
    scc.back().push_back(v);
    for (int i = 0; i < adj2[v].size(); i++) {
        int u = adj2[v][i];
        if (ch[u]) continue;
        dfs2(u);
    }
}
 
bool res;
set<int> S;
void check(int v) {
    ch[v] = 1;
    if (S.find(v%n) == S.end()) S.insert(v%n);
    else res = false;
    for (int i = 0; i < adj1[v].size(); i++) {
        int u = adj1[v][i];
        if (ch[u]) continue;
        check(u);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    while (scanf("%d %d", &n, &m) == 2) {
        bool ans = true;
        scc.clear();
        while (stk.size() > 0) stk.pop();
 
        for (int i = 1; i <= 2*n; i++) adj1[i].clear();
        for (int i = 1; i <= 2*n; i++) adj2[i].clear();
        
        for (int i = 0; i < m; i++) {
            int a, b, na, nb;
            scanf("%d %d", &a, &b);
            na = -a; nb = -b;
            if (a < 0) a = -a+n;
            if (b < 0) b = -b+n;
            if (na < 0) na = -na+n;
            if (nb < 0) nb = -nb+n;
            adj1[na].push_back(b);
            adj1[nb].push_back(a);
            adj2[b].push_back(na);
            adj2[a].push_back(nb);
        }
 
        for (int i = 1; i <= 2*n; i++) ch[i] = 0;
        for (int i = 1; i <= 2*n; i++) {
            if (ch[i]) continue;
            dfs1(i);
        }
 
        for (int i = 1; i <= 2*n; i++) ch[i] = 0;
        while (stk.size() > 0) {
            int v = stk.top();
            stk.pop();
            if (ch[v]) continue;
            scc.push_back(vector<int>());
            dfs2(v);
        }
 
        for (int i = 0; i < scc.size(); i++) {
            set<int> s;
            for (int j = 0; j < scc[i].size(); j++) {
                if (s.find(scc[i][j]%n) == s.end()) s.insert(scc[i][j]%n);
                else ans = false;
            }
        }
 
        for (int i = 1; i <= 2*n; i++) ch[i] = 0;
        res = true;
        S.clear();
        check(1);
        if (!res) ans = false;
 
        cout << (ans ? "yes\n" : "no\n");
 
    }
    
    return 0;
}