#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

// Patient data
struct Patient {
    string name;
    int age;
    string soundLevels;
    string brainActivity;
    string symptoms;
    string cbtSessions;
    string mindfulnessSessions;
    string medications;
    string soundTherapySessions;
    Patient* next;
};

// Album of tracks for tinnitus relief
string tinnitusTracks[] = {
    "Track 1: Gentle Rain",
    "Track 2: Ocean Waves",
    "Track 3: Forest Ambience",
    "Track 4: White Noise",
    "Track 5: Soft Piano"
};

// Suggest treatments
void suggestTreatments(const Patient* patient) {
    cout << "Suggested Treatments: ";
    if (patient->symptoms.find("ringing") != string::npos || patient->soundLevels == "High") {
        cout << "Sound therapy, Cognitive Behavioral Therapy, ";
    }
    if (patient->brainActivity == "Mild abnormality" || patient->symptoms.find("buzzing") != string::npos) {
        cout << "Tinnitus retraining therapy, Medications, ";
    }
    if (patient->soundLevels == "Moderate") {
        cout << "Hearing aids, Biofeedback, ";
    }
    if (patient->brainActivity == "Normal" && patient->symptoms.find("ringing") == string::npos) {
        cout << "Stress management, Exercise, Acupuncture, ";
    }
    cout << "Diet changes, Sleep therapy, Vitamin B12 supplementation, Ginkgo biloba" << endl;
}

// Validate age input
bool isValidAge(int age) {
    return age > 0 && age < 150;
}

// Validate choice input
bool isValidChoice(int choice, int min, int max) {
    return choice >= min && choice <= max;
}

// Create a new patient node
Patient* createPatient() {
    Patient* newPatient = new Patient();

    cout << "Enter patient's name: ";
    getline(cin, newPatient->name);
    cout << "Enter patient's age: ";
    cin >> newPatient->age;
    while (!isValidAge(newPatient->age)) {
        cout << "Invalid age. Enter patient's age: ";
        cin >> newPatient->age;
    }
    cin.ignore();
    cout << "Enter patient's sound levels: ";
    getline(cin, newPatient->soundLevels);
    cout << "Enter patient's brain activity: ";
    getline(cin, newPatient->brainActivity);
    cout << "Enter patient's symptoms: ";
    getline(cin, newPatient->symptoms);
    newPatient->next = nullptr;
    suggestTreatments(newPatient);
    return newPatient;
}

// Add a patient to the linked list
void addPatient(Patient*& head, Patient* newPatient) {
    if (head == nullptr) {
        head = newPatient;
    } else {
        Patient* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }
}

// Search for a patient
Patient* searchPatient(Patient* head, string name) {
    Patient* temp = head;
    while (temp != nullptr) {
        if (temp->name == name) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Display a patient's data
void displayPatient(Patient* patient) {
    if (patient == nullptr) {
        cout << "Patient not found." << endl;
        return;
    }
    cout << "Name: " << patient->name << endl;
    cout << "Age: " << patient->age << endl;
    cout << "Sound Levels: " << patient->soundLevels << endl;
    cout << "Brain Activity: " << patient->brainActivity << endl;
    cout << "Symptoms: " << patient->symptoms << endl;
    suggestTreatments(patient);
    // Display all sessions
    cout << "Sessions:" << endl;
    // CBT
    cout << "1. Cognitive Behavioral Therapy (CBT): " << patient->cbtSessions << endl;
    if (!patient->cbtSessions.empty()) {
        size_t pos = 0;
        size_t found = patient->cbtSessions.find(',');
        int sessionNum = 1;
        while (found != string::npos) {
            cout << "   Session " << sessionNum++ << ": " << patient->cbtSessions.substr(pos, found - pos) << endl;
            pos = found + 1;
            found = patient->cbtSessions.find(',', pos);
        }
        cout << "Session " << sessionNum++ << ": " << patient->cbtSessions.substr(pos) << endl;
    } else {
        cout << "No CBT sessions added yet." << endl;
    }
    // Mindfulness
    cout << "2. Mindfulness Sessions: " << patient->mindfulnessSessions << endl;
    if (!patient->mindfulnessSessions.empty()) {
        size_t pos = 0;
        size_t found = patient->mindfulnessSessions.find(',');
        int sessionNum = 1;
        while (found != string::npos) {
            cout << "   Session " << sessionNum++ << ": " << patient->mindfulnessSessions.substr(pos, found - pos) << endl;
            pos = found + 1;
            found = patient->mindfulnessSessions.find(',', pos);
        }
        cout << "   Session " << sessionNum++ << ": " << patient->mindfulnessSessions.substr(pos) << endl;
    } else {
        cout << "No mindfulness sessions added yet." << endl;
    }
    // Medication
    cout << "3. Medications: " << patient->medications << endl;
    if (!patient->medications.empty()) {
        size_t pos = 0;
        size_t found = patient->medications.find(',');
        int sessionNum = 1;
        while (found != string::npos) {
            cout << "   Session " << sessionNum++ << ": " << patient->medications.substr(pos, found - pos) << endl;
            pos = found + 1;
            found = patient->medications.find(',', pos);
        }
        cout << "   Session " << sessionNum++ << ": " << patient->medications.substr(pos) << endl;
    } else {
        cout << "No medications added yet." << endl;
    }
    // Sound Therapy
    cout << "4. Sound Therapy Sessions:" << endl;
    if (!patient->soundTherapySessions.empty()) {
        size_t pos = 0;
        size_t found = patient->soundTherapySessions.find(',');
        int sessionNum = 1;
        while (found != string::npos) {
            cout << "   Session " << sessionNum++ << ": " << patient->soundTherapySessions.substr(pos, found - pos) << endl;
            pos = found + 1;
            found = patient->soundTherapySessions.find(',', pos);
        }
        cout << "   Session " << sessionNum++ << ": " << patient->soundTherapySessions.substr(pos) << endl;
    } else {
        cout << "No sound therapy sessions added yet." << endl;
    }
}

// Manage sessions
void manageSessions(Patient* patient) {
    int choice;
    while (true) {
        cout << "Select session to manage:" << endl;
        cout << "1. Cognitive Behavioral Therapy (CBT)" << endl;
        cout << "2. Mindfulness Session" << endl;
        cout << "3. Manage Medication" << endl;
        cout << "4. Perform Sound Therapy" << endl;
        cout << "5. Exit session management" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        while (!isValidChoice(choice, 1, 5)) {
            cout << "Invalid choice. Enter your choice: ";
            cin >> choice;
        }
        cin.ignore();
        switch (choice) {
            case 1:
                {
        string session;
        cout << "Enter details of the CBT session: ";
        getline(cin, session);
        if (patient->cbtSessions.empty()) {
        patient->cbtSessions = session;
        } else {
        patient->cbtSessions += "," + session;
        }
        cout << "CBT session added." << endl;
        }
        break;
        case 2:
        {
        string session;
        cout << "Enter details of the mindfulness session: ";
        getline(cin, session);
        if (patient->mindfulnessSessions.empty()) {
        patient->mindfulnessSessions = session;
        } else {
        patient->mindfulnessSessions += "," + session;
        }
        cout << "Mindfulness session added." << endl;
        }
        break;
        case 3:
        {
        string medication;
        cout << "Enter medication details: ";
        getline(cin, medication);
        if (patient->medications.empty()) {
        patient->medications = medication;
        } else {
        patient->medications += "," + medication;
        }
        cout << "Medication added." << endl;
        }
        break;
        case 4:
        {
        cout << "Album of specific tracks for tinnitus relief:" << endl;
        for (size_t i = 0; i < sizeof(tinnitusTracks) / sizeof(tinnitusTracks[0]); ++i) {
        cout << i + 1 << ". " << tinnitusTracks[i] << endl;
        }
        string selectedSessions;
        int trackChoice;
        while (true) {
        cout << "Select a track to add (1-" << sizeof(tinnitusTracks) / sizeof(tinnitusTracks[0]) << ") or 0 to stop: ";
        cin >> trackChoice;
        while (!isValidChoice(trackChoice, 0, sizeof(tinnitusTracks) / sizeof(tinnitusTracks[0]))) {
        cout << "Invalid choice. Select a track to add (1-" << sizeof(tinnitusTracks) / sizeof(tinnitusTracks[0]) << ") or 0 to stop: ";
        cin >> trackChoice;
        }
        if (trackChoice == 0) {
        break;
        }
        if (selectedSessions.empty()) {
        selectedSessions = tinnitusTracks[trackChoice - 1];
        } else {
        selectedSessions += "," + tinnitusTracks[trackChoice - 1];
        }
        }
        if (!selectedSessions.empty()) {
        if (patient->soundTherapySessions.empty()) {
        patient->soundTherapySessions = selectedSessions;
        } else {
        patient->soundTherapySessions += "," + selectedSessions;
        }
        }
        cout << "Sound therapy sessions updated." << endl;
        }
        break;
        case 5:
        return;
        default:
        cout << "Invalid choice. Please try again." << endl;
        break;
        }
    }
}
// Display tinnitus relief tracks
void displayTinnitusTracks() {
cout << "Album of specific tracks for tinnitus relief:" << endl;
for (size_t i = 0; i < sizeof(tinnitusTracks) / sizeof(tinnitusTracks[0]); ++i) {
cout << i + 1 << ". " << tinnitusTracks[i] << endl;
    }
}

// Save patient data to a file
void savePatients(Patient* head) {
    ofstream outFile("patients.txt");
    Patient* temp = head;
    while (temp != nullptr) {
        outFile << temp->name << "\n";
        outFile << temp->age << "\n";
        outFile << temp->soundLevels << "\n";
        outFile << temp->brainActivity << "\n";
        outFile << temp->symptoms << "\n";
        outFile << temp->cbtSessions << "\n";
        outFile << temp->mindfulnessSessions << "\n";
        outFile << temp->medications << "\n";
        outFile << temp->soundTherapySessions << "\n";
        temp = temp->next;
    }
    outFile.close();
}

// Load patient data from a file
Patient* loadPatients() {
    ifstream inFile("patients.txt");
    if (!inFile) {
        cout << "No saved data found." << endl;
        return nullptr;
    }
    Patient* head = nullptr;
    Patient* temp = nullptr;
    while (!inFile.eof()) {
        Patient* newPatient = new Patient();
        getline(inFile, newPatient->name);
        if (newPatient->name.empty()) break;
        inFile >> newPatient->age;
        inFile.ignore();
        getline(inFile, newPatient->soundLevels);
        getline(inFile, newPatient->brainActivity);
        getline(inFile, newPatient->symptoms);
        getline(inFile, newPatient->cbtSessions);
        getline(inFile, newPatient->mindfulnessSessions);
        getline(inFile, newPatient->medications);
        getline(inFile, newPatient->soundTherapySessions);
        newPatient->next = nullptr;
        if (head == nullptr) {
        head = newPatient;
        temp = newPatient;
        } else {
        temp->next = newPatient;
        temp = newPatient;
        }
    }
    inFile.close();
    return head;
}
//Log Action
void logAction(const string& action) {
    ofstream logFile("log.txt", ios_base::app);
    if (logFile.is_open()) {
    time_t now = time(0);
    char* dt = ctime(&now);
    logFile << dt << ": " << action << endl;
    logFile.close();
    } else {
    cerr << "Unable to open log file." << endl;
    }
}
//To generate a report
void generateReport(Patient* patient) {
    ofstream reportFile(patient->name + "_report.txt");
    if (reportFile.is_open()) {
    reportFile << "Name: " << patient->name << endl;
    reportFile << "Age: " << patient->age << endl;
    reportFile << "Sound Levels: " << patient->soundLevels << endl;
    reportFile << "Brain Activity: " << patient->brainActivity << endl;
    reportFile << "Symptoms: " << patient->symptoms << endl;
    reportFile << "CBT Sessions: " << patient->cbtSessions << endl;
    reportFile << "Mindfulness Sessions: " << patient->mindfulnessSessions << endl;
    reportFile << "Medications: " << patient->medications << endl;
    reportFile << "Sound Therapy Sessions: " << patient->soundTherapySessions << endl;
    reportFile.close();
    cout << "Report generated successfully." << endl;
    logAction("Generated report for " + patient->name);
    } else {
    cerr << "Unable to open report file." << endl;
    }
}
// Function to add reminder
void addReminder(const string& reminder) {
    ofstream reminderFile("reminders.txt", ios_base::app);
    if (reminderFile.is_open()) {
    reminderFile << reminder << endl;
    reminderFile.close();
    cout << "Reminder added successfully." << endl;
    logAction("Added reminder: " + reminder);
    } else {
        cerr << "Unable to open reminders file." << endl;
    }
}
// Function to display reminders
void displayReminders() {
    ifstream reminderFile("reminders.txt");
    if (reminderFile.is_open()) {
    string reminder;
    cout << "Reminders:" << endl;
    while (getline(reminderFile, reminder)) {
    cout << "- " << reminder << endl;
        }
     reminderFile.close();
     logAction("Displayed reminders.");
    } else {
    cerr << "No reminders found." << endl;
    }
}
// Search function to filter patients
void filterPatients(Patient* head, const string& criteria, const string& value) {
    Patient* temp = head;
    bool found = false;
    while (temp != nullptr) {
    if ((criteria == "age" && to_string(temp->age) == value) ||
    (criteria == "symptoms" && temp->symptoms.find(value) != string::npos) ||
    (criteria == "treatment" && (temp->cbtSessions.find(value) != string::npos ||
    temp->mindfulnessSessions.find(value) != string::npos ||
    temp->medications.find(value) != string::npos ||
    temp->soundTherapySessions.find(value) != string::npos))) {
    displayPatient(temp);
    found = true;
        }
    temp = temp->next;
    }
    if (!found) {
    cout << "No patients found matching the criteria." << endl;
    }
}
// Error handling function
void handleError(const string& errorMsg) {
    cerr << "Error: " << errorMsg << endl;
    logAction("Error: " + errorMsg);
}
//User Authentication
bool authenticateUser() {
unordered_map<string, string> credentials;
ifstream authFile("auth.txt");
string line;
// Read credentials from the auth file
while (getline(authFile, line)) {
istringstream ss(line);
string username, password;
getline(ss, username, ',');
getline(ss, password, '\n');
credentials[username] = password;
}
int attempts = 0;
const int maxAttempts = 5;
while (attempts < maxAttempts) {
string username, password;
cout << "Enter username: ";
getline(cin, username);
cout << "Enter password: ";
getline(cin, password);
// Check credentials
if (credentials.find(username) != credentials.end() && credentials[username] == password) {
logAction("User " + username + " logged in.");
return true;
} else {
cout << "Invalid username or password. Attempts left: " << maxAttempts - attempts - 1 << endl;
attempts++;
}
}
cout << "Maximum login attempts reached. Exiting program." << endl;
logAction("Maximum login attempts reached. Program terminated.");
return false;
}

int main() {
    if (!authenticateUser()) {
    handleError("Authentication failed.");
    return 1;
    }

    Patient* head = loadPatients();
    int choice;
    cout << "*** TINNITUS MANAGEMENT AND ANALYSIS SYSTEM ***\n" << endl;
    cout << "\n";

    while (true) {
    cout << "Otolaryngologist's Record:\n";
    cout << "\n";
    cout << "1. Add a new patient" << endl;
    cout << "2. Search for a patient" << endl;
    cout << "3. Display patient details" << endl;
    cout << "4. Manage sessions for a patient" << endl;
    cout << "5. Display album of tinnitus relief tracks" << endl;
    cout << "6. Generate patient report" << endl;
    cout << "7. Add reminder" << endl;
    cout << "8. Display reminders" << endl;
    cout << "9. Filter patients" << endl;
    cout << "10. Exit" << endl;
    cout << "\n";
    cout << "Enter your choice: ";
    cin >> choice;
    while (!isValidChoice(choice, 1, 10)) {
    cout << "Invalid choice. Enter your choice: ";
    cin >> choice;
        }
    cin.ignore();

    switch (choice) {
    case 1:
    {
    Patient* newPatient = createPatient();
    addPatient(head, newPatient);
    cout << "Patient added successfully." << endl;
    cout << "\n";
    savePatients(head);
    logAction("Added new patient: " + newPatient->name);
    }
    break;
    case 2:
    {
    string name;
    cout << "Enter patient's name to search: ";
    getline(cin, name);
    Patient* foundPatient = searchPatient(head, name);
    if (foundPatient == nullptr) {
    handleError("Patient not found.");
    } else {
    cout << "Patient found. Type 3 to display details." << endl;
     logAction("Searched for patient: " + name);
    }
    }
    break;
    case 3:
    {
    string name;
    cout << "Enter patient's name to display details: ";
    getline(cin, name);
    Patient* foundPatient = searchPatient(head, name);
    if (foundPatient == nullptr) {
    handleError("Patient not found.");
    } else {
    displayPatient(foundPatient);
    logAction("Displayed patient details for: " + name);
    }
    }
    break;
    case 4:
    {
    string name;
    cout << "Enter patient's name to manage sessions: ";
    getline(cin, name);
    Patient* foundPatient = searchPatient(head, name);
    if (foundPatient == nullptr) {
    handleError("Patient not found.");
    } else {
    manageSessions(foundPatient);
    savePatients(head);
    logAction("Managed sessions for patient: " + name);
    }
    }
    break;
    case 5:
    displayTinnitusTracks();
    logAction("Displayed tinnitus relief tracks.");
    break;
    case 6:
    {
    string name;
    cout << "Enter patient's name to generate report: ";
    getline(cin, name);
    Patient* foundPatient = searchPatient(head, name);
    if (foundPatient == nullptr) {
    handleError("Patient not found.");
    } else {
    generateReport(foundPatient);
    }
    }
    break;
    case 7:
    {
    string reminder;
    cout << "Enter reminder: ";
    getline(cin, reminder);
    addReminder(reminder);
    }
    break;
    case 8:
    displayReminders();
    break;
    case 9:
    {
    string criteria, value;
    cout << "Enter filter criteria (age, symptoms, treatment): ";
    getline(cin, criteria);
    cout << "Enter filter value: ";
    getline(cin, value);
    filterPatients(head, criteria, value);
    }
    break;
    case 10:
    cout << "Exiting program." << endl;
    savePatients(head);
    logAction("Exited program.");
    while (head != nullptr) {
    Patient* temp = head;
    head = head->next;
    delete temp;
    }
    return 0;
    default:
    handleError("Invalid choice.");
    break;
    }
    }

    return 0;
}
