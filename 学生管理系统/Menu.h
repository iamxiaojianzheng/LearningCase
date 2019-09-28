#include	<stdio.h>
#include	<math.h> 
#include 	<windows.h>
#include 	<tchar.h>
#include 	"Student_LinkList.h"

//函数声明 
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
	功能：显示主界面
	返回：void 
*/
void MainMenu(){
	// 当head第一次为null时，初始化 
	if(head == NULL){
		head = init_student_list();
	}
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  成绩管理系统                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|    1.增加学生信息        2.删除学生信息        |\n");
    printf("\t\t|    3.修改学生信息        4.查找学生信息        |\n");
    printf("\t\t|    5.学生总信息          6.保存信息(修改后)    |\n");
    printf("\t\t|    其余任意键退出！(退出前请记得保存信息)      |\n");
    printf("\t\t|------------------------------------------------|\n");
	printf("\t\t 请输入您的选择："); 
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
    printf("\t\t|                  增加学生信息                  |\n");
    printf("\t\t|------------------------------------------------|\n");
	// 暂存学生信息 
	LinkList* node;
	node = (LinkList*)malloc(LEN); 
	
	// 姓名 
	printf("\t\t请输入姓名：");
	scanf("%s", node->student.name);
	
	// 年龄
	printf("\t\t请输入年龄：");
	int age = 0;
	while(scanf("%d", &age) != 1 || age < 0 || age > 100){
		printf("年龄输入有误，请重新输入！\n"); 
		printf("请输入年龄：");
	}
	node->student.age = age; 
	
	// 学号
	printf("\t\t请输入学号：");
	char number[12];
	strcpy(node->student.number, proofread_number(number)); 
	
	// 语文
	printf("\t\t请输入语文成绩：");
	double chinese = 0;
	chinese = proofread_chinese();
	node->student.grade.chinese = chinese;
 	
 	// 数学 
	printf("\t\t请输入数学成绩：");
	double math = proofread_math();
	node->student.grade.math = math;
 	
 	// 英语
	printf("\t\t请输入英语成绩：");
	double english = 0;
	english = proofread_english();
	node->student.grade.english = english;
 	
 	int judge = add_student(head, node);
 	if(judge == 1){
	 	printf("\t\t录入成功！\n");
		print_student(node);
	}else{
 		printf("\t\t%s已经存在！\n", node->student.number);
 	}
 	// 询问是否继续录入信息 
	printf("\t\t是否继续录入(Y/N)？");
 	char choice;
	getchar();	// 接受上一个scanf遗留下来的\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t请规范输入，谢谢！\n");
		printf("\t\t是否继续录入(Y/N)？");
		getchar();	// 接受上一个scanf遗留下来的\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
	
}

/*
	功能：	删除学生 
*/
void deleteStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  增加学生信息                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    
	printf("\t\t请输入你要删除学生的学号：");
	char number[12];
	proofread_number(number);
	LinkList* trail = head, *p = head->next;
	for(; p; trail = p, p = p->next){
		if(strcmp(number, p->student.number) == 0){
			delete_student(head, trail, p);
		}else if(p->next == NULL){
			printf("\t\t查无此人！\n");
		}	
	}
	// 询问是否继续删除信息 
	printf("\t\t是否继续删除(Y/N)？");
 	char choice;
	getchar();	// 接受上一个scanf遗留下来的\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t请规范输入，谢谢！");
		printf("\t\t是否继续删除(Y/N)？");
		getchar();	// 接受上一个scanf遗留下来的\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

/*
	功能：修改学生信息 
*/
void modifyStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  删除学生信息                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    
	printf("\t\t|请输入你要修改学生的学号：");
	char number[12];
	proofread_number(number);
	LinkList* link = search_studentByNumber(head, number);	// 因为要修改数据所以需要声明指针变量 
	if(link){
		modifyStudentMenu(link); 
	}else{
		printf("\t\t查无此人！\n");
	} 
	// 询问是否继续查找信息 
	printf("\t\t是否继续查找入(Y/N)？");
 	char choice;
	getchar();	// 接受上一个scanf遗留下来的\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t请规范输入，谢谢！");
		printf("\t\t是否继续查找(Y/N)？");
		getchar();	// 接受上一个scanf遗留下来的\n 
	} 
	if (choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

/*
	功能：	打印修改菜单 
	link:	学生节点 
	返回：	成功返回1，否则返回0 
*/
int modifyStudentMenu(LinkList* link){
	printf("\t\t|\t1.姓名\t");
	printf("\t2.年龄\t\t\t |\n");
	printf("\t\t|\t3.学号\t");
	printf("\t4.成绩\t\t\t |\n"); 
	printf("\t\t|请选择你要修改的选项：");
	int choice;
	while(scanf("%d", &choice) != 1 || choice != 1 && choice != 2 && choice != 3 && choice != 4){
		printf("\t\t输入有误，请重新输入！");
		printf("\t\t请选择你要修改的选项：");
	}
	switch(choice){
		case 1:
			printf("\t\t原姓名：%s", link->student.name);
			printf("\t\t请输入你要修改后的姓名：");
			char name[6];
			scanf("%s", name);
			if(strcmp(strcpy(link->student.name, name), link->student.name) == 0){
				printf("\t\t修改成功！");
			}
			break;
		case 2:
			printf("\t\t原年龄：%d", link->student.age);
			printf("\t\t请输入你要修改后的年龄：");
			int age =  proofread_age();
			link->student.age = age;
			if(link->student.age == age){
				printf("修改成功！");
			}else{
				printf("修改失败");
			}
			break;
		case 3:
			printf("原学号：%s", link->student.number);
			printf("请输入你要修改后的学号");
			char number[12];
			// strcpy函数将新number赋值给link->student.number
			// strcmp函数比较link->student.number是否等于修改后的数值 
			if(strcmp(strcpy(link->student.number, proofread_number(number)), link->student.number) == 0){
				printf("\t\t修改成功！");
			}else{
				printf("\t\t修改失败！");
			}
			break;
		case 4:
			printf("\t\t|\t1.语文");
			printf("\t\t2.数学");
			printf("\t\t3.英语\t |\n");
			printf("\t\t|请选择你的修改的选项：");
			int choiceGrade = 0;
			while(scanf("%d", &choiceGrade) != 1 || choiceGrade != 1 && choiceGrade != 2 && choiceGrade != 3){
				printf("\t\t输入有误，请重新输入！");
				printf("\t\t请选择你要修改的选项：");
			}
			switch(choiceGrade){
				case 1:
					printf("\t\t原语文成绩：%.1lf\n", link->student.grade.chinese);
					printf("\t\t请输入你要修改后的语文成绩：");
					double chinese;
					chinese = proofread_chinese();
					printf("%.1lf", chinese);
					link->student.grade.chinese = chinese;
					if(link->student.grade.chinese == chinese){
						printf("\t\t修改成功！\n");
					}else{
						printf("\t\t修改失败！\n");
					}
					break;
				case 2:
					printf("\t\t原数学成绩：%.1lf\n", link->student.grade.math);
					printf("\t\t请输入你要修改后的数学成绩：");
					double math;
					math = proofread_math();
					link->student.grade.math = math;
					if(link->student.grade.math == math){
						printf("\t\t修改成功！");
					}else{
						printf("\t\t修改失败！");
					}
					break;
				case 3:
					printf("\t\t原英语成绩：%.1lf", link->student.grade.english);
					printf("\t\t请输入你要修改后的数学成绩：");
					double english;
					english = proofread_english();
					link->student.grade.english = english;
					if(link->student.grade.english == english){
						printf("\t\t修改成功！");
					}else{
						printf("\t\t修改失败！");
					}
					break;
			}
	}
	// 询问是否继续录入信息 
	printf("\t\t是否继续修改(Y/N)？");
 	char Choice;
	getchar();	// 接受上一个scanf遗留下来的\n 
	while(scanf("%c", &Choice) != 1 || Choice != 'Y' && Choice != 'N'){
		printf("\t\t请规范输入，谢谢！");
		printf("\t\t是否继续修改(Y/N)？");
		getchar();	// 接受上一个scanf遗留下来的\n 
	} 
	if (Choice == 'Y'){
		addStudent(head);
	}else{
		system("cls");
		MainMenu();
	}
}

/*
	功能：查找学生信息 
*/
void findStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  查询学生信息                  |\n");
    printf("\t\t|------------------------------------------------|\n");
	printf("\t\t请输入你要查找学生的学号：");
	char number[12];
	proofread_number(number);
	LinkList* node = search_studentByNumber(head, number);
	if(node){
		print_student(node); 
	}else{
		printf("抱歉，查无此人！");
	}
	// 询问是否继续查询信息 
	printf("\t\t是否继续查询(Y/N)？");
 	char choice;
	getchar();	// 接受上一个scanf遗留下来的\n 
	while(scanf("%c", &choice) != 1 || choice != 'Y' && choice != 'N'){
		printf("\t\t请规范输入，谢谢！");
		printf("\t\t是否继续录入(Y/N)？");
		getchar();	// 接受上一个scanf遗留下来的\n 
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
    printf("\t\t|                  排序学生信息                  |\n");
    printf("\t\t|------------------------------------------------|\n");
	printf("\t\t|\t1.语文排序");
	printf("\t\t|\t1.数学排序");
	printf("\t\t|\t1.英语排序");
	printf("\t\t|\t1.总分排序");
	printf("\t\t|\t1.平均分排序");
	
}

LinkList* SelectSort(LinkList* head){  
    LinkList* pfirst;      // 排列后有序链的表头指针 
    LinkList* ptail;       // 排列后有序链的表尾指针 
    LinkList* pminBefore;  // 保留键值更小的节点的前驱节点的指针 
    LinkList* pmin;        // 存储最小节点  
    LinkList* p;           // 当前比较的节点 
   
    pfirst = NULL;  
    while (head != NULL){         //在链表中找键值最小的节点。 
    //	注意：这里for语句就是体现选择排序思想的地方 
        for (p = head, pmin = head; p->next != NULL; p = p->next){ //	循环遍历链表中的节点，找出此时最小的节点     
            if (p->next->student.grade.total > pmin->student.grade.total){ // 找到一个比当前min小的节点。 
                pminBefore = p;           // 保存找到节点的前驱节点：显然p->next的前驱节点是p。 
                pmin       = p->next;     // 保存键值更小的节点。
            }  
        }  
    
    // 上面for语句结束后，就要做两件事；一是把它放入有序链表中；二是根据相应的条件判断，安排它离开原来的链表。 
      
        /*第一件事*/  
        if (pfirst == NULL){     // 如果有序链表目前还是一个空链表  
            pfirst = pmin;      // 第一次找到键值最小的节点。
            ptail  = pmin;      // 注意：尾指针让它指向最后的一个节点。 
        }else{                 // 有序链表中已经有节点   
            ptail->next = pmin; // 把刚找到的最小节点放到最后，即让尾指针的next指向它。 
            ptail = pmin;       // 尾指针也要指向它。
        }  
        
        /*第二件事*/  
        if (pmin == head){       // 如果找到的最小节点就是第一个节点                 
            head = head->next;   // 显然让head指向原head->next,即第二个节点，就OK
        }else{ 
			//如果不是第一个节点   
            pminBefore->next = pmin->next; // 前次最小节点的next指向当前pmin的next,这样就让pmin离开了原链表。
        }  
    }  
  
    if (pfirst != NULL){     //循环结束得到有序链表first 
        ptail->next = NULL; //单向链表的最后一个节点的next应该指向NULL
    }  
    head = pfirst;  
    return head;  
}  

/*
	功能：	保存链表上的数据 
*/
void save(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                  保存学生信息                  |\n");
    printf("\t\t|------------------------------------------------|\n");
    
	if(write_student(head)){
		printf("\t\t保存成功！\n");
	}
	returnMainMenu();
}

/*
	功能：	打印所有学员信息 
*/
void printStudent(LinkList* head){
	system("cls");
	
	printf("\t\t|------------------------------------------------|\n");
    printf("\t\t|                   打印学生信息                 |\n");
    printf("\t\t|------------------------------------------------|\n");
	if(traverse_list(head) != 1){
		printf("\t\t暂无信息！");
	}
	returnMainMenu();
}

/*
	功能：	返回主界面 
*/
void returnMainMenu(){
	printf("\t\t是否返回主界面(Y/N)？");
 	char choice[10];
	getchar();	// 接受上一个scanf遗留下来的\n 
	while(scanf("%s", &choice) != 1){
		printf("\t\t请规范输入，谢谢！");
		printf("\t\t是否继续录入(Y/N)？");
		getchar();	// 接受上一个scanf遗留下来的\n 
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
		printf("\n 制作人：XXX班-XXX");
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
