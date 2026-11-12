#include <bits/stdc++.h>
using namespace std;
int l, g;
long long c[8010], dp[810][8010];
void f(int i, int l, int r, int s, int e)
{
    if(l>r) return;
    int mid=(l+r)/2, opt=-1;
    dp[i][mid]=1e18;
    for(int k=s; k<=min(e, mid-1); k++){
        long long x=dp[i-1][k]+(c[mid]-c[k])*(mid-k);
        if(dp[i][mid]>x){
            dp[i][mid]=x, opt=k;
        }
    }
    f(i, l, mid-1, s, opt);
    f(i, mid+1, r, opt, e);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>l>>g;
    g=min(g, l);
    for(int i=1; i<=l; i++) cin>>c[i], c[i]+=c[i-1];
    for(int i=1; i<=l; i++) dp[1][i]=i*c[i];
    for(int i=2; i<=g; i++) f(i, i, l, i-1, l-1);
    cout<<dp[g][l];
}