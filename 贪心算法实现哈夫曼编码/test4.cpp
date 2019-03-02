#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
#define N 6
#pragma warning(disable:4996)
typedef struct
{
	int weight;
	int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode; //动态分配数组存储Huffmanc编码表  



void select(HuffmanTree &HT, int n, int &s1, int &s2)//HT:哈夫曼树，HC:哈夫曼编码，w:构造哈夫曼树节点的权值，n:构造哈夫曼树节点的个数
{
	int i;
	s1 = s2 = 0;
	int min1 = INT_MAX;//最小值，INT_MAX在<limits.h>中定义的
	int min2 = INT_MAX;//次小值

	for (i = 1; i <= n; ++i)
	{
		if (HT[i].parent == 0)//筛选没有父节点的最小和次小权值下标
		{
			if (HT[i].weight < min1)//如果比最小值小
			{
				min2 = min1;
				s2 = s1;
				min1 = HT[i].weight;
				s1 = i;
			}
			else if ((HT[i].weight >= min1) && (HT[i].weight < min2))//如果大于等于最小值，且小于次小值
			{
				min2 = HT[i].weight;
				s2 = i;
			}
			else//如果大于次小值，则什么都不做
			{
				;
			}
		}
	}
}








void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n) // w存放n个字符的权值(均>0),构造赫夫曼树HT,并求出n个字符的赫夫曼编码HC
{

	int m, i, s1, s2, start;
	int c, f;
	HuffmanTree p;
	char *cd;

	if (n <= 1)  return;
	//检测结点数是否可以构成树
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)     //初始化叶子结点操作
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	for (; i <= m; ++i, ++p)   //初始化非叶子结点操作
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	for (i = n + 1; i <= m; ++i)// 建赫夫曼树
	{
		// 在HT[1~i-1]中选择parent为且weight最小的两个结点,其序号分别为s1和s2
		select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;  //设置s1和s2的parents值
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	HC = (HuffmanCode)malloc((m + 1) * sizeof(char *));	 // 从叶子到根逆向求每个字符的赫夫曼编码
	cd = new  char[n];
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)// 逐个字符求赫夫曼编码
	{
		start = n - 1; // 编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)// 从叶子到根逆向求编码
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char *)malloc((n - start) * sizeof(char)); // 为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);
	}
	free(cd); // 释放cd空间

}// HuffmanCoding


bool find(char &a, int &pos)
{

	if (a == 'a') {
		pos = 0;
		printf("a");
		return true;
	}
	else if (a == 'b') {
		pos = 1;
		printf("b");
		return true;
	}
	else if (a == 'c')
	{
		pos = 2;
		printf("c");
		return true;
	}
	else  if (a == 'd')
	{
		pos = 3;
		printf("d");
		return true;
	}
	else if (a == 'e')
	{
		pos = 4;
		printf("e");
		return true;
	}
	else
	{
		return false;
	}

}
void Encoding(char *str, char *poststr, HuffmanCode &HC)
{
	int i = 0;
	int pos = 0;
	char *posts;
	poststr[0] = '\0';  //每次进来清空
	posts = (char *)malloc(10 * sizeof(char));
	printf("字符为:");
	while (str[i])
	{
		if (find(str[i], pos)) {
			posts = HC[pos + 1];
			strcat(poststr, posts);
		}
		else
		{
			// printf("编码工作失败!\n") ;
			break;
		}
		i++;
	}
	printf("\n编码为:");
	printf("%s\n", poststr);
}


int main()
{








	int i;
	char key[N] = { '0','a','b','c','d','e' };
	int w[N] = { 2,8,6,4,10 };
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, w, N - 1);
	for (i = 1; i < N; i++)
		printf("%c:%s\n", key[i], HC[i]);
	printf("\n");
	char str[5] = { 'a','b','c','d','e' };
	char poststr[15];
	Encoding(str, poststr, HC);
	_sleep(60000);

	system("pause");

}