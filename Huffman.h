#include<stdio.h>
#define MAX 92
#define MAXSIZE 100000
typedef struct{			// ����Huffman�����ṹ
    char data;         		// ���ֵ
    int weight;        		// Ȩ��
    int parent;        		// �����
    int lchild;      		// ����
    int rchild;      		// �Һ���
}HTNode;
typedef struct {     		// ����Huffman����ṹ
    char cd[MAX]; 
    int start; 
}HCode;
void CreatHT(HTNode *HT, int n); //����Huffman�� 
void CreatHCode(HTNode *HT, HCode *hcd, int n); //����Huffman����
void PrintHCode(HTNode *HT, HCode *hcd, int n); //��ӡHuffman����
void CharFrequency(char ch[],char str[],int num[],int &count); //�ļ�����ͳ�ƴ�Ƶ 
void sort(char str[],int num[],int len); //��ASCII������
void encode(HTNode *HT,HCode *hcd,char fstr[],int n,char instr[]); //����
void decode(HTNode *HT,int n,char instr[]); //ת�� 



