// �ɼ��ṹ�� 
typedef struct Grade{
	double math;
	double chinese;
	double english;
	double total; 
}Grade;

// ѧ���ṹ�� 
typedef struct Student{
	char name[6];
	int age;
	char number[12];
	Grade grade;
}Student;
