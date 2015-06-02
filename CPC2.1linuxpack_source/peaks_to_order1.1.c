#include <stdio.h>

#include <string.h>
#include <stdlib.h>

void ptoo(char *f1,char *f2,char *f3,char *f4);//change the peaks file f1 to order file f2,f3 is the number of files,
                                                                   //f4 num of p1 file

void main(int argc,char *argv[])
{

/*printf("1");
scanf("%s",s1);
printf("2");
scanf("%s",s2);
printf("3");
scanf("%s",s3);*/                                       
ptoo(argv[1],argv[2],argv[3],argv[4]);

}


void ptoo(char *f1,char *f2,char *f3,char *f4)
{
  struct peak
{
  char chr[50];
  int start; //location
  int end;
 
} ; 

 struct peak peak;
 FILE *p1;
 FILE *p2;
 char c[50];
 int filenum;
 int fnum1;
 int num;
 int i;
 char ch1;
 filenum=atoi(f3);
 fnum1=atoi(f4);
//printf("Transfering peak file to order file!");
	if((p1=fopen(f1,"r"))==NULL) 
{
	printf("\nerror occurred when opening the input file to combine peaks!");
    getchar(); 
    exit(1); 
}
 
if((p2=fopen(f2,"wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}

num=1;
ch1=fgetc(p1);
 rewind(p1);
  if(ch1!=EOF)
while(!feof(p1))
{
//fscanf(p1,"%s\t%d\t%d\t%s\t%f\n",&peakfile1[cap1].chr,&peakfile1[cap1].start,&peakfile1[cap1].end,&c,&peakfile1[cap1].sanger);
fscanf(p1,"%s\t%d\t%d\t%s\t%s\n",&peak.chr,&peak.start,&peak.end,&c,&c);
fprintf(p2,"%s\t%d\t%d\tMACS_peak_order_%d\t",peak.chr,peak.start,peak.end,num);
num++;
for(i=0;i<=(filenum*filenum-1);i++)
if(i==fnum1)
fprintf(p2,"1");
else
fprintf(p2,"0");

fprintf(p2,"\n");





}





}