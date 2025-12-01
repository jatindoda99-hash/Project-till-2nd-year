#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream.h>
#define key 3
#define MAX 100

class Student
{
public:
    int Subject[5];
    int rollNo, total;
    char name[25];

    Student() { total = 0; }

    Student(int rollNo, char *name)
     {
	this->rollNo = rollNo;
	strcpy(this->name, name);
	encrypt(this->name);
	total = 0;
    }

    void toggleCase(char *str)
    {
	    for (int i = 0; i < strlen(str); i++)
	{
	    if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
	    else if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
	}
    }
    void encrypt(char *org)
     {
	toggleCase(org);
	for (int i = 0; i < strlen(org); i++)
     {
	if (org[i] >= 'A' && org[i] <= 'Z')
{
    org[i] = org[i] + key;
    if (org[i] > 'Z')
        org[i] = org[i] - 26;   
}
else if (org[i] >= 'a' && org[i] <= 'z')
{
    org[i] = org[i] + key;
    if (org[i] > 'z')
        org[i] = org[i] - 26;   
}

    }
}

void decrypt(char *str)
{
    for (int i = 0; i < strlen(str); i++)
     {
	if (str[i] >= 'A' && str[i] <= 'Z')
    {
    str[i] = str[i] - key;
    if (str[i] < 'A')
        str[i] = str[i] + 26;
    }
else if (str[i] >= 'a' && str[i] <= 'z')
    {
    str[i] = str[i] - key;
    if (str[i] < 'a')
        str[i] = str[i] + 26;
    }

    }
    toggleCase(str);
}


    void getMarks()
    {
	total = 0;
	for (int i = 0; i < 5; i++)
	{
	    cout << "Enter Marks For Subject " << i + 1 << ": ";
	    cin >> Subject[i];
	    total += Subject[i];
	}
    }
    static int isDuplicateRoll(int rollNo) 
    {
    fstream fin("pos", ios::in);
    if (!fin) return 0;
    Student temp;
    while (temp.readFromFile(fin)) 
    {
        if (temp.getRollNo() == rollNo) 
            return 1;
    }
    return 0;
    }


    void display()
    {
	char tempName[25];
	strcpy(tempName, name);
	decrypt(tempName);
	cout << "\n-----------------------------";
	cout << "\nRoll No: " << rollNo;
	cout << "\nName: " << tempName;
	cout << "\nMarks: ";
	    for (int i = 0; i < 5; i++) cout << Subject[i] << " ";
	cout << "\nTotal: " << total;
	cout << "\n-----------------------------\n";
    }

    int searchByName(char searchName[])
     {
        char temp[25];
        strcpy(temp, this->name);
        decrypt(temp);
        return !strcmpi(temp, searchName);
    }

    int getRollNo() 
    { return this->rollNo; }

    void writeToFile(fstream &fout)
     {
    fout << rollNo << "\n";            
    fout << name << "\n";              
    for (int i = 0; i < 5; i++) 
        fout << Subject[i] << " ";    
    fout << "\n" << total << "\n";    
}
int readFromFile(fstream &fin)
 {
    if (!(fin >> rollNo))  
        return 0;
    
    fin.get();                 
    fin.getline(name, 25);     

    for (int i = 0; i < 5; i++)
        fin >> Subject[i];

    fin >> total;
    fin.get();                
    return 1;
}


};

void main() {
    clrscr();
    Student* ps[MAX];
    int count = 0;
    int choice, rollNo;
    char name[25];

    while (1) {
        cout << "\n\nStudent Management System:";
        cout << "\n1. Admission";
        cout << "\n2. Display All Students";
        cout << "\n3. Search By Roll No";
        cout << "\n4. Search By Name";
        cout << "\n5. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
             if (count < MAX) 
                {
                    cout << "Enter Roll No: ";
                    cin >> rollNo;

                    
         if (Student::isDuplicateRoll(rollNo))
          {
            cout << "Roll No already exists! Admission denied.\n";
            break;
            }
                    
                  cout << "Enter Name: ";
                    gets(name);


                    ps[count] = new Student(rollNo, name);
                    ps[count]->getMarks();

                    fstream fout("pos", ios::out | ios::app);
                    ps[count]->writeToFile(fout);
                    fout.close();
                    count++;
                } 
                else
                    cout << "Cannot Admit More Students!..";
                break;

         case 2:
     {
	 fstream fin("pos", ios::in);
	if (!fin)
	{
		 cout << "Nothing In File!\n";
		 break;
	}

    count = 0;
    while (count < MAX)
    {
	ps[count] = new Student();
	if (!ps[count]->readFromFile(fin))
	{
	    delete ps[count];
	    break;
	}
	ps[count]->display();
	count++;
    }
    fin.close();
    break;
}

case 3:
	{
	cout << "Enter Roll No To Search: ";
	cin >> rollNo;

	fstream fin1("pos", ios::in);
	if (!fin1)
	 {
		cout << "File Is Empty!..\n";
		break;
	}

    Student tempRoll;
    int foundRollNo = 0;

    while (tempRoll.readFromFile(fin1))
    {
	if (tempRoll.getRollNo() == rollNo)
	{
	    tempRoll.display();
	    foundRollNo = 1;
	    break;
	}
    }

    fin1.close();

    if (!foundRollNo)
	cout << "Roll No not found in student list!\n";

    break;
}
case 4:
{
    char nameToSearch[50];
    cout << "Enter Name To Search: ";
    gets(nameToSearch);

    fstream fin("pos", ios::in);
    if (!fin)
    {
	cout << "File is empty!\n";
	break;
    }

    Student temp;
    int found = 0;

    while (temp.readFromFile(fin))
    {
	if (temp.searchByName(nameToSearch))
	{
	    temp.display();
	    found = 1;
	}
    }

    fin.close();
    if (!found)
	cout << "Name not found!\n";
    break;
}

	    case 5:
		exit(EXIT_SUCCESS);
	}
    }
}