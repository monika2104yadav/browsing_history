#include <bits/c++config.h>
#include <cstdint>
#include <iostream>
#include <cstdio>
#include <map>
#include <pthread.h>
#include <vector>
#include <string>
#include <list>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

// NOTE: will have to implement smart pointers here. 
class String {
public:
	string url = "";
	String* next = nullptr;
	String* prev = nullptr;
	String(const string& _url) :url(_url) {}
	~String() { next = nullptr; prev = nullptr; }
};

class BrowserHistory {
	//String url_history; 
	String* current_url;
public:
	BrowserHistory(const string& home) {
		current_url = new String(home);
	}
	void visit(const string& url);
	string back(int backsteps);
	string forward(int forward_steps);
	~BrowserHistory() {
		while (current_url->prev != nullptr) {
			String* temp = current_url->prev->prev;
			delete current_url->prev;
			current_url->prev = temp;
		}
		delete current_url;
	}
};

// should clear forward history
void BrowserHistory::visit(const string& url) {

	string ret_string = url;

	String* visit_url = new String(url);

	String* currently_next = current_url->next;

	if (current_url) {
		current_url->next = visit_url;
		visit_url->prev = current_url;
	}
	current_url = visit_url;
	// clears forward history. 
	while (currently_next != nullptr) {
		String* temp = currently_next->next;
		delete currently_next;
		currently_next = temp;
	}

	//return ret_string;
}

string BrowserHistory::back(int backsteps) {
	int index = 0;
	while (index < backsteps) {
		if (current_url->prev != nullptr)
			current_url = (current_url->prev);
		index++;
	}

	return current_url->url;
}

string BrowserHistory::forward(int nextsteps) {
	int index = 0;
	while (index < nextsteps) {
		if (current_url->next != nullptr)
			current_url = (current_url->next);
		index++;
	}

	return current_url->url;
}

int main() {
	BrowserHistory browser("leetcode.com");
	browser.visit("google.com");
	browser.visit("facebook.com");
	browser.visit("youtube.com");

	string output = browser.back(1);
	cout << output << endl;
	output = browser.back(1);
	cout << output << endl;
	//output = browser.forward(1);
	//cout<<output<<endl;

	browser.visit("linkedin.com");

	//output = browser.forward(2);
	//cout<<output<<endl;
	output = browser.back(2);
	cout << output << endl;
	output = browser.back(7);
	cout << output << endl;
}