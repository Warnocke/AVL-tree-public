#include <iostream>
#include <sstream>
#include "AVL.h"

using namespace std;

int main(){

	AVL tree;
	string line;
	string commands;
	getline(cin, commands);
	int count = 0;
	int num_of_commands = stoi(commands);
	while(count < num_of_commands) {
		getline(cin, line);
		istringstream inStream(line);
		string function;
		getline(inStream, function,' ');
		string next;
		string next2;

		if(function == "insert") {
			string name;
			string ufid;

			getline(inStream, next,'"');
			getline(inStream, name,'"');
			getline(inStream, next2,' ');
			getline(inStream, ufid,'\n');
			tree.insert(name,ufid);
		}
		if(function == "remove") {
			string ufid;
			getline(inStream, ufid,'\n');
			tree.remove(ufid);
		}
		if(function == "search") {
			string ufid;
			string name;
			char nextChar = inStream.peek();
			if (nextChar == '"') {
				inStream.ignore();
				getline(inStream, name,'"');
				tree.search(name);
			}
			else {
				getline(inStream, ufid,'\n');
				tree.searchUFID(ufid);
			}
		}
		if(function == "printInorder") {
			tree.printInorder();
		}
		if(function == "printPreorder") {
			tree.printPreorder();
		}
		if(function == "printPostorder") {
			tree.printPostorder();
		}
		if(function == "printLevelCount") {
			tree.printLevelCount();
		}
		if(function == "removeInorder") {
			string num;
			getline(inStream, num,'\n');
			if (stoi(num)||num == "0") {
				tree.removeInOrder(stoi(num));
			}
		}
	count++;
	}



}
