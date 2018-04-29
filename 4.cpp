#include<iostream>
#include<cstdio>
using namespace std;

int stock[1000010], pos[1000010], head=1, tail=1, outcnt = 0, incnt = 0;
long long tot = 0;


int main()
{
	//freopen("in4.txt", "r", stdin);
	setvbuf(stdin, new char [1 << 25], _IOFBF, 1 << 25);
	setvbuf(stdout, new char [1 << 25], _IOFBF, 1 << 25);
	
	int n;
	scanf("%d",&n);
	getchar();
	n = n*2;
	stock[0] = 0;
	stock[1] = 0;
	bool flag;
	int daylen, price;
	char c;
	while(n>0){
		flag = false;
		daylen = 0;
		price = 0;
		////////////////////input
		while(1){
			c = getchar();
			if(c>='0' && c<='9')
				daylen = daylen*10+c-'0';
			else
				break;
		}
		if(c == ' '){
			while(1){
				c = getchar();
				if('0'<=c && c<='9')
					price = price*10+c-'0';
				else
					break;
			}
		}
		////////////////////input
		//printf("dyalen: %d price: %d\n", daylen, price);
		
		tot += (long long)(stock[tail])*(long long)(daylen);
		//printf("bigprice: %d, daylen: %d\n", bigprice, daylen);
		if(price != 0){//stock in
			incnt++; 
			while(head > tail && stock[head-1] <= price){
				head--;
			}
			stock[head] = price;
			pos[head] = incnt;
			head++;
		}
		else{//stock out
			outcnt++;
			if(outcnt == pos[tail]){
				tail++;
			}
		}
		/*
		printf("stock: ");
		for(int i=tail; i<head; ++i){
			printf("%d ", stock[i]);
		}
		printf("\n");
		printf("incnt: %d outcnt: %d\n", incnt, outcnt);
		printf("head: %d tail: %d pos[tail]: %d\n\n", head, tail, pos[tail]);
		*/
		/*
		for(int i=tail; i<head; ++i)
			printf("%d ",stock[i]);
		printf("\n");
		printf("%d %d\n",tail, head);
		printf("400: %d\n", stock[2]);
		printf("%d %d\n",bigprice, bigpos);
		*/
		--n;
	}
	printf("%lld\n", tot);
	return 0;
}

