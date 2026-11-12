// 필요: <iostream>, <iomanip>, <string>, <sstream>, <limits>
// using namespace std; 각 함수는 별개의 입력 상황에서 사용.
// main 시작: ios::sync_with_stdio(false); cin.tie(nullptr);
// 동기화를 끈 뒤에는 scanf/printf와 cin/cout을 섞지 않는다.

void read_until_eof() { // 입력 개수 없이 EOF까지 정수 입력
    long long x;
    while (cin >> x) cout << x << '\n';
    // 두 개씩: while (cin >> a >> b) { ... }
    // 잘못된 형식도 반복 종료. while (!cin.eof())는 사용하지 않는다.
}
void read_lines() { // 공백/빈 줄을 포함하여 한 줄씩, EOF까지
    string line;
    while (getline(cin, line)) {
        // getline은 개행 문자를 소비하지만 line에는 넣지 않는다.
        cout << line << '\n';
    }
}
void read_after_number() {
    int n;
    if (!(cin >> n)) return;
    // >>가 남긴 개행을 포함해 현재 줄의 나머지를 버린 뒤 다음 줄 입력
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    if (!getline(cin, line)) return;
    // 한 줄에 있는 정수만 읽기 (개수 미지정)
    istringstream iss(line);
    int x;
    while (iss >> x) cout << x << '\n';
    // getline(cin >> ws, line)은 선행 공백과 빈 줄까지 모두 건너뜀.
    // 공백/빈 줄 보존이 필요하면 위의 ignore + getline 사용.
}
void precision_example() {
    double x = 123.456789;
    cout << fixed << setprecision(3) << x << '\n'; // 123.457 (소수 3자리)
    cout << defaultfloat << setprecision(5) << x << '\n'; // 123.46 (유효 5자리)
    cout << scientific << setprecision(2) << x << '\n'; // 1.23e+02
    // 설정은 이후 출력에도 유지. 기본 상태로 복원:
    cout << defaultfloat << setprecision(6);
}
