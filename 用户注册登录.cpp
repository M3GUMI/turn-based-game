#include <winsock2.h>
#include<windows.h>
#include <winsock.h>
#include <mysql.h> //数据库的变量类型和函数
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<graphics.h>//提供图形化界面的头文件
#include<easyx.h>//提供图形化界面的头文件
#include "用户登录注册.h"//实现登录注册的头文件
#pragma comment(lib,"Winmm.lib")
#include<mmsystem.h>

/***********************************************
*              用户登录注册系统 ！             *
*   得到用户输入的账号密码并且遍历数据库检查   *
*       得到是否注册或者登录成功的结果         *
************************************************/

bool UserLog(char userName[],char pwd[]) {
    //提示用户输入登录信息
    printf("请输入用户名(十位以内)：");
    scanf("%s", userName);
    printf("请输入密码(十位以内)：");
    scanf("%s", pwd);

    //检查长度是否合格
    if (strlen(userName) > 11 || strlen(pwd) > 11) {
        printf("请输入十位以内的字符串！\n");
        return FALSE;
    }

    //定义链接数据库的基本变量
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;
    conn = mysql_init(NULL);

    bool userExist = FALSE;
    bool logSuccess = FALSE;

    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //发送遍历数据库请求，如果失败报出错误信息
    if (mysql_query(conn, "select username,pwd from users")) {
        //ConnDB(conn,user,password,database,port);
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //收集数据库信息
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //先遍历数据库检查用户是否存在
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], userName) == 0) {
            userExist = TRUE;
            break;
        }
    }
    if (!userExist) {
        printf("用户不存在\n");
        return FALSE;
    }

    //清除之前的结果
    mysql_free_result(res);

    //重新查询
    if (mysql_query(conn, "select username,pwd from users")) {
        //ConnDB(conn,user,password,database,port);
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //得到查询结果
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);


    //遍历数据库查看用户密码是否正确
    while ((row = mysql_fetch_row(res)) != NULL) {
        if ((strcmp(row[0], userName) == 0) && (strcmp(row[1], pwd) == 0)) {
            logSuccess = TRUE;
            break;
        }
    }



    //关闭数据库
    mysql_close(conn);


    if (logSuccess) {
        printf("登陆成功！\n");
        return TRUE;
    }
    else {
        printf("密码错误！\n");
        return FALSE;
    }

}


bool UserReg(char userName[],char pwd[]) {
    //提示用户输入
    printf("请输入用户名(十位以内)：");
    scanf("%s", userName);
    printf("请输入密码（十位以内）：");
    scanf("%s", pwd);

    //检查长度是否合格
    if (strlen(userName) > 11 || strlen(pwd) > 11) {
        printf("请输入十位以内的字符串！\n");
        return FALSE;
    }

    //定义链接数据库的基本变量
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    /* db configure*/
    char server[] = "127.0.0.1";
    char user[] = "root";
    char password[] = "1malegebi";
    char database[] = "user";
    int  port = 3306;
    conn = mysql_init(NULL);

    bool userExist = FALSE;
    bool regSuccess = FALSE;
    char userInsert[150];

    //连接数据库，如果连接失败则会终止程序并且报出错误信息
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //遍历数据库看用户名是否已经存在
    if (mysql_query(conn, "select username from users;")) {
        //ConnDB(conn,user,password,database,port);
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //得到数据库的用户名数据
    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], userName) == 0) {
            userExist = TRUE;
            break;
        }
    }

    if (userExist) {
        //关闭数据库
        mysql_close(conn);

        printf("用户名已存在！\n");
        return FALSE;
    }
    else {
        //将用户信息插入数据库
        sprintf(userInsert, "INSERT INTO users (username,pwd,largeEXP,middleEXP,smallEXP,AoErJia,tower,Soul) VALUE(\"%s\",\"%s\",0,0,0,1,1,0)", userName, pwd);
        if (mysql_query(conn, userInsert)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(0);
        }
        //关闭数据库
        mysql_close(conn);

        printf("注册成功！\n");
        return TRUE;
    }
}


void UserLogOrReg(char userName[],char pwd[]) {
    bool logSuccess = FALSE;
    while (true) {
        printf("输入1为登录，输入r为注册：");
        char userSelect;
        userSelect = getchar();
        switch (userSelect) {
        case 'l': {
            //选择登录后用UserLog检测登录
            if (UserLog(userName, pwd) == TRUE) {
                logSuccess = TRUE;
            }
            break;
        }
        case 'r': {
            //选择注册，注册成功后回到登录界面
            if (UserReg(userName,pwd) == TRUE) {
                if (UserLog(userName, pwd) == 1) {
                    logSuccess = TRUE;
                }
            }
            break;
        }
        default: {printf("请输入正确指令！\n"); break; }
        }
        if (logSuccess) break;
    }
    system("pause");
}
