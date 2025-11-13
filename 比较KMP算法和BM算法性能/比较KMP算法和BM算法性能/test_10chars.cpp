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

int main() {
    cout << "===== (二) 测试开始: 字符集 (10种) =====" << endl;

    // [cite: 122] (从截图中推断的字符集)
    const string alphabet = "qwertyuiop";
    string text, pattern;

    // 1. 短模式串 [cite: 115]
    text = setup_test_string(1440, 20, alphabet, "Begin", pattern); // [cite: 116, 117, 119]
    run_test(text, pattern, "1. 短模式串 (N=1440, M=20, Begin)");

    text = setup_test_string(1440, 20, alphabet, "Middle", pattern); // [cite: 144, 145, 146]
    run_test(text, pattern, "1. 短模式串 (N=1440, M=20, Middle)");

    text = setup_test_string(1440, 20, alphabet, "End", pattern); // [cite: 171, 172, 173]
    run_test(text, pattern, "1. 短模式串 (N=1440, M=20, End)");

    // 2. 中等长度模式串 [cite: 200]
    text = setup_test_string(1440, 341, alphabet, "Begin", pattern); // [cite: 201, 202, 203]
    run_test(text, pattern, "2. 中模式串 (N=1440, M=341, Begin)");

    text = setup_test_string(1440, 350, alphabet, "Middle", pattern); // [cite: 233, 234, 235]
    run_test(text, pattern, "2. 中模式串 (N=1440, M=350, Middle)");

    text = setup_test_string(1440, 310, alphabet, "End", pattern); // [cite: 264, 265, 266]
    run_test(text, pattern, "2. 中模式串 (N=1440, M=310, End)");

    // 3. 长模式串 [cite: 294]
    text = setup_test_string(1440, 632, alphabet, "Begin", pattern); // [cite: 295, 296, 297]
    run_test(text, pattern, "3. 长模式串 (N=1440, M=632, Begin)");

    text = setup_test_string(1440, 400, alphabet, "Middle", pattern); // [cite: 329, 330, 331]
    run_test(text, pattern, "3. 长模式串 (N=1440, M=400, Middle)");

    text = setup_test_string(1440, 420, alphabet, "End", pattern); // [cite: 360, 361, 362]
    run_test(text, pattern, "3. 长模式串 (N=1440, M=420, End)");

    cout << "\n===== (二) 测试结束 =====" << endl;
    return 0;
}