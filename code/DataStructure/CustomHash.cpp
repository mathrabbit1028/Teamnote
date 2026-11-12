// 필요: <cstdint>, <chrono>, <utility>, <unordered_set>,
//       <unordered_map>, <string>, <cassert>, using namespace std;
struct CustomHash {
    static uint64_t mix(uint64_t x) { // splitmix64
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t seed =
            chrono::steady_clock::now().time_since_epoch().count();
        return mix(x + seed);
    }
};
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        // 두 32비트 정수를 하나의 64비트 값으로 합친다 (음수도 가능).
        uint64_t key = (uint64_t(uint32_t(p.first)) << 32)
                     | uint32_t(p.second);
        return CustomHash{}(key);
    }
};
void custom_hash_example() {
    // set은 두 번째, map은 세 번째 템플릿 인자가 해시 함수 객체.
    unordered_set<long long, CustomHash> st;
    unordered_map<pair<int, int>, string, PairHash> mp;
    st.max_load_factor(0.7f); st.reserve(1000); // 순서에 유의
    mp.max_load_factor(0.7f); mp.reserve(1000);
    st.insert(-42);
    mp[{1, -2}] = "hello";
    assert(st.count(-42) == 1);
    auto it = mp.find({1, -2}); // 조회만 할 때 []는 새 원소를 만들 수 있음
    assert(it != mp.end() && it->second == "hello");
    // 사용자 struct 키는 operator==도 정의 (또는 KeyEqual 지정).
    // seed는 실행 중 고정. 난수화는 최악 시간 복잡도를 보장하지 않음.
}
