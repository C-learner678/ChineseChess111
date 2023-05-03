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
	int mode = 0;//模式 0未选择 1双人对战 2玩家红电脑黑 3电脑红玩家黑

	int chessboard[10][9];
	int records[300][10][9] = {};
	int step;
	int turn;//红方先行 
	int moving;//0选择子 1点击下一步要走到哪 2游戏结束
	int x1, y1;//坐标
	int x2, y2;
	int redCheck;//红方将军黑方
	int blackCheck;//黑方将军红方
};
