#include<stdio.h>
#include<string.h>

const int MAX = 256;

struct student{
    char firstname[50], lastname[50], codemeli[50], filed[50];
    int studentcode;
};
struct course{
    char code[50], name[100], t_f[50], t_l[50];
    int unit;
};
struct teacher{
    char firstname[50], lastname[50], codemeli[50], role[50], course[50];
};
void deletedline(int line, char namefile[MAX],char namefile2[MAX]){
    FILE *ptr1 = fopen(namefile, "r"), *ptr2 = fopen(namefile2, "w");
    char str[MAX];
    int ctr = 0;
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
    if(ptr2 == NULL){
        fclose(ptr1);
        printf("file can't be opened\n");
        return;
    }
    while (!feof(ptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, ptr1);
        if (!feof(ptr1))
        {
            ctr++;
            /* skip the line at given line number */
            if (ctr != line)
            {
                fprintf(ptr2, "%s", str);
            }
        }
    }
    fclose(ptr1);
    fclose(ptr2);
                usleep(50);

    remove(namefile);
                usleep(50);

    rename(namefile2, namefile);
}
void createstudent(struct student st){
    FILE *p, *ptr = fopen("students.txt", "a") , *ptr1 = fopen("auth.txt","a");
    char namefile[50];
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    if(ptr1 == NULL){
        fclose(ptr);
        printf("file can't be opened\n");
        return;
    }
    fprintf(ptr1, "%d , %s , 2\n" , st.studentcode, st.codemeli);
    fprintf(ptr, "%s , %s , %d , %s , %s\n", st.firstname, st.lastname, st.studentcode, st.codemeli, st.filed);
    sprintf(namefile , "codemeli/%s.txt" , st.codemeli);
    p = fopen(namefile, "w");
    fclose(p);
    fclose(ptr);
    fclose(ptr1);
}
void readstudent(){
    FILE *ptr = fopen("students.txt", "r");
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    char pt;
    while(pt != EOF){
        pt = fgetc(ptr);
        printf("%c", pt);
    }
    fclose(ptr);
}
void deletestudent(char code[50]){
    FILE *ptr1 = fopen("students.txt", "r"), *ptr2 = fopen("auth.txt", "r");
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
    if(ptr2 == NULL){
        printf("file can't be opened\n");
        return;
    }
    char user[MAX];
    int line = 0;
    while(fscanf(ptr1, "%*s , %*s , %s , %*s , %*s", user) != EOF){
        line ++;
        if(!strcmp(user,code)){
            fclose(ptr1);
            deletedline(line, "students.txt","temp.txt");
        }
    }
	line = 0;
    while(fscanf(ptr2, "%s , %*s , %*d", user) != EOF){
          line ++;
          if(!strcmp(user,code)){
              fclose(ptr2);
              deletedline(line, "auth.txt","temp.txt");
          }
    }
}
void createcourses(struct course co){
    FILE *ptr = fopen("courses.txt", "a");
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    fprintf(ptr, "%s , %s , %s , %s , %d\n", co.code, co.name, co.t_f, co.t_l, co.unit);
    fclose(ptr);
}
void readcourse(){
    FILE *ptr = fopen("courses.txt", "r");
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    char pt;
    while(pt != EOF){
        pt = fgetc(ptr);
        printf("%c", pt);
    }
    fclose(ptr);
}
void deletedcourse(char code[50]){
    FILE *ptr = fopen("courses.txt", "r");
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    int line = 0;
    char courseCode[50];
    while(fscanf(ptr, "%s , %*50[^\n] , %*s , %*s , %*d", courseCode) == 1){
        line ++;
        if(!strcmp(courseCode,code)){
            fclose(ptr);
            deletedline(line, "courses.txt","temp.txt");
        }
    }
}
void createteachers(struct teacher te){
    FILE *ptr1 = fopen("teachers.txt", "a"), *ptr2 = fopen("auth.txt","a");
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
  	if(ptr2 == NULL){
      	fclose(ptr1);
        printf("file can't be opened\n");
        return;
    }
    fprintf(ptr2, "%s , %s , 3\n" , te.codemeli, te.codemeli);
    fprintf(ptr1, "%s , %s , %s , %s , %s\n", te.firstname, te.lastname, te.codemeli, te.role, te.course);
    fclose(ptr1);
  	fclose(ptr2);
}
void readteacher(){
    FILE *ptr = fopen("teachers.txt", "r");
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    char pt;
    while(pt != EOF){
        pt = fgetc(ptr);

        printf("%c", pt);
    }
    fclose(ptr);
}
void deletedteacher(char code[50]){
    FILE *ptr1 = fopen("teachers.txt", "r"), *ptr2 = fopen("auth.txt", "r");
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
    if(ptr2 == NULL){
        printf("file can't be opened\n");
    	fclose(ptr1);
        return;
    }
    int line = 0;
    char teacherCode[50];
    while(fscanf(ptr1, "%*s , %*s , %s , %*s , %*s", teacherCode) != EOF){
        line ++;
        if(!strcmp(teacherCode,code)){
            fclose(ptr1);
            deletedline(line, "teachers.txt","temp.txt");
        }
	}
  	line = 0;
	while(fscanf(ptr2, "%s , %*s , %*d", teacherCode) != EOF){
        line ++;
        if(!strcmp(teacherCode,code)){
            fclose(ptr2);
            deletedline(line, "auth.txt","temp.txt");
        }
	}

}
void addcourse(char code[50], char namefile[50]){
	FILE *ptr1 = fopen(namefile, "a+"), *ptr2 = fopen("courses.txt", "r");
  	struct course co;
  	if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
    if(ptr2 == NULL){
        printf("file can't be opened\n");
    	fclose(ptr1);
        return;
    }
    while(fscanf(ptr1, "%s , %*s , %*s , %*s , %*d", co.code) != EOF){
        if(!strcmp(co.code, code)){
            printf("course added last time");
            return;
        }
    }
	int line = 0;
    while(fscanf(ptr2, "%s , %s , %s , %s , %d", co.code, co.name, co.t_f, co.t_l, &co.unit) != EOF){
        line ++;
        if(!strcmp(co.code, code)){
            fclose(ptr2);
            fprintf(ptr1, "%s , %s , %s , %s , %d\n", co.code, co.name, co.t_f, co.t_l, co.unit);
    		fclose(ptr1);
            printf("\n%s\n", "The course has been successfully added to your list.");
            return;
        }
    }
    printf("course not found.");
	fclose(ptr1);
  	fclose(ptr2);
    return;
}
int authentication(char username[50] , char password[50]){
    FILE *ptr = fopen("auth.txt", "r");
    if(ptr == NULL){
        printf("file can't be opened\n");
      	printf("Your username or password is incorrect\n");
        return 0;
    }
    char user[50] , pass[50];
    int role;
    while(fscanf(ptr, "%s , %s , %d", user , pass , &role) != EOF){
        if(!strcmp(username,user)){
            if (!strcmp(password,pass))
            {
            	fclose(ptr);
                return role;
            }
        }
    }
	printf("Your username or password is incorrect\n");
    fclose(ptr);
    return 0;
}
/*

*/
void removecourse(char code[50],char namefile[50]){
     FILE *ptr1 = fopen(namefile, "r");
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
    int line = 0;
    char codecourse[50];
	while(fscanf(ptr1, "%s , %*s , %*s , %*s , %*d", codecourse) != EOF){
        line ++;
        if(!strcmp(codecourse,code)){
            fclose(ptr1);
            deletedline(line, namefile,"codemeli/temp.txt");
        }
	}
}
void showcourse(char namefile[50]){
    FILE *ptr = fopen(namefile, "r");
    if(ptr == NULL){
        printf("file can't be opened\n");
        return;
    }
    char pt;
    while(pt != EOF){
        pt = fgetc(ptr);
        printf("%c", pt);
    }
    fclose(ptr);
}
void showcourse_t(char code[50]){
    FILE *ptr1 = fopen("teachers", "r"), *ptr2 = fopen("courses", "r");
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        return;
    }
    if(ptr1 == NULL){
        printf("file can't be opened\n");
        fclose(ptr1);
        return;
    }
    char coursecode[50], coursename[50], t_f[50], t_l[50], firstname[50], lastname[50], teacherCode[50];
    int unit;
    while(fscanf(ptr1, "%s , %s , %s , %*s , %*s", firstname, lastname, teacherCode) != EOF)
        if(!strcmp(teacherCode, code))
                break;
    while(fscanf(ptr2, "%s , %s , %s , %s , %d", coursecode, coursename, t_f, t_l, unit) != EOF)
        if(!strcmp(firstname, t_f))
            if(!strcmp(lastname, t_l))
                printf("course code : %s --- course name : %s --- course unit : %d\n", coursecode, coursename, unit);
}
int main(){
    int role, request;
    struct student st;
    struct course co;
  	struct teacher te;
    char user[50], pass[50];
    printf("%s\n\n", "* * * Welcome to the unit selection system * * * ");
    //usleep(3000000);
    printf("Dear student, your username is your student code and your password is your national code.\n");
    printf("Dear professor, your username and password is your national code.\n\n");
    //usleep(8000000);
    do{
        printf("Please enter your username : ");
        scanf("%s", user);
        printf("Please enter your password : ");
        scanf("%s", pass);
        role = authentication(user, pass);
    }while(role == 0);
    printf("\nYour login was successful\n");
    //usleep(2000000);
    switch(role){
        case 1 :
            printf("%s\n", "0 - End of the work");
            printf("%s\n", "1 - Add student");
            printf("%s\n", "2 - Remove the student");
            printf("%s\n", "3 - View the list of students");
            printf("%s\n", "4 - Add a course");
            printf("%s\n", "5 - Delete a course");
            printf("%s\n", "6 - View the list of courses");
            printf("%s\n", "7 - Add a teacher");
            printf("%s\n", "8 - Remove the teacher");
            printf("%s\n\n", "9 - View the list of teachers");
            //usleep(5000000);
            do{
                printf("%s", "\nPlease select your request : ");
                scanf("%d", &request);
                switch(request){
                    case 1 :
                        printf("%s", "Please enter the student's firs name : ");
                        scanf("%s", st.firstname);
                        printf("%s", "Please enter the student's last name : ");
                        scanf("%s", st.lastname);
                        printf("%s", "Please enter the student's student code : ");
                        scanf("%d", &st.studentcode);
                        printf("%s", "Please enter the student's national code : ");
                        scanf("%s", st.codemeli);
                        printf("%s", "Please enter the student's field : ");
                        scanf("%s", st.filed);
                        createstudent(st);
                        printf("\n%s\n", "Adding the student to the list was done successfully.");
                        break;
                    case 2 :
                        printf("%s", "Please enter the student's student code : ");
                        char codestudent[50];
                        scanf("%s", codestudent);
                        deletestudent(codestudent);
                        printf("\n%s\n", "Removing the student from the list was done successfully.");
                        break;
                    case 3 :
                        printf("\nList of students : \n");
                        readstudent();
                        break;
                    case 4 :
                        printf("%s", "Please enter the course code : ");
                        scanf("%s", co.code);
                        printf("%s", "Please enter the course name : ");
                        scanf("%s", co.name);
                        printf("%s", "Please enter the first name of the teacher : ");
                        scanf("%s", &co.t_f);
                    	printf("%s", "Please enter the last name of the teacher : ");
                        scanf("%s", &co.t_l);
                    	printf("%s", "Please enter the unit code  : ");
                        scanf("%d", &co.unit);
                        createcourses(co);
                        printf("\n%s\n", "Adding the course to the list was done successfully.");
                        break;
                    case 5 :
                        printf("%s", "Please enter the course code : ");
                        char codecourse[50];
                        scanf("%s", codecourse);
                        deletedcourse(codecourse);
                        printf("\n%s\n", "Removing the course from the list was done successfully.");
                        break;
                    case 6 :
                        printf("\nList of courses : \n");
                        readcourse();
                        break;
                    case 7 :
                    	printf("%s", "Please enter the teacher's firs name : ");
                        scanf("%s", te.firstname);
                        printf("%s", "Please enter the teacher's last name : ");
                        scanf("%s", te.lastname);
                        printf("%s", "Please enter the teacher's codemeli : ");
                        scanf("%s", te.codemeli);
                        printf("%s", "Please enter the teacher's role : ");
                        scanf("%s", te.role);
                        printf("%s", "Please enter the teacher's course : ");
                        scanf("%s", te.course);
                        createteachers(te);
                        printf("\n%s\n", "Adding the teacher to the list was done successfully.");
                        break;
                    case 8 :
                    	printf("%s", "Please enter the Teacher's national code : ");
                        char code[50];
                        scanf("%s", code);
                        deletedteacher(code);
                        printf("\n%s\n", "Removing the teacher from the list was done successfully.");
                        break;
                    case 9 :
                    	printf("\nList of teachers : \n");
                        readteacher();
                        break;
                }
            }while(request != 0);
        case 2 :
            printf("%s\n", "0 - End of the work");
            printf("%s\n", "1 - View the list of courses");
            printf("%s\n", "2 - Add a course");
            printf("%s\n", "3 - Delete a course");
        	printf("%s\n", "4 - view the personal course");
        	char namefile[50];
        	sprintf(namefile , "codemeli/%s.txt" , pass);
        	do{
              	printf("%s", "\nPlease select your request : ");
                scanf("%d", &request);
                switch(request){
                	case 1 :
                    	printf("\nList of courses : \n");
                        readcourse();
                        break;
                  	case 2 :
                        printf("%s", "Please enter the course code : ");
                        char code[50];
                        scanf("%s", code);
                    	addcourse(code,namefile);
                        break;
                    case 3 :
                    	printf("%s", "Please enter the course code : ");
                        char codecourse[50];
                        scanf("%s", codecourse);
                    	removecourse(codecourse,namefile);
                    	printf("\n%s\n", "The course has been successfully Deleted to your list.");
                        break;
                    case 4 :
                        printf("\nList of courses : \n");
                        showcourse(namefile);
                        break;
                }
            }while(request != 0);
        case 3 :
            printf("%s\n", "0 - End of the work");
            printf("%s\n", "1 - View the list of courses you are going to offer");
            printf("%s\n", "2 - List of students enrolled in your courses");
            do{
                printf("%s", "\nPlease select your request : ");
                scanf("%d", &request);
                switch(request){
                    case 1:
                        printf("\nList of courses you are going to offer : \n");
                        showcourse_t1(user);
                    case 2:

                }
            }while(request != 0);
	}
}

