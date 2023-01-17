#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
using namespace std;

class Friend
{
private:
	char name[100];
	char email[50];
	int no_of_friends;
	int profile;

public:
	Friend()
	{
		strcpy(name, " ");
		strcpy(email, " ");
		no_of_friends = 0;
		profile = 0;
	}
	void create();
	void view();
	void add();
	int search(char n[100]);
	void remove(char n[100]);
	void loading(string);

	// ~Friend();
};

// MAIN MENU FUNCTION

void mainmenu()
{
	Friend obj;
	system("cls");

	system("Color 0E");
	char ch;
	while (1)
	{
		cout << "\n\n\n\n\n\n\n";
		cout << setw(20);
		for (int i = 0; i <= 109; i++)
			cout << "*";
		cout << "\n\n";
		cout << "\t\t\t1:Create your profile\n\n";
		cout << "\t\t\t2:Search a profile\n\n";
		cout << "\t\t\t3:View your profile\n\n";
		cout << "\t\t\t4:Add friend\n\n";
		cout << "\t\t\t5:Remove friend\n\n";
		cout << "\t\t\t0:Quit\n\n";
		cout << setw(20);
		for (int i = 0; i <= 109; i++)
			cout << "*";

		cout << "\n\n\n";
		cout << setw(45) << "Please enter your choice... ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			obj.create();
			break;

		case '2':
			char nn[100];
			cout << "\n\n\tEnter friend to be searched: ";
			fflush(stdin);
			gets(nn);
			if (obj.search(nn) == 1)
			{
				cout << "\n\n\tFound\n";
				ifstream in("friendlist.txt");
				while (in.eof() == 0)
				{
					string st;
					getline(in, st);
					string word = "";
					for (int i = 0; i < st.size(); i++)
					{
						if (st[i] == ' ')
						{
							if (word == nn)
							{
								in.close();
								cout << "\n\n\t" << st << "\n";
								break;
							}
							word = "";
						}
						else
						{
							word = word + st[i];
						}
					}
				}
				in.close();
			}
			else if (obj.search(nn) == 0)
				cout << "\n\n\tNot Found\n";
			else
				cout << "\n\n\tNo friends to search\n";
			break;
		case '3':
			obj.view();
			break;
		case '4':
			obj.add();
			break;
		case '5':
			char n[100];
			cout << "\n\n\tEnter friend to be removed: ";
			fflush(stdin);
			gets(n);
			obj.remove(n);
			break;
		case '0':
			exit(0);
		default:
			Sleep(10);
			cout << "\n\n"
				 << setw(110) << "INVALID CHOICE!!\n\n";
		}
	}
}
// }Sleep (120);mainmenu();	}

// CREATE PROFILE FUNCTION

void Friend::create()
{
	Friend::loading(" CREATING PROFILE ");

	if (profile == 0)
	{
		system("cls");
		fflush(stdin);
		cout << "\n\n\tEnter your name: ";
		gets(name);
		fflush(stdin);
		cout << "\n\n\tEnter your email: ";
		cin >> email;
		ofstream out("friendlist.txt", ios::app | ios::out);
		if (no_of_friends == 0)
		{
			out << "S.No Name email-address\n";
		}
		out.close();
		profile++;
	}
	else
	{
		cout << "\n\n"
			 << setw(45) << "Profile can only be created once !!";
	}

	// mainmenu();
}

// FUNCTION TO ADD FRIEND

void Friend::add()
{Friend::loading(" ADDING PROFILE PROFILE ");
	char fname[100];
	char femail[50];
	system("cls");
	fflush(stdin);
	cout << "\n\n\tEnter your Friend's name: ";
	gets(fname);
	fflush(stdin);
	if (search(fname) == 1)
	{
		cout << "\n\n"
			 << setw(45) << "You cannot add friends with same initial name\n";
	}
	else
	{
		cout << "\n\n\tEnter your friend's email: ";
		cin >> femail;
		ofstream out("friendlist.txt", ios::app | ios::out);
		no_of_friends++;
		out << no_of_friends << " " << fname << " " << femail << endl;
		out.close();
	}
	// }mainmenu();
}

// FUNCTION TO VIEW PROFILE

void Friend::view()
{
	Friend::loading(" VIEWING PROFILE ");
	system("cls");
	string st;
	cout << "\n\n\tYour Profile:";
	cout << "\n\n\tName: " << name << endl;
	cout << "\n\n\tEmail: " << email << endl;
	cout << "\n\n\tNo of Friends: " << no_of_friends << endl;

	if (no_of_friends != 0)
	{
		cout << "\n\n\tFriendlist: \n";
		ifstream in("friendlist.txt");
		while (in.eof() == 0)
		{
			getline(in, st);
			cout << "\t" << st << endl;
		}
		in.close();
	}
	// Sleep (120);
	// mainmenu();
}

// FUNCTION TO SEARCH FRIEND

int Friend::search(char nn[100])
{
	Friend::loading(" SEARCHING PROFILE ");
	system("cls");
	if (no_of_friends != 0)
	{
		ifstream in("friendlist.txt");
		while (in.eof() == 0)
		{
			string st;
			getline(in, st);
			string word = "";
			for (int i = 0; i < st.size(); i++)
			{
				if (st[i] == ' ')
				{
					if (word == nn)
					{
						in.close();
						return 1;
					}
					word = "";
				}
				else
				{
					word = word + st[i];
				}
			}
		}
		in.close();
		return 0;
	}
	else


	{
		return -1;
	}
	mainmenu();
}

// FUNCTION TO REMOVE FRIEND

void Friend::remove(char nn[100])
{
	Friend::loading(" REMOVING PROFILE ");
	system("cls");
	if (search(nn) == 1)
	{
		if (no_of_friends != 0)
		{
			ifstream in("friendlist.txt"); // read
			ofstream out("temp.txt");	   // write
			while (in.eof() == 0)
			{
				string st;
				getline(in, st);
				string word = "";
				int flag = 0;
				for (int i = 0; i < st.size(); i++)
				{
					if (st[i] == ' ')
					{
						if (strcmp(nn, word.c_str()) == 0)
						{
							flag = 1;
							cout << "\n\n\tFRIEND REMOVED!!!";
							break;
						}
						word = "";
					}
					else
					{
						word = word + st[i];
					}
				}
				if (flag == 1)
				{
					getline(in, st);
				}
				out << st << "\n";
			}
			out.close(); // temp close
			in.close();	 // friendlist close
			ofstream out1("friendlist.txt");
			out1.clear();
			ifstream in1("temp.txt");
			int count = 0;
			while (in1.eof() == 0)
			{
				string st;
				string word;
				getline(in1, st);
				if (count == 0)
				{
					out1 << st << "\n";
				}
				else if (count > 0)
				{
					st = st + " ";
					if (st == " ")
						break;
					int c = 0;
					for (int i = 0; i < st.size(); i++)
					{
						if (st[i] == ' ')
						{
							c++;
							if (c == 1)
							{
								out1 << count << " ";
							}
							else
							{
								out1 << word << " ";
							}
							word = "";
						}
						else
						{
							word = word + st[i];
						}
					}
					out1 << "\n";
				}
				count++;
			}
			out1.close();
			in1.close();
			ofstream out2("temp.txt");
			out2.clear();
			out2.close();

			no_of_friends -= 1;
		}
		else
		{
			cout << "\n\n\tYou don't have any friends to delete\n";
		}
	}
	else if (search(nn) == 0)
	{
		cout << "\n\n\tThis friend is not present\n";
	}
	else
	{
		cout << "\n\n\tNo friends to delete\n";
	}
	mainmenu();
}

// LOADING SCREEN

void Friend::loading(string a)
{

	string x = a;
	cout << "\n";
	int j, z = 0;
	for (j = 0; j <= 45; j++)
	{
		Sleep(30);
		cout << "\xDB";
	}
	for (int j = 0; j <= z; j++)
	{
		Sleep(60);
		cout << x;
	}
	for (int j = 0; j <= 45; j++)
	{
		Sleep(30);
		cout << "\xDB";
	}
}

// class User : private Friend {
// 	set_p();
//             cout<<"Enter the  Name:";
//             fflush(stdin);
//             cin.getline(firendlist,50);
//             cout<<"Enter the Course Fee:";
//             cin>>fee;
// }

// MAIN FUNCTION

int main()
{
	system("cls");

	system("Color 0A");
	cout << "\n\n\n\n\n\n\n";

	cout << setw(30);
	for (int i = 0; i <= 99; i++)
		cout << "*";

	cout << "\n\n";

	cout << setw(90) << "WELCOME TO FINDERRR\n\n";

	cout << setw(115) << "Designed and Coded By : Ashutosh Jha, Gourav Goyal and Gurleen kaur\n\n\n";

	cout << setw(85) << "Submitted To:\n";
	cout << setw(88) << " Mr. Rahul Agarwal\n\n";

	cout << setw(30);
	for (int i = 0; i <= 99; i++)
		cout << "*";

	cout << "\n\n\n\n\n\n\n\n\n";
	cout << setw(45) << "Press any key to continue....." << endl;
	getch();
	mainmenu();
	return 0;
}
