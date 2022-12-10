#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;

class item
{
public:
	string facultyName;
	string groupName;
	string surname;
	double averageScore;
};

void fileFill() {
	string faculties[3] = { "economic","juridical","historical" };
	string groups[2] = { "O-21-PRI", "O-21-SPIS" };
	string surnames[3] = { "eliseev","gazdiev", "chernenko" };
	double averageScore[4] = { 4.12,3.8,4.5,4 };

	fstream file("data.txt");

	int facultiesCh = 0;
	int groupsCh = 0;
	string tmpfaculties;
	string tmpgroups;
	int i = 0;
	if (file.is_open()) {
		while (i<100)
		{
			if (facultiesCh == 0) {
				facultiesCh = rand() % 10 + 10;
				tmpfaculties = faculties[rand() % 3];
			}
			if (groupsCh == 0) {
				groupsCh = rand() % 5 + 5;
				tmpgroups = groups[rand() % 2];
			}
			file << tmpfaculties << " ";
			file << tmpgroups << " ";
			file << surnames[rand() % 3] << " ";
			file << averageScore[rand() % 4] << " ";
			file << "\n";
			facultiesCh--;
			groupsCh--;
			i++;
		}
	}
	file.close();
}

struct selectedGroup
{
	string facultyName;
	string groupName;
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 
	srand(time(0));
	//fileFill();
	vector<item> items;
	vector<int> groupIdx;
	vector<int> facultiesIdx;

	fstream file("data.txt");
	if (file.is_open()) {
		while (!file.eof())
		{
			item Item;

			file >> Item.facultyName;
			file >> Item.groupName;
			file >> Item.surname;
			file >> Item.averageScore;

			items.push_back(Item);
		}
	}

	int idx = 0;
	item Itemtmp = items[0];
	groupIdx.push_back(0);
	facultiesIdx.push_back(0);
	for (item Item : items) {
		if (Item.facultyName != Itemtmp.facultyName) {
			facultiesIdx.push_back(idx);
		}
		if (Item.groupName != Itemtmp.groupName || Item.facultyName != Itemtmp.facultyName) {
			groupIdx.push_back(idx);
			Itemtmp = Item;
		}
		idx++;
	}

	cout << "индексы первого уровня\n";
	for (int _item : facultiesIdx) {
		cout << _item << " ";
	}
	cout << endl;

	cout << "индексы второго уровня\n";
	for (int _item : groupIdx) {
		cout << _item << " ";
	}
	cout << endl;

	string faculties[3] = { "economic","juridical","historical" };
	string groups[2] = { "O-21-PRI", "O-21-SPIS" };
	selectedGroup Group;

	int cmd;
	cout << "выбирите факультет\n1 - экономический\n2 - юридический\n3 - исторический\n";
	cin >> cmd;
	Group.facultyName = faculties[cmd - 1];
	cout << "выбирите группу\n1 - O-21-при\n2 - O-21-СПИС\n";
	cin >> cmd;
	Group.groupName = groups[cmd - 1];

	double sum = 0;
	int count = 0;
	int index = 0;
	for (int _item : facultiesIdx) {
		if (items[_item].facultyName == Group.facultyName) {
			for (int i = distance(groupIdx.begin(), find(groupIdx.begin(), groupIdx.end(), _item)); i < groupIdx.size(); i++) {

				if (items[groupIdx[i]].groupName == Group.groupName && 
					items[groupIdx[i]].facultyName == Group.facultyName) {
					index = groupIdx[i];

					while (items[index].groupName == Group.groupName &&
						items[index].facultyName == Group.facultyName)
					{
						sum += items[index].averageScore;
						count++;
						index++;
					}
				}
			}
		}
	}


	if (count > 0) {
		cout << "средняя оченка";
		cout << endl << sum / count;
	}
	else {
		cout << "такая группа не найдена";
	}
}
