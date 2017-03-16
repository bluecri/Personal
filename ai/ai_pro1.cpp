#include <iostream>
#include <math.h>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
//#include <hash_map>

#define PUZZLE_SIZE 3

using namespace std;

int max_int(int a, int b);
long myPow(long a, long n);
//void arrInPuz(int* arr, puzzle * p);

class puzzle {
public:
	int cnt = 0;
	int arr[PUZZLE_SIZE][PUZZLE_SIZE];
	long state = 0;
	int lastMove = 0; // 2:down 4:left 6:right: 8:up
	int zPosX = 0, zPosY = 0;
	int currentCost = 0;
	int futureCost = 0;

	puzzle(int * input_arr, int cnts) {
		int i, j;
		//arrInPuz(arr, p);
		for (i = 0; i < PUZZLE_SIZE; i++) {
			for (j = 0; j < PUZZLE_SIZE; j++) {
				state += input_arr[PUZZLE_SIZE * i + j];
				if(i != PUZZLE_SIZE-1 || j != PUZZLE_SIZE-1)
					state *= 10;
				arr[i][j] = input_arr[PUZZLE_SIZE * i + j];
				if (input_arr[PUZZLE_SIZE * i + j] == 0) {
					zPosX = i;
					zPosY = j;
				}
				if (i == PUZZLE_SIZE - 1 && j == PUZZLE_SIZE - 1)
					break;
			}
		}
		//state = state;
		cnt = cnts;
	}
	//puzzle(const puzzle& p)

	bool MoveLeft(void) {
		if (zPosY == 0) {
			//cout << "cant move left" << endl;
			return false;
		}
		int temp;
		arr[zPosX][zPosY] = arr[zPosX][zPosY - 1];
		arr[zPosX][zPosY - 1] = 0;

		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - zPosY) = position 0 -> new
		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - (zPosY-1)) = position new -> 0
		//original int = arr[zPosX][zPosY]
		//state = state + (arr[zPosX][zPosY] * myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - zPosY))
		//	- (arr[zPosX][zPosY] * myPow(10, PUZZLE_SIZE - zPosX - 1) * 10 * (PUZZLE_SIZE - (zPosY-1)));
		int invX = PUZZLE_SIZE - zPosX - 1;
		int invY = PUZZLE_SIZE - zPosY - 1;
		state = state + (arr[zPosX][zPosY] * myPow(1000, invX) * myPow(10, invY))
			- (arr[zPosX][zPosY] * myPow(1000, invX) * myPow(10, invY+1));
		lastMove = 4;	//last move
		cnt++;
		return true;
	}

	bool MoveRight(void) {
		if (zPosY == PUZZLE_SIZE-1) {
			//cout << "cant move rightt" << endl;
			return false;
		}
		int temp;
		arr[zPosX][zPosY] = arr[zPosX][zPosY + 1];
		arr[zPosX][zPosY + 1] = 0;

		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - zPosY) = position 0 -> new
		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - (zPosY-1)) = position new -> 0
		//original int = arr[zPosX][zPosY]
		//state = state + (arr[zPosX][zPosY] * myPow(10, PUZZLE_SIZE - zPosX - 1) * 10 * (PUZZLE_SIZE - zPosY))
		//	- (arr[zPosX][zPosY] * myPow(10, PUZZLE_SIZE - zPosX - 1) * 10 * (PUZZLE_SIZE - (zPosY + 1)));
		int invX = PUZZLE_SIZE - zPosX - 1;
		int invY = PUZZLE_SIZE - zPosY - 1;
		state = state + (arr[zPosX][zPosY] * myPow(1000, invX) * myPow(10, invY))
			- (arr[zPosX][zPosY] * myPow(1000, invX) * myPow(10, invY-1));
		lastMove = 6;	//last move
		cnt++;
		return true;
	}

	bool MoveUp(void) {
		if (zPosX == 0) {
			//cout << "cant move up" << endl;
			return false;
		}
		int temp;
		arr[zPosX][zPosY] = arr[zPosX - 1][zPosY];
		arr[zPosX - 1][zPosY] = 0;

		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - zPosY) = position 0 -> new
		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - (zPosY-1)) = position new -> 0
		//original int = arr[zPosX][zPosY]
		int invX = PUZZLE_SIZE - zPosX - 1;
		int invY = PUZZLE_SIZE - zPosY - 1;
		state = state + (arr[zPosX][zPosY] * myPow(1000, invX) * myPow(10, invY))
			- (arr[zPosX][zPosY] * myPow(1000, invX + 1) * myPow(10, invY));

		lastMove = 8;	//last move
		cnt++;
		return true;
	}

	bool MoveDown(void) {
		if (zPosX == PUZZLE_SIZE -1) {
			//cout << "cant move down" << endl;
			return false;
		}
		int temp;
		arr[zPosX][zPosY] = arr[zPosX + 1][zPosY];
		arr[zPosX + 1][zPosY] = 0;

		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - zPosY) = position 0 -> new
		//myPow(10, PUZZLE_SIZE - zPosX - 1) * 10*(PUZZLE_SIZE - (zPosY-1)) = position new -> 0
		//original int = arr[zPosX][zPosY]
		//state = state + (arr[zPosX][zPosY] * myPow(10, PUZZLE_SIZE - zPosX - 1) * 10 * (PUZZLE_SIZE - zPosY))
		//	- (arr[zPosX][zPosY] * myPow(10, PUZZLE_SIZE - (zPosX + 1) - 1) * 10 * (PUZZLE_SIZE - (zPosY)));
		int invX = PUZZLE_SIZE - zPosX - 1;
		int invY = PUZZLE_SIZE - zPosY - 1;
		state = state + (arr[zPosX][zPosY] * myPow(1000, invX) * myPow(10, invY))
			- (arr[zPosX][zPosY] * myPow(1000, invX - 1) * myPow(10, invY));
		lastMove = 2;	//last move
		cnt++;
		return true;
	}

	int ReturnState() {
		return state;
	}
};

struct for_min_heap {
	bool operator()(const puzzle &p1, const puzzle &p2) const {
		return p1.futureCost > p2.futureCost;
	}
};

void DFS();
void BFS();
void STAR();


//hash_map<int, int> pMap;
set<int> iSet;
stack<puzzle *> pStk;
queue<puzzle *> pQue;
priority_queue<int, puzzle *, for_min_heap> prioQue;


int FIRST[PUZZLE_SIZE*PUZZLE_SIZE] = { 1,2,3,4,0,6,7,5,8 };
//int FIRST[PUZZLE_SIZE*PUZZLE_SIZE] = { 4, 1,0,  6, 3, 2, 7, 5, 8 };
//int FIRST[PUZZLE_SIZE*PUZZLE_SIZE] = { 4, 3, 1, 6, 5, 2, 0, 7, 8 };
//int FIRST[PUZZLE_SIZE*PUZZLE_SIZE] = {3,1,0,4,5,2,6,7,8 };
//int FIRST[PUZZLE_SIZE*PUZZLE_SIZE] = { 0,1,2,3,4,5,6,7,8 };




puzzle * puz = new puzzle(FIRST, 0);


int main() {
	
	cout << "DFS : 1, BFS : 2 STAR; 3" << endl;
	int in;
	cin >> in;
	switch (in) {
	case 1:
		DFS();
	case 2:
		BFS();
	case 3:
		STAR();

	}
	return 0;
}

void BFS() {
	int visit = 0, open = 0;		//visit : total # of nodes visited, open : max length of queue or stack
	pQue.push(puz);
	puzzle * p = NULL;
	while (!pQue.empty()) {
		p = pQue.front();	//look front of queue
		visit++;
		open = max_int(open, pQue.size());
		if (p->state == 123456780) {
			cout << "result : " << p->cnt << endl;		//check p is sol
			cout << "visit : " << visit << "\topen : " << open << endl;
			break;
		}
		if (iSet.find(p->state) != iSet.end()) {	//check p is already visited
			pQue.pop();
			p = NULL;
			continue;
		}
		iSet.insert(p->state);						//check p is visited in iSet

		int tempArr[PUZZLE_SIZE*PUZZLE_SIZE];			
		//setting tempArr for init 'puzzle * pp'
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tempArr[PUZZLE_SIZE * i + j] = p->arr[i][j];
			}
		}

		puzzle * pp = NULL;
		
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 2) && (pp->MoveUp() == true) ) {
			pQue.push(pp);
			//iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 4) && (pp->MoveRight() == true)) {
			pQue.push(pp);
			//iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 8) && (pp->MoveDown() == true) ) {
			pQue.push(pp);
			//iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 6) && (pp->MoveLeft() == true) ) {
			pQue.push(pp);
			//iSet.insert(pp->state);
		}
		else {
			delete pp;
		}
		pp = NULL;
		pQue.pop();
		p = NULL;
	}
	cout << "end!" << endl;
	int temp;
	cin >> temp;
}

void DFS() {
	int visit = 0, open = 0;		//visit : total # of nodes visited, open : max length of queue or stack
	pStk.push(puz);
	while (!pStk.empty()) {
		puzzle * p = pStk.top();	//do not pop
		visit++;
		open = max_int(open, pStk.size());
		if (p->state == 123456780) {
			cout << "result : " << p->cnt << endl;		//check p is sol
			cout << "visit : " << visit << "\topen : " << open << endl;
			break;
		}
		int tempArr[PUZZLE_SIZE*PUZZLE_SIZE];

		//setting tempArr
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tempArr[PUZZLE_SIZE * i + j] = p->arr[i][j];
			}
		}

		puzzle * pp = NULL;
		pp = new puzzle(tempArr, p->cnt);
		if (iSet.find(pp->state) != iSet.end()) {
			pStk.pop();
			continue;
		}
		if ((pp->lastMove != 8) && (pp->MoveDown() == true) ) {
			pStk.push(pp);
			iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 4) && (pp->MoveRight() == true)) {
			pStk.push(pp);
			iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 2) && (pp->MoveUp() == true)) {
			pStk.push(pp);
			iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 6) && (pp->MoveLeft() == true)) {
			pStk.push(pp);
			iSet.insert(pp->state);
		}
		else {
			delete pp;
		}
		pp = NULL;
		pStk.pop();
		//delete p;
		p = NULL;
	}
	cout << "end!" << endl;
	int temp;
	cin >> temp;

}

void STAR(int (*calcCostFunc)(puzzle * inputP)) {
	int visit = 0, open = 0;		//visit : total # of nodes visited, open : max length of queue or stack
	
	prioQue.push(puz);
	puzzle * p = NULL;
	while (!pQue.empty()) {
		p = pQue.front();	//look front of queue
		visit++;
		open = max_int(open, prioQue.size());
		if (p->state == 123456780) {
			cout << "result : " << p->cnt << endl;		//check p is sol
			cout << "visit : " << visit << "\topen : " << open << endl;
			break;
		}
		if (iSet.find(p->state) != iSet.end()) {	//check p is already visited
			prioQue.pop();
			p = NULL;
			continue;
		}
		iSet.insert(p->state);						//check p is visited in iSet

		int tempArr[PUZZLE_SIZE*PUZZLE_SIZE];
		//setting tempArr for init 'puzzle * pp'
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tempArr[PUZZLE_SIZE * i + j] = p->arr[i][j];
			}
		}

		puzzle * pp = NULL;

		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 2) && (pp->MoveUp() == true)) {
			//set futurecost
			pp->futureCost = pp->cnt + calcCostFunc(pp);
			prioQue.push(pp);
			//iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 4) && (pp->MoveRight() == true)) {
			prioQue.push(pp);
			//iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 8) && (pp->MoveDown() == true)) {
			prioQue.push(pp);
			//iSet.insert(pp->state);
			pp = NULL;
		}
		else {
			delete pp;
		}
		pp = new puzzle(tempArr, p->cnt);
		if ((pp->lastMove != 6) && (pp->MoveLeft() == true)) {
			prioQue.push(pp);
			//iSet.insert(pp->state);
		}
		else {
			delete pp;
		}
		pp = NULL;
		prioQue.pop();
		p = NULL;
	}
	cout << "end!" << endl;
	int temp;
	cin >> temp;
}

long myPow(long a, long n) {
	long ret = 1;
	for (int i = 0; i < n; i++) {
		ret *= a;
	}

	return ret;
}

int max_int(int a, int b) {
	return (a > b) ? a : b;
}

int outOfPlace(puzzle * inputP) {
	
}

int manhattan(puzzle * inputP) {

}