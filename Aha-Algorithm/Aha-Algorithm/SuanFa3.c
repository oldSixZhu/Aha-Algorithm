//
//  SuanFa3.c
//  Aha-Algorithm
//
//  Created by Mac on 2017/6/23.
//  Copyright © 2017年 oldSix. All rights reserved.
//

#include <stdio.h>

//割点:在一个无向连通图中,如果删除某个顶点后,图不再连通(任意两点之间不能互相到达),称这样的顶点为割点
//割边:在一个无向连通图中,如果删除某条边后,图不再连通...
//使用邻接表来存储,时间复杂度为O(m+n)
//一个算法要选用合适的数据结构

//二分图最大分配
//二分图:如果一个图的所有顶点可以被分为x和y两个集合,并且所有边的两个顶点恰好一个属于集合x,另一个属于集合y,每个集合内的顶点没有边相连,那么就是二分图
//增加配对数称为增广路
//匈牙利算法 求二分图的最大匹配


//现在有一个序列,其中一个数出现的次数超过了50%,请找出这个数
//投票系统中如果有一个人的票数超过50%,这个人立即当选
//寻找多数元素,主元素问题
//在原序列中去除两个不同的元素后，那么在原序列中的多数元素在新的序列中还是多数元素。
int candidate(int a[], int m, int n)
{
    int j = m, c = a[m], count = 1;
    
    while (j < n && count > 0)
    {
        ++ j;
        if (a[j] == c)
            ++ count;
        else
            -- count;
    }
    
    if (j == n)
        return c;
    else
        return candidate(a, j+1, n);
};
//第一遍扫描完成以后，count不等于1，所以把A[1]舍去
//如果所有的元素都已经扫描完毕并且计数器大于0，那么返回c作为多数元素的候选者
// a[1...n]
int Majority(int a[], int n)
{
    int c = candidate(a, 1, 10);
    int count = 0;
    int majority;
    
    for (int i = 1; i <= n; ++ i)
        if (a[i] == c)
            ++ count;
    
    if (n%2 == 0)
        majority = n/2 + 1;
    else
        majority = n/2;
    if (count > majority)
        return c;
    else
        return -1;
};

void duoYuanSu()
{
    int a[11];
    
    for (int i = 1; i < 11; ++ i)
        scanf("%d",a+i);
    
    printf("%d\n",Majority(a, 10));
    getchar();
    getchar();
}



















