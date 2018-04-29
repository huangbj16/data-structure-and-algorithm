//#include "sort.h"
#include<cstdio>
#include <cstdlib>

int *A, *a, n, limit, cmp_cnt = 0;

inline void swap(int &a, int &b) {
	int t = a;
	a = b, b = t;
}

void Print(){
	printf("a[] = ");
	for(int i=0; i<n; ++i){
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("A[] = ");
	for(int i=0; i<n; ++i){
		printf("%d ", A[a[i]]);
	}
	printf("\n");
}

void Print2(int l, int r){
	printf("Print2: l: %d, r: %d\n", l, r);
}

void compare(int a, int b, int c, int *max, int *min) {
	printf("compare: a:%d b:%d c:%d\n", a, b, c);
	if (++cmp_cnt > limit) {
		printf("Wrong Answer --- exceeded limit\n");
		//exit(0);
	}
	
	if (a < 0 || a >= n || b < 0 || b >= n || c < 0 || c >= n) {
		printf("Wrong Answer --- invalid parameters\n");
		//exit(0);
	}
	
	if (A[a] > A[b]) swap(a, b);
	*max = A[b] > A[c] ? b : c;
	*min = A[a] < A[c] ? a : c;
}

void merge(int l, int r, int *a){
	int mid[3];
	mid[1] = (l+r)/2;
	mid[0] = (l+mid[1])/2;
	mid[2] = (mid[1]+r)/2;
	
	int len[5], rank[5]={0,0,0,0,0};
	len[1] = mid[0]-l;
	len[2] = mid[1]-mid[0];
	len[3] = mid[2]-mid[1];
	len[4] = r-mid[2];
	
	
	int *a1 = new int [len[1]];
	int *a2 = new int [len[2]];
	int *a3 = new int [len[3]];
	int *a4 = new int [len[4]];
	for(int i=l; i<mid[0]; ++i){
		a1[i-l] = a[i];
	}
	for(int i=mid[0]; i<mid[1]; ++i){
		a2[i-mid[0]] = a[i];
	}
	for(int i=mid[1]; i<mid[2]; ++i){
		a3[i-mid[1]] = a[i];
	}
	for(int i=mid[2]; i<r; ++i){
		a4[i-mid[2]] = a[i];
	}
	
	int i,j;
	for(i=l; rank[1]<len[1] + rank[2]<len[2] + rank[3]<len[3] + rank[4]<len[4] == 0;){//四路归并 
		int max, min;	
		compare(a1[rank[1]], a2[rank[2]], a3[rank[3]], &max, &min);
		compare(max, a4[rank[4]], a4[rank[4]], &max, &min);
		if(max == a1[rank[1]])
			a[l++] = a1[rank[1]++];
		if(max == a2[rank[2]])
			a[l++] = a2[rank[2]++];
		if(max == a3[rank[3]])
			a[l++] = a3[rank[3]++];
		if(max == a4[rank[4]])
			a[l++] = a4[rank[4]++];
	}
	for(; rank[1]<len[1] + rank[2]<len[2] + rank[3]<len[3] + rank[4]<len[4] == 1;){//三路归并
		int max, min;
		if(rank[1] == len[1])
			compare(a2[rank[2]], a3[rank[3]], a4[rank[4]], &max, &min);
		else if(rank[2] == len[2])
			compare(a1[rank[1]], a3[rank[3]], a4[rank[4]], &max, &min);
		else if(rank[3] == len[3])
			compare(a1[rank[1]], a2[rank[2]], a4[rank[4]], &max, &min);
		else
			compare(a1[rank[1]], a2[rank[2]], a3[rank[3]], &max, &min);
		if(max == a1[rank[1]])
			a[l++] = a1[rank[1]++];
		if(max == a2[rank[2]])
			a[l++] = a2[rank[2]++];
		if(max == a3[rank[3]])
			a[l++] = a3[rank[3]++];
		if(max == a4[rank[4]])
			a[l++] = a4[rank[4]++];
	}
	for(; rank[1]<len[1] + rank[2]<len[2] + rank[3]<len[3] + rank[4]<len[4] == 2;){//二路归并
		int max, min;
		if(rank[1] == len[1] && rank[2] == len[2])
			compare(a3[rank[3]], a4[rank[4]], a4[rank[4]], &max, &min);
		else if(rank[1] == len[1] && rank[3] == len[3])
			compare(a2[rank[2]], a4[rank[4]], a4[rank[4]], &max, &min);
		else if(rank[1] == len[1] && rank[4] == len[4])
			compare(a2[rank[2]], a3[rank[3]], a3[rank[3]], &max, &min);
		else if(rank[2] == len[2] && rank[3] == len[3])
			compare(a1[rank[1]], a4[rank[4]], a4[rank[4]], &max, &min);
		else if(rank[2] == len[2] && rank[4] == len[4])
			compare(a1[rank[1]], a3[rank[3]], a3[rank[3]], &max, &min);
		else
			compare(a1[rank[1]], a2[rank[2]], a2[rank[2]], &max, &min);
			
		if(max == a1[rank[1]])
			a[l++] = a1[rank[1]++];
		if(max == a2[rank[2]])
			a[l++] = a2[rank[2]++];
		if(max == a3[rank[3]])
			a[l++] = a3[rank[3]++];
		if(max == a4[rank[4]])
			a[l++] = a4[rank[4]++];
	}
	for(; rank[1]<len[1] + rank[2]<len[2] + rank[3]<len[3] + rank[4]<len[4] == 3;){//一路归并
		while(rank[1]<len[1]){
			a[l++] = a1[rank[1]++];
		}
		while(rank[2]<len[2]){
			a[l++] = a2[rank[2]++];
		}
		while(rank[3]<len[3]){
			a[l++] = a3[rank[3]++];
		}
		while(rank[4]<len[4]){
			a[l++] = a4[rank[4]++];
		}
	}
	
	delete []a1;
	delete []a2;
	delete []a3;
	delete []a4;
}

void mergesort(int l, int r, int *a){//左闭右开 
	Print2(l, r);
	if(l+1 >= r){//0或1个数 
		return;
	}
	else if(l+2 == r){//2个数 
		int max, min;
		compare(a[l], a[l+1], a[l+1], &max, &min);
		swap(max, a[l+1]);
		return;
	}
	else if(l+3 == r){//3个数 
		int max, min;
		compare(a[l], a[l+1], a[l+2], &max, &min);
		swap(max, a[l+2]);
		swap(min, a[l]);
	}
	else{//>=4
		int mid[3];
		mid[1] = (l+r)/2;
		mid[0] = (l+mid[1])/2;
		mid[2] = (mid[1]+r)/2;
		mergesort(l, mid[0], a);
		mergesort(mid[0], mid[1], a);
		mergesort(mid[1], mid[2], a);
		mergesort(mid[2], r, a);
		merge(l, r, a);
	}
}

void sort(int n, int limit, int *a) {
	mergesort(0, n, a);
}

int main(){
	scanf("%d %d", &n, &limit);
	A = new int [n];
	a = new int [n];
	for(int i=0; i<n; ++i){
		a[i] = i;
		scanf("%d", &A[i]);
	}
	Print();
	sort(n, limit, a);
	for(int i=0; i<n; ++i){
		printf("%d", A[a[i]]);
	}
}
