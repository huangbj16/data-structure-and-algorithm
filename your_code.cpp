#include "temperature.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

struct ColX{
	int row;
	int x;
};

struct RowY{
	int col;
	int y;
	int t;
};

struct SegmentTree{
	long long sum;
	int l,r;
	int cnt;
};

struct Result{
	long long sum;
	int cnt;
};

int N;
int totnode = 0;
SegmentTree tree[2002000];
int headnode[50500];
ColX col[50500];
RowY row[50500];

void swapcol(int x1, int x2){
	ColX tempc;
	tempc = col[x1];
	col[x1] = col[x2];
	col[x2] = tempc;
}

void swaprow(RowY &y1, RowY &y2){
	RowY y3;
	y3 = y1;
	y1 = y2;
	y2 = y3;
}

void swap(int &x1, int &x2){
	int x3;
	x3 = x1;
	x1 = x2;
	x2 = x3;
}

void quicksort_col(int x, int y);
void quicksort_row(int x, int y);
void Initial(int p, int lef, int rig);
int Newnode(int old);
void Insert(int p, int lef, int rig, int rank, long long temp);
int findcolx1(int x, int y);
int findcolx2(int x, int y);
int findrowy1(int y, int x);
int findrowy2(int y, int x);
Result ask(int p, int lef, int rig, int ql, int qr);

void init(int n, const int *x, const int *y, const int *temp) {
	srand((unsigned)time(NULL));
	N = n;
	for(int i=1; i<=N; ++i){
		col[i].row = i;
		col[i].x = x[i-1];
		row[i].col = i;
		row[i].y = y[i-1];
		row[i].t = temp[i-1];
	}
	quicksort_col(1, N);
	/*
	for(int i=1; i<=N; ++i){
		printf("%d %d\n", col[i].x, col[i].row );
	}
	for(int i=1; i<=N; ++i){
		printf("%d %d %d\n", row[i].y, row[i].col, row[i].t );
	}
	*/
	quicksort_row(1, N);
	//排序完成后col.row是不可靠的。
	/*
	for(int i=1; i<=N; ++i){
		printf("%d %d\n", col[i].x, col[i].row );
	}
	for(int i=1; i<=N; ++i){
		printf("%d %d %d\n", row[i].y, row[i].col, row[i].t );
	}
	*/
	totnode++;
	tree[0].sum = 0;
	tree[0].l = 0;
	tree[0].r = 0;
	tree[0].cnt = 0;
	headnode[0] = 0;
	Initial(0, 1, N);
	for(int i=1; i<=N; ++i){
		headnode[i] = Newnode(headnode[i-1]);
		//row[i].col, t;
		//printf("row[%d].col = %d, temp = %d\n", i, row[i].col, row[i].t);
		Insert(headnode[i], 1, N, row[i].col, row[i].t);
		//printf("sum: %d %lld\n", tree[headnode[i]].cnt, tree[headnode[i]].sum);
	}
}

void Insert(int p, int lef, int rig, int rank, long long temp){
	//printf("%d %d %d\n", p, lef, rig);
	tree[p].cnt++;
	tree[p].sum += temp;
	if(lef == rig){
		return;
	}
	int mid = (lef+rig)/2;
	if(rank <= mid){
		tree[p].l = Newnode(tree[p].l);
		Insert(tree[p].l, lef, mid, rank, temp);
	}
	else{
		tree[p].r = Newnode(tree[p].r);
		Insert(tree[p].r, mid+1, rig, rank, temp);
	}
}


int Newnode(int old){
	tree[totnode].l = tree[old].l;
	tree[totnode].r = tree[old].r;
	tree[totnode].sum = tree[old].sum;
	tree[totnode].cnt = tree[old].cnt;
	return totnode++;
}

void Initial(int p, int lef, int rig){
	//printf("%d %d %d\n", p, lef, rig);
	if(lef == rig) return;
	int mid = (lef+rig)/2;
	tree[p].l = Newnode(0);
	tree[p].r = Newnode(0);
	Initial(tree[p].l, lef, mid);
	Initial(tree[p].r, mid+1, rig);
}

int query(int x1, int y1, int x2, int y2) {
	
	int a1,a2,b1,b2;
	if(x1 > x2)
		swap(x1, x2);
	if(y1 > y2)
		swap(y1, y2);
	a1 = findcolx1(x1, y1);
	a2 = findcolx2(x2, y2);
	b1 = findrowy1(y1, x1);
	b2 = findrowy2(y2, x2);
	//printf("find: %d %d %d %d\n", a1, b1, a2, b2);
	
	Result res1, res2;
	res1 = ask(headnode[b1], 1, N, a1, a2);
	res2 = ask(headnode[b2], 1, N, a1, a2);
	//printf("res: %lld %lld %d %d\n", res2.sum, res1.sum, res2.cnt, res1.cnt);
	if(res1.cnt != res2.cnt) 
		return ((res2.sum-res1.sum)/(res2.cnt-res1.cnt));
	else
		return 0;
	
	//return 0;
}

Result ask(int p, int lef, int rig, int ql, int qr){
	if(ql<=lef && rig<=qr){
		Result res;
		res.cnt = tree[p].cnt;
		res.sum = tree[p].sum;
		return res;
	}
	int mid = (lef+rig)>>1;
	Result res;
	res.cnt = 0;
	res.sum = 0;
	if(ql<=mid){
		Result _res;
		_res = ask(tree[p].l, lef, mid, ql, qr);
		res.cnt += _res.cnt;
		res.sum += _res.sum;
	}
	if(mid<qr){
		Result _res;
		_res = ask(tree[p].r, mid+1, rig, ql, qr);
		res.cnt += _res.cnt;
		res.sum += _res.sum;
	}
	return res;
}

int findcolx1(int x, int y){
	int lo = 1, hi = N+1;
	while(lo < hi){
		int mid = (lo+hi)>>1;
		(x < col[mid].x || (x == col[mid].x && y <= row[col[mid].row].y))? hi = mid : lo = mid+1;
	}
	return --lo;
}

int findcolx2(int x, int y){
	int lo = 1, hi = N+1;
	while(lo < hi){
		//printf("lo:%d, hi:%d\n", lo, hi);
		int mid = (lo+hi)>>1;
		(x < col[mid].x || (x == col[mid].x && y < row[col[mid].row].y)) ? hi = mid : lo = mid+1;
	}
	return --lo;
}

int findrowy1(int y, int x){
	int lo = 1, hi = N+1;
	while(lo < hi){
		int mid = (lo+hi)>>1;
		(y < row[mid].y || (y == row[mid].y && x <= col[row[mid].col].x))? hi = mid : lo = mid+1;
	}
	return --lo;
}

int findrowy2(int y, int x){
	int lo = 1, hi = N+1;
	while(lo < hi){
		int mid = (lo+hi)>>1;
		(y < row[mid].y || (y == row[mid].y && x < col[row[mid].col].x))? hi = mid : lo = mid+1;
	}
	return --lo;
}

void quicksort_col(int x, int y){
	if(x >= y) return;
	//swapcol(x, x + rand()%(y-x+1));
	int l = x, r = y;
	ColX val = col[l];
	while(l < r){
		while(l < r){
			if(col[r].x < val.x || (col[r].x == val.x && row[col[r].row].y < row[val.row].y))
				break;
			r--;
		}
		if(l < r){
			row[col[r].row].col = l;
			col[l] = col[r];
			l++;
		}
		while(l < r){
			if(val.x < col[l].x || (val.x == col[l].x && row[val.row].y < row[col[l].row].y))
				break;
			l++;
		}
		if(l < r){
			row[col[l].row].col = r;
			col[r] = col[l];
			r--;
		}
	}
	int mid = (l+r)/2;
	col[mid] = val;
	row[val.row].col = mid;
	quicksort_col(x, mid-1);
	quicksort_col(mid+1, y);
}

void quicksort_row(int x, int y){
	if(x >= y) return;
	//swaprow(row[x], row[x + rand()%(y-x+1)]);
	int l = x, r = y;
	int pre = l;
	RowY val = row[l];
	while(l < r){
		while(l < r){
			if(row[r].y < val.y || (row[r].y == val.y && col[row[r].col].x < col[val.col].x))
				break;
			r--;
		}
		if(l < r){
			col[row[r].col].row = l;
			row[l] = row[r];
			l++;
		}
		while(l < r){
			if(val.y < row[l].y || (val.y == row[l].y && col[val.col].x < col[row[l].col].x))
 				break;
			l++;
		}
		if(l < r){
			col[row[l].col].row = r;
			row[r] = row[l];
			r--;
		}
	}
	int mid = (l+r)/2;
	row[mid] = val;
	col[val.col].row = mid;
	quicksort_row(x, mid-1);
	quicksort_row(mid+1, y);
}

