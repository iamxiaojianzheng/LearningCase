#include	<stdio.h> 
#include	<stdlib.h>
#include	<string.h>
#include 	"LinkList.h"
#include 	"Student_Proofread.h"
#define 	fileName "file//StudentInformation"
// �������� 
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
	���ܣ�	��ʼ�� 
	���أ�	��ʼ������ 
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
	���ܣ�		����ѧ����Ϣ
	head:		ͷ���
	node��		Ԥ����ڵ� 
	����intֵ��	���ӳɹ�����1��ʧ�ܷ���0 
*/
int add_student(LinkList* head, LinkList *node){
	// ��headΪ�� 
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
				// ���node�ڵ��number����temp�ڵ��number 
				if(strcmp(node->student.number, temp->student.number) > 0){
					maxNode = temp;		// ���¼��temp�ڵ� 
				}else if(strcmp(node->student.number, temp->student.number) < 0){
					minNode = prev;
					break;				//  С��һ�����˳� 
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
	���ܣ�		ɾ��ѧ����Ϣ
	head:		ͷ���
	number:	 	ѧ���ַ����� 
*/
int delete_student(LinkList* head, LinkList* trail, LinkList* node){
	// ɾ�� 
	return deteleNode(head, trail, node);
} 

/*
	���ܣ�		�޸�����
	node:		Ԥ�޸ĵĽڵ�
	name:		������ 
*/
int modify_name(LinkList* node, char name[]){
	if(strcpy(node->student.name, name)){
		return 1;
	}else{
		return 0;
	}
}

/*
	���ܣ�		�޸�ѧ��
	node:		Ԥ�޸ĵĽڵ�
	name:		������ 
*/
int modify_number(LinkList* node, char number[]){
	if(strcpy(node->student.number, number)){
		return 1;
	}else{
		return 0;
	}
}

/* 
	���ܣ�	����(����ѧ��) 
	head:	ͷ��� 
	number:	ѧ���ַ����� 
	���أ�	NULL���߽ڵ��ַ 
*/
LinkList* search_studentByNumber(LinkList* head, char number[]){
	LinkList* p = head;
	for(; p->next; p = p->next){
		// ��֤ѧ���Ƿ���� 
		if(strcmp(p->student.number, number) == 0){
			return p;
		}
	}
	return NULL;
} 

/* 
	���ܣ�	����(��������) 
	head:	ͷ��� 
	name:	�����ַ�����(�ַ���) 
	���أ�	����NULL���߽ڵ��ַ 
*/
LinkList* search_studentByName(LinkList* head, char name[]){
	LinkList* p = head;
	for(; p->next; p = p->next){
		// ��֤ѧ���Ƿ���� 
		if(strcmp(p->student.name, name) == 0){
			return p;
		}
	}
	return NULL;
}

/* 
	���ܣ�		��ӡ��ʽ����Ϣ
	student:	ѧ���ڵ� 
*/
void print_student(LinkList* node){
	printf("\t\t---------------------------------------------------\n");
	printf("\t\t������%s\t|", node->student.name);
	printf("���䣺%d\t|", node->student.age);
	printf("ѧ�ţ�%s\t|\n", node->student.number);
	printf("\t\t���ģ�%.1lf\t|", node->student.grade.chinese);
	printf("��ѧ��%.1lf\t|", node->student.grade.math);
	printf("Ӣ�%.1lf\t|\n", node->student.grade.english);
	printf("\t\t---------------------------------------------------\n");
}

/* 
	���ܣ�	�������� 
	head:	ͷ��� 
*/
int traverse_list(LinkList* head){
 	if(isEmpty(head) != 1){
	 	LinkList* p = head, *temp;  
    	while(p->next != NULL){  
    		temp = p->next;
	   		// �����Ҫ��������� 
	   		printf("\t\t---------------------------------------------------\n");
			printf("\t\t������%s\t|", temp->student.name);
			printf("���䣺%d\t|", temp->student.age);
			printf("ѧ�ţ�%s\t|\n", temp->student.number);
			printf("\t\t���ģ�%.1lf\t|", temp->student.grade.chinese);
			printf("��ѧ��%.1lf\t|", temp->student.grade.math);
			printf("Ӣ�%.1lf\t|\n", temp->student.grade.english);
			printf("\t\t---------------------------------------------------\n");
			p = p->next;     //�Ƶ���һ���ڵ�  
    	}
 	}else{
 		return 0;
 	}
} 

/*
	���ܣ�	���ṹ��д���ļ�
	head:	ͷ��� 
	���أ�	void 
*/
int write_student(LinkList* head){
	char file[] = fileName;
	return write(head, file); 
}

/*
	���ܣ�	���ļ��е����ݶ������� 
	head:	ͷ��� 
	���أ�	void 
*/
int read_student(LinkList* head){
	char file[] = fileName;
	return read(head, file);
}

/*
	ð������
	head:	ͷ��� 
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

