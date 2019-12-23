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
int  foodx, foody;//먹이의 위치
int score = 0;//점수이면서 동시에 뱀의 길이
void drawBoard(int n, int m)//맵을 화면에 출력
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
void makeFood(int n, int m)//먹이를 출력시킬 임의의 위치를 생성해 foodx, foody에 지정
{
	foodx = rand() % (n - 2) + 1;
	foody = rand() % (m - 2) + 1;
}
void init(int n, int m)//먹이와 뱀의 초기위치 설정, 뱀의 초기위치는 맵의 정중앙 cx,cy;
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
void Do(int sig, int n, int m)//main함수에 의해 0.3초마다 호출된다. 현재 뱀의 진행방향에 따라 다음화면에 출력될 뱀과 먹이의 위치 설정
{
	if (x[0] == foodx && y[0] == foody)//먹이를 먹음;
	{
		makeFood(n, m);
		score++;
		x[score] = x[score - 1];
		y[score] = y[score - 1];
		speed -= 7;//먹이를 먹으면 스피드가 빨라짐.
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
	if (sig == 'w' && lastc != 's')//이전키와 반대방향의 키가 나오지않는 경우에만 이동함.
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
int getCommand(void)//사용자로부터 입력받은키를 반환해준다.
{
	int c = 0;
	if (_kbhit())//입력을 받지않으면 이동하던 방향으로 계속 이동
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
	int temp;//엔터를 받아줌
	res = fscanf(ipt, "%d %d", &n, &m);
	for (i = 0; i < m; i++)
	{
		res = fscanf(ipt, "%c", &temp);
		for (j = 0; j < n; j++)
		{
			res = fscanf(ipt, "%c", &arr[i][j]);
		}
	}//맵 입력받음
	fclose(ipt);
	init(n, m);//뱀의 초기위치 초기화
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