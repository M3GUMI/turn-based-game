#include <winsock2.h>
#include<windows.h>
#include <winsock.h>
#include <mysql.h> //数据库的变量类型和函数
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<graphics.h>
#include<easyx.h>
#include<time.h>
#include <stdbool.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
#include<mmsystem.h>
#include"图形化界面.h"
#include"抽卡系统.h"
#include"怪物系统.h"
#include"人物系统.h"
#define charatotalnum 9

/**************************************
*            图形化界面系统 ！        *
*      实现图形化界面的搭建和交互     *
*   实现数据库的存入和后端数值的连接  *
***************************************/


//将字符串转化为整数
int GetInt(char str[]) {
    int num =0;
    for (int j = 0; str[j] != 0; j++) {
        num = num * 10 + (str[j] - '0');
    }
    return num;
}


//实时在人物界面显示用户数据的函数
void ShowCharacter(char level[],char EXPAmount[],int select,int number) {
    char characLevel[20] = { 0 };
    sprintf(characLevel, "LV:%s", level);
    //输出等级
    outtextxy(100+number*170, 100, characLevel);
    //输出数量
    switch (select) {
    case 0:outtextxy(670, 45, EXPAmount); break;
    case 1:outtextxy(870, 45, EXPAmount); break;
    case 2:outtextxy(1070, 45, EXPAmount); break;
    }
}


//切换到抽卡界面的动画
void HometoDrawAnime() {
    //加载图片
    IMAGE PHome, PDraw;
    loadimage(&PHome, ".\\img\\background\\主页背景.jpg", 1200, 600);
    loadimage(&PDraw, ".\\img\\background\\抽卡总界面.png", 1200, 600);

    //动画
    for (int i = 0; i <= 600; i += 3) {
        cleardevice();
        putimage(0, 0 + i, &PHome);
        putimage(0, -600 + i, &PDraw);
        Sleep(2);
    }
}


//切换到退出界面的动画
void HometoExitAnime() {
    //加载图片
    IMAGE PHome, PExit;
    loadimage(&PHome, ".\\img\\background\\主页背景.jpg", 1200, 600);
    loadimage(&PExit, ".\\img\\background\\退出背景.png", 1200, 600);

    //动画
    for (int i = 0; i <= 600; i += 3) {
        cleardevice();
        putimage(0, 0 + i, &PHome);
        putimage(0, -600 + i, &PExit);
        Sleep(2);
    }
}


//主页
void HomePage(char userName[]) {

    //声明图片变量
    IMAGE PBackground, PBattle, PCharac, PDraw, PExit, PTotal;

    //加载图片
    loadimage(&PExit, ".\\img\\button\\退出2.jpg", 160, 60);
    loadimage(&PDraw, ".\\img\\button\\抽卡2.jpg", 160, 60);
    loadimage(&PCharac, ".\\img\\button\\角色2.jpg", 160, 60);
    loadimage(&PBattle, ".\\img\\button\\战斗2.jpg", 160, 60);
    loadimage(&PBackground, ".\\img\\background\\主页背景.jpg", 1200, 600);
    loadimage(&PTotal, ".\\img\\button\\用户按键总.jpg", 850, 60);

    //开场动画
    for (int i = 0; i <= 550; i+=5) {
        cleardevice();
        putimage(0, -600+i, &PBackground);
        Sleep(20);
    }

    //主界面
    cleardevice();
    putimage(0, -50, &PBackground);
    putimage(170, 430, &PTotal);


    //通过鼠标操作实现按钮点击交互
    MOUSEMSG m;
    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //鼠标在规定区域划过时
        case WM_LBUTTONDOWN: {
            if (m.x >= 170 && m.x <= 330 && m.y >= 430 && m.y <= 490) {
                MapPage(userName);
            }
            if (m.x >= 400 && m.x <= 560 && m.y >= 430 && m.y <= 490) {
                CharacPage(userName);
            }
            if (m.x >= 630 && m.x <= 790 && m.y >= 430 && m.y <= 490) {
                HometoDrawAnime();
                DrawPage(userName);
            }
            if (m.x >= 860 && m.x <= 1020 && m.y >= 430 && m.y <= 490) {
                HometoExitAnime();
                ExitPage();
            }
        }
                           //鼠标在规定区域点击时
        case WM_MOUSEMOVE: {
            if (m.x >= 170 && m.x <= 330 && m.y >= 430 && m.y <= 490) {
                putimage(170, 430, &PBattle);
            }
            else if (m.x >= 400 && m.x <= 560 && m.y >= 430 && m.y <= 490) {
                putimage(400, 430, &PCharac);
            }
            else if (m.x >= 630 && m.x <= 790 && m.y >= 430 && m.y <= 490) {
                putimage(630, 430, &PDraw);
            }
            else if (m.x >= 860 && m.x <= 1020 && m.y >= 430 && m.y <= 490) {
                putimage(860, 430, &PExit);
            }
            else {
                putimage(170, 430, &PTotal);
                Sleep(1);
            }
        }
        }
    }

}


//抽卡页面
void DrawPage(char userName[]) {

    //加载图片
    IMAGE img, PSoul,PSoul2, PSoulBack, PSoulFrame, PCharac, PCharacBackground, PButtonBackground, PDanChou, PShiLian, PDanChou2, PShiLian2, PBack, PBack2, PBacky, PBili, PBilyBackground, PCxk, PCxkBackground, PAoErJia, PBily, PKeQin, PDVA, POuHuang, PKeShiFu, Pcxk, PLEXP, PMEXP, PSEXP,PPunch;
    MOUSEMSG m;
    IMAGE PMaterial[10];
    int result;
    char material[10][20] = { "AoErJia","DVA","cxk","KeShiFu","Bily","OuHuang","smallEXP","middleEXP","largeEXP","Soul" }, soul[5] = { 0 };
    loadimage(&img, ".\\img\\background\\抽卡背景.png", 1200, 600);
    loadimage(&PSoul, ".\\img\\material\\灵魂点数1.jpg", 50, 50);
    loadimage(&PSoul2, ".\\img\\material\\灵魂点数1c.jpg", 100, 100);
    loadimage(&PSoulBack, ".\\img\\material\\灵魂点数1y.jpg", 50, 50);
    loadimage(&PSoulFrame, ".\\img\\background\\灵魂点数背景框.jpg", 160, 60);
    loadimage(&PButtonBackground, ".\\img\\background\\灵魂点数背景框y.jpg", 160, 60);
    loadimage(&PCharac, ".\\img\\background\\人物抽卡背景.png", 800, 450);
    loadimage(&PCharacBackground, ".\\img\\background\\人物抽卡背景y.png", 800, 450);
    loadimage(&PDanChou, ".\\img\\button\\来一发.jpg", 160, 60);
    loadimage(&PShiLian, ".\\img\\button\\来十发.jpg", 160, 60);
    loadimage(&PShiLian2, ".\\img\\button\\来十发2.jpg", 160, 60);
    loadimage(&PDanChou2, ".\\img\\button\\来一发2.jpg", 160, 60);
    loadimage(&PBack, ".\\img\\button\\返回.png", 50, 40);
    loadimage(&PBack2, ".\\img\\button\\返回2.png", 50, 40);
    loadimage(&PBacky, ".\\img\\button\\返回y.png", 50, 40);
    loadimage(&PBilyBackground, ".\\img\\character\\比利王\\比利王背景.png", 250, 180);
    loadimage(&PBili, ".\\img\\character\\比利王\\比利王.png", 250, 180);
    loadimage(&PCxk, ".\\img\\character\\蔡徐坤\\蔡徐坤.png", 220, 280);
    loadimage(&PCxkBackground, ".\\img\\character\\蔡徐坤\\蔡徐坤背景.png", 220, 280); 
    loadimage(&PMaterial[0], ".\\img\\character\\奥尔加\\奥尔加头像.png", 100, 100);
    loadimage(&PMaterial[1], ".\\img\\character\\DVA\\DVA头像.png", 100, 100);
    loadimage(&PMaterial[2], ".\\img\\character\\蔡徐坤\\蔡徐坤头像.png", 100, 100);
    loadimage(&PMaterial[4], ".\\img\\character\\比利王\\比利王头像.png", 100, 100);
    loadimage(&PMaterial[3], ".\\img\\character\\氪师傅\\氪师傅头像.png", 100, 100);
    loadimage(&PMaterial[5], ".\\img\\character\\欧皇\\欧皇头像.png", 100, 100);
    loadimage(&PMaterial[6], ".\\img\\material\\经验药小c.png", 100, 100);
    loadimage(&PMaterial[7], ".\\img\\material\\经验药中c.png", 100,100);
    loadimage(&PMaterial[8], ".\\img\\material\\经验药大c.png", 100, 100);
    loadimage(&PMaterial[9], ".\\img\\material\\灵魂点数1c.jpg", 100, 100);
    loadimage(&PPunch, ".\\img\\background\\给你两拳.gif", 200, 200);
    


    //搭建抽卡初始页面
    putimage(0, 0, &img);
    putimage(60, 90, &PCharacBackground, SRCAND);
    putimage(60, 90, &PCharac, SRCPAINT);
    putimage(950, 100, &PButtonBackground, SRCAND);
    putimage(950, 100, &PSoulFrame, SRCPAINT);
    putimage(955, 105, &PSoulBack, SRCAND);
    putimage(955, 105, &PSoul, SRCPAINT);
    putimage(955, 305, &PButtonBackground, SRCAND);
    putimage(955, 305, &PDanChou, SRCPAINT);
    putimage(955, 405, &PButtonBackground, SRCAND);
    putimage(955, 405, &PShiLian, SRCPAINT);
    putimage(50, 15, &PBacky, SRCAND);
    putimage(50, 15, &PBack, SRCPAINT);
    putimage(90, 355, &PBilyBackground, SRCAND);
    putimage(90, 355, &PBili, SRCPAINT);
    putimage(270, 255, &PCxkBackground, SRCAND);
    putimage(270, 255, &PCxk, SRCPAINT);

    //显示抽卡概率
    outtextxy(955, 170, "抽出人物概率：6%");
    outtextxy(955, 190, "抽出大经验概率：10%");
    outtextxy(955, 210, "抽出中经验概率：25%");
    outtextxy(955, 230, "抽出小经验概率：39%");
    outtextxy(955, 250, "抽出灵魂点数概率：20%");

    //定义链接数据库的基本变量
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    char searchCommand[180];
    sprintf(searchCommand, "select Soul from users where username=\"%s\"", userName);

    //遍历数据库看灵魂点数数量存在
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //获得数据
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //在图形界面显示灵魂点数的值
    outtextxy(1025, 125, row[0]);

    mysql_free_result(res);

    sprintf(searchCommand, "select AoErJia,DVA,cxk,KeShiFu,Bily,OuHuang,smallEXP,middleEXP,largeEXP,Soul from users where username=\"%s\"", userName);
    //遍历数据库
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //获得数据
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //因为得到的数据是字符串，要把这些数据整数化
    int materialNum[4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; row[i + 6][j]!='\0'; j++) {
            materialNum[i] = materialNum[i] * 10 + (row[i+6][j] - '0');
        }
    }


    //循环收集鼠标信息进行交互
    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //鼠标在规定区域点击时
        case WM_LBUTTONDOWN: {
            //单抽函数
            if (m.x >= 955 && m.x <= 1115 && m.y >= 305 && m.y <= 365) {
                //检查用户的灵魂点数是否够抽卡
                if (materialNum[3] >= 1) {
                    //先扣除用户灵魂点数
                    sprintf(searchCommand, "UPDATE users SET Soul=%d where username=\"%s\"", --materialNum[3], userName);
                    if (mysql_query(conn, searchCommand)) {
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(10);
                    }
                    sprintf(soul, "%d", materialNum[3]);
                    outtextxy(1025, 125, soul);

                    //根据返回值判断抽卡结果并传入抽卡结果
                    result = OnePick();
                    putimage(400, 250, &PMaterial[result]);
                    if (result >= 0 && result < 6) {
                        if (row[result] == NULL) {
                            sprintf(searchCommand, "UPDATE users SET %s=%d where username=\"%s\"", material[result], 1, userName);
                            if (mysql_query(conn, searchCommand)) {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                            }
                        }
                    }
                    else {
                        sprintf(searchCommand, "UPDATE users SET %s=%d where username=\"%s\"", material[result], materialNum[result - 6] = materialNum[result - 6] + 1, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(1);

                        }
                        if (result == 9) {
                            sprintf(soul, "%d", materialNum[3]);
                            outtextxy(1025, 125, soul);
                        }
                    }
                    Sleep(1000);
                    DrawPage(userName);
                }
                else {
                outtextxy(925, 500, "你没有灵魂点数了");
                outtextxy(925, 520, "没用的东西");
                outtextxy(925, 540, "给你两拳！！");
                putimage(350, 200, &PPunch);
                }
            }
            //十连抽函数
            if (m.x >= 955 && m.x <= 1115 && m.y >= 405 && m.y <= 465) {
                //检查灵魂点数是否足够十连
                if (materialNum[3] >= 10) {
                    materialNum[3] -= 10;
                    sprintf(searchCommand, "UPDATE users SET Soul=%d where username=\"%s\"", materialNum[3], userName);
                    if (mysql_query(conn, searchCommand)) {
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(10);
                    }
                    sprintf(soul, "%d", materialNum[3]);
                    outtextxy(1025, 125, soul);
                    for (int y = 180; y < 400; y = y + 200) {
                        for (int x = 90; x < 800; x = x + 160) {
                            int result = OnePick();
                            //根据随机数返回值来得到抽卡结果并传入数据库
                            result = OnePick();
                            putimage(x, y, &PMaterial[result]);
                            if (result >= 0 && result < 6) {
                                if (row[result] == NULL) {
                                    sprintf(searchCommand, "UPDATE users SET %s=%d where username=\"%s\"", material[result], 1, userName);
                                    if (mysql_query(conn, searchCommand)) {
                                        fprintf(stderr, "%s\n", mysql_error(conn));
                                        exit(1);
                                    }
                                }
                            }
                            else {
                                sprintf(searchCommand, "UPDATE users SET %s=%d where username=\"%s\"", material[result], materialNum[result-6]=materialNum[result-6]+1, userName);
                                if (mysql_query(conn, searchCommand)) {
                                    fprintf(stderr, "%s\n", mysql_error(conn));
                                    exit(1);
                                }
                                if (result == 9) {
                                    sprintf(soul, "%d", materialNum[3]);
                                    outtextxy(1025, 125, soul);
                                }
                            }
                        }
                    }
                    Sleep(1000);
                    DrawPage(userName);
                }
                else {
                outtextxy(925, 500, "你没有灵魂点数了");
                outtextxy(925, 520, "没用的东西");
                outtextxy(925, 540, "给你两拳！！");
                putimage(350, 200, &PPunch);
                }
            }
            if (m.x >= 50 && m.x <= 100 && m.y >= 15 && m.y <= 55) {
                HomePage(userName);
            }
        }
                           //鼠标在规定区域划过时的浮动效果
        case WM_MOUSEMOVE: {
            if (m.x >= 955 && m.x <= 1115 && m.y >= 305 && m.y <= 365) {
                putimage(955, 305, &PButtonBackground, SRCAND);
                putimage(955, 305, &PDanChou2, SRCPAINT);
            }
            else if (m.x >= 955 && m.x <= 1115 && m.y >= 405 && m.y <= 465) {
                putimage(955, 405, &PButtonBackground, SRCAND);
                putimage(955, 405, &PShiLian2, SRCPAINT);
            }
            else if (m.x >= 50 && m.x <= 100 && m.y >= 15 && m.y <= 55) {
                putimage(50, 15, &PBacky, SRCAND);
                putimage(50, 15, &PBack2, SRCPAINT);
            }
            else {
                putimage(50, 15, &PBacky, SRCAND);
                putimage(50, 15, &PBack, SRCPAINT);
                putimage(955, 305, &PButtonBackground, SRCAND);
                putimage(955, 305, &PDanChou, SRCPAINT);
                putimage(955, 405, &PButtonBackground, SRCAND);
                putimage(955, 405, &PShiLian, SRCPAINT);

            }
        }
        }
    }
}


//退出界面
void ExitPage() {
    IMAGE PBackGround;
    loadimage(&PBackGround, ".\\img\\background\\退出背景.png", 1200, 600);
    putimage(0, 0, &PBackGround);
    Sleep(1500);
    exit(0);
}


//人物界面：用于实现人物的升级和等级的查询
void CharacPage(char userName[]) {
    struct userCharacter {
        char characName[20];
        int characLevel;
    };

    struct EXP {
        char EXPName[15];
        int EXPNumber;
        int EXPAmount;
    };

    //加载图片和声明变量
    struct userCharacter character[6] = {"",0};
    struct EXP EXPSelect[3];
    EXPSelect[0] = { "smallEXP",1,0 };
    EXPSelect[1] = { "middleEXP",2,0 };
    EXPSelect[2] = { "largeEXP",3,0 };
    int select=3;
    MOUSEMSG m;
    IMAGE PBackGround, PAoErJia, PBily, PKeQin, PDVA, POuHuang, PKeShiFu, Pcxk, PBack, PBack2, PBacky, PLEXP, PMEXP, PSEXP, PBackyB, PLEXPB, PMEXPB, PSEXPB, PFrame, PFrameB, PLEXP2, PMEXP2, PSEXP2, PLEXP3, PMEXP3, PSEXP3;
    char searchCommand[100], updateCommand[100];
    loadimage(&PBackGround, ".\\img\\background\\人物背景.png", 1200, 600);
    loadimage(&POuHuang, ".\\img\\character\\欧皇\\欧皇头像.png", 130, 130);
    loadimage(&PAoErJia, ".\\img\\character\\奥尔加\\奥尔加头像.png", 130, 130);
    loadimage(&PBily, ".\\img\\character\\比利王\\比利王头像.png", 130, 130);
    loadimage(&PKeShiFu, ".\\img\\character\\氪师傅\\氪师傅头像.png", 130, 130);
    loadimage(&PDVA, ".\\img\\character\\DVA\\DVA头像.png", 130, 130);
    loadimage(&Pcxk, ".\\img\\character\\蔡徐坤\\蔡徐坤头像.png", 130, 130);
    loadimage(&PBack, ".\\img\\button\\返回.png", 50, 40);
    loadimage(&PBack2, ".\\img\\button\\返回2.png", 50, 40);
    loadimage(&PBacky, ".\\img\\button\\返回y.png", 50, 40);
    loadimage(&PLEXP, ".\\img\\material\\经验药大.png", 50, 50);
    loadimage(&PMEXP, ".\\img\\material\\经验药中.png", 50, 50);
    loadimage(&PSEXP, ".\\img\\material\\经验药小.png", 50, 50);
    loadimage(&PLEXPB, ".\\img\\material\\经验药大背景.png", 50, 50);
    loadimage(&PMEXPB, ".\\img\\material\\经验药中背景.png", 50, 50);
    loadimage(&PSEXPB, ".\\img\\material\\经验药小背景.png", 50, 50);
    loadimage(&PFrame, ".\\img\\background\\灵魂点数背景框.jpg", 160, 60);
    loadimage(&PFrameB, ".\\img\\background\\灵魂点数背景框y.jpg", 160, 60);
    loadimage(&PLEXP2, ".\\img\\material\\经验药大c.png", 100, 100);
    loadimage(&PMEXP2, ".\\img\\material\\经验药中c.png", 100, 100);
    loadimage(&PSEXP2, ".\\img\\material\\经验药小c.png", 100, 100);
    loadimage(&PLEXP3, ".\\img\\material\\经验药大.png", 100, 100);
    loadimage(&PMEXP3, ".\\img\\material\\经验药中.png", 100, 100);
    loadimage(&PSEXP3, ".\\img\\material\\经验药小.png", 100, 100);


    //定义链接数据库的基本变量
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }



    //放背景图
    putimage(0, 0, &PBackGround);
    putimage(600, 20, &PFrameB, SRCAND);
    putimage(800, 20, &PFrameB, SRCAND);
    putimage(1000, 20, &PFrameB, SRCAND);
    putimage(600, 20, &PFrame, SRCPAINT);
    putimage(800, 20, &PFrame, SRCPAINT);
    putimage(1000, 20, &PFrame, SRCPAINT);
    putimage(1000, 25, &PLEXPB, SRCAND);
    putimage(800, 25, &PMEXPB, SRCAND);
    putimage(600, 25, &PSEXPB, SRCAND);
    putimage(1000, 25, &PLEXP, SRCPAINT);
    putimage(800, 25, &PMEXP, SRCPAINT);
    putimage(600, 25, &PSEXP, SRCPAINT);


   

    //对命令进行操作
    sprintf(searchCommand, "select AoErJia,DVA,cxk,KeShiFu,Bily,OuHuang,smallEXP,middleEXP,largeEXP from users where username=\"%s\"", userName);

    //遍历数据库看人物是否存在
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //获得数据
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //遍历获得数据检查玩家是否拥有人物，拥有则显示
    for (int i = 0, j = 0, x = 100; i < 6; i++, x = x + 170) {
        if (row[i] != NULL) {
            char characLevel[20] = { 0 };
            sprintf(characLevel, "LV:%s", row[i]);
            switch (i) {
                //此处strcpy是给对应显示出的人物图片打上人物编号，方便之后升级操作
            case 0:putimage(x, 100, &PAoErJia); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "AoErJia"); break;
            case 1:putimage(x, 100, &PDVA); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "DVA"); break;
            case 2:putimage(x, 100, &Pcxk); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "cxk"); break;
            case 3:putimage(x, 100, &PKeShiFu); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "KeShiFu"); break;
            case 4:putimage(x, 100, &PBily); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "Bily"); break;
            case 5:putimage(x, 100, &POuHuang); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "OuHuang"); break;
            }
        }
    }

    //图形界面显示大经验 中经验 小经验的数量
    outtextxy(670, 45, row[6]);
    outtextxy(870, 45, row[7]);
    outtextxy(1070, 45, row[8]);

    //放置大中小经验的贴图
    putimage(350, 400, &PSEXP2);
    putimage(550, 400, &PMEXP2);
    putimage(750, 400, &PLEXP2);


    for (int i = 0, characNum = 0; i < 6; i++) {
        //用if判断用户是否拥有该人物
        if (row[i] != NULL) {
            //将人物等级从字符串转化成数字
            for (int j = 0; row[i][j] != '\0'; j++) {
                character[characNum].characLevel = character[characNum].characLevel * 10 + (row[i][j] - '0');
            }
            printf("%d\n", character[characNum].characLevel);
            characNum++;
        }
    }


    for (int i = 6,number=0; i < 9; i++,number++) {
        for (int j = 0; row[i][j] != '\0'; j++) {
            EXPSelect[number].EXPAmount = EXPSelect[number].EXPAmount * 10 + (row[i][j] - '0');
        }
    }

    mysql_free_result(res);


    //循环收集鼠标信息进行交互
    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //鼠标在规定区域点击时做出相应反应
        case WM_LBUTTONDOWN: {
            if (m.x >= 50 && m.x <= 100 && m.y >= 15 && m.y <= 55) {
                HomePage(userName);
            }
            if (m.x >= 350 && m.x <= 450 && m.y >= 400 && m.y <= 500) {
                //用户根据点击来选择经验药
                putimage(350, 400, &PSEXP3);
                putimage(550, 400, &PMEXP2);
                putimage(750, 400, &PLEXP2);
                select = 0;
            }
            if (m.x >= 550 && m.x <= 650 && m.y >= 400 && m.y <= 500) {
                //用户根据点击来选择经验药
                putimage(350, 400, &PSEXP2);
                putimage(550, 400, &PMEXP3);
                putimage(750, 400, &PLEXP2);
                select = 1;
            }
            if (m.x >= 750 && m.x <= 850 && m.y >= 400 && m.y <= 500) {
                //用户根据点击来选择经验药
                putimage(350, 400, &PSEXP2);
                putimage(550, 400, &PMEXP2);
                putimage(750, 400, &PLEXP3);
                select = 2;
            }
            if (m.x >= 100 && m.x <= 200 && m.y >= 100 && m.y <= 200) {
                if (character[0].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    //检查用户经验药是否足够
                    if (EXPSelect[select].EXPAmount > 0) {
                        //用户升级
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[0].characName, character[0].characLevel = character[0].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
    
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //实时获取人物等级
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[0].characName,EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }
                        //获得数据
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);
                        //实时显示数据
                        ShowCharacter(row[0], row[1], select, 0);
                    }
                    else outtextxy(565, 300, "物品不足");
                }
            }
            if (m.x >= 270 && m.x <= 370 && m.y >= 100 && m.y <= 200) {
                if (character[1].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    if (EXPSelect[select].EXPAmount > 0) {
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[1].characName, character[1].characLevel = character[1].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //实时获取人物等级
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[1].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //获得数据
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //实时显示数据
                        ShowCharacter(row[0], row[1], select, 1);
                    }
                    else outtextxy(565, 300, "物品不足");
                }
            }
            if (m.x >= 440 && m.x <= 540 && m.y >= 100 && m.y <= 200) {
                if (character[2].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    if (EXPSelect[select].EXPAmount > 0) {
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[2].characName, character[2].characLevel = character[2].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //实时获取人物等级
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[2].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //获得数据
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //实时显示数据
                        ShowCharacter(row[0], row[1], select, 2);
                    }
                    else outtextxy(440, 300, "物品不足");
                }
            }
            if (m.x >= 610 && m.x <= 710 && m.y >= 100 && m.y <= 200) {
                if (character[3].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    if (EXPSelect[select].EXPAmount > 0) {
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[3].characName, character[3].characLevel = character[3].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //实时获取人物等级
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[3].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }
                        //获得数据
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //实时显示数据
                        ShowCharacter(row[0], row[1], select, 3);
                    }
                    else outtextxy(565, 300, "物品不足");
                }
            }
            if (m.x >= 780 && m.x <= 880 && m.y >= 100 && m.y <= 200) {
                if (character[4].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    if (EXPSelect[select].EXPAmount > 0) {
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[4].characName, character[4].characLevel = character[4].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //实时获取人物等级
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[4].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //获得数据
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //实时显示数据
                        ShowCharacter(row[0], row[1], select, 4);
                    }
                    else outtextxy(565, 300, "物品不足");
                }
            }
            if (m.x >= 950 && m.x <= 1050 && m.y >= 100 && m.y <= 200) {
                if (character[5].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    if (EXPSelect[select].EXPAmount > 0) {
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[5].characName, character[5].characLevel = character[5].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //实时获取人物等级
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[5].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }
                        //获得数据
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //实时显示数据
                        ShowCharacter(row[0], row[1], select, 5);
                    }
                    else outtextxy(565, 300, "物品不足");
                }
            }


            //鼠标在规定区域划过时
        case WM_MOUSEMOVE: {
            if (m.x >= 50 && m.x <= 100 && m.y >= 15 && m.y <= 55) {
                putimage(50, 15, &PBacky, SRCAND);
                putimage(50, 15, &PBack2, SRCPAINT);
            }
            else {
                putimage(50, 15, &PBacky, SRCAND);
                putimage(50, 15, &PBack, SRCPAINT);
            }
        }
        }
        }
    }
}


//战斗之前的地图界面
void MapPage(char userName[]) {

    srand(time(0));
    //定义临时变量
    int i, xchange = 0, ychange = 0, j, x, y;

    //定义地图数组
    struct mapinformation {
        bool walkable;
        int active;
    };
    struct mapinformation map[31][16];
    //定义地图
    for (i = 0; i < 31; i++) {
        for (j = 0; j < 16; j++) {
            map[i][j].walkable = false;
            map[i][j].active = 2;
        }
    }


    int EXPAmount = 0;
    char searchCommand[150] = { 0 }, updateCommand[150] = { 0 };

    //有交互的方块的定义
    map[8][9].active = rand()%2;
    map[11][1].active = rand() % 2;
    map[5][6].active = rand() % 2;
    map[14][8].active = rand() % 2;
    map[1][1].walkable = false;
    map[30][5].active = 4;
    map[29][5].active = 4;
    map[30][6].active = 4;


    //可行走方块定义
    map[4][5].walkable = true;
    map[15][5].walkable = true;
    map[14][6].walkable = true;
    map[13][7].walkable = true;
    map[5][6].walkable = true;
    map[14][8].walkable = true;
    map[0][1].walkable = true;
    map[1][1].walkable = true;
    map[2][1].walkable = true;
    map[2][2].walkable = true;
    map[2][3].walkable = true;
    map[1][3].walkable = true;
    map[1][4].walkable = true;
    map[2][4].walkable = true;
    map[1][5].walkable = true;
    map[1][6].walkable = true;
    map[2][6].walkable = true;
    map[3][6].walkable = true;
    map[3][7].walkable = true;
    map[3][8].walkable = true;
    map[1][8].walkable = true;
    map[1][9].walkable = true;
    map[3][9].walkable = true;
    map[1][10].walkable = true;
    map[3][10].walkable = true;
    map[4][10].walkable = true;
    map[5][10].walkable = true;
    map[6][10].walkable = true;
    map[1][11].walkable = true;
    map[2][11].walkable = true;
    map[3][11].walkable = true;
    map[3][12].walkable = true;
    map[1][13].walkable = true;
    map[2][13].walkable = true;
    map[3][13].walkable = true;
    map[1][14].walkable = true;
    map[3][14].walkable = true;
    map[4][14].walkable = true;
    map[5][14].walkable = true;
    map[5][13].walkable = true;
    map[6][13].walkable = true;
    map[6][1].walkable = true;
    map[5][1].walkable = true;
    map[4][1].walkable = true;
    map[16][11].walkable = true;
    map[6][9].walkable = true;
    map[6][8].walkable = true;
    map[6][12].walkable = true;
    map[7][12].walkable = true;
    map[7][11].walkable = true;
    map[8][12].walkable = true;
    map[9][12].walkable = true;
    map[9][13].walkable = true;
    map[9][14].walkable = true;
    map[10][14].walkable = true;
    map[11][14].walkable = true;
    map[11][13].walkable = true;
    map[11][12].walkable = true;
    map[11][11].walkable = true;
    map[11][10].walkable = true;
    map[10][10].walkable = true;
    map[9][10].walkable = true;
    map[8][9].walkable = true;
    map[11][9].walkable = true;
    map[11][8].walkable = true;
    map[11][7].walkable = true;
    map[10][7].walkable = true;
    map[10][6].walkable = true;
    map[9][6].walkable = true;
    map[8][6].walkable = true;
    map[7][6].walkable = true;
    map[7][5].walkable = true;
    map[7][4].walkable = true;
    map[7][3].walkable = true;
    map[7][2].walkable = true;
    map[7][1].walkable = true;
    map[8][3].walkable = true;
    map[9][3].walkable = true;
    map[9][4].walkable = true;
    map[10][3].walkable = true;
    map[11][3].walkable = true;
    map[11][4].walkable = true;
    map[11][1].walkable = true;
    map[12][3].walkable = true;
    map[12][2].walkable = true;
    map[13][1].walkable = true;
    map[13][3].walkable = true;
    map[13][4].walkable = true;
    map[14][3].walkable = true;
    map[15][3].walkable = true;
    map[15][2].walkable = true;
    map[15][1].walkable = true;
    map[16][3].walkable = true;
    map[16][4].walkable = true;
    map[16][5].walkable = true;
    map[16][1].walkable = true;
    map[17][1].walkable = true;
    map[18][1].walkable = true;
    map[19][1].walkable = true;
    map[19][2].walkable = true;
    map[19][3].walkable = true;
    map[20][2].walkable = true;
    map[20][3].walkable = true;
    map[20][4].walkable = true;
    map[20][5].walkable = true;
    map[19][5].walkable = true;
    map[21][4].walkable = true;
    map[21][5].walkable = true;
    map[22][4].walkable = true;
    map[22][3].walkable = true;
    map[23][3].walkable = true;
    map[23][2].walkable = true;
    map[24][2].walkable = true;
    map[25][2].walkable = true;
    map[25][1].walkable = true;
    map[26][1].walkable = true;
    map[27][1].walkable = true;
    map[28][1].walkable = true;
    map[29][1].walkable = true;
    map[28][2].walkable = true;
    map[29][2].walkable = true;
    map[21][6].walkable = true;
    map[21][7].walkable = true;
    map[21][8].walkable = true;
    map[21][9].walkable = true;
    map[20][9].walkable = true;
    map[20][10].walkable = true;
    map[20][11].walkable = true;
    map[19][11].walkable = true;
    map[18][11].walkable = true;
    map[18][10].walkable = true;
    map[18][9].walkable = true;
    map[17][11].walkable = true;
    map[16][6].walkable = true;
    map[16][7].walkable = true;
    map[16][6].walkable = true;
    map[17][7].walkable = true;
    map[17][11].walkable = true;
    map[15][11].walkable = true;
    map[15][12].walkable = true;
    map[15][13].walkable = true;
    map[14][13].walkable = true;
    map[13][13].walkable = true;
    map[17][12].walkable = true;
    map[17][13].walkable = true;
    map[18][13].walkable = true;
    map[19][13].walkable = true;
    map[19][14].walkable = true;
    map[20][14].walkable = true;
    map[21][14].walkable = true;
    map[22][14].walkable = true;
    map[23][14].walkable = true;
    map[23][13].walkable = true;
    map[23][12].walkable = true;
    map[24][13].walkable = true;
    map[24][12].walkable = true;
    map[24][11].walkable = true;
    map[24][10].walkable = true;
    map[25][10].walkable = true;
    map[25][9].walkable = true;
    map[25][8].walkable = true;
    map[26][8].walkable = true;
    map[27][8].walkable = true;
    map[27][9].walkable = true;
    map[27][10].walkable = true;
    map[27][11].walkable = true;
    map[27][12].walkable = true;
    map[26][12].walkable = true;
    map[26][13].walkable = true;
    map[26][14].walkable = true;
    map[27][14].walkable = true;
    map[28][14].walkable = true;
    map[29][14].walkable = true;
    map[29][13].walkable = true;
    map[29][12].walkable = true;
    map[29][11].walkable = true;
    map[29][10].walkable = true;
    map[29][9].walkable = true;
    map[29][8].walkable = true;
    map[29][7].walkable = true;
    map[29][6].walkable = true;
    map[30][6].walkable = true;
    map[29][5].walkable = true;
    map[30][5].walkable = true;
    //定义图像截取坐标
    int xback = 0, yback = 0;
    //定义人物中心坐标
    int xchara = 241, ychara = 121;
    //定义背景图数组
    IMAGE background;
    //定义人物图数组
    IMAGE chara[charatotalnum];
    IMAGE charay[charatotalnum];
    //加载图片
    //加载图片
    loadimage(&chara[0], ".\\img\\character\\奥尔加\\1.jpg", 256, 128);
    loadimage(&chara[1], ".\\img\\character\\奥尔加\\2.jpg", 256, 128);
    loadimage(&chara[2], ".\\img\\character\\奥尔加\\3.jpg", 256, 128);
    loadimage(&chara[3], ".\\img\\character\\奥尔加\\4.jpg", 256, 128);
    loadimage(&chara[4], ".\\img\\character\\奥尔加\\5.jpg", 256, 128);
    loadimage(&chara[5], ".\\img\\character\\奥尔加\\6.jpg", 256, 128);
    loadimage(&chara[6], ".\\img\\character\\奥尔加\\7.jpg", 256, 128);
    loadimage(&chara[7], ".\\img\\character\\奥尔加\\8.jpg", 256, 128);

    loadimage(&charay[0], ".\\img\\character\\奥尔加\\1y.jpg", 256, 128);
    loadimage(&charay[1], ".\\img\\character\\奥尔加\\2y.jpg", 256, 128);
    loadimage(&charay[2], ".\\img\\character\\奥尔加\\3y.jpg", 256, 128);
    loadimage(&charay[3], ".\\img\\character\\奥尔加\\4y.jpg", 256, 128);
    loadimage(&charay[4], ".\\img\\character\\奥尔加\\5y.jpg", 256, 128);
    loadimage(&charay[5], ".\\img\\character\\奥尔加\\6y.jpg", 256, 128);
    loadimage(&charay[6], ".\\img\\character\\奥尔加\\7y.jpg", 256, 128);
    loadimage(&charay[7], ".\\img\\character\\奥尔加\\8y.jpg", 256, 128);

    loadimage(&background, ".\\img\\background\\地图背景.png", 3720, 1920);


    //放置初始图片
    initgraph(1200, 600);
    putimage(0, 0, &background);
    //putimage(600, 300, &charay[0], SRCAND);
    //putimage(600, 300, &chara[0], SRCPAINT);

    //定义链接数据库的基本变量
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //对命令进行操作
    sprintf(searchCommand, "select smallEXP from users where username=\"%s\"", userName);

    //遍历数据库查看小经验数量是否存在
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //获得数据
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //将字符串转化成整数
    for (int i = 0; row[0][i] != 0; i++) {
        EXPAmount = EXPAmount * 10 + (row[0][i] - '0');
    }

    for (i = 0; 1; i++) {
        if (i == 71) {
            i = 0;
        }
        //获取键盘操作
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)//左
            xchange = -1;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//右
            xchange = 1;
        if (GetAsyncKeyState(VK_UP) & 0x8000)//上
            ychange = -1;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)//下
            ychange = 1;
        xchara += xchange;
        ychara += ychange;
        xback += xchange;
        yback += ychange;
        //判断人物是否在界面核心区域
        x = (xchara + xback) / 120;
        y = (ychara + yback) / 120;
        if (map[x][y].walkable) {
            if (xchara >= 240 && xchara <= 960) {
                xback -= xchange;
            }
            else {
                xchara -= xchange;
            }
            if (ychara >= 120 && ychara <= 480) {
                yback -= ychange;
            }
            else {
                ychara -= ychange;
            }
        }
        else {
            xchara -= xchange;
            ychara -= ychange;
            xback -= xchange;
            yback -= ychange;
        }
        switch (map[x][y].active) {
        case 0:
            map[x][y].active = 2;
            xchara = 241, ychara = 121;
            xback = 0, yback = 0;
            break;
        case 1:
            map[x][y].active = 2;
            sprintf(updateCommand, "UPDATE users SET smallEXP=%d where username=\"%s\"", EXPAmount=EXPAmount+1, userName);
            if (mysql_query(conn, updateCommand)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(0);
            }
            break;
        case 4:
            CharacSelect(userName);
        }
        cleardevice();
        putimage(0, 0, 1200, 1200, &background, xback, yback);
        putimage(xchara - 128, ychara - 72, &charay[i / 10], SRCAND);
        putimage(xchara - 128, ychara - 72, &chara[i / 10], SRCPAINT);
        xchange = 0;
        ychange = 0;
        Sleep(2);
    }
}


//在地图中遭遇boss选择玩家已有人物的函数
void CharacSelect(char userName[]) {
    struct userCharacter {
        char characName[20];
        int characLevel;
        int characNumber;
    };

    MOUSEMSG m;
    IMAGE PBackGround, PAoErJia, PBily, PKeQin, PDVA, POuHuang, PKeShiFu, Pcxk, PBack, PBack2, PBacky;
    char searchCommand[150] = { 0 };
    struct userCharacter character[6] = { "",0 };

    loadimage(&PBackGround, ".\\img\\background\\人物背景.png", 1200, 600);
    loadimage(&POuHuang, ".\\img\\character\\欧皇\\欧皇头像.png", 130, 130);
    loadimage(&PAoErJia, ".\\img\\character\\奥尔加\\奥尔加头像.png", 130, 130);
    loadimage(&PBily, ".\\img\\character\\比利王\\比利王头像.png", 130, 130);
    loadimage(&PKeShiFu, ".\\img\\character\\氪师傅\\氪师傅头像.png", 130, 130);
    loadimage(&PDVA, ".\\img\\character\\DVA\\DVA头像.png", 130, 130);
    loadimage(&Pcxk, ".\\img\\character\\蔡徐坤\\蔡徐坤头像.png", 130, 130);
    loadimage(&PBack, ".\\img\\button\\返回.png", 50, 40);
    loadimage(&PBack2, ".\\img\\button\\返回2.png", 50, 40);
    loadimage(&PBacky, ".\\img\\button\\返回y.png", 50, 40);

    //放背景图
    putimage(0, 0, &PBackGround);

    //定义链接数据库的基本变量
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }


    //对命令进行操作
    sprintf(searchCommand, "select AoErJia,DVA,cxk,KeShiFu,Bily,OuHuang from users where username=\"%s\"", userName);

    //遍历数据库看人物是否存在
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //获得数据
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //遍历获得数据检查玩家是否拥有人物，拥有则显示
    for (int i = 0, j = 0, x = 100; i < 6; i++, x = x + 170) {
        if (row[i] != NULL) {
            char characLevel[20] = { 0 };
            sprintf(characLevel, "LV:%s", row[i]);
            switch (i) {
                //此处strcpy是给对应显示出的人物图片打上人物编号，方便之后升级操作
            case 0:putimage(x, 100, &PAoErJia); outtextxy(x, 100, characLevel); character[j].characNumber = 0; strcpy(character[j++].characName, "AoErJia"); break;
            case 1:putimage(x, 100, &PDVA); outtextxy(x, 100, characLevel); character[j].characNumber = 1; strcpy(character[j++].characName, "DVA"); break;
            case 2:putimage(x, 100, &Pcxk); outtextxy(x, 100, characLevel); character[j].characNumber = 2; strcpy(character[j++].characName, "cxk"); break;
            case 3:putimage(x, 100, &PKeShiFu); outtextxy(x, 100, characLevel); character[j].characNumber = 3; strcpy(character[j++].characName, "KeShiFu"); break;
            case 4:putimage(x, 100, &PBily); outtextxy(x, 100, characLevel); character[j].characNumber = 4; strcpy(character[j++].characName, "Bily"); break;
            case 5:putimage(x, 100, &POuHuang); outtextxy(x, 100, characLevel); character[j].characNumber = 5; strcpy(character[j++].characName, "OuHuang"); break;
            }
        }
    }

    //将用户拥有的每个角色从数据库中获取的等级字符串转化成整数
    for (int i = 0, characNum = 0; i < 6; i++) {
        //用if判断用户是否拥有该人物
        if (row[i] != NULL) {
            //将人物等级从字符串转化成数字
            for (int j = 0; row[i][j] != '\0'; j++) {
                character[characNum].characLevel = character[characNum].characLevel * 10 + (row[i][j] - '0');
            }
            characNum++;
        }
    }

    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //鼠标在规定区域点击时做出相应反应
        case WM_LBUTTONDOWN: {
            if (m.x >= 100 && m.x <= 200 && m.y >= 100 && m.y <= 200) {
                //检查用户是否拥有该人物
                if (character[0].characName[0] != 0) {
                    BattlePage(userName, character[0].characNumber, character[0].characLevel);
                }
            }
            if (m.x >= 270 && m.x <= 370 && m.y >= 100 && m.y <= 200) {
                if (character[1].characName[0] != 0) {
                    BattlePage(userName,character[1].characNumber, character[1].characLevel);
                }
            }
            if (m.x >= 440 && m.x <= 540 && m.y >= 100 && m.y <= 200) {
                if (character[2].characName[0] != 0) {
                    BattlePage(userName,character[2].characNumber, character[2].characLevel);
                }
            }
            if (m.x >= 610 && m.x <= 710 && m.y >= 100 && m.y <= 200) {
                if (character[3].characName[0] != 0) {
                    BattlePage(userName, character[3].characNumber, character[3].characLevel);
                }
            }
            if (m.x >= 780 && m.x <= 880 && m.y >= 100 && m.y <= 200) {
                if (character[4].characName[0] != 0) {
                    BattlePage(userName, character[4].characNumber, character[4].characLevel);
                }
            }
            if (m.x >= 950 && m.x <= 1050 && m.y >= 100 && m.y <= 200) {
                if (character[5].characName[0] != 0) {
                    BattlePage(userName, character[5].characNumber, character[5].characLevel);
                }
            }
        }
        }
    }
}


//战斗界面
void BattlePage(char userName[], const int characNum, int characterLevel) {
    struct userInform {
        int Soul;
        int smallEXP;
        int character;
        int tower;
    };

    int random;
    struct userInform userInform = { 0 ,0 ,0 ,0 };
    struct characterInform characInform = { 0 , 0 , 0 };
    char updateCommand[150];
    char battleInform[150];
    char characName[6][15] = { "AoErJia","DVA","cxk","KeShiFu","Bily","OuHuang" };
    char bossName[10][15] = { "香蕉君","van","魔男","债务处理人","niko","simple","茄子","派蒙","马保国","微积分" };
    char battleInformation[100];


    bool CRound = true;
    char number[40];
    int i, size = 300, j, ch[3] = {0};//定义临时变量
    int zhaoshi = 0;
    double  CMHp = 0, CMMp = 0, CDamage = 0, BMHp = 0, BHp = 0, BDamage = 0;//分别为人物最大生命值，最大技能点，人物造成伤害，怪物最大生命值，怪物生命值，怪物造成伤害
    int pnum[6][3];   //大招人物及帧数
    char searchCommand[150] = { 0 };
    char characterName[6][20] = { "AoErJia","DVA","cxk","KeShiFu","Bily","OuHuang" };

    //定义链接数据库的基本变量
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }


    //对命令进行操作
    sprintf(searchCommand, "select tower,smallEXP,Soul from users where username=\"%s\"", userName);

    //遍历数据库看人物是否存在
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //获得数据
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //得到用户的材料信息，并且初始化人物和怪物的初始属性
    userInform.tower = GetInt(row[0]);
    userInform.character = characNum;
    userInform.smallEXP = GetInt(row[1]);
    userInform.Soul = GetInt(row[2]);
    CharacterAbility(userInform.character, characterLevel);
    BossAbility(userInform.tower);
    characInform = GetCharacInform();
    CMHp = characInform.Hp;
    CMMp = characInform.Mp;
    BMHp = GetBossHp();
    BHp = GetBossHp();
    int bossnum = userInform.tower % 10;

    //定义鼠标
    MOUSEMSG m;

    //定义图像
    IMAGE backgroundfight, choise[2], dazhao[2], dazhaoy, blood, bloody, lan, lany, die;
    IMAGE chara[6][3][12], charay[6][3][12], boss[10][2],victory[6];

    //加载图像
    loadimage(&choise[0], ".\\img\\battle\\框框.jpg", 300, 100);
    loadimage(&choise[1], ".\\img\\battle\\框框1.jpg", 300, 100);
    loadimage(&dazhao[0], ".\\img\\battle\\大招.jpg", 200, 200);
    loadimage(&dazhao[1], ".\\img\\battle\\大招1.jpg", 200, 200);
    loadimage(&dazhaoy, ".\\img\\battle\\大招y.jpg", 200, 200);
    loadimage(&backgroundfight, ".\\img\\battle\\backgroundfight.png", 1200, 600);
    loadimage(&chara[1][0][0], ".\\img\\battle\\DVA.png", size, size);
    loadimage(&chara[1][1][0], ".\\img\\battle\\DVA.png", size, size);
    loadimage(&chara[1][2][0], ".\\img\\battle\\DVA.png", size, size);
    loadimage(&chara[0][0][0], ".\\img\\battle\\奥尔加.png", size, size);
    loadimage(&chara[4][0][0], ".\\img\\battle\\比利王.png", size, size);
    loadimage(&chara[4][1][0], ".\\img\\battle\\比利王.png", size, size);
    loadimage(&chara[4][2][0], ".\\img\\battle\\比利王.png", size, size);
    loadimage(&chara[2][0][0], ".\\img\\battle\\蔡徐坤.png", size, size);
    loadimage(&chara[3][0][0], ".\\img\\battle\\氪师傅.png", size, size);
    loadimage(&chara[3][1][0], ".\\img\\battle\\氪师傅.png", size, size);
    loadimage(&chara[3][2][0], ".\\img\\battle\\氪师傅.png", size, size);
    loadimage(&chara[5][0][0], ".\\img\\battle\\欧皇.png", size, size);
    loadimage(&chara[5][1][0], ".\\img\\battle\\欧皇.png", size, size);
    loadimage(&chara[5][2][0], ".\\img\\battle\\欧皇.png", size, size);
    loadimage(&charay[1][0][0], ".\\img\\battle\\DVA背景.png", size, size);
    loadimage(&charay[1][1][0], ".\\img\\battle\\DVA背景.png", size, size);
    loadimage(&charay[1][2][0], ".\\img\\battle\\DVA背景.png", size, size);
    loadimage(&charay[0][0][0], ".\\img\\battle\\奥尔加背景.png", size, size);
    loadimage(&charay[4][0][0], ".\\img\\battle\\比利王背景.png", size, size);
    loadimage(&charay[4][1][0], ".\\img\\battle\\比利王背景.png", size, size);
    loadimage(&charay[4][2][0], ".\\img\\battle\\比利王背景.png", size, size);
    loadimage(&charay[2][0][0], ".\\img\\battle\\蔡徐坤背景.png", size, size);
    loadimage(&charay[3][0][0], ".\\img\\battle\\氪师傅背景.png", size, size);
    loadimage(&charay[3][1][0], ".\\img\\battle\\氪师傅背景.png", size, size);
    loadimage(&charay[3][2][0], ".\\img\\battle\\氪师傅背景.png", size, size);
    loadimage(&charay[5][0][0], ".\\img\\battle\\欧皇背景.png", size, size);
    loadimage(&charay[5][1][0], ".\\img\\battle\\欧皇背景.png", size, size);
    loadimage(&charay[5][2][0], ".\\img\\battle\\欧皇背景.png", size, size);
    loadimage(&boss[0][0], ".\\img\\battle\\xj1.jpg", size, size);
    loadimage(&boss[1][0], ".\\img\\battle\\vn1.jpg", size, size);
    loadimage(&boss[2][0], ".\\img\\battle\\mf1.jpg", size, size);
    loadimage(&boss[3][0], ".\\img\\battle\\zw1.jpg", size, size);
    loadimage(&boss[4][0], ".\\img\\battle\\nk1.jpg", size, size);
    loadimage(&boss[5][0], ".\\img\\battle\\sm1.jpg", size, size);
    loadimage(&boss[6][0], ".\\img\\battle\\qz1.jpg", size, size);
    loadimage(&boss[7][0], ".\\img\\battle\\pm1.jpg", size, size);
    loadimage(&boss[8][0], ".\\img\\battle\\mb1.jpg", size, size);
    loadimage(&boss[9][0], ".\\img\\battle\\wj1.jpg", size, size);
    loadimage(&boss[0][1], ".\\img\\battle\\xj1y.jpg", size, size);
    loadimage(&boss[1][1], ".\\img\\battle\\vn1y.jpg", size, size);
    loadimage(&boss[2][1], ".\\img\\battle\\mf1y.jpg", size, size);
    loadimage(&boss[3][1], ".\\img\\battle\\zw1y.jpg", size, size);
    loadimage(&boss[4][1], ".\\img\\battle\\nk1y.jpg", size, size);
    loadimage(&boss[5][1], ".\\img\\battle\\sm1y.jpg", size, size);
    loadimage(&boss[6][1], ".\\img\\battle\\qz1y.jpg", size, size);
    loadimage(&boss[7][1], ".\\img\\battle\\pm1y.jpg", size, size);
    loadimage(&boss[8][1], ".\\img\\battle\\mb1y.jpg", size, size);
    loadimage(&boss[9][1], ".\\img\\battle\\wj1y.jpg", size, size);

    loadimage(&die, ".\\img\\battle\\团长死亡.jpg", 1200, 600);

    loadimage(&bloody, ".\\img\\battle\\血条y.jpg", 300, 50);
    loadimage(&blood, ".\\img\\battle\\血条.jpg", 300, 50);
    loadimage(&lany, ".\\img\\battle\\蓝条y.jpg", 300, 20);
    loadimage(&lan, ".\\img\\battle\\蓝条.jpg", 300, 20);

    //导入招式动画
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            pnum[i][j] = 1;
        }
    }
    for (i = 0; i < 12; i++) {
        sprintf(number, ".\\img\\battle\\已完成(2)\\%d.jpg", i + 1);
        loadimage(&chara[2][1][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\已完成(2)\\%dy.jpg", i + 1);
        loadimage(&charay[2][1][i], number, 640, 360);
    }
    pnum[2][1] = 12;//招式动画帧数
    for (i = 0; i < 7; i++) {
        sprintf(number, ".\\img\\battle\\已完成(3)\\%d.jpg", i + 1);
        loadimage(&chara[2][2][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\已完成(3)\\%dy.jpg", i + 1);
        loadimage(&charay[2][2][i], number, 640, 360);
    }
    pnum[2][2] = 7;//招式动画帧数
    for (i = 0; i < 8; i++) {
        sprintf(number, ".\\img\\battle\\已完成(4)\\%d.jpg", i + 1);
        loadimage(&chara[0][2][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\已完成(4)\\%dy.jpg", i + 1);
        loadimage(&charay[0][2][i], number, 640, 360);
    }
    pnum[0][2] = 8;//招式动画帧数
    for (i = 0; i < 4; i++) {
        sprintf(number, ".\\img\\battle\\已完成(5)\\%d.jpg", i + 1);
        loadimage(&chara[0][1][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\已完成(5)\\%dy.jpg", i + 1);
        loadimage(&charay[0][1][i], number, 640, 360);
    }
    pnum[0][1] = 4;//招式动画帧数
    for (i = 0; i < 5; i++) {
        sprintf(number, ".\\img\\battle\\已完成(6)\\%d.jpg", i + 1);
        loadimage(&chara[1][2][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\已完成(6)\\%dy.jpg", i + 1);
        loadimage(&charay[1][2][i], number, 640, 360);
    }
    pnum[1][2] = 5;//招式动画帧数

    //导入胜利动画
    for (i = 0; i < 6; i++) {
        sprintf(number, ".\\img\\battle\\已完成(7)\\%d.png", i + 1);
        loadimage(&victory[i], number, 1200, 600);
    }

    loadimage(&chara[3][1][0], ".\\img\\battle\\kq1.jpg", 640, 360);
    loadimage(&charay[3][1][0], ".\\img\\battle\\kq1y.jpg", 640, 360);
    loadimage(&chara[3][2][0], ".\\img\\battle\\kq2.jpg", 640, 360);
    loadimage(&charay[3][2][0], ".\\img\\battle\\kq2y.jpg", 640, 360);
    loadimage(&chara[4][1][0], ".\\img\\battle\\bl1.jpg", 640, 360);
    loadimage(&charay[4][1][0], ".\\img\\battle\\bl1y.jpg", 640, 360);
    loadimage(&chara[4][2][0], ".\\img\\battle\\bl2.jpg", 640, 360);
    loadimage(&charay[4][2][0], ".\\img\\battle\\bl2y.jpg", 640, 360);
    loadimage(&chara[3][1][1], ".\\img\\battle\\kq1.jpg", 640, 360);
    loadimage(&charay[3][1][1], ".\\img\\battle\\kq1y.jpg", 640, 360);
    loadimage(&chara[3][2][1], ".\\img\\battle\\kq2.jpg", 640, 360);
    loadimage(&charay[3][2][1], ".\\img\\battle\\kq2y.jpg", 640, 360);
    loadimage(&chara[4][1][1], ".\\img\\battle\\bl1.jpg", 640, 360);
    loadimage(&charay[4][1][1], ".\\img\\battle\\bl1y.jpg", 640, 360);
    loadimage(&chara[4][2][1], ".\\img\\battle\\bl2.jpg", 640, 360);
    loadimage(&charay[4][2][1], ".\\img\\battle\\bl2y.jpg", 640, 360);
    pnum[3][1] = 2;
    pnum[3][2] = 2;
    pnum[4][1] = 2;
    pnum[4][2] = 2;

    //换出图像框
    initgraph(1200, 600);
    cleardevice();

    //放置初始图像
    putimage(0, 0, 1200, 600, &backgroundfight, 0, 0);
    putimage(100, 0, &charay[characNum][0][0], SRCAND);
    putimage(100, 0, &chara[characNum][0][0], SRCPAINT);
    putimage(200, 500, &choise[0]);
    putimage(500, 500, &choise[0]);
    putimage(0, 400, &dazhaoy, SRCAND);
    putimage(0, 400, &dazhao[0], SRCPAINT);

    i = 0;//零时循环变量


   
    //战斗过程中的图像循环
    while (1) {
        cleardevice();
        putimage(0, 0, 1200, 600, &backgroundfight, 0, 0);//贴背景
        //贴选项框
        putimage(200, 500, &choise[ch[1]]);
        putimage(500, 500, &choise[ch[0]]);
        putimage(0, 400, &dazhaoy, SRCAND);
        putimage(0, 400, &dazhao[ch[2]], SRCPAINT);
        //贴人物图像（静止和动画）
        putimage(100 + j, 100, &charay[characNum][zhaoshi][i], SRCAND);
        putimage(100 + j, 100, &chara[characNum][zhaoshi][i], SRCPAINT);
        //贴Boss图像
        putimage(800 - j, 100, &boss[bossnum][1], SRCAND);
        putimage(800 - j, 100, &boss[bossnum][0], SRCPAINT);
        //贴血条与蓝条
        putimage(100, 50, 300, 30, &bloody, 0, 0);
        putimage(100, 70, 300, 4, &lany, 0, 0);
        putimage(800, 50, 300, 30, &bloody, 0, 0);
        putimage(100, 50, characInform.Hp / CMHp * 300, 30, &blood, 0, 0);
        putimage(800, 50, BHp / BMHp * 300, 30, &blood, 0, 0);
        putimage(100, 70, characInform.Mp / CMMp * 300, 4, &lan, 0, 0);

        
        ch[0] = 0;
        ch[1] = 0;
        ch[2] = 0;

        //判断是否是在人物动画期间
        if (zhaoshi != 0) {
            Sleep(500);
        }
        else {
            //判断boss是否已经被击杀
            if (BHp <= 0) {
                //胜利特效
                mciSendString("open .\\img\\battle\\胜利.mp3 alias bkmusic", NULL, 0, NULL);
                mciSendString("play bkmusic", NULL, 0, NULL);
                for (i = 0; i < 10; i++) {
                    for (int j = 0; j < 6; j++) {
                        putimage(0, 0, 1200, 600, &victory[j], 0, 0);
                        Sleep(100);
                    }
                }
                //奖励进入数据库
                sprintf(updateCommand, "UPDATE users SET smallEXP=%d,Soul=%d,tower=%d,%s=%d WHERE username=\"%s\"", userInform.smallEXP = userInform.smallEXP + 1, userInform.Soul = userInform.Soul + 1, userInform.tower = userInform.tower + 1, characName[characNum], characterLevel = characterLevel + 1, userName);;
                if (mysql_query(conn, updateCommand)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(0);
                }
                mciSendString("close bkmusic", NULL, 0, NULL);
                HomePage(userName);
            }

            //判断玩家是否已经被击杀
            if (characInform.Hp <= 0) {
                //玩家死亡特效
                putimage(0, 0, &die);//播放图片
                //播放音乐
                mciSendString("open .\\img\\battle\\团长死亡.mp3 alias bkmusic", NULL, 0, NULL);
                mciSendString("play bkmusic", NULL, 0, NULL);
                //让音乐播放期间不退回到主界面
                Sleep(7000);
                mciSendString("close bkmusic", NULL, 0, NULL);
                //回到主界面
                HomePage(userName);

            }
            if (CRound) {//判断是否是人物回合
                m = GetMouseMsg();//获取鼠标操作
                switch (m.uMsg) {
                case WM_LBUTTONDOWN: {//监视鼠标左键是否按下

                    //角色使用大招
                    if (m.x <= 200 && m.x >= 0 && m.y >= 400 && m.y <= 600) {
                        CharacSkill3(userInform.character);
                        characInform = GetCharacInform();
                        BHp -= characInform.damage;
                        SetBossHp(BHp);
                        zhaoshi = 2;
                    }

                    //角色使用技能
                    if (m.x >= 200 && m.x <= 500 && m.y >= 500 && m.y <= 600) {
                        CharacSkill2(userInform.character);
                        characInform = GetCharacInform();
                        BHp -= characInform.damage;
                        SetBossHp(BHp);
                        zhaoshi = 1;
                    }

                    //角色使用普通攻击
                    if (m.x >= 500 && m.x <= 800 && m.y >= 500 && m.y <= 600) {//普攻（0）被按下
                        CharacSkill1(userInform.character);
                        characInform = GetCharacInform();
                        BHp -= characInform.damage;
                        SetBossHp(BHp);
                        zhaoshi = 0;
                    }
                    j = 10;//动作位移
                    CRound = false;//切换为Boss回合
                    break;
                }
                default: {
                    j = 0;//动作结束，人物复位
                    if (m.x <= 200 && m.x >= 0 && m.y >= 400 && m.y <= 600) {
                        ch[2] = 1;
                    }
                    //角色使用技能
                    if (m.x >= 200 && m.x <= 500 && m.y >= 500 && m.y <= 600) {
                        ch[1] = 1;
                    }
                    //角色使用普通攻击
                    if (m.x >= 500 && m.x <= 800 && m.y >= 500 && m.y <= 600) {//普攻（0）被按下
                        ch[0] = 1;
                    }
                }
                
                }
            }

            else {
                //boss回合，通过随机数来判断boss的释放招数
                srand(clock());
                random = rand() % 3;
                switch (random) {//根据随机数让Boss释放技能
                case 0: {
                    BDamage = BossDamage(userInform.tower);
                    characInform.Hp -= BDamage;
                    SetCharacterHp(characInform.Hp);
                }
                case 1: {
                    BossBuff(userInform.tower);
                }
                case 2: {
                    BossRecover(userInform.tower);
                    BHp = GetBossHp();
                }
                }
                CRound = true;//切换到人物回合
            }
        }

        i++;//循环变量加1（记录播放帧数）
        if (pnum[characNum][zhaoshi] == i) {//播放帧数等于招式帧数时播放结束并使人物复位
            i = 0;
            zhaoshi = 0;
        }

        
        Sleep(1.5);
    }

}

