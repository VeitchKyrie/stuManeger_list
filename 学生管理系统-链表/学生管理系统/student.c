//
//  student.c
//  学生管理系统
//
//  Created by zhufengzhu on 15/9/29.
//  Copyright (c) 2015年 朱凤珠. All rights reserved.
//

#include "student.h"
#include <string.h>
#include <stdlib.h>
NODE *pHead;//头结点
//初始化
void print_menu()
{
    printf("欢迎使用学生管理系统\n");
    printf("请选择操作:\n");
    printf("1、增加学生\n");
    printf("2、删除学生\n");
    printf("3、查找学生\n");
    printf("4、按照分数排序\n");
    printf("5、按照年龄排序\n");
    printf("6、打印全部学生信息\n");
    printf("7、退出\n");
}
void initList()
{
    pHead = malloc(sizeof(NODE));
    if(!pHead){
        printf("链表初始化失败\n");
        return ;
    }

    pHead->pNext = NULL;
}
//删除链表
void deleteList()
{
    NODE *p = pHead;
    while (p) {
        NODE *temp = p;
        p = p->pNext;
        free(temp);
        printf("free\n");
    }
}
void addToList(NODE *pNew)
{
    NODE *pNode = pHead;
    
    while (pNode->pNext) {
        pNode = pNode->pNext;
    }
    pNode->pNext=pNew;
}
void addStudent()
{
    NODE *pNode = (NODE *)malloc(sizeof(NODE));
    if(!pNode){
        printf("节点申请失败，不能添加\n");
        return;
    }
    memset(pNode, 0, sizeof(NODE));
    pNode->pNext = NULL;
    printf("请输入新增学生的名字\n");
    scanf("%s",pNode->name);
    printf("请输入新增学生的成绩\n");
    scanf("%d",&(pNode->score));
    printf("请输入新增学生的年龄\n");
    scanf("%d",&(pNode->age));
    addToList(pNode);
    
}
void printStudents()
{
    NODE *pNode = pHead->pNext;

    if(!pNode){
        printf("无学生信息！\n");
    }
    while (pNode) {
        printf("姓名:%s,",pNode->name);
        printf("年龄:%d,",pNode->age);
        printf("分数:%d\n",pNode->score);
        pNode = pNode->pNext;
    }
}

void sort(int choice)
{
    NODE *pNode = pHead->pNext;
    NODE *pPreNode;
    //插入排序 node节点插入到前面
    while (pNode->pNext) {
        pPreNode = pNode;
        pNode = pNode->pNext;//当前待插入节点
        
        NODE *plist = pHead;
        while (plist) {
            //找到插入的位置
            if((choice==SORT_AGE
               && plist->pNext->age > pNode->age)
               ||(choice==SORT_SCORE
               &&plist->pNext->score > pNode->score))
            {
                pPreNode->pNext = pPreNode->pNext->pNext;
                pNode->pNext = plist->pNext;
                plist->pNext = pNode;
                
                break;
            }
            
            if(plist->pNext == pNode){
                break;
            }
            plist = plist->pNext;
        }
        
    }
}

//返回上一个节点
NODE* searchStudentByName(char name[]){
    NODE *pNode = pHead;
    while (pNode->pNext) {
        if(!strcmp(pNode->pNext->name,name)){
            return pNode;
        }
        pNode = pNode->pNext;
    }
    return NULL;
}//根据名字查询学生
void searchStudent()
{
    char name[30] = {};
    printf("请输入要查询的学生姓名\n");
    scanf("%s",name);
    
    NODE * pParent = searchStudentByName(name);
    if(pParent == NULL){
        printf("没有找到该学生信息\n");
    }
    else{
        NODE *pNode = pParent->pNext;
        printf("您要查询的学生信息是 姓名:%s,成绩:%d,年龄:%d\n",
               pNode->name,
               pNode->score,
               pNode->age);
    }
    return;
}

void deletStudent()
{
    char name[30]={};
    
    printf("请输入您要删除的学生姓名\n");
    scanf("%s",name);
    NODE *pNode = searchStudentByName(name);
    if(pNode == NULL){
        printf("您要删除的学生不存在\n");
    }
    else{
        NODE *temp = pNode->pNext;
        pNode->pNext = pNode->pNext->pNext;
        free(temp);
    }
}
void action(int choice)
{
    switch (choice) {
        case ADD:
            addStudent();
            break;
        case DEL:
            deletStudent();
            break;
        case SER:
            searchStudent();
            break;
        case SORT_SCORE:
            sort(SORT_SCORE);
            break;
        case SORT_AGE:
            sort(SORT_AGE);
            break;
        case PRINT:
            printStudents();
            break;
        default:
            printf("选项错误\n");
            break;
    }
}
