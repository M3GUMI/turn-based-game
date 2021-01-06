#include <winsock2.h>
#include<windows.h>
#include <winsock.h>
#include <mysql.h> //���ݿ�ı������ͺͺ���
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<graphics.h>//�ṩͼ�λ������ͷ�ļ�
#include<easyx.h>//�ṩͼ�λ������ͷ�ļ�
#include "�û���¼ע��.h"//ʵ�ֵ�¼ע���ͷ�ļ�
#pragma comment(lib,"Winmm.lib")
#include<mmsystem.h>

/***********************************************
*              �û���¼ע��ϵͳ ��             *
*   �õ��û�������˺����벢�ұ������ݿ���   *
*       �õ��Ƿ�ע����ߵ�¼�ɹ��Ľ��         *
************************************************/

bool UserLog(char userName[],char pwd[]) {
    //��ʾ�û������¼��Ϣ
    printf("�������û���(ʮλ����)��");
    scanf("%s", userName);
    printf("����������(ʮλ����)��");
    scanf("%s", pwd);

    //��鳤���Ƿ�ϸ�
    if (strlen(userName) > 11 || strlen(pwd) > 11) {
        printf("������ʮλ���ڵ��ַ�����\n");
        return FALSE;
    }

    //�����������ݿ�Ļ�������
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

    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //���ͱ������ݿ��������ʧ�ܱ���������Ϣ
    if (mysql_query(conn, "select username,pwd from users")) {
        //ConnDB(conn,user,password,database,port);
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�ռ����ݿ���Ϣ
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    //�ȱ������ݿ����û��Ƿ����
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], userName) == 0) {
            userExist = TRUE;
            break;
        }
    }
    if (!userExist) {
        printf("�û�������\n");
        return FALSE;
    }

    //���֮ǰ�Ľ��
    mysql_free_result(res);

    //���²�ѯ
    if (mysql_query(conn, "select username,pwd from users")) {
        //ConnDB(conn,user,password,database,port);
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�õ���ѯ���
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);


    //�������ݿ�鿴�û������Ƿ���ȷ
    while ((row = mysql_fetch_row(res)) != NULL) {
        if ((strcmp(row[0], userName) == 0) && (strcmp(row[1], pwd) == 0)) {
            logSuccess = TRUE;
            break;
        }
    }



    //�ر����ݿ�
    mysql_close(conn);


    if (logSuccess) {
        printf("��½�ɹ���\n");
        return TRUE;
    }
    else {
        printf("�������\n");
        return FALSE;
    }

}


bool UserReg(char userName[],char pwd[]) {
    //��ʾ�û�����
    printf("�������û���(ʮλ����)��");
    scanf("%s", userName);
    printf("���������루ʮλ���ڣ���");
    scanf("%s", pwd);

    //��鳤���Ƿ�ϸ�
    if (strlen(userName) > 11 || strlen(pwd) > 11) {
        printf("������ʮλ���ڵ��ַ�����\n");
        return FALSE;
    }

    //�����������ݿ�Ļ�������
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

    //�������ݿ⣬�������ʧ�������ֹ�����ұ���������Ϣ
    if (!mysql_real_connect(conn, NULL,
        user, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�������ݿ⿴�û����Ƿ��Ѿ�����
    if (mysql_query(conn, "select username from users;")) {
        //ConnDB(conn,user,password,database,port);
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(0);
    }

    //�õ����ݿ���û�������
    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], userName) == 0) {
            userExist = TRUE;
            break;
        }
    }

    if (userExist) {
        //�ر����ݿ�
        mysql_close(conn);

        printf("�û����Ѵ��ڣ�\n");
        return FALSE;
    }
    else {
        //���û���Ϣ�������ݿ�
        sprintf(userInsert, "INSERT INTO users (username,pwd,largeEXP,middleEXP,smallEXP,AoErJia,tower,Soul) VALUE(\"%s\",\"%s\",0,0,0,1,1,0)", userName, pwd);
        if (mysql_query(conn, userInsert)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(0);
        }
        //�ر����ݿ�
        mysql_close(conn);

        printf("ע��ɹ���\n");
        return TRUE;
    }
}


void UserLogOrReg(char userName[],char pwd[]) {
    bool logSuccess = FALSE;
    while (true) {
        printf("����1Ϊ��¼������rΪע�᣺");
        char userSelect;
        userSelect = getchar();
        switch (userSelect) {
        case 'l': {
            //ѡ���¼����UserLog����¼
            if (UserLog(userName, pwd) == TRUE) {
                logSuccess = TRUE;
            }
            break;
        }
        case 'r': {
            //ѡ��ע�ᣬע��ɹ���ص���¼����
            if (UserReg(userName,pwd) == TRUE) {
                if (UserLog(userName, pwd) == 1) {
                    logSuccess = TRUE;
                }
            }
            break;
        }
        default: {printf("��������ȷָ�\n"); break; }
        }
        if (logSuccess) break;
    }
    system("pause");
}
