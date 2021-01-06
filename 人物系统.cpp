#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "人物系统.h"

/**************************************
*               人物系统 ！           *
*      得到人物的基本面板数据和技能   *
*       并且返回技能伤害等各种数值    *
***************************************/

#define false 0
#define true 1


struct character {
    char name[25];
    int HP;
    int MP;
    int ATK;
    int DP;
    int HPRatio;
    int MPRatio;
    int ATKRatio;
    int DPRatio;
    char skillName1[999];
    char skillName2[999];
    char skillName3[999];
};


struct character character[6] = {
   {"奥尔加",100,15,30,15,10,1,2,2,"射的很准：造成伤害","钢铁雄风：造成基于最大生命值的伤害","希望之花：回复当前生命值的一半"},
   {"DVA",100,10,30,15,20,1,2,2,"精准射击：造成伤害","这很IMBA：造成基于最大生命值的伤害","防御矩阵：回复最大生命值的五分之一"},
   {"蔡徐坤",100,10,30,15,10,1,4,2,"篮球投掷：造成伤害","跳：造成伤害回复等额生命值","鸡你太美：造成巨额伤害自身也受到一半伤害"},
   {"氪师傅",100,10,30,15,10,1,2,4,"辟邪剑法：造成伤害","刮痧：造成基于防御力的伤害，提高防御力","一碗牛杂：基于防御力的伤害"},
   {"比利王",100,10,30,15,10,2,2,2,"不灭之握：造成伤害","森之妖精：恢复三点法力值","长眠的理想乡：造成基于当前法力值的伤害"},
   {"欧皇",100,10,30,15,20,2,4,4,"欧皇之力：造成伤害","欧皇蔑视：一半概率回复半血，一半概率扣四分之一血","高贵血统：（被动）基础属性成长值是他人两倍"},
};


int finalHp, finalMp, finalAtk, finalDp, damage, MHp, MMp;//实时血量，实时蓝量，实时蓝量，实时攻击力，实时防御力，攻击数值，总血量，总蓝量
int character_List[6] = { true };//人物列表，第一个为初始人物

void CharacterAbility(int number,int level)
{
    finalHp = MHp = character[number].HP + (level - 1) * character[number].HPRatio;//计算人物总血量
    finalMp = MMp = character[number].MP + (level - 1) * character[number].MPRatio;//计算人物总蓝量
    finalAtk = character[number].ATK + (level - 1) * character[number].ATKRatio;	//计算人物攻击力
    finalDp = character[number].DP + (level - 1) * character[number].DPRatio;//计算人物防御力
}


void SetCharacterHp(int hp) {
    finalHp = hp;
}

struct characterInform GetCharacInform(){
    struct characterInform character;
    character.Hp = finalHp;
    character.Mp = finalMp;
    character.damage = damage;
    return character;
}

int CharacSkill1(int number)
{
    if (finalMp <= 0)//判定蓝量是否足够放技能
        printf("大爷，你没蓝了。");
    else
        if (number == 2)
        {
            damage = finalAtk * 3;
            finalMp -= 1;
        }
        else
        {
            damage = finalAtk * 4.5;
            finalMp -= 1;
        }

    return damage;//返回攻击数值
}

int CharacSkill2(int number)
{
    srand((unsigned)time(NULL));
    if (number == 4)//判定是否为四号人物的二技能
    {
        finalMp += 3;
        damage = 0;
    }
    else if (finalMp < 2)//判定蓝量是否小于2
        printf("大爷，你没蓝了。");
    else
        switch (number)
        {
        case 0: {
            damage = finalAtk + finalDp + finalHp * 0.2;
            finalMp -= 2;
            break;
        }
        case 1: {
            damage = finalAtk + MHp * 0.2;
            finalHp = finalHp + MHp * 0.2;
            finalMp -= 2;
            break;
        }
        case 2: {
            damage = finalAtk * 2;
            finalHp = finalHp + damage;
            finalMp -= 2;
            break;
        }
        case 3: {
            damage = finalAtk + finalDp;
            finalDp = finalDp * 2;
            finalMp -= 2;
            break;
        }
        case 5: {
            if (rand() % 2 == 0)
                finalHp = finalHp + MHp * 0.5;
            else
                finalHp = finalHp - MHp * 0.25;
            break;
        }
        }
    if (finalHp >= MHp)//判定血量是否超过总血量
        finalHp = MHp;

    if (finalMp >= MMp)//判定蓝量是否超过总蓝量
        finalMp = MMp;

    return damage;//返回攻击数值
}

int CharacSkill3(int number)
{
    if (finalMp < 4)//判定蓝量是否足够放技能
        printf("大爷，你没蓝了。");
    else
        switch (number)
        {
        case 0: {
            finalHp = finalHp * 1.5;
            damage = 0; 
            finalMp -= 4;
            break;
        }
        case 1: {
            damage = finalAtk * 3 + finalHp * 0.5;
            finalHp = finalHp * 0.5;
            finalMp -= 4;
            break;
        }
        case 2: {
            damage = finalAtk * 6;
            finalHp = finalHp - finalAtk * 3;
            finalMp -= 4;
            if (finalHp <= 0) {
                finalHp = 1;
            }
            break;
        }
        case 3: {
            damage = finalAtk * 3 + finalDp * 0.5;
            finalDp = finalDp * 0.5;
            finalMp -= 4;
            break;
        }
        case 4: {
            if (finalMp < 6) {
                damage = 0;
                break;
            }
            else
                damage = finalAtk + finalMp * 5;
            finalMp -= 6;
            break;
        }
              if (finalHp >= MHp)//判定血量是否超过总血量
                  finalHp = MHp;

              if (finalMp >= MMp)//判定蓝量是否超过总蓝量
                  finalMp = MMp;

              return damage;//返回攻击数值
        }
}
