#include <iostream>
#include <string>

using namespace std;

// ---------- MAIN MENU ----------
void showMainMenu() {
    cout << "\n==============================\n";
    cout << "   EMERGENCY SUPPORT SYSTEM\n";
    cout << "==============================\n";
    cout << "1. I am in an Emergency\n";
    cout << "2. Emergency Phone Numbers\n";
    cout << "3. Safety Awareness\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

// ---------- INPUT VALIDATION ----------
int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter a number between "
                 << min << " and " << max << ": ";
        } else {
            return choice;
        }
    }
}

// ---------- SHOW INSTRUCTIONS ----------
void showInstructions(string title, string steps[], int size) {
    cout << "\n" << title << " Instructions:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << steps[i] << endl;
    }
}

// ---------- SEND HELP ----------
void sendHelp(string emergency, string number, string location) {
    cout << "\n------------------------------\n";
    cout << "Emergency Type : " << emergency << endl;
    cout << "Contact Number : " << number << endl;
    cout << "Location       : " << location << endl;
    cout << "Status         : Help request sent\n";
    cout << "Red Cross / Red Crescent (907) notified if needed\n";
    cout << "------------------------------\n";
}

// ---------- PHONE NUMBERS ----------
void showEmergencyNumbers() {
    string numbers[] = {
        "Police Emergency     : 911 / 916",
        "Red crescent / Red Cross: 907",
        "Fire Department      : 939",
        "Power Outage         : 905",
        "Ambulance            : 8035"
    };

    cout << "\nEmergency Phone Numbers:\n";
    for (string n : numbers)
        cout << n << endl;
}

// ---------- BACK OR EXIT ----------
bool backOrExit() {
    cout << "\n1. Go back to Main Menu\n";
    cout << "2. Exit Application\n";
    cout << "Choose: ";
    return getValidChoice(1, 2) == 1;
}

// ---------- SAFETY AWARENESS ----------
void showAwareness() {
    cout << "\nSafety Awareness:\n";
    cout << "- Fire Safety: Avoid overloads, know exits\n";
    cout << "- First Aid: Stop bleeding, call 8035\n";
    cout << "- Accident Prevention: Follow safety rules\n";
    cout << "- Natural Disasters: Prepare emergency kits\n";
    cout << "- Security Threats: Stay alert, report immediately\n";
}

// ---------- MAIN ----------
int main() {
    bool running = true;
    string location;

    // Emergency data
    string emergencies[] = {
        "Fire Emergency",
        "Medical Emergency",
        "Police Emergency",
        "Power Outage",
        "Natural Disaster",
        "Security Threat"
    };

    string numbers[] = {
        "939", "907", "911 / 916", "905", "8035", "911 / 916"
    };

    // Instructions
    string fire[] = {"Stay calm", "Evacuate immediately", "Do not use elevators", "Move away"};
    string medical[] = {"Stay calm", "Call Ambulance (8035)", "Give first aid if trained", "Wait for help"};
    string police[] = {"Stay calm", "Avoid confrontation",  "Call police (911/916)", "Go to a safe place"};
    string power[] = {"Use flashlight", "Avoid candles", "Unplug electronics", "Report outage (call 905)"};

    string earthquake[] = {"Drop, Cover, Hold", "Avoid windows", "Evacuate carefully", "Call Red Cross"};
    string flood[] = {"Move to higher ground", "Avoid flood water", "Listen to alerts", "Call 907"};
    string wind[] = {"Stay indoors", "Secure surroundings", "Avoid travel", "Prepare emergency kit"};

    string robbery[] = {"Stay calm", "Do not resist", "Call police (911/916)", "Report details"};
    string suspicious[] = {"Observe safely", "Do not approach", "Call police (911/916)", "Share information"};

    while (running) {
        showMainMenu();
        int mainChoice = getValidChoice(1, 4);

        if (mainChoice == 1) {
            if (location.empty()) {
                cin.ignore();
                cout << "\nEnter your current location: ";
                getline(cin, location);
            }

            bool reportMore = true;

            while (reportMore) {
                cout << "\nSelect Emergency Type:\n";
                for (int i = 0; i < 6; i++)
                    cout << i + 1 << ". " << emergencies[i] << endl;

                int eChoice = getValidChoice(1, 6);

                if (eChoice == 5) { // Natural Disaster
                    cout << "\n1. Earthquake\n2. Flood\n3. Strong Wind\nChoose: ";
                    int nd = getValidChoice(1, 3);

                    if (nd == 1) showInstructions("Earthquake", earthquake, 4);
                    else if (nd == 2) showInstructions("Flood", flood, 4);
                    else showInstructions("Strong Wind", wind, 4);

                    sendHelp("Natural Disaster", "907", location);
                }
                else if (eChoice == 6) { // Security Threat
                    cout << "\n1. Robbery\n2. Suspicious Activity\nChoose: ";
                    int sec = getValidChoice(1, 2);

                    if (sec == 1) showInstructions("Robbery", robbery, 4);
                    else showInstructions("Suspicious Activity", suspicious, 4);

                    sendHelp("Security Threat", "911 / 916", location);
                }
                else {
                    string* lists[] = {fire, medical, police, power};
                    showInstructions(emergencies[eChoice - 1], lists[eChoice - 1], 4);
                    sendHelp(emergencies[eChoice - 1], numbers[eChoice - 1], location);
                }

                cout << "\nDo you want to report another emergency?\n";
                cout << "1. Yes\n2. No\nChoose: ";
                reportMore = (getValidChoice(1, 2) == 1);
            }

            running = backOrExit();
        }
        else if (mainChoice == 2) {
            showEmergencyNumbers();
            running = backOrExit();
        }
        else if (mainChoice == 3) {
            showAwareness();
            running = backOrExit();
        }
        else {
            cout << "\nExiting system. Stay safe!\n";
            running = false;
        }
    }

    return 0;
}
