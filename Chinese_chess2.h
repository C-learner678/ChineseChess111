#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chinese_chess2.h"

class Chinese_chess2 : public QMainWindow
{
    Q_OBJECT

public:
    Chinese_chess2(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *e);
	void keyPressEvent(QKeyEvent *event);

private:
    Ui::Chinese_chess2Class ui;
	int mode = 0;//ģʽ 0δѡ�� 1˫�˶�ս 2��Һ���Ժ� 3���Ժ���Һ�

	int chessboard[10][9];
	int records[300][10][9] = {};
	int step;
	int turn;//�췽���� 
	int moving;//0ѡ���� 1�����һ��Ҫ�ߵ��� 2��Ϸ����
	int x1, y1;//����
	int x2, y2;
	int redCheck;//�췽�����ڷ�
	int blackCheck;//�ڷ������췽
};
