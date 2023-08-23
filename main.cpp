#include"Huffman.h"
#include<iostream>
#include<string.h>
using namespace std;
int main(int argc, char** argv){
	int i,n;
	HTNode HT[2*MAX-1];                //HT数组构建Huffman树 
	HCode hcd[MAX];						//hcd数组储存编码 
	int count=0,loc1=0;					//count计算文件字符数 
	char infname[50],fstr[MAXSIZE],instr[MAXSIZE],ch; //infname数组储存文件名，fstr储存文件内容，													
	FILE *infp;		//instr储存编码二进制序列,ch作为储存getchar得到字符的变量 ，infp指向文件指针									
	char str[91];  //储存字符
	int num[91];   //储存对应字符权重 
	cout<<"**************开始创建Huffman树**************\n";
	cout<<"---------------------------------------------"<<endl;
	cout<<"请选择模式(t/T代表文件输入模式，m/M代表手动输入模式)：";
	ch=getchar();
	if(ch=='M'||ch=='m'){
		cout<<"---------------------------------------------"<<endl;
		cout<<"手动输入模式："<<endl;
		cout<<"---------------------------------------------"<<endl;
		/***确保n值合规***/
		do{	
			printf("请输入元素个数(1-52)：");
			while(scanf("%d",&n)!=1){
				cout<<"错误!请输入整数!\n";
				fflush(stdin);
				printf("请输入元素个数(1-52)：");
			}
		} 
		while(n<1||n>52);
		cout<<"---------------------------------------------"<<endl; 
		/***************/
		/***确保结点值及权值合规***/		
		for(i=1;i<=n;i++){		// Huffman树结点存放在ht数组从1下标开始的位置
		    fflush(stdin);
		    while(1){
		     	printf("第%d个元素的结点值==>", i);
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
							cout<<"错误！输入重复节点值！"<<endl;
							fflush(stdin);
							printf("请重新输入第%d个元素的结点值==>", i);
							ch=getchar();	
						}
					} 
					str[i-1]=ch;
					fflush(stdin);
					break;
				}
				else{
					cout<<"错误!请输入大写或小写英文!\n";
					fflush(stdin);
				} 			 	
			}					
			cout<<"\t权重==>";
			while(scanf("%d",&num[i-1])!=1){
				cout<<"\t错误!请输入整数\n";
				fflush(stdin);
				cout<<"\t权重==>";
			}	
			cout<<"---------------------------------------------"<<endl;
		/***************/		
		    }
		}
		else{
			/***输入文件名***/
			cout<<"---------------------------------------------"<<endl;  
			cout<<"文件输入模式：\n";
			cout<<"---------------------------------------------"<<endl; 
			cout<<"请输入输入文件名:";
			cin>>infname;
			while((infp = fopen(infname,"r")) == NULL){
				fflush(stdin);
			    cout<<"  文件打开错误!\n";
			    cout<<"请输入y/Y以重新输入，n/N以退出:";
			    if(getchar()=='n'){
					cout<<"---------------------------------------------"<<endl;
					cout<<"程序结束..."<<endl;
					cout<<"---------------------------------------------"<<endl;
					exit(1);
				}else{
					cout<<"---------------------------------------------"<<endl;
				}
			    fflush(stdin);
			    cout<<"请重新输入文件名:";
			    cin>>infname;
			}
			/***************/
			cout<<"  文件打开成功!"<<endl;
			cout<<"---------------------------------------------"<<endl;
			/***读入字符给fstr数组***/
			while((ch=fgetc(infp))!=EOF){
				fstr[loc1]=ch;
			    loc1++;
			}
			fclose(infp);
			/***************/
			/***计算词频率及排序***/
			CharFrequency(fstr,str,num,count);
			sort(str,num,count);
			n=count;
		}
			/***************/
			/***并结点值及权重赋给data及weight***/ 
			for(int k=1;k<=n;k++){
				HT[k].data=str[k-1];
				HT[k].weight=num[k-1];
			}
			/***************/
		/***创建树，编码，输出词频，译码，解码***/
		fflush(stdin);
		cout<<"按NETER键以创建Huffman树:";
		getchar();
		CreatHT(HT,n);
		cout<<"   Huffman树创建成功!\n";
		fflush(stdin);
		cout<<"---------------------------------------------"<<endl;
		cout<<"按NETER键以创建Huffman编码:";
		getchar();
		CreatHCode(HT,hcd,n);
		cout<<"   Huffman编码创建成功!\n";
		cout<<"---------------------------------------------"<<endl;  
		cout<<"按ENTR键以输出Huffman编码:";
		getchar();
		cout<<"---------------------------------------------"<<endl;
		PrintHCode(HT, hcd, n);
		cout<<"---------------------------------------------"<<endl; 
		cout<<"**************创建Huffman树结束**************\n";
		cout<<"---------------------------------------------"<<endl; 
		cout<<"是否显示词频率(y/Y代表确定，n/N代表取消):";
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
			cout<<"按ENTER键以译码：";
			getchar(); 
			cout<<"---------------------------------------------"<<endl;
			encode(HT,hcd,fstr,n,instr);
			cout<<"\n---------------------------------------------"<<endl;
			cout<<"按ENTER键以解码：";
			getchar();
			fflush(stdin);
			cout<<"---------------------------------------------"<<endl;
			decode(HT,n,instr);
			cout<<"\n---------------------------------------------"<<endl;	
		}
		/***************/
		cout<<"程序结束..."; 
		return 0;
}
