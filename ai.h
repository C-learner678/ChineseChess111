#pragma once
#include "chess.h"
#include <vector>

vector<int> move2(int chessboard[10][9], int turn); //返回本步棋的走法

vector<int> allMoves(int chessboard[10][9], int turn); //返回所有可走走法

int score(int chessboard[10][9], int turn);//给棋局打分

struct MoveAndScore maxScore(int chessboard[10][9], int turn, int depth, int alpha, int beta); //最大值算法

struct MoveAndScore minScore(int chessboard[10][9], int turn, int depth, int alpha, int beta);//最小值算法