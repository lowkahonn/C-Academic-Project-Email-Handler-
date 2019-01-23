#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
class cEmail
{
public:
	cEmail() { ; }
	~cEmail() { ; }
	char *getTo_From();
	char *getSubject();
	char *getCc();
	char *getMessage();
	int getDate();
	bool getTF();
	void setTo_From(char*, char*);
	void setSubject(char*);
	void setCc(char*);
	void setMessage(char*);
	void setDate(int);
private:
	char To_From[2048];
	char Subject[4096];
	char Cc[2048];
	char Message[32768];
	int Date;
	bool TF;
};

char *cEmail::getTo_From()
{
	return To_From;
}
char *cEmail::getSubject()
{
	return Subject;
}
char *cEmail::getCc()
{
	return Cc;
}
char *cEmail::getMessage()
{
	return Message;
}
int cEmail::getDate()
{
	return Date;
}
bool cEmail::getTF()
{
	return TF;
}
void cEmail::setTo_From(char* nm_em_tf, char *tf)
{
	strcpy(To_From, nm_em_tf);
	if (strcmp(tf, "T") == 0)
		TF = true;
	else if (strcmp(tf, "F") == 0)
		TF = false;
}
void cEmail::setSubject(char *sub)
{
	strcpy(Subject, sub);
}
void cEmail::setCc(char *cc)
{
	strcpy(Cc, cc);
}
void cEmail::setMessage(char *msg)
{
	strcpy(Message, msg);
}
void cEmail::setDate(int date)
{
	Date = date;
}

class Em_Han
{
public:
	Em_Han() { em = new cEmail[100]; noem = 0; }
	~Em_Han() { delete[] em; }
	void DisplayContent();
	void SortContent();
	void AddContent();
	void DeleteContent();
	void InputData(char*);
	void UpdateData(char*);
	int getnoem();
private:
	cEmail *em;
	int noem;
};
void Em_Han::DisplayContent()
{
	if (noem != 0)
	{
		for (int i = 0; i < noem; i++)
		{
			cout << endl;
			cout << "Name [address]\t: " << em[i].getTo_From() << endl;
			cout << "Cc\t\t: " << em[i].getCc() << endl;
			cout << "Subject\t\t: " << em[i].getSubject() << endl;
			cout << "Message\t\t: " << em[i].getMessage() << endl;
			if (em[i].getDate() >= 100000)
			cout << "Date\t\t: " << em[i].getDate() << endl;
			else
		    cout << "Date\t\t: " << '0' << em[i].getDate() << endl;
			cout << "*****************************************************" << endl;
		}
	}
	else
		cout << "There is no emails in your mailbox!\n";
}
void Em_Han::SortContent()
{
	if (noem != 0)
	{
		for (int i = 0; i < noem; i++)
		{
			for (int j = 0; j < noem; j++)
			{
				char nm[2048]; //to store the to-from string
				char sub[4096];
				char msg[32768];
				char cc[2048];
				int date;
				if (i != j && (strcmp(em[i].getTo_From(), em[j].getTo_From()) == -1) && !(em[i].getTF()) && !(em[j].getTF()))
				{
					//copy to temporary memory
					strcpy(nm, em[i].getTo_From());
					strcpy(sub, em[i].getSubject());
					strcpy(msg, em[i].getMessage());
					strcpy(cc, em[i].getCc());
					date = em[i].getDate();
					//i to be j
					em[i].setTo_From(em[j].getTo_From(), "F");
					em[i].setSubject(em[j].getSubject());
					em[i].setCc(em[j].getCc());
					em[i].setMessage(em[j].getMessage());
					em[i].setDate(em[j].getDate());
					//j to be temp
					em[j].setTo_From(nm, "F");
					em[j].setSubject(sub);
					em[j].setCc(cc);
					em[j].setMessage(msg);
					em[j].setDate(date);
				}
			}
		}
		for (int i = 0; i < noem; i++)
		{
			if (!(em[i].getTF()))
			{
				cout << endl;
				cout << "Name [address]\t: " << em[i].getTo_From() << endl;
				cout << "Subject\t\t: " << em[i].getSubject() << endl;
				if (em[i].getDate() > 100000)
					cout << "Date\t\t: " << em[i].getDate() << endl;
				else
					cout << "Date\t\t: 0" << em[i].getDate() << endl;
				cout << "*****************************************************" << endl;
			}
		}
	}
	else
		cout << "There is no emails in your mailbox!\n";
}
void Em_Han::AddContent()
{
	char a; //clear buffer
	char nm[2048];
	char email[2048];
	char message[32768];
	char subject[4096];
	char ccem[2048];
	char ccname[2048];
	char tf[10];
	int date;
	char ccornot;
	bool exitflag = false;
	if (noem <= 100)
	{
		cout << "Is it a sent-to-receiver email(T) or received-from-sender(F) email? " << endl;
		while (!exitflag)
		{
			cin >> tf;
			if (strcmp(tf, "T") == 0)
			{
				cout << "Enter the name of receiver: " << endl;
				exitflag = true;
			}
			else if (strcmp(tf, "F") == 0)
			{
				cout << "Enter the name of sender: " << endl;
				exitflag = true;
			}
			else
				cout << "Error! Please input only 'T' or 'F': ";
		}
		cin.get(a);
		cin.getline(nm, 2047);
		cout << "Email address: ";
		cin >> email;
		cout << "Do you want to cc someone? (Y/N)  ";
		cin >> ccornot;
		if (ccornot == 'Y')
		{
			cout << "Cc to (name): ";
			cin.get(a);
			cin.getline(ccname, 2047);
			cout << "Cc to (address): ";
			cin >> ccem;
		}
		cout << "Subject: ";
		cin.get(a);
		cin.getline(subject, 4096);
		cout << "Message: " << endl;
		cin.getline(message, 32767);
		cout << "Date (YYMMDD): ";
		cin >> date;
		//combine name, email and to from status
		char space[] = " ";
		char leftbrac[] = "[";
		char rightbrac[] = "]";
		strcat(nm, space);
		strcat(nm, leftbrac);
		strcat(nm, email);
		strcat(nm, rightbrac);
		strcat(nm, space);
		strcat(nm, tf);
		//combine cc name and email
		if (ccornot == 'Y')
		{
			strcat(ccname, space);
			strcat(ccname, leftbrac);
			strcat(ccname, ccem);
			strcat(ccname, rightbrac);
		}
		//set all the information into the array
		em[noem].setTo_From(nm, tf);
		if (ccornot == 'Y')
			em[noem].setCc(ccname);
		else if (ccornot == 'N')
			em[noem].setCc("");
		em[noem].setSubject(subject);
		em[noem].setMessage(message);
		em[noem].setDate(date);
		//number of email +1
		noem++;
	}
	else
	{
		cout << "The mailbox is full!" << endl;
	}
}
void Em_Han::DeleteContent()
{
	int i;
	char null[1];
	null[0] = NULL;
	if (noem != 0)
	{
		cout << "Enter the index of the email you want to delete: ";
		cin >> i;
		for (i; i < (noem - 1) && (i >= 0); i++) //if index 1 is deleted, index 2 become index 1, 3 become 2, ...
		{
			if ((em[i + 1].getTF()))
			{
				em[i].setTo_From(em[i + 1].getTo_From(), "T");
			}
			else
			{
				em[i].setTo_From(em[i + 1].getTo_From(), "F");
			}
			em[i].setSubject(em[i + 1].getSubject());
			em[i].setCc(em[i + 1].getCc());
			em[i].setMessage(em[i + 1].getMessage());
			em[i].setDate(em[i + 1].getDate());
		}
		//last object to be null
		em[noem].setTo_From(null, null);
		em[noem].setSubject(null);
		em[noem].setCc(null);
		em[noem].setMessage(null);
		em[noem].setDate(0);
		noem--;
	}
	else
		cout << "There is no emails in your mailbox!\n";
}
void Em_Han::InputData(char *uname)
{
	char a, b[5], nm_ad_tf[2048], cc[2048], sub[4096], msg[32768], date[8], filename[80], trash[5];
	int dtno = 0, dt;
	strcpy(filename, uname);
	strcat(filename, ".txt");
	ifstream r(filename);
	while (r.get(a))
	{
		if (a == '#')
			dtno++;
	}
	r.close();
	ifstream read(filename);
	for (int i = 0; i < dtno; i++)
	{
		dt = 0;
		read.getline(trash, 4);
		read.getline(nm_ad_tf, 2047);
		read.getline(cc, 2047);
		read.getline(sub, 4095);
		read.getline(msg, 32767);
		read.getline(date, 7);
		for (int j = 0; j < (strlen(nm_ad_tf)); j++)
		{
			if (nm_ad_tf[j] == 'T' && nm_ad_tf[j + 1] == '\0') // it is a null character after 'T' or 'F'
				strcpy(b,"T");      //need to set b as a "T" string
			else if (nm_ad_tf[j] == 'F' && nm_ad_tf[j + 1] == '\0')
				strcpy(b, "F");
		}
		for (int k = 0; k < 6; k++)
		{
				int c = 0;
				c = date[k] - '0';
				if (k == 0)
					c *= 100000;
				if (k == 1)
					c *= 10000;
				if (k == 2)
					c *= 1000;
				if (k == 3)
					c *= 100;
				if (k == 4)
					c *= 10;
				if (k == 5)
					c *= 1;
				dt += c;
		}
		em[i].setTo_From(nm_ad_tf, b);
		em[i].setCc(cc);
		em[i].setSubject(sub);
		em[i].setMessage(msg);
		em[i].setDate(dt);
		noem++;
	}
	read.close();
}
void Em_Han::UpdateData(char *uname)
{
	char filename[80];
	strcpy(filename, uname);
	strcat(filename, ".txt");
	ofstream update(filename);
	for (int i = 0; i < noem; i++)
	{
		update << '#' << i+1 << endl;
		update << em[i].getTo_From() << endl;
		if (strcmp(em[i].getCc(), "") != 0)
			update << em[i].getCc() << endl;
		else
			update << endl;
		update << em[i].getSubject() << endl;
		update << em[i].getMessage() << endl;
		if (em[i].getDate() > 100000) 
			update << em[i].getDate() << endl;
		else
			update << "0" << em[i].getDate() << endl;
	}
	update.close();
 }
int Em_Han::getnoem()
{
	return noem;
}

bool menu(Em_Han *);
bool login();
char uname[80];
bool findname = false;

int main()
{
	bool exitflag = false;
	char filename[80];
	if (login())
	{
		Em_Han *emhan = new Em_Han();
		strcpy(filename, uname);
		strcat(filename, ".txt");
		if (findname)
			emhan->InputData(uname);
		else
		{
			ofstream fo(filename);
			fo.close();
		}
		while (!exitflag)
			exitflag = menu(emhan);
		emhan->UpdateData(uname);
		delete emhan;
	}
	else
	return 0;
}
bool menu(Em_Han *em)
{
	char choice;
	cout << "Hi " << uname << "! You can store up to " << 100 - (em->getnoem()) << " emails!" << endl;
	cout << "1. Add Content\n";
	cout << "2. Delete content\n";
	cout << "3. Sort content for received emails and display them\n";
	cout << "4. Display content\n";
	cout << "5. Exit program\n";
	cout << "Enter your choice (1-5): ";
	cin >> choice;
	switch (choice)
	{
	case '1': em->AddContent(); return false; break;
	case '2': em->DeleteContent(); return false; break;
	case '3': em->SortContent(); return false; break;
	case '4': em->DisplayContent(); return false; break;
	case '5': cout << "Good-bye user!\n"; return true; break;
	default: cout << "Invalid input! Please input again!\n"; return false;
	}
}
bool login()
{
	int maxAtmp = 3, noline = 1;
	char pword[80], dname[80], dpword[80], a, trash[80];
	bool checkpword = false;
	cout << "Username: ";
	cin >> uname;
	ifstream fin("Username_Password.txt");
	while (fin.get(a)) //to get the number of lines in file for for-loop purpose
	{
		if (a == '\n')
			noline++;
	}
	fin.close();
	ifstream c("Username_Password.txt");
	for (int i = 1; i < noline+1; i++) //check if the username entered by the user is found in the file
	{
		if ((i % 3 == 1))
		{
			c.getline(dname, 79);
			if (strcmp(uname, dname) == 0)
				findname = true;
		}
		else
			c.getline(trash,79);
	}
	c.close();
	if (findname)
	{
		while (maxAtmp > 0)   //run while-loop at most 3 times since initially maxAtmp=3
		{
			bool checkname = false;
			cout << "Password: ";
			cin >> pword;
			ifstream check("Username_Password.txt");
			for (int i = 1; i < (noline + 1) && (checkname==false); i++) //check if the password entered by the user is found in the file
			{
				if ((i % 3 == 1))
				{
					check.getline(dname, 79);
					if (strcmp(uname, dname) == 0)
						checkname = true;
				}
				else
					check.getline(trash, 79);
			}
			check.getline(dpword, 79);
			if (strcmp(pword, dpword) == 0)
				checkpword = true;
			check.close();
			if (checkpword == true)
			{
				return true;
			}
			else
			{
				cout << "Wrong password! Please input again!\n";
				maxAtmp--;
				if (maxAtmp == 0)
				{
					cout << "Good-bye user!\n";
					return false;
				}
			}
		}
	}
	else
	{
		ofstream insert("Username_Password.txt", ios::app);
		insert << endl << uname << endl;
		cout << "Welcome new user! Please enter your password: ";
		cin >> pword;
		insert << pword<<endl;
		insert.close();
		return true;
	}
}