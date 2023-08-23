#include"Huffman.h"
#include<iostream>
#include<string.h>
using namespace std;
void CreatHT(HTNode *HT, int n){
	int i,k,l,r;
		int m1, m2;					// m1ȡ��СȨ�أ�m2ȡ��СȨ��
	    for(i=1;i<2*n; i++) 
	        HT[i].parent=HT[i].lchild=HT[i].rchild = 0;	// ��ʼ��
	    for(i=n+1; i<2*n; i++){    		// ����Huffman��
	        m1=m2 =32767;			//m1��m2��ʼ��Ϊһ���ֵ(Ȩ�ز�����ȡ��) 
	    	int lnode=0,rnode=0;     		// lnode, rnode�ֱ�ȡ������СȨ�صĽ��λ��
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
			HT[lnode].parent=i;  //lnode��rnode��˫�׽�㸳ֵʹ�䲻�ٲ���ѭ�� 
			HT[rnode].parent=i;
			HT[i].weight =m1+m2; //lnode��rnode��Ӧ�ĸ��ڵ㸳ֵ 
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
            if(HT[f].lchild==c)   	//c��f�����ӣ�����ȡ'0'������ȡ'1'
                hc.cd[--hc.start]='0';
            else
                hc.cd[--hc.start]='1';
            c = f;					//�����㷽������,����Ϊ���� 
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
//ͳ�ƴ�Ƶ
	    int loc=0;
	    for(int i=0;i<strlen(ch);i++){
	        if((ch[i]>='a'&&ch[i]<='z')||(ch[i]>='A'&&ch[i]<='Z')||(ch[i]>=' '&&ch[i]<='@')){
	                /***�ַ���str����***/
	                int n=0;
	                for(;n<loc;n++){
	                    if(str[n]==ch[i])break;
	                }   
	                /**���ҵ�i���ַ����Ѵ���str������ַ��Ƿ���ͬ**/
	                /***��ͬ������Ӧƥ��λ�õ�Ȩ�ؼ�һ,��ͬ�������str���飬��ʹ��Ȩ��Ϊ1***/
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
//ð������ 
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
//ƥ�䲢��� 
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
//�Ӹ��ڵ���������ֱ��Ҷ�ӽڵ㣬����ַ����ٴӸ��ڵ㿪ʼ 
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
