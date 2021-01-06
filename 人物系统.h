/**************************************
*               人物系统 ！           *
*      得到人物的基本面板数据和技能   *
*       并且返回技能伤害等各种数值    *
***************************************/
struct characterInform {
	int Hp;
	int Mp;
	int damage;
};
void CharacterAbility(int number, int level);
int CharacSkill1(int number);
int CharacSkill2(int number);
int CharacSkill3(int number);
struct characterInform GetCharacInform();
void SetCharacterHp(int hp);

