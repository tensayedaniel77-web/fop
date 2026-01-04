// File: emergency_system.cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// Data (arrays)
const int NUM_SERVICES = 5;
string emergencyTypes[NUM_SERVICES] = {"Fire", "Medical", "Police", "Ambulance", "Poison Control"};
string contactNumbers[NUM_SERVICES] = {"101", "102", "100", "108", "1800-111-111"};

// Function prototypes
void displayMainMenu();
void showEmergencyContacts(int choice);
void displayContact(const string* contactPtr);
void showInstructions(int choice);
int getValidatedChoice();
void searchEmergency(const string services[], const string contacts[], int size);

// Main program
int main() {
    int choice = 0;
    cout << "=== Emergency Contact Alert System ===\n";
    do {
        displayMainMenu();
        choice = getValidatedChoice();

        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                showEmergencyContacts(choice - 1);
                showInstructions(choice - 1);
                break;
            case 6:
                searchEmergency(emergencyTypes, contactNumbers, NUM_SERVICES);
                break;
            case 7:
                cout << "Exiting the Emergency Contact Alert System. Stay safe!\n";
                break;
            default:
                cout << "Invalid selection. Please choose a number from the menu.\n";
                break;
        }

        if (choice != 7) {
            cout << "\nPress Enter to return to the main menu...";
            // Clear any leftover input and wait for Enter
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 7);

    return 0;
}

// Display the main menu
void displayMainMenu() {
    cout << "\nMain Menu:\n";
    for (int i = 0; i < NUM_SERVICES; ++i) {
        cout << "  " << (i + 1) << ". " << emergencyTypes[i] << "\n";
    }
    cout << "  6. Search emergency by name\n";
    cout << "  7. Exit\n";
    cout << "Select an option (1-" << (NUM_SERVICES + 2) << "): ";
}

// Show contact details for a selected emergency (uses pointer demo)
void showEmergencyContacts(int index) {
    if (index < 0 || index >= NUM_SERVICES) {
        cout << "Error: invalid emergency index.\n";
        return;
    }
    // Pointer demonstration
    const string* contactPtr = &contactNumbers[index];
    cout << "\n--- " << emergencyTypes[index] << " Emergency ---\n";
    displayContact(contactPtr);
}

// Display contact using a pointer
void displayContact(const string* contactPtr) {
    if (contactPtr == nullptr) {
        cout << "No contact available.\n";
        return;
    }
    cout << "Emergency Contact Number: " << *contactPtr << "\n";
}

// Show brief instructions for the selected emergency
void showInstructions(int index) {
    cout << "Instructions:\n";
    switch (index) {
        case 0: // Fire
            cout << "  - Evacuate the area if safe; call the fire station immediately.\n";
            cout << "  - Do not use elevators; assist others if possible.\n";
            break;
        case 1: // Medical
            cout << "  - Check responsiveness and breathing; call for an ambulance.\n";
            cout << "  - Provide first aid if trained; keep the person comfortable.\n";
            break;
        case 2: // Police
            cout << "  - Move to a safe location; call the police to report threats or crimes.\n";
            cout << "  - Provide clear details: location, description, and immediate danger.\n";
            break;
        case 3: // Ambulance
            cout << "  - Call ambulance for urgent medical transport; follow dispatcher instructions.\n";
            break;
        case 4: // Poison Control
            cout << "  - If ingestion or exposure suspected, call poison control immediately.\n";
            cout << "  - Do not induce vomiting unless instructed by a professional.\n";
            break;
        default:
            cout << "  - No instructions available.\n";
            break;
    }
}

// Get validated numeric choice from user (handles non-numeric input)
int getValidatedChoice() {
    string input;
    int number = -1;
    if (!getline(cin, input)) {
        return -1;
    }
    // Trim leading/trailing spaces
    auto l = input.find_first_not_of(" \t\r\n");
    auto r = input.find_last_not_of(" \t\r\n");
    if (l == string::npos) {
        return -1;
    }
    input = input.substr(l, r - l + 1);

    // Check that input is all digits
    bool allDigits = !input.empty() && (input.find_first_not_of("0123456789") == string::npos);
    if (allDigits) {
        try {
            number = stoi(input);
        } catch (...) {
            number = -1;
        }
    } else {
        number = -1;
    }
    return number;
}

// Search emergency by name (case-insensitive)
void searchEmergency(const string services[], const string contacts[], int size) {
    cout << "\nEnter emergency name to search (e.g., Fire, Medical): ";
    string query;
    if (!getline(cin, query) || query.empty()) {
        cout << "No input provided.\n";
        return;
    }

    // Normalize query to lowercase safely
    transform(query.begin(), query.end(), query.begin(),
              [](unsigned char c){ return static_cast<char>(std::tolower(c)); });

    bool found = false;
    for (int i = 0; i < size; ++i) {
        string serviceLower = services[i];
        transform(serviceLower.begin(), serviceLower.end(), serviceLower.begin(),
                  [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
        if (serviceLower.find(query) != string::npos) {
            cout << "\nFound: " << services[i] << " -> " << contacts[i] << "\n";
            showInstructions(i);
            found = true;
        }
    }
    if (!found) {
        cout << "No matching emergency service found for \"" << query << "\".\n";
    }
}
