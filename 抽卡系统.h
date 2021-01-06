/**************************************
*               抽卡系统 ！           *
* 实现抽卡的后端逻辑和抽卡记录的储存  *
***************************************/
int OnePick(void);
void Result_Save(int random, char userName[]);
char* File_Name(char userName[]);
char* Cur_Time(void);
void Result_Look(char userName[]);
