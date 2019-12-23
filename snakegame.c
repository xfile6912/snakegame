#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

int time_out, cx, cy, game_over;
int lastc;
int speed = 200;
int arr[10000][10000];
int x[20] = { -1 };
int y[20] = { -1 };
int  foodx, foody;//������ ��ġ
int score = 0;//�����̸鼭 ���ÿ� ���� ����
void drawBoard(int n, int m)//���� ȭ�鿡 ���
{
	system("cls");
	int temp;
	int i, j, k;
	int flag = 0;
	puts("");
	printf("Snake Game |Score : %d|\n", score * 100);
	puts("");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			flag = 0;
			for (k = 0; k <= score; k++)
			{
				if (i == y[k] && j == x[k])
				{
					printf("@");
					flag = 1;
				}
			}
			if (foody == i && foodx == j && flag != 1)
				printf("F");
			else if (arr[i][j] == '1')
				printf("A");
			else if (flag != 1)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}
void makeFood(int n, int m)//���̸� ��½�ų ������ ��ġ�� ������ foodx, foody�� ����
{
	foodx = rand() % (n - 2) + 1;
	foody = rand() % (m - 2) + 1;
}
void init(int n, int m)//���̿� ���� �ʱ���ġ ����, ���� �ʱ���ġ�� ���� ���߾� cx,cy;
{
	int i, j;
	cx = n / 2;
	cy = m / 2;
	x[0] = cx;
	y[0] = cy;
	game_over = 0;
	time_out = 0;
	makeFood(n, m);
}
void Do(int sig, int n, int m)//main�Լ��� ���� 0.3�ʸ��� ȣ��ȴ�. ���� ���� ������⿡ ���� ����ȭ�鿡 ��µ� ��� ������ ��ġ ����
{
	if (x[0] == foodx && y[0] == foody)//���̸� ����;
	{
		makeFood(n, m);
		score++;
		x[score] = x[score - 1];
		y[score] = y[score - 1];
		speed -= 7;//���̸� ������ ���ǵ尡 ������.
	}
	if (x[0] == 0 || y[0] == 0 || x[0] == n - 1 || y[0] == m - 1)
	{
		game_over = 1;
		return;
	}
	for (int i = score; i > 0; i--)
	{
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	if (sig == 'w' && lastc != 's')//����Ű�� �ݴ������ Ű�� �������ʴ� ��쿡�� �̵���.
	{
		lastc = sig;
		y[0]--;
	}
	else if (sig == 'd' && lastc != 'a')
	{
		lastc = sig;
		x[0]++;
	}
	else if (sig == 'a' && lastc != 'd')
	{
		lastc = sig;
		x[0]--;
	}
	else if (sig == 's' && lastc != 'w')
	{
		lastc = sig;
		y[0]++;
	}
	else if (lastc == 's')
		y[0]++;
	else if (lastc == 'a')
		x[0]--;
	else if (lastc == 'd')
		x[0]++;
	else if (lastc == 'w')
		y[0]--;
	for (int i = 1; i <= score; i++)
		if (x[0] == x[i] && y[0] == y[i])
		{
			game_over = 1;
			return;
		}
}
int getCommand(void)//����ڷκ��� �Է¹���Ű�� ��ȯ���ش�.
{
	int c = 0;
	if (_kbhit())//�Է��� ���������� �̵��ϴ� �������� ��� �̵�
		c = _getch();
	else
		c = lastc;
	return c;
}
int main(void)
{
	FILE* ipt = fopen("board.txt", "r");
	int res;
	int command;
	int n, m, j, i;
	int temp;//���͸� �޾���
	res = fscanf(ipt, "%d %d", &n, &m);
	for (i = 0; i < m; i++)
	{
		res = fscanf(ipt, "%c", &temp);
		for (j = 0; j < n; j++)
		{
			res = fscanf(ipt, "%c", &arr[i][j]);
		}
	}//�� �Է¹���
	fclose(ipt);
	init(n, m);//���� �ʱ���ġ �ʱ�ȭ
	srand(time(NULL));
	do {
		Sleep(speed);
		command = getCommand();
		printf("%d", game_over);
		Do(command, n, m);
		drawBoard(n, m);
	} while (!game_over);
	system("cls");
	printf("game over!\n");
}