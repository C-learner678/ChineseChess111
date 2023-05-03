#pragma execution_character_set("utf-8") //���ı��루���룩

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
	turn = 0;//�췽���� 
	moving = 0;//0ѡ���� 1�����һ��Ҫ�ߵ��� 2��Ϸ����
	x1 = 0;//����
	y1 = 0;
	x2 = 0;
	y2 = 0;
	redCheck = 0;//�췽�����ڷ�
	blackCheck = 0;//�ڷ������췽
	step = 0;
	insert_into_records(records, chessboard, step);
	step++;
	statusBar()->showMessage(tr("�����Ļ��ʼ"));

	mode = 0;//ģʽ 0δѡ�� 1˫�˶�ս 2��Һ���Ժ� 3���Ժ���Һ�
}


void Chinese_chess2::paintEvent(QPaintEvent *event)

{
	QPainter paint(this);
	QPen pen;  //Ĭ�ϻ���
	QPointF point;
	//��������
	pen.setWidth(2);//���Ʊ߿�
	paint.setPen(pen);
	paint.drawLine(50, 50, 450, 50);
	paint.drawLine(50, 50, 50, 500);
	paint.drawLine(450, 50, 450, 500);
	paint.drawLine(50, 500, 450, 500);
	pen.setWidth(1);//��������
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
	paint.drawText(point, "����                 ����");
	//��������
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
				else {//�������µߵ�
					paint.drawEllipse(j * 50 + 30, (9 - i) * 50 + 30, 40, 40);
					point.setX(j * 50 + 38);
					point.setY((9 - i) * 50 + 58);
				}
				if (chessboard[i][j] > 0) {
					paint.setPen(Qt::red);
					if (chessboard[i][j] == 1) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == 2) {
						paint.drawText(point, "�h");
					}
					else if (chessboard[i][j] == 3) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == 4) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == 5) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == 6) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == 7) {
						paint.drawText(point, "��");
					}
				}
				else {
					paint.setPen(Qt::black);
					if (chessboard[i][j] == -1) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == -2) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == -3) {
						paint.drawText(point, "܇");
					}
					else if (chessboard[i][j] == -4) {
						paint.drawText(point, "�R");
					}
					else if (chessboard[i][j] == -5) {
						paint.drawText(point, "��");
					}
					else if (chessboard[i][j] == -6) {
						paint.drawText(point, "ʿ");
					}
					else if (chessboard[i][j] == -7) {
						paint.drawText(point, "��");
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
	if (e->button() == Qt::LeftButton) //���
	{
		if (mode == 0) {
			rb = QMessageBox::information(NULL, "��ѡ��", "���Ƿ�Ҫ��ʼ˫�˶�ս��", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if (rb == QMessageBox::Yes)
			{
				mode = 1;
				statusBar()->showMessage(tr("��Ϸ��ʼ��"));
			}
			else {
				rb = QMessageBox::information(NULL, "��ѡ��", "���Ƿ�ѡ��ִ�췽��", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				if (rb == QMessageBox::Yes)
				{
					mode = 2;
					turn = 0;
					statusBar()->showMessage(tr("��Ϸ��ʼ��"));
				}
				else {
					mode = 3;//���Ժ췽����ʱ��������һ����
					turn = 0;
					statusBar()->showMessage(tr("��Ϸ��ʼ��"));
					repaint();//�ػ�����
					vector<int> v = move2(chessboard, turn);//��������
					x1 = v[0];
					y1 = v[1];
					x2 = v[2];
					y2 = v[3];
					move1(chessboard, x1, y1, x2, y2);
					repaint();//�ػ�����
					insert_into_records(records, chessboard, step);
					step++;
					statusBar()->showMessage(tr("�����ӣ�") + QString::number(x2) + "," + QString::number(y2) + tr("�������ֵ��ڷ�"));
					turn = 1;
				}
			}
		}
		else {
			int clickX = e->x();
			int clickY = e->y();
			int x = 0;
			int y = 0;
			if (clickX > 25 && clickX < 475 && clickY > 25 && clickY < 525) {//�����̷�Χ��
				y = (clickX - 25) / 50;
				x = (clickY - 25) / 50;
				if (mode == 3) {//�������µߵ�
					x = 9 - x;
				}
				if (moving == 0) {//ѡ����
					if (turn == 0) {//��
						if (chessboard[x][y] > 0) {
							moving = 1;
							statusBar()->showMessage(tr("��ѡ�У�") + QString::number(x) + "," + QString::number(y) + tr("���Ҽ�ȡ����"));
							x1 = x;
							y1 = y;
						}
					}
					else if (turn == 1) {//��
						if (chessboard[x][y] < 0) {
							moving = 1;
							statusBar()->showMessage(tr("��ѡ�У�") + QString::number(x) + "," + QString::number(y) + tr("���Ҽ�ȡ����"));
							x1 = x;
							y1 = y;
						}
					}
				}
				else if (moving = 1) {//����
					if (turn == 0) {//��
						if (blackCheck == 0) {//������
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
					else if (turn == 1) {//��
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
					if (canmove) {//�߶�
						moving = 0;
						x2 = x;
						y2 = y;
						move1(chessboard, x1, y1, x2, y2);
						insert_into_records(records, chessboard, step);
						if (turn == 1) {//�ڷ�
							statusBar()->showMessage(tr("�����ӣ�") + QString::number(x2) + "," + QString::number(y2) + tr("�������ֵ��췽"));
						}
						else {//�췽
							statusBar()->showMessage(tr("�����ӣ�") + QString::number(x2) + "," + QString::number(y2) + tr("�������ֵ��ڷ�"));
						}
						repaint();//�ػ�����
						int temp = repeat(records, chessboard, step);
						if (temp > 0) {//�ظ����Σ�����޽���Ϊ���壬���һ����������һ��ʤ
							if (temp == 1) {
								statusBar()->showMessage(tr("���������ظ������壡���Ҽ����¿�ʼ��"));
							}
							else if (temp == 2) {
								statusBar()->showMessage(tr("�췽�������ڷ�ʤ�����Ҽ����¿�ʼ��"));
							}
							else {
								statusBar()->showMessage(tr("�ڷ��������췽ʤ�����Ҽ����¿�ʼ��"));
							}
							moving = 2;
						}
						else {
							if (check(chessboard, turn)) {
								if (turn == 1) {
									blackCheck = 1;
									statusBar()->showMessage(tr("�ڷ�������"));
								}
								else {
									redCheck = 1;
									statusBar()->showMessage(tr("�췽������"));
								}
								vector<int> v = availableMoves(chessboard, 1 - turn);
								if (v.size() == 0) {//����
									if (turn == 1) {
										statusBar()->showMessage(tr("�췽���������ڷ�ʤ�����Ҽ����¿�ʼ��"));
									}
									else {
										statusBar()->showMessage(tr("�ڷ����������췽ʤ�����Ҽ����¿�ʼ��"));
									}
									moving = 2;
								}
							}
							else {
								if (!canMove(chessboard, 1 - turn)) {//���ӿɶ�
									if (turn == 1) {
										statusBar()->showMessage(tr("�췽���ӿɶ����ڷ�ʤ�����Ҽ����¿�ʼ��"));
									}
									else {
										statusBar()->showMessage(tr("�ڷ����ӿɶ����췽ʤ�����Ҽ����¿�ʼ��"));
									}
									moving = 2;
								}
							}
						}
						step++;
						if (moving != 2) {
							if (mode == 1) { //˫�˶�ս
								turn = 1 - turn;
							}
							else {//�˻���ս��turn����
								vector<int> v;
								if (mode == 2) {//���Ժڷ�
									v = move2(chessboard, 1);
								}
								else {//���Ժ췽
									v = move2(chessboard, 0);
								}
								x1 = v[0];
								y1 = v[1];
								x2 = v[2];
								y2 = v[3];
								move1(chessboard, x1, y1, x2, y2);
								repaint();//�ػ�����
								insert_into_records(records, chessboard, step);
								if (mode == 2) {//���Ժڷ�
									statusBar()->showMessage(tr("�����ӣ�") + QString::number(x2) + "," + QString::number(y2) + tr("�������ֵ��췽"));
								}
								else {//���Ժ췽
									statusBar()->showMessage(tr("�����ӣ�") + QString::number(x2) + "," + QString::number(y2) + tr("�������ֵ��ڷ�"));
								}
								int temp = repeat(records, chessboard, step);
								if (temp > 0) {//�ظ����Σ�����޽���Ϊ���壬���һ����������һ��ʤ
									if (temp == 1) {
										statusBar()->showMessage(tr("���������ظ������壡���Ҽ����¿�ʼ��"));
									}
									else if (temp == 2) {
										statusBar()->showMessage(tr("�췽�������ڷ�ʤ�����Ҽ����¿�ʼ��"));
									}
									else {
										statusBar()->showMessage(tr("�ڷ��������췽ʤ�����Ҽ����¿�ʼ��"));
									}
									moving = 2;
								}
								else {
									if (mode == 2) { //��Һ�
										if (check(chessboard, 1)) {
											blackCheck = 1;
											statusBar()->showMessage(tr("�ڷ�������"));
											vector<int> v = availableMoves(chessboard, 0);
											if (v.size() == 0) {//����
												statusBar()->showMessage(tr("�췽���������ڷ�ʤ�����Ҽ����¿�ʼ��"));
												moving = 2;
											}
										}
										else {
											if (!canMove(chessboard, 0)) {//���ӿɶ�
												statusBar()->showMessage(tr("�췽���ӿɶ����ڷ�ʤ�����Ҽ����¿�ʼ��"));
												moving = 2;
											}
										}
									}
									else {//��Һ�
										if (check(chessboard, 0)) {
											redCheck = 1;
											statusBar()->showMessage(tr("�췽������"));
											vector<int> v = availableMoves(chessboard, 1);
											if (v.size() == 0) {//����
												statusBar()->showMessage(tr("�ڷ����������췽ʤ�����Ҽ����¿�ʼ��"));
												moving = 2;
											}
										}
										else {
											if (!canMove(chessboard, 1)) {//���ӿɶ�
												statusBar()->showMessage(tr("�ڷ����ӿɶ����췽ʤ�����Ҽ����¿�ʼ��"));
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
	else if (e->button() == Qt::RightButton) { //�Ҽ�������ȡ��
		if (moving == 1) {
			moving = 0;
			statusBar()->showMessage(tr("��ȡ��"));
		}
		else if (moving == 2) {
			//��Ϸ���¿�ʼ
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
			turn = 0;//�췽���� 
			moving = 0;//0ѡ���� 1�����һ��Ҫ�ߵ��� 2��Ϸ����
			x1 = 0;//����
			y1 = 0;
			x2 = 0;
			y2 = 0;
			redCheck = 0;//�췽�����ڷ�
			blackCheck = 0;//�ڷ������췽
			step = 0;
			insert_into_records(records, chessboard, step);
			step++;
			repaint();
			mode = 0;
			statusBar()->showMessage(tr("�����Ļ��ʼ"));
		}
	}
}


void Chinese_chess2::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_Q)
	{
		if (moving == 0) {//Ŀǰ��ѡ����״̬
			if (mode == 1) { //˫�˶�ս
				if (step > 1) {
					step--;
					turn = 1 - turn;
					takeBack(chessboard, records, step - 1);
					statusBar()->showMessage(tr("�ѻ���"));
					repaint();
				}
			}
			else {//�˻���ս
				if (mode == 2 && step > 1 && step % 2 == 1) {//��Һ�
					step -= 2;
					takeBack(chessboard, records, step - 1);
					statusBar()->showMessage(tr("�ѻ���"));
					repaint();
				}
				else if(mode == 3 && step > 2 && step % 2 == 0) {//��Һ�
					step -= 2;
					takeBack(chessboard, records, step - 1);
					statusBar()->showMessage(tr("�ѻ���"));
					repaint();
				}
			}
		}
	}
}
