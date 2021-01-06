#include <winsock2.h>
#include<windows.h>
#include <winsock.h>
#include <mysql.h> //数据库的变量类型和函数
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<graphics.h>//图形化界面
#include<easyx.h>//图形化界面
#include "图形化界面.h"//提供图形化界面的头文件
#include "用户登录注册.h"//实现登录注册的头文件

/**************************************
*               注 意 ！              *
*        启动游戏需要配置环境         *
*     还请在VS环境下安装easyX库       * 
*          并且导入mysql.h            *
***************************************/

int main() {
    //用户登录或注册
    char userName[50] = { 0 }, pwd[50] = { 0 };
    UserLogOrReg(userName,pwd);

    //跳转图形化界面
    initgraph(1200, 600);//初始化一个图形窗口
    HomePage(userName);//实现主页图形函数
}
