#include<stdio.h>
#define MAX 92
#define MAXSIZE 100000
typedef struct{			// 定义Huffman树结点结构
    char data;         		// 结点值
    int weight;        		// 权重
    int parent;        		// 父结点
    int lchild;      		// 左孩子
    int rchild;      		// 右孩子
}HTNode;
typedef struct {     		// 定义Huffman编码结构
    char cd[MAX]; 
    int start; 
}HCode;
void CreatHT(HTNode *HT, int n); //构建Huffman树 
void CreatHCode(HTNode *HT, HCode *hcd, int n); //构建Huffman编码
void PrintHCode(HTNode *HT, HCode *hcd, int n); //打印Huffman编码
void CharFrequency(char ch[],char str[],int num[],int &count); //文件输入统计词频 
void sort(char str[],int num[],int len); //按ASCII码排序
void encode(HTNode *HT,HCode *hcd,char fstr[],int n,char instr[]); //译码
void decode(HTNode *HT,int n,char instr[]); //转码 



