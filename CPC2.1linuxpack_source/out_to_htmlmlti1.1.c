#include <stdio.h>//change output.bed to .html
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
void addcontect(FILE *des,char *src);//des is opening
void creathtml(char *inputfile,char *outputmain,char *outputpath,int filenum,char *grapht,char *htmltitle);
void replace(char *str);
char * itoa(int n, char * p) ;
void main(int argc,char *argv[])//argv[1] inputfile,argv[2] output mainpage,argv[3] number of file,argv[4] graph tag
{
	int filenum;
	char tempchar[1000];
filenum=atoi(argv[3]);

creathtml(argv[1],"total_html/total.html","total_html/",filenum,argv[4],"Total");
creathtml("class1.bed","class1_html/class1.html","class1_html/",filenum,argv[4],"Class1");
creathtml("class2.bed","class2_html/class2.html","class2_html/",filenum,argv[4],"Class2");
creathtml("class3.bed","class3_html/class3.html","class3_html/",filenum,argv[4],"Class3");
creathtml("class4.bed","class4_html/class4.html","class4_html/",filenum,argv[4],"Class4");
creathtml("class5.bed","class5_html/class5.html","class5_html/",filenum,argv[4],"Class5");
{strcpy(tempchar,"cp html_ingre/load_page.html ");
strcat(tempchar,argv[2]);
replace(tempchar);
system(tempchar);
}


}
void addcontect(FILE *des,char *src)
{
FILE *f1;
char ch;
if((f1=fopen(src,"r"))==NULL) //imput txt
{
	printf("\nerror occurred when opening the src file to combine peaks!");
    getchar(); 
    exit(1); 
}

ch = fgetc(f1);
while(!feof(f1))
{
    fputc(ch,des);
    ch = fgetc(f1);
}
fclose(f1);

}


void creathtml(char *inputfile,char *outputmain,char *outputpath,int filenum,char *grapht,char *htmltitle)//inputfile inputfile,outputmain output mainpage,filenum number of file,argv[4] graph tag
{
  struct peak
{
  char c1[1000];
  char c2[1000];
  char c3[1000];
  char c4[1000];
  char c5[1000];
  int c6;
} peak; 
 FILE *p1;

 FILE *p3;
 FILE *pa;//every html
 int num=1;
 int numppage=40;  //number of item in a page
 int pagestart=1;
 char chartemp[20];
 char pagefilename[1000];
 int flag=0;
 char ch1;
 int i;
 char tagtemp[1000];
 char graphtemp[1000];
 char *result = NULL;
 mkdir(outputpath,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

 
if((p1=fopen(inputfile,"r"))==NULL) //input txt
{
	printf("\nerror occurred when opening the input file to combine peaks!");
    getchar(); 
    exit(1); 
}


strcpy(pagefilename,outputpath);
strcat(pagefilename,"data.js");
if((p3=fopen(pagefilename,"wb"))==NULL)  //set up data.js
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}

strcpy(pagefilename,"cp html_ingre/pageTurn.html ");
strcat(pagefilename,outputmain);
replace(pagefilename);
system(pagefilename);

strcpy(pagefilename,"cp html_ingre/drawchartscript.js ");
strcat(pagefilename,outputpath);
replace(pagefilename);
system(pagefilename);

strcpy(pagefilename,"cp html_ingre/Chart.js ");
strcat(pagefilename,outputpath);
replace(pagefilename);
system(pagefilename);

strcpy(pagefilename,"cp html_ingre/foot.js ");
strcat(pagefilename,outputpath);
replace(pagefilename);
system(pagefilename);

strcpy(pagefilename,"cp html_ingre/site.css ");
strcat(pagefilename,outputpath);
replace(pagefilename);
system(pagefilename);

strcpy(pagefilename,"cp html_ingre/style.js ");
strcat(pagefilename,outputpath);
replace(pagefilename);
system(pagefilename);

ch1=fgetc(p1);
rewind(p1);

while(!feof(p1))
{
flag=0;
fscanf(p1,"%s\t%s\t%s\t%s\t%s\t%d\n",&peak.c1,&peak.c2,&peak.c3,&peak.c4,&peak.c5,&peak.c6);

//create html
{
//create page when num%40==1
if(num%40==1){
itoa(pagestart,chartemp);
strcpy(pagefilename,outputpath);
strcat(pagefilename,"id");
strcat(pagefilename,chartemp);
itoa(pagestart+39,chartemp);
strcat(pagefilename,"-");
strcat(pagefilename,chartemp);
strcat(pagefilename,".html");

if((pa=fopen(pagefilename,"wb"))==NULL)  //new page
{ 
	printf("\ncreate html file error\n");
    getchar(); 
    exit(1); 
}
//import head.html
addcontect(pa,"html_ingre/head.html");

if(ch1!=EOF)
fprintf(pa," <tr>\n<td id=\"startnum\">%d</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%d</td>\n<td>%s</td>\n<td>\
<canvas id=\"myChart%d\" width=\"200\" height=\"80\"></canvas></td>\n\
</tr>\n",num,peak.c1,peak.c2,peak.c3,peak.c6,peak.c5,num);

}
else
{
fprintf(pa," <tr>\n<td>%d</td>\n<td>%s</td>\n<td>%s</td>\n<td>%s</td>\n<td>%d</td>\n<td>%s</td>\n<td>\
<canvas id=\"myChart%d\" width=\"200\" height=\"80\"></canvas></td>\n\
</tr>\n",num,peak.c1,peak.c2,peak.c3,peak.c6,peak.c5,num);

}



}
//create data.js num

{

  if(num==1)
  {if(strcmp("NA",peak.c5)==0)
  fprintf(p3,"var dataarr = [[%s]","");
  else
  fprintf(p3,"var dataarr = [[%s]",peak.c5);
  }
  else
  {if(strcmp("NA",peak.c5)==0)
  fprintf(p3,",\n[%s]","");
  else
  fprintf(p3,",\n[%s]",peak.c5);
  }

  
}

num++;
if(num%40==1)
{
pagestart=pagestart+40;
addcontect(pa,"html_ingre/rear.html");
fclose(pa);
flag=1;
}

}



fprintf(p3,"\n];\n");
//transfer input tag to available tag
{
 strcpy(graphtemp,grapht);
  strcpy(tagtemp,""); 
   result = strtok( graphtemp, "," );
   i=1;
   while( result != NULL ) {
   strcat(tagtemp,"\"");
   strcat(tagtemp,result);
   strcat(tagtemp,"\"");
   if(i!=filenum)
   strcat(tagtemp,",");
   i++;
       result = strtok( NULL, "," );
   } 
}   

fprintf(p3,"var labelsset=[%s];\n",tagtemp);
fprintf(p3,"var iPageSize = %d;\n",40);
fprintf(p3,"var iProCount = %d;\n",(num-1));
fprintf(p3,"var mainPageUrl = \"%s\";\n",outputmain);
fprintf(p3,"var datapath = \"%s\";\n",outputpath);
fprintf(p3,"var titleName = \"%s\";\n",htmltitle);
if(flag==0)
{addcontect(pa,"html_ingre/rear.html");
fclose(pa);
}


fclose(p1);

fclose(p3);



}
 void replace(char *str)
 {
    /*if (NULL == str) {
        return;
    }
     
    while (*str != '\0') {
        if (*str == '/') {
            *str = '\\';
        }
		str++;
    }*/
}
char * itoa(int n, char * p) 

{ 

    sprintf(p, "%d", n); 

    return (p); 

}
