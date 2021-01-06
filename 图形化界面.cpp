#include <winsock2.h>
#include<windows.h>
#include <winsock.h>
#include <mysql.h> //���ݿ�ı������ͺͺ���
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
#include"ͼ�λ�����.h"
#include"�鿨ϵͳ.h"
#include"����ϵͳ.h"
#include"����ϵͳ.h"
#define charatotalnum 9

/**************************************
*            ͼ�λ�����ϵͳ ��        *
*      ʵ��ͼ�λ�����Ĵ�ͽ���     *
*   ʵ�����ݿ�Ĵ���ͺ����ֵ������  *
***************************************/


//���ַ���ת��Ϊ����
int GetInt(char str[]) {
    int num =0;
    for (int j = 0; str[j] != 0; j++) {
        num = num * 10 + (str[j] - '0');
    }
    return num;
}


//ʵʱ�����������ʾ�û����ݵĺ���
void ShowCharacter(char level[],char EXPAmount[],int select,int number) {
    char characLevel[20] = { 0 };
    sprintf(characLevel, "LV:%s", level);
    //����ȼ�
    outtextxy(100+number*170, 100, characLevel);
    //�������
    switch (select) {
    case 0:outtextxy(670, 45, EXPAmount); break;
    case 1:outtextxy(870, 45, EXPAmount); break;
    case 2:outtextxy(1070, 45, EXPAmount); break;
    }
}


//�л����鿨����Ķ���
void HometoDrawAnime() {
    //����ͼƬ
    IMAGE PHome, PDraw;
    loadimage(&PHome, ".\\img\\background\\��ҳ����.jpg", 1200, 600);
    loadimage(&PDraw, ".\\img\\background\\�鿨�ܽ���.png", 1200, 600);

    //����
    for (int i = 0; i <= 600; i += 3) {
        cleardevice();
        putimage(0, 0 + i, &PHome);
        putimage(0, -600 + i, &PDraw);
        Sleep(2);
    }
}


//�л����˳�����Ķ���
void HometoExitAnime() {
    //����ͼƬ
    IMAGE PHome, PExit;
    loadimage(&PHome, ".\\img\\background\\��ҳ����.jpg", 1200, 600);
    loadimage(&PExit, ".\\img\\background\\�˳�����.png", 1200, 600);

    //����
    for (int i = 0; i <= 600; i += 3) {
        cleardevice();
        putimage(0, 0 + i, &PHome);
        putimage(0, -600 + i, &PExit);
        Sleep(2);
    }
}


//��ҳ
void HomePage(char userName[]) {

    //����ͼƬ����
    IMAGE PBackground, PBattle, PCharac, PDraw, PExit, PTotal;

    //����ͼƬ
    loadimage(&PExit, ".\\img\\button\\�˳�2.jpg", 160, 60);
    loadimage(&PDraw, ".\\img\\button\\�鿨2.jpg", 160, 60);
    loadimage(&PCharac, ".\\img\\button\\��ɫ2.jpg", 160, 60);
    loadimage(&PBattle, ".\\img\\button\\ս��2.jpg", 160, 60);
    loadimage(&PBackground, ".\\img\\background\\��ҳ����.jpg", 1200, 600);
    loadimage(&PTotal, ".\\img\\button\\�û�������.jpg", 850, 60);

    //��������
    for (int i = 0; i <= 550; i+=5) {
        cleardevice();
        putimage(0, -600+i, &PBackground);
        Sleep(20);
    }

    //������
    cleardevice();
    putimage(0, -50, &PBackground);
    putimage(170, 430, &PTotal);


    //ͨ��������ʵ�ְ�ť�������
    MOUSEMSG m;
    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //����ڹ涨���򻮹�ʱ
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
                           //����ڹ涨������ʱ
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


//�鿨ҳ��
void DrawPage(char userName[]) {

    //����ͼƬ
    IMAGE img, PSoul,PSoul2, PSoulBack, PSoulFrame, PCharac, PCharacBackground, PButtonBackground, PDanChou, PShiLian, PDanChou2, PShiLian2, PBack, PBack2, PBacky, PBili, PBilyBackground, PCxk, PCxkBackground, PAoErJia, PBily, PKeQin, PDVA, POuHuang, PKeShiFu, Pcxk, PLEXP, PMEXP, PSEXP,PPunch;
    MOUSEMSG m;
    IMAGE PMaterial[10];
    int result;
    char material[10][20] = { "AoErJia","DVA","cxk","KeShiFu","Bily","OuHuang","smallEXP","middleEXP","largeEXP","Soul" }, soul[5] = { 0 };
    loadimage(&img, ".\\img\\background\\�鿨����.png", 1200, 600);
    loadimage(&PSoul, ".\\img\\material\\������1.jpg", 50, 50);
    loadimage(&PSoul2, ".\\img\\material\\������1c.jpg", 100, 100);
    loadimage(&PSoulBack, ".\\img\\material\\������1y.jpg", 50, 50);
    loadimage(&PSoulFrame, ".\\img\\background\\������������.jpg", 160, 60);
    loadimage(&PButtonBackground, ".\\img\\background\\������������y.jpg", 160, 60);
    loadimage(&PCharac, ".\\img\\background\\����鿨����.png", 800, 450);
    loadimage(&PCharacBackground, ".\\img\\background\\����鿨����y.png", 800, 450);
    loadimage(&PDanChou, ".\\img\\button\\��һ��.jpg", 160, 60);
    loadimage(&PShiLian, ".\\img\\button\\��ʮ��.jpg", 160, 60);
    loadimage(&PShiLian2, ".\\img\\button\\��ʮ��2.jpg", 160, 60);
    loadimage(&PDanChou2, ".\\img\\button\\��һ��2.jpg", 160, 60);
    loadimage(&PBack, ".\\img\\button\\����.png", 50, 40);
    loadimage(&PBack2, ".\\img\\button\\����2.png", 50, 40);
    loadimage(&PBacky, ".\\img\\button\\����y.png", 50, 40);
    loadimage(&PBilyBackground, ".\\img\\character\\������\\����������.png", 250, 180);
    loadimage(&PBili, ".\\img\\character\\������\\������.png", 250, 180);
    loadimage(&PCxk, ".\\img\\character\\������\\������.png", 220, 280);
    loadimage(&PCxkBackground, ".\\img\\character\\������\\����������.png", 220, 280); 
    loadimage(&PMaterial[0], ".\\img\\character\\�¶���\\�¶���ͷ��.png", 100, 100);
    loadimage(&PMaterial[1], ".\\img\\character\\DVA\\DVAͷ��.png", 100, 100);
    loadimage(&PMaterial[2], ".\\img\\character\\������\\������ͷ��.png", 100, 100);
    loadimage(&PMaterial[4], ".\\img\\character\\������\\������ͷ��.png", 100, 100);
    loadimage(&PMaterial[3], ".\\img\\character\\�ʦ��\\�ʦ��ͷ��.png", 100, 100);
    loadimage(&PMaterial[5], ".\\img\\character\\ŷ��\\ŷ��ͷ��.png", 100, 100);
    loadimage(&PMaterial[6], ".\\img\\material\\����ҩСc.png", 100, 100);
    loadimage(&PMaterial[7], ".\\img\\material\\����ҩ��c.png", 100,100);
    loadimage(&PMaterial[8], ".\\img\\material\\����ҩ��c.png", 100, 100);
    loadimage(&PMaterial[9], ".\\img\\material\\������1c.jpg", 100, 100);
    loadimage(&PPunch, ".\\img\\background\\������ȭ.gif", 200, 200);
    


    //��鿨��ʼҳ��
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

    //��ʾ�鿨����
    outtextxy(955, 170, "���������ʣ�6%");
    outtextxy(955, 190, "���������ʣ�10%");
    outtextxy(955, 210, "����о�����ʣ�25%");
    outtextxy(955, 230, "���С������ʣ�39%");
    outtextxy(955, 250, "������������ʣ�20%");

    //�����������ݿ�Ļ�������
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    char searchCommand[180];
    sprintf(searchCommand, "select Soul from users where username=\"%s\"", userName);

    //�������ݿ⿴��������������
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //��ͼ�ν�����ʾ��������ֵ
    outtextxy(1025, 125, row[0]);

    mysql_free_result(res);

    sprintf(searchCommand, "select AoErJia,DVA,cxk,KeShiFu,Bily,OuHuang,smallEXP,middleEXP,largeEXP,Soul from users where username=\"%s\"", userName);
    //�������ݿ�
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //��Ϊ�õ����������ַ�����Ҫ����Щ����������
    int materialNum[4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; row[i + 6][j]!='\0'; j++) {
            materialNum[i] = materialNum[i] * 10 + (row[i+6][j] - '0');
        }
    }


    //ѭ���ռ������Ϣ���н���
    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //����ڹ涨������ʱ
        case WM_LBUTTONDOWN: {
            //���麯��
            if (m.x >= 955 && m.x <= 1115 && m.y >= 305 && m.y <= 365) {
                //����û����������Ƿ񹻳鿨
                if (materialNum[3] >= 1) {
                    //�ȿ۳��û�������
                    sprintf(searchCommand, "UPDATE users SET Soul=%d where username=\"%s\"", --materialNum[3], userName);
                    if (mysql_query(conn, searchCommand)) {
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(10);
                    }
                    sprintf(soul, "%d", materialNum[3]);
                    outtextxy(1025, 125, soul);

                    //���ݷ���ֵ�жϳ鿨���������鿨���
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
                outtextxy(925, 500, "��û����������");
                outtextxy(925, 520, "û�õĶ���");
                outtextxy(925, 540, "������ȭ����");
                putimage(350, 200, &PPunch);
                }
            }
            //ʮ���麯��
            if (m.x >= 955 && m.x <= 1115 && m.y >= 405 && m.y <= 465) {
                //����������Ƿ��㹻ʮ��
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
                            //�������������ֵ���õ��鿨������������ݿ�
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
                outtextxy(925, 500, "��û����������");
                outtextxy(925, 520, "û�õĶ���");
                outtextxy(925, 540, "������ȭ����");
                putimage(350, 200, &PPunch);
                }
            }
            if (m.x >= 50 && m.x <= 100 && m.y >= 15 && m.y <= 55) {
                HomePage(userName);
            }
        }
                           //����ڹ涨���򻮹�ʱ�ĸ���Ч��
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


//�˳�����
void ExitPage() {
    IMAGE PBackGround;
    loadimage(&PBackGround, ".\\img\\background\\�˳�����.png", 1200, 600);
    putimage(0, 0, &PBackGround);
    Sleep(1500);
    exit(0);
}


//������棺����ʵ������������͵ȼ��Ĳ�ѯ
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

    //����ͼƬ����������
    struct userCharacter character[6] = {"",0};
    struct EXP EXPSelect[3];
    EXPSelect[0] = { "smallEXP",1,0 };
    EXPSelect[1] = { "middleEXP",2,0 };
    EXPSelect[2] = { "largeEXP",3,0 };
    int select=3;
    MOUSEMSG m;
    IMAGE PBackGround, PAoErJia, PBily, PKeQin, PDVA, POuHuang, PKeShiFu, Pcxk, PBack, PBack2, PBacky, PLEXP, PMEXP, PSEXP, PBackyB, PLEXPB, PMEXPB, PSEXPB, PFrame, PFrameB, PLEXP2, PMEXP2, PSEXP2, PLEXP3, PMEXP3, PSEXP3;
    char searchCommand[100], updateCommand[100];
    loadimage(&PBackGround, ".\\img\\background\\���ﱳ��.png", 1200, 600);
    loadimage(&POuHuang, ".\\img\\character\\ŷ��\\ŷ��ͷ��.png", 130, 130);
    loadimage(&PAoErJia, ".\\img\\character\\�¶���\\�¶���ͷ��.png", 130, 130);
    loadimage(&PBily, ".\\img\\character\\������\\������ͷ��.png", 130, 130);
    loadimage(&PKeShiFu, ".\\img\\character\\�ʦ��\\�ʦ��ͷ��.png", 130, 130);
    loadimage(&PDVA, ".\\img\\character\\DVA\\DVAͷ��.png", 130, 130);
    loadimage(&Pcxk, ".\\img\\character\\������\\������ͷ��.png", 130, 130);
    loadimage(&PBack, ".\\img\\button\\����.png", 50, 40);
    loadimage(&PBack2, ".\\img\\button\\����2.png", 50, 40);
    loadimage(&PBacky, ".\\img\\button\\����y.png", 50, 40);
    loadimage(&PLEXP, ".\\img\\material\\����ҩ��.png", 50, 50);
    loadimage(&PMEXP, ".\\img\\material\\����ҩ��.png", 50, 50);
    loadimage(&PSEXP, ".\\img\\material\\����ҩС.png", 50, 50);
    loadimage(&PLEXPB, ".\\img\\material\\����ҩ�󱳾�.png", 50, 50);
    loadimage(&PMEXPB, ".\\img\\material\\����ҩ�б���.png", 50, 50);
    loadimage(&PSEXPB, ".\\img\\material\\����ҩС����.png", 50, 50);
    loadimage(&PFrame, ".\\img\\background\\������������.jpg", 160, 60);
    loadimage(&PFrameB, ".\\img\\background\\������������y.jpg", 160, 60);
    loadimage(&PLEXP2, ".\\img\\material\\����ҩ��c.png", 100, 100);
    loadimage(&PMEXP2, ".\\img\\material\\����ҩ��c.png", 100, 100);
    loadimage(&PSEXP2, ".\\img\\material\\����ҩСc.png", 100, 100);
    loadimage(&PLEXP3, ".\\img\\material\\����ҩ��.png", 100, 100);
    loadimage(&PMEXP3, ".\\img\\material\\����ҩ��.png", 100, 100);
    loadimage(&PSEXP3, ".\\img\\material\\����ҩС.png", 100, 100);


    //�����������ݿ�Ļ�������
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }



    //�ű���ͼ
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


   

    //��������в���
    sprintf(searchCommand, "select AoErJia,DVA,cxk,KeShiFu,Bily,OuHuang,smallEXP,middleEXP,largeEXP from users where username=\"%s\"", userName);

    //�������ݿ⿴�����Ƿ����
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //����������ݼ������Ƿ�ӵ�����ӵ������ʾ
    for (int i = 0, j = 0, x = 100; i < 6; i++, x = x + 170) {
        if (row[i] != NULL) {
            char characLevel[20] = { 0 };
            sprintf(characLevel, "LV:%s", row[i]);
            switch (i) {
                //�˴�strcpy�Ǹ���Ӧ��ʾ��������ͼƬ���������ţ�����֮����������
            case 0:putimage(x, 100, &PAoErJia); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "AoErJia"); break;
            case 1:putimage(x, 100, &PDVA); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "DVA"); break;
            case 2:putimage(x, 100, &Pcxk); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "cxk"); break;
            case 3:putimage(x, 100, &PKeShiFu); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "KeShiFu"); break;
            case 4:putimage(x, 100, &PBily); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "Bily"); break;
            case 5:putimage(x, 100, &POuHuang); outtextxy(x, 100, characLevel); strcpy(character[j++].characName, "OuHuang"); break;
            }
        }
    }

    //ͼ�ν�����ʾ���� �о��� С���������
    outtextxy(670, 45, row[6]);
    outtextxy(870, 45, row[7]);
    outtextxy(1070, 45, row[8]);

    //���ô���С�������ͼ
    putimage(350, 400, &PSEXP2);
    putimage(550, 400, &PMEXP2);
    putimage(750, 400, &PLEXP2);


    for (int i = 0, characNum = 0; i < 6; i++) {
        //��if�ж��û��Ƿ�ӵ�и�����
        if (row[i] != NULL) {
            //������ȼ����ַ���ת��������
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


    //ѭ���ռ������Ϣ���н���
    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //����ڹ涨������ʱ������Ӧ��Ӧ
        case WM_LBUTTONDOWN: {
            if (m.x >= 50 && m.x <= 100 && m.y >= 15 && m.y <= 55) {
                HomePage(userName);
            }
            if (m.x >= 350 && m.x <= 450 && m.y >= 400 && m.y <= 500) {
                //�û����ݵ����ѡ����ҩ
                putimage(350, 400, &PSEXP3);
                putimage(550, 400, &PMEXP2);
                putimage(750, 400, &PLEXP2);
                select = 0;
            }
            if (m.x >= 550 && m.x <= 650 && m.y >= 400 && m.y <= 500) {
                //�û����ݵ����ѡ����ҩ
                putimage(350, 400, &PSEXP2);
                putimage(550, 400, &PMEXP3);
                putimage(750, 400, &PLEXP2);
                select = 1;
            }
            if (m.x >= 750 && m.x <= 850 && m.y >= 400 && m.y <= 500) {
                //�û����ݵ����ѡ����ҩ
                putimage(350, 400, &PSEXP2);
                putimage(550, 400, &PMEXP2);
                putimage(750, 400, &PLEXP3);
                select = 2;
            }
            if (m.x >= 100 && m.x <= 200 && m.y >= 100 && m.y <= 200) {
                if (character[0].characName[0] != 0 && EXPSelect[select].EXPNumber != 0) {
                    //����û�����ҩ�Ƿ��㹻
                    if (EXPSelect[select].EXPAmount > 0) {
                        //�û�����
                        sprintf(updateCommand, "UPDATE users SET %s=%d,%s=%d where username=\"%s\"", character[0].characName, character[0].characLevel = character[0].characLevel + EXPSelect[select].EXPNumber, EXPSelect[select].EXPName, EXPSelect[select].EXPAmount = EXPSelect[select].EXPAmount - 1, userName);
    
                        if (mysql_query(conn, updateCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //ʵʱ��ȡ����ȼ�
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[0].characName,EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }
                        //�������
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);
                        //ʵʱ��ʾ����
                        ShowCharacter(row[0], row[1], select, 0);
                    }
                    else outtextxy(565, 300, "��Ʒ����");
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

                        //ʵʱ��ȡ����ȼ�
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[1].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //�������
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //ʵʱ��ʾ����
                        ShowCharacter(row[0], row[1], select, 1);
                    }
                    else outtextxy(565, 300, "��Ʒ����");
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

                        //ʵʱ��ȡ����ȼ�
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[2].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //�������
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //ʵʱ��ʾ����
                        ShowCharacter(row[0], row[1], select, 2);
                    }
                    else outtextxy(440, 300, "��Ʒ����");
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

                        //ʵʱ��ȡ����ȼ�
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[3].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }
                        //�������
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //ʵʱ��ʾ����
                        ShowCharacter(row[0], row[1], select, 3);
                    }
                    else outtextxy(565, 300, "��Ʒ����");
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

                        //ʵʱ��ȡ����ȼ�
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[4].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }

                        //�������
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //ʵʱ��ʾ����
                        ShowCharacter(row[0], row[1], select, 4);
                    }
                    else outtextxy(565, 300, "��Ʒ����");
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

                        //ʵʱ��ȡ����ȼ�
                        sprintf(searchCommand, "select %s,%s from users where username=\"%s\"", character[5].characName, EXPSelect[select].EXPName, userName);
                        if (mysql_query(conn, searchCommand)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(0);
                        }
                        //�������
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);

                        //ʵʱ��ʾ����
                        ShowCharacter(row[0], row[1], select, 5);
                    }
                    else outtextxy(565, 300, "��Ʒ����");
                }
            }


            //����ڹ涨���򻮹�ʱ
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


//ս��֮ǰ�ĵ�ͼ����
void MapPage(char userName[]) {

    srand(time(0));
    //������ʱ����
    int i, xchange = 0, ychange = 0, j, x, y;

    //�����ͼ����
    struct mapinformation {
        bool walkable;
        int active;
    };
    struct mapinformation map[31][16];
    //�����ͼ
    for (i = 0; i < 31; i++) {
        for (j = 0; j < 16; j++) {
            map[i][j].walkable = false;
            map[i][j].active = 2;
        }
    }


    int EXPAmount = 0;
    char searchCommand[150] = { 0 }, updateCommand[150] = { 0 };

    //�н����ķ���Ķ���
    map[8][9].active = rand()%2;
    map[11][1].active = rand() % 2;
    map[5][6].active = rand() % 2;
    map[14][8].active = rand() % 2;
    map[1][1].walkable = false;
    map[30][5].active = 4;
    map[29][5].active = 4;
    map[30][6].active = 4;


    //�����߷��鶨��
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
    //����ͼ���ȡ����
    int xback = 0, yback = 0;
    //����������������
    int xchara = 241, ychara = 121;
    //���屳��ͼ����
    IMAGE background;
    //��������ͼ����
    IMAGE chara[charatotalnum];
    IMAGE charay[charatotalnum];
    //����ͼƬ
    //����ͼƬ
    loadimage(&chara[0], ".\\img\\character\\�¶���\\1.jpg", 256, 128);
    loadimage(&chara[1], ".\\img\\character\\�¶���\\2.jpg", 256, 128);
    loadimage(&chara[2], ".\\img\\character\\�¶���\\3.jpg", 256, 128);
    loadimage(&chara[3], ".\\img\\character\\�¶���\\4.jpg", 256, 128);
    loadimage(&chara[4], ".\\img\\character\\�¶���\\5.jpg", 256, 128);
    loadimage(&chara[5], ".\\img\\character\\�¶���\\6.jpg", 256, 128);
    loadimage(&chara[6], ".\\img\\character\\�¶���\\7.jpg", 256, 128);
    loadimage(&chara[7], ".\\img\\character\\�¶���\\8.jpg", 256, 128);

    loadimage(&charay[0], ".\\img\\character\\�¶���\\1y.jpg", 256, 128);
    loadimage(&charay[1], ".\\img\\character\\�¶���\\2y.jpg", 256, 128);
    loadimage(&charay[2], ".\\img\\character\\�¶���\\3y.jpg", 256, 128);
    loadimage(&charay[3], ".\\img\\character\\�¶���\\4y.jpg", 256, 128);
    loadimage(&charay[4], ".\\img\\character\\�¶���\\5y.jpg", 256, 128);
    loadimage(&charay[5], ".\\img\\character\\�¶���\\6y.jpg", 256, 128);
    loadimage(&charay[6], ".\\img\\character\\�¶���\\7y.jpg", 256, 128);
    loadimage(&charay[7], ".\\img\\character\\�¶���\\8y.jpg", 256, 128);

    loadimage(&background, ".\\img\\background\\��ͼ����.png", 3720, 1920);


    //���ó�ʼͼƬ
    initgraph(1200, 600);
    putimage(0, 0, &background);
    //putimage(600, 300, &charay[0], SRCAND);
    //putimage(600, 300, &chara[0], SRCPAINT);

    //�����������ݿ�Ļ�������
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //��������в���
    sprintf(searchCommand, "select smallEXP from users where username=\"%s\"", userName);

    //�������ݿ�鿴С���������Ƿ����
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //���ַ���ת��������
    for (int i = 0; row[0][i] != 0; i++) {
        EXPAmount = EXPAmount * 10 + (row[0][i] - '0');
    }

    for (i = 0; 1; i++) {
        if (i == 71) {
            i = 0;
        }
        //��ȡ���̲���
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)//��
            xchange = -1;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//��
            xchange = 1;
        if (GetAsyncKeyState(VK_UP) & 0x8000)//��
            ychange = -1;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)//��
            ychange = 1;
        xchara += xchange;
        ychara += ychange;
        xback += xchange;
        yback += ychange;
        //�ж������Ƿ��ڽ����������
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


//�ڵ�ͼ������bossѡ�������������ĺ���
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

    loadimage(&PBackGround, ".\\img\\background\\���ﱳ��.png", 1200, 600);
    loadimage(&POuHuang, ".\\img\\character\\ŷ��\\ŷ��ͷ��.png", 130, 130);
    loadimage(&PAoErJia, ".\\img\\character\\�¶���\\�¶���ͷ��.png", 130, 130);
    loadimage(&PBily, ".\\img\\character\\������\\������ͷ��.png", 130, 130);
    loadimage(&PKeShiFu, ".\\img\\character\\�ʦ��\\�ʦ��ͷ��.png", 130, 130);
    loadimage(&PDVA, ".\\img\\character\\DVA\\DVAͷ��.png", 130, 130);
    loadimage(&Pcxk, ".\\img\\character\\������\\������ͷ��.png", 130, 130);
    loadimage(&PBack, ".\\img\\button\\����.png", 50, 40);
    loadimage(&PBack2, ".\\img\\button\\����2.png", 50, 40);
    loadimage(&PBacky, ".\\img\\button\\����y.png", 50, 40);

    //�ű���ͼ
    putimage(0, 0, &PBackGround);

    //�����������ݿ�Ļ�������
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }


    //��������в���
    sprintf(searchCommand, "select AoErJia,DVA,cxk,KeShiFu,Bily,OuHuang from users where username=\"%s\"", userName);

    //�������ݿ⿴�����Ƿ����
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //����������ݼ������Ƿ�ӵ�����ӵ������ʾ
    for (int i = 0, j = 0, x = 100; i < 6; i++, x = x + 170) {
        if (row[i] != NULL) {
            char characLevel[20] = { 0 };
            sprintf(characLevel, "LV:%s", row[i]);
            switch (i) {
                //�˴�strcpy�Ǹ���Ӧ��ʾ��������ͼƬ���������ţ�����֮����������
            case 0:putimage(x, 100, &PAoErJia); outtextxy(x, 100, characLevel); character[j].characNumber = 0; strcpy(character[j++].characName, "AoErJia"); break;
            case 1:putimage(x, 100, &PDVA); outtextxy(x, 100, characLevel); character[j].characNumber = 1; strcpy(character[j++].characName, "DVA"); break;
            case 2:putimage(x, 100, &Pcxk); outtextxy(x, 100, characLevel); character[j].characNumber = 2; strcpy(character[j++].characName, "cxk"); break;
            case 3:putimage(x, 100, &PKeShiFu); outtextxy(x, 100, characLevel); character[j].characNumber = 3; strcpy(character[j++].characName, "KeShiFu"); break;
            case 4:putimage(x, 100, &PBily); outtextxy(x, 100, characLevel); character[j].characNumber = 4; strcpy(character[j++].characName, "Bily"); break;
            case 5:putimage(x, 100, &POuHuang); outtextxy(x, 100, characLevel); character[j].characNumber = 5; strcpy(character[j++].characName, "OuHuang"); break;
            }
        }
    }

    //���û�ӵ�е�ÿ����ɫ�����ݿ��л�ȡ�ĵȼ��ַ���ת��������
    for (int i = 0, characNum = 0; i < 6; i++) {
        //��if�ж��û��Ƿ�ӵ�и�����
        if (row[i] != NULL) {
            //������ȼ����ַ���ת��������
            for (int j = 0; row[i][j] != '\0'; j++) {
                character[characNum].characLevel = character[characNum].characLevel * 10 + (row[i][j] - '0');
            }
            characNum++;
        }
    }

    while (1) {
        m = GetMouseMsg();
        switch (m.uMsg) {
            //����ڹ涨������ʱ������Ӧ��Ӧ
        case WM_LBUTTONDOWN: {
            if (m.x >= 100 && m.x <= 200 && m.y >= 100 && m.y <= 200) {
                //����û��Ƿ�ӵ�и�����
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


//ս������
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
    char bossName[10][15] = { "�㽶��","van","ħ��","ծ������","niko","simple","����","����","����","΢����" };
    char battleInformation[100];


    bool CRound = true;
    char number[40];
    int i, size = 300, j, ch[3] = {0};//������ʱ����
    int zhaoshi = 0;
    double  CMHp = 0, CMMp = 0, CDamage = 0, BMHp = 0, BHp = 0, BDamage = 0;//�ֱ�Ϊ�����������ֵ������ܵ㣬��������˺��������������ֵ����������ֵ����������˺�
    int pnum[6][3];   //�������Ｐ֡��
    char searchCommand[150] = { 0 };
    char characterName[6][20] = { "AoErJia","DVA","cxk","KeShiFu","Bily","OuHuang" };

    //�����������ݿ�Ļ�������
    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;


    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }


    //��������в���
    sprintf(searchCommand, "select tower,smallEXP,Soul from users where username=\"%s\"", userName);

    //�������ݿ⿴�����Ƿ����
    if (mysql_query(conn, searchCommand)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //�õ��û��Ĳ�����Ϣ�����ҳ�ʼ������͹���ĳ�ʼ����
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

    //�������
    MOUSEMSG m;

    //����ͼ��
    IMAGE backgroundfight, choise[2], dazhao[2], dazhaoy, blood, bloody, lan, lany, die;
    IMAGE chara[6][3][12], charay[6][3][12], boss[10][2],victory[6];

    //����ͼ��
    loadimage(&choise[0], ".\\img\\battle\\���.jpg", 300, 100);
    loadimage(&choise[1], ".\\img\\battle\\���1.jpg", 300, 100);
    loadimage(&dazhao[0], ".\\img\\battle\\����.jpg", 200, 200);
    loadimage(&dazhao[1], ".\\img\\battle\\����1.jpg", 200, 200);
    loadimage(&dazhaoy, ".\\img\\battle\\����y.jpg", 200, 200);
    loadimage(&backgroundfight, ".\\img\\battle\\backgroundfight.png", 1200, 600);
    loadimage(&chara[1][0][0], ".\\img\\battle\\DVA.png", size, size);
    loadimage(&chara[1][1][0], ".\\img\\battle\\DVA.png", size, size);
    loadimage(&chara[1][2][0], ".\\img\\battle\\DVA.png", size, size);
    loadimage(&chara[0][0][0], ".\\img\\battle\\�¶���.png", size, size);
    loadimage(&chara[4][0][0], ".\\img\\battle\\������.png", size, size);
    loadimage(&chara[4][1][0], ".\\img\\battle\\������.png", size, size);
    loadimage(&chara[4][2][0], ".\\img\\battle\\������.png", size, size);
    loadimage(&chara[2][0][0], ".\\img\\battle\\������.png", size, size);
    loadimage(&chara[3][0][0], ".\\img\\battle\\�ʦ��.png", size, size);
    loadimage(&chara[3][1][0], ".\\img\\battle\\�ʦ��.png", size, size);
    loadimage(&chara[3][2][0], ".\\img\\battle\\�ʦ��.png", size, size);
    loadimage(&chara[5][0][0], ".\\img\\battle\\ŷ��.png", size, size);
    loadimage(&chara[5][1][0], ".\\img\\battle\\ŷ��.png", size, size);
    loadimage(&chara[5][2][0], ".\\img\\battle\\ŷ��.png", size, size);
    loadimage(&charay[1][0][0], ".\\img\\battle\\DVA����.png", size, size);
    loadimage(&charay[1][1][0], ".\\img\\battle\\DVA����.png", size, size);
    loadimage(&charay[1][2][0], ".\\img\\battle\\DVA����.png", size, size);
    loadimage(&charay[0][0][0], ".\\img\\battle\\�¶��ӱ���.png", size, size);
    loadimage(&charay[4][0][0], ".\\img\\battle\\����������.png", size, size);
    loadimage(&charay[4][1][0], ".\\img\\battle\\����������.png", size, size);
    loadimage(&charay[4][2][0], ".\\img\\battle\\����������.png", size, size);
    loadimage(&charay[2][0][0], ".\\img\\battle\\����������.png", size, size);
    loadimage(&charay[3][0][0], ".\\img\\battle\\�ʦ������.png", size, size);
    loadimage(&charay[3][1][0], ".\\img\\battle\\�ʦ������.png", size, size);
    loadimage(&charay[3][2][0], ".\\img\\battle\\�ʦ������.png", size, size);
    loadimage(&charay[5][0][0], ".\\img\\battle\\ŷ�ʱ���.png", size, size);
    loadimage(&charay[5][1][0], ".\\img\\battle\\ŷ�ʱ���.png", size, size);
    loadimage(&charay[5][2][0], ".\\img\\battle\\ŷ�ʱ���.png", size, size);
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

    loadimage(&die, ".\\img\\battle\\�ų�����.jpg", 1200, 600);

    loadimage(&bloody, ".\\img\\battle\\Ѫ��y.jpg", 300, 50);
    loadimage(&blood, ".\\img\\battle\\Ѫ��.jpg", 300, 50);
    loadimage(&lany, ".\\img\\battle\\����y.jpg", 300, 20);
    loadimage(&lan, ".\\img\\battle\\����.jpg", 300, 20);

    //������ʽ����
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            pnum[i][j] = 1;
        }
    }
    for (i = 0; i < 12; i++) {
        sprintf(number, ".\\img\\battle\\�����(2)\\%d.jpg", i + 1);
        loadimage(&chara[2][1][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\�����(2)\\%dy.jpg", i + 1);
        loadimage(&charay[2][1][i], number, 640, 360);
    }
    pnum[2][1] = 12;//��ʽ����֡��
    for (i = 0; i < 7; i++) {
        sprintf(number, ".\\img\\battle\\�����(3)\\%d.jpg", i + 1);
        loadimage(&chara[2][2][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\�����(3)\\%dy.jpg", i + 1);
        loadimage(&charay[2][2][i], number, 640, 360);
    }
    pnum[2][2] = 7;//��ʽ����֡��
    for (i = 0; i < 8; i++) {
        sprintf(number, ".\\img\\battle\\�����(4)\\%d.jpg", i + 1);
        loadimage(&chara[0][2][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\�����(4)\\%dy.jpg", i + 1);
        loadimage(&charay[0][2][i], number, 640, 360);
    }
    pnum[0][2] = 8;//��ʽ����֡��
    for (i = 0; i < 4; i++) {
        sprintf(number, ".\\img\\battle\\�����(5)\\%d.jpg", i + 1);
        loadimage(&chara[0][1][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\�����(5)\\%dy.jpg", i + 1);
        loadimage(&charay[0][1][i], number, 640, 360);
    }
    pnum[0][1] = 4;//��ʽ����֡��
    for (i = 0; i < 5; i++) {
        sprintf(number, ".\\img\\battle\\�����(6)\\%d.jpg", i + 1);
        loadimage(&chara[1][2][i], number, 640, 360);
        sprintf(number, ".\\img\\battle\\�����(6)\\%dy.jpg", i + 1);
        loadimage(&charay[1][2][i], number, 640, 360);
    }
    pnum[1][2] = 5;//��ʽ����֡��

    //����ʤ������
    for (i = 0; i < 6; i++) {
        sprintf(number, ".\\img\\battle\\�����(7)\\%d.png", i + 1);
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

    //����ͼ���
    initgraph(1200, 600);
    cleardevice();

    //���ó�ʼͼ��
    putimage(0, 0, 1200, 600, &backgroundfight, 0, 0);
    putimage(100, 0, &charay[characNum][0][0], SRCAND);
    putimage(100, 0, &chara[characNum][0][0], SRCPAINT);
    putimage(200, 500, &choise[0]);
    putimage(500, 500, &choise[0]);
    putimage(0, 400, &dazhaoy, SRCAND);
    putimage(0, 400, &dazhao[0], SRCPAINT);

    i = 0;//��ʱѭ������


   
    //ս�������е�ͼ��ѭ��
    while (1) {
        cleardevice();
        putimage(0, 0, 1200, 600, &backgroundfight, 0, 0);//������
        //��ѡ���
        putimage(200, 500, &choise[ch[1]]);
        putimage(500, 500, &choise[ch[0]]);
        putimage(0, 400, &dazhaoy, SRCAND);
        putimage(0, 400, &dazhao[ch[2]], SRCPAINT);
        //������ͼ�񣨾�ֹ�Ͷ�����
        putimage(100 + j, 100, &charay[characNum][zhaoshi][i], SRCAND);
        putimage(100 + j, 100, &chara[characNum][zhaoshi][i], SRCPAINT);
        //��Bossͼ��
        putimage(800 - j, 100, &boss[bossnum][1], SRCAND);
        putimage(800 - j, 100, &boss[bossnum][0], SRCPAINT);
        //��Ѫ��������
        putimage(100, 50, 300, 30, &bloody, 0, 0);
        putimage(100, 70, 300, 4, &lany, 0, 0);
        putimage(800, 50, 300, 30, &bloody, 0, 0);
        putimage(100, 50, characInform.Hp / CMHp * 300, 30, &blood, 0, 0);
        putimage(800, 50, BHp / BMHp * 300, 30, &blood, 0, 0);
        putimage(100, 70, characInform.Mp / CMMp * 300, 4, &lan, 0, 0);

        
        ch[0] = 0;
        ch[1] = 0;
        ch[2] = 0;

        //�ж��Ƿ��������ﶯ���ڼ�
        if (zhaoshi != 0) {
            Sleep(500);
        }
        else {
            //�ж�boss�Ƿ��Ѿ�����ɱ
            if (BHp <= 0) {
                //ʤ����Ч
                mciSendString("open .\\img\\battle\\ʤ��.mp3 alias bkmusic", NULL, 0, NULL);
                mciSendString("play bkmusic", NULL, 0, NULL);
                for (i = 0; i < 10; i++) {
                    for (int j = 0; j < 6; j++) {
                        putimage(0, 0, 1200, 600, &victory[j], 0, 0);
                        Sleep(100);
                    }
                }
                //�����������ݿ�
                sprintf(updateCommand, "UPDATE users SET smallEXP=%d,Soul=%d,tower=%d,%s=%d WHERE username=\"%s\"", userInform.smallEXP = userInform.smallEXP + 1, userInform.Soul = userInform.Soul + 1, userInform.tower = userInform.tower + 1, characName[characNum], characterLevel = characterLevel + 1, userName);;
                if (mysql_query(conn, updateCommand)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(0);
                }
                mciSendString("close bkmusic", NULL, 0, NULL);
                HomePage(userName);
            }

            //�ж�����Ƿ��Ѿ�����ɱ
            if (characInform.Hp <= 0) {
                //���������Ч
                putimage(0, 0, &die);//����ͼƬ
                //��������
                mciSendString("open .\\img\\battle\\�ų�����.mp3 alias bkmusic", NULL, 0, NULL);
                mciSendString("play bkmusic", NULL, 0, NULL);
                //�����ֲ����ڼ䲻�˻ص�������
                Sleep(7000);
                mciSendString("close bkmusic", NULL, 0, NULL);
                //�ص�������
                HomePage(userName);

            }
            if (CRound) {//�ж��Ƿ�������غ�
                m = GetMouseMsg();//��ȡ������
                switch (m.uMsg) {
                case WM_LBUTTONDOWN: {//�����������Ƿ���

                    //��ɫʹ�ô���
                    if (m.x <= 200 && m.x >= 0 && m.y >= 400 && m.y <= 600) {
                        CharacSkill3(userInform.character);
                        characInform = GetCharacInform();
                        BHp -= characInform.damage;
                        SetBossHp(BHp);
                        zhaoshi = 2;
                    }

                    //��ɫʹ�ü���
                    if (m.x >= 200 && m.x <= 500 && m.y >= 500 && m.y <= 600) {
                        CharacSkill2(userInform.character);
                        characInform = GetCharacInform();
                        BHp -= characInform.damage;
                        SetBossHp(BHp);
                        zhaoshi = 1;
                    }

                    //��ɫʹ����ͨ����
                    if (m.x >= 500 && m.x <= 800 && m.y >= 500 && m.y <= 600) {//�չ���0��������
                        CharacSkill1(userInform.character);
                        characInform = GetCharacInform();
                        BHp -= characInform.damage;
                        SetBossHp(BHp);
                        zhaoshi = 0;
                    }
                    j = 10;//����λ��
                    CRound = false;//�л�ΪBoss�غ�
                    break;
                }
                default: {
                    j = 0;//�������������︴λ
                    if (m.x <= 200 && m.x >= 0 && m.y >= 400 && m.y <= 600) {
                        ch[2] = 1;
                    }
                    //��ɫʹ�ü���
                    if (m.x >= 200 && m.x <= 500 && m.y >= 500 && m.y <= 600) {
                        ch[1] = 1;
                    }
                    //��ɫʹ����ͨ����
                    if (m.x >= 500 && m.x <= 800 && m.y >= 500 && m.y <= 600) {//�չ���0��������
                        ch[0] = 1;
                    }
                }
                
                }
            }

            else {
                //boss�غϣ�ͨ����������ж�boss���ͷ�����
                srand(clock());
                random = rand() % 3;
                switch (random) {//�����������Boss�ͷż���
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
                CRound = true;//�л�������غ�
            }
        }

        i++;//ѭ��������1����¼����֡����
        if (pnum[characNum][zhaoshi] == i) {//����֡��������ʽ֡��ʱ���Ž�����ʹ���︴λ
            i = 0;
            zhaoshi = 0;
        }

        
        Sleep(1.5);
    }

}

