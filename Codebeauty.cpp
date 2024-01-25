// Codebeauty.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include<string>
using namespace std;

class AbstractEmployee {
	virtual void AskForPromotion() = 0;
};

class Employee :AbstractEmployee{
	string Company;
	int Age;

protected:
	string Name;

public:
	void setName(string name)
	{
		Name = name;
	}

	string getName()
	{
		return Name;
	}

	void setCompany(string Company)
	{
		this->Company = Company;
	}

	string getCompany()
	{
		return this->Company;
	}


	void setAge(int Age) {
		if (Age >= 18)
		{
			this->Age = Age;
		}
	}
	int getAge()
	{
		return Age;
	}
	Employee(string name, string company, int age)
	{
		Name = name;
		Company = company;
		Age = age;

	}

	void AskForPromotion() {
		if (Age > 30) {
			cout << Name << ", got promoted! " << endl;
		}
		else
		{
			cout << Name<<", Sorry, too young for promotion" << endl;
		}
	}

	virtual void Work()
	{
		cout << Name << " is checking email " << endl;
	}


};

class Developer:public Employee
{
public:
	string favProgrammingLanguage;

	Developer(string name, string company, int age,string favProgrammingLanguage)
		:Employee(name,company,age)
	{
		this->favProgrammingLanguage = favProgrammingLanguage;
	}

	void FixBug()
	{
		cout << Name << " fixed bug using: " << favProgrammingLanguage<<endl;
	}
	void Work()
	{
		cout << Name << " is writing code in "<<favProgrammingLanguage << endl;

	}
};

class Teacher :public Employee{
public:
	string Subject;
	void PrepareLesson()
	{
		cout << Name << " is preparing " << Subject << " lesson" << endl;
	}

	Teacher(string name, string company, int age, string subject)
		:Employee(name, company, age) {
		Subject = subject;
	}

	void Work()
	{
		cout << Name << " is teaching " << Subject << endl;

	}
};

int main()
{
   
	Employee employee1=Employee("Alexia","YT",21);

	Employee employee2 = Employee("John", "Amazon", 35);


	cout << employee1.getAge()<<endl;
	employee1.setAge(22);
	cout << employee1.getAge()<<endl;

	employee1.AskForPromotion();
	employee2.AskForPromotion();

	Developer d("Ana","YT",24,"C++");
	d.FixBug();
	d.AskForPromotion();


	Teacher t("Jack","Coool School",35,"History");
	t.PrepareLesson();
	t.AskForPromotion();

	d.Work();
	t.Work();

	Employee* e1 = &d;
	Employee* e2 = &t;



	e1->Work();
	e2->Work();

}

