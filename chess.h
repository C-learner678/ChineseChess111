#pragma once
#include <vector>

using namespace std;

vector<int> moves(int chessboard[10][9], int x1, int y1);//����һ���ӵ�ȫ���Ϸ���λ
bool isValid(int chessboard[10][9], int x1, int y1, int x2, int y2); //�ж���λ�Ƿ�Ϸ�
bool check(int chessboard[10][9], int turn); //0�췽�Ƿ񽫾��ڷ���1�ڷ��Ƿ񽫾��췽
void move1(int chessboard[10][9], int x1, int y1, int x2, int y2);//����
bool generalFace(int chessboard[10][9]);//��˧����
bool checkAfterMove(int chessboard[10][9], int turn, int x1, int y1, int x2, int y2);//����󼺷��Ƿ�ᱻ�����������жϽ�˧����
vector<int> availableMoves(int chessboard[10][9], int turn); //�ڱ�����������¿�����Щ��
bool isAvailableMoves(vector<int> v, int x1, int y1, int x2, int y2); //�ж��߷��Ƿ��ڿ����߷���
bool canMove(int chessboard[10][9], int turn);//�Ƿ����ӿɶ�
void insert_into_records(int records[300][10][9], int chessboard[10][9], int step);
int repeat(int records[300][10][9], int chessboard[10][9], int step); //�жϾ����Ƿ��ظ����Σ�������ظ�����0���ظ����޽�������1���췽��������2���ڷ���������3
void takeBack(int chessboard[10][9], int records[300][10][9], int step);//����