#include<stdio.h>
#include<string.h>

int proofread_choice(){
	char choice[10];
	while(scanf("%s", &choice) != 1){
		printf("\t\t选择输入有误，请重新输入！\n"); 
		printf("\t\t请输入选择：");
	}
	return atoi(choice);
}

// 校对学号
char* proofread_number(char number[]){
	while(scanf("%s", number) != 1 || strncasecmp(number, "201601420", 9) || strlen(number) > 12){
		printf("\t\t学号输入有误，请重新输入！\n"); 
		printf("\t\t请输入学号：");
	}
	return number;
}

// 校对年龄
int proofread_age(){
	int age = 0;
	while(scanf("%d", &age) != 1 || age < 0 || age > 100){
		printf("年龄输入有误，请重新输入！\n"); 
		printf("请输入年龄：");
	}
	return age;
} 

// 校对语文成绩
double proofread_chinese(){
	double chinese = 0;
	while(scanf("%lf", &chinese) != 1 || chinese < 0 || chinese > 100){
		printf("\t\t语文成绩输入有误，请重新输入！\n"); 
		printf("\t\t请输入语文成绩：");
	}
	return chinese;
} 

// 校对数学成绩
double proofread_math(){
	double math = 0;
	while(scanf("%lf", &math) != 1 || math < 0 || math > 100){
		printf("\t\t语文成绩输入有误，请重新输入！"); 
		printf("\t\t请输入语文成绩：");
	}
	return math;
} 

// 校对英语成绩
double proofread_english(){
	double english = 0;
	while(scanf("%lf", &english) != 1 || english < 0 || english > 100){
		printf("\t\t语文成绩输入有误，请重新输入！"); 
		printf("\t\t请输入语文成绩：");
	}
	return english;
} 
