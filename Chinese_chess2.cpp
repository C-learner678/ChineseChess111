#pragma execution_character_set("utf-8") //中文编码（必须）

#include "Chinese_chess2.h"
#include "chess.h"
#include "ai.h"
#include <QPainter> 
#include <QMouseEvent>
#include <QMessageBox>
#include <vector>

using namespace std;
Chinese_chess2::Chinese_chess2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	/*
	int chessboard[10][9] = {
		{-3,-4,-5,-6,-7,-6,-5,-4,-3},
		{0,0,0,0,0,0,0,0,0},
		{0,-2,0,0,0,0,0,-2,0},
		{-1,0,-1,0,-1,0,-1,0,-1},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{1,0,1,0,1,0,1,0,1},
		{0,2,0,0,0,0,0,2,0},
		{0,0,0,0,0,0,0,0,0},
		{3,4,5,6,7,6,5,4,3},
	};
	*/
	int temp_chessboard[10][9] = {
		{-3,-4,-5,-6,-7,-6,-5,-4,-3},
		{0,0,0,0,0,0,0,0,0},
		{0,-2,0,0,0,0,0,-2,0},
		{-1,0,-1,0,-1,0,-1,0,-1},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{1,0,1,0,1,0,1,0,1},
		{0,2,0,0,0,0,0,2,0},
		{0,0,0,0,0,0,0,0,0},
		{3,4,5,6,7,6,5,4,3},
	};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			chessboard[i][j] = temp_chessboard[i][j];
		}
	}
	for (int k = 0; k < 300; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				chessboard[i][j] = temp_chessboard[i][j];
			}
		}
	}
	turn = 0;//红方先行 
	moving = 0;//0选择子 1点击下一步要走到哪 2游戏结束
	x1 = 0;//坐标
	y1 = 0;
	x2 = 0;
	y2 = 0;
	redCheck = 0;//红方将军黑方
	blackCheck = 0;//黑方将军红方
	step = 0;
	insert_into_records(records, chessboard, step);
	step++;
	statusBar()->showMessage(tr("点击屏幕开始"));

	mode = 0;//模式 0未选择 1双人对战 2玩家红电脑黑 3电脑红玩家黑
}


void Chinese_chess2::paintEvent(QPaintEvent *event)

{
	QPainter paint(this);
	QPen pen;  //默认画笔
	QPointF point;
	//绘制棋盘
	pen.setWidth(2);//绘制边框
	paint.setPen(pen);
	paint.drawLine(50, 50, 450, 50);
	paint.drawLine(50, 50, 50, 500);
	paint.drawLine(450, 50, 450, 500);
	paint.drawLine(50, 500, 450, 500);
	pen.setWidth(1);//其他线条
	paint.setPen(pen);
	for (int i = 0; i < 8; i++) {
		paint.drawLine(50, 100 + i * 50, 450, 100 + i * 50);
	}
	for (int i = 0; i < 7; i++) {
		paint.drawLine(100 + i * 50, 50, 100 + i * 50, 250);
		paint.drawLine(100 + i * 50, 300, 100 + i * 50, 500);
	}
	paint.drawLine(200, 50, 300, 150);
	paint.drawLine(300, 50, 200, 150);
	paint.drawLine(200, 400, 300, 500);
	paint.drawLine(300, 400, 200, 500);
	point.setX(120);
	point.setY(285);
	paint.setFont(QFont("Arial", 15));
	paint.drawText(point, "楚河                 汉界");
	//绘制棋子
	paint.setBrush(QColor(222, 211, 140));
	paint.setFont(QFont("Arial", 12));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (chessboard[i][j] != 0) {
				paint.setPen(Qt::black);
				if (mode != 3) {
					paint.drawEllipse(j * 50 + 30, i * 50 + 30, 40, 40);
					point.setX(j * 50 + 38);
					point.setY(i * 50 + 58);
				}
				else {//棋盘上下颠倒
					paint.drawEllipse(j * 50 + 30, (9 - i) * 50 + 30, 40, 40);
					point.setX(j * 50 + 38);
					point.setY((9 - i) * 50 + 58);
				}
				if (chessboard[i][j] > 0) {
					paint.setPen(Qt::red);
					if (chessboard[i][j] == 1) {
						paint.drawText(point, "兵");
					}
					else if (chessboard[i][j] == 2) {
						paint.drawText(point, "砲");
					}
					else if (chessboard[i][j] == 3) {
						paint.drawText(point, "车");
					}
					else if (chessboard[i][j] == 4) {
						paint.drawText(point, "马");
					}
					else if (chessboard[i][j] == 5) {
						paint.drawText(point, "相");
					}
					else if (chessboard[i][j] == 6) {
						paint.drawText(point, "仕");
					}
					else if (chessboard[i][j] == 7) {
						paint.drawText(point, "帥");
					}
				}
				else {
					paint.setPen(Qt::black);
					if (chessboard[i][j] == -1) {
						paint.drawText(point, "卒");
					}
					else if (chessboard[i][j] == -2) {
						paint.drawText(point, "炮");
					}
					else if (chessboard[i][j] == -3) {
						paint.drawText(point, "車");
					}
					else if (chessboard[i][j] == -4) {
						paint.drawText(point, "馬");
					}
					else if (chessboard[i][j] == -5) {
						paint.drawText(point, "象");
					}
					else if (chessboard[i][j] == -6) {
						paint.drawText(point, "士");
					}
					else if (chessboard[i][j] == -7) {
						paint.drawText(point, "将");
					}
				}
			}
		}
	}
}


void Chinese_chess2::mousePressEvent(QMouseEvent *e)
{
	QMessageBox::StandardButton rb;
	bool canmove = false;
	if (e->button() == Qt::LeftButton) //左键
	{
		if (mode == 0) {
			rb = QMessageBox::information(NULL, "请选择", "您是否要开始双人对战？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if (rb == QMessageBox::Yes)
			{
				mode = 1;
				statusBar()->showMessage(tr("游戏开始！"));
			}
			else {
				rb = QMessageBox::information(NULL, "请选择", "您是否选择执红方？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				if (rb == QMessageBox::Yes)
				{
					mode = 2;
					turn = 0;
					statusBar()->showMessage(tr("游戏开始！"));
				}
				else {
					mode = 3;//电脑红方，此时电脑先走一步棋
					turn = 0;
					statusBar()->showMessage(tr("游戏开始！"));
					repaint();//重绘棋盘
					vector<int> v = move2(chessboard, turn);//电脑走棋
					x1 = v[0];
					y1 = v[1];
					x2 = v[2];
					y2 = v[3];
					move1(chessboard, x1, y1, x2, y2);
					repaint();//重绘棋盘
					insert_into_records(records, chessboard, step);
					step++;
					statusBar()->showMessage(tr("已走子：") + QString::number(x2) + "," + QString::number(y2) + tr("，现在轮到黑方"));
					turn = 1;
				}
			}
		}
		else {
			int clickX = e->x();
			int clickY = e->y();
			int x = 0;
			int y = 0;
			if (clickX > 25 && clickX < 475 && clickY > 25 && clickY < 525) {//在棋盘范围内
				y = (clickX - 25) / 50;
				x = (clickY - 25) / 50;
				if (mode == 3) {//棋盘上下颠倒
					x = 9 - x;
				}
				if (moving == 0) {//选择子
					if (turn == 0) {//红
						if (chessboard[x][y] > 0) {
							moving = 1;
							statusBar()->showMessage(tr("已选中：") + QString::number(x) + "," + QString::number(y) + tr("（右键取消）"));
							x1 = x;
							y1 = y;
						}
					}
					else if (turn == 1) {//黑
						if (chessboard[x][y] < 0) {
							moving = 1;
							statusBar()->showMessage(tr("已选中：") + QString::number(x) + "," + QString::number(y) + tr("（右键取消）"));
							x1 = x;
							y1 = y;
						}
					}
				}
				else if (moving = 1) {//走子
					if (turn == 0) {//红
						if (blackCheck == 0) {//被将军
							if (isValid(chessboard, x1, y1, x, y) && !checkAfterMove(chessboard, turn, x1, y1, x, y)) {
								canmove = true;
							}
						}
						else {
							vector<int> v = availableMoves(chessboard, turn);
							if (isAvailableMoves(v, x1, y1, x, y)) {
								canmove = true;
								blackCheck = 0;
							}
						}
					}
					else if (turn == 1) {//黑
						if (redCheck == 0) {
							if (isValid(chessboard, x1, y1, x, y) && !checkAfterMove(chessboard, turn, x1, y1, x, y)) {
								canmove = true;
							}
						}
						else {
							vector<int> v = availableMoves(chessboard, turn);
							if (isAvailableMoves(v, x1, y1, x, y)) {
								canmove = true;
								redCheck = 0;
							}
						}
					}
					if (canmove) {//走动
						moving = 0;
						x2 = x;
						y2 = y;
						move1(chessboard, x1, y1, x2, y2);
						insert_into_records(records, chessboard, step);
						if (turn == 1) {//黑方
							statusBar()->showMessage(tr("已走子：") + QString::number(x2) + "," + QString::number(y2) + tr("，现在轮到红方"));
						}
						else {//红方
							statusBar()->showMessage(tr("已走子：") + QString::number(x2) + "," + QString::number(y2) + tr("，现在轮到黑方"));
						}
						repaint();//重绘棋盘
						int temp = repeat(records, chessboard, step);
						if (temp > 0) {//重复三次，如果无将军为和棋，如果一方长将则另一方胜
							if (temp == 1) {
								statusBar()->showMessage(tr("局面三次重复，和棋！（右键重新开始）"));
							}
							else if (temp == 2) {
								statusBar()->showMessage(tr("红方长将，黑方胜！（右键重新开始）"));
							}
							else {
								statusBar()->showMessage(tr("黑方长将，红方胜！（右键重新开始）"));
							}
							moving = 2;
						}
						else {
							if (check(chessboard, turn)) {
								if (turn == 1) {
									blackCheck = 1;
									statusBar()->showMessage(tr("黑方将军！"));
								}
								else {
									redCheck = 1;
									statusBar()->showMessage(tr("红方将军！"));
								}
								vector<int> v = availableMoves(chessboard, 1 - turn);
								if (v.size() == 0) {//将死
									if (turn == 1) {
										statusBar()->showMessage(tr("红方被将死，黑方胜！（右键重新开始）"));
									}
									else {
										statusBar()->showMessage(tr("黑方被将死，红方胜！（右键重新开始）"));
									}
									moving = 2;
								}
							}
							else {
								if (!canMove(chessboard, 1 - turn)) {//无子可动
									if (turn == 1) {
										statusBar()->showMessage(tr("红方无子可动，黑方胜！（右键重新开始）"));
									}
									else {
										statusBar()->showMessage(tr("黑方无子可动，红方胜！（右键重新开始）"));
									}
									moving = 2;
								}
							}
						}
						step++;
						if (moving != 2) {
							if (mode == 1) { //双人对战
								turn = 1 - turn;
							}
							else {//人机对战，turn不变
								vector<int> v;
								if (mode == 2) {//电脑黑方
									v = move2(chessboard, 1);
								}
								else {//电脑红方
									v = move2(chessboard, 0);
								}
								x1 = v[0];
								y1 = v[1];
								x2 = v[2];
								y2 = v[3];
								move1(chessboard, x1, y1, x2, y2);
								repaint();//重绘棋盘
								insert_into_records(records, chessboard, step);
								if (mode == 2) {//电脑黑方
									statusBar()->showMessage(tr("已走子：") + QString::number(x2) + "," + QString::number(y2) + tr("，现在轮到红方"));
								}
								else {//电脑红方
									statusBar()->showMessage(tr("已走子：") + QString::number(x2) + "," + QString::number(y2) + tr("，现在轮到黑方"));
								}
								int temp = repeat(records, chessboard, step);
								if (temp > 0) {//重复三次，如果无将军为和棋，如果一方长将则另一方胜
									if (temp == 1) {
										statusBar()->showMessage(tr("局面三次重复，和棋！（右键重新开始）"));
									}
									else if (temp == 2) {
										statusBar()->showMessage(tr("红方长将，黑方胜！（右键重新开始）"));
									}
									else {
										statusBar()->showMessage(tr("黑方长将，红方胜！（右键重新开始）"));
									}
									moving = 2;
								}
								else {
									if (mode == 2) { //玩家红
										if (check(chessboard, 1)) {
											blackCheck = 1;
											statusBar()->showMessage(tr("黑方将军！"));
											vector<int> v = availableMoves(chessboard, 0);
											if (v.size() == 0) {//将死
												statusBar()->showMessage(tr("红方被将死，黑方胜！（右键重新开始）"));
												moving = 2;
											}
										}
										else {
											if (!canMove(chessboard, 0)) {//无子可动
												statusBar()->showMessage(tr("红方无子可动，黑方胜！（右键重新开始）"));
												moving = 2;
											}
										}
									}
									else {//玩家黑
										if (check(chessboard, 0)) {
											redCheck = 1;
											statusBar()->showMessage(tr("红方将军！"));
											vector<int> v = availableMoves(chessboard, 1);
											if (v.size() == 0) {//将死
												statusBar()->showMessage(tr("黑方被将死，红方胜！（右键重新开始）"));
												moving = 2;
											}
										}
										else {
											if (!canMove(chessboard, 1)) {//无子可动
												statusBar()->showMessage(tr("黑方无子可动，红方胜！（右键重新开始）"));
												moving = 2;
											}
										}
									}
								}
								step++;
							}
						}
					}
				}
			}
		}
	}
	else if (e->button() == Qt::RightButton) { //右键，用于取消
		if (moving == 1) {
			moving = 0;
			statusBar()->showMessage(tr("已取消"));
		}
		else if (moving == 2) {
			//游戏重新开始
			int temp_chessboard[10][9] = {
				{-3,-4,-5,-6,-7,-6,-5,-4,-3},
				{0,0,0,0,0,0,0,0,0},
				{0,-2,0,0,0,0,0,-2,0},
				{-1,0,-1,0,-1,0,-1,0,-1},
				{0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0},
				{1,0,1,0,1,0,1,0,1},
				{0,2,0,0,0,0,0,2,0},
				{0,0,0,0,0,0,0,0,0},
				{3,4,5,6,7,6,5,4,3},
			};
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 9; j++) {
					chessboard[i][j] = temp_chessboard[i][j];
				}
			}
			for (int k = 0; k < 300; k++) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 9; j++) {
						chessboard[i][j] = temp_chessboard[i][j];
					}
				}
			}
			turn = 0;//红方先行 
			moving = 0;//0选择子 1点击下一步要走到哪 2游戏结束
			x1 = 0;//坐标
			y1 = 0;
			x2 = 0;
			y2 = 0;
			redCheck = 0;//红方将军黑方
			blackCheck = 0;//黑方将军红方
			step = 0;
			insert_into_records(records, chessboard, step);
			step++;
			repaint();
			mode = 0;
			statusBar()->showMessage(tr("点击屏幕开始"));
		}
	}
}


void Chinese_chess2::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_Q)
	{
		if (moving == 0) {//目前在选择子状态
			if (mode == 1) { //双人对战
				if (step > 1) {
					step--;
					turn = 1 - turn;
					takeBack(chessboard, records, step - 1);
					statusBar()->showMessage(tr("已悔棋"));
					repaint();
				}
			}
			else {//人机对战
				if (mode == 2 && step > 1 && step % 2 == 1) {//玩家红
					step -= 2;
					takeBack(chessboard, records, step - 1);
					statusBar()->showMessage(tr("已悔棋"));
					repaint();
				}
				else if(mode == 3 && step > 2 && step % 2 == 0) {//玩家黑
					step -= 2;
					takeBack(chessboard, records, step - 1);
					statusBar()->showMessage(tr("已悔棋"));
					repaint();
				}
			}
		}
	}
}
