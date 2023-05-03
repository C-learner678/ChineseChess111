#include "ai.h"
#include "chess.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static int count1 = 0;

struct MoveAndScore { //记录走法及对应的棋盘分数
	int x1;
	int y1;
	int x2;
	int y2;
	int score;
};

vector<int> move2(int chessboard[10][9], int turn) { //返回本步棋的走法
	vector<int> move = { 0,0,0,0 };
	int temp_chessboard[10][9];//复制棋盘
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			temp_chessboard[i][j] = chessboard[i][j];
		}
	}
	struct MoveAndScore result;
	result = maxScore(temp_chessboard, turn, 1, 99999, -99999);
	move[0] = result.x1;
	move[1] = result.y1;
	move[2] = result.x2;
	move[3] = result.y2;
	count1++;
	//
	return move;
}

/*
	//生成随机走法
	vector<int> results = allMoves(chessboard, turn);
	int num = results.size() / 4;
	unsigned seed;
	seed = time(0);
	srand(seed);
	int r = rand() % num;
	move[0] = results[r * 4];
	move[1] = results[r * 4 + 1];
	move[2] = results[r * 4 + 2];
	move[3] = results[r * 4 + 3];
*/

vector<int> allMoves(int chessboard[10][9], int turn) {//返回所有可走走法（其实与availableMoves()函数基本相同）
	vector<int> result = {};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (turn == 0) {//红方
				if (chessboard[i][j] > 0) {
					vector<int> v = moves(chessboard, i, j);
					for (int k = 0; k < v.size(); k += 2) {
						if (!checkAfterMove(chessboard, turn, i, j, v[k], v[k + 1])) {
							result.push_back(i);
							result.push_back(j);
							result.push_back(v[k]);
							result.push_back(v[k + 1]);
						}
					}
				}
			}
			else {//黑方
				if (chessboard[i][j] < 0) {
					vector<int> v = moves(chessboard, i, j);
					for (int k = 0; k < v.size(); k += 2) {
						if (!checkAfterMove(chessboard, turn, i, j, v[k], v[k + 1])) {
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
	return result;
}

int score(int chessboard[10][9], int turn) {//给棋局打分
	int score = 0;
	for(int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (chessboard[i][j] > 0) {
				if (chessboard[i][j] == 1) {//兵
					if (i > 4) {
						score += 10;
					}
					else {
						score += 20;
					}
				}
				else if (chessboard[i][j] == 2) {//炮
					score += 45;
				}
				else if (chessboard[i][j] == 3) {//车
					score += 90;
				}
				else if (chessboard[i][j] == 4) {//马
					score += 40;
				}
				else if (chessboard[i][j] == 5) {//相
					score += 20;
				}
				else if (chessboard[i][j] == 6) {//士
					score += 20;
				}
			}
			else if (chessboard[i][j] < 0) {
				if (chessboard[i][j] == -1) {
					if (i < 6) {
						score -= 10;
					}
					else {
						score -= 20;
					}
				}
				else if (chessboard[i][j] == -2) {
					score -= 45;
				}
				else if (chessboard[i][j] == -3) {
					score -= 90;
				}
				else if (chessboard[i][j] == -4) {
					score -= 40;
				}
				else if (chessboard[i][j] == -5) {
					score -= 20;
				}
				else if (chessboard[i][j] == -6) {
					score -= 20;
				}
			}
		}
	}
	if (turn == 1) { //黑方
		score = -score;
	}
	return score;
}

struct MoveAndScore maxScore(int chessboard[10][9], int turn, int depth, int alpha, int beta) {//最大值算法（奇数层，我方走子）
	vector<int> results = {  };
	results = allMoves(chessboard, turn);
	int num = results.size() / 4;
	int sc = -99999;
	int no = 0;//选择第no个走法
	struct MoveAndScore result;
	int temp_beta = sc;
	if (num != 0) {//有子可走（未被将死或无子可动）
		for (int i = 0; i < num * 4; i += 4) {
			//用于还原棋盘
			int temp_x2 = results[i + 2];
			int temp_y2 = results[i + 3];
			int before = chessboard[temp_x2][temp_y2];
			//模拟移动后的局面
			move1(chessboard, results[i], results[i + 1], results[i + 2], results[i + 3]);
			struct MoveAndScore temp;
			temp = minScore(chessboard, turn, depth + 1, alpha, temp_beta);
			if (sc < temp.score) {
				sc = temp.score;
				no = i / 4;
				temp_beta = sc;
				//剪枝
				if (sc > alpha) {
					move1(chessboard, results[i + 2], results[i + 3], results[i], results[i + 1]);
					chessboard[temp_x2][temp_y2] = before;
					break;
				}
			}
			//还原
			move1(chessboard, results[i + 2], results[i + 3], results[i], results[i + 1]);
			chessboard[temp_x2][temp_y2] = before;
		}
		result.score = sc;
		result.x1 = results[no * 4];
		result.y1 = results[no * 4 + 1];
		result.x2 = results[no * 4 + 2];
		result.y2 = results[no * 4 + 3];
	}
	else {//无子可走，已被将死或无子可动，不再递归
		result.score = -99999;
		result.x1 = -1;
		result.y1 = -1;
		result.x2 = -1;
		result.y2 = -1;
	}
	return result;
}

struct MoveAndScore minScore(int chessboard[10][9], int turn, int depth, int alpha, int beta) {//最小值算法（偶数层，对方走子）
	int max_depth = 4;//最大层数，为偶数
	vector<int> results = {  };
	results = allMoves(chessboard, 1 - turn);
	int num = results.size() / 4;
	int sc = 99999;
	int no = 0;//选择第no个走法
	struct MoveAndScore result;
	if (depth < max_depth) {//未到最大层，递归
		if (num != 0) {//有子可走（未被将死或无子可动）
			int temp_alpha = sc;
			for (int i = 0; i < num * 4; i += 4) {
				//用于还原棋盘
				int temp_x2 = results[i + 2];
				int temp_y2 = results[i + 3];
				int before = chessboard[temp_x2][temp_y2];
				//模拟移动后的局面
				move1(chessboard, results[i], results[i + 1], results[i + 2], results[i + 3]);
				struct MoveAndScore temp;
				temp = maxScore(chessboard, turn, depth + 1, temp_alpha, beta);
				if (sc > temp.score) {
					sc = temp.score;
					no = i / 4;
					temp_alpha = sc;
					//剪枝
					if (sc < beta) {
						move1(chessboard, results[i + 2], results[i + 3], results[i], results[i + 1]);
						chessboard[temp_x2][temp_y2] = before;
						break;
					}
				}
				//还原
				move1(chessboard, results[i + 2], results[i + 3], results[i], results[i + 1]);
				chessboard[temp_x2][temp_y2] = before;
			}
			result.score = sc;
			result.x1 = results[no * 4];
			result.y1 = results[no * 4 + 1];
			result.x2 = results[no * 4 + 2];
			result.y2 = results[no * 4 + 3];
		}
		else {//无子可走，已被将死或无子可动，不再递归
			result.score = 99999;
			result.x1 = -1;
			result.y1 = -1;
			result.x2 = -1;
			result.y2 = -1;
		}
		return result;
	}
	else {//已到最深层，根据棋局算分（一定是偶数层）
		if (num != 0) {//有子可走（未被将死或无子可动）
			for (int i = 0; i < num * 4; i += 4) {
				//用于还原棋盘
				int temp_x2 = results[i + 2];
				int temp_y2 = results[i + 3];
				int before = chessboard[temp_x2][temp_y2];
				//模拟移动后的局面
				move1(chessboard, results[i], results[i + 1], results[i + 2], results[i + 3]);
				struct MoveAndScore temp;
				temp.score = score(chessboard, turn);//打分
				count1++;
				if (sc > temp.score) {
					sc = temp.score;
					no = i / 4;
					//剪枝
					if (sc < beta) {
						move1(chessboard, results[i + 2], results[i + 3], results[i], results[i + 1]);
						chessboard[temp_x2][temp_y2] = before;
						break;
					}
				}
				//还原
				move1(chessboard, results[i + 2], results[i + 3], results[i], results[i + 1]);
				chessboard[temp_x2][temp_y2] = before;
			}
			result.score = sc;
			result.x1 = results[no * 4];
			result.y1 = results[no * 4 + 1];
			result.x2 = results[no * 4 + 2];
			result.y2 = results[no * 4 + 3];
		}
		else {//无子可走，已被将死或无子可动
			result.score = 99999;
			result.x1 = -1;
			result.y1 = -1;
			result.x2 = -1;
			result.y2 = -1;
		}
		return result;
	}
}
