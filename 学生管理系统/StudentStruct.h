// 成绩结构体 
typedef struct Grade{
	double math;
	double chinese;
	double english;
	double total; 
}Grade;

// 学生结构体 
typedef struct Student{
	char name[6];
	int age;
	char number[12];
	Grade grade;
}Student;
