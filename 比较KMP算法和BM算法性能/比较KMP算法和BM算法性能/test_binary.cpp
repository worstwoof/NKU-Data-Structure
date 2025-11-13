#include "algorithms.hpp"

using namespace std;

// 辅助函数：根据位置植入模式串
string setup_test_string(int N, int M, const string& alphabet, const string& pos_str, string& pattern) {
    string text = generate_random_string(N, alphabet);
    pattern = generate_random_string(M, alphabet);

    if (pos_str == "Begin") {
        text.replace(0, M, pattern);
    }
    else if (pos_str == "Middle") {
        text.replace(N / 2, M, pattern);
    }
    else if (pos_str == "End") {
        text.replace(N - M, M, pattern);
    }

    return text;
}

// 生成 ASCII 32-126 字符集
string get_ascii_alphabet() {
    string s = "";
    for (char c = 32; c <= 126; ++c) {
        s += c;
    }
    return s;
}

int main() {
    cout << "===== (三) 测试开始: 字符集 (ASCII 32-126) =====" << endl;

    const string alphabet = get_ascii_alphabet(); // 
    string text, pattern;

    // 1. 短模式串 [cite: 392]
    text = setup_test_string(1210, 32, alphabet, "Begin", pattern); // [cite: 393, 394, 395]
    run_test(text, pattern, "1. 短模式串 (N=1210, M=32, Begin)");

    text = setup_test_string(1210, 40, alphabet, "Middle", pattern); // [cite: 410, 411, 412]
    run_test(text, pattern, "1. 短模式串 (N=1210, M=40, Middle)");

    text = setup_test_string(1210, 40, alphabet, "End", pattern); // [cite: 427, 428, 429]
    run_test(text, pattern, "1. 短模式串 (N=1210, M=40, End)");

    // 2. 中等长度模式串 [cite: 443]
    text = setup_test_string(1210, 130, alphabet, "Begin", pattern); // [cite: 444, 445, 446]
    run_test(text, pattern, "2. 中模式串 (N=1210, M=130, Begin)");

    text = setup_test_string(1210, 145, alphabet, "Middle", pattern); // [cite: 461, 462, 463]
    run_test(text, pattern, "2. 中模式串 (N=1210, M=145, Middle)");

    text = setup_test_string(1210, 170, alphabet, "End", pattern); // [cite: 478, 479, 480]
    run_test(text, pattern, "2. 中模式串 (N=1210, M=170, End)");

    // 3. 长模式串 [cite: 496]
    text = setup_test_string(1210, 385, alphabet, "Begin", pattern); // [cite: 497, 498, 499]
    run_test(text, pattern, "3. 长模式串 (N=1210, M=385, Begin)");

    text = setup_test_string(1210, 500, alphabet, "Middle", pattern); // [cite: 514, 515, 516]
    run_test(text, pattern, "3. 长模式串 (N=1210, M=500, Middle)");

    text = setup_test_string(1210, 405, alphabet, "End", pattern); // [cite: 533, 534, 535]
    run_test(text, pattern, "3. 长模式串 (N=1210, M=405, End)");

    cout << "\n===== (三) 测试结束 =====" << endl;
    return 0;
}