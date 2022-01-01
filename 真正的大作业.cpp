#include <stdio.h>
#include<io.h>
#include<string.h>//strlen 
int count=0,counthang = 0,countwhile = 0, countfor = 0 ,countif = 0;//初始化行数，while for if语句数，
int pjdmhs,sumwenjian;//记录总代码数，总行数，总if，while，for语句数,平均代码行数,总文件数；
char filename[100];//文件名

FILE * fpp = fopen("Bosshomework.txt","w");//保存到的文本文件 

int judgehang(char *ch,int t,int k,int counthang)//判断行数的函数 
{
	for(int j = 0;j < t - 1;j++)
						{
							if(ch[j] == ' ' || ch[0] == 0) 
							{
								k = 1;
							} 
							else
							{
								k = 0;
								break;
							}
						}
						if(k == 0)
						{
							counthang++;
						}
						return counthang;
}

int judgeif(char *ch,int t,int countif)//判断if数量的函数 
{
	for(int j = 0;j < t - 1;j++)
						{
							if(ch[j] == ' '|| j==0)
							{
								if(ch[j + 1] == 'i' && ch[j + 2] == 'f' && (ch[j + 3] == '(' || ch[j + 3] == ' '))
								{
									countif++;
								}
							}
						}
						return countif;
}

int judgewhile(char *ch,int t,int countwhile)//判断while数量的函数 
{
	for(int j = 0;j < t - 1;j++) 
						{
							if(ch[j] == ' ' || j==0)
							{
								if(ch[j + 1] == 'w' && ch[j + 2] == 'h' && ch[j + 3] == 'i' && ch[j + 4] == 'l' && ch[j + 5] == 'e' && (ch[j + 6] == '(' || ch[j + 6] == ' '))
								{
									countwhile++;
								}
							}
						}
						return countwhile;
}

int judgefor(char *ch,int t,int countfor)//判断for数量的函数 
{
	for(int j = 0;j < t - 1;j++)
						{
							if(ch[j] == ' ' || j==0)
							{
								if(ch[j + 1] == 'f' && ch[j + 2] == 'o' && ch[j + 3] == 'r' && (ch[j + 4] == '(' || ch[j + 4] == ' '))
								{
									countfor++;
								}
							}
						}
						return countfor;
}

int Bianliwenjian(char *a,char *b)//文件夹遍历函数
{
	int ok = 0;//是否完成一次遍历的标志 
	int cok = 0;//判断是否遍历完.c的文件的标志 
	char savepath[100];//保存路径 
	strcpy(savepath, a);
	char c[100];//暂时保存路径 
	strcpy(c, a);
	strcat(a, b);//遍历文件的条件 
	struct _finddata_t file;//本目录的结构体 
	struct _finddata_t file1;//暂时的本目录的结构体 
	long fHandle; //暂时文件句柄
	long fHandle1; //文件句柄
	if((fHandle1=_findfirst(a, &file)) == -1L )//判断是否有文件，有就进入do while 
	{
		return 0;
	}
	else
		do{
			if(file.attrib & _A_SUBDIR && cok == 1)//判断是否是文件夹,属性相同 
			{
				//判断是否为"."当前目录，".."上一层目录
				if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0) && ok == 0)//遍历文件夹 
				{
					char newPath[100];
					strcat(c, "\\");
					strcpy(newPath, c);
					strcat(newPath, file.name);
					puts(file.name);
					puts(newPath);
					Bianliwenjian(newPath,b);//递归调用
					ok = 1;
				}
				else if((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0) && ok == 1)//遍历文件夹 
				{
					char newPath[100];
					strcpy(newPath, c);
					strcat(newPath, file.name);
					puts(file.name);
					puts(newPath);
					Bianliwenjian(newPath,b);//递归调用
				}
			}
			else if(cok == 0)//先查找每个文件夹中.c的文件； 
			{
				
//				int count;
				cok = 1;
				char savepath1[100];
				char savepath2[100];
				strcpy(savepath1,savepath);
				strcat(savepath1,"\\");
				strcpy(savepath2,savepath1);
				strcat(savepath,"\\*.c");
				if( (fHandle=_findfirst(savepath , &file1 )) == -1L )//遍历文件； 
				{
					cok = 1; 
					continue;//若不是.c文件，继续 
				} 
				else 
				{
				do{
				    sumwenjian++;
					strcat(savepath1,file1.name);
					puts(savepath1);
					FILE *fp = fopen(savepath1,"r");//声明fp是指针，只读打开一个文本文件 
					if(fp == NULL)
					{
						return -1;
					}
//					count = 0;
					while(fgetc(fp) != EOF)//查阅字符数; 
					{
						count++;//统计字符数 
					} 
					rewind(fp);//回到首位置 
					char ch[1000];
					int k;
					
					while(fgets(ch, 1000, fp) != 0)
					{
						int t = strlen(ch);
						counthang=judgehang(ch,t,k,counthang);
						countif=judgeif(ch,t,countif);
						countwhile=judgewhile(ch,t,countwhile);
						countfor=judgefor(ch,t,countfor);
					}
					fclose(fp);//				    count1+=count;
				    printf("%d ",count);
				    strcpy(savepath1,savepath2);//复制原路径 
					}while( _findnext(fHandle,&file1)==0);
				}
			}
		}while( _findnext(fHandle1,&file)==0 );
		//关闭句柄 
		_findclose( fHandle );
	return 0;
}



int main()
{
	pjdmhs = 0,sumwenjian = 0;//平均代码数 总文件数 
	struct _finddata_t ag;
	long fHandle2;
	char a[100];//保存文件夹名； 
	char path[100];//保存路径；
	char b[5]="\\*.*";   // *.*代表全部类型的文件，类似的 *.txt则代表txt类型的文件
	printf("请输入文件夹的名字:\n");
	scanf("%s",a);
	strcpy(path,a);
	strcat(a,"\\*.*");
	if( (fHandle2=_findfirst(a, &ag))==-1L )
	{
		printf( "当前目录下没有文件\n");
		return 0;
	}
	else{
    do
	 {
		if(ag.attrib & _A_SUBDIR)//判断是否是文件夹； 属性，文件夹属性 
		{
			
			//判断是否为"."当前目录，".."上一层目录
			if ((strcmp(ag.name, ".") != 0) && (strcmp(ag.name, "..") != 0))//遍历文件夹 
			{
				char newPath[100];
				strcpy(newPath, path);
				strcat(newPath, "\\");
				strcat(newPath, ag.name);
				strcpy(filename, ag.name);
				printf("%s\n",filename);
				Bianliwenjian(newPath, b);//调用遍历文件夹的函数
				if(sumwenjian == 0)
					pjdmhs = 0;
				else
				{
					pjdmhs = counthang / sumwenjian;
				}
				fprintf(fpp, "%s   :  .c文件数为%d,   平均代码行数%d,   字符数为%d,   总共有%d行代码,   总共有%d个if语句,   总共有%d个while语句, 总共有%d个for语句\n",filename, sumwenjian, pjdmhs, count,counthang,countif,countwhile,countfor);
				printf("文件数量：%d\n",sumwenjian);
				printf("\n");
			}
		}
		counthang = 0,count = 0,countif = 0,countwhile = 0,countfor = 0,pjdmhs = 0,sumwenjian = 0;//初始化 
		}while(_findnext(fHandle2,&ag)==0 );
	}
		
	printf("文件已生成");
	fclose(fpp);
	return 0; 
}
