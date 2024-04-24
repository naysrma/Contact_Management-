#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
using namespace std;

class temp{
    string phoneNo,name,address,description,search,find;
    bool  contactExists;
    //creating an object to access the file
    fstream file;
    public:
    void addContact();
    void showAll();
    void searchContact();
    void update();
    void deleteContact();
}obj;

int main(){
   int choice;
do {
   cout<<"1. --> Add contact details: "<<endl;
   cout<<"2. --> view all contact: "<<endl;
   cout<<"3. --> Search contact: "<<endl;
   cout<<"4. --> Update contact: "<<endl;
   cout<<"5. --> Delete contact: "<<endl;
   cout<<"6. --> exit";
   cin>>choice;
   switch(choice){
    case 1: 
    obj.addContact();
    break;

    case 2: 
    obj.showAll();
    break;

    case 3: 
    obj.searchContact();
    break;

    case 4: 
        obj.update();
    break;

    case 5: 
        obj.deleteContact();
    break;

    case 6: 
        cout<<"Exiting......................................";
        break;
    break;

    default: 
        cout<<"Press valid key";
    break;
   }
}while(choice != 6);
return 0;
}

void temp :: addContact(){
    //*using Getline function instead of cin because we need to take input with spaces in between*
    cin.ignore();
    cout << "Enter Phone Number: ";
    getline(cin, phoneNo);
    cout << "Enter Name: ";
    getline(cin, name);

    // Check if the contact already exists by searching for the name or phone number
    file.open("data.csv", ios::in);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, phoneNo, ',');
        getline(ss, name, ',');
        // Check if the current contact matches the input phone number or name
        if (name == this->name || phoneNo == this->phoneNo) {
            contactExists = true;
            break; // Exit the loop if a duplicate is found
        }
    }
    file.close();
     if (contactExists) {
        cout << "Contact already exists." << endl;
        return;
    }

    // If no duplicate contact is found, proceed to enter the remaining details
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Description: ";
    getline(cin, description);

    // Open the file in append mode to add the new contact
    file.open("data.csv", ios::out | ios::app);
    file << phoneNo << "," << name << "," << address << "," << description << "\n";
    file.close();

    cout << "Contact added successfully." << endl;
}


void  temp :: showAll(){
    file.open("data.csv", ios :: in);
    getline(file,phoneNo,',');
    getline(file,name,',');
    getline(file,address,',');
    getline(file,description,',');

    //loop to fetch data till end
    while(!file.eof()){
        cout<<"Phone Number :: "<<phoneNo<<endl;
        cout<<"Name :: "<<name<<endl;
        cout<<"Address:: "<<address<<endl;
        cout<<"Description:: "<<description<<endl;
        getline(file,phoneNo,',');
        getline(file,name,',');
        getline(file,address,',');
        getline(file,description,',');
    }
    file.close();
}

void temp :: searchContact(){
    cout<<"Enter phone number ::";
    getline(cin,search);
    file.open("data.csv", ios :: in);
    getline(file,phoneNo,',');
    getline(file,name,',');
    getline(file,address,',');
    getline(file,description,',');

    //loop to fetch data till end
    while(!file.eof()){
        if(phoneNo == search){
        cout<<"Phone Number :: "<<phoneNo<<endl;
        cout<<"Name :: "<<name<<endl;
        cout<<"Address:: "<<address<<endl;
        cout<<"Description:: "<<description<<endl;
        }
        getline(file,phoneNo,',');
        getline(file,name,',');
        getline(file,address,',');
        getline(file,description,',');
    }
    file.close();
}

 void temp :: update() {
    string find;
    cout << "Enter the name of the contact you want to update: ";
    cin.ignore(); // Ignore any leftover newline characters in the input buffer
    getline(cin, find);

    fstream file("data.csv", ios::in); // Open file for reading
    ofstream tempFile("temp.csv", ios::out); // Create a temporary file for writing updated data

    string line;
    bool found = false;

    // Iterate through each line in the file
    while (getline(file, line)) {
        stringstream ss(line);
        string phoneNo, name, address, description;
        
        // Extract data from the current line
        getline(ss, phoneNo, ',');
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, description, ',');

        // If the name matches the one we want to update
        if (name == find) {
            found = true;
            cout << "Enter new phone number: ";
            getline(cin, phoneNo);
            cout << "Enter new address: ";
            getline(cin, address);
            cout << "Enter new description: ";
            getline(cin, description);
        }

        // Write the updated or unchanged data to the temporary file
        tempFile << phoneNo << "," << name << "," << address << "," << description << "\n";
    }

    file.close();
    tempFile.close();

    // Remove the original file
    remove("data.csv");
    // Rename the temporary file to the original file name
    rename("temp.csv", "data.csv");

    if (found) {
        cout << "Contact updated successfully." << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}


void temp :: deleteContact() {
    string find;
    cout << "Enter the name of the contact you want to delete: ";
    cin.ignore(); // Ignore any leftover newline characters in the input buffer
    getline(cin, find);

    fstream file("data.csv", ios::in); // Open file for reading
    ofstream tempFile("temp.csv", ios::out); // Create a temporary file for writing updated data

    string line;
    bool found = false;

    // Iterate through each line in the file
    while (getline(file, line)) {
        stringstream ss(line);
        string phoneNo, name, address, description;
        
        // Extract data from the current line
        getline(ss, phoneNo, ',');
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, description, ',');

        // If the name matches the one we want to delete
        if (name == find) {
            found = true;
            continue; // Skip writing this line to the temporary file
        }

        // Write the unchanged data to the temporary file
        tempFile << phoneNo << "," << name << "," << address << "," << description << "\n";
    }

    file.close();
    tempFile.close();

    // Remove the original file
    remove("data.csv");
    // Rename the temporary file to the original file name
    rename("temp.csv", "data.csv");

    if (found) {
        cout << "Contact deleted successfully." << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}


