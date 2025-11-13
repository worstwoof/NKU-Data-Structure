#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <chrono>      // 用于高精度计时
#include <random>      // 用于生成随机字符串
#include <iomanip>     // 用于格式化输出 (setw, left)
#include <algorithm>   // 用于 std::max
#include <numeric>     // 用于 std::accumulate

using namespace std;

// ------------------------------------------------------------------
// 辅助函数：字符串生成
// ------------------------------------------------------------------
string generate_random_string(int length, const string& alphabet) {
    string result = "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphabet.length() - 1);
    for (int i = 0; i < length; ++i) {
        result += alphabet[dis(gen)];
    }
    return result;
}

// ------------------------------------------------------------------
// 算法 1: 标准 KMP (来自您的 PDF [cite: 699-741])
// ... (此部分代码与之前相同，为节省篇幅故折叠) ...
// ------------------------------------------------------------------
namespace KMP_Standard {
    // [cite: 700-720]
    vector<int> computeLPS(const string& pattern) {
        int length = 0;
        vector<int> lps(pattern.size(), 0);
        int i = 1;
        while (i < pattern.size()) {
            if (pattern[i] == pattern[length]) {
                length++;
                lps[i] = length;
                i++;
            }
            else {
                if (length != 0) {
                    length = lps[length - 1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    // [cite: 721-741] 
    int KMP(const string& text, const string& pattern, int& comparisons) {
        vector<int> lps = computeLPS(pattern);
        int i = 0, j = 0;
        comparisons = 0;
        while (i < text.size()) {
            comparisons++;
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            if (j == pattern.size()) {
                return i - j; // 匹配成功
            }
            else if (i < text.size() && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                }
                else {
                    i++;
                }
            }
        }
        return -1; // 匹配失败
    }
} // namespace KMP_Standard

// ------------------------------------------------------------------
// 算法 2: 优化的 KMP (nextval)
// ... (此部分代码与之前相同，为节省篇幅故折叠) ...
// ------------------------------------------------------------------
namespace KMP_Optimized {
    vector<int> get_optimized_nextval(const string& b) {
        int m = b.length();
        if (m == 0) return {};
        vector<int> nextval(m);
        nextval[0] = 0;
        int j = 0;
        for (int i = 1; i < m; i++) {
            while (j > 0 && b[i] != b[j]) {
                j = nextval[j - 1];
            }
            if (b[i] == b[j]) {
                j++;
            }
            if (j > 0 && b[i] == b[j] && j < m) {
                nextval[i] = nextval[j - 1];
            }
            else {
                nextval[i] = j;
            }
        }
        return nextval;
    }

    int KMP_Opt(const string& text, const string& pattern, int& comparisons) {
        if (pattern.empty()) return 0;
        vector<int> nextval = get_optimized_nextval(pattern);
        int i = 0, j = 0;
        comparisons = 0;
        while (i < text.size()) {
            comparisons++;
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            if (j == pattern.size()) {
                return i - j; // 匹配成功
            }
            else if (i < text.size() && pattern[j] != text[i]) {
                if (j != 0) {
                    j = nextval[j - 1];
                }
                else {
                    i++;
                }
            }
        }
        return -1; // 匹配失败
    }
} // namespace KMP_Optimized


// ------------------------------------------------------------------
// 算法 3: 修正后的 BM 算法 (坏字符 + 好后缀)
// ... (此部分代码与之前相同，为节省篇幅故折叠) ...
// ------------------------------------------------------------------
namespace BM_Corrected {

    // 1. 坏字符规则
    void buildBadChar(const string& pattern, vector<int>& badChar) {
        int m = pattern.length();
        badChar.assign(256, -1);
        for (int i = 0; i < m; i++) {
            badChar[(int)pattern[i]] = i;
        }
    }

    // 2. 好后缀规则 (一个正确的实现)
    void buildGoodSuffix(const string& pattern, vector<int>& goodSuffix) {
        int m = pattern.length();
        goodSuffix.assign(m + 1, m);
        vector<int> suffix(m, 0);

        // Pass 1: 计算 suffix 数组
        suffix[m - 1] = m;
        int g = m - 1, f = 0;
        for (int i = m - 2; i >= 0; --i) {
            if (i > g && suffix[i + m - 1 - f] < i - g) {
                suffix[i] = suffix[i + m - 1 - f];
            }
            else {
                if (i < g) g = i;
                f = i;
                while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                    --g;
                }
                suffix[i] = f - g;
            }
        }

        // Pass 2: (情况2: 找到匹配的前缀)
        // (修正: j = m-1-i)
        for (int i = m - 1; i >= 0; --i) {
            if (suffix[i] == i + 1) { // i+1 是后缀长度
                for (int j = 0; j <= m - 1 - (i + 1); ++j) {
                    if (goodSuffix[j] == m) {
                        goodSuffix[j] = m - 1 - i;
                    }
                }
            }
        }

        // Pass 3: (情况1: 找到另一个匹配的后缀)
        // (修正: j = m-1-suffix[i])
        for (int i = 0; i <= m - 2; ++i) {
            // (修正: goodSuffix[m-1-suffix[i]] -> goodSuffix[m-suffix[i]-1])
            // (修正: m-1-i -> m-i-1)
            // (注: 原代码此处逻辑有误，已修正为标准实现)
            goodSuffix[m - 1 - suffix[i]] = min(goodSuffix[m - 1 - suffix[i]], m - 1 - i);
        }
    }

    int BM(const string& text, const string& pattern, int& comparisons) {
        int n = text.length();
        int m = pattern.length();
        if (m == 0) return 0;
        if (n < m) return -1;

        vector<int> badChar;
        vector<int> goodSuffix;
        buildBadChar(pattern, badChar);
        buildGoodSuffix(pattern, goodSuffix);

        comparisons = 0;
        int s = 0;
        while (s <= n - m) {
            int j = m - 1;

            while (j >= 0) {
                comparisons++;
                if (pattern[j] != text[s + j]) {
                    break;
                }
                j--;
            }

            if (j < 0) {
                return s; // 匹配成功
            }
            else {
                int badCharShift = j - badChar[(int)text[s + j]];
                int goodSuffixShift = goodSuffix[j + 1];

                s += max({ 1, badCharShift, goodSuffixShift });
            }
        }
        return -1; // 匹配失败
    }
} // namespace BM_Corrected


// ------------------------------------------------------------------
// 实验运行和打印函数 (*** 已更新为循环10次取平均值 ***)
// ------------------------------------------------------------------

void run_test(string text, string pattern, const string& test_name) {
    cout << "\n--- " << test_name << " ---" << endl;
    cout << "主串长度: " << text.length() << endl;
    cout << "模式串长度: " << pattern.length() << endl;

    // 打印主串和模式串 (与您PDF报告一致 [cite: 147-158, 173-190, 205-224])
    cout << "主串: " << text << endl;
    cout << "模式串: " << pattern << endl;

    // ----- 新增：循环运行10次 -----
    const int RUN_COUNT = 10;
    int comparisons = 0;
    int result = -1;

    double total_time_kmp_std = 0;
    long long total_comps_kmp_std = 0;

    double total_time_kmp_opt = 0;
    long long total_comps_kmp_opt = 0;

    double total_time_bm = 0;
    long long total_comps_bm = 0;

    for (int i = 0; i < RUN_COUNT; ++i) {
        // --- 1. KMP (Standard) ---
        comparisons = 0;
        auto start = chrono::high_resolution_clock::now();
        result = KMP_Standard::KMP(text, pattern, comparisons);
        auto end = chrono::high_resolution_clock::now();
        total_time_kmp_std += chrono::duration<double, std::milli>(end - start).count();
        total_comps_kmp_std += comparisons;

        // --- 2. KMP (Optimized) ---
        comparisons = 0;
        start = chrono::high_resolution_clock::now();
        result = KMP_Optimized::KMP_Opt(text, pattern, comparisons);
        end = chrono::high_resolution_clock::now();
        total_time_kmp_opt += chrono::duration<double, std::milli>(end - start).count();
        total_comps_kmp_opt += comparisons;

        // --- 3. Boyer-Moore (Corrected) ---
        comparisons = 0;
        start = chrono::high_resolution_clock::now();
        result = BM_Corrected::BM(text, pattern, comparisons);
        end = chrono::high_resolution_clock::now();
        total_time_bm += chrono::duration<double, std::milli>(end - start).count();
        total_comps_bm += comparisons;
    }

    // --- 打印平均结果 ---

    cout << "KMP算法 (Standard):" << endl;
    cout << "  匹配结果索引: " << result << endl;
    cout << "  (平均)字符比较次数: " << total_comps_kmp_std / RUN_COUNT << endl;
    cout << "  (平均)搜索时间: " << fixed << setprecision(4) << (total_time_kmp_std / RUN_COUNT) << "ms" << endl;

    cout << "KMP算法 (Optimized):" << endl;
    cout << "  匹配结果索引: " << result << endl;
    cout << "  (平均)字符比较次数: " << total_comps_kmp_opt / RUN_COUNT << endl;
    cout << "  (平均)搜索时间: " << fixed << setprecision(4) << (total_time_kmp_opt / RUN_COUNT) << "ms" << endl;

    cout << "Boyer-Moore算法:" << endl;
    cout << "  匹配结果索引: " << result << endl;
    cout << "  (平均)字符比较次数: " << total_comps_bm / RUN_COUNT << endl;
    cout << "  (平均)搜索时间: " << fixed << setprecision(4) << (total_time_bm / RUN_COUNT) << "ms" << endl;
}

#endif // ALGORITHMS_HPP