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
    int status;//状态参量 1可用，0不可用，为回收站功能预留，现已上线
}student[109];
struct Node1
{
    struct Node1 *next;
    struct Node1 *front;
    char name[109];
    int cap;
    char major[109];
    int source;
    int status;//状态参量 1可用，0不可用，为回收站功能预留，现已上线
}course[109];
struct Node2
{
    struct Node2 *next;
    struct Node2 *front;
    int num;
    char passwd[109];
    int cou1;
    int cou2;
    int cou3;
    int status;//状态参量 1可用，0不可用，此处没什么用，为后期（可能是100年以后）升级预留接口
}stulog[1009];
char passwd[109];
int student_tot=-1;
int course_tot=-1;
char buffer[1000];
int main()
{
    getcwd(buffer,1000);
    char buffer1[1000];
    strcpy(buffer1,buffer);
    char str1[]="\\Login.txt";
    strcat(buffer1,str1);
    char buffer2[1000];
    strcpy(buffer2,buffer);
    char str2[]="\\Course.txt";
    strcat(buffer2,str2);
    char buffer3[1000];
    strcpy(buffer3,buffer);
    char str3[]="\\Student.txt";
    strcat(buffer3,str3);
    char buffer4[1000];
    strcpy(buffer4,buffer);
    char str4[]="\\StuLog.txt";
    strcat(buffer4,str4);
    login:
    printf("***********************LOGIN************************\n");
    int login_temp;
    FILE *fp=fopen(buffer1,"r");
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
    FILE *fp2=fopen(buffer1,"w");
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
                        FILE *fp=fopen(buffer3,"r");
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
                    printf("6.Show The Recycle Bin\n");
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
                            printf("Please input the student's name, student's number and major:");
                            scanf("%s%d%s",student[student_tot].name,&student[student_tot].num,student[student_tot].major);
                            student[student_tot].status=1;
                            student_tot++;
                            printf("Student's Informations have been successfully added...\n");
                            sleep(1);
                            goto StudentMenu;
                            break;
                        case '3':
                            printf("Please input the student's number who you are going to delete:");
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
                            printf("Please input the student's number who you are going to edit:");
                            int student_temp2;
                            fflush(stdin);
                            scanf("%d",&student_temp2);
                            for(int i=0;i<student_tot;i++)
                            {
                                if(student[i].num==student_temp2&&(student[i].status))
                                {
                                    printf("Please input the student's new name and major:");
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
                            printf("Please input your choice:");
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
                        case '6':
                            StuBin:
                            printf("*************RECYCLE BIN MENU**************\n");
                            printf("1.Show The Recycle Bin\n");
                            printf("2.Complete Delete with the student's number\n");
                            printf("3.Recovery with the student's number\n");
                            printf("Other:Back to Student Information Menu...\n");
                            printf("Please input your choice:");
                            char Bchoice1;
                            fflush(stdin);
                            scanf("%c",&Bchoice1);
                            switch(Bchoice1)
                            {
                                case '1':
                                    printf("Name\tNumber\tMajor\n");
                                    for(int i=0;i<student_tot;i++)
                                    {
                                        if(!student[i].status)
                                        printf("%s\t\t%d\t\t%s\n",student[i].name,student[i].num,student[i].major);
                                    }
                                    sleep(1);
                                    goto StuBin;
                                    break;
                                case '2':
                                    printf("Please input the student's number who you are going to complete delete:");
                                    int del1;
                                    scanf("%d",&del1);
                                    for(int i=0;i<student_tot;i++)
                                    {
                                        if(student[i].num==del1)
                                        {
                                            for(int j=i;j<student_tot-1;j++)
                                            {
                                                student[j]=student[j+1];
                                            }
                                            student_tot--;
                                            printf("Student's Informations have been completely deleted...\n");
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
                                    goto StuBin;
                                    break;
                                case '3':
                                    printf("Please input the student's number who you are going to recovery:");
                                    int del2;
                                    scanf("%d",&del2);
                                    for(int i=0;i<student_tot;i++)
                                    {
                                        if(student[i].num==del2)
                                        {
                                            student[i].status=1;
                                            printf("Student's Informations have been successfully recovery...\n");
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
                                    goto StuBin;
                                    break;
                                default:
                                    goto StudentMenu;
                                    break;
                            }
                        default:
                            FILE *fp=fopen(buffer3,"w");
                            fprintf(fp,"%d\n",student_tot);
                            for(int i=0;i<student_tot;i++)
                            {
                                fprintf(fp,"%s %d %s %d\n",student[i].name,student[i].num,student[i].major,student[i].status);
                            }
                            student_tot=-1;
                            goto AdminMenu;
                            break;
                    }
                    break;
                case '2':
                    if(course_tot==-1)
                    {
                        FILE *fp=fopen(buffer2,"r");
                        fscanf(fp,"%d",&course_tot);
                        for(int i=0;i<course_tot;i++)
                        {
                            fscanf(fp,"%s%d%s%d%d",course[i].name,&course[i].cap,course[i].major,&course[i].status,&course[i].source);
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
                    printf("6.Show The Recycle Bin\n");
                    printf("Other:Save and Back to Administration Menu...\n");
                    printf("Please input your choice:");
                    char choice4;
                    fflush(stdin);
                    scanf("%c",&choice4);
                    switch(choice4)
                    {
                        case '1':
                            printf("Name\t\t\t\t\tCapacity\t\t\t\t\tMajor\t\t\t\t\tQuota\n");
                            for(int i=0;i<course_tot;i++)
                            {
                                if(course[i].status)
                                printf("%s\t\t\t\t\t%d\t\t\t\t\t%s\t\t\t\t\t%d\n",course[i].name,course[i].cap,course[i].major,course[i].source);
                            }
                            sleep(1);
                            goto CourseMenu;
                            break;
                        case '2':
                            printf("Please input the course's name, course's capacity, major and quota:");
                            scanf("%s%d%s%d",course[course_tot].name,&course[course_tot].cap,course[course_tot].major,&course[course_tot].source);
                            course[course_tot].status=1;
                            course_tot++;
                            printf("Course's Informations have been successfully added...\n");
                            sleep(1);
                            goto CourseMenu;
                            break;
                        case '3':
                            printf("Please input the course's name who you are going to delete:");
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
                            printf("Please input the course's name who you are going to edit:");
                            char course_temp2[109];
                            fflush(stdin);
                            scanf("%s",course_temp2);
                            for(int i=0;i<course_tot;i++)
                            {
                                if((!strcmp(course_temp2,course[i].name))&&(course[i].status))
                                {
                                    printf("Please input the course's new capacity, major and quota:");
                                    scanf("%d%s%d",&course[i].cap,course[i].major,&course[i].source);
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
                                    printf("Name\t\t\t\t\tCapacity\t\t\t\t\tMajor\t\t\t\tQuota\n");
                                    printf("%s\t\t\t\t\t%d\t\t\t\t\t%s\t\t\t\t\t%d\n",course[i].name,course[i].cap,course[i].major,course[i].source);
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
                        case '6':
                            CourseBin:
                            printf("*************RECYCLE BIN MENU**************\n");
                            printf("1.Show The Recycle Bin\n");
                            printf("2.Complete Delete with the course's name\n");
                            printf("3.Recovery with the course's name\n");
                            printf("Other:Back to Course Information Menu...\n");
                            printf("Please input your choice:");
                            char Bchoice2;
                            fflush(stdin);
                            scanf("%c",&Bchoice2);
                            switch(Bchoice2)
                            {
                                case '1':
                                    printf("Name\t\t\t\t\tCapacity\t\t\t\t\tMajor\t\t\t\t\tQuota\n");
                                    for(int i=0;i<course_tot;i++)
                                    {
                                        if(!course[i].status)
                                        printf("%s\t\t\t\t\t%d\t\t\t\t\t%s\t\t\t\t\t%d\n",course[i].name,course[i].cap,course[i].major,course[i].source);
                                    }
                                    sleep(1);
                                    goto CourseBin;
                                    break;
                                case '2':
                                    printf("Please input the course's name which you are going to complete delete:");
                                    char del3[109];
                                    fflush(stdin);
                                    scanf("%s",del3);
                                    for(int i=0;i<course_tot;i++)
                                    {
                                        if(strcmp(course[i].name,del3)==0)
                                        {
                                            for(int j=i;j<course_tot-1;j++)
                                            {
                                                course[j]=course[j+1];
                                            }
                                            course_tot--;
                                            printf("Course's Informations have been completely deleted...\n");
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
                                    goto CourseBin;
                                    break;
                                case '3':
                                    printf("Please input the course's name who you are going to recovery:");
                                    char del4[109];
                                    fflush(stdin);
                                    scanf("%s",del4);
                                    for(int i=0;i<course_tot;i++)
                                    {
                                        if(strcmp(course[i].name,del4)==0)
                                        {
                                            course[i].status=1;
                                            printf("Course's Informations have been successfully recovery...\n");
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
                                    goto CourseBin;
                                    break;
                                default:
                                    goto CourseMenu;
                                    break;
                            }
                        default:
                            FILE *fp=fopen(buffer2,"w");
                            fprintf(fp,"%d\n",course_tot);
                            for(int i=0;i<course_tot;i++)
                            {
                                fprintf(fp,"%s %d %s %d %d\n",course[i].name,course[i].cap,course[i].major,course[i].status,course[i].source);
                            }
                            course_tot=-1;
                            fclose(fp);
                            goto AdminMenu;
                            break;
                    }
                    break;
                case '3':
                    if(course_tot==-1)
                    {
                        FILE *fp=fopen(buffer2,"r");
                        fscanf(fp,"%d",&course_tot);
                        for(int i=0;i<course_tot;i++)
                        {
                            fscanf(fp,"%s%d%s%d%d",course[i].name,&course[i].cap,course[i].major,&course[i].status,&course[i].source);
                        }
                        fclose(fp);
                    }
                    ChoiceMenu:
                    printf("*************CHOICE INFORMATION CONFIGURE MENU**************\n");
                    printf("1.Different courses selected in order from highest to lowest\n");
                    printf("2.Any one major sorted by the selection of different courses\n");
                    printf("Other:Back to Administration Menu...\n");
                    printf("Please input your choice:");
                    char choice9;
                    fflush(stdin);
                    scanf("%c",&choice9);
                    switch(choice9)
                    {
                        case '1':
                            int cnt[1009][109];
                            for(int i=0;i<1009;i++)
                            {
                                for(int j=0;j<109;j++)
                                {
                                    cnt[i][j]=-1;
                                }
                            }
                            for(int i=0;i<course_tot;i++)
                            {
                                int j=0;
                                while(cnt[course[i].source][j]!=-1)
                                {
                                    j++;
                                }
                                cnt[course[i].source][j]=i;
                            }
                            printf("The result is:\n");
                            for(int i=0;i<1009;i++)
                            {
                                int j=0;
                                while(cnt[i][j]!=-1)
                                {
                                    printf("%s\n",course[cnt[i][j]].name);
                                    j++;
                                }
                            }
                            printf("Finished...\n");
                            sleep(1);
                            goto ChoiceMenu;
                            break;
                        case '2':
                        {
                            int flg=0;
                            printf("Please input the major's name:");
                            char majorn[109];
                            fflush(stdin);
                            scanf("%s",majorn);
                            int cnt1[1009][109];
                            for(int i=0;i<1009;i++)
                            {
                                for(int j=0;j<109;j++)
                                {
                                    cnt1[i][j]=-1;
                                }
                            }
                            for(int i=0;i<course_tot;i++)
                            {
                                if(!strcmp(majorn,course[i].major))
                                {
                                    flg=1;
                                    int j=0;
                                    while(cnt1[course[i].source][j]!=-1)
                                    {
                                        j++;
                                    }
                                    cnt1[course[i].source][j]=i;
                                }
                            }
                            if(!flg)
                            {
                                printf("Cannot find this major...\n");
                                sleep(1);
                                goto ChoiceMenu;
                                break;
                            }
                            printf("The result is:\n");
                            for(int i=0;i<1009;i++)
                            {
                                int j=0;
                                while(cnt1[i][j]!=-1)
                                {
                                    printf("%s\n",course[cnt1[i][j]].name);
                                    j++;
                                }
                            }
                            printf("Finished...\n");
                            sleep(1);
                            goto ChoiceMenu;
                            break;
                        }
                        default:
                            goto AdminMenu;
                    }
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
            if(course_tot==-1)
            {
                FILE *fp=fopen(buffer2,"r");
                fscanf(fp,"%d",&course_tot);
                for(int i=0;i<course_tot;i++)
                {
                    fscanf(fp,"%s%d%s%d%d",course[i].name,&course[i].cap,course[i].major,&course[i].status,&course[i].source);
                }
                fclose(fp);
            }
            FILE *fp=fopen(buffer4,"r");
            fscanf(fp,"%d",&login_stu);
            for(int i=0;i<login_stu;i++)
            {
                fflush(stdin);
                fscanf(fp,"%d%s%d%d%d",&stulog[i].num,stulog[i].passwd,&stulog[i].cou1,&stulog[i].cou2,&stulog[i].cou3);
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
                {
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
                                StuMenu2:
                                printf("***********************STUDENT MENU************************\n");
                                printf("1.View all your courses\n");
                                printf("2.Choose a new course\n");
                                printf("3.Delete a course you have chosen\n");
                                printf("Other:Save and Logout...\n");
                                printf("Please input your choice:");
                                char choice6;
                                fflush(stdin);//此处清空缓冲区，不然scanf归西
                                scanf("%c",&choice6);
                                switch(choice6)
                                {
                                    case '1':
                                        printf("Number\t\t\tCourse1\t\t\tCourse2\t\t\tCourse3\n");
                                        printf("%d\t",acc);
                                        if(stulog[i].cou1!=-1)
                                        {
                                            printf("%s\t\t",course[stulog[i].cou1].name);
                                        }
                                        else
                                        {
                                            printf("NONE\t\t");
                                        }
                                        if(stulog[i].cou2!=-1)
                                        {
                                            printf("%s\t\t",course[stulog[i].cou2].name);
                                        }
                                        else
                                        {
                                            printf("NONE\t\t");
                                        }
                                        if(stulog[i].cou3!=-1)
                                        {
                                            printf("%s\n",course[stulog[i].cou3].name);
                                        }
                                        else
                                        {
                                            printf("NONE\n");
                                        }
                                        printf("Finished...\n");
                                        sleep(1);
                                        goto StuMenu2;
                                        break;
                                    case '2':
                                        printf("***********************COURSE CHOOSING MENU************************\n");
                                        printf("1.Choose your first course\n");
                                        printf("2.Choose your second course\n");
                                        printf("3.Choose your third course\n");
                                        printf("Other:Back to the Student Menu...\n");
                                        printf("Please input your choice:");
                                        char choice7;
                                        fflush(stdin);//此处清空缓冲区，不然scanf归西
                                        scanf("%c",&choice7);
                                        switch(choice7)
                                        {
                                            case '1':
                                                printf("Number\t\tName\n");
                                                for(int j=0;j<course_tot;j++)
                                                {
                                                    if(course[j].status)
                                                    {
                                                        printf("  %d\t\t\t%s\n",j,course[j].name);
                                                    }
                                                }
                                                printf("Please input the course's number which you would like to choose:");
                                                fflush(stdin);
                                                scanf("%d",&stulog[i].cou1);
                                                if(course[stulog[i].cou1].source>0)
                                                {
                                                    printf("The course has been chosen successfully...\n");
                                                    course[stulog[i].cou1].source--;
                                                }
                                                else
                                                {
                                                    printf("There is no quota left.\n");
                                                    printf("The course choosing failed...\n");
                                                    stulog[i].cou1=-1;
                                                }
                                                sleep(1);
                                                goto StuMenu2;
                                                break;
                                            case '2':
                                                printf("Number\t\tName\n");
                                                for(int j=0;j<course_tot;j++)
                                                {
                                                    if(course[j].status)
                                                    {
                                                        printf("  %d\t\t\t%s\n",j,course[j].name);
                                                    }
                                                }
                                                printf("Please input the course's number which you would like to choose:");
                                                fflush(stdin);
                                                scanf("%d",&stulog[i].cou2);
                                                if(course[stulog[i].cou2].source>0)
                                                {
                                                    printf("The course has been chosen successfully...\n");
                                                    course[stulog[i].cou2].source--;
                                                }
                                                else
                                                {
                                                    printf("There is no quota left.\n");
                                                    printf("The course choosing failed...\n");
                                                    stulog[i].cou2=-1;
                                                }
                                                sleep(1);
                                                goto StuMenu2;
                                                break;
                                            case '3':
                                                printf("Number\t\tName\n");
                                                for(int j=0;j<course_tot;j++)
                                                {
                                                    if(course[j].status)
                                                    {
                                                        printf("  %d\t\t\t%s\n",j,course[j].name);
                                                    }
                                                }
                                                printf("Please input the course's number which you would like to choose:");
                                                fflush(stdin);
                                                scanf("%d",&stulog[i].cou3);
                                                if(course[stulog[i].cou3].source>0)
                                                {
                                                    printf("The course has been chosen successfully...\n");
                                                    course[stulog[i].cou3].source--;
                                                }
                                                else
                                                {
                                                    printf("There is no quota left.\n");
                                                    printf("The course choosing failed...\n");
                                                    stulog[i].cou3=-1;
                                                }
                                                sleep(1);
                                                goto StuMenu2;
                                                break;
                                            default:
                                                printf("Back to Student Menu...\n");
                                                sleep(1);
                                                goto StuMenu2;
                                        }
                                        break;
                                    case '3':
                                        printf("***********************COURSE DELETING MENU************************\n");
                                        printf("1.Delete your first course\n");
                                        printf("2.Delete your second course\n");
                                        printf("3.Delete your third course\n");
                                        printf("Other:Back to the Student Menu...\n");
                                        printf("Please input your choice:");
                                        char choice8;
                                        fflush(stdin);//此处清空缓冲区，不然scanf归西
                                        scanf("%c",&choice8);
                                        switch(choice8)
                                        {
                                            case '1':
                                                stulog[i].cou1=-1;
                                                course[stulog[i].cou1].source++;
                                                printf("The course has been deleted successfully...\n");
                                                sleep(1);
                                                goto StuMenu2;
                                                break;
                                            case '2':
                                                stulog[i].cou2=-1;
                                                course[stulog[i].cou2].source++;
                                                printf("The course has been deleted successfully...\n");
                                                sleep(1);
                                                goto StuMenu2;
                                                break;
                                            case '3':
                                                stulog[i].cou3=-1;
                                                course[stulog[i].cou3].source++;
                                                printf("The course has been deleted successfully...\n");
                                                sleep(1);
                                                goto StuMenu2;
                                                break;
                                            default:
                                                printf("Back to Student Menu...\n");
                                                sleep(1);
                                                goto StuMenu2;
                                        }
                                        break;
                                    default:
                                        FILE *fp=fopen(buffer2,"w");
                                        fprintf(fp,"%d\n",course_tot);
                                        for(int i=0;i<course_tot;i++)
                                        {
                                            fprintf(fp,"%s %d %s %d %d\n",course[i].name,course[i].cap,course[i].major,course[i].status,course[i].source);
                                        }
                                        course_tot=-1;
                                        fclose(fp);
                                        FILE *fp1=fopen(buffer4,"w");
                                        fprintf(fp1,"%d\n",login_stu);
                                        for(int i=0;i<login_stu;i++)
                                        {
                                            fprintf(fp1,"%d %s %d %d %d\n",stulog[i].num,stulog[i].passwd,stulog[i].cou1,stulog[i].cou2,stulog[i].cou3);
                                        }
                                        fclose(fp1);
                                        login_stu=-1;
                                        sleep(1);
                                        goto StuLogMenu;
                                }
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
                }
                case '2':
                {
                    printf("Please input your student number:");
                    fflush(stdin);
                    scanf("%d",&stulog[login_stu].num);
                    printf("Please input your password:");
                    fflush(stdin);
                    scanf("%s",stulog[login_stu].passwd);
                    stulog[login_stu].cou1=-1;
                    stulog[login_stu].cou2=-1;
                    stulog[login_stu].cou3=-1;
                    login_stu++;
                    FILE *fp=fopen(buffer4,"w");
                    fprintf(fp,"%d\n",login_stu);
                    for(int i=0;i<login_stu;i++)
                    {
                        fprintf(fp,"%d %s %d %d %d\n",stulog[i].num,stulog[i].passwd,stulog[i].cou1,stulog[i].cou2,stulog[i].cou3);
                    }
                    fclose(fp);
                    printf("Sign up finished...\n");
                    sleep(1);
                    goto StuLogMenu;
                }
                default:
                    goto login;
            }
            }
            break;
        default:
            printf("The program will exit...\n");
            return 0;
    }
    return 0;
}
