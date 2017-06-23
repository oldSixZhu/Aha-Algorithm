//
//  PaiXu.c
//  Aha-Algorithm
//
//  Created by Mac on 2017/6/19.
//  Copyright © 2017年 oldSix. All rights reserved.
//

#include "PaiXu.h"

//桶排序
//根据最大值设立桶数,每出现一个数,就在对应编号的桶中放旗子做标记,最后根据旗子数打印桶序数
//时间复杂度为O(m+n),但是浪费空间
void tong(){
    printf("开始桶排序\n");
    int tong[1001],i,j,t,n;
    for (i = 0; i <= 1000; i++)
    {
        tong[i] = 0;
    }
    //输入一个数n,表示接下来有n个数
    printf("输入数据个数\n");
    scanf("%d",&n);
    
    
    //循环读入n个数,并进行桶排序
    printf("输入数据\n");
    for (i = 1; i <= n; i++)
    {
        scanf("%d",&t);
        //计数,对编号为t的桶插一个旗子
        tong[t]++;
    }
    printf("桶排序完成\n");
    //依次判断带编号的桶
    for (i = 1000; i >= 0; i--)
    {
        //出现几次就将桶编号打印几次
        for (j = 1; j <= tong[i]; j++)
        {
            printf("%d\n",i);
        }
    }
}


//冒泡排序
//每次都比较两个相邻的元素,如果它们的顺序错误就把它们交换过来,顺序正确位置不变,继续比较
//时间复杂度是O(n²)
void maoPao(){
    printf("开始冒泡排序\n");
    int a[100],i,j,n;
    printf("输入数据个数\n");
    scanf("%d",&n);
    printf("输入数据\n");
    //循环读入数据
    for (i = 1; i <= n; i++)
    {
        scanf("%d",&a[i]);
    }
    
    
    //开始排序
    for (i = 1; i <= n-1; i++)
    {
        for (j = 1; j <= n-i; j++)
        {
            if (a[j] < a[j+1])
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    
    
    printf("冒泡排序完成\n");
    //输出
    for (i = 1; i <= n; i++)
    {
        printf("%d\n",a[i]);
    }
}

//快速排序
//也是交换排序,每次交换是跳跃式的.
//每次排序的时候设置一个基准点(通常是第一个数),然后从两头开始比较交换,将小于等于基准点的数全部放在基准点的左边,将大于等于基准点的数全部放在基准点的右边
//平均时间复杂度O(nlogn)

//快速排序
int a[101];
//a[0,3,5,1,4,2]
//left 1 right 5
void realKuaiSu(int left,int right){
    int i,j,t,temp;
    if (left > right)
    {
        return;
    }
    //temp为基准数
    temp = a[left];//temp=3
    i = left;      //i=1
    j = right;      //j=5
    //i不等于j,就一直循环
    while (i != j)
    {
        //从右往左找,当条件成立时,执行j--,再判断表达式,直到跳出
        //2>=3 j=5 跳出
        //5>=3 j=4
        //4>=3 j=3
        //1>=3 j=3 跳出
        while (a[j] >= temp && i < j)
        {
            j--;
        }
        //j=5
        //j=3
        
        //从左往右找
        //3<=3 i=2
        //5<=3 i=2 跳出
        //2<=3 i=3
        //1<=3 i=j 跳出
        while (a[i] <= temp && i < j)
        {
            i++;
        }
        //i=2
        //i=3
        
        //当两个哨兵没有相遇,交换两个数在数组中的位置
        if (i < j)
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    //a[0,3,2,1,4,5]  2!=5 循环 此时j=5 i=2 temp=3
    //i=3 j=3 跳出 此时a[0,3,2,1,4,5] temp=3
    
    //将基准数归位
    a[left] = a[i]; //a[1]=1
    a[i] = temp;    //a[3]=3
    //a[0,1,2,3,4,5]
    //然后一直处理左半边的
    realKuaiSu(left, i-1); //1,2
    //处理右边的
    realKuaiSu(i+1, right); //4,5
}
//调用快速排序
void kuaiSu(){
    printf("开始快速排序\n");
    int i,n;
    printf("输入数据个数\n");
    scanf("%d",&n);
    printf("输入数据\n");
    //循环读入数据
    for (i = 1; i <= n; i++)
    {
        scanf("%d",&a[i]);
    }
    
    realKuaiSu(1, n);
    
    printf("快速排序完成\n");
    //输出
    for (i = 1; i <= n; i++)
    {
        printf("%d\n",a[i]);
    }
}







