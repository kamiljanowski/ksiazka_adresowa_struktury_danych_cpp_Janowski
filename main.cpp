#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

struct InformationAboutSingleContact
{
    string firstName, lastName, phoneNumber, email, address;
    int userId, id;
};

struct InformationAboutUsers
{
    string userName, password;
    int id;
};

vector<InformationAboutSingleContact> loadContactList(int totalAmountOfContacts, InformationAboutSingleContact acquaintance, int idLoggedUser)
{
    string line;
    fstream file;
    vector<InformationAboutSingleContact> acquaintances;
    char searchedSign='|';

    file.open("ksiazka.txt", ios::in);

    if(file.good() == true)
    {
        while (!file.eof())
        {
            for (int i=0; i<totalAmountOfContacts; i++)
            {
                getline(file,line);

                size_t position1 = line.find(searchedSign);
                acquaintance.id = atoi((line.substr(0,position1)).c_str());

                size_t position2 = line.find(searchedSign, position1 + 1 );
                acquaintance.userId = atoi((line.substr(position1+1,(position2-position1-1))).c_str());

                size_t position3 = line.find( searchedSign, position2 + 1 );
                acquaintance.firstName = line.substr(position2+1,(position3-position2-1));

                size_t position4 = line.find( searchedSign, position3 + 1 );
                acquaintance.lastName = line.substr(position3+1,(position4-position3-1));

                size_t position5 = line.find( searchedSign, position4 + 1 );
                acquaintance.phoneNumber = line.substr(position4+1,(position5-position4-1));

                size_t position6 = line.find( searchedSign, position5 + 1 );
                acquaintance.email = line.substr(position5+1,(position6-position5-1));

                size_t position7 = line.find( searchedSign, position6 + 1 );
                acquaintance.address = line.substr(position6+1,(position7-position6-1));

                if (acquaintance.userId == idLoggedUser)
                {
                    acquaintances.push_back(acquaintance);
                }
            }
        }
    }
    file.close();

    return acquaintances;
}

vector<InformationAboutUsers> loadUsersList(int totalAmountOfUsers, InformationAboutUsers user)
{
    string line;
    fstream file;
    vector<InformationAboutUsers> users;
    char searchedSign='|';

    file.open("uzytkownicy.txt", ios::in);

    if(file.good()==true)
    {
        while (!file.eof())
        {
            for (int i=0; i<totalAmountOfUsers; i++)
            {
                getline(file,line);

                size_t position1 = line.find(searchedSign);
                user.id = atoi((line.substr(0,position1)).c_str());

                size_t position2 = line.find( searchedSign, position1 + 1 );
                user.userName = line.substr(position1+1,(position2-position1-1));

                size_t position3 = line.find( searchedSign, position2 + 1 );
                user.password = line.substr(position2+1,(position3-position2-1));

                users.push_back(user);
            }
        }
    }
    file.close();

    return users;
}

int checkTotalAmountOfContacts ()
{
    int totalAmountOfContacts;
    int LineNumber=0;

    fstream file;
    file.open("ksiazka.txt", ios::in);

    if(file.good()==false)
        totalAmountOfContacts=0;

    else
    {
        string line;
        while (getline(file, line))
        {
            LineNumber++;
        }
        totalAmountOfContacts=LineNumber;
    }

    file.close();
    return totalAmountOfContacts;
}

int checkTotalAmountOfUsers ()
{
    int totalAmountOfUsers;
    int LineNumber=0;

    fstream file;
    file.open("uzytkownicy.txt", ios::in);

    if(file.good()==false)
        totalAmountOfUsers=0;

    else
    {
        string line;
        while (getline(file, line))
        {
            LineNumber++;
        }
        totalAmountOfUsers = LineNumber;
    }

    file.close();
    return totalAmountOfUsers;
}

int checkLastId (int totalAmountOfContacts)
{
    fstream file;
    string line;
    int lastId = 0;

    file.open("ksiazka.txt", ios::in);
    for (int i = 0; i < totalAmountOfContacts; i++)
    {
        getline(file,line);

        char searchedSign='|';
        size_t position1 = line.find(searchedSign);
        lastId = atoi((line.substr(0,position1)).c_str());
    }
    file.close();

    return lastId;
}

void saveNewContact(InformationAboutSingleContact acquaintance, vector<InformationAboutSingleContact>acquaintances, int totalAmountOfContacts, int idLoggedUser)
{
    string firstName, lastName, phoneNumber, email, address;
    int id;

    cout<<"Podaj imie: ";
    cin >> firstName;
    cout<<"Podaj nazwisko: ";
    cin >> lastName;
    cout<<"Podaj numer telefonu: ";
    cin >> phoneNumber;
    cout<<"Podaj e-mail: ";
    cin >> email;
    cout<<"Podaj adres: ";
    cin.sync();
    getline(cin, address);

    fstream file;
    file.open("ksiazka.txt", ios::in);

    if(file.good()==false)
        id = 1;

    else
        id = checkLastId(totalAmountOfContacts) + 1;

    file.close();

    file.open("ksiazka.txt", ios::out | ios::app);
    file << id << '|' << idLoggedUser << '|' << firstName << '|' << lastName << '|' << phoneNumber << '|' << email << '|' << address << '|' << endl;
    file.close();

    cout << "Kontakt dodano do ksiazki adresowej: " << firstName << " " << lastName << endl;
    Sleep(2000);
}

void searchByFirstName(vector<InformationAboutSingleContact>acquaintances)
{
    string firstName;
    string correctData = "";

    cout << "Podaj imie szukanego kontaktu ";
    cin >> firstName;

    for(int i=0; i < acquaintances.size(); i++)
    {
        if(acquaintances[i].firstName==firstName)
        {
            correctData = "OK";
            cout<<endl;
            cout<<"Imie i nazwisko: "<< acquaintances[i].firstName << " "<< acquaintances[i].lastName << endl;
            cout<<"Numer telefonu: " << acquaintances[i].phoneNumber << endl;
            cout<<"E-mail: " << acquaintances[i].email << endl;
            cout<<"Adres: " << acquaintances[i].address << endl ;
        }
    }
    cout<<endl;

    if(correctData == "OK")
    {
        cout << "Wyswietlono wszystkie kontakty o takim imieniu." << endl;
    }
    else
    {
        cout << "Brak kontaktow o wskazanym imieniu." << endl;
    }

    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void searchByLastName(vector<InformationAboutSingleContact>acquaintances)
{
    string lastName;
    string correctData = "";

    cout << "Podaj nazwisko szukanego kontaktu ";
    cin >> lastName;
    for(int i=0; i < acquaintances.size(); i++)
    {
        if(acquaintances[i].lastName == lastName)
        {
            correctData = "OK";
            cout<<endl;
            cout<<"Imie i nazwisko: "<< acquaintances[i].firstName << " "<< acquaintances[i].lastName << endl;
            cout<<"Numer telefonu: " << acquaintances[i].phoneNumber << endl;
            cout<<"E-mail: " << acquaintances[i].email << endl;
            cout<<"Adres: " << acquaintances[i].address << endl ;
        }
    }
    cout<<endl;

    if(correctData == "OK")
    {
        cout << "Wyswietlono wszystkie kontakty o takim nazwisku." << endl;
    }
    else
    {
        cout << "Brak kontaktow o wskazanym nazwisku." << endl;
    }

    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void displayAllContacts(vector<InformationAboutSingleContact> acquaintances)
{
    fstream file;
    file.open("ksiazka.txt", ios::in);

    if(file.good()==false)
    {
        cout<<"Twoja ksiazka adresowa jest pusta." << endl;
    }

    else
    {
        for(int i=0; i < acquaintances.size(); i++)
        {
            cout<<endl;
            cout << acquaintances[i].id << ". " << acquaintances[i].firstName <<" "<< acquaintances[i].lastName << endl;
            cout<<"Nr tel.: " << acquaintances[i].phoneNumber <<", e-mail: " << acquaintances[i].email << endl;
            cout <<"Adres: " << acquaintances[i].address << endl ;
        }
    }
    file.close();

    cout<<endl;
    cout<<"Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();

}

void deleteContact (int totalAmountOfContacts, vector<InformationAboutSingleContact> acquaintances)
{
    int id;
    char userChoiceSideMenu;
    cout << "Podaj numer ID kontaktu ktory zamierzasz usunac ";
    cin >> id;
    cout << "Usunac kontakt o numerze ID " << id << "? (potwierdz klawiszem t/n) ";
    cin >> userChoiceSideMenu;
    cout << endl;
    bool condition = false;

    if (userChoiceSideMenu == 't')
    {
        for(int i=0; i<acquaintances.size(); i++)
        {
            if (acquaintances[i].id == id)
                condition = true;
        }

        if (condition == false)
        {
            cout << "Kontakt o wskazanym numerze ID nie istnieje." << endl;
        }

        else
        {
            fstream file, file2;
            string line;

            file.open("ksiazka.txt", ios::in);
            file2.open("ksiazka_tymczasowa.txt", ios::out);

            for (int i=0; i < totalAmountOfContacts; i++)
            {
                getline(file,line);

                char searchedSign='|';
                size_t position1 = line.find(searchedSign);
                int checkedId = atoi((line.substr(0,position1)).c_str());

                if (checkedId != id)
                {
                    file2 << line << endl;
                }
            }

            file.close();
            file2.close();

            remove("ksiazka.txt");
            rename( "ksiazka_tymczasowa.txt", "ksiazka.txt" );

            cout << "Adresat zostal usuniety. ";
        }

        cout << endl;
        cout << "Wcisnij enter aby wrocic do menu glownego.";
        getchar();
        getchar();
    }
}

void editContact (int totalAmountOfContacts, vector<InformationAboutSingleContact> acquaintances)
{
    int id;
    char userChoiceSideMenu;
    string changedData;
    string correctID="";

    cout << "Podaj numer ID kontaktu ktory chcesz edytowac ";
    cin >> id;

    for(int i = 0; i < acquaintances.size(); i++)
    {
        if(acquaintances[i].id == id)
        {
            correctID = "ID poprawne";
        }
    }

    if (correctID == "ID poprawne")
    {
        cout << "Ktore dane chcesz edytowac? " << endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. E-mail" << endl;
        cout << "5. Adres" << endl;
        cout << "6. Powrot do menu glownego" << endl;
        cout << "Twoj wybor: ";
        cin >> userChoiceSideMenu;
        cout << endl;

        if (userChoiceSideMenu == '1')
        {
            for(int i = 0; i < acquaintances.size(); i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualne imie: " << acquaintances[i].firstName <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].firstName = changedData;
                    cout << endl << "Imie zostalo zmienione."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '2')
        {
            for(int i = 0; i < acquaintances.size(); i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualne nazwisko: " << acquaintances[i].lastName <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].lastName = changedData;
                    cout << endl << "Nazwisko zostalo zmienione."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '3')
        {
            for(int i = 0; i < acquaintances.size(); i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualny nr. telefonu : " << acquaintances[i].phoneNumber <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].phoneNumber = changedData;
                    cout << endl << "Nr. telefonu zostal zmieniony."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '4')
        {
            for(int i = 0; i < acquaintances.size(); i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualny email: " << acquaintances[i].email <<endl;
                    cout << "Zmiana na : " ;
                    cin >> changedData;
                    acquaintances[i].email = changedData;
                    cout << endl << "Email zostal zmieniony."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu == '5')
        {
            for(int i = 0; i < acquaintances.size(); i++)
            {
                if(acquaintances[i].id == id)
                {
                    cout << "Aktualny adres: " << acquaintances[i].address <<endl;
                    cout << "Zmiana na : " ;
                    cin.sync();
                    getline(cin, changedData);
                    acquaintances[i].address = changedData;
                    cout << endl << "Adres zostal zmieniony."<< endl;
                }
            }
        }

        else if (userChoiceSideMenu=='6')
        {
            exit(0);
        }

        fstream file, file2;
        string line;

        file.open("ksiazka.txt", ios::in);
        file2.open("ksiazka_tymczasowa.txt", ios::out);

        for (int i=0; i < totalAmountOfContacts; i++)
        {
            getline(file,line);

            char searchedSign='|';
            size_t position1 = line.find(searchedSign);
            int checkedId = atoi((line.substr(0,position1)).c_str());

            if (checkedId == id)
            {
                for(int changedPosition = 0; changedPosition < acquaintances.size(); changedPosition++)
                {
                    if(acquaintances[changedPosition].id == id)
                    {
                        file2 << acquaintances[changedPosition].id << '|' << acquaintances[changedPosition].userId << '|' << acquaintances[changedPosition].firstName << '|' << acquaintances[changedPosition].lastName << '|' << acquaintances[changedPosition].phoneNumber << '|' << acquaintances[changedPosition].email << '|' << acquaintances[changedPosition].address << '|' << endl;
                    }
                }
            }
            else
            {
                file2 << line << endl;
            }
        }

        file.close();
        file2.close();

        remove("ksiazka.txt");
        rename( "ksiazka_tymczasowa.txt", "ksiazka.txt" );
    }

    else
    {
        cout << "Kontakt o wskazanym numerze ID nie istnieje." << endl;
    }

    cout << endl;
    cout << "Wcisnij enter aby wrocic do menu glownego.";
    getchar();
    getchar();
}

void registartion (int totalAmountOfUsers, vector<InformationAboutUsers> users)
{
    int id;
    string userName, password;
    cout << "Podaje nazwe uzytkownika: ";
    cin >> userName;

    int i = 0;
    while (i < totalAmountOfUsers)
    {
        if (users[i].userName == userName)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> userName;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;

    fstream file;
    file.open("uzytkownicy.txt", ios::in);

    if(file.good()==false)
        id = 1;
    else
        id = users[totalAmountOfUsers-1].id + 1;

    file.close();

    file.open("uzytkownicy.txt", ios::out | ios::app);
    file << id << '|' << userName << '|' << password << '|' << endl;
    file.close();

    cout << "Konto zalozone";
    Sleep(1000);
}

int loggingIn (int totalAmountOfUsers, vector<InformationAboutUsers> users)
{
    string userName, password;
    cout << "Podaj nazwa uzytkownika: ";
    cin >> userName;

    int i = 0;
    while (i < totalAmountOfUsers)
    {
        if (users[i].userName == userName)
        {
            for (int attempt=0; attempt < 3; attempt++)
            {
                cout << "Podaj haslo. Pozostalo prob "  << 3-attempt << ": ";
                cin >> password;
                if (users[i].password == password)
                {
                    cout << "Zalogowasles sie." << endl;
                    Sleep (1000);
                    return users[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Odczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Podany uzytkownik nie istnieje";
    Sleep (1500);
    return 0;
}

void changePassword (int totalAmountOfUsers, vector<InformationAboutUsers> users, int idLoggedUser)
{
    fstream file;
    string password;
    cout << "Podaj nowe haslo: ";
    cin >> password;

    for (int i=0; i < totalAmountOfUsers; i++)
    {
        if (users[i].id == idLoggedUser)
        {
            users[i].password = password;
            cout << "Haslo zostalo zmienione"<<endl;
            Sleep (2000);
        }
    }

    file.open("uzytkownicy.txt", ios::out);
    for(int i = 0; i < totalAmountOfUsers; i++)
    {
        file << users[i].id << '|' << users[i].userName << '|' << users[i].password << '|' << endl;
    }
    file.close();
}

int main()
{
    InformationAboutSingleContact acquaintance;
    InformationAboutUsers user;

    int totalAmountOfContacts = checkTotalAmountOfContacts();
    int totalAmountOfUsers = checkTotalAmountOfUsers();

    vector<InformationAboutSingleContact> acquaintances;
    vector<InformationAboutUsers> users = loadUsersList(totalAmountOfUsers, user);

    char userChoiceLogInMenu;
    char userChoiceMainMenu;

    int idLoggedUser = 0;

    while(1)
    {
        if (idLoggedUser == 0)
        {
            system("cls");
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
            cin >> userChoiceLogInMenu;
            cout << endl;

            if (userChoiceLogInMenu=='1')
            {
                idLoggedUser = loggingIn (totalAmountOfUsers, users);
            }

            else if (userChoiceLogInMenu=='2')
            {
                registartion (totalAmountOfUsers, users);
                totalAmountOfUsers = checkTotalAmountOfUsers();
                users = loadUsersList(totalAmountOfUsers, user);
            }

            else if (userChoiceLogInMenu=='9')
            {
                exit(0);
            }
        }

        else
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresta" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
            cin >> userChoiceMainMenu;
            cout << endl;

            totalAmountOfContacts = checkTotalAmountOfContacts();
            acquaintances = loadContactList(totalAmountOfContacts, acquaintance, idLoggedUser);

            if (userChoiceMainMenu=='1')
            {
                saveNewContact(acquaintance, acquaintances, totalAmountOfContacts, idLoggedUser);
            }

            else if (userChoiceMainMenu=='2')
            {
                searchByFirstName(acquaintances);
            }

            else if (userChoiceMainMenu=='3')
            {
                searchByLastName(acquaintances);
            }

            else if (userChoiceMainMenu=='4')
            {
                displayAllContacts(acquaintances);
            }

            else if (userChoiceMainMenu=='5')
            {
                deleteContact(totalAmountOfContacts, acquaintances);
                totalAmountOfContacts = checkTotalAmountOfContacts();
            }

            else if (userChoiceMainMenu=='6')
            {
                editContact(totalAmountOfContacts, acquaintances);
            }

            else if (userChoiceMainMenu=='7')
            {
                changePassword(totalAmountOfUsers, users, idLoggedUser);
                users = loadUsersList(totalAmountOfUsers, user);
            }

            else if (userChoiceMainMenu=='8')
            {
                idLoggedUser = 0;
            }

            else if (userChoiceMainMenu=='9')
            {
                exit(0);
            }
        }
    }
    return 0;
}
