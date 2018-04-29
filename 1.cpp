#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<ctime>
using namespace std;

#define BIG  100000000

void count(){
	long long res[1500];
	memset(res, 0, sizeof(res));
	char add1[5050], add2[5050];
	int len1=0, len2=0;
	char chr;
	int pre = 1;
	while(1){//readin
		chr = getchar();
		if(chr>='0' && chr<='9'){
			if(pre==1){
				add1[len1++] = chr;
			}
			else{
				add2[len2++] = chr;
			}
		}
		else if(chr == ' '){
			pre = 2;
		}
		else{
			break;
		}
	}
	
	if((len1 == 1 && add1[0] == '0') || (len2 == 1 && add2[0] == '0')){
		printf("0\n");
		return;
	}
	int l1 = len1/8, l2 = len2/8;
	long long nb1[700], nb2[700];
	memset(nb1, 0, sizeof(nb1));
	memset(nb2, 0, sizeof(nb2));
	if(len1%8!=0){
		l1++;
		for(int i=0; i<len1%8; ++i){
			nb1[l1-1] = nb1[l1-1]*10+add1[i]-'0';
		}
		pre = len1%8;
		for(int i=1; i<l1; ++i){
			for(int j=0; j<8; ++j){
				nb1[l1-1-i] = nb1[l1-1-i]*10 + add1[pre] - '0';
				pre++;
			}
		}
	}
	else{
		pre = 0;
		for(int i=1; i<=l1; ++i){
			for(int j=0; j<8; ++j){
				nb1[l1-i] = nb1[l1-i]*10 + add1[pre] - '0';
				pre++;
			}
		}
	}
	if(len2%8!=0){
		l2++;
		for(int i=0; i<len2%8; ++i){
			nb2[l2-1] = nb2[l2-1]*10+add2[i]-'0';
		}
		pre = len2%8;
		for(int i=1; i<l2; ++i){
			for(int j=0; j<8; ++j){
				nb2[l2-1-i] = nb2[l2-1-i]*10 + add2[pre] - '0';
				pre++;
			}
		}
	}
	else{
		pre = 0;
		for(int i=1; i<=l2; ++i){
			for(int j=0; j<8; ++j){
				nb2[l2-i] = nb2[l2-i]*10 + add2[pre] - '0';
				pre++;
			}
		}
	}
	
	for(int i=0; i<l1; ++i){
		for(int j=0; j<l2; ++j){
			res[i+j] += nb1[i]*nb2[j];
		}
	}
	for(int i=0; i<l1+l2-1; ++i){
		res[i+1] += res[i]/BIG;
		res[i] %= BIG;
	}
	
	pre = l1+l2-1;
	while(res[pre] == 0){
		pre--;
	}
	printf("%lld", res[pre]);
	pre--;
	while(pre>=0){
		printf("%.8lld", res[pre]);
		pre--;
	}
	printf("\n");
}

int main()
{
	setvbuf(stdin, new char [1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char [1 << 20], _IOFBF, 1 << 20);
	int num;
	scanf("%d",&num);
	getchar();
	for(int i=0;i<num;++i){
		count();
	}
	return 0;
}


