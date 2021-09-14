
//数组

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
//119. 杨辉三角 II
//法一：手动模拟构造过程，整个过程中只需用到两个数组，一个tmp储存上一行的元素，一个ans按照tmp来构造新的数组，通过将ans=tmp来实现数组下移
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return { 1 };
        } 
        vector<int> ans, tmp;
        ans = { 1,1 };
        for (int i = 0; i < rowIndex-1; i++) {
            tmp.clear();
            tmp.push_back(1);
            for (int j = 0; j < ans.size()-1; j++) {
                tmp.push_back(ans[j] + ans[j + 1]);
            }
            tmp.push_back(1);
            ans = tmp;
        }
        return ans;
        
    }
};

//官解类似
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> pre, cur;
        for (int i = 0; i <= rowIndex; ++i) {
            cur.resize(i + 1);
            cur[0] = cur[i] = 1;
            for (int j = 1; j < i; ++j) {
                cur[j] = pre[j - 1] + pre[j];
            }
            pre = cur;
        }
        return pre;
    }
};

//方法二：进一步优化，只用一个数组，倒着计算当前行，这样计算到第 i 项时，第 i−1 项仍然是上一行的值。
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1);
        row[0] = 1;
        for (int i = 1; i <= rowIndex; ++i) {
            for (int j = i; j > 0; --j) {
                row[j] += row[j - 1];  
            }
        }
        return row;
    }
};

//方法三：线形递推，由组合公式，C(m,n)=C(m-1,n)*(n-m+1)/m
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1);
        row[0] = 1;
        for (int i = 1; i <= rowIndex; ++i) {
            row[i] = 1LL * row[i - 1] * (rowIndex - i + 1) / i;
        }
        return row;
    }
};



//48. 旋转图像
// 法一：
//层层旋转，每一圈的四个方向位置的元素进行旋转
class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size();
		for (int i = 0; i < n / 2; i++) {
			for (int j = i; j < n - i - 1; j++) {
				int row = i, col = j;
				int tmp1 = matrix[row][col];
				for (int k = 0; k < 4; k++) {
					int tmp2 = matrix[col][n - 1 - row];
					matrix[col][n - 1 - row] = tmp1;
					tmp1 = tmp2;
					int r = row;
					row = col, col = n - 1 - r;
				}
			}
		}
	}
};
//官解类似
class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size();
		for (int i = 0; i < n / 2; ++i) {
			for (int j = 0; j < (n + 1) / 2; ++j) {
				int temp = matrix[i][j];
				matrix[i][j] = matrix[n - j - 1][i];
				matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
				matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
				matrix[j][n - i - 1] = temp;
				//C++17写法
				//tie(matrix[i][j], matrix[n - j - 1][i], matrix[n - i - 1][n - j - 1], matrix[j][n - i - 1]) \
                    = make_tuple(matrix[n - j - 1][i], matrix[n - i - 1][n - j - 1], matrix[j][n - i - 1], matrix[i][j]);

			}
		}
	}
};

//方法二：用翻转代替旋转
//先按水平轴翻转，再按对称轴翻转，即可得到于法一相同的替换规律matrix[col][n-row-1]=matrix[row][col]
class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size();
		// 水平翻转
		for (int i = 0; i < n / 2; ++i) {
			for (int j = 0; j < n; ++j) {
				swap(matrix[i][j], matrix[n - i - 1][j]);
			}
		}
		// 主对角线翻转
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				swap(matrix[i][j], matrix[j][i]);
			}
		}
	}
};


//59. 螺旋矩阵 II
//法一：从对角线开始，顺时针绕改圈赋值
class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		int index = 1;
		vector<vector<int>> ans(n, vector<int>(n));
		for (int i = 0; i < (n+1) / 2; i++) {
			//上
			for (int j = i; j < n - i; j++) {
				ans[i][j] = index++;
			}
			//右
			for (int j = i + 1; j < n - i; j++) {
				ans[j][n - i - 1] = index++;
			}
			//下
			for (int j = n - i - 2; j >= i; j--) {
				ans[n - i - 1][j] = index++;
			}
			//左
			for (int j = n - i - 2; j > i; j--) {
				ans[j][i] = index++;
			}
		}
		return ans;
	}
};

//官解类似
class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		int num = 1;
		vector<vector<int>> matrix(n, vector<int>(n));
		int left = 0, right = n - 1, top = 0, bottom = n - 1;
		while (left <= right && top <= bottom) {
			for (int column = left; column <= right; column++) {
				matrix[top][column] = num;
				num++;
			}
			for (int row = top + 1; row <= bottom; row++) {
				matrix[row][right] = num;
				num++;
			}

			for (int column = right - 1; column > left; column--) {
				matrix[bottom][column] = num;
				num++;
			}
			for (int row = bottom; row > top; row--) {
				matrix[row][left] = num;
				num++;
			}

			left++;
			right--;
			top++;
			bottom--;
		}
		return matrix;
	}
};


//方法二：模拟
class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		int maxNum = n * n;
		int curNum = 1;
		vector<vector<int>> matrix(n, vector<int>(n));
		int row = 0, column = 0;
		vector<vector<int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };  // 右下左上
		int directionIndex = 0;
		while (curNum <= maxNum) {
			matrix[row][column] = curNum;
			curNum++;
			int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
			if (nextRow < 0 || nextRow >= n || nextColumn < 0 || nextColumn >= n || matrix[nextRow][nextColumn] != 0) {
				directionIndex = (directionIndex + 1) % 4;  // 顺时针旋转至下一个方向
			}
			row = row + directions[directionIndex][0];
			column = column + directions[directionIndex][1];
		}
		return matrix;
	}
};


//方法三：
//撞墙法，一直向前走，当遇到边界或数字不会0时改变方向
class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> ans(n, vector<int>(n,0));
		int i = 0, j = 0, di = 0, dj = 1;
		for (int k = 1; k <= n * n; k++) {
			ans[i][j] = k;
			if ( j + dj == n || i + di == n || j + dj == -1 || ans[(i + di) % n][(j + dj) % n] ) {
				int tmp = di;
				di = dj;
				dj = -tmp;
			}
			i += di;
			j += dj;
		}
		return ans;
	}
};

