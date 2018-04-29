#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAXN 500050

class LinkedList{
	public:
		int cur[2], len[2];
		int val;
		int *link[2];//m vs M
		LinkedList();
		void append(int p, int val);
		void print();
		void clear();
};

LinkedList::LinkedList(){
	cur[0] = 0;
	cur[1] = 0;
	len[0] = 2;
	len[1] = 2;
	link[0] = new int[len[0]];
	link[1] = new int[len[1]];
	val = 0;
}

void LinkedList::append(int p, int val){
	//printf("append: %d %d\n", p, val);
	if(cur[val] != len[val]){
		link[val][cur[val]++] = p;
	}
	else{
		//printf("extend\n");
		len[val] *= 2;
		int *tmp = new int[len[val]];
		for(int i=0; i<cur[val]; ++i){
			tmp[i] = link[val][i];
		}
		delete []link[val];
		link[val] = tmp;
		link[val][cur[val]++] = p;
	}
}

void LinkedList::print(){
	/*
	for(int i=0; i<=1; ++i){
		for(int j=0; j<cur[i]; ++j){
			printf("%d ", link[i][j]);
		}
		printf("/");
	}
	printf("\n");
	*/
}

void LinkedList::clear(){
	cur[0] = 0;
	cur[1] = 0;
}

int n, m;
LinkedList line[MAXN];
bool visited[MAXN];
bool del[MAXN];
int val[MAXN];
int l1[MAXN*3], l2[MAXN*3];
int fs[MAXN], len[MAXN];
int dfn[MAXN], low[MAXN];
char s[MAXN];
int clock;
int stack[MAXN], top;
int que[MAXN], fa[MAXN]; 
bool instack[MAXN];
int sbc[MAXN], sbclen;//从0开始 
int dp[MAXN];

void mission1(){
	memset(visited, false, sizeof(visited)); 
	int l = 0, r = 1;
	val[0] == 1 ? len[0] = 1 : len[0] = 0;
	fs[0] = 0;
	visited[0] = true;
	
	
	while(l<r){
		//printf("round\n");
		//dfs, take line[0] linem
		int tmpl = l, tmpr = r;
		while(tmpl != tmpr){
			for(int i=tmpl; i<tmpr; ++i){//traverse to find equal len
				int p = fs[i];
				for(int j=0; j<line[p].cur[0]; ++j){
					int _p = line[p].link[0][j];
					if(!visited[_p]){
						fs[r++] = _p;
						visited[_p] = true;
						len[_p] = len[p];
						//printf("dfs: enqueue: %d\n", _p);
					}
				}
			}
			tmpl = tmpr;
			tmpr = r;
		}
		//bfs
		tmpr = r;
		for(int i=l; i<tmpr; ++i){
			int p = fs[i];
			for(int j=0; j<line[p].cur[1]; ++j){
				int _p = line[p].link[1][j];
				if(!visited[_p]){
					fs[r++] = _p;
					visited[_p] = true;
					len[_p] = len[p]+1;
					//printf("bfs: enqueue: %d\n", _p);
				}
			}
		}	
		l = tmpr;
	}
	
	//printf("len[n-1]: %d\n", len[n-1]);
	printf("%d\n", len[n-1]);
}

void delpoint(int p){
	del[p] = true;
	for(int i=0; i<=1; ++i){
		for(int j=0; j<line[p].cur[i]; ++j){
			int _p = line[p].link[i][j];
			if(!del[_p]){
				delpoint(_p);
			}
		}
	}
}

void tarjan(int p){
	int node = 0;
	
	visited[p] = true;
	dfn[p] = ++clock;
	low[p] = clock;
	instack[p] = true;
	stack[top++] = p;
	que[node] = p;
	
	while(node != -1){
		int q = que[node];
		if(!visited[q]){//还未访问过，那么加入后继节点 
			bool flag = false;
			for(int i=0; i<=1; ++i){
				for(int j=0; j<line[q].cur[i]; ++j){
					int _q = line[q].link[i][j];
					if(!visited[_q]){
						
					}
				}
			}
		}
		else{//已经visited，那就看能不能更新它的父亲。 
			
		}
	}
	
	for(int i=0; i<=1; ++i){
		for(int j=0; j<line[p].cur[i]; ++j){
			int _p = line[p].link[i][j];
			if(!visited[_p]){//not visited
				tarjan(_p);
				if(low[p] > low[_p])
					low[p] = low[_p];
			}
			else if(instack[_p] && low[p] > dfn[_p])
				low[p] = dfn[_p];
		}
	}
	
	if(dfn[p] == low[p]){//新的强联通分量 
		//printf("new sbc %d :", sbclen);
		int _p;
		do{
			_p = stack[--top];
			instack[_p] = false;
			sbc[_p] = sbclen;
			//printf("%d ",_p);
		}while(_p != p);
		//printf("\n");
		sbclen++;
	}
	
}

void topotraverse(int p){
	visited[p] = true;
	int q;
	for(int i=0; i<line[p].cur[0]; ++i){
		q = line[p].link[0][i];
		if(!visited[q]){
			topotraverse(q);
		}
	}
	stack[top++] = p;
}

void mission2(){
	//删去无关节点
	//memset(del, false, sizeof(del));
	//delpoint(0);
	//for(int i=0; i<)
	//求强联通
	memset(visited, false, sizeof(visited));
	memset(instack, false, sizeof(instack));
	top = 0;
	clock = 0;
	sbclen = 0;
	tarjan(0);
	
	//合并节点和边,sbc中存了对应的强联通分量 
	//注意：可能有重边 
	for(int i=0; i<n; ++i){
		line[i].clear();
		if(!val[i]){
			line[sbc[i]].val ++;
		}
	}
	int p, q;
	for(int i=0; i<m; ++i){
		p = l1[i];
		q = l2[i];
		if(visited[p] && visited[q]){
			p = sbc[p];
			q = sbc[q];
			if(p != q)
				line[p].append(q, 0);//选择存到0 
		}
	}
	
	for(int i=0; i<sbclen; ++i){
		line[i].print();
	}
	//拓扑序遍历求最大m 
	memset(visited, 0, sizeof(visited));
	top = 0;
	topotraverse(sbc[0]);
	for(int i=0; i<sbclen; ++i){
		dp[i] = line[i].val;
	}
	while(top != 0){
		p = stack[--top];
		for(int i=0; i<line[p].cur[0]; ++i){
			q = line[p].link[0][i];
			if(dp[q] < dp[p] + line[q].val)
				dp[q] = dp[p] + line[q].val;
		}
	}
	
	//printf("max[n-1] = %d\n", dp[sbc[n-1]]);
	printf("%d\n", dp[sbc[n-1]]);
}

int main(){
	//freopen("in4.txt", "r", stdin);
	
	scanf("%d %d", &n, &m);
	scanf("%s", s);
	for(int i=0; i<n; ++i){
		s[i] == 'M' ? val[i] = 1 : val[i] = 0;
	}
	/*
	for(int i=0; i<n; ++i){
		printf("%d ", val[i]);
	}
	printf("\n");
	*/
	int j,k;
	for(int i=0; i<m; ++i){
		scanf("%d %d", &j ,&k);
		line[j].append(k, val[k]);
		l1[i] = j;
		l2[i] = k;
	}
	/*
	for(int i=0; i<n; ++i){
		printf("%d: ", i);
		line[i].print();
	}
	*/
	mission1();
	mission2();
	
	
	return 0;
}
