#include <stdio.h>  
  
#define maxn 10009001  
//#define maxn 9000001  
int prim[maxn];  
char isNotPrim[maxn] = {1, 1};  
int num=0, i, j;  
//__int64 sum;  
int main()  
{  
	freopen("prime.txt", "w", stdout);
    for(i=2; i<maxn; i++)  
    {  
        if(!isNotPrim[i])  
        {  
            prim[num++] = i;  
            //sum+=i;  
            printf("%d\n", i);  
        }  
        for(j=0; j<num && i*prim[j]<maxn; j++)  
        {  
            isNotPrim[i*prim[j]] = 1;  
            if(!(i%prim[j]))  
                break;  
        }  
    }  
//  printf("%I64d/n", sum);  
} 
