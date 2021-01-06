#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "����ϵͳ.h"

/**************************************
*               ����ϵͳ ��           *
*      �õ�����Ļ���������ݺͼ���   *
*       ���ҷ��ؼ����˺��ȸ�����ֵ    *
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
   {"�¶���",100,15,30,15,10,1,2,2,"��ĺ�׼������˺�","�����۷磺��ɻ����������ֵ���˺�","ϣ��֮�����ظ���ǰ����ֵ��һ��"},
   {"DVA",100,10,30,15,20,1,2,2,"��׼���������˺�","���IMBA����ɻ����������ֵ���˺�","�������󣺻ظ��������ֵ�����֮һ"},
   {"������",100,10,30,15,10,1,4,2,"����Ͷ��������˺�","��������˺��ظ��ȶ�����ֵ","����̫������ɾ޶��˺�����Ҳ�ܵ�һ���˺�"},
   {"�ʦ��",100,10,30,15,10,1,2,4,"��а����������˺�","������ɻ��ڷ��������˺�����߷�����","һ��ţ�ӣ����ڷ��������˺�"},
   {"������",100,10,30,15,10,2,2,2,"����֮�գ�����˺�","ɭ֮�������ָ����㷨��ֵ","���ߵ������磺��ɻ��ڵ�ǰ����ֵ���˺�"},
   {"ŷ��",100,10,30,15,20,2,4,4,"ŷ��֮��������˺�","ŷ�����ӣ�һ����ʻظ���Ѫ��һ����ʿ��ķ�֮һѪ","�߹�Ѫͳ�����������������Գɳ�ֵ����������"},
};


int finalHp, finalMp, finalAtk, finalDp, damage, MHp, MMp;//ʵʱѪ����ʵʱ������ʵʱ������ʵʱ��������ʵʱ��������������ֵ����Ѫ����������
int character_List[6] = { true };//�����б���һ��Ϊ��ʼ����

void CharacterAbility(int number,int level)
{
    finalHp = MHp = character[number].HP + (level - 1) * character[number].HPRatio;//����������Ѫ��
    finalMp = MMp = character[number].MP + (level - 1) * character[number].MPRatio;//��������������
    finalAtk = character[number].ATK + (level - 1) * character[number].ATKRatio;	//�������﹥����
    finalDp = character[number].DP + (level - 1) * character[number].DPRatio;//�������������
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
    if (finalMp <= 0)//�ж������Ƿ��㹻�ż���
        printf("��ү����û���ˡ�");
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

    return damage;//���ع�����ֵ
}

int CharacSkill2(int number)
{
    srand((unsigned)time(NULL));
    if (number == 4)//�ж��Ƿ�Ϊ�ĺ�����Ķ�����
    {
        finalMp += 3;
        damage = 0;
    }
    else if (finalMp < 2)//�ж������Ƿ�С��2
        printf("��ү����û���ˡ�");
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
    if (finalHp >= MHp)//�ж�Ѫ���Ƿ񳬹���Ѫ��
        finalHp = MHp;

    if (finalMp >= MMp)//�ж������Ƿ񳬹�������
        finalMp = MMp;

    return damage;//���ع�����ֵ
}

int CharacSkill3(int number)
{
    if (finalMp < 4)//�ж������Ƿ��㹻�ż���
        printf("��ү����û���ˡ�");
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
              if (finalHp >= MHp)//�ж�Ѫ���Ƿ񳬹���Ѫ��
                  finalHp = MHp;

              if (finalMp >= MMp)//�ж������Ƿ񳬹�������
                  finalMp = MMp;

              return damage;//���ع�����ֵ
        }
}
