#include"Huffman.h"
#include<iostream>
#include<string.h>
using namespace std;
int main(int argc, char** argv){
	int i,n;
	HTNode HT[2*MAX-1];                //HT���鹹��Huffman�� 
	HCode hcd[MAX];						//hcd���鴢����� 
	int count=0,loc1=0;					//count�����ļ��ַ��� 
	char infname[50],fstr[MAXSIZE],instr[MAXSIZE],ch; //infname���鴢���ļ�����fstr�����ļ����ݣ�													
	FILE *infp;		//instr����������������,ch��Ϊ����getchar�õ��ַ��ı��� ��infpָ���ļ�ָ��									
	char str[91];  //�����ַ�
	int num[91];   //�����Ӧ�ַ�Ȩ�� 
	cout<<"**************��ʼ����Huffman��**************\n";
	cout<<"---------------------------------------------"<<endl;
	cout<<"��ѡ��ģʽ(t/T�����ļ�����ģʽ��m/M�����ֶ�����ģʽ)��";
	ch=getchar();
	if(ch=='M'||ch=='m'){
		cout<<"---------------------------------------------"<<endl;
		cout<<"�ֶ�����ģʽ��"<<endl;
		cout<<"---------------------------------------------"<<endl;
		/***ȷ��nֵ�Ϲ�***/
		do{	
			printf("������Ԫ�ظ���(1-52)��");
			while(scanf("%d",&n)!=1){
				cout<<"����!����������!\n";
				fflush(stdin);
				printf("������Ԫ�ظ���(1-52)��");
			}
		} 
		while(n<1||n>52);
		cout<<"---------------------------------------------"<<endl; 
		/***************/
		/***ȷ�����ֵ��Ȩֵ�Ϲ�***/		
		for(i=1;i<=n;i++){		// Huffman���������ht�����1�±꿪ʼ��λ��
		    fflush(stdin);
		    while(1){
		     	printf("��%d��Ԫ�صĽ��ֵ==>", i);
				ch=getchar();
				if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
					if(i==1){
						str[0]=ch;
						fflush(stdin);
						break;
					} 
					while(1){
						int j=0;
						for(;j<strlen(str);j++){
							if(ch==str[j])break;
						}
						if(j==strlen(str))break;
						else {
							cout<<"���������ظ��ڵ�ֵ��"<<endl;
							fflush(stdin);
							printf("�����������%d��Ԫ�صĽ��ֵ==>", i);
							ch=getchar();	
						}
					} 
					str[i-1]=ch;
					fflush(stdin);
					break;
				}
				else{
					cout<<"����!�������д��СдӢ��!\n";
					fflush(stdin);
				} 			 	
			}					
			cout<<"\tȨ��==>";
			while(scanf("%d",&num[i-1])!=1){
				cout<<"\t����!����������\n";
				fflush(stdin);
				cout<<"\tȨ��==>";
			}	
			cout<<"---------------------------------------------"<<endl;
		/***************/		
		    }
		}
		else{
			/***�����ļ���***/
			cout<<"---------------------------------------------"<<endl;  
			cout<<"�ļ�����ģʽ��\n";
			cout<<"---------------------------------------------"<<endl; 
			cout<<"�����������ļ���:";
			cin>>infname;
			while((infp = fopen(infname,"r")) == NULL){
				fflush(stdin);
			    cout<<"  �ļ��򿪴���!\n";
			    cout<<"������y/Y���������룬n/N���˳�:";
			    if(getchar()=='n'){
					cout<<"---------------------------------------------"<<endl;
					cout<<"�������..."<<endl;
					cout<<"---------------------------------------------"<<endl;
					exit(1);
				}else{
					cout<<"---------------------------------------------"<<endl;
				}
			    fflush(stdin);
			    cout<<"�����������ļ���:";
			    cin>>infname;
			}
			/***************/
			cout<<"  �ļ��򿪳ɹ�!"<<endl;
			cout<<"---------------------------------------------"<<endl;
			/***�����ַ���fstr����***/
			while((ch=fgetc(infp))!=EOF){
				fstr[loc1]=ch;
			    loc1++;
			}
			fclose(infp);
			/***************/
			/***�����Ƶ�ʼ�����***/
			CharFrequency(fstr,str,num,count);
			sort(str,num,count);
			n=count;
		}
			/***************/
			/***�����ֵ��Ȩ�ظ���data��weight***/ 
			for(int k=1;k<=n;k++){
				HT[k].data=str[k-1];
				HT[k].weight=num[k-1];
			}
			/***************/
		/***�����������룬�����Ƶ�����룬����***/
		fflush(stdin);
		cout<<"��NETER���Դ���Huffman��:";
		getchar();
		CreatHT(HT,n);
		cout<<"   Huffman�������ɹ�!\n";
		fflush(stdin);
		cout<<"---------------------------------------------"<<endl;
		cout<<"��NETER���Դ���Huffman����:";
		getchar();
		CreatHCode(HT,hcd,n);
		cout<<"   Huffman���봴���ɹ�!\n";
		cout<<"---------------------------------------------"<<endl;  
		cout<<"��ENTR�������Huffman����:";
		getchar();
		cout<<"---------------------------------------------"<<endl;
		PrintHCode(HT, hcd, n);
		cout<<"---------------------------------------------"<<endl; 
		cout<<"**************����Huffman������**************\n";
		cout<<"---------------------------------------------"<<endl; 
		cout<<"�Ƿ���ʾ��Ƶ��(y/Y����ȷ����n/N����ȡ��):";
		ch=getchar();
		if(ch=='y'||ch=='y'){
			cout<<"---------------------------------------------"<<endl;
			for(int j=1;j<=n;j++){
				cout<<HT[j].data<<":"<<HT[j].weight<<"\t";
				if(j%5==0)cout<<endl;
			}
			fflush(stdin);
			cout<<"---------------------------------------------"<<endl;
		}
		else{
			cout<<" ---------------------------------------------"<<endl;
		}
		fflush(stdin);
		if(*infname!='\0'){
			cout<<"��ENTER�������룺";
			getchar(); 
			cout<<"---------------------------------------------"<<endl;
			encode(HT,hcd,fstr,n,instr);
			cout<<"\n---------------------------------------------"<<endl;
			cout<<"��ENTER���Խ��룺";
			getchar();
			fflush(stdin);
			cout<<"---------------------------------------------"<<endl;
			decode(HT,n,instr);
			cout<<"\n---------------------------------------------"<<endl;	
		}
		/***************/
		cout<<"�������..."; 
		return 0;
}
