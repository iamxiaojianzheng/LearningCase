#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	"StudentStruct.h" 
#define LEN sizeof(LinkList)
/*
// 成绩结构体 
typedef struct Grade{
	double math;
	double chinese;
	double english;
}Grade;

// 学生结构体 
typedef struct Student{
	char name[6];
	int age;
	char number[12];
	Grade grade;
}Student;
*/
// 链表结构体 
typedef struct LinkList{
	Student student;
	struct LinkList *next;
}LinkList;

// 函数声明 
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

// 初始化链表 
LinkList* initList(){
	LinkList* head = NULL; // 头结点 
	// 开辟len(sizeof(Student))大小的空间 
	head = (LinkList*)malloc(LEN);
	// 如果开辟成功，则赋值给head，否则输出开辟空间失败 
	if (head != NULL){
		head->next= NULL;
	} else {
		printf("\nCann't create it, try it again in a moment!\n");
	}
	return head;
}

//清空链表 
void clearList(LinkList* head){
	LinkList *p;
	// 当链表不为空时，删除链表中的所有节点 
	while(head->next!=NULL){
		p = head->next;	// 保存被删节点 ，从链上摘下节点 
		head->next = p->next; // 将要删除的节点指向的下一个节点地址赋给head节点 
		free(p);	// 删除(仅保留头结点) 
	}	  
}

// 判断链表是否为空
int isEmpty(LinkList* head){
	return head->next == NULL ? 1 : 0;
}

/* 
	功能：	增加节点
	head:	头结点
 	trail：	插入位置的前驱节点
 	node：	预插入节点 
	返回：	int 
*/
int addNode(LinkList* head, LinkList* trail, LinkList* node){
	if(trail){
		// 前驱不为空，插入trail之后 
		node->next = trail->next;
		trail->next = node;
	}else{
		// 前驱为空，链表无节点，插入在头结点之后 
		head->next = node;
		node->next = NULL;
	}
	return 1; 
} 

/* 
	功能：	删除链表
	head:	头结点
	trail：	删除节点的前驱节点
	node：	预删除的节点 
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
	功能：	查找链表（除头节点外）是否存在特定值得节点  
	head:	头节点
	number:	预查找的字符数组 
*/
LinkList* findNode(LinkList *head, char number[]){  
    LinkList *p = head;
	for(; p; p = p->next){
		if(p->student.number == number)
			return p;
	}
}  

/* 
	功能：	计算链表长度 
	head:	头结点 
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
	功能：	将结构体写入文件
	file:	文件名称 
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
	将数据从结构体中读入链表中 
	file:	文件名称 
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
	// feof函数，判断是否指向文件末尾，是返回1，否则返回0 
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
