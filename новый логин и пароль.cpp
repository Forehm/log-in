#include <iostream>
#include <string>
#include <list>

using namespace std;
class Profil;
list<Profil> ProfilesList;

class LogInException : public exception
{
public:

	LogInException(string problem)
	{
		this->problem = problem;
	}

	string GetProbem() { return problem; }


private:
	string problem;
};

class Profil
{
public:
	
	enum SubscribersStatus { IsSubscribed, IsNotSubscribed };

	Profil(string login, string password, string data, SubscribersStatus status);
	
	void static LogIn();

	

	void GetInfo()
	{
		cout << data << endl; ///// временная функция, которую мне стало лень удалять
	}

	

private:

	int GetId();
	


	string login;
	string password;
	string data;
	int id;
	int static Count;
	SubscribersStatus status;
};


int Profil::Count = 0;


Profil::Profil(string login, string password, string data, SubscribersStatus status)
{
		this->login = login;
		this->password = password;
		this->data = data;
		this->status = status;
		this->id = GetId();
		ProfilesList.push_back(*this);
}

void Profil::LogIn()
{
	string log, pass;
	cout << "Введите логин" << endl;
	cin >> log;
	cout << "Введите пароль" << endl;
	cin >> pass;
	int counter = 0;


	for (auto it = ProfilesList.begin(); it != ProfilesList.end(); it++)
	{
		if (log != (*it).login && pass != (*it).password )
		{
			counter++;
			if (counter == ProfilesList.size())
			{
				throw LogInException("Упс... Пользователя с таким логином и паролем не существует");
			}
			
		}
		else
		{
			(*it).GetInfo();
		}
		
	}
}



int Profil::GetId()
{
	Count++;
	return Count;
}


int main()
{
	setlocale(LC_ALL, "ru");
	
	Profil Mark("Mark", "mark3321", "Любит чиспы", Profil::SubscribersStatus::IsSubscribed);
	Profil Kirill("Kirill", "Kira1937", "Увлекается историей Англии", Profil::SubscribersStatus::IsNotSubscribed);
	Profil Egor("EGor", "135241", "Я Егор", Profil::SubscribersStatus::IsSubscribed);
	try
	{
		Profil::LogIn();
	}
	catch (LogInException& error)
	{
		cout << error.GetProbem();
	}




	return 0; 
}

