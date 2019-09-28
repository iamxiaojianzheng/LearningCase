#include	<stdio.h>
#include	<math.h> 
#include 	<windows.h>
#include 	<tchar.h>
#include 	"Student_LinkList.h"

//�������� 
void 		MainMenu();
void 		addStudent(LinkList* head);
void 		deleteStudent(LinkList* head);
void 		modifyStudent(LinkList* head);
int 		modifyStudentMenu(LinkList* link);
void 		findStudent(LinkList* head);
void 		save(LinkList* head);
void 		printStudent(LinkList* head);
void 		returnMainMenu(); 
void 		Exit();
float 		f(float x, float y, float z);
float 		h(float x, float z);
LinkList* 	SelectSort(LinkList* head);

LinkList* 	head = NULL;

/*
	���ܣ���ʾ������
	���أ�void 
*/
void MainMenu(){
	// ��head��һ��Ϊnullʱ����ʼ�� 
	if(head == NULL){
		head = init_student_list();
	}
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  �ɼ�����ϵͳ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|    1.����ѧ����Ϣ        2.ɾ��ѧ����Ϣ        |\n");
    printf("\t\t|    3.�޸�ѧ����Ϣ        4.����ѧ����Ϣ        |\n");
    printf("\t\t|    5.ѧ������Ϣ          6.������Ϣ(�޸ĺ�)    |\n");
    printf("\t\t|    ����������˳���(�˳�ǰ��ǵñ�����Ϣ)      |\n");
    printf("\t\t|------------------------------------------------|\n");
	printf("\t\t ����������ѡ��"); 
	int choice;
	choice = proofread_choice();
	switch(choice){
		case 1: 
			addStudent(head);
			break;
		case 2:
			deleteStudent(head);
			break;
		case 3:
			modifyStudent(head);
			break;
	 	case 4:
	 		findStudent(head); 
	 		break;
 		case 5:
 			printStudent(head);
 			break;
		case 6:
			save(head);
			break;
		default:
			Exit();
	}
}

void addStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  ����ѧ����Ϣ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
	// �ݴ�ѧ����Ϣ 
	LinkList* node;
	node = (LinkList*)malloc(LEN); 
	
	// ���� 
	printf("\t\t������������");
	scanf("%s", node->student.name);
	
	// ����
	printf("\t\t���������䣺");
	int age = 0;
	while(scanf("%d", &age) != 1 || age < 0 || age > 100){
		printf("���������������������룡\n"); 
		printf("���������䣺");
	}
	node->student.age = age; 
	
	// ѧ��
	printf("\t\t������ѧ�ţ�");
	char number[12];
	strcpy(node->student.number, proofread_number(number)); 
	
	// ����
	printf("\t\t���������ĳɼ���");
	double chinese = 0;
	chinese = proofread_chinese();
	node->student.grade.chinese = chinese;
 	
 	// ��ѧ 
	printf("\t\t��������ѧ�ɼ���");
	double math = proofread_math();
	node->student.grade.math = math;
 	
 	// Ӣ��
	printf("\t\t������Ӣ��ɼ���");
	double english = 0;
	english = proofread_english();
	node->student.grade.english = english;
 	
 	int judge = add_student(head, node);
 	if(judge == 1){
	 	printf("\t\t¼��ɹ���\n");
		print_student(node);
	}else{
 		printf("\t\t%s�Ѿ����ڣ�\n", node->student.number);
 	}
 	// ѯ���Ƿ����¼����Ϣ 
	printf("\t\t�Ƿ����¼��(Y/N)��");
 	char choice;
	getchar();	// ������һ��scanf����������\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t��淶���룬лл��\n");
		printf("\t\t�Ƿ����¼��(Y/N)��");
		getchar();	// ������һ��scanf����������\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
	
}

/*
	���ܣ�	ɾ��ѧ�� 
*/
void deleteStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  ����ѧ����Ϣ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    
	printf("\t\t��������Ҫɾ��ѧ����ѧ�ţ�");
	char number[12];
	proofread_number(number);
	LinkList* trail = head, *p = head->next;
	for(; p; trail = p, p = p->next){
		if(strcmp(number, p->student.number) == 0){
			delete_student(head, trail, p);
		}else if(p->next == NULL){
			printf("\t\t���޴��ˣ�\n");
		}	
	}
	// ѯ���Ƿ����ɾ����Ϣ 
	printf("\t\t�Ƿ����ɾ��(Y/N)��");
 	char choice;
	getchar();	// ������һ��scanf����������\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t��淶���룬лл��");
		printf("\t\t�Ƿ����ɾ��(Y/N)��");
		getchar();	// ������һ��scanf����������\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

/*
	���ܣ��޸�ѧ����Ϣ 
*/
void modifyStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  ɾ��ѧ����Ϣ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    
	printf("\t\t|��������Ҫ�޸�ѧ����ѧ�ţ�");
	char number[12];
	proofread_number(number);
	LinkList* link = search_studentByNumber(head, number);	// ��ΪҪ�޸�����������Ҫ����ָ����� 
	if(link){
		modifyStudentMenu(link); 
	}else{
		printf("\t\t���޴��ˣ�\n");
	} 
	// ѯ���Ƿ����������Ϣ 
	printf("\t\t�Ƿ����������(Y/N)��");
 	char choice;
	getchar();	// ������һ��scanf����������\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t��淶���룬лл��");
		printf("\t\t�Ƿ��������(Y/N)��");
		getchar();	// ������һ��scanf����������\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

/*
	���ܣ�	��ӡ�޸Ĳ˵� 
	link:	ѧ���ڵ� 
	���أ�	�ɹ�����1�����򷵻�0 
*/
int modifyStudentMenu(LinkList* link){
	printf("\t\t|\t1.����\t");
	printf("\t2.����\t\t\t |\n");
	printf("\t\t|\t3.ѧ��\t");
	printf("\t4.�ɼ�\t\t\t |\n"); 
	printf("\t\t|��ѡ����Ҫ�޸ĵ�ѡ�");
	int choice;
	while(scanf("%d", &choice) != 1 || choice != 1 && choice != 2 && choice != 3 && choice != 4){
		printf("\t\t�����������������룡");
		printf("\t\t��ѡ����Ҫ�޸ĵ�ѡ�");
	}
	switch(choice){
		case 1:
			printf("\t\tԭ������%s", link->student.name);
			printf("\t\t��������Ҫ�޸ĺ��������");
			char name[6];
			scanf("%s", name);
			if(strcmp(strcpy(link->student.name, name), link->student.name) == 0){
				printf("\t\t�޸ĳɹ���");
			}
			break;
		case 2:
			printf("\t\tԭ���䣺%d", link->student.age);
			printf("\t\t��������Ҫ�޸ĺ�����䣺");
			int age =  proofread_age();
			link->student.age = age;
			if(link->student.age == age){
				printf("�޸ĳɹ���");
			}else{
				printf("�޸�ʧ��");
			}
			break;
		case 3:
			printf("ԭѧ�ţ�%s", link->student.number);
			printf("��������Ҫ�޸ĺ��ѧ��");
			char number[12];
			// strcpy��������number��ֵ��link->student.number
			// strcmp�����Ƚ�link->student.number�Ƿ�����޸ĺ����ֵ 
			if(strcmp(strcpy(link->student.number, proofread_number(number)), link->student.number) == 0){
				printf("\t\t�޸ĳɹ���");
			}else{
				printf("\t\t�޸�ʧ�ܣ�");
			}
			break;
		case 4:
			printf("\t\t|\t1.����");
			printf("\t\t2.��ѧ");
			printf("\t\t3.Ӣ��\t |\n");
			printf("\t\t|��ѡ������޸ĵ�ѡ�");
			int choiceGrade = 0;
			while(scanf("%d", &choiceGrade) != 1 || choiceGrade != 1 && choiceGrade != 2 && choiceGrade != 3){
				printf("\t\t�����������������룡");
				printf("\t\t��ѡ����Ҫ�޸ĵ�ѡ�");
			}
			switch(choiceGrade){
				case 1:
					printf("\t\tԭ���ĳɼ���%.1lf\n", link->student.grade.chinese);
					printf("\t\t��������Ҫ�޸ĺ�����ĳɼ���");
					double chinese;
					chinese = proofread_chinese();
					printf("%.1lf", chinese);
					link->student.grade.chinese = chinese;
					if(link->student.grade.chinese == chinese){
						printf("\t\t�޸ĳɹ���\n");
					}else{
						printf("\t\t�޸�ʧ�ܣ�\n");
					}
					break;
				case 2:
					printf("\t\tԭ��ѧ�ɼ���%.1lf\n", link->student.grade.math);
					printf("\t\t��������Ҫ�޸ĺ����ѧ�ɼ���");
					double math;
					math = proofread_math();
					link->student.grade.math = math;
					if(link->student.grade.math == math){
						printf("\t\t�޸ĳɹ���");
					}else{
						printf("\t\t�޸�ʧ�ܣ�");
					}
					break;
				case 3:
					printf("\t\tԭӢ��ɼ���%.1lf", link->student.grade.english);
					printf("\t\t��������Ҫ�޸ĺ����ѧ�ɼ���");
					double english;
					english = proofread_english();
					link->student.grade.english = english;
					if(link->student.grade.english == english){
						printf("\t\t�޸ĳɹ���");
					}else{
						printf("\t\t�޸�ʧ�ܣ�");
					}
					break;
			}
	}
	// ѯ���Ƿ����¼����Ϣ 
	printf("\t\t�Ƿ�����޸�(Y/N)��");
 	char Choice;
	getchar();	// ������һ��scanf����������\n 
	while(scanf("%c", &Choice) != 1 || Choice != 'Y' && Choice != 'N'){
		printf("\t\t��淶���룬лл��");
		printf("\t\t�Ƿ�����޸�(Y/N)��");
		getchar();	// ������һ��scanf����������\n 
	} 
	if (Choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

/*
	���ܣ�����ѧ����Ϣ 
*/
void findStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  ��ѯѧ����Ϣ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
	printf("\t\t��������Ҫ����ѧ����ѧ�ţ�");
	char number[12];
	proofread_number(number);
	LinkList* node = search_studentByNumber(head, number);
	if(node){
		print_student(node); 
	}else{
		printf("��Ǹ�����޴��ˣ�");
	}
	// ѯ���Ƿ������ѯ��Ϣ 
	printf("\t\t�Ƿ������ѯ(Y/N)��");
 	char choice;
	getchar();	// ������һ��scanf����������\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t��淶���룬лл��");
		printf("\t\t�Ƿ����¼��(Y/N)��");
		getchar();	// ������һ��scanf����������\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

void sortStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  ����ѧ����Ϣ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
	printf("\t\t|\t1.��������");
	printf("\t\t|\t1.��ѧ����");
	printf("\t\t|\t1.Ӣ������");
	printf("\t\t|\t1.�ܷ�����");
	printf("\t\t|\t1.ƽ��������");
	
}

LinkList* SelectSort(LinkList* head){  
    LinkList* pfirst;      // ���к��������ı�ͷָ�� 
    LinkList* ptail;       // ���к��������ı�βָ�� 
    LinkList* pminBefore;  // ������ֵ��С�Ľڵ��ǰ���ڵ��ָ�� 
    LinkList* pmin;        // �洢��С�ڵ�  
    LinkList* p;           // ��ǰ�ȽϵĽڵ� 
   
    pfirst = NULL;  
    while (head != NULL){         //���������Ҽ�ֵ��С�Ľڵ㡣 
    //	ע�⣺����for����������ѡ������˼��ĵط� 
        for (p = head, pmin = head; p->next != NULL; p = p->next){ //	ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ�     
            if (p->next->student.grade.total > pmin->student.grade.total){ // �ҵ�һ���ȵ�ǰminС�Ľڵ㡣 
                pminBefore = p;           // �����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p�� 
                pmin       = p->next;     // �����ֵ��С�Ľڵ㡣
            }  
        }  
    
    // ����for�������󣬾�Ҫ�������£�һ�ǰ����������������У����Ǹ�����Ӧ�������жϣ��������뿪ԭ�������� 
      
        /*��һ����*/  
        if (pfirst == NULL){     // �����������Ŀǰ����һ��������  
            pfirst = pmin;      // ��һ���ҵ���ֵ��С�Ľڵ㡣
            ptail  = pmin;      // ע�⣺βָ������ָ������һ���ڵ㡣 
        }else{                 // �����������Ѿ��нڵ�   
            ptail->next = pmin; // �Ѹ��ҵ�����С�ڵ�ŵ���󣬼���βָ���nextָ������ 
            ptail = pmin;       // βָ��ҲҪָ������
        }  
        
        /*�ڶ�����*/  
        if (pmin == head){       // ����ҵ�����С�ڵ���ǵ�һ���ڵ�                 
            head = head->next;   // ��Ȼ��headָ��ԭhead->next,���ڶ����ڵ㣬��OK
        }else{ 
			//������ǵ�һ���ڵ�   
            pminBefore->next = pmin->next; // ǰ����С�ڵ��nextָ��ǰpmin��next,��������pmin�뿪��ԭ����
        }  
    }  
  
    if (pfirst != NULL){     //ѭ�������õ���������first 
        ptail->next = NULL; //������������һ���ڵ��nextӦ��ָ��NULL
    }  
    head = pfirst;  
    return head;  
}  

/*
	���ܣ�	���������ϵ����� 
*/
void save(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  ����ѧ����Ϣ                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    
	if(write_student(head)){
		printf("\t\t����ɹ���\n");
	}
	returnMainMenu();
}

/*
	���ܣ�	��ӡ����ѧԱ��Ϣ 
*/
void printStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                   ��ӡѧ����Ϣ                 |\n");
    printf("\t\t|------------------------------------------------|\n");
	if(traverse_list(head) != 1){
		printf("\t\t������Ϣ��");
	}
	returnMainMenu();
}

/*
	���ܣ�	���������� 
*/
void returnMainMenu(){
	printf("\t\t�Ƿ񷵻�������(Y/N)��");
 	char choice[10];
	getchar();	// ������һ��scanf����������\n 
	while(scanf("%s", &choice) != 1){
		printf("\t\t��淶���룬лл��");
		printf("\t\t�Ƿ����¼��(Y/N)��");
		getchar();	// ������һ��scanf����������\n 
	}
	if (strcmp(choice,"Y") == 0){
		system("cls");
		MainMenu();
	}
}

void Exit(){
	system("color Fc");
	
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
	_TCHAR buffer[25][80] = { _T(' ') };
	_TCHAR ramp[] = _T(".:-=+*#%@");
	float t;
	for (t = 0.0f;; t += 0.1f) {
		int sy = 0;
		float s = sinf(t);
		float a = s * s * s * s * 0.2f;
		float z;
		for (z = 1.3f; z > -1.2f; z -= 0.1f) {
			_TCHAR* p = &buffer[sy++][0];
			float tz = z * (1.2f - a);
			float x;
			for (x = -1.5f; x < 1.5f; x += 0.05f) {
				float tx = x * (1.2f + a);
				float v = f(tx, 0.0f, tz);
				if (v <= 0.0f) {
					float y0 = h(tx, tz);
					float ny = 0.01f;
					float nx = h(tx + ny, tz) - y0;
					float nz = h(tx, tz + ny) - y0;
					float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
					float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
					*p++ = ramp[(int)(d * 5.0f)];
				}
				else
					*p++ = ' ';
			}
		}

		for (sy = 0; sy < 25; sy++) {
			COORD coord = { 0, sy };
			SetConsoleCursorPosition(o, coord);
			WriteConsole(o, buffer[sy], 79, NULL, 0);
		}
		Sleep(33);
		printf("\n �����ˣ�XXX��-XXX");
	}
}

float f(float x, float y, float z) {
	float a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
	return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
}

float h(float x, float z) {
	float y;
	for (y = 1.0f; y >= 0.0f; y -= 0.001f){
		if (f(x, y, z) <= 0.0f){
			return y;
		}	
	}
	return 0.0f;
}
