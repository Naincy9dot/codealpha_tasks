//LOGIN AND REGISTRATION SYSTEM 
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

// File to store user credentials
const string DATABASE_FILE = "users.txt";

// Function to hash password (simple hash for demo, not secure in real systems!)
string hashPassword(const string &password) {
    string hash = "";
    for (char c : password) {
        hash += to_string((c * 17) % 256); // Simple obfuscation
    }
    return hash;
}

// Function to load all users from file into memory
unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream file(DATABASE_FILE);
    string username, passwordHash;

    while (file >> username >> passwordHash) {
        users[username] = passwordHash;
    }

    file.close();
    return users;
}

// Registration Function
void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers();

    if (users.find(username) != users.end()) {
        cout << "Error: Username already exists! Try another.\n";
        return;
    }

    ofstream file(DATABASE_FILE, ios::app);
    file << username << " " << hashPassword(password) << "\n";
    file.close();

    cout << "Registration successful!\n";
}

// Login Function
void loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers();

    if (users.find(username) == users.end()) {
        cout << "Error: Username not found!\n";
        return;
    }

    if (users[username] == hashPassword(password)) {
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "Error: Incorrect password!\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Login & Registration System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}