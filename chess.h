#pragma once
#include <vector>

using namespace std;

vector<int> moves(int chessboard[10][9], int x1, int y1);//返回一个子的全部合法走位
bool isValid(int chessboard[10][9], int x1, int y1, int x2, int y2); //判断走位是否合法
bool check(int chessboard[10][9], int turn); //0红方是否将军黑方，1黑方是否将军红方
void move1(int chessboard[10][9], int x1, int y1, int x2, int y2);//走子
bool generalFace(int chessboard[10][9]);//将帅照面
bool checkAfterMove(int chessboard[10][9], int turn, int x1, int y1, int x2, int y2);//走棋后己方是否会被将军，包括判断将帅照面
vector<int> availableMoves(int chessboard[10][9], int turn); //在被将军的情况下可走哪些棋
bool isAvailableMoves(vector<int> v, int x1, int y1, int x2, int y2); //判断走法是否在可行走法内
bool canMove(int chessboard[10][9], int turn);//是否无子可动
void insert_into_records(int records[300][10][9], int chessboard[10][9], int step);
int repeat(int records[300][10][9], int chessboard[10][9], int step); //判断局面是否重复三次，如果不重复返回0，重复且无将军返回1，红方长将返回2，黑方长将返回3
void takeBack(int chessboard[10][9], int records[300][10][9], int step);//悔棋