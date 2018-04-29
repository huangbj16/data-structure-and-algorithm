//ÅÆ´Ó1µ½n,×óÓÒ±Õ 
#include<iostream>
#include<cstdio>
using namespace std;

struct Node{
	int l, r;
	int posnum;
};

int n,p,q;
int lastans = 0;
int tot = 1;
int ql, qr;
Node node[20002000];


int change(int p, int l, int r){
	printf("change: %d %d %d\n", p, l, r);
	if((ql == l && qr >= r) || (qr == r && ql <= l)){
		node[p].posnum = 0;
		return 0;
	}
	int mid = (l+r)/2;
	int delta1 = mid-l+1, delta2 = r-mid;
	if((ql>=l && ql<=mid) || (qr>=l && qr<=mid)){
		if(node[p].l == 0){
			node[p].l = tot;
			node[tot].l = 0;
			node[tot].r = 0;
			node[tot].posnum = mid-l+1;
			tot++;
		}
		delta1 = change(node[p].l, l, mid);
	}
	if((qr>=mid+1 && qr<=r) || (ql>=mid+1 && ql<=r)){
		if(node[p].r == 0){
			node[p].r = tot;
			node[tot].l = 0;
			node[tot].r = 0;
			node[tot].posnum = r-mid;
			tot++;
		}
		delta2 = change(node[p].r, mid+1, r);
	}
	node[p].posnum = delta1 + delta2;
	printf("pos%d:%d\n", p, node[p].posnum);
	return node[p].posnum;
}

int ask(int p, int l, int r){
	printf("ask: %d %d %d\n", p, l, r);
	if((ql == l && qr >= r) || (qr == r && ql <= l)){
		return node[p].posnum;
	}
	int mid = (l+r)/2;
	int delta1 = 0, delta2 = 0;
	if((ql>=l && ql<=mid) || (qr>=l && qr<=mid)){
		if(node[p].l != 0)
			delta1 = ask(node[p].l, l, mid);
		else{
			int maxl, minr;
			ql>=l ? maxl = ql : maxl = l;
			qr<=mid ? minr = qr : minr = mid;
			delta1 = minr-maxl+1;
		}
	}
	if((qr>=mid+1 && qr<=r) || (ql>=mid+1 && ql<=r)){
		if(node[p].r != 0)
			delta2 = ask(node[p].r, mid+1, r);
		else{
			int maxl, minr;
			ql>=mid+1 ? maxl = ql : maxl = mid+1;
			qr<=r ? minr = qr : minr = r;
			delta2 = minr-maxl+1;
		}
	}
	return delta1 + delta2;
}

int main()
{
	freopen("in1.txt", "r", stdin);
	cin>>n>>p>>q;
	node[0].l = 0;
	node[0].r = 0;
	//node[0].posnum = n;
	 
	int i,j,k;
	for(int j=0; j<p+q; ++j){
		scanf("%d %d %d", &i, &ql, &qr);
		ql = ql^lastans;
		qr = qr^lastans;
		if(i==0){
			printf("change: %d %d\n", ql, qr);
			change(0, 1, n);
		}
		else{
			printf("ask: %d %d\n", ql, qr);
			lastans = ask(0, 1, n);
			printf("ans: %d\n", lastans);
		}
	} 
	return 0;
}

