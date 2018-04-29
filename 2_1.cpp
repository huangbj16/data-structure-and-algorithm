//共2500个数， 每个10^9, 最大需要10^22500， 需要用unsigned long long 来做高精度乘法，压8位。 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;
typedef unsigned long long ull;

class LONG_NUMBER{
	public:
		int val;
		ull arr[4000];//8-bit-press 
		int len;
		void press();	
};

void LONG_NUMBER::press(){
	if(val < 100000000){
		arr[0] = val;
		len = 1;
	}
	else{
		arr[0] = val % 100000000;
		arr[1] = val / 100000000;
		len = 2;
	}
}

int N;
LONG_NUMBER lnum[3000];
ull res[50000];
int reslen;
int pos[4000];
int ls[4000], rs[4000], llen, rst, red;
ull temp[50000], temp1[4000], temp2[4000], temp3[4000];

void LNsort(int x, int y){
	//printf("l: %d, r: %d\n", x, y);
	if(x >= y) return;
	swap(lnum[x], lnum[x + rand()%(y-x+1)]);
	int l = x, r = y;
	int pre = l;
	int _val = lnum[l].val;
	LONG_NUMBER t = lnum[l]; 
	while(l < r){
		while(l < r){
			if(lnum[r].val <= _val)
				break;
			r--;
		}
		if(l < r){
			lnum[l] = lnum[r];
			l++;
		}
		while(l < r){
			if(lnum[l].val >= _val)
				break;
			l++;
		}
		if(l < r){
			lnum[r] = lnum[l];
			r--;
		}
	}
	int mid = (l+r)/2;
	lnum[mid] = t;
	LNsort(x, mid-1);
	LNsort(mid+1, y);
}

void Multi(int p1, int p2){
	int totlen = lnum[p1].len + lnum[p2].len;
	int l1 = lnum[p1].len;
	int l2 = lnum[p2].len;
	//ull *temp = new ull[totlen];
	memset(temp, 0, totlen*sizeof(ull));
	
	//算法核心，高精度乘法 
	for(int i=0; i<l1; ++i){
		for(int j=0; j<l2; ++j){
			temp[i+j] += lnum[p1].arr[i] * lnum[p2].arr[j];
		}
	}
	
	//进位
	for(int i=0; i<l1+l2-1; ++i){
		temp[i+1] += temp[i]/100000000;
		lnum[p1].arr[i] = temp[i]%100000000;
	}
	if(temp[l1+l2-1] != 0){
		lnum[p1].arr[l1+l2-1] = temp[l1+l2-1];
		lnum[p1].len = l1 + l2;
	}
	else{
		lnum[p1].len = l1 + l2 - 1;
	}
	//delete []temp;
}

void MultiRes(int p){
	int totlen = reslen + lnum[p].len + 1;
	int l1 = reslen;
	int l2 = lnum[p].len;
	//ull *temp = new ull[totlen];
	memset(temp, 0, totlen*sizeof(ull));
	
	//算法核心，高精度乘法 
	for(int i=0; i<l1; ++i){
		for(int j=0; j<l2; ++j){
			temp[i+j] += res[i] * lnum[p].arr[j];
			temp[i+j+1] += temp[i+j] / 100000000;
			temp[i+j] %= 100000000;
		}
	}
	
	//进位
	for(int i=0; i<l1+l2-1; ++i){
		res[i] = temp[i];
	}
	if(temp[l1+l2-1] != 0){
		res[l1+l2-1] = temp[l1+l2-1];
		reslen = l1 + l2;
	}
	else{
		reslen = l1 + l2 - 1;
	}
	/* 
	//算法核心，高精度乘法 
	for(int i=0; i<l1; ++i){
		for(int j=0; j<l2; ++j){
			temp[i+j] += res[i] * lnum[p].arr[j];
		}
	}
	
	//进位
	for(int i=0; i<l1+l2-1; ++i){
		temp[i+1] += temp[i]/100000000;
		res[i] = temp[i]%100000000;
	}
	if(temp[l1+l2-1] != 0){
		res[l1+l2-1] = temp[l1+l2-1];
		reslen = l1 + l2;
	}
	else{
		reslen = l1 + l2 - 1;
	}
	//delete []temp;
	*/
}

bool Smaller12(){
	if(!(llen > 0 && red-rst > 0)){//2不存在 
		return true;
	}
	else if(!(llen > 1)){//1不存在 
		return false;
	}
	else{
		int len1, len2;
		len1 = lnum[ls[llen-1]].len + lnum[ls[llen-2]].len;
		len2 = lnum[ls[llen-1]].len + lnum[rs[rst]].len;
		//是否可以通过位数判断 
		if(len1 < len2-1){
			return true;
		}		
		if(len2 < len1-1){
			return false;
		}
		//不行则需计算 
		memset(temp1, 0, len1*sizeof(ull));
		memset(temp2, 0, len2*sizeof(ull));
		
		int l1, l2, l3;
		l1 = lnum[ls[llen-1]].len;
		l2 = lnum[ls[llen-2]].len;
		l3 = lnum[rs[rst]].len;
		
		for(int i=0; i<l1; ++i){
			for(int j=0; j<l2; ++j){
				temp1[i+j] += lnum[ls[llen-1]].arr[i] * lnum[ls[llen-2]].arr[j];
			}
		}
		for(int i=0; i<l1+l2-1; ++i){
			temp1[i+1] += temp1[i]/100000000;
			temp1[i] %= 100000000;
		}
		if(temp1[l1+l2-1] != 0){
			len1 = l1 + l2;
		}
		else{
			len1 = l1 + l2 - 1;
		}
		
		for(int i=0; i<l1; ++i){
			for(int j=0; j<l3; ++j){
				temp2[i+j] += lnum[ls[llen-1]].arr[i] * lnum[rs[rst]].arr[j];
			}
		}
		for(int i=0; i<l1+l3-1; ++i){
			temp2[i+1] += temp2[i]/100000000;
			temp2[i] %= 100000000;
		}
		if(temp2[l1+l3-1] != 0){
			len2 = l1 + l3;
		}
		else{
			len2 = l1 + l3 - 1;
		}
		//是否可以通过位数判断 
		if(len1 < len2){
			return true;
		}
		else if(len2 < len1){
			return false;
		}
		else{//不能，则做对比 
			for(int i= len1-1; i>=0; ++i){
				if(temp1[i] < temp2[i]){
					return true;
				}
				else if(temp2[i] < temp1[i]){
					return false;
				}
			}
			return true;//二者真的一样大，返回谁都一样 
		}
	}
}
bool Smaller13(){
	if(!(red-rst > 1)){//3不存在 
		return true;
	}
	else if(!(llen > 1)){//1不存在 
		return false;
	}
	else{
		int len1, len3;
		len1 = lnum[ls[llen-1]].len + lnum[ls[llen-2]].len;
		len3 = lnum[rs[rst]].len + lnum[rs[rst+1]].len;
		//是否可以通过位数判断 
		if(len1 < len3-1){
			return true;
		}		
		if(len3 < len1-1){
			return false;
		}
		//不行则需计算 
		memset(temp1, 0, len1*sizeof(ull));
		memset(temp3, 0, len3*sizeof(ull));
		
		int l1, l2, l3, l4;
		l1 = lnum[ls[llen-1]].len;
		l2 = lnum[ls[llen-2]].len;
		l3 = lnum[rs[rst]].len;
		l4 = lnum[rs[rst+1]].len;
		
		for(int i=0; i<l1; ++i){
			for(int j=0; j<l2; ++j){
				temp1[i+j] += lnum[ls[llen-1]].arr[i] * lnum[ls[llen-2]].arr[j];
			}
		}
		for(int i=0; i<l1+l2-1; ++i){
			temp1[i+1] += temp1[i]/100000000;
			temp1[i] %= 100000000;
		}
		if(temp1[l1+l2-1] != 0){
			len1 = l1 + l2;
		}
		else{
			len1 = l1 + l2 - 1;
		}
		
		for(int i=0; i<l3; ++i){
			for(int j=0; j<l4; ++j){
				temp3[i+j] += lnum[rs[rst]].arr[i] * lnum[rs[rst+1]].arr[j];
			}
		}
		for(int i=0; i<l3+l4-1; ++i){
			temp3[i+1] += temp3[i]/100000000;
			temp3[i] %= 100000000;
		}
		if(temp3[l3+l4-1] != 0){
			len3 = l3 + l4;
		}
		else{
			len3 = l3 + l4 - 1;
		}
		//是否可以通过位数判断 
		if(len1 < len3){
			return true;
		}
		else if(len3 < len1){
			return false;
		}
		else{//不能，则做对比 
			for(int i= len1-1; i>=0; ++i){
				if(temp1[i] < temp3[i]){
					return true;
				}
				else if(temp3[i] < temp1[i]){
					return false;
				}
			}
			return false;//二者真的一样大，返回谁都一样 
		}
	}
}

bool Smaller23(){
	if(!(red-rst > 1)){//3不存在 
		return true;
	}
	else if(!(llen > 0 && red-rst > 0)){//2不存在 
		return false;
	}
	else{
		int len2, len3;
		len2 = lnum[ls[llen-1]].len + lnum[rs[rst]].len;
		len3 = lnum[rs[rst]].len + lnum[rs[rst+1]].len;
		//是否可以通过位数判断 
		if(len2 < len3-1){
			return true;
		}		
		if(len3 < len2-1){
			return false;
		}
		//不行则需计算 
		memset(temp2, 0, len2*sizeof(ull));
		memset(temp3, 0, len3*sizeof(ull));
		
		int l1, l3, l4;
		l1 = lnum[ls[llen-1]].len;
		l3 = lnum[rs[rst]].len;
		l4 = lnum[rs[rst+1]].len;
		
		for(int i=0; i<l1; ++i){
			for(int j=0; j<l3; ++j){
				temp2[i+j] += lnum[ls[llen-1]].arr[i] * lnum[rs[rst]].arr[j];
			}
		}
		for(int i=0; i<l1+l3-1; ++i){
			temp2[i+1] += temp2[i]/100000000;
			temp2[i] %= 100000000;
		}
		if(temp2[l1+l3-1] != 0){
			len2 = l1 + l3;
		}
		else{
			len2 = l1 + l3 - 1;
		}
		
		for(int i=0; i<l3; ++i){
			for(int j=0; j<l4; ++j){
				temp3[i+j] += lnum[rs[rst]].arr[i] * lnum[rs[rst+1]].arr[j];
			}
		}
		for(int i=0; i<l3+l4-1; ++i){
			temp3[i+1] += temp3[i]/100000000;
			temp3[i] %= 100000000;
		}
		if(temp3[l3+l4-1] != 0){
			len3 = l3 + l4;
		}
		else{
			len3 = l3 + l4 - 1;
		}
		//是否可以通过位数判断 
		if(len2 < len3){
			return true;
		}
		else if(len3 < len2){
			return false;
		}
		else{//不能，则做对比 
			for(int i= len2-1; i>=0; ++i){
				if(temp2[i] < temp3[i]){
					return true;
				}
				else if(temp3[i] < temp2[i]){
					return false;
				}
			}
			return true;//二者真的一样大，返回谁都一样 
		}
	}
}


int FindSmall(){
	//printf("findsmall: %d %d %d\n",llen, rst, red);
	if(Smaller12()){
		if(Smaller13()){
			return 1;
		}
		else{
			return 3;
		}
	}
	else{
		if(Smaller23()){
			return 2;
		}
		else{
			return 3;
		}
	}
}



void Huffman(){
	while(llen+red-rst >= 2){//两边加起来不小于2 
		int flag = FindSmall();
		//printf("flag:%d\n",flag);
		if(flag == 1){
			Multi(ls[llen-2], ls[llen-1]); 
			MultiRes(ls[llen-2]);
			llen -= 2;
			rs[red++] = ls[llen]; 
		}
		else if(flag == 2){
			Multi(ls[llen-1], rs[rst]); 
			MultiRes(ls[llen-1]);
			llen--;
			rst++;
			rs[red++] = ls[llen];
		}	
		else{//flag == 3
			Multi(rs[rst], rs[rst+1]); 
			MultiRes(rs[rst]);
			rs[red++] = rs[rst];
			rst += 2;
		}
		/*
		printf("res: ");
		for(int i=reslen-1; i>=0; --i){
			printf("%llu ",res[i]);
		}
		printf("\n");
		for(int i=0; i<N; ++i){
			printf("lnum[%d]: ", i);
			for(int j=lnum[i].len-1; j>=0; --j){
				printf("%llu ", lnum[i].arr[j]);
			}
			printf("\n");
		}
		*/
	}
	
	printf("%llu", res[reslen-1]);
	for(int i=reslen-2; i>=0; --i){
		printf("%08llu", res[i]);
	}
}

int main()
{
	//freopen("in1.txt", "r", stdin);
	//freopen("out1.txt", "w", stdout);
	//setvbuf(stdin, new char [1 << 20], _IOFBF, 1 << 20);
	//setvbuf(stdout, new char [1 << 20], _IOFBF, 1 << 20);
	
	srand((unsigned)time(NULL));
	cin>>N;
	if(N == 0){
		printf("0\n");
		return 0;
	}
	for(int i=0; i<N; ++i){
		scanf("%d",&lnum[i].val);
		lnum[i].press();
	}
	//////initial 
	memset(res, 0, sizeof(res));
	res[0] = 1;
	reslen = 1;
	llen = N;
	rst = 0;
	red = 0;
	//////
	for(int i=0; i<N; ++i){
		ls[i] = N-i-1;
	}
	/*
	for(int i=0; i<N; ++i){
		printf("%d ", lnum[i].val);
		printf("%llu", lnum[i].arr[0]);
		printf("\n");
	}
	*/
	//printf("1\n");
	LNsort(0, N-1);
	//printf("1\n");
	/*
	for(int i=0; i<N; ++i){
		printf("%d ", lnum[i].val);
		printf("%llu %llu", lnum[i].arr[0], lnum[i].arr[1]);
		printf("\n");
	}
	*/
	
	Huffman();
	
	return 0;
}

