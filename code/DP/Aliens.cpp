#include <bits/stdc++.h>
using namespace std;
#define int long long int
int n, k;
int a[50010], dp[50010], dis[50010];
int cost(int x, int y)
{
    return dp[x]+(y-x)*(a[y]-a[x]);
}
int cross(int x, int y)
{
    int l=y+1, r=n+1;
    while(1){
        if(l>=r) return l-1;
        int mid=(l+r)/2;
        if(cost(x, mid)<cost(y, mid)) l=mid+1;
        else r=mid;
    }
}
void monotone(int m)
{
    deque<int> dq;
    for(int i=1; i<=n; i++){
        while(dq.size()>=2){
            int x=dq[dq.size()-2];
            int y=dq[dq.size()-1];
            if(cross(x, y)>=cross(y, i-1)) dq.pop_back();
            else break;
        }
        dq.push_back(i-1);
        while(dq.size()>=2){
            int x=dq[0], y=dq[1];
            if(cross(x, y)<i) dq.pop_front();
            else break;
        }
        dis[i]=dis[dq[0]]+1;
        dp[i]=cost(dq[0], i)+m;
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>k;
    for(int i=1; i<=n; i++) cin>>a[i], a[i]+=a[i-1];
    if(k>=n){
        cout<<a[n];
        return 0;
    }
    int l=0, r=2e14;
    while(l<r){
        int mid=(l+r)/2;
        monotone(mid);
        if(dis[n]>k) l=mid+1;
        else r=mid;
    }
    monotone(l);
    cout<<dp[n]-k*l;
}
void monotone(int m)
{
    int x=0, y=1;
    q[0]=0, c[0]=n;
    for(int i=1; i<=n; i++){
        while(c[x]<i) x++;
        dp[i]=cost(q[x], i)+m;
        dis[i]=dis[q[x]]+1;
        while(x+1<y&&c[y-2]>=cross(q[y-1], i)) y--;
        c[y-1]=cross(q[y-1], i), q[y]=i, c[y++]=n;
    }
}