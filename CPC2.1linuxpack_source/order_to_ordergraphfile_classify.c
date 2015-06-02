#include <stdio.h>

#include <string.h>
#include <stdlib.h>

int classify_graph_function(int* ordg,int filenum);
int monotonic_decrease(int* ordg,int filenum);//1 for yes,0 for no
int monotonic_increase(int* ordg,int filenum);//1 for yes,0 for no
int one_convex_peak(int* ordg,int filenum);//1 for yes,0 for no
int one_concave_peak(int* ordg,int filenum);//1 for yes,0 for no
//int mutiple_peaks(int* ordg,int filenum);//1 for yes,0 for no
int *otoog(int *ordm,int filenum);//change order matrix to order graph array
void main(int argc,char *argv[])//argv[1] input file name, argv[2] output file name,argv[3] file number
{
  struct peak
{
  char chr[50];
  int start; //location
  int end;
  int* ord;
} peak; 

 FILE *p1;
 FILE *p2;
 FILE *class1;
 FILE *class2;
 FILE *class3;
 FILE *class4;
 FILE *class5;
 int filenum;
 char c[50];
 int* orda;
 int num=1;
 int i;
 int ord_classify;
if((p1=fopen(argv[1],"r"))==NULL) 
{
	printf("\nerror occurred when opening the input file to combine peaks!");
    getchar(); 
    exit(1); 
}
 
if((p2=fopen(argv[2],"wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}

if((class1=fopen("class1.bed","wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}

if((class2=fopen("class2.bed","wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}
if((class3=fopen("class3.bed","wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}
if((class4=fopen("class4.bed","wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}
if((class5=fopen("class5.bed","wb"))==NULL)  //set up output
{ 
	printf("\ncreate output file error\n");
    getchar(); 
    exit(1); 
}


filenum=atoi(argv[3]);
while(!feof(p1))
{

fscanf(p1,"%s\t%d\t%d\t%s\t",&peak.chr,&peak.start,&peak.end,&c);
if((peak.ord=(int*)malloc(sizeof(int)*filenum*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating order graph file fails.");
	  exit(0);
	  getchar();
	}
for(i=0;i<=(filenum*filenum-1);i++)
peak.ord[i]=fgetc(p1)-48;

fscanf(p1,"\n");

//create order array
if((orda=(int*)malloc(sizeof(int)*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating order array file fails.");
	  exit(0);
	  getchar();
	}

orda=otoog(peak.ord,filenum);
//compute the classification
if(orda!=NULL)
ord_classify=classify_graph_function(orda,filenum);
else
ord_classify=0;

switch (ord_classify)
{ 
case 1:
{fprintf(class1,"%s\t%d\t%d\tMACS_peak_ordergraph_%d\t",peak.chr,peak.start,peak.end,num);
if(orda==NULL)
fprintf(class1,"NA\t0");
else
{
for(i=0;i<=(filenum-1);i++)
{
fprintf(class1,"%d",orda[i]);
if(i!=(filenum-1))
fprintf(class1,",");


}

fprintf(class1,"\t%d",ord_classify);
}
fprintf(class1,"\n");
}
break;
case 2:
{fprintf(class2,"%s\t%d\t%d\tMACS_peak_ordergraph_%d\t",peak.chr,peak.start,peak.end,num);
if(orda==NULL)
fprintf(class2,"NA\t0");
else
{
for(i=0;i<=(filenum-1);i++)
{
fprintf(class2,"%d",orda[i]);
if(i!=(filenum-1))
fprintf(class2,",");


}

fprintf(class2,"\t%d",ord_classify);
}
fprintf(class2,"\n");
}
break;
case 3:
{fprintf(class3,"%s\t%d\t%d\tMACS_peak_ordergraph_%d\t",peak.chr,peak.start,peak.end,num);
if(orda==NULL)
fprintf(class3,"NA\t0");
else
{
for(i=0;i<=(filenum-1);i++)
{
fprintf(class3,"%d",orda[i]);
if(i!=(filenum-1))
fprintf(class3,",");


}

fprintf(class3,"\t%d",ord_classify);
}
fprintf(class3,"\n");
}
break;
case 4:
{fprintf(class4,"%s\t%d\t%d\tMACS_peak_ordergraph_%d\t",peak.chr,peak.start,peak.end,num);
if(orda==NULL)
fprintf(class4,"NA\t0");
else
{
for(i=0;i<=(filenum-1);i++)
{
fprintf(class4,"%d",orda[i]);
if(i!=(filenum-1))
fprintf(class4,",");


}

fprintf(class4,"\t%d",ord_classify);
}
fprintf(class4,"\n");
}
break;
case 5:
{fprintf(class5,"%s\t%d\t%d\tMACS_peak_ordergraph_%d\t",peak.chr,peak.start,peak.end,num);
if(orda==NULL)
fprintf(class5,"NA\t0");
else
{
for(i=0;i<=(filenum-1);i++)
{
fprintf(class5,"%d",orda[i]);
if(i!=(filenum-1))
fprintf(class5,",");


}

fprintf(class5,"\t%d",ord_classify);
}
fprintf(class5,"\n");
}
break;
default:
break;
}



fprintf(p2,"%s\t%d\t%d\tMACS_peak_ordergraph_%d\t",peak.chr,peak.start,peak.end,num);
if(orda==NULL)
fprintf(p2,"NA\t0");
else
{
for(i=0;i<=(filenum-1);i++)
{
fprintf(p2,"%d",orda[i]);
if(i!=(filenum-1))
fprintf(p2,",");


}

fprintf(p2,"\t%d",ord_classify);
}


fprintf(p2,"\n");


free(orda);
free(peak.ord);
num++;


}
fclose(p1);
fclose(p2);
fclose(class1);
fclose(class2);
fclose(class3);
fclose(class4);
fclose(class5);
}




int *otoog(int *ordm,int filenum)
{

int* remain;
int remainnum;
int i;
int** ogm;
int ogmnum;
int flag;
int j;
int* oga;//order graph array
//create remain array
if((remain=(int*)malloc(sizeof(int)*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating remain array fails.");
	  exit(0);
	  getchar();
	}
for(i=0;i<=filenum-1;i++)
remain[i]=i;

remainnum=filenum;

//create order graph matrix
if((ogm=(int**)malloc(sizeof(int*)*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating order graph matrix fails.");
	  exit(0);
	  getchar();
	}
for(i=0;i<=filenum-1;i++)
   {
if((ogm[i]=(int*)malloc(sizeof(int)*(filenum+1)))==NULL)
	{
	  printf("Memory is not sufficent.Creating order graph matrix fails.");
	  exit(0);
	  getchar();
	}
	ogm[i][0]=0;
	
	}
ogmnum=0;

//file in the ogm
while(remainnum!=0)
{
//judge if is smallest
for(i=0;i<=(remainnum-1);i++)
{
   
flag=0;
for(j=0;j<=(remainnum-1);j++)
flag=flag+ordm[remain[i]*filenum+remain[j]];

if(flag==0)
{ogm[ogmnum][ogm[ogmnum][0]+1]=remain[i];
ogm[ogmnum][0]++;
}

}

if(ogm[ogmnum][0]==0)
return NULL;
//process the remain array
for(i=0;i<=(ogm[ogmnum][0]-1);i++)
{
flag=0;
for(j=0;j<=(remainnum-2);j++)
{

if(remain[j]==ogm[ogmnum][i+1])
flag=1;

if(flag==1)
remain[j]=remain[j+1];


}

remainnum--;
}



ogmnum++;
}


//create the order graph array
if((oga=(int*)malloc(sizeof(int)*filenum))==NULL)
	{
	  printf("Memory is not sufficent.Creating order graph array fails.");
	  exit(0);
	  getchar();
	}

for(i=0;i<=ogmnum-1;i++)
for(j=1;j<=ogm[i][0];j++)
oga[ogm[i][j]]=i+1;

free(remain);
for(i=0;i<=filenum-1;i++)
free(ogm[i]);
free(ogm);
return oga;

}


int classify_graph_function(int* ordg,int filenum)//detect the type of graph,return int
                                      //1 monotonic decrease
									  //2 monotonic increase
									  //3 one convex peak 
									  //4 one concave peak
									  //5 mutiple peaks
{

	int flag;


flag=0;
flag=monotonic_decrease(ordg,filenum);
if(flag==1)
return 1;

flag=0;
flag=monotonic_increase(ordg,filenum);
if(flag==1)
return 2;

flag=0;
flag=one_convex_peak(ordg,filenum);
if(flag==1)
return 3;

flag=0;
flag=one_concave_peak(ordg,filenum);
if(flag==1)
return 4;

//flag=0;
//flag=mutiple_peaks(ordg,filenum);
//if(flag==1)
return 5;


}
int monotonic_decrease(int* ordg,int filenum)//1 for yes,0 for no
{
int i;
for(i=1;i<=filenum-1;i++)
if(ordg[i]>ordg[i-1])
return 0;

return 1;
}
int monotonic_increase(int* ordg,int filenum)//1 for yes,0 for no
{
int i;
for(i=1;i<=filenum-1;i++)
if(ordg[i]<ordg[i-1])
return 0;

return 1;

}
int one_convex_peak(int* ordg,int filenum)//1 for yes,0 for no
{
int i;
if(filenum<=2)
return 0;
if(ordg[1]<ordg[0])
return 0;
for(i=1;i<=filenum-1;i++)
if(ordg[i]<ordg[i-1])
break;
for(;i<=filenum-1;i++)
if(ordg[i]>ordg[i-1])
return 0;

return 1;

}
int one_concave_peak(int* ordg,int filenum)//1 for yes,0 for no
{
int i;
if(filenum<=2)
return 0;
if(ordg[1]>ordg[0])
return 0;
for(i=1;i<=filenum-1;i++)
if(ordg[i]>ordg[i-1])
break;
for(;i<=filenum-1;i++)
if(ordg[i]<ordg[i-1])
return 0;

return 1;



}
//int mutiple_peaks(int* ordg,int filenum)//1 for yes,0 for no
