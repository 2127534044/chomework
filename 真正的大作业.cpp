#include <stdio.h>
#include<io.h>
#include<string.h>//strlen 
int count=0,counthang = 0,countwhile = 0, countfor = 0 ,countif = 0;//��ʼ��������while for if�������
int pjdmhs,sumwenjian;//��¼�ܴ�����������������if��while��for�����,ƽ����������,���ļ�����
char filename[100];//�ļ���

FILE * fpp = fopen("Bosshomework.txt","w");//���浽���ı��ļ� 

int judgehang(char *ch,int t,int k,int counthang)//�ж������ĺ��� 
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

int judgeif(char *ch,int t,int countif)//�ж�if�����ĺ��� 
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

int judgewhile(char *ch,int t,int countwhile)//�ж�while�����ĺ��� 
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

int judgefor(char *ch,int t,int countfor)//�ж�for�����ĺ��� 
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

int Bianliwenjian(char *a,char *b)//�ļ��б�������
{
	int ok = 0;//�Ƿ����һ�α����ı�־ 
	int cok = 0;//�ж��Ƿ������.c���ļ��ı�־ 
	char savepath[100];//����·�� 
	strcpy(savepath, a);
	char c[100];//��ʱ����·�� 
	strcpy(c, a);
	strcat(a, b);//�����ļ������� 
	struct _finddata_t file;//��Ŀ¼�Ľṹ�� 
	struct _finddata_t file1;//��ʱ�ı�Ŀ¼�Ľṹ�� 
	long fHandle; //��ʱ�ļ����
	long fHandle1; //�ļ����
	if((fHandle1=_findfirst(a, &file)) == -1L )//�ж��Ƿ����ļ����оͽ���do while 
	{
		return 0;
	}
	else
		do{
			if(file.attrib & _A_SUBDIR && cok == 1)//�ж��Ƿ����ļ���,������ͬ 
			{
				//�ж��Ƿ�Ϊ"."��ǰĿ¼��".."��һ��Ŀ¼
				if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0) && ok == 0)//�����ļ��� 
				{
					char newPath[100];
					strcat(c, "\\");
					strcpy(newPath, c);
					strcat(newPath, file.name);
					puts(file.name);
					puts(newPath);
					Bianliwenjian(newPath,b);//�ݹ����
					ok = 1;
				}
				else if((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0) && ok == 1)//�����ļ��� 
				{
					char newPath[100];
					strcpy(newPath, c);
					strcat(newPath, file.name);
					puts(file.name);
					puts(newPath);
					Bianliwenjian(newPath,b);//�ݹ����
				}
			}
			else if(cok == 0)//�Ȳ���ÿ���ļ�����.c���ļ��� 
			{
				
//				int count;
				cok = 1;
				char savepath1[100];
				char savepath2[100];
				strcpy(savepath1,savepath);
				strcat(savepath1,"\\");
				strcpy(savepath2,savepath1);
				strcat(savepath,"\\*.c");
				if( (fHandle=_findfirst(savepath , &file1 )) == -1L )//�����ļ��� 
				{
					cok = 1; 
					continue;//������.c�ļ������� 
				} 
				else 
				{
				do{
				    sumwenjian++;
					strcat(savepath1,file1.name);
					puts(savepath1);
					FILE *fp = fopen(savepath1,"r");//����fp��ָ�룬ֻ����һ���ı��ļ� 
					if(fp == NULL)
					{
						return -1;
					}
//					count = 0;
					while(fgetc(fp) != EOF)//�����ַ���; 
					{
						count++;//ͳ���ַ��� 
					} 
					rewind(fp);//�ص���λ�� 
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
				    strcpy(savepath1,savepath2);//����ԭ·�� 
					}while( _findnext(fHandle,&file1)==0);
				}
			}
		}while( _findnext(fHandle1,&file)==0 );
		//�رվ�� 
		_findclose( fHandle );
	return 0;
}



int main()
{
	pjdmhs = 0,sumwenjian = 0;//ƽ�������� ���ļ��� 
	struct _finddata_t ag;
	long fHandle2;
	char a[100];//�����ļ������� 
	char path[100];//����·����
	char b[5]="\\*.*";   // *.*����ȫ�����͵��ļ������Ƶ� *.txt�����txt���͵��ļ�
	printf("�������ļ��е�����:\n");
	scanf("%s",a);
	strcpy(path,a);
	strcat(a,"\\*.*");
	if( (fHandle2=_findfirst(a, &ag))==-1L )
	{
		printf( "��ǰĿ¼��û���ļ�\n");
		return 0;
	}
	else{
    do
	 {
		if(ag.attrib & _A_SUBDIR)//�ж��Ƿ����ļ��У� ���ԣ��ļ������� 
		{
			
			//�ж��Ƿ�Ϊ"."��ǰĿ¼��".."��һ��Ŀ¼
			if ((strcmp(ag.name, ".") != 0) && (strcmp(ag.name, "..") != 0))//�����ļ��� 
			{
				char newPath[100];
				strcpy(newPath, path);
				strcat(newPath, "\\");
				strcat(newPath, ag.name);
				strcpy(filename, ag.name);
				printf("%s\n",filename);
				Bianliwenjian(newPath, b);//���ñ����ļ��еĺ���
				if(sumwenjian == 0)
					pjdmhs = 0;
				else
				{
					pjdmhs = counthang / sumwenjian;
				}
				fprintf(fpp, "%s   :  .c�ļ���Ϊ%d,   ƽ����������%d,   �ַ���Ϊ%d,   �ܹ���%d�д���,   �ܹ���%d��if���,   �ܹ���%d��while���, �ܹ���%d��for���\n",filename, sumwenjian, pjdmhs, count,counthang,countif,countwhile,countfor);
				printf("�ļ�������%d\n",sumwenjian);
				printf("\n");
			}
		}
		counthang = 0,count = 0,countif = 0,countwhile = 0,countfor = 0,pjdmhs = 0,sumwenjian = 0;//��ʼ�� 
		}while(_findnext(fHandle2,&ag)==0 );
	}
		
	printf("�ļ�������");
	fclose(fpp);
	return 0; 
}
