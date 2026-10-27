#include<stdio.h>
#include<graphics.h>//easyx图形库
#include<conio.h>
#include<time.h>//生成随机数

int map[5][8];
struct Board {
	int x;
	int y;
	int w;
	int h;
	//速度   
	int v;
};//木板初始化
struct Board board= { 300,650,150,25,7};
void drawBoard(){
	setfillcolor(WHITE);
	//方块画x y
	fillrectangle(board.x,board.y,board.x+board.w,board.y + board.h);
}

//木板按键
void keyDown(){
	if ((GetAsyncKeyState('A') & 0x8000) || GetAsyncKeyState(VK_LEFT) & 0x8000) {
		board.x -= board.v;
	};
	if ((GetAsyncKeyState('D') & 0x8000) || GetAsyncKeyState(VK_RIGHT)&0x8000) {
		board.x += board.v;
 }
}
struct Ball {
	int x;
	int y;
	int r;
	int dx;
	int dy;
};
struct Ball ball = { 400,400,15,3,-3 };
//画球
void drawBall() { 
	ball.x += ball.dx;
	ball.y += ball.dy;
	//球的颜色
	setfillcolor(RED);
	solidcircle(ball.x,ball.y,ball.r);
}
//时间间隔 id控制定时器
int Timer(int duration,int id){
//开始时间 0-10  
	static int startTime[10];
	//上一次的结果
	int endTime = clock();
	if (endTime - startTime[10] > duration)
	{
		startTime[id] = endTime;
		return 1;
	} return 0;
}
//球的移动

void moveball() {
	int hitBricks();
	int hitBoard();
	if (ball.x + ball.r >= 100 * 8|| ball.x - ball.r<= 0)
	{
		ball.dx = -ball.dx;
	}
	if (hitBoard() || hitBricks() || ball.y - ball.r <= 0) { ball.dy = -ball.dy; }
	ball.x += ball.dx;
	ball.y += ball.dy;
}
//碰撞
int  hitBoard() {
	if (ball.y + ball.r >= board.y)//碰到了
	{
		if (ball.x >= board.x && ball.x <= board.x + board.w)
		{
			return 1;
	}
	}

	return 0;
}
//砖块消失
int hitBricks() {
	int j = ball.x / 100;
	int i = (ball.y - ball.r) / 25;
	if (i < 5 && j < 8 && map[i][j] != 0)
	{
		map[i][j] = 0;
		return 1;
	}return 0;
}  




void initmap() //初始化地图
{
	for (int i = 0;i<5;i++)
	{
		for (int j = 0;j<8;j++)
		{
			map[i][j] = rand() % 3 + 1;// rand%3+1 




		}
	}
}
void drawmap(){
	for (int i = 0;i < 5;i++) 
	{
		for (int j = 0;j < 8;j++) {
			int x = 100 * j;
			int y = 25 * i;
			//选择颜色
			switch (map[i][j])
			{
			case 0:
			
					break;
			case 1:setfillcolor(GREEN);
				//方块画x y
				fillrectangle(x,y, x+100, y+25);
				    break;
			case 2:setfillcolor(YELLOW);
				//方块画x y
				fillrectangle(x, y, x + 100, y + 25);
				   break;
			case 3:setfillcolor(BLUE);
				//方块画x y
				fillrectangle(x, y, x + 100, y + 25);
				break;
			}
		}
	}
}
   
 
int main() {
	srand((unsigned int)time(0));//无符号小整形数
	//创建一个窗口 
	initgraph(800, 700, 1);//初始化
	//设置方块的颜色  数值 取色器  
	setfillcolor(RGB(255, 255, 128));
	//方块画x y

	initmap();
	BeginBatchDraw();
	while (1) {
		cleardevice();
		drawmap();
		//画木板  
		drawBoard();
		keyDown();
		drawBall();
		if(Timer(100,0))
		moveball();
		FlushBatchDraw();//刷新双缓存
		Sleep(10);

	}
	//清理屏幕
	closegraph();
	return 0;
}