// 필요: <bitset>, <string>, <cassert>, using namespace std;
void bitset_example() {
    bitset<8> a(string("00101100")), b(5); // b = 00000101
    assert(a[2] && a.test(3)); // 비트 읽기, 유효 인덱스 [0, 8)
    a.set(0); a.reset(2); a.flip(1); // 1로, 0으로, 반전
    a[7] = true;
    auto both = a & b; // 교집합
    auto either = a | b; // 합집합
    auto diff = a ^ b; // 서로 다른 비트
    auto inv = ~a; // 전체 반전
    auto left = a << 2; // 높은 자리로 이동, 넘친 비트 버림
    auto right = a >> 2; // 빈 자리는 0으로 채움
    auto cnt = a.count(); // 1의 개수
    bool any = a.any(), all = a.all(), none = a.none();
    string s = a.to_string(); // 항상 8자리
    auto x = a.to_ullong(); // 범위를 넘으면 overflow_error
    assert(both.to_ulong() == 1 && either.to_ulong() == 175);
    assert(diff.to_ulong() == 174 && inv.to_ulong() == 84);
    assert(left.to_ulong() == 172 && right.to_ulong() == 42);
    assert(cnt == 5 && any && !all && !none);
    assert(s == "10101011" && x == 171);
    a.set(); a.flip(); a.reset(); // 전체 1, 전체 반전, 전체 0

    // 부분집합 합: 각 수를 최대 한 번 사용 (모두 음이 아닌 정수)
    // dp[s] = 합 s를 만들 수 있는가? 0 <= s <= MAX_SUM만 관리
    constexpr int MAX_SUM = 100;
    bitset<MAX_SUM + 1> dp;
    dp[0] = 1;
    for (int v : {3, 5, 8}) dp |= dp << v;
    assert(dp[8] && dp[16] && !dp[7]);
    // 비트 연산은 보통 O(비트 수 / 워드 크기), 공간 O(비트 수).
    // 런타임 크기가 필요하면 vector<uint64_t> 등으로 구현.
}
