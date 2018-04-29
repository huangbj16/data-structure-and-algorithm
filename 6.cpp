#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

char ls[4000040], rs[4000040], strs[12000120];
int lslen, rslen, ordernum;
int reverse, cross;
int head1,head2; 


void Initial(){
	reverse = 1;
	cross = 1;
	lslen = 0;
	rslen = 0;
	head1 = 4000040;
	head2 = 4000040;
	
	//∂¡»Î
	char chr;
	while(1){
		chr = getchar();
		if(chr != '\n'){
			strs[head2++] = chr;
		}
		else{
			break;
		}
	}
	/*
	for(int i=head1; i<head2; ++i){
		printf("%c",strs[i]);
	}
	printf("\n");
	
	preq = head1;
	while(preq->next != NULL){
		printf("%c\n",preq->val);
		preq = preq->next;
	}
	*/
}

void Movelef(){
	//printf("Movelef\n");
	char side;
	getchar();
	side = getchar();
	getchar();
	int d = cross*reverse;
	if(cross == 1){//Œ¥‘ΩΩÁ 
		if(side == 'L'){//◊Û¿®∫≈ 
			if(lslen != 0){
				strs[head1-d] = ls[--lslen];
				head1 = head1-d;
				printf("T\n");
			}
			else{
				printf("F\n");
			}
		}
		else{//”“¿®∫≈ 
			if(head1 != head2){
				rs[rslen++] = strs[head2-d];
				head2 = head2-d;
				printf("T\n");
			}
			else{
				if(lslen != 0){
					cross = -1;
					strs[head2-d] = ls[--lslen];
					head2 = head2-d;
					printf("T\n");
				}
				else{
					printf("F\n");
				}
			}
		}
	}
	else{//cross == -1
		if(side == 'R'){
			if(lslen!=0){
				strs[head2+d] = ls[--lslen];
				head2 = head2+d;
				printf("T\n");
			}
			else{
				printf("F\n");
			}
		}
		else{//side == 'L'
			rs[rslen++] = strs[head1+d];
			head1 = head1+d;
			printf("T\n");
			if(head1 == head2){
				cross = 1;
			}
		}
	}
}

void Moverig(){
	//printf("Moverig\n");
	char side;
	getchar();
	side = getchar();
	getchar();
	//printf(" %c\n", side);
	int d = cross*reverse;
	if(cross == 1){//Œ¥‘ΩΩÁ
		if(side == 'R'){//”“¿®∫≈ 
			if(rslen != 0){
				strs[head2] = rs[--rslen];
				head2 = head2+d;
				printf("T\n");
			}
			else{
				printf("F\n");
			}
		}
		else{//◊Û¿®∫≈ 
			if(head1 != head2){
				ls[lslen++] = strs[head1];
				head1 = head1+d;
				printf("T\n");
			}
			else{
				if(rslen != 0){
					cross = -1;
					strs[head2] = rs[--rslen];
					head1 = head1+d;
					printf("T\n");
				}
				else{
					printf("F\n");
				}
			}
		}
	}
	else{//cross == -1
		if(side == 'L'){
			if(rslen!=0){
				strs[head1] = rs[--rslen];
				head1 = head1-d;
				printf("T\n");
			}
			else{
				printf("F\n");
			}
		}
		else{//side == 'R'
			ls[lslen++] = strs[head2];
			head2 = head2-d;
			printf("T\n");
			if(head1 == head2){
				cross = 1;
			}
		}
	}
}

void Insert(){
	//printf("Insert\n");
	char side, inval;
	getchar();
	side = getchar();
	getchar();
	inval = getchar();
	getchar();
	//printf(" %c %c\n", side, inval);
	int d = reverse * cross;
	if(cross == 1){
		if(side == 'L'){
			ls[lslen++] = inval;
		}
		else{
			if(head1 != head2){
				strs[head2] = inval;
				head2 = head2 + d;
			}
			else{
				ls[lslen++] = inval;
			}
		}
	}
	else{//cross == -1
		if(side == 'R'){
			ls[lslen++] = inval;
		}
		else{
			strs[head1] = inval;
			head1 = head1 - d;
		}
	}
	printf("T\n");
}

void Delete(){
	//printf("Delete\n");
	char side;
	getchar();
	side = getchar();
	getchar();
	//printf(" %c\n", side);
	int d = reverse * cross;
	if(cross == 1){
		if(side == 'R'){
			if(rslen != 0){
				rslen--;
				printf("T\n");
			}
			else
				printf("F\n");
		}
		else{//side == 'L'
			if(head1 != head2){
				head1 = head1 + d;
				printf("T\n");
			}
			else{
				if(rslen != 0){
					rslen--;
					printf("T\n");
				}
				else{
					printf("F\n");
				}
			}
		}
	}
	else{//cross == -1
		if(side == 'L'){
			if(rslen != 0){
				rslen--;
				printf("T\n");
			}		
			else{
				printf("F\n");
			}
		}
		else{//side == 'R'
			head2 = head2 - d;
			printf("T\n");
			if(head1 == head2){
				cross = 1;
			}
		}
	}
}

void Reverse(){
	//printf("Reverse\n");
	getchar();
	//printf("\n");
	if(cross==1 && head1 != head2){
		int d = reverse;
		int temp = head1;
		head1 = head2 - d;
		head2 = temp - d;
		reverse = reverse*(-1);
		printf("T\n");
	} 
	else{
		printf("F\n");
	}
}

void Show(){
	//printf("Show\n");
	//getchar();
	//printf("\n");
	
	//("cross: %d, reverse: %d\n",cross, reverse);
	/*
	printf("rs:");
	for(int i=rslen-1; i>=0; --i){
		printf(" %c",rs[i]);
	}
	printf("\n");
	*/
	
	for(int i=0; i<lslen; ++i)
		printf("%c",ls[i]);
	//printf(" ");
	
	if(cross == 1 && reverse == 1){
		for(int i=head1; i<head2; ++i){
			printf("%c",strs[i]);
		}
	}
	else if(cross == 1 && reverse == -1){
		for(int i=head1; i>head2; --i){
			printf("%c",strs[i]);
		}
	}
	else if(cross == -1 && reverse == 1){
		for(int i=head2; i<head1; ++i){
			printf("%c",strs[i]);
		}
	}
	else{//-1 -1 
		for(int i=head2; i>head1; --i){
			printf("%c",strs[i]);
		}
	}
	//printf(" ");
	
	for(int i=rslen-1; i>=0; --i)
		printf("%c",rs[i]);
	printf("\n");
}

int main()
{
	setvbuf(stdin, new char [1 << 25], _IOFBF, 1 << 25);
	setvbuf(stdout, new char [1 << 25], _IOFBF, 1 << 25);
	//freopen("in6.txt","r",stdin);
	//freopen("out6.txt","w",stdout);
	
	
	Initial();
	
	scanf("%d", &ordernum);
	//printf("%d\n", ordernum);
	getchar();
	for(int i=0; i<ordernum; ++i){
		char order;
		scanf("%c",&order);
		//printf("%c",order);
		switch(order)
		{
			case '<':
				Movelef();
				break;
			case '>':
				Moverig();
				break;
			case 'I':
				Insert();
				break;
			case 'D':
				Delete();
				break;
			case 'R':
				Reverse();
				break;
			case 'S':
				getchar();
				Show();
				break;
		}
		//Show();
	}
	
	return 0;
}
