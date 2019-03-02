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

typedef char **HuffmanCode; //��̬��������洢Huffmanc�����  



void select(HuffmanTree &HT, int n, int &s1, int &s2)//HT:����������HC:���������룬w:������������ڵ��Ȩֵ��n:������������ڵ�ĸ���
{
	int i;
	s1 = s2 = 0;
	int min1 = INT_MAX;//��Сֵ��INT_MAX��<limits.h>�ж����
	int min2 = INT_MAX;//��Сֵ

	for (i = 1; i <= n; ++i)
	{
		if (HT[i].parent == 0)//ɸѡû�и��ڵ����С�ʹ�СȨֵ�±�
		{
			if (HT[i].weight < min1)//�������СֵС
			{
				min2 = min1;
				s2 = s1;
				min1 = HT[i].weight;
				s1 = i;
			}
			else if ((HT[i].weight >= min1) && (HT[i].weight < min2))//������ڵ�����Сֵ����С�ڴ�Сֵ
			{
				min2 = HT[i].weight;
				s2 = i;
			}
			else//������ڴ�Сֵ����ʲô������
			{
				;
			}
		}
	}
}








void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n) // w���n���ַ���Ȩֵ(��>0),����շ�����HT,�����n���ַ��ĺշ�������HC
{

	int m, i, s1, s2, start;
	int c, f;
	HuffmanTree p;
	char *cd;

	if (n <= 1)  return;
	//��������Ƿ���Թ�����
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)     //��ʼ��Ҷ�ӽ�����
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	for (; i <= m; ++i, ++p)   //��ʼ����Ҷ�ӽ�����
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	for (i = n + 1; i <= m; ++i)// ���շ�����
	{
		// ��HT[1~i-1]��ѡ��parentΪ��weight��С���������,����ŷֱ�Ϊs1��s2
		select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;  //����s1��s2��parentsֵ
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	HC = (HuffmanCode)malloc((m + 1) * sizeof(char *));	 // ��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
	cd = new  char[n];
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)// ����ַ���շ�������
	{
		start = n - 1; // ���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)// ��Ҷ�ӵ������������
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char *)malloc((n - start) * sizeof(char)); // Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);
	}
	free(cd); // �ͷ�cd�ռ�

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
	poststr[0] = '\0';  //ÿ�ν������
	posts = (char *)malloc(10 * sizeof(char));
	printf("�ַ�Ϊ:");
	while (str[i])
	{
		if (find(str[i], pos)) {
			posts = HC[pos + 1];
			strcat(poststr, posts);
		}
		else
		{
			// printf("���빤��ʧ��!\n") ;
			break;
		}
		i++;
	}
	printf("\n����Ϊ:");
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