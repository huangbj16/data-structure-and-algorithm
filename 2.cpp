#include<iostream>
#include<cstdio>
using namespace std;

int lx[200020], ly[200020];
int n,m;
int px[200020], py[200020];

void xsort(int x, int y){
	//printf("l: %d, r: %d\n", x, y);
	if(x >= y) return;
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
	xsort(x, mid-1);
	xsort(mid+1, y);
}

void ysort(int x, int y){
	//printf("l: %d, r: %d\n", x, y);
	if(x >= y) return;
	int l = x, r = y;
	int pre = l;
	int val = ly[l];
	while(l < r){
		while(l < r){
			if(ly[r] < val)
				break;
			r--;
		}
		if(l < r){
			ly[l] = ly[r];
			l++;
		}
		while(l < r){
			if(ly[l] > val)
				break;
			l++;
		}
		if(l < r){
			ly[r] = ly[l];
			r--;
		}
	}
	int mid = (l+r)>>1;
	ly[mid] = val;
	ysort(x, mid-1);
	ysort(mid+1, y);
}

bool cross(long long x1, long long y1, long long x2, long long y2){
	long long left =  x1*y2 + y1*x2;
	long long right = x2*y2;
	return left >= right;
}

void count(int x, int y, int l, int r){
	while(l < r){
		int mid = (l+r)>>1;
		cross(x, y, lx[mid], ly[mid]) ? l = mid+1 : r = mid;
	}
	printf("%d\n", l);
}

int main()
{
	/*
	freopen("in2.txt", "r", stdin);
	freopen("out2.txt", "w", stdout);
	*/
	scanf("%d", &n);
	for(int i=0; i<n; ++i){
		scanf("%d", &lx[i]);
	}
	for(int i=0; i<n; ++i){
		scanf("%d", &ly[i]);
	}
	
	scanf("%d", &m);
	for(int i=0; i<m; ++i){
		scanf("%d %d", &px[i], &py[i]);
	}
	
	xsort(0, n-1);
	ysort(0, n-1);
	/*
	for(int i=0; i<n; ++i){
		printf("%d ", lx[i]);
	}
	printf("\n"); 
	for(int i=0; i<n; ++i){
		printf("%d ", ly[i]);
	}
	*/
	for(int i=0; i<m; ++i){
		count(px[i], py[i], 0, n);
	}
	return 0;
}

