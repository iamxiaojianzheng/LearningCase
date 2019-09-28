#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	"StudentStruct.h" 
#define LEN sizeof(LinkList)
/*
// �ɼ��ṹ�� 
typedef struct Grade{
	double math;
	double chinese;
	double english;
}Grade;

// ѧ���ṹ�� 
typedef struct Student{
	char name[6];
	int age;
	char number[12];
	Grade grade;
}Student;
*/
// ����ṹ�� 
typedef struct LinkList{
	Student student;
	struct LinkList *next;
}LinkList;

// �������� 
LinkList* 	initList();
void 		clearList(LinkList* head);
int 		isEmpty(LinkList* head);
int 		addNode(LinkList* head, LinkList* trail, LinkList* node);
int 		deteleNode(LinkList* head, LinkList* trail, LinkList* node);
LinkList* 	findNode(LinkList* head, char number[]);
void 		traverseNode(LinkList* head);
int 		lengthList(LinkList* head);
int 		write(LinkList* head, char file[]);
int 		read(LinkList* head, char file[]);

// ��ʼ������ 
LinkList* initList(){
	LinkList* head = NULL; // ͷ��� 
	// ����len(sizeof(Student))��С�Ŀռ� 
	head = (LinkList*)malloc(LEN);
	// ������ٳɹ�����ֵ��head������������ٿռ�ʧ�� 
	if (head != NULL){
		head->next= NULL;
	} else {
		printf("\nCann't create it, try it again in a moment!\n");
	}
	return head;
}

//������� 
void clearList(LinkList* head){
	LinkList *p;
	// ������Ϊ��ʱ��ɾ�������е����нڵ� 
	while(head->next!=NULL){
		p = head->next;	// ���汻ɾ�ڵ� ��������ժ�½ڵ� 
		head->next = p->next; // ��Ҫɾ���Ľڵ�ָ�����һ���ڵ��ַ����head�ڵ� 
		free(p);	// ɾ��(������ͷ���) 
	}	  
}

// �ж������Ƿ�Ϊ��
int isEmpty(LinkList* head){
	return head->next == NULL ? 1 : 0;
}

/* 
	���ܣ�	���ӽڵ�
	head:	ͷ���
 	trail��	����λ�õ�ǰ���ڵ�
 	node��	Ԥ����ڵ� 
	���أ�	int 
*/
int addNode(LinkList* head, LinkList* trail, LinkList* node){
	if(trail){
		// ǰ����Ϊ�գ�����trail֮�� 
		node->next = trail->next;
		trail->next = node;
	}else{
		// ǰ��Ϊ�գ������޽ڵ㣬������ͷ���֮�� 
		head->next = node;
		node->next = NULL;
	}
	return 1; 
} 

/* 
	���ܣ�	ɾ������
	head:	ͷ���
	trail��	ɾ���ڵ��ǰ���ڵ�
	node��	Ԥɾ���Ľڵ� 
*/
int deteleNode(LinkList* head, LinkList* trail, LinkList* node){
	if(trail){
		trail->next = node->next;
	}else{
		head = head->next;
	}
	free(node); 
	return 1;
}

/* 
	���ܣ�	����������ͷ�ڵ��⣩�Ƿ�����ض�ֵ�ýڵ�  
	head:	ͷ�ڵ�
	number:	Ԥ���ҵ��ַ����� 
*/
LinkList* findNode(LinkList *head, char number[]){  
    LinkList *p = head;
	for(; p; p = p->next){
		if(p->student.number == number)
			return p;
	}
}  

/* 
	���ܣ�	���������� 
	head:	ͷ��� 
*/
int lengthList(LinkList *head){
	LinkList *p = head->next;
	int count = 0;
	while(p!=NULL){
		p = p->next;
		count++;
	}
	return count;
}

/*
	���ܣ�	���ṹ��д���ļ�
	file:	�ļ����� 
*/
int write(LinkList* head, char file[]){
	FILE* fp;
	if((fp = fopen(file, "wb")) == NULL){
		perror("File Write Error!");
		return 0;
	}
	LinkList* p = head;
	while(p->next != NULL){
		p = p->next;
		if(fwrite(p, LEN,  1, fp) < 0){
			printf("File Write Error!");
		}
		// printf("%s", p->student.name);
		// p = p->next;
	}
	fclose(fp);
	return 1;
} 

/*
	�����ݴӽṹ���ж��������� 
	file:	�ļ����� 
*/
int read(LinkList* head, char file[]){
	FILE* fp;
	if((fp = fopen(file, "rb+")) == NULL){
		perror("File Read Error!");
		return 0;
	}
	LinkList* p = (LinkList*)malloc(LEN);
	LinkList* temp;
	p = head;
	p->next = NULL;
	// feof�������ж��Ƿ�ָ���ļ�ĩβ���Ƿ���1�����򷵻�0 
	while(!feof(fp)){
		temp = (LinkList*)malloc(LEN);
		fread(temp, LEN, 1, fp);
		if(feof(fp)){
			p->next = NULL;
			break;
		}
		p->next = temp;
		p = temp;
		p->next = NULL;
	}
	fclose(fp);
	return 1;
}
