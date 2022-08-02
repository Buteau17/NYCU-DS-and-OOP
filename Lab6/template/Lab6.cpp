﻿#include "role.h"
#include "magician.h"
#include "warrior.h"
#include "archer.h"
#include "staff.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;



int main() {
	
	// TODO : Read the file
	// 1. Read the input file to get the information
	ifstream inputFile;
	inputFile.open("input2.txt");
	string s;
	getline(inputFile, s);

	//cout << "S " << s << ' ' << s.size() << '\n';
	Role* role[1000];
	int lines = 6;
	for (int i = 0; i<lines; i++) {
		getline(inputFile, s);
		//cout << "S " << s << ' ' << s.size() << '\n';
		string name, type;
		int a, b, c;
		string tmp = "";
		string str[5];
		int cnt = 0;
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == ',') {
				str[cnt++] = tmp;
				//cout << "tmp " << tmp << endl;
				tmp = "";
				j++;
				continue;
			}
			tmp += s[j];
		}
		str[cnt++] = tmp;
		tmp = "";
		name = str[0];
		//cout << "name " << name << endl;
		type = str[1];
		//cout << str[2] << endl;
		a = stoi(str[2]);
		b = stoi(str[3]);
		c = stoi(str[4]);
		if (type == "Warrior") {
			 role[i]= new Warrior(name , a , b , c );
			role[i]->printAllInfo();
			role[i]->ShowRole();
			cout << endl;
		}
		else if (type == "Archer") {
			 role[i] = new Archer(name, a, b, c);
			role[i]->printAllInfo();
			role[i]->ShowRole();
			cout << endl;

		}
		else {
			role[i]= new Magician(name, a , b, c);
			 role[i]->printAllInfo();
			 role[i]->ShowRole();
			 cout << endl;

		}
	}
	
	// TODO : Create the Role according to the input file
	// 1. Create the role
	// 2. Print this role's Infomation
	// 3. Show Role ( refer to spec )
	// Example :
	// -------------------------------------------------------
	//Role* warrior = new Warrior( warrior's Name, warrior's Level, warrior's Money, warrior's HP);
	//warrior->printAllInfo();
	//warrior->ShowRole();
	 //cout << endl;
	
	//Role* archer = new Archer(archer's Name, archer's Level, archer's Money, archer's HP);
	//archer->printAllInfo();
	//archer->ShowRole();
	//cout << endl;
	// 
	// Role* magician = new Magician(magician's Name, magician's Level, magician's Money, magician's HP);
	// magician->printAllInfo();
	// magician->ShowRole();
	// cout << endl;
	// -------------------------------------------------------
	// HINT : Not necessarily just three roles


	Staff* staff = new Staff("flame");
	cout << "Checking whether the role can equip a staff.." << endl;

	//
	// TODO : Check wheather all characters can get staff or not
	// Example :
	// -------------------------------------------------------
	//staff->equipable(warrior);
	// staff->equipable(archer);
	 //staff->equipable(magician);
	for (int i = 0; i < lines; i++) {
		staff->equipable(role[i]);
	}

	// -------------------------------------------------------
	// HINT : Not necessarily just three roles
	cout << endl;




	system("PAUSE");
	return 0;
}