#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int n,k;
int num[500050];
int sum[500050];

struct Node{
	Node *l, *r;//left & right 
	int cnt;//count how many nodes under this node
};

class Bintree{
	public:
		Node *head;//head node
		Bintree();
		void Insert(int x);
		void Delete(int x);
		int FindLarge(int x);
};

Bintree::Bintree(){
	head = new Node;
	head->l = NULL;
	head->r = NULL;
	head->cnt = 0;
}

void Bintree::Insert(int x){
	//cmp is used to find whether go left or right
	Node *cur = head; 
	for(int cmp = 1<<30; cmp != 0; cmp>>=1){
		cur->cnt ++;//new node is under this node
		if(cmp & x){//right
			if(cur->r == NULL){//if null, new a node called nNode
				Node *nNode = new Node; 
				nNode->l = NULL;
				nNode->r = NULL;
				nNode->cnt = 0; 
				cur->r = nNode;	
			}
			cur = cur->r;//go to next node
		}
		else{//left
			if(cur->l == NULL){//if null, new a node called nNode
				Node *nNode = new Node;
				nNode->l = NULL;
				nNode->r = NULL;
				nNode->cnt = 0;
				cur->l = nNode;
			}
			cur = cur->l;//go to left
		}
	}
	cur->cnt ++;
}

void Bintree::Delete(int x){
	Node *cur = head;
	Node *h =  new Node;
	h->l = head;
	
	for(int cmp = 1<<30; cmp!=0; cmp>>=1){
		cur->cnt --;
		if(cur->cnt > 0){
			h = cur;
			if(cmp & x){
				cur = cur->r;
			}
			else{
				cur = cur->l;
			}
		}
		else{
			break;
		}
	}
	if(cur->l == NULL && cur->r == NULL){
		cur->cnt --;
	}
	if(cur->cnt == 0){
		if(h->l == cur)
			h->l = NULL;
		else
			h->r = NULL;
		
		while(1){
			h = cur;
			if(cur->l == NULL && cur->r == NULL){
				delete cur;
				break;
			}
			else{
				if(cur->l != NULL)
					cur = cur->l;
				else
					cur = cur->r;
				delete h;
			}
		}
	}
}

int Bintree::FindLarge(int x){
	//take the reverse side to make x^findlarge biggest
	Node *cur = head;
	int res = 0;
	
	for(int cmp = 1<<30; cmp!=0; cmp>>=1){
		if(cur->l == NULL){
			res = res*2 + 1;
			cur = cur->r;
		}
		else if(cur->r == NULL){
			res = res*2;
			cur = cur->l;
		}
		else{
			if(x & cmp){
				cur = cur->l;
				res = res*2;
			}
			else{
				cur = cur->r;
				res = res*2 + 1;
			}
		}
	}
	return res;
}

int main()
{
	//freopen("in2.txt", "r", stdin);
	//freopen("out2.txt", "w", stdout);
	setvbuf(stdin, new char [1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char [1 << 20], _IOFBF, 1 << 20);
	
	int Res = 0;
	memset(num, 0, sizeof(num));
	memset(sum, 0, sizeof(sum));
	Bintree tree;
	scanf("%d %d", &n, &k);
	for(int i=1; i<=n; ++i){
		scanf("%d", &num[i]);
		Res = Res^num[i];
		sum[i] = Res; 
	}
	for(int i=1; i<=k; ++i){
		tree.Insert(sum[i]);
	}
	long long tot = 0;
	int tmp;
	for(int i=1; i<=n; ++i){
		tmp = tree.FindLarge(sum[i-1]);
		tot += tmp ^ sum[i-1];
		tree.Delete(sum[i]);
		if(i+k <= n){
			tree.Insert(sum[i+k]);
		}
	}
	printf("%lld\n", tot%2147483648);
	return 0;
}

