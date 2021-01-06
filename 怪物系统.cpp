#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "怪物系统.h"

/**************************************
*               怪物系统 ！           *
*      得到boss的基本面板数据和技能   *
*         并且返回技能的各种数值      *
***************************************/

#define false 0
#define true 1

struct Monster {
    char name[50];                     //怪物名称 
    char skillName[50];                //攻击技能名称 
    char buffName[50];                 //buff技能名称 
    char recoverName[50];              //恢复技能名称 
    int  hpBossM;
    int  hpBossRatio;                  //生命成长值 
    int  atkBoss;
    int  atkBossRatio;                 //攻击成长值 
    int  dpBoss;
    int  dpBossRatio;                  //防御成长值 
    int  skillRatio;                   //技能倍率 
    int  skillEffection;               //技能效果 
    int  recoverNum;                   //恢复量 
};


//定义怪物数据
struct Monster monster[10] = {
    {"Mr.Banana","蕉迟但到","自信回眸","美利坚大香蕉",380,50,20,3,20,4,5,2,95},
    {"van","强人锁男","fa♂声乐器","DDF",200,20,11,1,11,1,3,2,50},
    {"magicalMan","致命风华","微笑","TOC",220,20,12,1,12,1,3,2,55},
    {"dunner","雪山剑法","挑衅","TYLOO",240,20,13,1,13,1,4,2,60},
    {"niko","oneTap","火沙鹰","ATEAM",260,30,14,2,14,2,4,2,65},
    {"s1mple","盲狙","AWP","还钱",280,30,15,2,15,2,3,2,70},
    {"eggplant","发把狙","白给","WDNMD",300,30,16,2,16,2,4,2,75},
    {"paymon","金华火腿","应急食物","十连抽",320,40,17,2,17,3,4,2,80},
    {"baoGuoMa","松果闪电五连鞭","化劲","闪",340,40,17,2,18,3,5,2,85},
    {"calculus","泰勒公式","洛必达","不讲学德",360,40,19,3,19,3,5,2,90},
};


int hpBoss, hpBossM, atkBoss, dpBoss, levelBoss;//boss实时血量,血量最大值，攻击力，防御力，等级 


//获取boss数据
void BossAbility(int cs)                 //boss数据 
{
    levelBoss = cs;
    int bossNum;


    //每十层对应怪的编号
    bossNum = cs % 10;

    hpBossM = monster[bossNum].hpBossM + (levelBoss - 1) * monster[bossNum].hpBossRatio;
    dpBoss = monster[bossNum].dpBoss + (levelBoss - 1) * monster[bossNum].dpBossRatio;
    atkBoss = monster[bossNum].atkBoss + (levelBoss - 1) * monster[bossNum].atkBossRatio;
    hpBoss = hpBossM;
}


//获取boss的生命值
int GetBossHp() {
    return hpBoss;
}


//设置boss的生命值
void SetBossHp(int hp) {
    hpBoss = hp;
}


//获取boss攻击技能的伤害
int BossDamage(int cs)                //伤害计算
{
    int harm,bossNum;
    bossNum = cs % 10;
    harm = atkBoss * 1;
    return harm;
}


//给boss属性加成
void BossBuff(int cs)          //buff增益，第十层及十的倍数层atk，dp都增益，其余层数仅有atk增益 
{
    int bossNum = cs % 10;
    if (cs % 10 != 0)
        atkBoss = atkBoss * monster[bossNum].atkBossRatio;
    else {
        atkBoss = atkBoss * monster[bossNum].atkBossRatio;
        dpBoss = dpBoss * monster[bossNum].dpBossRatio;
    }
}


//给boss回复
void BossRecover(int cs)       //恢复技能，每一层根据基础回复量加上层数成长值恢复血量 
{
    int bossNum = cs % 10;
    hpBoss = hpBoss + monster[bossNum].recoverNum + cs * 5;
    if (hpBoss > hpBossM)
        hpBoss = hpBossM;
}