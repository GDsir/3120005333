#include<stdio.h>
#include<stdlib.h>

int fnum; //������Ŀ���� 
int limit=10;
int length=20;//ʽ�ӳ��� 
char z_shizi[100];//��Ŀ�ݴ� 
char c_shizi[10000][100];//������Ŀ����λ�� 

void WriteFile();//д���ļ����� 
void ReadFile();

/*����д���ļ�*/
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
	//���ǰ�Ҫ�����������в����ı����˳� 
	if(argc!=3){
		printf("������ ��Ŀ����+��ֵ��Χ ��");
		return 0;
	}
	//�������в���ת��Ϊ���ͱ��� 
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
	
	fnum=num;//num���ڼ�������Ŀ�����������С��fnumΪ�̶�ֵ 
	
	int si,sj; 
	int max_s;//����������3�� 
	char snumber[20]; //���ͱ���ת��Ϊ�ַ����Ĵ洢λ�� 
	int selet;//������ɵ�ѡ���� 
	int number;//������ɵ����� 
	int l_bk;//ǰ���ŵĸ��������γɺ����ŵ�ʱ����Ҫ�б�ǰ���Ƿ���ǰ���� 
	
	int flag=0; 
	/*
	flag�����ж��������ɵ���Ŀ��ǰλ�õ�ǰһ��������ʲô 
	0.ǰһ������Ϊ�գ����һ��ֻ�������ֻ���ǰ���� 
	1.ǰһ����������������� ��һ��ֻ�������ֻ���ǰ���� 
	2.ǰһ�������Ǻ����ţ����һ��ֻ����������� 
	3.ǰһ�����������֣����һ��ֻ����������Ż��ߺ����� 
	4.ǰһ��������ǰ���ţ����һ��ֻ�������� 
	*/ 
	
	/*
	��ɸ���ҵ���벿�ֵĹ��� 
	1.��������� 
	srand(time(0));
	int number=rand()%11;
	printf("%d",number);
	
	2.�����ͱ���ת��Ϊ�ַ��� 
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
	�ַ���ccΪ���յĽ�� 
	
	3.���⣺ǰ��������������Ӧ
	�����  
	while(l_bk!=0){
		z_shizi[i++]=')';
		l_bk--;
	} 
	��l_bk��Ϊ0����ǰ���űȺ����Ŷ��ʱ�򣬺��油�϶�����Ĳ��� 
	
	4.���⣺ֱ�Ӳ����ſ��ܵ���ʽ�Ӻ�벿�ִ���
	�����������ǰ���ȴӺ���ǰɾ��������Ԫ��
	while(!((z_shizi[i-1]>'0'&&z_shizi[i-1]<='9')||z_shizi[i-1]==')')||z_shizi[i-2]=='('){			
		if(z_shizi[i-1]=='(')l_bk--;
		i--;
		if(i<=1)break;
	}
	�����һ������ʹ���ֶ��ҵ����ڶ�������ǰ����ʱ���Ϳ��Կ�ʼ�������� 
	
	5.���⣺��ǰһ�������������У�����ֻ�ǽ�z_shizi��ʼ�����ŵ�λ����ǰ����δɾ����֮ǰ���ҵĲ���
	������ı������ʽ����i��Ϊz_shizi����ȷ���ֳ���
	for(k=0;k<i;k++){
		printf("%c",z_shizi[k]);
	}
	
	��ĿǰΪֹ�Ѿ����ȶ�������ȷ��ʽ�ӣ���������Ϊ������ĿҪ����иĶ� 
	
	Ҫ��1.���ɵ���Ŀ�м�����̲��ܲ���������Ҳ����˵�������ʽ�������������e1- e2���ӱ��ʽ����ôe1�� e2
	����������ǰ�ж�ǰ���Ƿ�Ϊ���ţ���Ϊ���ţ��������Ϊ�ȱ�����С���� 
	if(z_shizi[i-1]=='-'&&z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'){
		number=z_shizi[i-2]-'0'-1;
	} else{
		number=rand()%(limit-1)+1;
	}
	�˷���ֻ�ǰѼ���ǰ���������ֱ�ɷ���Ҫ�����������Ի���Ҫ���� 
	�������ޣ����ǰ�󲻶�ֻ�����ֵĻ��������Ÿ�Ϊ�Ӻ�
	
	Ҫ��2.ÿ����Ŀ�г��ֵ����������������3����
	�������max_s�������1~3
	ÿ����һ���������ʱ���ñ�����һ
	������������֮��max_sС��0ʱ �����������ʽ�Ӳ��ҽ����������ɾ��
	
	*/
	do{
		/*
		���￪ʼ������Ŀ 
		*/ 
		l_bk=0;//ǰ���ų�ʼΪ0
		max_s=rand()%3+1;//����������������1~3�� 
		j=length-1;
		flag=0;
		for(k=0;k<100;k++)
			z_shizi[i]=' ';
		for(i=0;i<length;i++){			 	
		 	//ǰһ������Ϊ��,���һ��ֻ�������ֻ���ǰ����
			if(flag==0){
				selet=rand()%2;
				if(selet==0){//��λ��Ϊ���� 					
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
					
				}else{//��λ��Ϊǰ���� 
					z_shizi[i]='(';
					l_bk++;
					flag=4;
				} 
				
			}else 
			//ǰһ����������������� ��һ��ֻ�������ֻ���ǰ����  
			if(flag==1){
				selet=rand()%2;
				if(z_shizi[i-1]=='-'||z_shizi[i-1]=='/')selet=0;
				if(selet==0){
					//��λ��Ϊ���� 
					/*
					��ǰ��Ϊ���ţ��������Ϊ�ȱ�����С���� 
					��ǰ��Ϊ���ţ��������Ϊ�ȱ���������� 
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
				} else{//��λ��Ϊǰ���� 
					z_shizi[i]='(';
					l_bk++;
					flag=4;				
				}
							
			}else 
			//ǰһ�������Ǻ����ţ����һ��ֻ�����������
			if(flag==2){
				//��λ��Ϊ������� 
				/*
				Ϊ�˷���Ҫ�󣬵�ǰ��Ϊʽ�Ӷ���������ʱ�������ж�ǰ���С�������͸�λ���趨Ϊֻ�ܼӺŻ��߳��� 
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
			//ǰһ�����������֣����һ��ֻ����������Ż��ߺ�����
			if(flag==3){
				selet=0;
				if(l_bk>0&&z_shizi[i-2]!='('&&!(z_shizi[i-2]>'0'&&z_shizi[i-2]<='9'))
					selet=rand()%2;
				if(selet==0){
					//��λ��Ϊ������� 
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
					//��λ��Ϊ������ 
					z_shizi[i]=')';
					flag=2;
					l_bk--;
				} 			
			}else
			//ǰһ��������ǰ���ţ����һ��ֻ�������� 
			if(flag==4){
				//��λ��Ϊ���� 
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
			//��Ҫ����������������С��0ʱ����������ʽ��		
			 if(max_s<0){			 	
			 	break;
			 }			
		}
		/*
		һ������Ϊlength��ԭʼʽ�����ɵ��˽��������ڵ�ʽ�ӻ����ܳ��ָ�������
		����ͻ��ȡһЩ��ʩʹʽ����ȷ�ҷ���Ҫ�� 
		*/
		//ɾ��ʽ�Ӻ��治����Ĳ��� 
		while(!((z_shizi[i-1]>'0'&&z_shizi[i-1]<='9')||z_shizi[i-1]==')')||z_shizi[i-2]=='('){			
			if(z_shizi[i-1]=='(')l_bk--;
			i--;
			if(i<=1)break;
		}
			
		//�����Ų��� 
		while(l_bk>0){
			z_shizi[i]=')';
			l_bk--;
			i++;
		} 
		
		/*
		������ʽ���Ѿ��Ƿ��ϳ����� 
		*/
	
		//��ʽ��һһ�оٳ��� 
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
	
	WriteFile();//�����ɵ�ʽ��д���ļ� 

	return 0;
}



