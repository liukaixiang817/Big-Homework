#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
struct Node0
{
    struct Node0 *next;
    struct Node0 *front;
    char name[109];
    int num;
    char major[109];
    int status;//状态参量 1可用，0不可用
}student[109];
struct Node1
{
    struct Node1 *next;
    struct Node1 *front;
    char name[109];
    int cap;
    char major[109];
    char source[109];
    int status;//状态参量 1可用，0不可用
}course[109];
struct Node2
{
    struct Node2 *next;
    struct Node2 *front;
    int num;
    char passwd[109];
    int status;//状态参量 1可用，0不可用
}stulog[1009];
char passwd[109];
int student_tot=-1;
int course_tot=-1;
int main()
{
    login:
    printf("***********************LOGIN************************\n");
    int login_temp;
    FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/Login.txt","r");//*相对路径异常*，暂时引用为绝对路径
    fscanf(fp,"%d",&login_temp);
    if(!login_temp)//login_temp==0
    {
        printf("Please set the administrator's password:");
        fflush(stdin);
        scanf("%s",passwd);
        printf("***********************LOGIN************************\n");
    }
    else
    {
        fscanf(fp,"%s",passwd);
    }
    fclose(fp);
    FILE *fp2=fopen("/Users/liukaixiang/Desktop/C/C/Login.txt","w");//*相对路径异常*，暂时引用为绝对路径
    fprintf(fp2,"1\n");
    fprintf(fp2,"%s",passwd);
    fclose(fp2);
    printf("If you are the administrator, please input 1. \nIf you are a student, please input 2.\nIf you want to exit, please input other key.\n");
    printf("Please input any key:");
    char choice1;
    fflush(stdin);//此处清空缓冲区，不然第二次之后的scanf会归西
    scanf("%c",&choice1);
    switch(choice1)
    {
        case '1':
            printf("Please input the password:");
            char pawd1[109];//你输入的密码
            fflush(stdin);
            scanf("%s",pawd1);
            if(strcmp(pawd1,passwd)!=0)//总共可以输入三次密码，避免恶意穷举，虽然治标不治本，程序可以无限次打开..
            {
                printf("You may have 2 more chances to enter the correct password.\n");
                printf("Please input the password:");
                char pawd2[109];//你输入的密码
                fflush(stdin);
                scanf("%s",pawd2);
                if(strcmp(pawd2,passwd)!=0)
                {
                    printf("You may have 1 more chance to enter the correct password.\n");
                    printf("Please input the password:");
                    char pawd3[109];//你输入的密码
                    fflush(stdin);
                    scanf("%s",pawd3);
                    if(strcmp(pawd3,passwd)!=0)
                    {
                        printf("Sorry, the program will exit...\n");
                        return 0;
                    }
                }
            }
            printf("Login successfully...\n");
            sleep(1);
            AdminMenu:
            printf("***********************ADMININSTRATION MENU************************\n");
            printf("1.Student Informations Configure\n");
            printf("2.Course Informations Configure\n");
            printf("3.Choice Informations Configure\n");
            printf("Other:Logout...\n");
            printf("Please input your choice:");
            char choice2;
            fflush(stdin);//此处清空缓冲区，不然scanf归西
            scanf("%c",&choice2);
            switch(choice2)
            {
                case '1':
                    if(student_tot==-1)
                    {
                        FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/Student.txt","r");//*相对路径异常*，暂时引用为绝对路径
                        fscanf(fp,"%d",&student_tot);
                        for(int i=0;i<student_tot;i++)
                        {
                            fscanf(fp,"%s%d%s%d",student[i].name,&student[i].num,student[i].major,&student[i].status);
                        }
                        fclose(fp);
                    }
                    StudentMenu:
                    printf("*************STUDENT INFORMATION CONFIGURE MENU**************\n");
                    printf("1.View Students' Informations\n");
                    printf("2.Add Students' Informations\n");
                    printf("3.Delete Students' Informations\n");
                    printf("4.Edit Students' Informations\n");
                    printf("5.Query Students' Informations\n");
                    printf("Other:Save and Back to Administration Menu...\n");
                    printf("Please input your choice:");
                    char choice3;
                    fflush(stdin);
                    scanf("%c",&choice3);
                    switch(choice3)
                    {
                        case '1':
                            printf("Name\tNumber\tMajor\n");
                            for(int i=0;i<student_tot;i++)
                            {
                                if(student[i].status)
                                printf("%s\t\t%d\t\t%s\n",student[i].name,student[i].num,student[i].major);
                            }
                            //system("pause");
                            sleep(1);
                            goto StudentMenu;
                            break;
                        case '2':
                            printf("Please input the student's name, student's number and major.\n");
                            scanf("%s%d%s",student[student_tot].name,&student[student_tot].num,student[student_tot].major);
                            student[student_tot].status=1;
                            student_tot++;
                            printf("Student's Informations have been successfully added...\n");
                            sleep(1);
                            goto StudentMenu;
                            break;
                        case '3':
                            printf("Please input the student's number who you are going to delete.\n");
                            int student_temp1;
                            fflush(stdin);
                            scanf("%d",&student_temp1);
                            for(int i=0;i<student_tot;i++)
                            {
                                if(student[i].num==student_temp1&&(student[i].status))
                                {
                                    student[i].status=0;
                                    printf("Student's Informations have been successfully deleted...\n");
                                    sleep(1);
                                    break;
                                }
                                if(i==student_tot-1)
                                {
                                    printf("Cannot find the student...\n");
                                    printf("Back to Student Information Menu...\n");
                                    sleep(1);
                                }
                            }
                            goto StudentMenu;
                            break;
                        case '4':
                            printf("Please input the student's number who you are going to edit.\n");
                            int student_temp2;
                            fflush(stdin);
                            scanf("%d",&student_temp2);
                            for(int i=0;i<student_tot;i++)
                            {
                                if(student[i].num==student_temp2&&(student[i].status))
                                {
                                    printf("Please input the student's new name and major.\n");
                                    scanf("%s%s",student[i].name,student[i].major);
                                    printf("Student's Informations have been successfully edited...\n");
                                    sleep(1);
                                    break;
                                }
                                if(i==student_tot-1)
                                {
                                    printf("Cannot find the student...\n");
                                    printf("Back to Student Information Menu...\n");
                                    sleep(1);
                                }
                            }
                            goto StudentMenu;
                            break;
                        case '5':
                            printf("*************STUDENT INFORMATION QUERY MENU**************\n");
                            printf("1.Use Students' Number\n");
                            printf("2.Use Students' Name\n");
                            printf("Other:Back to Student Information Menu...\n");
                            char choice4;
                            fflush(stdin);
                            scanf("%c",&choice4);
                            switch(choice4)
                            {
                                case '1':
                                    printf("Please input the student's number who you are going to query:");
                                    int student_temp3;
                                    fflush(stdin);
                                    scanf("%d",&student_temp3);
                                    for(int i=0;i<student_tot;i++)
                                    {
                                        if(student[i].num==student_temp3&&(student[i].status))
                                        {
                                            printf("Name\tNumber\tMajor\n");
                                            printf("%s\t\t%d\t\t%s\n",student[i].name,student[i].num,student[i].major);
                                            printf("Finish...\n");
                                            sleep(1);
                                            break;
                                        }
                                        if(i==student_tot-1)
                                        {
                                            printf("Cannot find the student...\n");
                                            printf("Back to Student Information Menu...\n");
                                            sleep(1);
                                        }
                                    }
                                    goto StudentMenu;
                                    break;
                                case '2':
                                    printf("Please input the student's name who you are going to query:");
                                    char student_temp4[109];
                                    fflush(stdin);
                                    scanf("%s",student_temp4);
                                    for(int i=0;i<student_tot;i++)
                                    {
                                        if((!strcmp(student[i].name,student_temp4))&&(student[i].status))
                                        {
                                            printf("Name\tNumber\tMajor\n");
                                            printf("%s\t\t%d\t\t%s\n",student[i].name,student[i].num,student[i].major);
                                            printf("Finish...\n");
                                            sleep(1);
                                            break;
                                        }
                                        if(i==student_tot-1)
                                        {
                                            printf("Cannot find the student...\n");
                                            printf("Back to Student Information Menu...\n");
                                            sleep(1);
                                        }
                                    }
                                    goto StudentMenu;
                                    break;
                                default:
                                    goto StudentMenu;
                                    break;
                            }
                        default:
                            FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/Student.txt","w");//*相对路径异常*，暂时引用为绝对路径
                            fprintf(fp,"%d\n",student_tot);
                            for(int i=0;i<student_tot;i++)
                            {
                                fprintf(fp,"%s %d %s %d\n",student[i].name,student[i].num,student[i].major,student[i].status);
                            }
                            goto AdminMenu;
                            break;
                    }
                    break;
                case '2':
                    if(course_tot==-1)
                    {
                        FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/Course.txt","r");//*相对路径异常*，暂时引用为绝对路径
                        fscanf(fp,"%d",&course_tot);
                        for(int i=0;i<course_tot;i++)
                        {
                            fscanf(fp,"%s%d%s%d",course[i].name,&course[i].cap,course[i].major,&course[i].status);
                        }
                        fclose(fp);
                    }
                    CourseMenu:
                    printf("*************COURSE INFORMATION CONFIGURE MENU**************\n");
                    printf("1.View Courses' Informations\n");
                    printf("2.Add Courses' Informations\n");
                    printf("3.Delete Courses' Informations\n");
                    printf("4.Edit Courses' Informations\n");
                    printf("5.Query Courses' Informations\n");
                    printf("Other:Save and Back to Administration Menu...\n");
                    printf("Please input your choice:");
                    char choice4;
                    fflush(stdin);
                    scanf("%c",&choice4);
                    switch(choice4)
                    {
                        case '1':
                            printf("Name\t\t\t\t\tCapacity\t\t\t\t\tMajor\n");
                            for(int i=0;i<course_tot;i++)
                            {
                                if(course[i].status)
                                printf("%s\t\t\t\t\t%d\t\t\t\t\t%s\n",course[i].name,course[i].cap,course[i].major);
                            }
                            sleep(1);
                            goto CourseMenu;
                            break;
                        case '2':
                            printf("Please input the course's name, course's capacity and major.\n");
                            scanf("%s%d%s",course[course_tot].name,&course[course_tot].cap,course[course_tot].major);
                            course[course_tot].status=1;
                            course_tot++;
                            printf("Course's Informations have been successfully added...\n");
                            sleep(1);
                            goto CourseMenu;
                            break;
                        case '3':
                            printf("Please input the course's name who you are going to delete.\n");
                            char course_temp1[109];
                            fflush(stdin);
                            scanf("%s",course_temp1);
                            for(int i=0;i<course_tot;i++)
                            {
                                if((!strcmp(course_temp1,course[i].name))&&(course[i].status))
                                {
                                    course[i].status=0;
                                    printf("Course's Informations have been successfully deleted...\n");
                                    sleep(1);
                                    break;
                                }
                                if(i==course_tot-1)
                                {
                                    printf("Cannot find the course...\n");
                                    printf("Back to Course Information Menu...\n");
                                    sleep(1);
                                }
                            }
                            goto CourseMenu;
                            break;
                        case '4':
                            printf("Please input the course's name who you are going to edit.\n");
                            char course_temp2[109];
                            fflush(stdin);
                            scanf("%s",course_temp2);
                            for(int i=0;i<course_tot;i++)
                            {
                                if((!strcmp(course_temp2,course[i].name))&&(course[i].status))
                                {
                                    printf("Please input the course's new capacity and major.\n");
                                    scanf("%d%s",&course[i].cap,course[i].major);
                                    printf("Student's Informations have been successfully edited...\n");
                                    sleep(1);
                                    break;
                                }
                                if(i==course_tot-1)
                                {
                                    printf("Cannot find the course...\n");
                                    printf("Back to Course Information Menu...\n");
                                    sleep(1);
                                }
                            }
                            goto CourseMenu;
                            break;
                        case '5':
                            printf("Please input the course's name who you are going to query:");
                            char course_temp3[109];
                            fflush(stdin);
                            scanf("%s",course_temp3);
                            for(int i=0;i<course_tot;i++)
                            {
                                if((!strcmp(course[i].name,course_temp3))&&(course[i].status))
                                {
                                    printf("Name\t\t\t\t\tCapacity\t\t\t\t\tMajor\n");
                                    printf("%s\t\t\t\t\t%d\t\t\t\t\t%s\n",course[i].name,course[i].cap,course[i].major);
                                    printf("Finish...\n");
                                    sleep(1);
                                    break;
                                }
                                if(i==course_tot-1)
                                {
                                    printf("Cannot find the course...\n");
                                    printf("Back to Course Information Menu...\n");
                                    sleep(1);
                                }
                            }
                            goto CourseMenu;
                            break;
                        default:
                            FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/Course.txt","w");//*相对路径异常*，暂时引用为绝对路径
                            fprintf(fp,"%d\n",course_tot);
                            for(int i=0;i<course_tot;i++)
                            {
                                fprintf(fp,"%s %d %s %d\n",course[i].name,course[i].cap,course[i].major,course[i].status);
                            }
                            fclose(fp);
                            goto AdminMenu;
                            break;
                    }
                    break;
                case '3':
                    break;
                default:
                    goto login;
            }
            break;
        case '2':
            {
            StuLogMenu:
            printf("***********************STUDENT LOGIN MENU************************\n");
            int login_stu;
            FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/StuLog.txt","r");//*相对路径异常*，暂时引用为绝对路径
            fscanf(fp,"%d",&login_stu);
            for(int i=0;i<login_stu;i++)
            {
                fflush(stdin);
                fscanf(fp,"%d%s",&stulog[i].num,stulog[i].passwd);
            }
            fclose(fp);
            printf("1.Student Sign in\n");
            printf("2.Student Sign up\n");
            printf("Other:Back to Login Menu...\n");
            printf("Please input your choice:");
            char choice5;
            fflush(stdin);
            scanf("%c",&choice5);
            switch(choice5)
            {
                case '1':
                    printf("Please input your student number:");
                    int acc;
                    fflush(stdin);
                    scanf("%d",&acc);
                    for(int i=0;i<login_stu;i++)
                    {
                        if(acc==stulog[i].num)
                        {
                            char pwd[109];
                            printf("Please enter your password:");
                            fflush(stdin);
                            scanf("%s",pwd);
                            if(!strcmp(pwd,stulog[i].passwd))
                            {
                                StuMenu:
                                printf("Login successfully...\n");
                                sleep(1);
                                printf("***********************STUDENT MENU************************\n");//尚未完成
                                printf("1.Student Informations Configure\n");
                                printf("2.Course Informations Configure\n");
                                printf("3.Choice Informations Configure\n");
                                printf("Other:Logout...\n");
                                printf("Please input your choice:");
                                char choice2;
                                fflush(stdin);//此处清空缓冲区，不然scanf归西
                                scanf("%c",&choice2);
                                
                            }
                            else
                            {
                                    printf("You may have 2 more chances to enter the correct password.\n");
                                    printf("Please input the password:");
                                    char pwd2[109];//你输入的密码
                                    fflush(stdin);
                                    scanf("%s",pwd2);
                                    if(strcmp(pwd2,stulog[i].passwd)!=0)
                                    {
                                        printf("You may have 1 more chance to enter the correct password.\n");
                                        printf("Please input the password:");
                                        char pwd3[109];//你输入的密码
                                        fflush(stdin);
                                        scanf("%s",pwd3);
                                        if(strcmp(pwd3,stulog[i].passwd)!=0)
                                        {
                                            printf("Sorry, the program will exit...\n");
                                            return 0;
                                        }
                                        else
                                        {
                                            goto StuMenu;
                                        }
                                    }
                                    else
                                    {
                                        goto StuMenu;
                                    }
                            }
                            break;
                        }
                        if(i==login_stu-1)
                        {
                            printf("Cannot find you in the data base...\n");
                            printf("Back to Student Login Menu...\n");
                            sleep(1);
                            goto StuLogMenu;
                        }
                    }
                case '2':
                    printf("Please input your student number:");
                    fflush(stdin);
                    scanf("%d",&stulog[login_stu].num);
                    printf("Please input your password:");
                    fflush(stdin);
                    scanf("%s",stulog[login_stu].passwd);
                    login_stu++;
                    FILE *fp=fopen("/Users/liukaixiang/Desktop/C/C/StuLog.txt","w");//*相对路径异常*，暂时引用为绝对路径
                    fprintf(fp,"%d\n",login_stu);
                    for(int i=0;i<login_stu;i++)
                    {
                        fprintf(fp,"%d %s\n",stulog[i].num,stulog[i].passwd);
                    }
                    fclose(fp);
                    goto StuLogMenu;
            }
            }
            break;
        default:
            printf("The program will exit...\n");
            return 0;
    }
    return 0;
}