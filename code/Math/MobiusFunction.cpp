// ——— μ(n) 누적합: M(n)=∑_{i≤n} μ(i) ———
unordered_map<ll,ll> memoM;
ll getM(ll n){
    if(n<2) return n;
    if(auto it=memoM.find(n); it!=memoM.end()) return it->second;
    ll res = 1;
    for(ll i=2, j; i<=n; i=j+1){
        ll q = n/i;
        j = n/q;
        res = (res - (j-i+1) * (getM(q)%MOD) % MOD + MOD) % MOD;  // divide by g(1)=1 for φ case
    }
    return memoM[n] = res;
}

// ——— S₀(N)=∑_{d≤N} φ(d) 재귀 — φ*1 = id  ⇒  s_{φ*1}(N)=N(N+1)/2
unordered_map<ll,ll> memo0;
ll getS0(ll n){
    if(n<=TH) return pref0[n];  // 아래 전처리 참조
    if(auto it=memo0.find(n); it!=memo0.end()) return it->second;
    ll res = mul(n%MOD, (n+1)%MOD) * inv2 % MOD;  // N(N+1)/2
    // 빼기 ∑_{d=2..n} S0(n/d)*1
    for(ll i=2, j; i<=n; i=j+1){
        ll q = n/i;
        j = n/q;
        ll cnt = (j - i + 1) % MOD;
        res = (res - cnt * getS0(q) % MOD + MOD) % MOD;
    }
    return memo0[n] = res;
}

// ——— S₁(N)=∑ d·φ(d) 재귀 — (nφ)*n = n² ⇒ s_{f*g}=∑ i²
unordered_map<ll,ll> memo1;
ll getS1(ll n){
    if(n<=TH) return pref1[n];
    if(auto it=memo1.find(n); it!=memo1.end()) return it->second;
    // ∑_{i=1..n} i² = n(n+1)(2n+1)/6
    ll res = mul( mul(n%MOD,(n+1)%MOD), ((2*n+1)%MOD) ) * inv6 % MOD;
    // 빼기 ∑_{d=2..n} S1(n/d)*d
    for(ll i=2, j; i<=n; i=j+1){
        ll q = n/i;
        j = n/q;
        // ∑_{d=i..j} d = (i+j)*(j-i+1)/2
        ll sumd = mul( mul((i+j)%MOD, (j-i+1)%MOD), inv2 );
        res = (res - sumd * getS1(q) % MOD + MOD) % MOD;
    }
    return memo1[n] = res;
}

// ——— S₂(N)=∑ d²·φ(d) 재귀 — (n²φ)*n² = n³ ⇒ s_{f*g}=∑ i³
unordered_map<ll,ll> memo2;
ll getS2(ll n){
    if(n<=TH) return pref2[n];
    if(auto it=memo2.find(n); it!=memo2.end()) return it->second;
    // ∑ i³ = [n(n+1)/2]²
    ll t = mul( mul(n%MOD,(n+1)%MOD), inv2 );
    ll res = mul(t, t);
    // 빼기 ∑_{d=2..n} S2(n/d)*d²
    for(ll i=2, j; i<=n; i=j+1){
        ll q = n/i;
        j = n/q;
        // ∑_{d=i..j} d² = sumSq(j)-sumSq(i-1)
        ll sj = mul( mul(mul(j%MOD,(j+1)%MOD),((2*j+1)%MOD)), inv6 );
        ll si = mul( mul(mul(((i-1)%MOD+MOD)%MOD, i%MOD), ((2*(i-1)+1)%MOD)), inv6 );
        ll sumd2 = sub(sj, si);
        res = (res - sumd2 * getS2(q) % MOD + MOD) % MOD;
    }
    return memo2[n] = res;
}

    TH = min<ll>(D, pow((long double)D, 2.0L/3.0L) + 1);
    pref0.assign(TH+1,0);
    pref1.assign(TH+1,0);
    pref2.assign(TH+1,0);

    // – 선형체로 μ와 φ 동시 전처리 –
    vector<int> primes;
    vector<bool> is_comp(TH+1,false);
    vector<int> phi(TH+1,0);
    phi[1]=1;
    for(int i=2;i<=TH;i++){
        if(!is_comp[i]){
            primes.push_back(i);
            phi[i]=i-1;
        }
        for(int p:primes){
            ll x=1LL*p*i;
            if(x>TH) break;
            is_comp[x]=true;
            if(i%p==0){
                phi[x]=phi[i]*p;
                break;
            }else{
                phi[x]=phi[i]*(p-1);
            }
        }
    }

    // – pref sums of φ, kφ, k²φ –
    inv2 = (MOD+1)/2;
    inv6 = modpow(6);
    for(int i=1;i<=TH;i++){
        pref0[i] = add(pref0[i-1], phi[i]);
        pref1[i] = add(pref1[i-1], mul(i, phi[i]));
        pref2[i] = add(pref2[i-1], mul(mul(i,i), phi[i]));
    }