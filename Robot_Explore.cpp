/*������λ·������*/
/* 0 1 2
   3 p 4
   5 6 7*/  
/*����ı��ͼ�ߴ������޸ĺ궨���е�row��column��ֵ*/ 
/*����ı���������ٶ�����ı����³���������Sleep�����в�����ֵ*/
/*�˳��򲢲�֧����ڵ㲻��ԭ������*/
/*-------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

#define robot_position 'R'
#define row 18
#define column 56 //���ݵ�ͼ�ߴ��С�ı������ֵ 

int Obligatory_temp = 0; //���뵽��Ŀ������ͳ�� 
int Necessary_temp = 0;//�ɵ����Ŀ��� 
char Direction_temp[10000] = {0}; //��λ�ݴ����� 
int temp = 0;//��λ�ݴ������±� 
char Map_temp[row][column];//��ͼԪ���ݴ����� 

void Map_Init();
void Map_show(); //�������� 

struct Robot_Nature{
	int Axis[2]; //����������λ�ýṹ�� 
}Robot;

struct Necessary_Target{
	char Direction[10000]; //�����ԭ��ķ�λ·�� 
	int Axis[2]; //Ŀ������� 
	int Distance; //��ԭ��ľ��� 
}Necessary_Net[20];

struct Obligatory_Target{
	char Direction[10000];
	int Axis[2];
	int Distance;
}Obligatory_Net[20];

struct Map{
	char nature; //�õ������ 
	int Axis[2]; //�õ���ͼ�ϵ����� 
	struct Map *Next_Element[8];//����Χ���ܵ����˸���һ���ڵ� 
	struct Map *Last_Element; //������һ���ڵ� 
	int Last_Element_Mark;
	int Invisited ; //�Ƿ񱻷��ʹ� 
	
}Map_Element[row][column],*Entrance = &Map_Element[0][0]; /*��ʼ����ͼԪ�ؽṹ��*/


void Check_Round_FindFather(struct Map *p,int flag){
	int Axis[2] = {p->Axis[0],p->Axis[1]}; //��ȡ���� 
	for(int i=0 ;i<8;i++){ /*�ж���һ���ڵ㲻��ǽ��û�б����ʹ��Ҹõ��ڵ�ͼ���Ǵ��ڵģ����������������Ϊ�ɵ������һ���ڵ�*/ 
	   if(i == 0) p->Next_Element[i] = ((Axis[0]-1>=0&&Axis[0]-1<=row-1)&&(Axis[1]-1>=0&&Axis[1]-1<=column-1))?((Map_Element[Axis[0]-1][Axis[1]-1].Invisited != 1&&Map_Element[Axis[0]-1][Axis[1]-1].nature!='.'&&Map_Element[Axis[0]-1][Axis[1]-1].Last_Element == NULL)? &Map_Element[Axis[0]-1][Axis[1]-1]:NULL):NULL;
		if(i == 1) p->Next_Element[i] = ((Axis[0]-1>=0&&Axis[0]-1<=row-1)&&(Axis[1]>=0&&Axis[1]<=column-1))?((Map_Element[Axis[0]-1][Axis[1]].Invisited != 1&&Map_Element[Axis[0]-1][Axis[1]].nature!='.'&&Map_Element[Axis[0]-1][Axis[1]].Last_Element == NULL)? &Map_Element[Axis[0]-1][Axis[1]]:NULL):NULL;
		if(i == 2) p->Next_Element[i] = ((Axis[0]-1>=0&&Axis[0]-1<=row-1)&&(Axis[1]+1>=0&&Axis[1]+1<=column-1))?((Map_Element[Axis[0]-1][Axis[1]+1].Invisited != 1&&Map_Element[Axis[0]-1][Axis[1]+1].nature!='.'&&Map_Element[Axis[0]-1][Axis[1]+1].Last_Element == NULL)? &Map_Element[Axis[0]-1][Axis[1]+1]:NULL):NULL;
		if(i == 3) p->Next_Element[i] = ((Axis[0]>=0&&Axis[0]<=row-1)&&(Axis[1]-1>=0&&Axis[1]-1<=column-1))?((Map_Element[Axis[0]][Axis[1]-1].Invisited != 1&&Map_Element[Axis[0]][Axis[1]-1].nature!='.'&&Map_Element[Axis[0]][Axis[1]-1].Last_Element == NULL)? &Map_Element[Axis[0]][Axis[1]-1]:NULL):NULL;
		if(i == 4) p->Next_Element[i] = ((Axis[0]>=0&&Axis[0]<=row-1)&&(Axis[1]+1>=0&&Axis[1]+1<=column-1))?((Map_Element[Axis[0]][Axis[1]+1].Invisited != 1&&Map_Element[Axis[0]][Axis[1]+1].nature!='.'&&Map_Element[Axis[0]][Axis[1]+1].Last_Element == NULL)? &Map_Element[Axis[0]][Axis[1]+1]:NULL):NULL;
		if(i == 5) p->Next_Element[i] = ((Axis[0]+1>=0&&Axis[0]+1<=row-1)&&(Axis[1]-1>=0&&Axis[1]-1<=column-1))?((Map_Element[Axis[0]+1][Axis[1]-1].Invisited != 1&&Map_Element[Axis[0]+1][Axis[1]-1].nature!='.'&&Map_Element[Axis[0]+1][Axis[1]-1].Last_Element == NULL)? &Map_Element[Axis[0]+1][Axis[1]-1]:NULL):NULL;
		if(i == 6) p->Next_Element[i] = ((Axis[0]+1>=0&&Axis[0]+1<=row-1)&&(Axis[1]>=0&&Axis[1]<=column-1))?((Map_Element[Axis[0]+1][Axis[1]].Invisited != 1&&Map_Element[Axis[0]+1][Axis[1]].nature!='.'&&Map_Element[Axis[0]+1][Axis[1]].Last_Element == NULL)? &Map_Element[Axis[0]+1][Axis[1]]:NULL):NULL;
		if(i == 7) p->Next_Element[i] = ((Axis[0]+1>=0&&Axis[0]+1<=row-1)&&(Axis[1]+1>=0&&Axis[1]+1<=column-1))?((Map_Element[Axis[0]+1][Axis[1]+1].Invisited != 1&&Map_Element[Axis[0]+1][Axis[1]+1].nature!='.'&&Map_Element[Axis[0]+1][Axis[1]+1].Last_Element == NULL)? &Map_Element[Axis[0]+1][Axis[1]+1]:NULL):NULL;
		if(p->Next_Element[i]!=NULL&&flag == 1){
			p->Next_Element[i]->Last_Element = p; //��ǿɵ������һ���ڵ� ����һ���ڵ㣨���ýڵ㱾�� 
			p->Next_Element[i]->Last_Element_Mark = i;
		}
	}

	
}

/*��Ҫע����ǣ��������ڵ�ӵ��ͬһ���ӽڵ�ʱ�����ȡ�ĸ��ڵ㽫���ӽڵ����ǿ�ж�㣬�����ܴ�����ǰ�ڵ���ӽڵ�ȱʧ�������*/

int Check_NULL(struct Map *s){ //����Ƿ�����һ���ڵ㣬����еĻ�����1�����򷵻�0 
	for(int i = 0;i < 8; i++){
		if(s->Next_Element[i]!=NULL){
			return 1;
		}
	}
	return 0;
}

void Visit(struct Map *p){
	Direction_temp[temp] = p->Last_Element_Mark + '0'; //��¼��ǰ·�� 
	Direction_temp[++temp] = '\0';
	p->Invisited = 1;  //�ѷ��ʹ� 
	Check_Round_FindFather(p,1); //���ýڵ���Χ��Ѱ����һ���ڵ� 
	
	if(p->nature == '*'){ //�����Findable target 
		strcpy(Necessary_Net[Necessary_temp].Direction,Direction_temp); //���Ƶ�ǰ·����Ŀ���·�� 
		Necessary_Net[Necessary_temp].Axis[0] = p->Axis[0];  //��¼���� 
		Necessary_Net[Necessary_temp].Axis[1] = p->Axis[1]; 
		Necessary_Net[Necessary_temp].Distance = strlen(Direction_temp) - 1; //��¼���ȡ�����ͷ��㲻�����ܳ��ȹ���-1 
		Necessary_temp++;
	}
	if(p->nature == '#'){ //�����Obligatory target 
		strcpy(Obligatory_Net[Obligatory_temp].Direction,Direction_temp);
		Obligatory_Net[Obligatory_temp].Axis[0] = p->Axis[0];
		Obligatory_Net[Obligatory_temp].Axis[1] = p->Axis[1];
		Obligatory_Net[Obligatory_temp].Distance = strlen(Direction_temp) - 1;
		Obligatory_temp++;
	}
	
	Map_Init();
	Map_temp[p->Axis[0]][p->Axis[1]] = robot_position;
	Sleep(100); /*���Ĳ������������ٶ�*/
	system("cls");
	Map_show();
	/*��ʼ������ͼ�ݴ����飬��ͼ�������£�������һ֡���棬�����˷�λ�ƶ�*/
}

void Go_Back_FatherNet(struct Map *p){
	
	int flag = 0; //���ؽ������ 
	while(flag == 0){
		for(int i = 0;i<8;i++){
			if(p->Next_Element[i]==NULL){
				
				continue; //�����ǰ�ڵ����ӽڵ� 
			}else{
				flag = 1;
				break;//����еĻ��ͽ��� 
			}
		}
		if(flag == 0){
			Direction_temp[--temp] = '\0'; //�����ǰ�ڵ����ӽڵ㣬�������ǰ·����ĩλ 
			Map_Init();
			Map_temp[p->Last_Element->Axis[0]][p->Last_Element->Axis[1]] = robot_position;
			Sleep(100);/*���Ĳ������������ٶ�*/
			system("cls");
			Map_show();
			/*���»���*/
			p->Last_Element->Next_Element[p->Last_Element_Mark] = NULL; //��ǰһ���ڵ�ָ��ǰ�ڵ��ָ����Ϊ�� 
			p = p->Last_Element; //��������һ���ڵ� 
		}
	}
	
}

void Map_Save(){
	/*�����ͼ*/
	FILE *fp;
	fp = fopen("Map1.txt","r"); //�����ȡ�����ĵ�ͼ����ĵ�ͼ�ļ����� 
	char ch;
	int i = 0;
	int j = 0;
	while(fp != NULL&&!(i==row - 1&&j==column)){
		(Map_Element[i][j]).nature = fgetc(fp);
		printf("%c",(Map_Element[i][j]).nature);
		Map_Element[i][j].Axis[0] = i;
		Map_Element[i][j].Axis[1] = j;
		if(j!=column){
			j++;
			continue;
		}else{
			
			i++;
			j = 0;
			continue;
		}
		
	}
	fclose(fp);
}
void Map_Init(){
	for(int i = 0 ; i<row ; i++) for(int j=0 ;j < column ; j++) {
		Map_temp[i][j] = Map_Element[i][j].nature;
	}
}

void Map_show(){ /*�����ǰ��ͼ*/
	for(int i = 0 ; i<row ; i++){
		for(int j = 0; j < column ; j++){
			printf("%c",Map_temp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	if(Necessary_temp != 0){
		for(int i = 0;i<Necessary_temp ;i++){
			printf("Findable Target[%d] Has Been Found !\n",i+1);
			printf("Axis: (%d, %d)  ",Necessary_Net[i].Axis[0],Necessary_Net[i].Axis[1]);
			printf("Distance: %d\n",Necessary_Net[i].Distance);
			printf("Directions: ",i+1);
			puts(Necessary_Net[i].Direction+1);
			printf("\n");
		}
	}
	if(Obligatory_temp != 0){
		for(int i = 0;i<Obligatory_temp ; i++){
			printf("Obligatory Target[%d] Has Been Found !\n",i+1);
			printf("Axis: (%d, %d)  ",Obligatory_Net[i].Axis[0],Obligatory_Net[i].Axis[1]);
			printf("Distance: %d\n",Obligatory_Net[i].Distance);
			printf("Directions:  ",i+1);
			puts(Obligatory_Net[i].Direction+1);
			printf("\n");
		}
	}
}

void DFS(struct Map *p){
	int i = p->Axis[0]; //�����ͼԪ������ 
	int j = p->Axis[1];
	Robot.Axis[0] = i; //���»�������������ǰ���� 
	Robot.Axis[1] = j;
	
	Visit(p); //�Ե�ǰ�ڵ���з��� 
	
	if(Check_NULL(p) == 0){
		Go_Back_FatherNet(p); //�����ǰ�ڵ����ӽڵ㣬�򷵻��丸�ڵ㣬�ݹ鷵�أ�ֱ����ǰ�ڵ����ӽڵ�λ�� 
		if(p == &Map_Element[0][0]){ //������ص���ԭ�㣬���������������������������˳� 
			exit(0);
		}
	}else{ //������ӽڵ�Ļ������ 
		for(int k = 0;k<8;k++){
		if(p->Next_Element[k]!=NULL) DFS(p->Next_Element[k]);
		}
	}	
}

int main(){
	Robot.Axis[0] = 0;
	Robot.Axis[1] = 0; //��ʼ��������λ�� 
	Map_Save(); //���ļ��ж�ȡ��ͼ 
	Map_Init(); //��ͼ�ݴ������ʼ�� 
	
	DFS(Entrance); //����������� 
	
	return 0; 
}
