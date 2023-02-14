#include "PersonGen.h"

bool PersonGen::ReadFile()
{
	ifstream male{ "FirstMale.txt" }, female{ "FirstFemale.txt" }, last{ "Last.txt" };

	// if bool usefile is not true, read other files
	if (!usefile) {
		try {
			if (male.good() && female.good() && last.good()) {
				int count{};
				string temp;

				while (male.good()) {
					getline(male, temp);
					firstMale.push_back(temp);
					++count;
				}
				fileLength = count;

				count = 0;
				while (female.good()) {
					getline(female , temp);
					firstFemale.push_back(temp);
					++count;
				}

				count = 0;
				while (last.good()) {
					getline(last, temp);
					lastNames.push_back(temp);
					++count;
				}
			}
			else
				throw;
		}
		catch (...) { 
			return false; 
		}
	}

	return true;
}

string PersonGen::NameGen()
{
	string name{};

	distribution = uniform_int_distribution<int>(0, fileLength-1);

	name += lastNames[distribution(eng)] + ", ";

	distribution = uniform_int_distribution<int>(0, 2);
	if (distribution(eng) == 1)
		maleFemale = true;
	else
		maleFemale = false;

	distribution = uniform_int_distribution<int>(0, fileLength-1);
	if (maleFemale)
		name += firstMale[distribution(eng)];
	else
		name += firstFemale[distribution(eng)];

	return name;
}

Person PersonGen::ReadUseFile()
{
	int m, d, y;
	string temp;
	Person p;

	getline(usefileStream, temp, '|');
	temp.pop_back();
	p.SetName(temp);

	getline(usefileStream, temp, '|');
	m = stoi(temp);

	getline(usefileStream, temp, '|');
	d = stoi(temp);

	getline(usefileStream, temp);
	y = stoi(temp);

	p.SetBirthday(m, d, y);

	// decrement lineCount and check if we are at end of file
	--lineCount;
	if (lineCount == 0)
		usefile = false;
		usefileStream.close();

	return p;
}

Date PersonGen::BirthdayGen(string name)
{
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int currentYear = (duration_cast<years> (system_clock::now().time_since_epoch())).count() + 1970;

	distribution = uniform_int_distribution<int>(young, old);

	int year = (currentYear - distribution(eng));

	if (year % 4 == 0)
		days[1] = 29;

	distribution = uniform_int_distribution<int>(1, 12);
	int month = distribution(eng);

	distribution = uniform_int_distribution<int>(1, days[month-1]);
	int day = distribution(eng);

	return Date(month, day, year, name);
}

PersonGen::PersonGen() : seed{ static_cast<int>(system_clock::now().time_since_epoch().count()) }
{
	fileReadOK = ReadFile();

	//seed engines
	eng.seed(seed);

}

PersonGen::PersonGen(int youngAge, int oldAge) : PersonGen()
{
	young = youngAge;
	old = oldAge;
}

Person PersonGen::GetPerson()
{

	if (usefile && usefileStream.good()) {
		Person p(ReadUseFile());
		return p;
	}

	else {
		string name(NameGen());
		Person p(name, BirthdayGen(name));
		return p;
	}
		

}

Person* PersonGen::GetNewPerson()
{
	
	Person* pp = new Person;

	if (usefile && usefileStream.good()) {
		*pp = ReadUseFile();
	}

	else {
		string name(NameGen());
		pp->SetName(name);
		pp->SetBirthday(BirthdayGen(name));
	}
		

	return pp;
}

bool PersonGen::IsTextFileRead()
{
	return fileReadOK;
}

bool PersonGen::CreateFile(string filename, int numOfPersons)
{
	ofstream out(filename);
	
	try {
		if (out) {
			for (int i{}; i < numOfPersons; ++i) {
				Person p = GetPerson();
				out << p.GetName() << " | " << p.GetBirthDay().GetMonth() << " | " << p.GetBirthDay().GetDay() << " | " << p.GetBirthDay().GetYear() << endl;
			}
		}
		else
			throw;
	}
	catch (...) { return false; }

	return true;
}

bool PersonGen::UseFile(string filename)
{
	usefileStream.open(filename);
	string temp;

	try {
		if (usefileStream) {
			getline(usefileStream, temp);
			lineCount = stoi(temp);
			usefile = true;
			return true;
		}
	}
	catch (...) {
		fileReadOK = false;
		return false;
	}
}