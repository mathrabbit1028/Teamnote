// 필요: <vector>, <cassert>, using namespace std;
struct Fenwick {
    int n;
    vector<long long> tree;
    Fenwick(int n) : n(n), tree(n + 1) {}
    void add(int i, long long delta) { // a[i] += delta, 1 <= i <= n
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    long long prefix(int i) const { // a[1] + ... + a[i], prefix(0) = 0
        long long ret = 0;
        for (; i > 0; i -= i & -i) ret += tree[i];
        return ret;
    }
    long long sum(int l, int r) const { // [l, r], 1 <= l <= r <= n
        return prefix(r) - prefix(l - 1);
    }
};

void fenwick_example() {
    Fenwick ft(5);
    vector<long long> a = {0, 1, 2, 3, 4, 5}; // a[0] 미사용
    for (int i = 1; i <= 5; ++i) ft.add(i, a[i]);
    assert(ft.sum(2, 4) == 9);
    // a[3]을 10으로 대입하려면 기존 값과의 차이를 더한다.
    ft.add(3, 10 - a[3]); a[3] = 10;
    assert(ft.prefix(3) == 13);
    // add(0, ...)는 무한 루프! 인덱스는 반드시 1 이상.
}
