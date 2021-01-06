#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "����ϵͳ.h"

/**************************************
*               ����ϵͳ ��           *
*      �õ�boss�Ļ���������ݺͼ���   *
*         ���ҷ��ؼ��ܵĸ�����ֵ      *
***************************************/

#define false 0
#define true 1

struct Monster {
    char name[50];                     //�������� 
    char skillName[50];                //������������ 
    char buffName[50];                 //buff�������� 
    char recoverName[50];              //�ָ��������� 
    int  hpBossM;
    int  hpBossRatio;                  //�����ɳ�ֵ 
    int  atkBoss;
    int  atkBossRatio;                 //�����ɳ�ֵ 
    int  dpBoss;
    int  dpBossRatio;                  //�����ɳ�ֵ 
    int  skillRatio;                   //���ܱ��� 
    int  skillEffection;               //����Ч�� 
    int  recoverNum;                   //�ָ��� 
};


//�����������
struct Monster monster[10] = {
    {"Mr.Banana","���ٵ���","���Ż���","��������㽶",380,50,20,3,20,4,5,2,95},
    {"van","ǿ������","fa��������","DDF",200,20,11,1,11,1,3,2,50},
    {"magicalMan","�����绪","΢Ц","TOC",220,20,12,1,12,1,3,2,55},
    {"dunner","ѩɽ����","����","TYLOO",240,20,13,1,13,1,4,2,60},
    {"niko","oneTap","��ɳӥ","ATEAM",260,30,14,2,14,2,4,2,65},
    {"s1mple","ä��","AWP","��Ǯ",280,30,15,2,15,2,3,2,70},
    {"eggplant","���Ѿ�","�׸�","WDNMD",300,30,16,2,16,2,4,2,75},
    {"paymon","�𻪻���","Ӧ��ʳ��","ʮ����",320,40,17,2,17,3,4,2,80},
    {"baoGuoMa","�ɹ�����������","����","��",340,40,17,2,18,3,5,2,85},
    {"calculus","̩�չ�ʽ","��ش�","����ѧ��",360,40,19,3,19,3,5,2,90},
};


int hpBoss, hpBossM, atkBoss, dpBoss, levelBoss;//bossʵʱѪ��,Ѫ�����ֵ�������������������ȼ� 


//��ȡboss����
void BossAbility(int cs)                 //boss���� 
{
    levelBoss = cs;
    int bossNum;


    //ÿʮ���Ӧ�ֵı��
    bossNum = cs % 10;

    hpBossM = monster[bossNum].hpBossM + (levelBoss - 1) * monster[bossNum].hpBossRatio;
    dpBoss = monster[bossNum].dpBoss + (levelBoss - 1) * monster[bossNum].dpBossRatio;
    atkBoss = monster[bossNum].atkBoss + (levelBoss - 1) * monster[bossNum].atkBossRatio;
    hpBoss = hpBossM;
}


//��ȡboss������ֵ
int GetBossHp() {
    return hpBoss;
}


//����boss������ֵ
void SetBossHp(int hp) {
    hpBoss = hp;
}


//��ȡboss�������ܵ��˺�
int BossDamage(int cs)                //�˺�����
{
    int harm,bossNum;
    bossNum = cs % 10;
    harm = atkBoss * 1;
    return harm;
}


//��boss���Լӳ�
void BossBuff(int cs)          //buff���棬��ʮ�㼰ʮ�ı�����atk��dp�����棬�����������atk���� 
{
    int bossNum = cs % 10;
    if (cs % 10 != 0)
        atkBoss = atkBoss * monster[bossNum].atkBossRatio;
    else {
        atkBoss = atkBoss * monster[bossNum].atkBossRatio;
        dpBoss = dpBoss * monster[bossNum].dpBossRatio;
    }
}


//��boss�ظ�
void BossRecover(int cs)       //�ָ����ܣ�ÿһ����ݻ����ظ������ϲ����ɳ�ֵ�ָ�Ѫ�� 
{
    int bossNum = cs % 10;
    hpBoss = hpBoss + monster[bossNum].recoverNum + cs * 5;
    if (hpBoss > hpBossM)
        hpBoss = hpBossM;
}