// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
struct List {
	int info;
	List * next;
};
struct Data {
	int data;
	Data *next;
	Data *prev;
};
void makeListCon(bool(*cond)(int),List *oldP, List *&newP) {
	if (oldP != NULL) {
		if (cond(oldP->info)) {
			List *r = new List();
			newP->next = r;
			r->next = NULL;
			r->info = oldP->info;
			newP = r;
		}
		makeListCon(cond ,oldP->next, newP);
	}
	else newP->next = NULL;
}
void makeListCon(List *oldP, List *&newP) {
	if (oldP != NULL) {
		if (oldP->info < 0) {
			List *r = new List();
			newP->next = r;
			r->next = NULL;
			r->info = oldP->info;
			newP = r;
		}
		makeListCon(oldP->next, newP);
	}
	else newP->next = NULL;
}
void replaceSimpleCon(List *&p, int n) {
	if (p == NULL) return;
	if (p->info > 0) p->info = n;
	replaceSimpleCon(p->next, n);
}
void replaceWithNifCon(bool(*cond)(int,int), List *&p, int n)
{
	cout << "Step" << endl;
	if (p != NULL) {
		if (cond(p->info, 5)) p->info = n;
		replaceWithNifCon(cond, p->next, n);
	}
}
int sumConRec(bool(*func)(int), List* p) {
	if (p == NULL) return 0;
	if (func(p->info)) return p->info + sumConRec(func, p->next);
	else return sumConRec(func, p->next);

}
int prodConRec(bool(*func)(int), List* p) {
	if (p == NULL) return 1;
	if (func(p->info)) return p->info * prodConRec(func, p->next);
	else return prodConRec(func, p->next);

}
void insertAfter(Data *&p, int x) {
	Data *r = new Data();
	r->data = x;
	if (p->next == NULL) {
		r->next = NULL;
	}
	else {
		r->next = p->next;
		p->next->prev = r;
	}
	p->next = r;
	r->prev = p;
	p = r;
}
void insertBefore(Data *&p, int x, Data *&h) {
	Data *r = new Data();
	r->data = x;
	if (p == h) {
		r->prev = NULL;
		h = r;
	}
	else {
		r->prev = p->prev;
		p->prev->next = r;
	}
	r->next = p;
	p->prev = r;
}
void removeElem(Data *&el, Data *&h) {
	Data * temp = NULL;
	if (el->next == NULL && el->prev == NULL) {
		temp = el;
		el = NULL;
		delete temp;
		return;
	}
	else if (el->prev == NULL) {
		temp = el;
		el = el->next;
		temp->next->prev = NULL;
		h = temp->next;
		delete temp;
		return;
	}
	else if (el->next == NULL) {
		temp = el;
		el = NULL;
		temp->prev->next = NULL;
		delete temp;
		return;
	}
	else {
		temp = el;
		el = el->next;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
		return;
	}
}
void deleteList(Data *h) {
	Data *p = h;
	while (p != NULL) {
		Data* r = p;
		p = p->next;
		delete r;
	}
}
void outputList(Data* h) {
	Data *pout = h;
	while (pout != NULL) {
		cout << pout->data << endl;
		pout = pout->next;
	}
}
bool fib(int n) {
	int a = 0;
	int b = 1;
	while (n > a || n > b) {
		if (a == n || b == n) return true;
		if (b > a)
			a += b;
		else b += a;
	}
	return false;
}
int firstDig(int num)
{
	int n = abs(num);
	while (n > 9) n /= 10;
	return n % 10;
}
bool isPerfect(int n) {
	if (n < 5)
		return false;
	int su = 0;
	for (int i = 1; i < n; i++)
		if (n%i == 0) su += i;
	if (n == su) return true;
	else return false;
}
int digSum(int n) {
	int sum = 0;
	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}
bool hasDigit(int n, int k) {
	while (n > 0) {
		if (n % 10 == k) return true;
		n /= 10;
	}
	return false;
}
bool isSimple(int n) {
	if (n < 2) return false;
	for (int i = 2; i <= n / 2; i++) 
		if (n%i == 0) return false;
	return true;
}
Data* createNewNum(int n) {
	int x;
	cin >> x;
	if (n > 0) {
		Data *head = new Data;
		head->next = NULL;
		head->data = x;
		Data *p = head;
		for (int i = 1; i < n; i++) {
			cin >> x;
			Data *r = new Data;
			r->next = NULL;
			p->next = r;
			r->data = x;
			p = r;
		}
		return head;
	}
	else return NULL;
}
Data* createNew0() {
	int x;
	cin >> x;
	if (x != 0) {
		Data *head = new Data;
		head->next = NULL;
		head->data = x;
		head->prev = NULL;
		Data *p = head;
		cin >> x;
		while (x!=0) {
			Data *r = new Data;
			r->next = NULL;
			r->prev = p;
			p->next = r;
			r->data = x;
			p = r;
			cin >> x;
		}
		return head;
	}
	else return NULL;
}
List * createList0() {
	int x;
	cin >> x;
	if (x != 0) {
		List * head = new List();
		head->next = NULL;
		head->info = x;
		List * p = head;
		cin >> x;
		while (x != 0) {
			List * r = new List();
			r->next = NULL;
			p->next = r;
			r->info = x;
			p = r;
			cin >> x;
		}
		return head;
	}
	else return NULL;
}
void deleteList(List *h) {
	List * p = h;
	while (p != NULL) {
		List * r = p;
		p = p->next;
		delete r;
	}
}
void outputList(List *h) {
	List * p = h;
	while (p != NULL) {
		cout << p->info << endl;
		p = p->next;
	}
}
void deleteCircleList(Data *h) {
	Data *p = h;
	do {
		Data *r = p;
		p = p->next;
		delete r;
	} while (p != h);
}
Data* createNewCircle0() {
	int x;
	cin >> x;
	if (x != 0) {
		Data * head = new Data();
		head->next = head;
		head->prev = head;
		head->data = x;
		Data * p = head;
		cin >> x;
		do { 
			Data *r = new Data();
			p->next = r;
			r->next = NULL;
			r->prev = p;
			r->data = x;
			p = r;
			cin >> x;
		} while (x != 0);
		p->next = head;
		head->prev = p;
		return head;
	}
	else return NULL;
}
void outputCircleList(Data *h) {
	Data * p = h;
	do {
		cout << p->data << endl;
		p = p->next;
	} while (p != h);
}
void removeElemCircle(Data *&p, Data *&h) {
		Data * r = p;
		//cout << "elem remove";
		r->prev->next = r->next;
		r->next->prev = r->prev;
		if (p == p->next && p == p->prev) {
			p = NULL;
			delete r;
			return;
		}
		if (p == h) h = r->next;
		p = p->next;
		delete r;
}
void insertElemCircleAfter(Data *&p, int n) {
	Data * r = new Data();
	r->data = n;
	p->next->prev = r;
	r->next = p->next;
	r->prev = p;
	p->next = r;
	p = r;
}
void insertElemCircleBefore(Data *&p, Data *&h, int n) {
	Data * r = new Data();
	r->data = n;
	r->next = p;
	r->prev = p->prev;
	p->prev->next = r;
	p->prev = r;
	if (p == h) r = h;
}
int main()
{
	int k;
	int product = 1;
	int sum = 0;
	int count = 0;
	bool flag = 1;
	Data * head = createNewCircle0();
	Data * p = head;
	do {
		if (p->data < 0) sum += abs(p->data);
		p = p->next;
	} while (p != head);
	p = head;
	do{
		if (p->data % 2) insertElemCircleBefore(p, head, sum);
		p = p->next;
	
	
	} while (p != head);
	/*while (p == head) {
		if (hasDigit(p->data, 5)) removeElemCircle(p, head);
		else p = p->next;
	}
		if (p != NULL) {
		do {
			if (hasDigit(p->data, 5)) {
				removeElemCircle(p, head);
				if (p == NULL) break;

			}
			else p = p->next;
		} while (p != head);
	}
	*/
	outputCircleList(head);
	deleteCircleList(head);
	/*Data *r = head;
	do {
		p = p->next;
	
	} while (p->next != head);
	do {
		if (p->data != r->data) {
			flag = 0;
			break;
		}
		p = p->next;
		r = r->prev;
	} while (p != head);
	cout << flag;
	*/
	/*cout << "Input list 1 :";
	List * head1 = createList0();
	cout << "Input list 2 :";
	List * head2 = createList0();
	List * head3 = new List();
	head3->next = NULL;
	List * p1 = head1;
	List *p2 = head2;
	List *p3 = head3;
	while (p1 != NULL) {
		if (!hasDigit(p1->info, 1)) {
			List * r = new List();
			r->next = NULL;
			p3->next = r;
			r->info = p1->info;
			p3 = r;
		}
		p1 = p1->next;
	}
	while (p2 != NULL) {
		if (!hasDigit(p2->info, 1)) {
			List * r = new List();
			r->next = NULL;
			p3->next = r;
			r->info = p2->info;
			p3 = r;
		}
		p2 = p2->next;
	}
		List * r = head3;
		head3 = head3->next;
		delete r;
	// << "Input k" << endl;
	//cin >> k;
	/*while (p->next != NULL) {
		if ((p->data) <= p->next->data) {
			flag = false;
			break;
		}
		p = p->next;
	}
	p = head;
	if (flag) {
		while (p != NULL) {
			if (digSum(p->data) % 2 == 0)
				product *= p->data;
			p = p->next;
		}
		cout << product;
	}
	else {
		while (p != NULL) {
			if (p->data % 10 == 3)
				p->data = digSum(p->data);
			p = p->next;
		}
		outputList(head);
	}
	/*if (flag) {
		while (p != NULL) {
			if (p->data > 0)
				sum += p->data;
			p = p->next;
		}
		p = head;
		while (p != NULL) {
			if (p->data % 3 == 0)
				p->data = sum;
			p = p->next;
		}
	}
	*/

	//p = p->next;
	//int min = head->data;
	/*while (p != NULL) {
		if (p->data > 0)
			count++;
		p = p->next;
	}
	*/

	/*if (isSimple(head->data)) {
		Data *r = new Data;
		r->next = head;
		r->data = 13;
		head = r;
	}
	cout << isSimple(4);
	/*Data* min = head;
	while (p != NULL) {
		if (min->data > p->data)
			min = p;
		p = p->next;
	}
	cout << min->data;
	*/
	//outputList(head3);
	//deleteList(head1);
	//deleteList(head2);
	//deleteList(head3);
	system("pause");

    return 0;
}

