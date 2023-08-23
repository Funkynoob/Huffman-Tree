#include"Huffman.h"
#include<iostream>
#include<string.h>
using namespace std;
void CreatHT(HTNode *HT, int n){
	int i,k,l,r;
		int m1, m2;					// m1取最小权重，m2取次小权重
	    for(i=1;i<2*n; i++) 
	        HT[i].parent=HT[i].lchild=HT[i].rchild = 0;	// 初始化
	    for(i=n+1; i<2*n; i++){    		// 构造Huffman树
	        m1=m2 =32767;			//m1与m2初始化为一最大值(权重不可能取到) 
	    	int lnode=0,rnode=0;     		// lnode, rnode分别取两个最小权重的结点位置
	       	for( k=1; k<i; k++){
				if(HT[k].parent==0){
			   		if(HT[k].weight<m1) {
			   	    	m2 = m1;  
			   			rnode=lnode;
			   			m1 = HT[k].weight;  
			   			lnode=k;
			   		}
			   		else if(HT[k].weight<m2){
			   			m2 =HT[k].weight;
			   			rnode =k;
			   		}
			    }
			}
			HT[lnode].parent=i;  //lnode和rnode的双亲结点赋值使其不再参与循环 
			HT[rnode].parent=i;
			HT[i].weight =m1+m2; //lnode和rnode对应的父节点赋值 
			HT[i].lchild =lnode;
			HT[i].rchild =rnode;
	}
}
void CreatHCode(HTNode *HT, HCode *hcd, int n){
	int i, f, c;
	HCode hc;
    for(i=1; i<=n; i++) 
    {
		hc.start = n;
        c = i;
        f = HT[i].parent;
        while( f!=0 ) {
            if(HT[f].lchild==c)   	//c是f的左孩子，编码取'0'，否则取'1'
                hc.cd[--hc.start]='0';
            else
                hc.cd[--hc.start]='1';
            c = f;					//向根结点方向搜索,编码为倒序 
			f= HT[f].parent;
        }
		hcd[i]=hc;
    }
}
void PrintHCode(HTNode *HT, HCode *hcd, int n){
	int i,k;
		for(i=1;i<=n; i++) 
		{
			printf("%c:",HT[i].data);
			for(k=hcd[i].start;k<n;k++)
				cout<<hcd[i].cd[k];
			printf("\n");
		}
}
void CharFrequency(char ch[],char str[],int num[],int &count){
//统计词频
	    int loc=0;
	    for(int i=0;i<strlen(ch);i++){
	        if((ch[i]>='a'&&ch[i]<='z')||(ch[i]>='A'&&ch[i]<='Z')||(ch[i]>=' '&&ch[i]<='@')){
	                /***字符进str数组***/
	                int n=0;
	                for(;n<loc;n++){
	                    if(str[n]==ch[i])break;
	                }   
	                /**查找第i个字符与已存入str数组的字符是否相同**/
	                /***相同，则相应匹配位置的权重加一,不同，则存入str数组，并使其权重为1***/
	                if(n!=loc)num[n]++; 
	                else{
	                    str[loc]=ch[i];
	                    num[loc]=1;
	                    loc++;
	                    count++;
	                } 
	                /****************/                 
	        }
	    }
}
void sort(char str[],int num[],int len){
//冒泡排序 
	int i,j,temp;
		for(i=0;i<len;i++){
			for(j=0;j<len-1-i;j++)
	        {
				if(str[j]>str[j+1])
	            {
					temp=str[j+1];
					str[j+1]=str[j];
					str[j]=temp;
	                temp=num[j+1];
					num[j+1]=num[j];
					num[j]=temp;
	            }
	        }
	    }
}
void encode(HTNode *HT,HCode *hcd,char fstr[],int n,char instr[]){
//匹配并输出 
	char *p=fstr;
	char *inp=instr;
	char ch[n];
	while(*p!='\0'){
		int i=1;
		if(*p=='\n')*inp++='\n';
		if((*p>='a'&&*p<='z')||(*p>='A'&&*p<='Z')||(*p>=' '&&*p<='@')){
			while(*p!=HT[i].data){
				i++;
			}
			for(int k=hcd[i].start;k<n;k++){
				cout<<hcd[i].cd[k];
				*inp++=hcd[i].cd[k];
			}
		}
		p++;
	}
}
void decode(HTNode *HT,int n,char instr[]){
//从根节点往下搜索直到叶子节点，输出字符，再从根节点开始 
	char ch;
	int loc= 2*n-1;
	char *p= instr;
	while(*p!='\0'){
		if(*p=='\n'){
			cout<<'\n';
		}
		if(HT[loc].lchild!=0&&HT[loc].rchild!=0){
			if(*p=='0')loc=HT[loc].lchild;
			if(*p=='1')loc=HT[loc].rchild;
		}
		if(HT[loc].lchild==0&&HT[loc].rchild==0){
			cout<<HT[loc].data;
			loc=2*n-1;
		}
		p++;
	}
}
