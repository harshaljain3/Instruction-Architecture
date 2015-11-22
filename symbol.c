#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 25
int symbolmatch(char *s){
    char *a=(char *)malloc(sizeof(char)*max);
    int w=0,kk=0;
    FILE *l=fopen("symboltable.txt","r");
    while(fgets(a,max,l)!=NULL){
            int j=0;
            w=0;
            int k;
            while(a[j]!=' '){
                if(s[j]!=a[j]){
                    w=1;
                    break;
                }
                j++;
            }
            if(w!=1&&j==strlen(s)){
                kk=1;
                    break;
            }
    }
        fclose(l);
       return kk;
}
int findopcode(char *s,int gf){
    char *p=(char *)malloc(sizeof(char)*max);
    int w=0,kk=0,ll;
    FILE *q=fopen("opcode.txt","r");
    while(fgets(p,max,q)!=NULL){
            int j=0;
            w=0;
            int k;
            if(p[j]==s[0]&&gf==1){
                    for(ll=0;p[ll]!=' ';ll++)
                printf("%c",p[ll]);
                printf("\n");
            }
            while(p[j]!=' '){
                if(s[j]!=p[j]){
                    w=1;
                    break;
                }
                j++;
            }
            if(w!=1 && j==strlen(s)){
                    kk=1;
                    break;
        }
    }
            fclose(q);
            return kk;
}
void main()
{
 	FILE *fr,*fw;
 	int cx,bx,lin=0;
 	char output[20],input[20];
 	printf("Project information: 16 bit Architecture\n");
 	printf(" \n");
 	printf("Total 16 Registers,1 register of 4 bit\n");
 	printf(" \n");
 	printf("Enter your input file\n");
 	scanf("%s",input);
 	printf("Enter your Symboltable file\n");
 	scanf("%s",output);
	fr = fopen(input,"r");
	fw = fopen (output,"w");
	char a[50];
	char ch;
	int line=1,i=0,ll=0;
	while(1){
        ch=fgetc(fr);
		if(ch==EOF){
                if(ll==0){
                    printf("Error!!! Empty File\n");
                }
			break;
		}
		else
		{   ll=1;
		    if(ch==10)
            {
                line++;
                i=0;
            }
            a[i]=ch;
            i++;
			if(ch==':')
			{
				a[i-1]='\0';
				i=0;
				fprintf(fw,"%s %d\n",a,line);
			}
		}
	}
	fclose(fr);
	fclose(fw);
	fr = fopen(input,"r");
	line=1;
	i=0;
	int zz=0,h=0;
	while(1)
	{
		ch=fgetc(fr);
		if(ch==EOF)
			break;
		else
		{
		    if(i==0 && ch>=48&&ch<=57){
                h=0;
                zz=1;
            }
			if(ch==':')
			{
			    h=0;
				a[i]='\0';
				i=0;
				cx=findopcode(a,0);
				if(cx==1){
                    printf("error %d opcode use as label!!\n",line);
				}
			}
			else if(ch!=' '&&ch!='\n'&&ch!=','){
                    h=0;
                a[i]=ch;
                i++;
			}
			else if(ch==' ' || ch=='\n' || ch==','){
                    h++;
                a[i]='\0';
                cx=findopcode(a,0);
              bx=symbolmatch(a);
              if(cx!=1&&bx!=1&&zz==0){
                    FILE *sx;
                    sx=fopen("binary.txt","w");
                    fclose(sx);
                if(strlen(a)!=0&&a[i-1]!='h'){
                        if(a[0]!='R'){
                printf("error in %d line(%s is not valid opcode)\n",line,a);
                        }
                else{
                        char ee;
                printf("error in %d line(%s is not valid register)\n",line,a);
                }
                }
              }
              if(ch=='\n')
                    line++;
            i=0;
            if(zz==1)
                zz=0;
			}
		}
	}
	fclose(fr);
	fclose(fw);
}
