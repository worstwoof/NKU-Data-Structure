#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // 1. 读取矩阵
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> matrix[i][j];
        }
    }

    // 存储最终结果
    vector<int> result;

    // 2. 定义边界
    int top = 0, bottom = n - 1;
    int left = 0, right = m - 1;

    // 3. 定义旋转方向
    bool clockwise = true;

    // 4. 循环处理直到边界相遇
    while (top <= bottom && left <= right) {

        if (clockwise) {
            // --- 顺时针 ---

            // 1. 打印顶行 (从左到右)
            for (int i = left; i <= right; ++i) {
                result.push_back(matrix[top][i]);
            }
            top++; // 顶边界下移

            // 2. 打印右列 (从上到下)
            for (int i = top; i <= bottom; ++i) {
                result.push_back(matrix[i][right]);
            }
            right--; // 右边界左移

            // 3. 打印底行 (从右到左)
            // 检查行边界是否仍然有效
            if (top <= bottom) {
                for (int i = right; i >= left; --i) {
                    result.push_back(matrix[bottom][i]);
                }
                bottom--; // 底边界上移
            }

            // 4. 打印左列 (从下到上)
            // 检查列边界是否仍然有效
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    result.push_back(matrix[i][left]);
                }
                left++; // 左边界右移
            }
        }
        else {

            // 1. 打印左列 (从上到下)
            for (int i = top; i <= bottom; ++i) {
                result.push_back(matrix[i][left]);
            }
            left++; // 左边界右移

            // 2. 打印底行 (从左到右)
            if (top <= bottom) {
                for (int i = left; i <= right; ++i) {
                    result.push_back(matrix[bottom][i]);
                }
                bottom--; // 底边界上移
            }

            // 3. 打印右列 (从下到上)
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    result.push_back(matrix[i][right]);
                }
                right--; // 右边界左移
            }

            // 4. 打印顶行 (从右到左)
            if (top <= bottom) {
                for (int i = right; i >= left; --i) {
                    result.push_back(matrix[top][i]);
                }
                top++; // 顶边界下移
            }
        }

        // 切换方向
        clockwise = !clockwise;
    }

    // 5. 按格式输出结果
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}