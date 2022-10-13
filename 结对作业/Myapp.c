#include<stdio.h>
#include<stdlib.h>

int fnum; //生成题目数量 
int limit=10;
int length=20;//式子长度 
char z_shizi[100];//题目暂存 
char c_shizi[10000][100];//最终题目储存位置 

void WriteFile();//写入文件函数 
void ReadFile();

/*数据写入文件*/
void WriteFile(){
	int i,k;	
	FILE *p=fopen("Exercises.txt","w");	
	if(p==NULL){		
		printf("ERROR!");
		return;		
	}
	for(i=0;i<fnum;i++){		
		fwrite(&c_shizi[i],sizeof(c_shizi[i]),1,p);
	}		
	 fclose(p);	
}

void ReadFile(){
	FILE *p=fopen("Exercises.txt","r");
	if(p==NULL){		
		printf("ERROR!");
		return;		
	}
	 fclose(p);
}



int main(int argc,char *argv[]){
	int num=0;
	limit=0;
	int i,j=length-1,k;
	char snum[5],slimit[5];
	ReadFile();
	srand(time(0));
	//不是按要求输入命令行参数的报错退出 
	if(argc!=3){
		printf("请输入 题目数量+数值范围 ！");
		return 0;
	}
	//将命令行参数转化为整型变量 
	for(i=0;i<5;i++){
		snum[i]=argv[1][i];	
	}
	snum[i]='\0';
	for(i=0;i<5;i++){		
		slimit[i]=argv[2][i];
	}
	slimit[i]='\0';	
	for(i=0;snum[i]!='\0';i++){
		num=num*10+(snum[i]-'0');
	}
	for(i=0;slimit[i]!='\0';i++){
		limit=limit*10+(slimit[i]-'0');
	}
	
	fnum=num;//num用于计生成题目的数量，会减小，fnum为固定值 
	
	int si,sj; 
	int max_s;//运算符号最多3个 
	char snumber[20]; //整型变量转化为字符串的存储位置 
	int selet;//随机生成的选择项 
	int number;//随机生成的数字 
	int l_bk;//前括号的个数，在形成后括号的时候，需要判别前面是否有前括号 
	
	int flag=0; 
	/*
	flag用于判定正在生成的题目当前位置的前一个符号是什么 
	0.前一个符号为空，则后一个只能是数字或者前括号 
	1.前一个符号是运算符，则 后一个只能是数字或者前括号 
	2.前一个符号是后括号，则后一个只能是运算符号 
	3.前一个符号是数字，则后一个只能是运算符号或者后括号 
	4.前一个符号是前括号，则后一个只能是数字 
	*/ 
	
	/*
	完成该作业代码部分的过程 
	1.随机数生成 
	srand(time(0));
	int number=rand()%11;
	printf("%d",number);
	
	2.将整型变量转化为字符串 
	int n=123455;
    int i=0,j=0;
    char c[10],cc[10];
    while(n){
    	c[i++]=n%10+'0';
    	n/=10;
	}
	c[i]='\0';
	i--;
	while(i>=0)cc[j++]=c[i--];
	cc[j]='\0';	
	字符串cc为最终的结果 
	
	3.问题：前后括号数量不对应
	解决：  
	while(l_bk!=0){
		z_shizi[i++]=')';
		l_bk--;
	} 
	当l_bk不为0，即前括号比后括号多的时候，后面补上多出来的部分 
	
	4.问题：直接补括号可能导致式子后半部分错乱
	解决：补括号前，先从后往前删除非数字元素
	while(!((z_shizi[i-1]>'0'&&z_shizi[i-1]<='9')||z_shizi[i-1]==')')||z_shizi[i-2]=='('){			
		if(z_shizi[i-1]=='(')l_bk--;
		i--;
		if(i<=1)break;
	}
	当最后一个符号使数字而且倒数第二个不是前括号时，就可以开始补后括号 
	
	5.问题：在前一个问题解决方案中，仅仅只是将z_shizi开始补括号的位置提前，并未删除掉之前错乱的部分
	解决：改变输出方式，将i变为z_shizi的正确部分长度
	for(k=0;k<i;k++){
		printf("%c",z_shizi[k]);
	}
	
	到目前为止已经能稳定生成正确的式子，接下来就为符合题目要求进行改动 
	
	要求1.生成的题目中计算过程不能产生负数，也就是说算术表达式中如果存在形如e1- e2的子表达式，那么e1≥ e2
	在生成数字前判断前面是否为减号，若为减号，则减数改为比被减数小的数 
	if(z_shizi[i-1]=='-'&&z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'){
		number=z_shizi[i-2]-'0'-1;
	} else{
		number=rand()%(limit-1)+1;
	}
	此方法只是把减号前后两个数字变成符合要求的情况，所以还需要改善 
	能力有限，如果前后不都只是数字的话，将减号改为加号
	
	要求2.每道题目中出现的运算符个数不超过3个。
	加入变量max_s随机个数1~3
	每增加一个运算符号时，该变量减一
	当添加运算符号之后，max_s小于0时 ，则完成生成式子并且将该运算符号删除
	
	*/
	do{
		/*
		这里开始生成题目 
		*/ 
		l_bk=0;//前括号初始为0
		max_s=rand()%3+1;//运算符号最多个数随机1~3个 
		j=length-1;
		flag=0;
		for(k=0;k<100;k++)
			z_shizi[i]=' ';
		for(i=0;i<length;i++){			 	
		 	//前一个符号为空,则后一个只能是数字或者前括号
			if(flag==0){
				selet=rand()%2;
				if(selet==0){//该位置为数字 					
					if(z_shizi[i-1]=='-'&&z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'){
						number=z_shizi[i-2]-'0'-1;
					} else{
						number=rand()%(limit-1)+1;
					}					
					si=0;
					while(number){
						snumber[si++]=number%10+'0';
						number/=10;	
					}
					snumber[si]='\0';
					si--;
					while(si>=0)z_shizi[i++]=snumber[si--];
					i--;
					flag=3; 
					
				}else{//该位置为前括号 
					z_shizi[i]='(';
					l_bk++;
					flag=4;
				} 
				
			}else 
			//前一个符号是运算符，则 后一个只能是数字或者前括号  
			if(flag==1){
				selet=rand()%2;
				if(z_shizi[i-1]=='-'||z_shizi[i-1]=='/')selet=0;
				if(selet==0){
					//该位置为数字 
					/*
					若前面为减号，则减数变为比被减数小的数 
					若前面为除号，则除数变为比被除数大的数 
					*/ 
					if(z_shizi[i-1]=='-'&&z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'){
						number=z_shizi[i-2]-'0'-1;						
					} else{
						number=rand()%(limit-1)+1;
					}
					if(z_shizi[i-1]=='/'&&z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'){
						number=z_shizi[i-2]-'0'+2;						
					} else if(z_shizi[i-1]!='-'){
						number=rand()%(limit-1)+1;
					}
					si=0;
					if(number==0)z_shizi[i++]='0';
					while(number){
						snumber[si++]=number%10+'0';
						number/=10;	
					}
					snumber[si]='\0';
					si--;
					while(si>=0)z_shizi[i++]=snumber[si--];
					i--;
					flag=3; 
				} else{//该位置为前括号 
					z_shizi[i]='(';
					l_bk++;
					flag=4;				
				}
							
			}else 
			//前一个符号是后括号，则后一个只能是运算符号
			if(flag==2){
				//该位置为运算符号 
				/*
				为了符合要求，当前面为式子而不是数字时，难以判断前后大小，不妨就该位置设定为只能加号或者除号 
				*/
				selet=rand()%2;
				if(selet==0){
					z_shizi[i]='+';
					max_s--; 
				} else if(selet==1){
					z_shizi[i]='*';
					max_s--; 
				}
				flag=1;			
			}else 
			//前一个符号是数字，则后一个只能是运算符号或者后括号
			if(flag==3){
				selet=0;
				if(l_bk>0&&z_shizi[i-2]!='('&&!(z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'))
					selet=rand()%2;
				if(selet==0){
					//该位置为运算符号 
					selet=rand()%4;
					if(selet==0){
						z_shizi[i]='+';
						max_s--; 
					} else if(selet==1){
						if(z_shizi[i-2]=='-'){
							z_shizi[i]='+';
						}else{
							z_shizi[i]='-';
						}												
						max_s--; 
					}else if(selet==2){
						z_shizi[i]='*';
						max_s--; 
					}else{
						z_shizi[i]='/';	
						max_s--; 			
					}
					flag=1;
				}else{					
					//该位置为后括号 
					z_shizi[i]=')';
					flag=2;
					l_bk--;
				} 			
			}else
			//前一个符号是前括号，则后一个只能是数字 
			if(flag==4){
				//该位置为数字 
				if(z_shizi[i-1]=='-'&&z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'){
					number=z_shizi[i-2]-'0'-1;
				} else{
					number=rand()%(limit-1)+1;
				}
				si=0;
				while(number){
					snumber[si++]=number%10+'0';
					number/=10;	
				}
				snumber[si]='\0';
				si--;
				while(si>=0)z_shizi[i++]=snumber[si--];
				i--;
				flag=3; 
			} 
			//当要加入的运算符号数量小于0时，结束生成式子		
			 if(max_s<0){			 	
			 	break;
			 }			
		}
		/*
		一个长度为length的原始式子生成到此结束，现在的式子还可能出现各种问题
		下面就会采取一些措施使式子正确且符合要求 
		*/
		//删除式子后面不合理的部分 
		while(!((z_shizi[i-1]>'0'&&z_shizi[i-1]<='9')||z_shizi[i-1]==')')||z_shizi[i-2]=='('){			
			if(z_shizi[i-1]=='(')l_bk--;
			i--;
			if(i<=1)break;
		}
			
		//补括号操作 
		while(l_bk>0){
			z_shizi[i]=')';
			l_bk--;
			i++;
		} 
		
		/*
		到这里式子已经是符合常理了 
		*/
	
		//将式子一一列举出来 
		for(k=0;k<i;k++){
			if(z_shizi[k]=='+'||z_shizi[k]=='-'||z_shizi[k]=='*'||z_shizi[k]=='/'){
				num--;
				printf("%d:\t",num+1);
				for(k=0;k<i;k++){
					c_shizi[num][k]=z_shizi[k]; 
					printf("%c",c_shizi[num][k]);
				}
				for(k=i;k<length;k++){
					c_shizi[num][k]=' ';
				}
				printf("\n");
				break;
			}
		} 

		
	} while(num>0);
	
	WriteFile();//将生成的式子写入文件 

	return 0;
}



