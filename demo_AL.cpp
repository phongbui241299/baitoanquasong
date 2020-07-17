#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <stdlib.h>
#include <iostream> 
#include <fstream> 
#include <iostream>
#define MaxConQuy 3
#define MaxTuSi 3
#define Maxlength 100

using namespace std;


typedef struct{
	int so_tusi;
	int so_quy;
	char vitri_thuyen;
}State;

typedef struct Node{
	State state;
	struct Node *Parent;
	int no_function;
}Node;
	
	

void init_state(State* state){
	state->so_quy=3;
	state->so_tusi=3;
	state->vitri_thuyen='A';
	}
	
int min(int a, int b){
	return a<b?a:b ;
}

int max(int a, int b){
	return a>b?a:b ;
}	
	

int compareStates(State A, State B){
	return A.so_quy==B.so_quy && A.so_tusi==B.so_tusi && A.vitri_thuyen==B.vitri_thuyen; 
	}

int goalCheck(State state){
	return state.so_quy==0 && state.so_tusi==0 && state.vitri_thuyen=='B';
	}	
	

	
int chuyen1Nguoi0Quy(State cur_state, State *result){
	*result = cur_state;
	if(cur_state.vitri_thuyen == 'A' && cur_state.so_tusi>0){
		result->so_tusi = cur_state.so_tusi-1;
		result->vitri_thuyen = 'B';
	}
	else if(cur_state.vitri_thuyen=='B' && (MaxTuSi - cur_state.so_tusi)>0){
		result->so_tusi = cur_state.so_tusi + 1;
		result->vitri_thuyen ='A';
	}
	if(((result->so_quy < result->so_tusi && result->so_tusi ==3) 
		|| result->so_quy == result->so_tusi 
		|| result->so_quy > result->so_tusi && result->so_tusi ==0)
			&& !compareStates(*result, cur_state))
			return 1;
	return 0;
}

int chuyen0Nguoi1Quy(State cur_state, State *result){
	*result = cur_state;
	if(cur_state.vitri_thuyen == 'A' && cur_state.so_quy>0){
		result->so_quy = cur_state.so_quy - 1;
		result->vitri_thuyen = 'B';
	}
	else if(cur_state.vitri_thuyen =='B'&&(MaxConQuy - cur_state.so_quy)>0){
		result->so_quy = cur_state.so_quy + 1;
		result->vitri_thuyen ='A';
	}
	if(((result->so_quy < result->so_tusi && result->so_tusi ==3)
		||result->so_quy == result->so_tusi
		||result->so_quy > result->so_tusi && result->so_tusi ==0)
			&& !compareStates(*result, cur_state))
			return 1;
	return 0;
}

 int chuyen1Nguoi1Quy(State cur_state, State *result){
	*result = cur_state;
	if(cur_state.vitri_thuyen == 'A' && cur_state.so_quy>0 && cur_state.so_tusi>0){
		result->so_tusi = cur_state.so_tusi - 1;
		result->so_quy = cur_state.so_quy - 1;
		result->vitri_thuyen = 'B';
	}
	else if(cur_state.vitri_thuyen=='B' && (MaxConQuy - cur_state.so_quy)>0 && (MaxTuSi - cur_state.so_tusi)>0){
		result->so_tusi = cur_state.so_tusi + 1;
		result->so_quy = cur_state.so_quy + 1;
		result->vitri_thuyen ='A';
	}
	if(((result->so_quy < result->so_tusi && result->so_tusi ==3)
		||result->so_quy == result->so_tusi
		||result->so_quy > result->so_tusi && result->so_tusi ==0)
			&& !compareStates(*result, cur_state))
			return 1;
	return 0;
}

 
int chuyen2Nguoi0Quy(State cur_state, State *result){
	*result = cur_state;
		if(cur_state.vitri_thuyen == 'A' && cur_state.so_tusi>1){
			result->so_tusi = cur_state.so_tusi - 2;
			result->vitri_thuyen = 'B';
		}
		else if(cur_state.vitri_thuyen=='B' && (MaxTuSi - cur_state.so_tusi)>1){
			result->so_tusi = cur_state.so_tusi + 2;
			result->vitri_thuyen ='A';
		}
		if(((result->so_quy < result->so_tusi && result->so_tusi ==3)
			||result->so_quy == result->so_tusi
			||result->so_quy > result->so_tusi && result->so_tusi ==0)
				&& !compareStates(*result, cur_state))
				return 1;
		return 0;
}
 
int chuyen0Nguoi2Quy(State cur_state, State *result){
	*result = cur_state;
		if(cur_state.vitri_thuyen == 'A' && cur_state.so_quy>1){
			result->so_quy = cur_state.so_quy - 2;
			result->vitri_thuyen = 'B';
		}
		else if(cur_state.vitri_thuyen=='B'&&(MaxConQuy - cur_state.so_quy)>1){
			result->so_quy = cur_state.so_quy + 2;
			result->vitri_thuyen ='A';
		}
		if(((result->so_quy < result->so_tusi && result->so_tusi ==3)
		||result->so_quy == result->so_tusi
		||result->so_quy > result->so_tusi && result->so_tusi ==0)
			&& !compareStates(*result, cur_state))
			return 1;
		return 0;
}
const char* action[]={"First State", "Chuyen 0 nguoi 1 quy","Chuyen 1 nguoi 0 quy",
					"Chuyen 1 nguoi 1 quy","Chuyen 0 nguoi 2 quy",
					"Chuyen 2 nguoi 0 quy"};
void print_State(ofstream &Demo, State state){
	int n;
	if(state.vitri_thuyen == 'A'){
		n=0;
	} else n=1;
	printf("\n%d %d %d %d %d", state.so_tusi, state.so_quy, MaxTuSi-state.so_tusi, MaxConQuy-state.so_quy, n);
//	Demo<<state.so_tusi<<" "<<state.so_quy<<" "<<MaxTuSi-state.so_tusi<<" "<<MaxConQuy-state.so_quy<<" "<<n<<'\n';

}

int call_operator(State cur_state, State *result, int option){
	switch(option){
		case 1: return chuyen0Nguoi1Quy(cur_state, result);
		case 2: return chuyen1Nguoi0Quy(cur_state, result);
		case 3: return chuyen1Nguoi1Quy(cur_state, result);
		case 4: return chuyen0Nguoi2Quy(cur_state, result);
		case 5: return chuyen2Nguoi0Quy(cur_state, result);
		default: printf("Error calls operators");
			return 0; 
		}
	}
 

int find_State(State state, stack<Node*> openStack){
	while(!openStack.empty()){
		if(compareStates(openStack.top()->state,state))
			return 1;
		openStack.pop();
	}
	return 0;
}


Node* DFS_Algorithm(ofstream &Demo,State state){
	stack<Node*> Open_DFS;
	stack<Node*> Close_DFS;
	Node* root = (Node*)malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	Open_DFS.push(root);
	while(!Open_DFS.empty()){
		Node* node = Open_DFS.top();
		Open_DFS.pop();
		Close_DFS.push(node);
		if(goalCheck(node->state))
			return node;
		int opt;
		for(opt = 1; opt <= 5; opt++){
			State newstate;
			if(call_operator(node->state, &newstate, opt)){
				if(find_State(newstate, Close_DFS) || find_State(newstate, Open_DFS))
					continue;
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state=newstate;
				newNode->Parent=node;
				newNode->no_function=opt;
				Open_DFS.push(newNode);
			}
		}
	}
	return NULL;
}

void print_WaysToGetGoal(ofstream &Demo, Node* node){
	stack<Node*> stackPrint;
	while(node->Parent != NULL){
		stackPrint.push(node);
		node=node->Parent;
	}
	stackPrint.push(node);
	int no_action=0;
	while(!stackPrint.empty()){
		print_State(Demo, stackPrint.top()->state);
		printf("\nAction: %d", stackPrint.top()->no_function);
		// print no_function to file 
		Demo<<stackPrint.top()->no_function<<" ";
		stackPrint.pop();
		no_action++;
	}
	printf("\n%d ",no_action);
//	Demo<<no_action;
	

}


int main(){
	ofstream Demo("File Demo.txt");
 	State state;
		init_state(&state);
		Node* node = DFS_Algorithm(Demo,state);
		print_WaysToGetGoal(Demo, node);
   	Demo.close();
	return 0;
}


