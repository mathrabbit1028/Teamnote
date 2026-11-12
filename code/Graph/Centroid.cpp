#include <bits/stdc++.h>
using namespace std;
int n, sz[200010];
long long int a[200010], b[200010], ans, chk[200010];
vector<int> v[200010];
map<long long int, int> m;
int get_size(int x, int y)
{
    sz[x]=1;
    for(int e:v[x]){
        if(e!=y&&chk[e]==0) sz[x]+=get_size(e, x);
    }
    return sz[x];
}
int get_centroid(int x, int y, int z)
{
    for(int e:v[x]){
        if(e!=y&&chk[e]==0&&z<sz[e]) return get_centroid(e, x, z);
    }
    return x;
}
void cal(int x, int y, int z)
{
    ans+=m[-z];
    for(int e:v[x]){
        if(e!=y&&chk[e]==0) cal(e, x, z+a[e]);
    }
}
void update(int x, int y, int z)
{
    m[z]+=1;
    for(int e:v[x]){
        if(e!=y&&chk[e]==0){
            update(e, x, z+a[e]);
        }
    }
}
void cd(int x, int y)
{
    int z=get_size(x, y);
    int c=get_centroid(x, y, z/2);
    chk[c]=1;
    m.clear();
    for(int e:v[c]){
        if(chk[e]==0){
            cal(e, c, a[c]+a[e]);
            update(e, c, a[e]);
        }
    }
    ans+=m[-a[c]];
    for(int e:v[c]){
        if(chk[e]==0) cd(e, c);
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n;
    for(int i=1; i<=n; i++){
        char c;
        cin>>c;
        if(c=='U') a[i]=200001;
        if(c=='C') a[i]=-200002;
        if(c=='P') a[i]=200003;
    }
    for(int i=1; i<n; i++){
        int x, y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    cd(1, 0);
    cout<<ans;
}