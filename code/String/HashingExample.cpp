// 위 Hashing 정의와 <vector>, <string>, <cassert> 필요.
// h[i] = (h[i-1] * P + s[i-1]) % M
// hash(l, r) = (h[r] - h[l-1] * P^(r-l+1)) mod M
// 앞부분을 빼므로 시작 위치가 달라도 같은 길이끼리 직접 비교 가능.
void rolling_hash_example() {
    string s = "abracadabra", pattern = "abra";
    // 두 모듈러를 함께 비교하여 충돌 가능성을 줄인다.
    Hashing<911382323, 1000000007> a, pa;
    Hashing<911382323, 1000000009> b, pb;
    a.build(s); b.build(s);
    pa.build(pattern); pb.build(pattern);
    assert(a.get(1, 4) == a.get(8, 11));
    int n = s.size(), m = pattern.size(); // 이 예제는 m >= 1
    vector<int> positions;
    for (int l = 1; l + m - 1 <= n; ++l) {
        int r = l + m - 1;
        if (a.get(l, r) == pa.get(1, m) &&
            b.get(l, r) == pb.get(1, m)) positions.push_back(l);
    }
    assert((positions == vector<int>{1, 8})); // 1-based 시작 위치
    // 전체 O(n+m). 이중 해시도 충돌 가능성은 0이 아니다.
    // 정확한 매칭 보장이 필요하면 KMP/Z 사용.
}
