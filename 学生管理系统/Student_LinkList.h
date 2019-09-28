#include	<stdio.h> 
#include	<stdlib.h>
#include	<string.h>
#include 	"LinkList.h"
#include 	"Student_Proofread.h"
#define 	fileName "file//StudentInformation"
// 函数声明 
LinkList* 	init_student_list();
int 		add_student(LinkList* head, LinkList *node);
int 		traverse_list(LinkList* head);
int 		delete_student(LinkList* head, LinkList* trail, LinkList* node);
int 		modify_name(LinkList* node, char name[]); 
int 		modify_number(LinkList* node, char number[]);
LinkList* 	search_studentByNumber(LinkList* head, char number[]);
LinkList* 	search_studentByName(LinkList* head, char number[]);
void 		print_student(LinkList* node);
int 		write_student(LinkList* head);
int 		read_student(LinkList* head);
LinkList* 	bubble(LinkList* head);


/*
	功能：	初始化 
	返回：	初始化链表 
*/
LinkList* init_student_list(){
	LinkList* head = initList();
	if(read_student(head)){
		return head;	
	}else{
		return NULL; 
	}
}

/*
	功能：		增加学生信息
	head:		头结点
	node：		预插入节点 
	返回int值：	增加成功返回1，失败返回0 
*/
int add_student(LinkList* head, LinkList *node){
	// 若head为空 
	if(head->next == NULL){
		return addNode(head, NULL, node);
	}else{
		LinkList* p, *prev, *maxNode, *minNode;
		p = head;
		prev = head;
		maxNode = NULL;
		minNode = NULL;
		if(search_studentByNumber(head, node->student.number) == NULL){
			for(; p->next; prev = p, p = p->next){
				LinkList* temp = p->next; 
				// 如果node节点的number大于temp节点的number 
				if(strcmp(node->student.number, temp->student.number) > 0){
					maxNode = temp;		// 则记录下temp节点 
				}else if(strcmp(node->student.number, temp->student.number) < 0){
					minNode = prev;
					break;				//  小于一次则退出 
				}
			}
			if(maxNode != NULL){
				return addNode(head, maxNode, node); 
			}else if(minNode != NULL){
				return addNode(head, minNode, node); 
			} 
		}else{
			return 0;
		}
	} 
}

/* 
	功能：		删除学生信息
	head:		头结点
	number:	 	学号字符数组 
*/
int delete_student(LinkList* head, LinkList* trail, LinkList* node){
	// 删除 
	return deteleNode(head, trail, node);
} 

/*
	功能：		修改姓名
	node:		预修改的节点
	name:		新姓名 
*/
int modify_name(LinkList* node, char name[]){
	if(strcpy(node->student.name, name)){
		return 1;
	}else{
		return 0;
	}
}

/*
	功能：		修改学号
	node:		预修改的节点
	name:		新姓名 
*/
int modify_number(LinkList* node, char number[]){
	if(strcpy(node->student.number, number)){
		return 1;
	}else{
		return 0;
	}
}

/* 
	功能：	查找(根据学号) 
	head:	头结点 
	number:	学号字符数组 
	返回：	NULL或者节点地址 
*/
LinkList* search_studentByNumber(LinkList* head, char number[]){
	LinkList* p = head;
	for(; p->next; p = p->next){
		// 验证学号是否相等 
		if(strcmp(p->student.number, number) == 0){
			return p;
		}
	}
	return NULL;
} 

/* 
	功能：	查找(根据姓名) 
	head:	头结点 
	name:	姓名字符数组(字符串) 
	返回：	返回NULL或者节点地址 
*/
LinkList* search_studentByName(LinkList* head, char name[]){
	LinkList* p = head;
	for(; p->next; p = p->next){
		// 验证学号是否相等 
		if(strcmp(p->student.name, name) == 0){
			return p;
		}
	}
	return NULL;
}

/* 
	功能：		打印格式化信息
	student:	学生节点 
*/
void print_student(LinkList* node){
	printf("\t\t---------------------------------------------------\n");
	printf("\t\t姓名：%s\t|", node->student.name);
	printf("年龄：%d\t|", node->student.age);
	printf("学号：%s\t|\n", node->student.number);
	printf("\t\t语文：%.1lf\t|", node->student.grade.chinese);
	printf("数学：%.1lf\t|", node->student.grade.math);
	printf("英语：%.1lf\t|\n", node->student.grade.english);
	printf("\t\t---------------------------------------------------\n");
}

/* 
	功能：	遍历数据 
	head:	头结点 
*/
int traverse_list(LinkList* head){
 	if(isEmpty(head) != 1){
	 	LinkList* p = head, *temp;  
    	while(p->next != NULL){  
    		temp = p->next;
	   		// 输出想要输出的数据 
	   		printf("\t\t---------------------------------------------------\n");
			printf("\t\t姓名：%s\t|", temp->student.name);
			printf("年龄：%d\t|", temp->student.age);
			printf("学号：%s\t|\n", temp->student.number);
			printf("\t\t语文：%.1lf\t|", temp->student.grade.chinese);
			printf("数学：%.1lf\t|", temp->student.grade.math);
			printf("英语：%.1lf\t|\n", temp->student.grade.english);
			printf("\t\t---------------------------------------------------\n");
			p = p->next;     //移到下一个节点  
    	}
 	}else{
 		return 0;
 	}
} 

/*
	功能：	将结构体写入文件
	head:	头结点 
	返回：	void 
*/
int write_student(LinkList* head){
	char file[] = fileName;
	return write(head, file); 
}

/*
	功能：	将文件中的数据读入链表 
	head:	头结点 
	返回：	void 
*/
int read_student(LinkList* head){
	char file[] = fileName;
	return read(head, file);
}

/*
	冒泡排序
	head:	头结点 
*/
LinkList* bubble(LinkList* head){
    LinkList* v, *u;
    u = (LinkList*)malloc(LEN);
    u->next=head;
    head=u;
    LinkList *endpt, *p;
    for(endpt=NULL; endpt!=head; endpt=p){
        for(p = u = head; u->next->next != endpt; u = u -> next){
            if((u->next->student.grade.chinese) < (u->next->next->student.grade.chinese)){                            
                v = u->next->next;   
                u->next->next = v->next;   
                v->next = u->next;   
                u->next = v;   
                p = u->next->next;   
            } 
        }
    }
    u=head;   
    head=head->next;       
    return head; 
}

