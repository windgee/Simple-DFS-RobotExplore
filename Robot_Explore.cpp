/*������λ·������*/
/* 0 1 2
   3 p 4
   5 6 7*/  
/*����ı��ͼ�ߴ������޸ĺ궨���е�row��column��ֵ*/ 
/*����ı���������ٶ�����ı����³���������Sleep�����в�����ֵ*/
/*�˳��򲢲�֧����ڵ㲻��ԭ������*/

/*                         �����㷨�� �����������                               */
/*-------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>


#define robot_position 'R'
#define row 18
#define column 56 //���ݵ�ͼ�ߴ��С�ı������ֵ 
#define Max 100000

int Obligatory_temp = 0; //���뵽��Ŀ������ͳ�� 
int Necessary_temp = 0;//�ɵ����Ŀ��� 
int Target_temp = 0; //ͳ��Ŀ�������±� 
int Target_number = 0; //Ŀ���ĸ��� 

char Direction_temp[10000] = {0}; //��λ�ݴ����� 
int temp = 0;//��λ�ݴ������±� 
int finish = 0; //�������������� 

int ID_T = 0; //���������е�ȫ�ֱ��� 

char Map_temp[row][column];//��ͼԪ���ݴ����� 
/*------------------------------------------------------------------------��������----------------------------------------------------------------------*/
void Map_Save();//�����ͼ 
void Map_Init();   //��ͼ�ݴ������ʼ�� 
void Map_Element_Init(); //��ͼԪ�س�ʼ�� 
void Map_show();  //�������1 
void Map_show2(); //�������2 
void Map_Show3(); //�������3 
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Graph_Weight_Show(); //��ͼȨ����� 
int Locate_CheckID(int ID, int ID2); //��λID�е�����Ŀ���ID2����ṹ���е��±� 
int Graph_Connect(int ID); //�������㣬������Ȩ 
void Graph_Fix(); //�޸��ڽӾ��� 
void Graph_Init(); //��ʼ��ͼ��Ԫ�� 
void Simplify_Graph();  //�ص���·��ʹ�����н� 
int IF_Impasse(int ID); //����Ƿ�Ϊ���ڵ� 
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Robot_Seen(); //���������ܿ����ķ�Χ 
void Check_Round_FindFather(struct Map *p,int flag); //��鸽����8�����Ƿ���ߣ������� 
int Check_NULL(struct Map *s); //����Ƿ�Ϊ���ڵ� 
void Visit(struct Map *p); //��Ŀ��ڵ���з��� 
void Go_Back_FatherNet(struct Map *p); //�ص����ڵ� 
int DFS(struct Map *p); //�������������1�� 
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Reverse_Direction(char str[], char p[]); //��A->B��·��ת��ΪB->A��·�� 
void Visit2(struct Map *p); //��Ŀ�����з��� 
void Go_Back_FatherNet2(struct Map *p); //�ص����ڵ� 
int DFS2(struct Map *p); //�������������2�� 
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Adjacent_Target_Checker(); //����Ŀ��������Ŀ��� 
int DFS3(int ID); //�������������3�� 
void Back(int ID); //�ص����ڵ� 
void TSP(); //���������⣬̰���㷨 
void Play_Shortest_Road(); //����������·�� 
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
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

struct Target{ //����Ŀ���Ľṹ�� 
	int Axis[2];
	int ID;
	struct Target* Adjacent_Point[40]; //������������Ŀ������ڵ�����Ŀ��� 
	int Adjacent_Point_ID[40] = {0};  //����Ŀ����ID 
	int Adjacent_Point_Num = 0; //��Ŀ�����ӵ�е�����Ŀ�������� 
	char Direction[40][10000]; //��Ŀ��㵽����������Ŀ����·�� 
	int Distance[40]; //����������Ŀ��ľ��� 
}Target_Point[40];



struct Map{
	char nature; //�õ������ 
	int Axis[2]; //�õ���ͼ�ϵ����� 
	struct Map *Next_Element[8];//����Χ���ܵ����˸���һ���ڵ� 
	struct Map *Last_Element; //������һ���ڵ� 
	int Last_Element_Mark;
	int Invisited ; //�Ƿ񱻷��ʹ� 
	int ID;
	int Seen; //�Ƿ��ܱ������˿��� 
}Map_Element[row][column],*Entrance = &Map_Element[0][0]; /*��ʼ����ͼԪ�ؽṹ��*/


/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

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
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
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
		Target_Point[Target_temp].ID = Target_temp;
		p->ID = Target_temp;
		Target_Point[Target_temp].Axis[0] = p->Axis[0]; //Target�ṹ��ͬʱ��¼ 
		Target_Point[Target_temp].Axis[1] = p->Axis[1];
		Target_temp++; 
		Necessary_temp++;
	}
	if(p->nature == '#'){ //�����Obligatory target 
		strcpy(Obligatory_Net[Obligatory_temp].Direction,Direction_temp);
		Obligatory_Net[Obligatory_temp].Axis[0] = p->Axis[0];
		Obligatory_Net[Obligatory_temp].Axis[1] = p->Axis[1];
		Obligatory_Net[Obligatory_temp].Distance = strlen(Direction_temp) - 1;
		p->ID = Target_temp;
		Target_Point[Target_temp].ID = Target_temp;
		Target_Point[Target_temp].Axis[0] = p->Axis[0];
		Target_Point[Target_temp].Axis[1] = p->Axis[1];
		Target_temp++; 
		Obligatory_temp++;
	}
	
	Map_Init();
	Map_temp[p->Axis[0]][p->Axis[1]] = robot_position;
	Robot.Axis[0] = p->Axis[0];
	Robot.Axis[1] = p->Axis[1];
	Sleep(100);
	system("cls");
	Map_show(); 
	/*��ʼ������ͼ�ݴ����飬��ͼ�������£�������һ֡���棬�����˷�λ�ƶ�*/
}

void Visit2(struct Map *p){
	if(p->Axis[0]!=Target_Point[Target_temp].Axis[0]||p->Axis[1]!=Target_Point[Target_temp].Axis[1]){ 
		Direction_temp[temp] = p->Last_Element_Mark + '0'; //��¼��ǰ·�� 
		Direction_temp[++temp] = '\0';
	}
	p->Invisited = 1;  //�ѷ��ʹ� 
	Check_Round_FindFather(p,1); //���ýڵ���Χ��Ѱ����һ���ڵ� 
	
	if((p->nature == '*'||p->nature == '#'||p == &Map_Element[0][0])&&(p->Axis[0]!=Target_Point[Target_temp].Axis[0]||p->Axis[1]!=Target_Point[Target_temp].Axis[1])){  //����Ŀ����ǲ������� 
		
		Target_Point[Target_temp].Adjacent_Point[Target_Point[Target_temp].Adjacent_Point_Num] = &Target_Point[p->ID];
		Target_Point[Target_temp].Distance[Target_Point[Target_temp].Adjacent_Point_Num] = strlen(Direction_temp);
		Target_Point[Target_temp].Adjacent_Point_ID[Target_Point[Target_temp].Adjacent_Point_Num] = p->ID;
		strcpy(Target_Point[Target_temp].Direction[Target_Point[Target_temp].Adjacent_Point_Num], Direction_temp);
		Target_Point[Target_temp].Adjacent_Point_Num++;
	}
	Map_Init();
	Map_temp[p->Axis[0]][p->Axis[1]] = robot_position;
	Robot.Axis[0] = p->Axis[0];
	Robot.Axis[1] = p->Axis[1];
	Sleep(100);
	system("cls");
	Map_show2(); 
	
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
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
			if(p != &Map_Element[0][0]){
				Map_temp[p->Last_Element->Axis[0]][p->Last_Element->Axis[1]] = robot_position;
				Robot.Axis[0] = p->Last_Element->Axis[0];
				Robot.Axis[1] = p->Last_Element->Axis[1];
			}else{
				Robot.Axis[0] = 0;
				Robot.Axis[1] = 0;
				Map_temp[0][0] = robot_position;
			}
			Sleep(100);
			system("cls");
			Map_show(); 
			
			if(p!=&Map_Element[0][0]){ 
				p->Last_Element->Next_Element[p->Last_Element_Mark] = NULL; //��ǰһ���ڵ�ָ��ǰ�ڵ��ָ����Ϊ�� 
				p = p->Last_Element; //��������һ���ڵ� 
			}else{
				flag = 1; //���������1 
			}
		}
	}
	
}
void Go_Back_FatherNet2(struct Map *p){
	
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
			if(p->Axis[0]!=Target_Point[Target_temp].Axis[0]||p->Axis[1]!=Target_Point[Target_temp].Axis[1]){ //����ǲ������� 
				Map_temp[p->Last_Element->Axis[0]][p->Last_Element->Axis[1]] = robot_position;
				Robot.Axis[0] = p->Last_Element->Axis[0];
				Robot.Axis[1] = p->Last_Element->Axis[1];
			}else{
				Robot.Axis[0] = 0;
				Robot.Axis[1] = 0;
				Map_temp[0][0] = robot_position;
			}
			
			Sleep(100);
			system("cls");
			Map_show2(); 
			/*���»���*/
			if(p->Axis[0]!=Target_Point[Target_temp].Axis[0]||p->Axis[1]!=Target_Point[Target_temp].Axis[1]){  //����ǲ������� 
				p->Last_Element->Next_Element[p->Last_Element_Mark] = NULL; //��ǰһ���ڵ�ָ��ǰ�ڵ��ָ����Ϊ�� 
				p = p->Last_Element; //��������һ���ڵ� 
			}else{
				flag = 1;
			} 
			
		}
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

void Map_Save(){
	/*�����ͼ*/
	FILE *fp; //�ļ�ָ�� 
	fp = fopen("Map1.txt","r"); //�����ȡ�����ĵ�ͼ����ĵ�ͼ�ļ����� 
	char ch;
	int i = 0;
	int j = 0;
	while(fp != NULL&&!(i==row - 1&&j==column)){
		(Map_Element[i][j]).nature = fgetc(fp); //��һ��ָ�����һλ 
		printf("%c",(Map_Element[i][j]).nature);
		Map_Element[i][j].Axis[0] = i; //������ 
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
	fclose(fp); //���ļ� 
}

void Map_Init(){
	for(int i = 0 ; i<row ; i++) for(int j=0 ;j < column ; j++) {
		Map_temp[i][j] = Map_Element[i][j].nature;
	}
} //��ԭ�ṹ���ж�ȡ 

void Map_Element_Init(){
	for(int i = 0; i < row; i++) for(int j = 0; j < column ; j++) Map_Element[i][j].Invisited = 0, Map_Element[i][j].Next_Element[8] = {NULL}, Map_Element[i][j].Last_Element_Mark = 0, Map_Element[i][j].Last_Element = NULL; //��ʼ�� 
}
void Robot_Seen(){
	int i = Robot.Axis[0];
	int j = Robot.Axis[1];
	//��Χ�˸����ǿ��Կ����ģ�Ҫ���Ʊ߽� 
	if(i-1>=0&&i-1<=row-1&&j-1>=0&&j-1<=column-1) Map_Element[i-1][j-1].Seen = 1;
	if(i-1>=0&&i-1<=row-1&&j>=0&&j<=column-1) Map_Element[i-1][j].Seen = 1;
	if(i-1>=0&&i-1<=row-1&&j+1>=0&&j+1<=column-1) Map_Element[i-1][j+1].Seen = 1;
	if(i>=0&&i<=row-1&&j-1>=0&&j-1<=column-1) Map_Element[i][j-1].Seen = 1;
	if(i>=0&&i<=row-1&&j+1>=0&&j+1<=column-1) Map_Element[i][j+1].Seen = 1;
	if(i+1>=0&&i+1<=row-1&&j-1>=0&&j-1<=column-1) Map_Element[i+1][j-1].Seen = 1;
	if(i+1>=0&&i+1<=row-1&&j>=0&&j<=column-1) Map_Element[i+1][j].Seen = 1;
	if(i+1>=0&&i+1<=row-1&&j+1>=0&&j+1<=column-1) Map_Element[i+1][j+1].Seen = 1;
	
}
/*--------------------------------------------------------------------Part 1----------------------------------------------------------------------------*/
void Map_show(){ /*�����ǰ��ͼ*/
	Robot_Seen();
	for(int i = 0 ; i<row ; i++){
		for(int j = 0; j < column ; j++){
			if(finish == 0)	if(Map_Element[i][j].Seen == 1)printf("%c",Map_temp[i][j]);
							else printf(" ");
			else printf("%c",Map_temp[i][j]); 
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
			puts(Necessary_Net[i].Direction+1); //��һ��Ԫ�ز�����·�� 
			printf("\n");
		}
	}
	if(Obligatory_temp != 0){
		for(int i = 0;i<Obligatory_temp ; i++){
			printf("Obligatory Target[%d] Has Been Found !\n",i+1);//��1��ʼ 
			printf("Axis: (%d, %d)  ",Obligatory_Net[i].Axis[0],Obligatory_Net[i].Axis[1]);
			printf("Distance: %d\n",Obligatory_Net[i].Distance);
			printf("Directions:  ",i+1);
			puts(Obligatory_Net[i].Direction+1);
			printf("\n");
		}
	}
}

void Map_show2(){
	for(int i = 0 ; i<row ; i++){
		for(int j = 0; j < column ; j++){
			printf("%c",Map_temp[i][j]);
		}
		printf("\n");
	}
	printf("Please wait...... The robot is checking the targets' adjacent targets......\n\n");
	printf("Now, it is checking the Target_Point[%d]......\n\n", Target_temp);
	if(Target_Point[Target_temp].Adjacent_Point_Num != 0){
		printf("We have found its adjacent points : \n");
		for(int j = 0; j < Target_Point[Target_temp].Adjacent_Point_Num ; j++ ){
			printf("Adjacent Point[%d] : Target_Point[%d] \n", j,Target_Point[Target_temp].Adjacent_Point_ID[j]); //ID
			printf("Distance : %d  \nDirection : ", Target_Point[Target_temp].Distance[j]); //���� 
			puts(Target_Point[Target_temp].Direction[j]); //·�� 
			printf("\n");
		}
	}
	
}

void Map_show3(){
	for(int i = 0 ; i<row ; i++){
		for(int j = 0; j < column ; j++){
			printf("%c",Map_temp[i][j]);
		}
		printf("\n");
	}
}

int DFS(struct Map *p){
	int i = p->Axis[0]; //�����ͼԪ������ 
	int j = p->Axis[1];
	Robot.Axis[0] = i; //���»�������������ǰ���� 
	Robot.Axis[1] = j;
	
	Visit(p); //�Ե�ǰ�ڵ���з��� 
	
	if(Check_NULL(p) == 0){
		Go_Back_FatherNet(p); //�����ǰ�ڵ����ӽڵ㣬�򷵻��丸�ڵ㣬�ݹ鷵�أ�ֱ����ǰ�ڵ����ӽڵ�λ�� 
		if(p == &Map_Element[0][0]){ //������ص���ԭ�㣬���������������������������˳� 
			finish = 1;
			return 0;
		}
		return 0;
	}else{ //������ӽڵ�Ļ������ 
		for(int k = 7;k>=0;k--){
		if(p->Next_Element[k]!=NULL) DFS(p->Next_Element[k]);
		}
		return 0;
	}	
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Reverse_Direction(char str[], char p[])
{
    int i, j;
    char temp;
    int n = strlen(str);

    for (i = 0, j = n - 1; j >= 0; i++, j--) {
        *(p+i) = 7 - (str[j] - '0') + '0'; //��ת����λ���ת�� 
    }
    *(p+i) = '\0';
}

int DFS2(struct Map *s){
	Visit2(s); //�Ե�ǰ�ڵ���з��� 
	if(Check_NULL(s) == 0){
		Go_Back_FatherNet2(s);
		return 0;
	}else{ //������ӽڵ�Ļ������ 
		for(int k = 7;k>=0;k--){
			if(s->Next_Element[k]!=NULL)if(s->Next_Element[k]->nature == '*'||s->Next_Element[k]->nature == '#'){ //�����Ŀ��� 
			 	 
			 	 for(int j = 0; j < 8 ; j++) if(j!=k){s->Next_Element[j] = NULL;  //�ϵ���Χ��Ŀ�������߸��㣬ʹ�䲻�ܳ�Ϊ�Լ�����һ���ڵ� 
			 	  }
			 	  Visit2(s->Next_Element[k]); //����Ŀ��� 
			 	 s = s->Next_Element[k]; //���� 
			 	 for(int j = 0; j < 8 ; j++) s->Next_Element[j] = NULL; //�ϵ�Ŀ�����Χ�İ˸��㣬ʹ�䲻�ܳ�Ϊ�Լ�����һ���ڵ� 
				 Go_Back_FatherNet2(s); //���뷵�� 
				 return 0;
			}
		}
		for(int k = 7; k>=0 ;k--){
			if(s->Next_Element[k]!=NULL) DFS2(s->Next_Element[k]); //�����Χ�˸���û��Ŀ����������������� 
		}
	}
	return 0;	
}

void Adjacent_Target_Checker(){
	struct Map *s;
	Direction_temp[10000] = {0}; //���·���ݴ����� 
	for(int i = 0; i< Target_number  ; i++){
		temp = 0;
		Direction_temp[10000] = {0};
		Map_Element_Init(); //��ʼ����ͼԪ�� 
		s = &Map_Element[Target_Point[i].Axis[0]][Target_Point[i].Axis[1]]; //��������Ŀ��� 
		s->Last_Element_Mark = 0; //��ʼ����Ͻڵ�����Ϊ0 
		DFS2(s); //����������� 
		Target_temp++; //���� 
	}
	printf("Please hit enter to continue :\n");
	system("pause");
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Graph[40][40];
int Graph_Weight[40] = {0};
int DFS_Count = 0;
int Count = 0;
int Must = 0;

int Distance_temp[2]; //[0]���浱ǰ���룬 [1]������̾��� 
int Invisited[40];
char Direction_Must[40][10000] = {0};
int Distance_Must[40] = {0};
int Direction_ID[2][40];//[0] ���浱ǰ·���� [1]�������·�� 
void Back(int ID);


int Locate_CheckID(int ID, int ID2){
	for(int i = 0 ;i < Target_Point[ID].Adjacent_Point_Num ; i++){
		if(Target_Point[ID].Adjacent_Point_ID[i] == ID2) return i; //������Ŀ��ṹ����ID2����Ӧ���±� 
	}
	return -1; //���������������˵��ID�ṹ���в�����ID2����Ŀ��㣻 
}

int IF_Impasse(int ID){
	int count = 0;
	for(int i = 0; i < Target_number ; i++){
		if(Graph[ID][i]!=Max&&i!=ID&&Graph[ID][i] == Graph[i][ID]) count++;
	}
	if(count == 1) return 1;
	else return 0;
}

int Graph_Connect(int ID){
	if(IF_Impasse(ID)){//������ 
			int Last_Net;
			int i = 0;
			for(i = 0; i < Target_number ; i++) if(i!=ID&&Graph[ID][i]!=Max) Last_Net = i;
			i = 0;
			char Direction_temp2[10000]; // 0000
			Reverse_Direction(Target_Point[Last_Net].Direction[Locate_CheckID(Last_Net, ID)],Direction_temp2); //1234 -> 6543 ��λ��ת������·�� 
			strcat(Target_Point[Last_Net].Direction[Locate_CheckID(Last_Net, ID)], Direction_temp);  // 1234 + Direction 
			strcpy(Direction_temp,Target_Point[Last_Net].Direction[Locate_CheckID(Last_Net, ID)]);  // Direction = 1234 + Direction 
			strcat(Direction_temp, Direction_temp2);// Direction = 1234 + Direction + 6543 ��β���  ȥ���ֻ� 
			Distance_temp[0] += 2*Graph[Last_Net][ID]; // + �������� 
			Graph[ID][Last_Net] = Max; //������Ļ�ͨ·����ͼ��Ĩȥ 
			Graph[Last_Net][ID] = Max;
			Graph_Weight[Last_Net] = Graph_Weight[ID] + 1; //Ȩ�ص������ 
			Graph_Connect(Last_Net); //���������һ���ڵ���е��飬ֱ���ýڵ㲻������ 
	}else{ //�������� 
		Distance_Must[ID] = Distance_temp[0]; //�ؾ����� 
		strcpy(Direction_Must[ID], Direction_temp); //�ؾ�·�� 
		Direction_temp[10000] = {0};
		Distance_temp[0] = 0;
	}
}

void Graph_Weight_Show(){ //���ͼ��Ȩ�� 
	
	for(int i = 0; i < Target_number ; i++) printf("%7d", Graph_Weight[i]);printf("\n");
	printf("\n");
	printf("OK, We branch simplified the graph and these numbers are the weight coefficients of all target points in the graph\n\n");
	printf("Please hit enter to continue :\n");
	system("pause");
}

void Simplify_Graph(){ //��ͼ������Ȩ�أ��ų����� 

	for(ID_T= 1 ; ID_T < Target_number ; ID_T++){ //ԭ�㲻����Ϊ���� 
		Graph_Connect(ID_T);
		
	}
	Sleep(100);
	system("cls");
	Graph_Weight_Show();
}

void Graph_Fix(){ //�ų�ͼ����������A->B ������ B->A���������ͼ�����޸� 
	for(int i = 0; i < Target_number ; i++) for(int j = 0; j < Target_number ; j++){
		if(Graph[i][j] == Graph[j][i]){ //����ԳƵ�����������޸� 
			continue;
		}else{ //���� 
			int shorter_id = (Graph[i][j] < Graph[j][i])? i : j; //ȡ·������С����Ϊshorter 
			int longer_id = (Graph[i][j] < Graph[j][i])? j : i; //·����������Ϊlonger 
			int shorter_locate; //���������ڻ���Ľṹ���ж�λ 
			int longer_locate;
			int check_have = 0; //���ܴ��ڶԷ����Լ��Ľṹ���в����ڵ������������Ҫ����һ�����������ж� 
			for(int k = 0; k < Target_Point[shorter_id].Adjacent_Point_Num ; k++) {if(Target_Point[shorter_id].Adjacent_Point_ID[k] == j)  shorter_locate = k, check_have = 1; } //�±궨λ 
			if(check_have == 0) shorter_locate = ++Target_Point[shorter_id].Adjacent_Point_Num - 1, Target_Point[shorter_id].Adjacent_Point_ID[shorter_locate] = j; //��������� 
			check_have = 0;
			for(int k = 0; k < Target_Point[longer_id].Adjacent_Point_Num ; k++) {if(Target_Point[longer_id].Adjacent_Point_ID[k] == i)  longer_locate = k, check_have = 1;}
			if(check_have == 0) longer_locate = ++Target_Point[longer_id].Adjacent_Point_Num - 1, Target_Point[longer_id].Adjacent_Point_ID[longer_locate] = i; //ǿ������ 
			
			Target_Point[longer_id].Distance[longer_locate] = Target_Point[shorter_id].Distance[shorter_locate];  //Num++��·���;����ͳһΪ�϶̵�һ�� 
			Reverse_Direction(Target_Point[shorter_id].Direction[shorter_locate],Target_Point[longer_id].Direction[longer_locate]); //�ԶԷ���·������������ 
			
			Graph[longer_id][shorter_id] = Graph[shorter_id][longer_id]; //�޸�ͼ 
		}
	}
}

void Graph_Init(){
	for(int i = 0; i < Target_number ; i++) for(int j = 0; j < Target_number ; j++){
		Graph[i][j] = Max;
		Graph_Weight[i] = 1; //��ʼ��Ȩ�ؾ�Ϊ1 
	} 
	for(int i = 0; i < Target_number ; i++){
		Graph[i][i] = 0;
		for(int j = 0; j < Target_Point[i].Adjacent_Point_Num ; j++){
			Graph[i][Target_Point[i].Adjacent_Point_ID[j]] = Target_Point[i].Distance[j];
		}
	}
	Graph_Fix();
	system("cls");
	for(int i = 0; i < Target_number ; i++){ for(int j = 0; j < Target_number ; j++) printf("%7d",Graph[i][j]);printf("\n");}
	Sleep(100);
	printf("\n");
	printf("This is the adjacency matrix of all target points in the figure, where the number in row i and column j represents the distance between the target point i and the target point j. If the number is 100000, there is no direct path between the ith and the JTH target points, that is, they are not adjacent.\n\n");
	printf("Please hit enter to continue :\n");
	system("pause");
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

int DFS3(int ID){
	 Count++; //����������Ϊ�����±� 
	if(DFS_Count == Target_number - 1){ //���Ȩ������ 
	 	Distance_temp[0] += Graph[ID][0]; //����ǰ��·��������ϸõ㵽ԭ���·������ 
	 	if(Distance_temp[1] == 0) Distance_temp[1] = Distance_temp[0]; //�����ʱ��1����λ����0����ֱ�Ӹ��ƹ�ȥ 
	 	if(Distance_temp[0] <= Distance_temp[1]){ //�����ǰ·������С�ڵ������·����������� 
	 		for(int i = 0 ; i < Target_number; i++) Direction_ID[1][i] = Direction_ID[0][i];
	 		Distance_temp[1] = Distance_temp[0];
	 		Back(ID); //���� 
	 		return 0; 
	 	}else{
	 		Back(ID); //����ֱ�ӷ��� 
	 		return 0;
	 	}
	}else{
		
		int i = 0;
		for( i = 0 ; i < Target_number; i++){
		 if(Graph[ID][i]!=Max&&Invisited[i]!=1&&i!=ID) {
		 	Invisited[i] = 1; //�������� 
		 	Direction_ID[0][Count] = i;
			Distance_temp[0] += Graph[ID][i];
			DFS_Count += Graph_Weight[i]; //��Ȩ�� 
			if(Graph_Weight[i]!=1){
				Distance_temp[0] += Distance_Must[ID];
			}
			DFS3(i) ;
		}
		}
		if(i == Target_number) Back(ID);
	}
}

void Back(int ID){
	DFS_Count -= Graph_Weight[ID]; //��Ȩ�� 
	Count = Count - 1;
	Distance_temp[0] -= Graph[Direction_ID[0][Count-1]][ID];

	Direction_ID[0][Count] = 0;
	Invisited[ID] = 0;
}

void TSP(){ //̰���㷨 
	Graph_Init(); //��ʼ��ͼ 
	Simplify_Graph(); //��ͼ���м� 
	for(int terminal = 1; terminal < Target_number ; terminal++){ //����Ҫ���ԭ·���ص����񣬲��ܽ�ԭ����Ϊ���ն��㡣����������ֱ�ȡʣ�µ�����Ŀ���ֱ���Ϊ���ն��� 
		if(Locate_CheckID(terminal,0)==-1) continue; //�����ȡ�����ն���û�з���ԭ���·�����������һ��ѭ�� 
		Invisited[40] = {0}; //��ʼ�� 
		DFS_Count = 0; 
		Count = 0;
		Distance_temp[0] = 0;
		Direction_ID[0][0] = 0;
		Invisited[0] = 1;
		DFS3(0); //����������� 
	}		
		
}

void Play_Shortest_Road(){
	char Direction_Shortest[10000] = {0};
	int temp = 0;
	do{
		if(Graph_Weight[Direction_ID[1][temp]] != 1) strcat(Direction_Shortest, Direction_Must[Direction_ID[1][temp]]); //����õ�Ȩ�ز�Ϊ0������Ҫ���ӱ��뾭����·�� 
		if(temp == 0) strcpy(Direction_Shortest, Target_Point[Direction_ID[1][temp]].Direction[Locate_CheckID(Direction_ID[1][temp], Direction_ID[1][temp+1])]); //��һ�������ַ������� 
		else strcat(Direction_Shortest, Target_Point[Direction_ID[1][temp]].Direction[Locate_CheckID(Direction_ID[1][temp], Direction_ID[1][temp+1])]); //��������� 
		temp++;
	}while(Direction_ID[1][temp]!=0);
	int i = 0;
	int j = 0;
	temp = 0;
	int distance = 0;
	int num = 0;
	do{
		if(Direction_Shortest[temp] == '0') i--,j--; //·��ת��Ϊ��λ 
		if(Direction_Shortest[temp] == '1') i--;
		if(Direction_Shortest[temp] == '2') i--,j++;
		if(Direction_Shortest[temp] == '3') j--;
		if(Direction_Shortest[temp] == '4') j++;
		if(Direction_Shortest[temp] == '5') i++,j--;
		if(Direction_Shortest[temp] == '6') i++;
		if(Direction_Shortest[temp] == '7') i++,j++;
		/*if((Map_Element[i][j].nature == '*'||Map_Element[i][j].nature == '#')) num++;*/
		Map_Init();
		Map_temp[i][j] = robot_position;
		system("cls");
		Map_show3();
		printf("Please wait......\n");
		printf("The Robot is traveling in the most energy-efficient way possible ! \n\n");
		printf("Cumulative Distance : %d\n\n", distance);
		printf("Planned path : %s\n\n", Direction_Shortest);
		/*if(num!=0){
			for(int i = 1 ;i <= num; i++){
				printf("Arrive Target[%d]\n", Direction_ID[1][i]);
			}
		}*/
		Sleep(500);
		temp++;
		distance++;
	}while(temp <= strlen(Direction_Shortest)); 
	
	printf("Now, All the problems have been solved ! !\n\n");
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
int main(){
	Target_Point[0].Axis[0] = 0;
	Target_Point[0].Axis[1] = 0;
	Target_Point[0].ID = 0;
	Target_temp++;
	Robot.Axis[0] = 0;
	Robot.Axis[1] = 0; //��ʼ��������λ�� 
	Map_Save(); //���ļ��ж�ȡ��ͼ 
	Map_Init(); //��ͼ�ݴ������ʼ�� 
	
	DFS(Entrance); //����������� 
	finish = 1;
	printf("\nPlease input 'Y' to continue \n");
	Target_number = Target_temp;
	Target_temp = 0;
	char Next_Order = '\0';
	Next_Order = getchar();
	
	if(Next_Order == 'Y'){
		temp = 0;
		Direction_temp[10000] = {0};
		
		system("cls");
		Map_Init();
		Map_Element_Init();
		Adjacent_Target_Checker();
		TSP();
		Distance_temp[0] = 0;
		Play_Shortest_Road();
	}
	system("pause");
	return 0; 
}
/*���磬�㿴�Ҷమ�㣬�߰ٶ��д�����˵д��д���㿴���ǲ��ǣ�ÿ�����Ǹ�Ǯ�����ҵ�*/
