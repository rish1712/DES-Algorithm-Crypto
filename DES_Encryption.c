#include<stdio.h>
// Values to be used in Q3: 1/16th DES
int sub[32];
  int PC1[56] = {
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
  };

  int PC2[48] = {
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
  };

  int IP[64] = {
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7};

  int Expansion[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,
     6,  7,  8,  9,  8,  9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32,  1};

  int SBox[8][4][16] = {
     {
     {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
     { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
     { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
     {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
     },

     {
     {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
     { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
     { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
     {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
     },

     {
     {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
     {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
     {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
     { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
     },

     {
     { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
     {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
     {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
     { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
     },

     {
     { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
     {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
     { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
     {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
     },

     {
     {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
     {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
     { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
     { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
     },

     {
     { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
     {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
     { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
     { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
     },

     {
     {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
     { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
     { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
     { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
     },};

  int PBox[32] = {
      16,  7, 20, 21, 29, 12, 28, 17,
       1, 15, 23, 26,  5, 18, 31, 10,
       2,  8, 24, 14, 32, 27,  3,  9,
      19, 13, 30,  6, 22, 11,  4, 25
  };
  int shifttable[16]=
    {    1, 1, 2, 2,
        2, 2, 2, 2,
        1, 2, 2, 2,
        2, 2, 2, 1
    };
void hextobit(char c[],int l[])
{
  int i=0;
  int j=0;
  //printf("gibreis");
  for(int k=0;k<16;k++){
  if(c[k]=='0')
  {
    l[j++]=0;
    l[j++]=0;
    l[j++]=0;
    l[j++]=0;
  }
  if(c[k]=='1')
  {
    l[j++]=0;
    l[j++]=0;
    l[j++]=0;
    l[j++]=1;
  }
  if(c[k]=='2')
  {
    l[j++]=0;
    l[j++]=0;
    l[j++]=1;
    l[j++]=0;
  }
  if(c[k]=='3')
  {
    l[j++]=0;
    l[j++]=0;
    l[j++]=1;
    l[j++]=1;
  }
  if(c[k]=='4')
  {
    l[j++]=0;
    l[j++]=1;
    l[j++]=0;
    l[j++]=0;
  }
  if(c[k]=='5')
  {
    l[j++]=0;
    l[j++]=1;
    l[j++]=0;
    l[j++]=1;
  }
  if(c[k]=='6')
  {
    l[j++]=0;
    l[j++]=1;
    l[j++]=1;
    l[j++]=0;
  }
  if(c[k]=='7')
  {
    l[j++]=0;
    l[j++]=1;
    l[j++]=1;
    l[j++]=1;
  }
  if(c[k]=='8')
  {
    l[j++]=1;
    l[j++]=0;
    l[j++]=0;
    l[j++]=0;
  }
  if(c[k]=='9')
  {
    l[j++]=1;
    l[j++]=0;
    l[j++]=0;
    l[j++]=1;
  }
  if(c[k]=='A')
  {
    l[j++]=1;
    l[j++]=0;
    l[j++]=1;
    l[j++]=0;
  }
  if(c[k]=='B')
  {
    l[j++]=1;
    l[j++]=0;
    l[j++]=1;
    l[j++]=1;
  }
  if(c[k]=='C')
  {
    l[j++]=1;
    l[j++]=1;
    l[j++]=0;
    l[j++]=0;
  }
  if(c[k]=='D')
  {
    l[j++]=1;
    l[j++]=1;
    l[j++]=0;
    l[j++]=1;
  }
  if(c[k]=='E')
  {
    l[j++]=1;
    l[j++]=1;
    l[j++]=1;
    l[j++]=0;
  }
  if(c[k]=='F')
  {
    l[j++]=1;
    l[j++]=1;
    l[j++]=1;
    l[j++]=1;
  }}
}
void leftshift(int c[],int d[],int j)
{
  int shift=shifttable[j];
  int x;
  int y;
  for(int k=0;k<shift;k++)
  {
    x=c[0];
    y=d[0];
    for(int i=1;i<28;i++)
    {
      c[i-1]=c[i];
      d[i-1]=d[i];
    }
    c[27]=x;
    d[27]=y;
  }
  /*for(int i=0;i<28;i++)
  {
    printf("%d",c[i]);
  }
  printf("\n");
  for(int i=0;i<28;i++)
  {
    //printf("\n");
    printf("%d",d[i]);
  //  printf("\n");
  }
  printf("\nNEXT\n");*/
}
char binary(int a[],int i)
{
  int x=8*a[i]+4*a[i+1]+2*a[i+2]+a[i+3];
  if(x==0)
    return '0';
  if(x==1)
    return '1';
  if(x==2)
    return '2';
  if(x==3)
    return '3';
  if(x==4)
    return '4';
  if(x==5)
    return '5';
  if(x==6)
    return '6';
  if(x==7)
    return '7';
  if(x==8)
    return '8';
  if(x==9)
    return '9';
  if(x==10)
    return 'A';
  if(x==11)
    return 'B';
  if(x==12)
    return 'C';
  if(x==13)
    return 'D';
  if(x==14)
    return 'E';
  if(x==15)
    return 'F';
}
int main()
{
  char k[100];
  char pt[100];
  int bitkey[64];
  int bitpt[64];
  char roundkey1[16];
  scanf("%s",pt);
  scanf("%s",k);
  //printf("%s",pt);
  hextobit(k,bitkey);
  hextobit(pt,bitpt);
  int kl=0;
  /*for(int i=0;i<64;i++)
  {
    kl++;
    printf("bitkey=%d,i=%d\n",bitpt[i],i);
    if(kl==4)
    {
      printf("\n" );
      kl=0;
    }
  }*/
   kl=0;
  int actualkey[56];
  char roundkey[16];
  for(int i=0;i<56;i++)
  {
      actualkey[kl++]=bitkey[PC1[i]-1];
  }
  for(int i=0;i<56;i++)
  {
      //actualkey[kl++]=bitkey[PC1[i]];
      //printf("%d\n",actualkey[i]);
  }
  kl=0;
  int c[28],d[28],e[56],f[48];
  for(int i=0;i<28;i++)
  {
    c[i]=actualkey[i];
    d[i]=actualkey[28+i];
  }
/*  for(int i=0;i<28;i++)
  {
    kl++;
    //printf("%d",d[i]);
    if(kl%7==0)
    {
      //printf("\n");
    }
  }*/
  kl=0;
  int gl=0;
  for(int i=0;i<16;i++)
  {
    gl++;
    leftshift(c,d,i);
    //printf("gibreissh");
    for(int j=0;j<28;j++)
    {
      e[j]=c[j];
      //printf("%d\n",e[j] );
      e[28+j]=d[j];
    }
  //  printf("gibreish");
    /*for(int i=0;i<28;i++)
    {
      kl++;
      //printf("%d",e[i]);
      if(kl%7==0)
        //printf("\n");
    }*/
    kl=0;
    for(int q=0;q<48;q++)
    {
        f[kl++]=e[PC2[q]-1];
    }
    kl=0;
    for(int i=0;i<48;i=i+4)
    {
      roundkey[kl++]=binary(f,i);
    }
    kl=0;
    if(gl==1)
    {
      for(int i=0;i<12;i++)
      {
        roundkey1[i]=roundkey[i];
      }
    }
    for(int i=0;i<12;i++)
    {
      printf("%c",roundkey[i]);
    }
    printf("\n");
  }
  /*for(int i=0;i<16;i++)
  {
    printf("%c",roundkey1[i]);
  }*/
  int ippt[64];
  kl=0;
  for(int i=0;i<64;i++)
  {
    ippt[kl++]=bitpt[IP[i]-1];
  }
  kl=0;
  /*for(int i=0;i<64;i++)
  {
      kl++;
      //actualkey[kl++]=bitkey[PC1[i]];
      printf("%d",ippt[i]);
      if(kl%4==0)
      printf(" ");
  }*/
  int l[32],r[32];
  for(int i=0;i<32;i++)
  {
    l[i]=ippt[i];
    r[i]=ippt[32+i];
  }
  /*for(int i=0;i<32;i++)
  {
    kl++;
    printf("%d",r[i]);
    if(kl%4==0)
    printf(" ");
  }*/
  int l1[32];
  for(int i=0;i<32;i++)
  {
    l1[i]=r[i];
  }
  /*for(int i=0;i<32;i++)
  {
    kl++;
    printf("%d",l1[i]);
    if(kl%4==0)
    printf(" ");
  }*/
  kl=0;
  int expan[48];
  for(int i=0;i<48;i++)
  {
    expan[kl++]=r[Expansion[i]-1];
  }
  kl=0;
  /*for(int i=0;i<48;i++)
  {
    kl++;
    printf("%d",expan[i]);
    if(kl%6==0)
    printf(" ");
  }*/
  int k1[48];
  int zor[48];
  hextobit(roundkey1,k1);
  for(int i=0;i<48;i++)
  {
    zor[i]=expan[i]^k1[i];
  }
  kl=0;
  /*for(int i=0;i<48;i++)
  {
    kl++;
    printf("%d",zor[i]);
    if(kl%6==0)
    printf(" ");
  }*/
  kl=0;
  int b[8][6];
  int o;
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<6;j++)
    {
      b[i][j]=zor[kl++];
    }
  }
  int row,col;
  kl=0;
  for(int i=0;i<8;i++)
  {
    row=2*b[i][0]+b[i][5];
    col=8*b[i][1]+4*b[i][2]+2*b[i][3]+b[i][4];
    o=SBox[i][row][col];
    if(o==0)
    {
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=0;
    }
    if(o==1)
    {
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=1;
    }
    if(o==2)
    {
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=0;
    }
    if(o==3)
    {
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=1;
    }
    if(o==4)
    {
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=0;
    }
    if(o==5)
    {
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=1;
    }
    if(o==6)
    {
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=0;
    }
    if(o==7)
    {
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=1;
    }
    if(o==8)
    {
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=0;
    }
    if(o==9)
    {
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=0;
      sub[kl++]=1;
    }
    if(o==10)
    {
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=0;
    }
    if(o==11)
    {
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=1;
      sub[kl++]=1;
    }
    if(o==12)
    {
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=0;
    }
    if(o==13)
    {
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=0;
      sub[kl++]=1;
    }
    if(o==14)
    {
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=0;
    }
    if(o==15)
    {
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=1;
      sub[kl++]=1;
    }
  }
  kl=0;
  /*for(int i=0;i<32;i++)
  {
    kl++;
    printf("%d",sub[i] );
    if(kl%4==0)
    {
      printf(" ");
    }
  }*/
  for(int i=0;i<32;i++)
  {
    r[i]=sub[PBox[i]-1];
  }
  /*for(int i=0;i<32;i++)
  {
    kl++;
    printf("%d",r[i] );
    if(kl%4==0)
    {
      printf(" ");
    }
  }*/
  for(int i=0;i<32;i++)
  {
    l[i]=l[i]^r[i];
  }
  /*for(int i=0;i<32;i++)
  {
    kl++;
    printf("%d",l[i] );
    if(kl%4==0)
    {
      printf(" ");
    }
  }*/
//  printf("\n");
  for(int i=0;i<64;i++)
  {
    ippt[i]=l1[i];
    ippt[32+i]=l[i];
  }

  char encrypt[16];
  kl=0;
  for(int i=0;i<32;i=i+4)
  {
      encrypt[kl++]=binary(l1,i);
  }
  for(int i=0;i<32;i=i+4)
  {
      encrypt[kl++]=binary(l,i);
  }
  for(int i=0;i<16;i++)
  {
    printf("%c",encrypt[i]);
  }
//  printf("\n");
}
