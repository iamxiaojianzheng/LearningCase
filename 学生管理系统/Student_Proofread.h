#include<stdio.h>
#include<string.h>

int proofread_choice(){
	char choice[10];
	while(scanf("%s", &choice) != 1){
		printf("\t\tѡ�������������������룡\n"); 
		printf("\t\t������ѡ��");
	}
	return atoi(choice);
}

// У��ѧ��
char* proofread_number(char number[]){
	while(scanf("%s", number) != 1 || strncasecmp(number, "201601420", 9) || strlen(number) > 12){
		printf("\t\tѧ�������������������룡\n"); 
		printf("\t\t������ѧ�ţ�");
	}
	return number;
}

// У������
int proofread_age(){
	int age = 0;
	while(scanf("%d", &age) != 1 || age < 0 || age > 100){
		printf("���������������������룡\n"); 
		printf("���������䣺");
	}
	return age;
} 

// У�����ĳɼ�
double proofread_chinese(){
	double chinese = 0;
	while(scanf("%lf", &chinese) != 1 || chinese < 0 || chinese > 100){
		printf("\t\t���ĳɼ������������������룡\n"); 
		printf("\t\t���������ĳɼ���");
	}
	return chinese;
} 

// У����ѧ�ɼ�
double proofread_math(){
	double math = 0;
	while(scanf("%lf", &math) != 1 || math < 0 || math > 100){
		printf("\t\t���ĳɼ������������������룡"); 
		printf("\t\t���������ĳɼ���");
	}
	return math;
} 

// У��Ӣ��ɼ�
double proofread_english(){
	double english = 0;
	while(scanf("%lf", &english) != 1 || english < 0 || english > 100){
		printf("\t\t���ĳɼ������������������룡"); 
		printf("\t\t���������ĳɼ���");
	}
	return english;
} 
