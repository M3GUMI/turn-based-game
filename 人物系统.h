/**************************************
*               ����ϵͳ ��           *
*      �õ�����Ļ���������ݺͼ���   *
*       ���ҷ��ؼ����˺��ȸ�����ֵ    *
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

