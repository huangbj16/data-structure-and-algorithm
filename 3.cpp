#include<iostream>
#include<cstdio>
using namespace std;

struct Link{
	int pre, next, val;
}link[2000020];

int pos[2000020];

int main()
{
	setvbuf(stdin, new char [1 << 25], _IOFBF, 1 << 25);
	setvbuf(stdout, new char [1 << 25], _IOFBF, 1 << 25);
	/* 
	freopen("in3.txt", "r", stdin);
	freopen("out3.txt", "w", stdout);
	*/
	int n;
	scanf("%d",&n);
	int m;
	for(int i=1; i<=n; ++i){
		scanf("%d",&m);
		link[i].pre = i-1;
		link[i].next = i+1;
		link[i].val = m;
		pos[m] = i;
	}
	link[0].val = 0;
	link[0].next = 1;
	link[n+1].val = n+1;
	link[n+1].pre = n;
	//for(int i=0; i<=n+1; ++i)
		//printf("%d val: %d, pre: %d, next: %d\n",i, link[i].val, link[i].pre, link[i].next);
	int p = 0;
	for(int i=n; i>=1; --i){
		if(pos[p] < pos[i] || link[link[pos[p]].pre].val == i){
			printf("%d ",i);
			p = i;
			int _pre = link[pos[p]].pre;
			int _next = link[pos[p]].next;
			link[_pre].next = _next;
			link[_next].pre = _pre;
		}
		while(link[link[pos[p]].pre].val > i){
			printf("%d ",link[link[pos[p]].pre].val);
			p = link[link[pos[p]].pre].val;
			int _pre = link[pos[p]].pre;
			int _next = link[pos[p]].next;
			link[_pre].next = _next;
			link[_next].pre = _pre;
		}
		//for(int i=0; i<=n+1; ++i)
			//printf("%d val: %d, pre: %d, next: %d\n",i, link[i].val, link[i].pre, link[i].next);
	}
	p = link[n+1].pre;
	while(p!=0){
		printf("%d ", link[p].val);
		p = link[p].pre;
	}
	printf("\n");
	
	return 0;
}

