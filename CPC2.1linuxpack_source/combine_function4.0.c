#include <stdio.h>

#include <string.h>
#include <stdlib.h>

void combine(char *f1,char *f2,char *f3,char *f4,char *f5);//combine the peaks in f1 and f2, combine the peaks if overlap
                                                                    //f1 is order file,f2 is peak file
																	//f4 is the number of files,
                                                                   //f5 num of p2 file

int max(int a,int b);
int min(int a,int b); 																   
void main(int argc,char *argv[])
{

/*printf("1");
scanf("%s",s1);
printf("2");
scanf("%s",s2);
printf("3");
scanf("%s",s3);*/                                       
combine(argv[1],argv[2],argv[3],argv[4],argv[5]);

}

void combine(char *f1,char *f2,char *f3,char *f4,char *f5)
{ 
  struct peak
{
  char chr[50];
  int start; //location
  int end;
  int* ord;

} ; 

struct peak* peakfile1;
struct peak* peakfile2;
struct peak* peakfile3;
struct peak peaktemp;
 struct peak peak;
 
FILE *p1;
FILE *p2;
FILE *p3;
int cap1;
int cap2;
int temp1=0;
int temp2=0;
int tagstart=0;
int tagend=0;
int tagtemp=0;
int flag=0;
int flag2=0;
int start;
int end;
int num=0;
int num2=1;
int j;
char mid;
int i;
int k;
char c[50];
char ch1;
char ch2;
int filenum;
//int fnum1;
int fnum2;
filenum=atoi(f4);
//fnum1=atoi(f5);
fnum2=atoi(f5);
    //open file
	if((p1=fopen(f1,"r"))==NULL) 
{
	printf("\nerror occurred when opening the input file to combine peaks!");
    getchar(); 
    exit(1); 
}
 	if((p2=fopen(f2,"r"))==NULL) 
{
	printf("\nerror occurred when opening the input file to combine peaks!");
    getchar(); 
    exit(1); 
}

if((p3=fopen(f3,"wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}

 ch1=fgetc(p1);
 ch2=fgetc(p2);
 rewind(p1);
 rewind(p2);
  if((ch1!=EOF)||(ch2!=EOF))
  if(ch1==EOF)
   while(!feof(p2))
    { 
	 fscanf(p2,"%s\t%d\t%d\t%s\t%s\n",&peak.chr,&peak.start,&peak.end,&c,&c);
     fprintf(p3,"%s\t%d\t%d\tMACS_peak_order_%d\t",peak.chr,peak.start,peak.end,num2);
     num2++;
     for(i=0;i<=(filenum*filenum-1);i++)
     if(i==fnum2)
     fprintf(p3,"1");
     else
     fprintf(p3,"0");

    fprintf(p3,"\n");

	 
	 
	  
	}
  else if(ch2==EOF)
     while(!feof(p1))
	 {
	 ch1=fgetc(p1);
	  if(ch1!=EOF)
	  fputc(ch1,p3);
	  
	 }
 else
{
//calculate the size of f1
   cap1=0;
while(!feof(p1))
     {   
           mid=fgetc(p1);
           if(mid=='\n')  
            cap1++;   
      }
   
       cap1=cap1+1;   
       rewind(p1);
//calculate the size of f2
cap2=0;
	   while(!feof(p2))
     {   
           mid=fgetc(p2);
           if(mid=='\n')  
            cap2++;   
      }
   
       cap2=cap2+1;   
       rewind(p2);
// read data to mem
if((peakfile1=(struct peak*)malloc(sizeof(struct peak)*cap1))==NULL)
	{
	  printf("Memory is not sufficent.Creating output file fails.");
	  exit(0);
	  getchar();
	}

if((peakfile2=(struct peak*)malloc(sizeof(struct peak)*cap2))==NULL)
	{
	  printf("Memory is not sufficent.Creating output file fails.");
	  exit(0);
	  getchar();
	}
if((peakfile3=(struct peak*)malloc(sizeof(struct peak)*(cap1+cap2)))==NULL)
	{
	  printf("Memory is not sufficent.Creating output file fails.");
	  exit(0);
	  getchar();
	}

	
	cap1=0;
	cap2=0;
	
while(!feof(p1))
{
//fscanf(p1,"%s\t%d\t%d\t%s\t%f\n",&peakfile1[cap1].chr,&peakfile1[cap1].start,&peakfile1[cap1].end,&c,&peakfile1[cap1].sanger);
fscanf(p1,"%s\t%d\t%d\t%s\t",&peakfile1[cap1].chr,&peakfile1[cap1].start,&peakfile1[cap1].end,&c);
if((peakfile1[cap1].ord=(int*)malloc(sizeof(int)*filenum*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating order file fails.");
	  exit(0);
	  getchar();
	}
for(i=0;i<=(filenum*filenum-1);i++)
peakfile1[cap1].ord[i]=fgetc(p1)-48;

fscanf(p1,"\n");

cap1++;



}
 while(!feof(p2))
{
//fscanf(p2,"%s\t%d\t%d\t%s\t%f\n",&peakfile2[cap2].chr,&peakfile2[cap2].start,&peakfile2[cap2].end,&c,&peakfile2[cap2].sanger);
fscanf(p2,"%s\t%d\t%d\t%s\t%s\n",&peakfile2[cap2].chr,&peakfile2[cap2].start,&peakfile2[cap2].end,&c,&c);
if((peakfile2[cap2].ord=(int*)malloc(sizeof(int)*filenum*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating order file fails.");
	  exit(0);
	  getchar();
	}
for(i=0;i<=(filenum*filenum-1);i++)
peakfile2[cap2].ord[i]=0;

peakfile2[cap2].ord[fnum2]=1;

cap2++;


}

//sort in one file
num=0;
 for(temp2=0;temp2<=(cap2-1);temp2++)
{
   if((strcmp(peakfile2[temp2].chr,peakfile1[0].chr)<0)||(strcmp(peakfile2[temp2].chr,peakfile1[0].chr)==0)&&(peakfile2[temp2].start<peakfile1[0].start)) 
    {
	 strcpy(peakfile3[num].chr,peakfile2[temp2].chr);
	 peakfile3[num].start=peakfile2[temp2].start;
	 peakfile3[num].end=peakfile2[temp2].end;
	 peakfile3[num].ord=peakfile2[temp2].ord;
	 num++;
	}
   else
   break;
}
 
 for(temp1=0;temp1<=(cap1-2);temp1++)
{
    strcpy(peakfile3[num].chr,peakfile1[temp1].chr);
	 peakfile3[num].start=peakfile1[temp1].start;
	 peakfile3[num].end=peakfile1[temp1].end;
	 peakfile3[num].ord=peakfile1[temp1].ord;
	 num++;
	 
for(;temp2<=(cap2-1);temp2++)
{
 if((strcmp(peakfile2[temp2].chr,peakfile1[temp1+1].chr)<0)||(strcmp(peakfile2[temp2].chr,peakfile1[temp1+1].chr)==0)&&(peakfile2[temp2].start<peakfile1[temp1+1].start)) 
  {
     strcpy(peakfile3[num].chr,peakfile2[temp2].chr);
	 peakfile3[num].start=peakfile2[temp2].start;
	 peakfile3[num].end=peakfile2[temp2].end;
	 peakfile3[num].ord=peakfile2[temp2].ord;
	 num++;  
  
  }
  else
  break;
  
  
}


}
 
   {strcpy(peakfile3[num].chr,peakfile1[temp1].chr);
	 peakfile3[num].start=peakfile1[temp1].start;
	 peakfile3[num].end=peakfile1[temp1].end;
	 peakfile3[num].ord=peakfile1[temp1].ord;
	 num++;}
 
 for(;temp2<=(cap2-1);temp2++)
{
     strcpy(peakfile3[num].chr,peakfile2[temp2].chr);
	 peakfile3[num].start=peakfile2[temp2].start;
	 peakfile3[num].end=peakfile2[temp2].end;
	 peakfile3[num].ord=peakfile2[temp2].ord;
	 num++;  
 
}



 
 //combine the peaks
 
 num2=1;
  {strcpy(peaktemp.chr,peakfile3[0].chr);
	peaktemp.start=peakfile3[0].start;
	peaktemp.end=peakfile3[0].end;
	peaktemp.ord=peakfile3[0].ord;}
 
 for(i=1;i<=(cap1+cap2-1);i++)
 {
   if((strcmp(peaktemp.chr,peakfile3[i].chr)==0)&&(!((peaktemp.end<peakfile3[i].start)||(peakfile3[i].end<peaktemp.start))))//overlap
	{
	peaktemp.start=min(peakfile3[i].start,peaktemp.start);
	peaktemp.end=max(peakfile3[i].end,peaktemp.end);
	for(j=0;j<=(filenum*filenum-1);j++)
	peaktemp.ord[j]=peakfile3[i].ord[j]||peaktemp.ord[j];
	
	}
	else
    {
	
	if(strlen(peaktemp.chr)<=6)
	{
	fprintf(p3,"%s\t%d\t%d\tMACS_peak_order_%d\t",peaktemp.chr,peaktemp.start,peaktemp.end,num2);
     for(j=0;j<=(filenum*filenum-1);j++)
    fprintf(p3,"%d",peaktemp.ord[j]);
	fprintf(p3,"\n");
	 
	 num2++;
	 }
	strcpy(peaktemp.chr,peakfile3[i].chr);
	peaktemp.start=peakfile3[i].start;
	peaktemp.end=peakfile3[i].end;
	peaktemp.ord=peakfile3[i].ord;
	 

	
	
	}
 
 
 
 
 
 
 }
 
   
 	fprintf(p3,"%s\t%d\t%d\tMACS_peak_order_%d\t",peaktemp.chr,peaktemp.start,peaktemp.end,num2);
     for(j=0;j<=(filenum*filenum-1);j++)
    fprintf(p3,"%d",peaktemp.ord[j]);
	fprintf(p3,"\n");
	 

 
 
 
 

}
fclose(p1);
fclose(p2);
fclose(p3);



}


int max(int a,int b)
{
  if(a>=b)
  return a;
  else
  return b;


}
int min(int a,int b)
{
if(a<=b)
return a;
else 
return b;



} 	
