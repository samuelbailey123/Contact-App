/**
 * @author Samuel Bailey 
 * Contact list
 * The goal of the program is to write and read a phone contact list. 
    */

#include <iostream>
#include <vector>
#include <fstream> 
#include <iterator> 
#include <string>
#include <cctype>
#include<ctype.h>

using namespace std;

struct person{
    string name; 
    int age; 
    long number;
};

vector<person> contactStorage;

//declaration of functons
void printStruct(person person);
void inputData();
void displayMenu();
void displayData(vector<person> contactStorage);
void downloadData();
void saveData(); 
void checkData();
int getCountForFile();

int main(){

    downloadData();
    displayMenu();

}

void displayMenu(){
    int selection =0; 
    do {
    cout << "Enter a selection" << endl; 
    cout << "1: Input Data" << endl; 
    cout << "2: View Data" << endl; 
    cout << "3: Exit" << endl; 
    cin >> selection; 
    if(cin.fail()){
        cin.clear(); cin.ignore(512, '\n');
        cout << "Not a number" << endl;
    }else if(selection > 3 || selection < 1){
        cout << "Not a valid selection, try again" << endl;
    }else{
        if (selection == 1 || selection == 2 || selection == 3){
        switch (selection){
            case 1: 
                inputData();
                break;
            case 2: 
                displayData(contactStorage);
                break;
            case 3: 
                saveData();
                break;
            default: 
                cout << "Incorrect number, try again" << endl; 
            }
    }
    }
    }while(selection != 3);
}
void displayData(vector<person> contactStorage){
    if (contactStorage.empty() == true){
        cout << "There is not any data yet." << endl; 
        cout << "Would you like to input data?" << endl; 
        string answer; 
        cin >> answer;
        if (answer == "yes" || answer == "y" || answer == "Yes" || answer == "YES"){
            // inputData();
            // return displayMenu();
            cout << "Great, returning to main menu. Please enter option 1 " << endl;
        }
    }if(contactStorage.empty() != true){
        for (int i =0; i<contactStorage.size(); i++){
            cout << "Contact List:" << i << ": " << contactStorage.at(i).name << ", " << contactStorage.at(i).age << ", " << contactStorage.at(i).number << endl;
    }
}
}
void inputData(){
    string input = "yes"; 
    while (input=="yes" || input == "y"){
        person fill; 
        do{
            cout << "Enter the name" << endl; 
            cin >> fill.name;
            fill.name[0] = toupper(fill.name[0]);
            if (isalpha(fill.name.at(0)) == false){
                cout << "Invalid name, try again" << endl; 
            }
        }while(isalpha(fill.name.at(0)) == false);

        do{
            cout << "Enter the age" << endl;
            cin >> fill.age;
            if (cin.fail()){
                cin.clear(); cin.ignore(512, '\n');
                cout << "Not a number" << endl;
                fill.age = 200; 
            }
            else if (fill.age > 115 || fill.age < 0){
                cout << "Incorrect age, try again" << endl;
            }
        }while(fill.age > 110 || fill.age < 0);
        
        do{
        cout << "Enter the 10 digit phone number" << endl; 
        cin >> fill.number;
        if (cin.fail()){
            cin.clear(); cin.ignore(512, '\n');
            cout << "Not a number" << endl;
        }else if (fill.number > 9999999999 && fill.number < 0000000000){
            cout << "Not a valid phone #" << endl; 
            }
        }while(fill.number > 9999999999 && fill.number < 0000000000);
           
        contactStorage.push_back(fill);

        cout << "Would you like to input more?(yes or no)" << endl; 
        cin >> input;
        if (input == "no" || input == "No" || input == "n"){
            break;
        }
    }
}
void printStruct(person person){
    cout << person.name << endl; 
    cout << person.age << endl; 
    cout << person.number << endl; 
}
void downloadData(){
    ifstream input_file("./contacts.xls");
    if (input_file.is_open()){
    for (int i =0; i<getCountForFile(); i++){
        person fill; 
        input_file >> fill.name; 
        input_file >> fill.age; 
        input_file >> fill.number; 
        contactStorage.push_back(fill);
    }
    input_file.close();
  }
}   
void saveData(){
    ofstream output_file("./contacts.xls");
    if (output_file.is_open()){
        for (int i=0; i<contactStorage.size(); i++){
            output_file << contactStorage.at(i).name << " " <<  contactStorage.at(i).age << " " << contactStorage.at(i).number << endl;
        }
    }
    output_file.close();
}
void checkData(){
      ifstream file ("./contacts");
    if (file.peek() == std::ifstream::traits_type::eof()){
   // Empty File
   cout << "There is nothing in the file" << endl; 
}else{
    downloadData();
}
}
int getCountForFile(){
    ifstream input_file("./contacts.xls");
    int count = 0;
    string line;
    while (getline(input_file, line))
        count++;
    input_file.close();
    return count; 
}