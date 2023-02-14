//Aaron Grycner, agrycner@cnm.edu, GrycnerP2

#include "PersonGen.h"
#include <iostream>

int main() {

	cout << "\nAaron Grycner, GrycnerP2\nThe Person Generator\n\n";

	string filename("file.txt");
	int counter{};
	PersonGen* pgen = new PersonGen(10, 50);

	pgen->IsTextFileRead() ? cout << "\nFiles read ok!\n" : cout << "\nError reading files!\n";

	// test stack array and persons

	Person array[10];
	for (Person p : array) {
		p = pgen->GetPerson();
		cout << p.GetFullDesc() << "    INDEX: " << counter << "   ";
		++counter;
	}

	cout << endl;

	// test heap array with persons
	try {
		Person* ppPerson = nullptr;

		ppPerson = new Person[10];

		for (int i{}; i < 10; ++i) {
			ppPerson[i] = pgen->GetPerson();
			cout << ppPerson[i].GetFullDesc() << "    INDEX: " << i;
		}
		delete[] ppPerson;
	}
	catch (...) { cout << "\nHeap Allocation Error!\n"; }


	cout << endl;

	try {
		Person* ppArray[10];

		// test array of pointers to heap persons
		counter = 0;

		for (Person* p : ppArray) {
			p = pgen->GetNewPerson();
			cout << p->GetFullDesc() << "    INDEX: " << counter << "   ";
			delete p;
			++counter;
		}
	}
	catch (...) { cout << "\nHeap Allocation Error!\n"; }


	cout << endl;


	try {
		Person** pppArray = new Person * [10];

		//test heap array with pointers to heap persons
		for (int i{}; i < 10; ++i) {
			pppArray[i] = pgen->GetNewPerson();
			cout << pppArray[i]->GetFullDesc() << "    INDEX: " << i << "   ";
			delete pppArray[i];
		}
		delete[] pppArray;

	}
	catch (...) { cout << "\nHeap Allocation Error!\n"; }

	cout << endl;

	// test usefile

	if (pgen->UseFile("PersonGenTest15.txt"))
		cout << "\n\nFile found!\n\n";
	else
		cout << "\n\nError locating requested file...\n\n";


	for (int i{}; i < 20; ++i) {
		cout << pgen->GetPerson().GetFullDesc() << "    INDEX: " << i << "   ";
	}

	// test createfile

	if (pgen->CreateFile("me.txt", 10))
		cout << "\n\nfile created successfully!\n";
	else
		cout << "\n\nError creating file\n";

	// testing file use of custom file
	pgen->UseFile("me.txt");

	for (int i{}; i < 15; ++i) {
		cout << pgen->GetPerson().GetFullDesc() << "    INDEX: " << i << "   ";
	}

	cout << endl;

	// test alternate between getperson and getnewperson
	cout << pgen->GetPerson().GetFullDesc();
	cout << pgen->GetNewPerson()->GetFullDesc();
	cout << pgen->GetPerson().GetFullDesc();
	cout << pgen->GetNewPerson()->GetFullDesc();

	cout << endl;

	if (!pgen->UseFile("gumbo.txt"))
		cout << "\n\nError locating requested file...\n\n";
	else
		cout << "\n\nFile found!\n\n";

	for (int i{}; i < 5; ++i) {
		cout << pgen->GetPerson().GetFullDesc() << "    INDEX: " << i << "   ";
	}

	delete pgen;

	return 0;
}