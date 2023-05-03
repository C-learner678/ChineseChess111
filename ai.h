#pragma once
#include "chess.h"
#include <vector>

vector<int> move2(int chessboard[10][9], int turn); //���ر�������߷�

vector<int> allMoves(int chessboard[10][9], int turn); //�������п����߷�

int score(int chessboard[10][9], int turn);//����ִ��

struct MoveAndScore maxScore(int chessboard[10][9], int turn, int depth, int alpha, int beta); //���ֵ�㷨

struct MoveAndScore minScore(int chessboard[10][9], int turn, int depth, int alpha, int beta);//��Сֵ�㷨