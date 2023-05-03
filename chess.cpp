#include"chess.h"
#include <vector>

using namespace std;

vector<int> moves(int chessboard[10][9], int x1, int y1) {//返回一个子的全部合法走位
	vector<int> pos = {};
	if (x1 < 0 || x1 > 9 || y1 < 0 || y1 > 8 || chessboard[x1][y1] == 0)
	{
	}
	else if (chessboard[x1][y1] > 0) {//红
		if (chessboard[x1][y1] == 1) { //兵
			if (x1 > 4) { //未过河
				if (chessboard[x1 - 1][y1] <= 0) {//前方没有己方子
					pos.push_back(x1 - 1);
					pos.push_back(y1);
				}
			}
			else if (x1 > 0) {//未下底
				if (chessboard[x1 - 1][y1] <= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1);
				}
				if (y1 > 0) {
					if (chessboard[x1][y1 - 1] <= 0) { //向左
						pos.push_back(x1);
						pos.push_back(y1 - 1);
					}
				}
				if (y1 < 8) {
					if (chessboard[x1][y1 + 1] <= 0) { //向右
						pos.push_back(x1);
						pos.push_back(y1 + 1);
					}
				}
			}
			else {//底线兵
				if (y1 > 0) {
					if (chessboard[x1][y1 - 1] <= 0) { //向左
						pos.push_back(x1);
						pos.push_back(y1 - 1);
					}
				}
				if (y1 < 8) {
					if (chessboard[x1][y1 + 1] <= 0) { //向右
						pos.push_back(x1);
						pos.push_back(y1 + 1);
					}
				}
			}
		}
		else if (chessboard[x1][y1] == 2) {//炮
			if (x1 > 0) { //向上
				int i = 1;
				while (chessboard[x1 - i][y1] == 0) {
					pos.push_back(x1 - i);
					pos.push_back(y1);
					i++;
					if (x1 - i < 0) break;
				}
				if (x1 - i > 0) { //吃子
					i++;
					while (x1 - i >= 0) {
						if (chessboard[x1 - i][y1] > 0) break; //己方子，不吃
						if (chessboard[x1 - i][y1] < 0) {
							pos.push_back(x1 - i);
							pos.push_back(y1);
							break;
						}
						i++;
					}
				}
			}
			if (x1 < 8) { //向下
				int i = 1;
				while (chessboard[x1 + i][y1] == 0) {
					pos.push_back(x1 + i);
					pos.push_back(y1);
					i++;
					if (x1 + i > 9) break;
				}
				if (x1 + i < 9) { //吃子
					i++;
					while (x1 + i <= 9) {
						if (chessboard[x1 + i][y1] > 0) break; //己方子，不吃
						if (chessboard[x1 + i][y1] < 0) {
							pos.push_back(x1 + i);
							pos.push_back(y1);
							break;
						}
						i++;
					}
				}
			}
			if (y1 > 0) { //向左
				int i = 1;
				while (chessboard[x1][y1 - i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 - i);
					i++;
					if (y1 - i < 0) break;
				}
				if (y1 - i > 0) { //吃子
					i++;
					while (y1 - i >= 0) {
						if (chessboard[x1][y1 - i] > 0) break; //己方子，不吃
						if (chessboard[x1][y1 - i] < 0) {
							pos.push_back(x1);
							pos.push_back(y1 - i);
							break;
						}
						i++;
					}
				}
			}
			if (y1 < 9) { //向右
				int i = 1;
				while (chessboard[x1][y1 + i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 + i);
					i++;
					if (y1 + i > 8) break;
				}
				if (y1 + i < 8) { //吃子
					i++;
					while (y1 + i <= 8) {
						if (chessboard[x1][y1 + i] > 0) break; //己方子，不吃
						if (chessboard[x1][y1 + i] < 0) {
							pos.push_back(x1);
							pos.push_back(y1 + i);
							break;
						}
						i++;
					}
				}
			}
		}
		else if (chessboard[x1][y1] == 3) {//车
			if (x1 > 0) { //向上
				int i = 1;
				while (chessboard[x1 - i][y1] == 0) {
					pos.push_back(x1 - i);
					pos.push_back(y1);
					i++;
					if (x1 - i < 0) break;
				}
				if (x1 - i >= 0) { //吃子
					if (chessboard[x1 - i][y1] < 0) {
						pos.push_back(x1 - i);
						pos.push_back(y1);
					}
				}
			}
			if (x1 < 9) { //向下
				int i = 1;
				while (chessboard[x1 + i][y1] == 0) {
					pos.push_back(x1 + i);
					pos.push_back(y1);
					i++;
					if (x1 + i > 9) break;
				}
				if (x1 + i <= 9) {
					if (chessboard[x1 + i][y1] < 0) {
						pos.push_back(x1 + i);
						pos.push_back(y1);
					}
				}
			}
			if (y1 > 0) { //向左
				int i = 1;
				while (chessboard[x1][y1 - i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 - i);
					i++;
					if (y1 - i < 0) break;
				}
				if (y1 - i >= 0) {
					if (chessboard[x1][y1 - i] < 0) {
						pos.push_back(x1);
						pos.push_back(y1 - i);
					}
				}
			}
			if (y1 < 8) { //向右
				int i = 1;
				while (chessboard[x1][y1 + i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 + i);
					i++;
					if (y1 + i > 8) break;
				}
				if (y1 + i <= 8) {
					if (chessboard[x1][y1 + i] < 0) {
						pos.push_back(x1);
						pos.push_back(y1 + i);
					}
				}
			}
		}
		else if (chessboard[x1][y1] == 4) {//马
			if (x1 > 0) {
				if (chessboard[x1 - 1][y1] == 0) {//上方马腿
					if (x1 - 2 >= 0 && x1 - 2 <= 9 && y1 - 1 >= 0 && y1 - 1 <= 8) {
						if (chessboard[x1 - 2][y1 - 1] <= 0) {
							pos.push_back(x1 - 2);
							pos.push_back(y1 - 1);
						}
					}
					if (x1 - 2 >= 0 && x1 - 2 <= 9 && y1 + 1 >= 0 && y1 + 1 <= 8) {
						if (chessboard[x1 - 2][y1 + 1] <= 0) {
							pos.push_back(x1 - 2);
							pos.push_back(y1 + 1);
						}
					}
				}
			}
			if (x1 < 9) {
				if (chessboard[x1 + 1][y1] == 0) {//下方马腿
					if (x1 + 2 >= 0 && x1 + 2 <= 9 && y1 - 1 >= 0 && y1 - 1 <= 8) {
						if (chessboard[x1 + 2][y1 - 1] <= 0) {
							pos.push_back(x1 + 2);
							pos.push_back(y1 - 1);
						}
					}
					if (x1 + 2 >= 0 && x1 + 2 <= 9 && y1 + 1 >= 0 && y1 + 1 <= 8) {
						if (chessboard[x1 + 2][y1 + 1] <= 0) {
							pos.push_back(x1 + 2);
							pos.push_back(y1 + 1);
						}
					}
				}
			}
			if (y1 > 0) {
				if (chessboard[x1][y1 - 1] == 0) {//左方马腿
					if (x1 - 1 >= 0 && x1 - 1 <= 9 && y1 - 2 >= 0 && y1 - 2 <= 8) {
						if (chessboard[x1 - 1][y1 - 2] <= 0) {
							pos.push_back(x1 - 1);
							pos.push_back(y1 - 2);
						}
					}
					if (x1 + 1 >= 0 && x1 + 1 <= 9 && y1 - 2 >= 0 && y1 - 2 <= 8) {
						if (chessboard[x1 + 1][y1 - 2] <= 0) {
							pos.push_back(x1 + 1);
							pos.push_back(y1 - 2);
						}
					}
				}
			}
			if (y1 < 8) {
				if (chessboard[x1][y1 + 1] == 0) {//右方马腿
					if (x1 - 1 >= 0 && x1 - 1 <= 9 && y1 + 2 >= 0 && y1 + 2 <= 8) {
						if (chessboard[x1 - 1][y1 + 2] <= 0) {
							pos.push_back(x1 - 1);
							pos.push_back(y1 + 2);
						}
					}
					if (x1 + 1 >= 0 && x1 + 1 <= 9 && y1 + 2 >= 0 && y1 + 2 <= 8) {
						if (chessboard[x1 + 1][y1 + 2] <= 0) {
							pos.push_back(x1 + 1);
							pos.push_back(y1 + 2);
						}
					}
				}
			}
		}
		else if (chessboard[x1][y1] == 5) { //象
			if (y1 == 0) {
				if (chessboard[x1 - 2][y1 + 2] <= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
				if (chessboard[x1 + 2][y1 + 2] <= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 2 && x1 == 5) {
				if (chessboard[x1 + 2][y1 - 2] <= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 + 2] <= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 2 && x1 == 9) {
				if (chessboard[x1 - 2][y1 - 2] <= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 - 2][y1 + 2] <= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 4 && x1 == 7) {
				if (chessboard[x1 - 2][y1 - 2] <= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 - 2][y1 + 2] <= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
				if (chessboard[x1 + 2][y1 - 2] <= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 + 2] <= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 6 && x1 == 5) {
				if (chessboard[x1 + 2][y1 - 2] <= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 + 2] <= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 6 && x1 == 9) {
				if (chessboard[x1 - 2][y1 - 2] <= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 - 2][y1 + 2] <= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 8) {
				if (chessboard[x1 - 2][y1 - 2] <= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 - 2] <= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
			}
		}
		else if (chessboard[x1][y1] == 6) { //士
			if (x1 == 7 && y1 == 3) {
				if (chessboard[x1 + 1][y1 + 1] <= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 + 1);
				}
			}
			else if (x1 == 9 && y1 == 3) {
				if (chessboard[x1 - 1][y1 + 1] <= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 + 1);
				}
			}
			else if (x1 == 7 && y1 == 5) {
				if (chessboard[x1 + 1][y1 - 1] <= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 - 1);
				}
			}
			else if (x1 == 9 && y1 == 5) {
				if (chessboard[x1 - 1][y1 - 1] <= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 - 1);
				}
			}
			else if (x1 == 8 && y1 == 4) {
				if (chessboard[x1 - 1][y1 - 1] <= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 - 1);
				}
				if (chessboard[x1 + 1][y1 - 1] <= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 - 1);
				}
				if (chessboard[x1 - 1][y1 + 1] <= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 + 1);
				}
				if (chessboard[x1 + 1][y1 + 1] <= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 + 1);
				}
			}
		}
		else if (chessboard[x1][y1] == 7) { //帅
			if (x1 != 7) { //向上
				if (chessboard[x1 - 1][y1] <= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1);
				}
			}
			if (x1 != 9) { //向下
				if (chessboard[x1 + 1][y1] <= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1);
				}
			}
			if (y1 != 3) { //向左
				if (chessboard[x1][y1 - 1] <= 0) {
					pos.push_back(x1);
					pos.push_back(y1 - 1);
				}
			}
			if (y1 != 5) { //向右
				if (chessboard[x1][y1 + 1] <= 0) {
					pos.push_back(x1);
					pos.push_back(y1 + 1);
				}
			}
		}
	}
	else {//黑
		if (chessboard[x1][y1] == -1) { //卒
			if (x1 < 5) { //未过河
				if (chessboard[x1 + 1][y1] >= 0) {//前方没有己方子
					pos.push_back(x1 + 1);
					pos.push_back(y1);
				}
			}
			else if (x1 < 9) {//未下底
				if (chessboard[x1 + 1][y1] >= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1);
				}
				if (y1 > 0) {
					if (chessboard[x1][y1 - 1] >= 0) { //向左
						pos.push_back(x1);
						pos.push_back(y1 - 1);
					}
				}
				if (y1 < 8) {
					if (chessboard[x1][y1 + 1] >= 0) { //向右
						pos.push_back(x1);
						pos.push_back(y1 + 1);
					}
				}
			}
			else {//底线兵
				if (y1 > 0) {
					if (chessboard[x1][y1 - 1] >= 0) { //向左
						pos.push_back(x1);
						pos.push_back(y1 - 1);
					}
				}
				if (y1 < 8) {
					if (chessboard[x1][y1 + 1] >= 0) { //向右
						pos.push_back(x1);
						pos.push_back(y1 + 1);
					}
				}
			}
		}
		else if (chessboard[x1][y1] == -2) {//炮
			if (x1 > 0) { //向上
				int i = 1;
				while (chessboard[x1 - i][y1] == 0) {
					pos.push_back(x1 - i);
					pos.push_back(y1);
					i++;
					if (x1 - i < 0) break;
				}
				if (x1 - i > 0) { //吃子
					i++;
					while (x1 - i >= 0) {
						if (chessboard[x1 - i][y1] < 0) break; //己方子，不吃
						if (chessboard[x1 - i][y1] > 0) {
							pos.push_back(x1 - i);
							pos.push_back(y1);
							break;
						}
						i++;
					}
				}
			}
			if (x1 < 9) { //向下
				int i = 1;
				while (chessboard[x1 + i][y1] == 0) {
					pos.push_back(x1 + i);
					pos.push_back(y1);
					i++;
					if (x1 + i > 9) break;
				}
				if (x1 + i < 9) { //吃子
					i++;
					while (x1 + i <= 9) {
						if (chessboard[x1 + i][y1] < 0) break; //己方子，不吃
						if (chessboard[x1 + i][y1] > 0) {
							pos.push_back(x1 + i);
							pos.push_back(y1);
							break;
						}
						i++;
					}
				}
			}
			if (y1 > 0) { //向左
				int i = 1;
				while (chessboard[x1][y1 - i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 - i);
					i++;
					if (y1 - i < 0) break;
				}
				if (y1 - i > 0) { //吃子
					i++;
					while (y1 - i >= 0) {
						if (chessboard[x1][y1 - i] < 0) break; //己方子，不吃
						if (chessboard[x1][y1 - i] > 0) {
							pos.push_back(x1);
							pos.push_back(y1 - i);
							break;
						}
						i++;
					}
				}
			}
			if (y1 < 9) { //向右
				int i = 1;
				while (chessboard[x1][y1 + i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 + i);
					i++;
					if (y1 + i > 8) break;
				}
				if (y1 + i < 8) { //吃子
					i++;
					while (y1 + i <= 8) {
						if (chessboard[x1][y1 + i] < 0) break; //己方子，不吃
						if (chessboard[x1][y1 + i] > 0) {
							pos.push_back(x1);
							pos.push_back(y1 + i);
							break;
						}
						i++;
					}
				}
			}
		}
		else if (chessboard[x1][y1] == -3) {//车
			if (x1 > 0) { //向上
				int i = 1;
				while (chessboard[x1 - i][y1] == 0) {
					pos.push_back(x1 - i);
					pos.push_back(y1);
					i++;
					if (x1 - i < 0) break;
				}
				if (x1 - i >= 0) { //吃子
					if (chessboard[x1 - i][y1] > 0) {
						pos.push_back(x1 - i);
						pos.push_back(y1);
					}
				}
			}
			if (x1 < 9) { //向下
				int i = 1;
				while (chessboard[x1 + i][y1] == 0) {
					pos.push_back(x1 + i);
					pos.push_back(y1);
					i++;
					if (x1 + i > 9) break;
				}
				if (x1 + i <= 9) {
					if (chessboard[x1 + i][y1] > 0) {
						pos.push_back(x1 + i);
						pos.push_back(y1);
					}
				}
			}
			if (y1 > 0) { //向左
				int i = 1;
				while (chessboard[x1][y1 - i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 - i);
					i++;
					if (y1 - i < 0) break;
				}
				if (y1 - i >= 0) {
					if (chessboard[x1][y1 - i] > 0) {
						pos.push_back(x1);
						pos.push_back(y1 - i);
					}
				}
			}
			if (y1 < 8) { //向右
				int i = 1;
				while (chessboard[x1][y1 + i] == 0) {
					pos.push_back(x1);
					pos.push_back(y1 + i);
					i++;
					if (y1 + i > 8) break;
				}
				if (y1 + i <= 8) {
					if (chessboard[x1][y1 + i] > 0) {
						pos.push_back(x1);
						pos.push_back(y1 + i);
					}
				}
			}
		}
		else if (chessboard[x1][y1] == -4) {//马
			if (x1 > 0) {
				if (chessboard[x1 - 1][y1] == 0) {//上方马腿
					if (x1 - 2 >= 0 && x1 - 2 <= 9 && y1 - 1 >= 0 && y1 - 1 <= 8) {
						if (chessboard[x1 - 2][y1 - 1] >= 0) {
							pos.push_back(x1 - 2);
							pos.push_back(y1 - 1);
						}
					}
					if (x1 - 2 >= 0 && x1 - 2 <= 9 && y1 + 1 >= 0 && y1 + 1 <= 8) {
						if (chessboard[x1 - 2][y1 + 1] >= 0) {
							pos.push_back(x1 - 2);
							pos.push_back(y1 + 1);
						}
					}
				}
			}
			if (x1 < 9) {
				if (chessboard[x1 + 1][y1] == 0) {//下方马腿
					if (x1 + 2 >= 0 && x1 + 2 <= 9 && y1 - 1 >= 0 && y1 - 1 <= 8) {
						if (chessboard[x1 + 2][y1 - 1] >= 0) {
							pos.push_back(x1 + 2);
							pos.push_back(y1 - 1);
						}
					}
					if (x1 + 2 >= 0 && x1 + 2 <= 9 && y1 + 1 >= 0 && y1 + 1 <= 8) {
						if (chessboard[x1 + 2][y1 + 1] >= 0) {
							pos.push_back(x1 + 2);
							pos.push_back(y1 + 1);
						}
					}
				}
			}
			if (y1 > 0) {
				if (chessboard[x1][y1 - 1] == 0) {//左方马腿
					if (x1 - 1 >= 0 && x1 - 1 <= 9 && y1 - 2 >= 0 && y1 - 2 <= 8) {
						if (chessboard[x1 - 1][y1 - 2] >= 0) {
							pos.push_back(x1 - 1);
							pos.push_back(y1 - 2);
						}
					}
					if (x1 + 1 >= 0 && x1 + 1 <= 9 && y1 - 2 >= 0 && y1 - 2 <= 8) {
						if (chessboard[x1 + 1][y1 - 2] >= 0) {
							pos.push_back(x1 + 1);
							pos.push_back(y1 - 2);
						}
					}
				}
			}
			if (y1 < 8) {
				if (chessboard[x1][y1 + 1] == 0) {//右方马腿
					if (x1 - 1 >= 0 && x1 - 1 <= 9 && y1 + 2 >= 0 && y1 + 2 <= 8) {
						if (chessboard[x1 - 1][y1 + 2] >= 0) {
							pos.push_back(x1 - 1);
							pos.push_back(y1 + 2);
						}
					}
					if (x1 + 1 >= 0 && x1 + 1 <= 9 && y1 + 2 >= 0 && y1 + 2 <= 8) {
						if (chessboard[x1 + 1][y1 + 2] >= 0) {
							pos.push_back(x1 + 1);
							pos.push_back(y1 + 2);
						}
					}
				}
			}
		}
		else if (chessboard[x1][y1] == -5) { //象
			if (y1 == 0) {
				if (chessboard[x1 - 2][y1 + 2] >= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
				if (chessboard[x1 + 2][y1 + 2] >= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 2 && x1 == 0) {
				if (chessboard[x1 + 2][y1 - 2] >= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 + 2] >= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 2 && x1 == 4) {
				if (chessboard[x1 - 2][y1 - 2] >= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 - 2][y1 + 2] >= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 4 && x1 == 2) {
				if (chessboard[x1 - 2][y1 - 2] >= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 - 2][y1 + 2] >= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
				if (chessboard[x1 + 2][y1 - 2] >= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 + 2] >= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 6 && x1 == 0) {
				if (chessboard[x1 + 2][y1 - 2] >= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 + 2] >= 0 && chessboard[x1 + 1][y1 + 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 6 && x1 == 4) {
				if (chessboard[x1 - 2][y1 - 2] >= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 - 2][y1 + 2] >= 0 && chessboard[x1 - 1][y1 + 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 + 2);
				}
			}
			else if (y1 == 8) {
				if (chessboard[x1 - 2][y1 - 2] >= 0 && chessboard[x1 - 1][y1 - 1] == 0) {
					pos.push_back(x1 - 2);
					pos.push_back(y1 - 2);
				}
				if (chessboard[x1 + 2][y1 - 2] >= 0 && chessboard[x1 + 1][y1 - 1] == 0) {
					pos.push_back(x1 + 2);
					pos.push_back(y1 - 2);
				}
			}
		}
		else if (chessboard[x1][y1] == -6) { //士
			if (x1 == 0 && y1 == 3) {
				if (chessboard[x1 + 1][y1 + 1] >= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 + 1);
				}
			}
			else if (x1 == 2 && y1 == 3) {
				if (chessboard[x1 - 1][y1 + 1] >= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 + 1);
				}
			}
			else if (x1 == 0 && y1 == 5) {
				if (chessboard[x1 + 1][y1 - 1] >= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 - 1);
				}
			}
			else if (x1 == 2 && y1 == 5) {
				if (chessboard[x1 - 1][y1 - 1] >= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 - 1);
				}
			}
			else if (x1 == 1 && y1 == 4) {
				if (chessboard[x1 - 1][y1 - 1] >= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 - 1);
				}
				if (chessboard[x1 + 1][y1 - 1] >= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 - 1);
				}
				if (chessboard[x1 - 1][y1 + 1] >= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1 + 1);
				}
				if (chessboard[x1 + 1][y1 + 1] >= 0) {
					pos.push_back(x1 + 1);
					pos.push_back(y1 + 1);
				}
			}
		}
		else if (chessboard[x1][y1] == -7) { //将
			if (x1 != 0) {
				if (chessboard[x1 - 1][y1] >= 0) {
					pos.push_back(x1 - 1);
					pos.push_back(y1);
				}
			}
			if (x1 != 2) {
				if (chessboard[x1 + 1][y1] >= 0) {				
					pos.push_back(x1 + 1);
					pos.push_back(y1);
				}
			}
			if (y1 != 3) {
				if (chessboard[x1][y1 - 1] >= 0) {
					pos.push_back(x1);
					pos.push_back(y1 - 1);
				}
			}
			if (y1 != 5) {
				if (chessboard[x1][y1 + 1] >= 0) {
					pos.push_back(x1);
					pos.push_back(y1 + 1);
				}
			}
		}
	}
	return pos;
}

bool isValid(int chessboard[10][9], int x1, int y1, int x2, int y2) {//判断走位是否合法
	vector<int> v = moves(chessboard, x1, y1);
	for (int i = 0; i < v.size(); i += 2) {
		if (x2 == v[i]) {
			if (y2 == v[i + 1]) {
				return true;
			}
		}
	}
	return false;
}

bool check(int chessboard[10][9], int turn) {//0红方是否将军黑方，1黑方是否将军红方
	//把将/帅视为车、马、炮、兵（卒），看能不能吃到对方的车、马、炮、兵（卒）
	int x3 = 0;//将/帅坐标
	int y3 = 0;
	if (turn == 1) {
		int b = false;
		for (int i = 9; i > 6; i--) {
			for (int j = 3; j < 6; j++) {
				if (chessboard[i][j] == 7) {
					x3 = i;
					y3 = j;
					b = true;
					break;
				}
			}
			if (b)
				break;
		}
		int i;
		//判断是否被过河卒攻击
		if (chessboard[x3 - 1][y3] == -1 || chessboard[x3][y3 - 1] == -1 || chessboard[x3][y3 + 1] == -1) {
			return true;
		}
		//判断是否被马攻击
		//左上马
		if (chessboard[x3 - 1][y3 - 1] == 0) {
			if (chessboard[x3 - 1][y3 - 2] == -4 || chessboard[x3 - 2][y3 - 1] == -4) {
				return true;
			}
		}
		//右上马
		if (chessboard[x3 - 1][y3 + 1] == 0) {
			if (chessboard[x3 - 1][y3 + 2] == -4 || chessboard[x3 - 2][y3 + 1] == -4) {
				return true;
			}
		}
		//左下马
		if (x3 != 9) {
			if (chessboard[x3 + 1][y3 - 1] == 0) {
				if (chessboard[x3 + 1][y3 - 2] == -4) {
					return true;
				}
				if (x3 == 7) {
					if (chessboard[x3 + 2][y3 - 1] == -4) {
						return true;
					}
				}
			}
		}
		//右下马
		if (x3 != 9) {
			if (chessboard[x3 + 1][y3 + 1] == 0) {
				if (chessboard[x3 + 1][y3 + 2] == -4) {
					return true;
				}
				if (x3 == 7) {
					if (chessboard[x3 + 2][y3 + 1] == -4) {
						return true;
					}
				}
			}
		}
		//判断是否被车攻击
		//上方
		i = 1;
		while (chessboard[x3 - i][y3] == 0) {
			i++;
			if (x3 - i < 0) break;
		}
		if (x3 - i >= 0) { //吃子
			if (chessboard[x3 - i][y3] == -3) {
				return true;
			}
		}
		//下方
		if (x3 != 9) {
			i = 1;
			while (chessboard[x3 + i][y3] == 0) {
				i++;
				if (x3 + i > 9) break;
			}
			if (x3 + i <= 9) {
				if (chessboard[x3 + i][y3] == -3) {
					return true;
				}
			}
		}
		//左方
		i = 1;
		while (chessboard[x3][y3 - i] == 0) {
			i++;
			if (y3 - i < 0) break;
		}
		if (y3 - i >= 0) {
			if (chessboard[x3][y3 - i] == -3) {
				return true;
			}
		}
		//右方
		i = 1;
		while (chessboard[x3][y3 + i] == 0) {
			i++;
			if (y3 + i > 8) break;
		}
		if (y3 + i <= 8) {
			if (chessboard[x3][y3 + i] == -3) {
				return true;
			}
		}
		//判断是否被炮攻击
		//上方
		i = 1;
		while (chessboard[x3 - i][y3] == 0) {
			i++;
			if (x3 - i < 0) break;
		}
		if (x3 - i > 0) {
			i++;
			while (x3 - i >= 0) {
				if (chessboard[x3 - i][y3] == -2) {
					return true;
				}
				else if (chessboard[x3 - i][y3] != 0) {
					break;
				}
				i++;
			}
		}
		//左方
		i = 1;
		while (chessboard[x3][y3 - i] == 0) {
			i++;
			if (y3 - i < 0) break;
		}
		if (y3 - i > 0) {
			i++;
			while (y3 - i >= 0) {
				if (chessboard[x3][y3 - i] == -2) {
					return true;
				}
				else if (chessboard[x3][y3 - i] != 0) {
					break;
				}
				i++;
			}
		}
		//右方
		i = 1;
		while (chessboard[x3][y3 + i] == 0) {
			i++;
			if (y3 + i > 8) break;
		}
		if (y3 + i < 8) { //吃子
			i++;
			while (y3 + i <= 8) {
				if (chessboard[x3][y3 + i] == -2) {
					return true;
				}
				else if (chessboard[x3][y3 + i] != 0) {
					break;
				}
				i++;
			}
		}
		//下方
		if (x3 == 7) {
			if (chessboard[x3 + 2][y3] == -2 && chessboard[x3 + 1][y3] != 0) {
				return true;
			}
		}
	}
	else {
		int b = false;
		for (int i = 0; i < 3; i++) {
			for (int j = 3; j < 6; j++) {
				if (chessboard[i][j] == -7) {
					x3 = i;
					y3 = j;
					b = true;
					break;
				}
			}
			if (b)
				break;
		}
		int i;
		//判断是否被过河卒攻击
		if (chessboard[x3 + 1][y3] == 1 || chessboard[x3][y3 - 1] == 1 || chessboard[x3][y3 + 1] == 1) {
			return true;
		}
		//判断是否被马攻击
		//左下马
		if (chessboard[x3 + 1][y3 - 1] == 0) {
			if (chessboard[x3 + 1][y3 - 2] == 4 || chessboard[x3 + 2][y3 - 1] == 4) {
				return true;
			}
		}
		//右下马
		if (chessboard[x3 + 1][y3 + 1] == 0) {
			if (chessboard[x3 + 1][y3 + 2] == 4 || chessboard[x3 + 2][y3 + 1] == 4) {
				return true;
			}
		}
		//左上马
		if (x3 != 0) {
			if (chessboard[x3 - 1][y3 - 1] == 0) {
				if (chessboard[x3 - 1][y3 - 2] == 4) {
					return true;
				}
				if (x3 == 2) {
					if (chessboard[x3 - 2][y3 - 1] == 4) {
						return true;
					}
				}
			}
		}
		//右上马
		if (x3 != 0) {
			if (chessboard[x3 - 1][y3 + 1] == 0) {
				if (chessboard[x3 - 1][y3 + 2] == 4) {
					return true;
				}
				if (x3 == 2) {
					if (chessboard[x3 - 2][y3 + 1] == 4) {
						return true;
					}
				}
			}
		}
		//判断是否被车攻击
		//上方
		if (x3 != 0) {
			i = 1;
			while (chessboard[x3 - i][y3] == 0) {
				i++;
				if (x3 - i < 0) break;
			}
			if (x3 - i >= 0) { 
				if (chessboard[x3 - i][y3] == 3) {
					return true;
				}
			}
		}
		//下方
		i = 1;
		while (chessboard[x3 + i][y3] == 0) {
			i++;
			if (x3 + i > 9) break;
		}
		if (x3 + i <= 9) {
			if (chessboard[x3 + i][y3] == 3) {
				return true;
			}
		}
		//左方
		i = 1;
		while (chessboard[x3][y3 - i] == 0) {
			i++;
			if (y3 - i < 0) break;
		}
		if (y3 - i >= 0) {
			if (chessboard[x3][y3 - i] == 3) {
				return true;
			}
		}
		//右方
		i = 1;
		while (chessboard[x3][y3 + i] == 0) {
			i++;
			if (y3 + i > 8) break;
		}
		if (y3 + i <= 8) {
			if (chessboard[x3][y3 + i] == 3) {
				return true;
			}
		}
		//判断是否被炮攻击
		//下方
		i = 1;
		while (chessboard[x3 + i][y3] == 0) {
			i++;
			if (x3 + i > 9) break;
		}
		if (x3 + i < 9) { 
			i++;
			while (x3 + i <= 9) {
				if (chessboard[x3 + i][y3] == 2) {
					return true;
				}
				else if (chessboard[x3 + i][y3] != 0) {
					break;
				}
				i++;
			}
		}
		//左方
		i = 1;
		while (chessboard[x3][y3 - i] == 0) {
			i++;
			if (y3 - i < 0) break;
		}
		if (y3 - i > 0) {
			i++;
			while (y3 - i >= 0) {
				if (chessboard[x3][y3 - i] == 2) {
					return true;
				}
				else if (chessboard[x3][y3 - i] != 0) {
					break;
				}
				i++;
			}
		}
		//右方
		i = 1;
		while (chessboard[x3][y3 + i] == 0) {
			i++;
			if (y3 + i > 8) break;
		}
		if (y3 + i < 8) { //吃子
			i++;
			while (y3 + i <= 8) {
				if (chessboard[x3][y3 + i] == 2) {
					return true;
				}
				else if (chessboard[x3][y3 + i] != 0) {
					break;
				}
				i++;
			}
		}
		//上方
		if (x3 == 2) {
			if (chessboard[x3 - 2][y3] == 2 && chessboard[x3 - 1][y3] != 0) {
				return true;
			}
		}
	}
	return false;
}

void move1(int chessboard[10][9], int x1, int y1, int x2, int y2) {//走子
	int temp = chessboard[x1][y1];
	chessboard[x1][y1] = 0;
	chessboard[x2][y2] = temp;
}

bool generalFace(int chessboard[10][9]) {//将帅照面
	for (int i = 0; i < 3; i++) {
		for (int j = 3; j < 6; j++) {
			if (chessboard[i][j] == -7) {//将
				for (int k = i + 1; k < 10; k++) {
					if (chessboard[k][j] != 0) {
						if (chessboard[k][j] == 7) {
							return true;//照面
						}
						else {
							return false;//有子
						}
					}
				}
				return false;//该列除将以外无子
			}
		}
	}
	return false;
}

bool checkAfterMove(int chessboard[10][9], int turn, int x1, int y1, int x2, int y2) { //走棋后己方是否会被将军，包括判断将帅照面
	int temp_chessboard[10][9];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			temp_chessboard[i][j] = chessboard[i][j];
		}
	}
	move1(temp_chessboard, x1, y1, x2, y2);
	if (check(temp_chessboard, 1 - turn) || generalFace(temp_chessboard)) {
		return true;
	}
	else {
		return false;
	}
}

vector<int> availableMoves(int chessboard[10][9], int turn) { //在被将军的情况下可走哪些棋
	vector<int> result = {};
	if (!check(chessboard, 1 - turn)) {
	}
	else
	{
		if (turn == 0) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9; j++) {
					if (chessboard[i][j] > 0) { //红方子
						vector<int> v = {};
						v = moves(chessboard, i, j); //全部可走
						for (int k = 0; k < v.size(); k += 2) {
							if (!checkAfterMove(chessboard, turn, i, j, v[k], v[k + 1])) { //走了以后可以避免被将军
								result.push_back(i);
								result.push_back(j);
								result.push_back(v[k]);
								result.push_back(v[k + 1]);
							}
						}
					}
				}
			}
		}
		else {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9; j++) {
					if (chessboard[i][j] < 0) { //黑方子
						vector<int> v = {};
						v = moves(chessboard, i, j); //全部可走
						for (int k = 0; k < v.size(); k += 2) {
							if (!checkAfterMove(chessboard, turn, i, j, v[k], v[k + 1])) { //走了以后可以避免被将军
								result.push_back(i);
								result.push_back(j);
								result.push_back(v[k]);
								result.push_back(v[k + 1]);
							}
						}
					}
				}
			}
		}
	}
	return result;
}

bool isAvailableMoves(vector<int> v, int x1, int y1, int x2, int y2) { //判断走法是否在可行走法内
	for (int i = 0; i < v.size(); i += 4) {
		if (v[i] == x1 && v[i + 1] == y1 && v[i + 2] == x2 && v[i + 3] == y2) {
			return true;
		}
	}
	return false;
}

bool canMove(int chessboard[10][9], int turn) { //是否无子可动
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (turn == 0) {
				if (chessboard[i][j] > 0) {
					vector<int> v = {};
					v = moves(chessboard, i, j);
					if (v.size() != 0) {
						for (int k = 0; k < v.size(); k += 2) {
							if (!checkAfterMove(chessboard, turn, i, j, v[k], v[k + 1])) {
								return true;
							}
						}
					}
				}
			}
			else {
				if (chessboard[i][j] < 0) {
					vector<int> v = {};
					v = moves(chessboard, i, j);
					if (v.size() != 0) {
						for (int k = 0; k < v.size(); k += 2) {
							if (!checkAfterMove(chessboard, turn, i, j, v[k], v[k + 1])) {
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void insert_into_records(int records[300][10][9], int chessboard[10][9], int step) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			records[step][i][j] = chessboard[i][j];
		}
	}
}

int repeat(int records[300][10][9], int chessboard[10][9], int step) { //判断局面是否重复三次
	if (step < 3) return 0;
	int repeats = 0;
	int out = 0;
	int i = 0;
	for (int k = 0; k < step; k++) {
		for (i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				if (records[k][i][j] != chessboard[i][j]) {
					out = 1;
					break;
				}
			}
			if (out == 1) {
				out = 0;
				break;
			}
		}
		if (i == 10) repeats++;
	}
	if (repeats >= 2) {
		if (check(chessboard, 0)) {
			return 2;//红方长将
		}
		else if (check(chessboard, 1)) {
			return 3;//黑方长将
		}
		else {
			return 1;//无长将，和棋
		}
		return true;
	}
	else {
		return 0;
	}
}

void takeBack(int chessboard[10][9], int records[300][10][9], int step) {//悔棋
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			chessboard[i][j] = records[step][i][j];
		}
	}
}