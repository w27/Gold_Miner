// Gold_Miner.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Point {
	int x;
	int y;
};

struct Mine {
	IMAGE MinePic;
	Point center;
	int value;
	int weight;
};

struct Node
{
	Mine mine;
	Node* next;
};

void LoadAllImage(IMAGE *pic)
{
	char tool[20], mine[20], miner[20], botton[20];
	strcpy_s(tool, "images/tool1.jpg");
	strcpy_s(mine, "images/mine1.jpg");
	strcpy_s(miner, "images/mining1.jpg");
	strcpy_s(botton, "images/botton1.jpg");
	loadimage(pic, "images/background.jpg");	//pic[0] = 背景
	for (int i = 1; i < 24; i++)
	{
		if (i == 1)
			loadimage(pic + i, "images/Miner_Normal.jpg");	//pic[1] = 正常矿工
		else if (i == 2)
			loadimage(pic + i, "images/Miner_Grab.jpg");		//pic[2] = 向下矿工
		else if (i <= 8)
		{
			loadimage(pic + i, miner);		//pic[3]-pic[8] = 向上矿工
			miner[13]++;
		}
		else if (i <= 12)
		{
			loadimage(pic + i, botton);		//pic[9] 开始 [10] 排行榜 [11] 退出 [12] 暂停
			botton[13]++;
		}
		else if (i <= 15)
		{
			loadimage(pic + i, tool);		//pic[13] 炸药 [14] 大力水 [15] 眼镜
			tool[11]++;
		}
		else if (i == 16)
			loadimage(pic + i, "images/Grabber.jpg");	// pic[16] 钩子
		else if (i == 17)
			loadimage(pic + i, "images/bag.jpg");	//pic[17] 道具包
		else if (i <= 23)
		{
			loadimage(pic + i, mine);	//[18] 小金块 [19] 中金块 [20] 大金块
			mine[11]++;					//[21] 小石头 [22] 大石头 [23] 钻石
		}
	}
}

void MakeMask(IMAGE* pic, IMAGE* mask)		//制作掩码图
{
	for (int i = 0; i < 8; i++)
	{
		mask[i] = pic[i];
		DWORD *pmemPic = GetImageBuffer(pic + i);
		DWORD *pmemMask = GetImageBuffer(mask + i);
		COLORREF maskbk = pmemPic[0];
		int width = (pic + i)->getwidth();
		int height = (pic + i)->getheight();
		for (int j = 0; j < width * height; j++)
		{
			if (pmemPic[j] <= 0x111111 && pmemPic[i] >= 0)
				pmemMask[j] = WHITE;
			else
				pmemMask[j] = BLACK;
		}
	}
}

void Initialize(IMAGE* pic, IMAGE* mask)
{
	initgraph(WINDOWWIDTH, WINDOWHEIGHT);
	setbkcolor(RGB(0xff, 0xcf, 0x34));
	cleardevice();
	settextstyle(20, 0, "Times New Roman");
	rectangle(0, 0, BGWIDTH, BGHEIGHT);
	rectangle(BGWIDTH, 0, WINDOWWIDTH, INFOHEIGHT);
	LoadAllImage(pic);
	MakeMask(pic + 16, mask);
	putimage(0, 0, pic);
}

void PutLucidImage(int x, int y, IMAGE* pic, IMAGE* mask)
{
	BeginBatchDraw();
	putimage(x, y, mask, SRCAND);
	putimage(x, y, pic, SRCPAINT);
	FlushBatchDraw();
	EndBatchDraw();
}

boolean StartMenu(char *Username, IMAGE *pic, IMAGE* mask)
{
	InputBox(Username, 14, "Enter your name with no more than 14 characters",
		"Gold Miner", "player0");

	putimage(FNPLACEX, BOTTON1PLACE, pic + 9);		//按钮图片
	putimage(FNPLACEX, BOTTON2PLACE, pic + 10);
	putimage(FNPLACEX, BOTTON3PLACE, pic + 11);

	putimage(MINERPLACEX, MINERPLACEY, pic + 1);	//初始矿工
	PutLucidImage(GRPLACEX, GRPLACEY, pic + 16, mask);	//钩子
	int TextY = 450;
	{		//输出信息
		outtextxy(FNPLACEX, TEXT1PLACE, "Player Name:");
		outtextxy(TEXTMSGPLACEX, TEXT1PLACE, Username);
		outtextxy(FNPLACEX, TEXT2PLACE, "Score:");
		outtextxy(TEXTMSGPLACEX, TEXT2PLACE, "0");
		outtextxy(FNPLACEX, TEXT3PLACE, "Time Left:");
		outtextxy(TEXTMSGPLACEX, TEXT3PLACE, "0");
		outtextxy(FNPLACEX, TEXT4PLACE, "High Score:");
	}
	while (true)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.x >= FNPLACEX && m.x <= FNPLACEX + BOTTONWIDTH)
		{
			if (m.y >= BOTTON1PLACE && m.y <= BOTTON1PLACE + BOTTONHEIGHT)
			{
				if (m.mkLButton == true)
					return true;
			}
			if (m.y >= BOTTON2PLACE && m.y <= BOTTON2PLACE + BOTTONHEIGHT)
			{

			}
			if (m.y >= BOTTON3PLACE && m.y <= BOTTON3PLACE + BOTTONHEIGHT)
			{
				if (m.mkLButton == true)
					return false;
			}
		}
		Sleep(10);
	}
}

int RandomNum()
{
	srand((unsigned long)time(NULL));
	int num = pow(rand() % 50000, 2) / 39;
	return num;
}

void MainGame()
{
	Mine mine[7];
	for (int i = 0; i < 7; i++)
	{
		mine[i].MinePic = 
	}
}

int main()
{	
	IMAGE Pic[24];
	IMAGE MaskPic[8];
	char UserName[15];
	Initialize(Pic, MaskPic);
	if (StartMenu(UserName, Pic, MaskPic) == true)
	{
		MainGame();
	}
	closegraph();

    return 0;
}