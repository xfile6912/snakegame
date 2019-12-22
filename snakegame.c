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
int snake[10000][10000];
int  foodx, foody;//������ ��ġ
int score = 0;//�����̸鼭 ���ÿ� ���� ����
int getfood;//0�̸� �������̸� ����������,1�̸� ��������
void drawBoard(int n, int m)//���� ȭ�鿡 ���
{
	system("cls");
	int temp;
	int i, j;
	puts("");
	printf("Snake Game |Score : %d|\n", score * 100);
	puts("");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == cy && j == cx)
				printf("@");
			else if (foody == i && foodx == j)
				printf("F");
			else if (arr[i][j] == '1')
				printf("A");
			else
				printf(" ");
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
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			snake[i][j] = 0;
		}
	}
	cx = n / 2;
	cy = m / 2;
	snake[cy][cx] = 1;
	game_over = 0;
	time_out = 0;
	getfood = 0;
	makeFood(n, m);
}
void Do(int sig, int n, int m)//main�Լ��� ���� 0.3�ʸ��� ȣ��ȴ�. ���� ���� ������⿡ ���� ����ȭ�鿡 ��µ� ��� ������ ��ġ ����
{
	if (sig == 'w' && lastc != 's')//����Ű�� �ݴ������ Ű�� �������ʴ� ��쿡�� �̵���.
	{
		lastc = sig;
		cy--;
	}
	else if (sig == 'd' && lastc != 'a')
	{
		lastc = sig;
		cx++;
	}
	else if (sig == 'a' && lastc != 'd')
	{
		lastc = sig;
		cx--;
	}
	else if (sig == 's' && lastc != 'w')
	{
		lastc = sig;
		cy++;
	}
	if (cx == foodx && cy == foody)//���̸� ����;
		getfood = 1;
	if (cx == 0 || cy == 0 || cx == n - 1 || cy == m - 1)
		game_over = 1;
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
		if (getfood == 1)
		{
			makeFood(n, m);
			score++;
			speed -= 7;//���̸� ������ ���ǵ尡 ������.
			getfood = 0;
		}
		drawBoard(n, m);
	} while (!game_over);
	system("cls");
	printf("game over!\n");
}