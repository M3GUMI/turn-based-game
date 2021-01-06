#include <winsock2.h>
#include<windows.h>
#include <winsock.h>
#include <mysql.h> //数据库的变量类型和函数
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#include <stdbool.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")
#include<mmsystem.h>
#include"抽卡系统.h"
#define charatotalnum 9

/**************************************
*               抽卡系统 ！           *
* 实现抽卡的后端逻辑和抽卡记录的储存  *
***************************************/


int OnePick(void) {
    int result;
    int random, receive;
    srand(clock());
    random = rand() % 100;
    Sleep(1000);
    if (random == 0) {
        return 0;
    }
    else if (random == 1) {
        return 1;
    }
    else if (random == 2) {
        return 2;
    }
    else if (random == 3) {
        return 3;
    }
    else if (random == 4) {
        return 4;
    }
    else if (random == 5) {
        return 5;
    }
    else if (random > 5 && random < 45) {
        return 6;
    }
    else if (random >= 45 && random < 70) {
        return 7;
    }
    else if (random >= 70 && random < 80) {
        return 8;
    }
    else if (random >= 80 && random < 100) {
        return 9;
    }
    else return 10;
}


void Result_Save(int random,char userName[])
{
    FILE* fp;
    fp = fopen(File_Name(userName), "a");
    if (random == 0) fprintf(fp, "DVA\t");
    else if (random == 1) fprintf(fp, "cxk\t");
    else if (random == 2) fprintf(fp, "氪师傅\t");
    else if (random == 3) fprintf(fp, "比利王\t");
    else if (random == 4) fprintf(fp, "欧皇\t");
    else if (random >= 5 && random < 45) fprintf(fp, "一级经验药水\t");
    else if (random >= 45 && random < 70) fprintf(fp, "二级经验药水\t");
    else if (random >= 70 && random < 80) fprintf(fp, "三级经验药水\t");
    else if (random >= 80 && random < 100) fprintf(fp, "灵魂点数\t");
    fprintf(fp, "%s\n", Cur_Time());
    fclose(fp);
}


char* Cur_Time(void)
{
    time_t timep;
    time(&timep);
    return ctime(&timep);
}


char* File_Name(char userName[])
{
    char name[50] = { 0 };
    sprintf(name, ".\\抽卡记录\\%s.txt", userName);
    return name;
}


void Result_Look(char userName[])
{
    char buf[1024];
    FILE* fp;
    int len;
    int times = 0;
    char ch;
    system("cls");
    if ((fp = fopen(File_Name(userName),"r") )== NULL) {
        perror("fail to read");
        system("cls");
    }
    while (fgets(buf, 1024, fp)) {
        len = strlen(buf);
        buf[len - 1] = '\0';
        printf("%s\n", buf);
        times++;
        if (times % 20 == 0) {
            while ((ch = getchar()) == ' ');
            printf("按回车键查看下一页...");
            ch = getchar();
            system("cls");
        }
    }
    printf("按回车键返回...");
    ch = getchar();
    system("cls");
}