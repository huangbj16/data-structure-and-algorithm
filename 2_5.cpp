#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

struct Order{
	int o;
	int x, y;
};

int cntx[2200000], cnty[2200000];
Order ord[1000100];
int n;
int N = 1048576;//2^20
int arrx[1000100], arry[1000100];
int arrlen = 0;
int curlen = 0;

void quicksort(int *lx, int x, int y){
	//printf("l: %d, r: %d\n", x, y);
	if(x >= y) return;
	swap(lx[x], lx[x + rand()%(y-x+1)]);
	int l = x, r = y;
	int pre = l;
	int val = lx[l];
	while(l < r){
		while(l < r){
			if(lx[r] < val)
				break;
			r--;
		}
		if(l < r){
			lx[l] = lx[r];
			l++;
		}
		while(l < r){
			if(lx[l] > val)
				break;
			l++;
		}
		if(l < r){
			lx[r] = lx[l];
			r--;
		}
	}
	int mid = (l+r)/2;
	lx[mid] = val;
	quicksort(lx, x, mid-1);
	quicksort(lx, mid+1, y);
}

int find(int *arr, int val){
	int l = 0, r = arrlen, mid;
	while(l < r){
		mid = (l+r)>>1;
		val < arr[mid] ? r = mid : l = mid + 1;
	}
	return --l;
}

void add(int *cnt, int pos){
	while(pos != 0){
		cnt[pos] ++;
		pos >>= 1;
	}
}

void del(int *arr, int *cnt, int pos){
	int p = 1;
	int cnt1, cnt2;
	while(p < N){
		cnt[p] --;
		cnt1 = arr[2*p];
		cnt2 = arr[2*p+1];
		if(pos > cnt1){
			pos -= cnt1;
			p = p*2 + 1;
		}
		else{
			p *= 2;
		}
	}
	cnt[p]--;
}

bool cross(long long x1, long long y1, long long x2, long long y2){
	long long left =  x1*y2 + y1*x2;
	long long right = x2*y2;
	return left >= right;
}

int findcount(int *cnt, int rank){
	int p = 1;
	int cnt1, cnt2;
	while(p < N){
		cnt1 = cnt[2*p];
		cnt2 = cnt[2*p+1];
		if(cnt1 < rank){
			p = p*2+1;
			rank -= cnt1;
		}
		else{
			p = p*2;
		}
	}
	return p;
}

void count(int px, int py){
	int l = 0, r = curlen, mid, x, y;
	while(l < r){
		mid = (l+r)>>1;
		x = arrx[N+findcount(cntx, mid)];
		y = arry[N+findcount(cnty, mid)];
		
		cross(px, py, x, y) ? l = mid+1 : r = mid;
	}
}

int main()
{
	freopen("in5.txt", "r", stdin);
	
	memset(cntx, 0, sizeof(cntx));
	memset(cnty, 0, sizeof(cnty));
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		scanf("%d %d %d",&ord[i].o, &ord[i].x, &ord[i].y);
		if(ord[i].o == 0){
			arrx[arrlen] = ord[i].x;
			arry[arrlen] = ord[i].y;
			arrlen++;
		}
	}
	
	quicksort(arrx, 0, arrlen-1);
	quicksort(arry, 0, arrlen-1);
	/*
	for(int i=0; i<arrlen; ++i){
		printf("%d ", arrx[i]);
	}
	printf("\n");
	for(int i=0; i<arrlen; ++i){
		printf("%d ", arry[i]);
	}
	printf("\n");
	*/
	
	for(int i=0; i<n; ++i){
		switch(ord[i].o){
			case 0:
				int x = find(arrx, ord[i].x);
				int y = find(arry, ord[i].y);
				add(cntx, N+x);
				add(cnty, N+y);
				curlen ++;
			break;
			case 1:
				count(ord[i].x, ord[i].y);
			break;
			case 2:
				del(arrx, cntx, ord[i].x);
				del(arry, cnty, ord[i].y);
				curlen --;
			break;
		}
	}
	return 0;
}

