#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

vector<vector<int>> transpose(const vector<vector<int>> &m){
    vector<vector<int>> result(m[0].size(), vector<int>(m.size(), 0));
    for(auto row = 0; row < m.size(); row++){
        for(auto col = 0; col < m[0].size(); col++){
            result[col][row] = m[row][col];
        }
    }
    return result;
}

int dot_product(const vector<int> &v1, const vector<int> &v2){
    int result = 0;
    for(auto i = 0; i < v1.size(); i++){
        result += v1[i] * v2[i];
    }
    return result;
}

vector<int> single_product(const vector<int> &v, const vector<vector<int>> &m){
    vector<int> result(m[0].size(), 0);
    for(auto i = 0; i < m[0].size(); i++){
        result[i] = dot_product(v, m[i]);
    }
    return result;
}

auto recurse(const vector<vector<int>> &m1, const vector<vector<int>> &m2, int l, int u){
    if(u-l == 1){
        auto row = single_product(m1[l], m2);
        return vector<vector<int>>{row};
    }
    int mid = (l+u+1)/2;
    auto result = recurse(m1, m2, l, mid);
    auto result2 = recurse(m1, m2, mid, u);
    result.insert(result.end(), result2.begin(), result2.end());
    return result;
}

auto product(vector<vector<int>> m1, vector<vector<int>> m2){
    if(m1[0].size() != m2.size()){
        throw invalid_argument("Matrix dimensions do not match");
    }
    m2 = transpose(m2);
    int n = m1.size();
    return recurse(m1, m2, 0, n);
}

void printMatrix(const vector<vector<int>> &m){
    for(auto row = 0; row < m.size(); row++){
        for(auto col = 0; col < m[0].size(); col++){
            cout << m[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Create a 3x3 matrix filled with 1s
    std::vector<std::vector<int>> matrix1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    // Create a 3x3 matrix filled with 2s
    std::vector<std::vector<int>> matrix2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    // Now you can use matrix1 and matrix2
    auto result = product(matrix1, matrix2);

    cout << "Matrix 1: " << endl;
    printMatrix(matrix1);
    cout << "Matrix 2: " << endl;
    printMatrix(matrix2);
    cout << "Product: " << endl;
    printMatrix(result);
}