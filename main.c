#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_TRACKS 5
#define MAX_REMINDERS 100
#define MAX_LOG_LENGTH 1000

typedef struct Patient {
    char name[100];
    int age;
    char soundLevels[50];
    char brainActivity[50];
    char symptoms[256];
    char cbtSessions[1024];
    char mindfulnessSessions[1024];
    char medications[1024];
    char soundTherapySessions[1024];
    struct Patient* next;
} Patient;

const char* tinnitusTracks[MAX_TRACKS] = {
    "Track 1: Gentle Rain",
    "Track 2: Ocean Waves",
    "Track 3: Forest Ambience",
    "Track 4: White Noise",
    "Track 5: Soft Piano"
};

pthread_mutex_t lock;

// Function prototypes
void suggestTreatments(const Patient* patient);
int isValidAge(int age);
int isValidChoice(int choice, int min, int max);
Patient* createPatient();
void addPatient(Patient** head, Patient* newPatient);
Patient* searchPatient(Patient* head, const char* name);
void displayPatient(const Patient* patient);
void manageSessions(Patient* patient);
void displayTinnitusTracks();
void savePatients(Patient* head);
Patient* loadPatients();
void logAction(const char* action);
void generateReport(const Patient* patient);
void addReminder(const char* reminder);
void displayReminders();
void filterPatients(Patient* head, const char* criteria, const char* value);
void handleError(const char* errorMsg);
int authenticateUser();

void suggestTreatments(const Patient* patient) {
    printf("Suggested Treatments: ");
    if (strstr(patient->symptoms, "ringing") != NULL || strcmp(patient->soundLevels, "High") == 0) {
        printf("Sound therapy, Cognitive Behavioral Therapy, ");
    }
    if (strcmp(patient->brainActivity, "Mild abnormality") == 0 || strstr(patient->symptoms, "buzzing") != NULL) {
        printf("Tinnitus retraining therapy, Medications, ");
    }
    if (strcmp(patient->soundLevels, "Moderate") == 0) {
        printf("Hearing aids, Biofeedback, ");
    }
    if (strcmp(patient->brainActivity, "Normal") == 0 && strstr(patient->symptoms, "ringing") == NULL) {
        printf("Stress management, Exercise, Acupuncture, ");
    }
    printf("Diet changes, Sleep therapy, Vitamin B12 supplementation, Ginkgo biloba\n");
}

int isValidAge(int age) {
    return age > 0 && age < 150;
}

int isValidChoice(int choice, int min, int max) {
    return choice >= min && choice <= max;
}

Patient* createPatient() {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (!newPatient) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    printf("Enter patient's name: ");
    fgets(newPatient->name, sizeof(newPatient->name), stdin);
    newPatient->name[strcspn(newPatient->name, "\n")] = 0;

    printf("Enter patient's age: ");
    scanf("%d", &newPatient->age);
    while (!isValidAge(newPatient->age)) {
        printf("Invalid age. Enter patient's age: ");
        scanf("%d", &newPatient->age);
    }
    getchar();

    printf("Enter patient's sound levels: ");
    fgets(newPatient->soundLevels, sizeof(newPatient->soundLevels), stdin);
    newPatient->soundLevels[strcspn(newPatient->soundLevels, "\n")] = 0;

    printf("Enter patient's brain activity: ");
    fgets(newPatient->brainActivity, sizeof(newPatient->brainActivity), stdin);
    newPatient->brainActivity[strcspn(newPatient->brainActivity, "\n")] = 0;

    printf("Enter patient's symptoms: ");
    fgets(newPatient->symptoms, sizeof(newPatient->symptoms), stdin);
    newPatient->symptoms[strcspn(newPatient->symptoms, "\n")] = 0;
newPatient->cbtSessions[0] = '\0';
    newPatient->mindfulnessSessions[0] = '\0';
    newPatient->medications[0] = '\0';
    newPatient->soundTherapySessions[0] = '\0';
    newPatient->next = NULL;

    suggestTreatments(newPatient);
    return newPatient;
}

void addPatient(Patient** head, Patient* newPatient) {
    if (*head == NULL) {
        *head = newPatient;
    } else {
        Patient* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPatient;
    }
}

Patient* searchPatient(Patient* head, const char* name) {
    Patient* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void displayPatient(const Patient* patient) {
    if (patient == NULL) {
        printf("Patient not found.\n");
   return;
    }
    printf("Name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
    printf("Sound Levels: %s\n", patient->soundLevels);
    printf("Brain Activity: %s\n", patient->brainActivity);
    printf("Symptoms: %s\n", patient->symptoms);
    suggestTreatments(patient);

    printf("Sessions:\n");
    // CBT
    printf("1. Cognitive Behavioral Therapy (CBT): %s\n", patient->cbtSessions);
    // Mindfulness
    printf("2. Mindfulness Sessions: %s\n", patient->mindfulnessSessions);
    // Medication
    printf("3. Medications: %s\n", patient->medications);
    // Sound Therapy
    printf("4. Sound Therapy Sessions: %s\n", patient->soundTherapySessions);
}

void manageSessions(Patient* patient) {
    int choice;
    while (1) {
        printf("Select session to manage:\n");
        printf("1. Cognitive Behavioral Therapy (CBT)\n");
        printf("2. Mindfulness Session\n");
        printf("3. Manage Medication\n");
        printf("4. Perform Sound Therapy\n");
        printf("5. Exit session management\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (!isValidChoice(choice, 1, 5)) {
            printf("Invalid choice. Enter your choice: ");
            scanf("%d", &choice);
        }
        getchar();
char session[2];
        switch (choice) {
            case 1:
                printf("Enter details of the CBT session: ");
                fgets(session, sizeof(session), stdin);
                session[strcspn(session, "\n")] = 0;
                if (strlen(patient->cbtSessions) > 0) {
                    strcat(patient->cbtSessions, ",");
                }
                strcat(patient->cbtSessions, session);
                printf("CBT session added.\n");
                break;
            case 2:
                printf("Enter details of the mindfulness session: ");
                fgets(session, sizeof(session), stdin);
                session[strcspn(session, "\n")] = 0;
                if (strlen(patient->mindfulnessSessions) > 0) {
                    strcat(patient->mindfulnessSessions, ",");
                }
                strcat(patient->mindfulnessSessions, session);
                printf("Mindfulness session added.\n");
                break;
            case 3:
                printf("Enter medication details: ");
                fgets(session, sizeof(session), stdin);
                session[strcspn(session, "\n")] = 0;
                if (strlen(patient->medications) > 0) {
                    strcat(patient->medications, ",");
                }
                strcat(patient->medications, session);
                printf("Medication added.\n");
                break;
            case 4:
                printf("Album of specific tracks for tinnitus relief:\n");
                for (size_t i = 0; i < MAX_TRACKS; ++i) {
                    printf("%zu. %s\n", i + 1, tinnitusTracks[i]);
}
                char selectedSessions[1024] = "";
                int trackChoice;
                while (1) {
                    printf("Select a track to add (1-%d) or 0 to stop: ", MAX_TRACKS);
                    scanf("%d", &trackChoice);
                    while (!isValidChoice(trackChoice, 0, MAX_TRACKS)) {
                        printf("Invalid choice. Select a track to add (1-%d) or 0 to stop: ", MAX_TRACKS);
                        scanf("%d", &trackChoice);
                    }
                    getchar();
                    if (trackChoice == 0) {
                        break;
                    }
                    if (strlen(selectedSessions) > 0) {
                        strcat(selectedSessions, ", ");
                    }
                    strcat(selectedSessions, tinnitusTracks[trackChoice - 1]);
                }
                strcat(patient->soundTherapySessions, selectedSessions);
                printf("Sound therapy session(s) added.\n");
                break;
            case 5:
                return;
        }
    }
}

void displayTinnitusTracks() {
    printf("Tinnitus Relief Sound Tracks:\n");
    for (int i = 0; i < MAX_TRACKS; ++i) {
        printf("%d. %s\n", i + 1, tinnitusTracks[i]);
    }
}

void savePatients(Patient* head) {
    FILE* file = fopen("patients.dat", "wb");
  if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    Patient* temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(Patient), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

Patient* loadPatients() {
    FILE* file = fopen("patients.dat", "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return NULL;
    }
    Patient* head = NULL;
    Patient* temp = NULL;
    while (1) {
        Patient* newPatient = (Patient*)malloc(sizeof(Patient));
        if (!newPatient) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        if (fread(newPatient, sizeof(Patient), 1, file) != 1) {
            free(newPatient);
            break;
        }
        newPatient->next = NULL;
        if (head == NULL) {
            head = newPatient;
            temp = head;
        } else {
            temp->next = newPatient;
            temp = temp->next;
  }
    }
    fclose(file);
    return head;
}

void logAction(const char* action) {
    FILE* file = fopen("log.txt", "a");
    if (!file) {
        perror("Failed to open log file for appending");
        return;
    }
    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    timestamp[strcspn(timestamp, "\n")] = 0;
    fprintf(file, "[%s] %s\n", timestamp, action);
    fclose(file);
}

void generateReport(const Patient* patient) {
    if (patient == NULL) {
        printf("Patient not found.\n");
        return;
    }
    char filename[128];
    snprintf(filename, sizeof(filename), "%s_report.txt", patient->name);
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open report file for writing");
        return;
    }
    fprintf(file, "Patient Report for %s\n", patient->name);
    fprintf(file, "Name: %s\n", patient->name);
    fprintf(file, "Age: %d\n", patient->age);
    fprintf(file, "Sound Levels: %s\n", patient->soundLevels);
    fprintf(file, "Brain Activity: %s\n", patient->brainActivity);
    fprintf(file, "Symptoms: %s\n", patient->symptoms);
suggestTreatments(patient);
    fprintf(file, "\nSessions:\n");
    fprintf(file, "1. Cognitive Behavioral Therapy (CBT): %s\n", patient->cbtSessions);
    fprintf(file, "2. Mindfulness Sessions: %s\n", patient->mindfulnessSessions);
    fprintf(file, "3. Medications: %s\n", patient->medications);
    fprintf(file, "4. Sound Therapy Sessions: %s\n", patient->soundTherapySessions);
    fclose(file);
    printf("Report generated: %s\n", filename);
}

void addReminder(const char* reminder) {
    static int reminderCount = 0;
    static char reminders[MAX_REMINDERS][256];

    if (reminderCount >= MAX_REMINDERS) {
        printf("Maximum reminder limit reached.\n");
return;
    }

    strncpy(reminders[reminderCount], reminder, sizeof(reminders[reminderCount]) - 1);
    reminders[reminderCount][sizeof(reminders[reminderCount]) - 1] = '\0';
    reminderCount++;

    FILE* file = fopen("reminders.txt", "a");
    if (!file) {
        perror("Failed to open reminders file for appending");
        return;
    }
    fprintf(file, "%s\n", reminder);
    fclose(file);
}

void displayReminders() {
    FILE* file = fopen("reminders.txt", "r");
    if (!file) {
        perror("Failed to open reminders file for reading");
        return;
    }
    char reminder[256];
    printf("Reminders:\n");
    while (fgets(reminder, sizeof(reminder), file) != NULL) {
        printf("- %s", reminder);
    }
    fclose(file);
}

void filterPatients(Patient* head, const char* criteria, const char* value) {
    printf("Patients with %s = %s:\n", criteria, value);
    Patient* temp = head;
    while (temp != NULL) {
        if (strcmp(criteria, "age") == 0 && temp->age == atoi(value)) {
            displayPatient(temp);
        } else if (strcmp(criteria, "sound levels") == 0 && strcmp(temp->soundLevels, value) == 0) {
displayPatient(temp);
        } else if (strcmp(criteria, "brain activity") == 0 && strcmp(temp->brainActivity, value) == 0) {
            displayPatient(temp);
        } else if (strcmp(criteria, "symptoms") == 0 && strstr(temp->symptoms, value) != NULL) {
            displayPatient(temp);
        }
        temp = temp->next;
    }
}

void handleError(const char* errorMsg) {
    perror(errorMsg);
    exit(EXIT_FAILURE);
}

int authenticateUser() {
    const char* correctUsername = "SFS";
    const char* correctPassword = "12345";

    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        return 1; // Authentication successful
    }

    return 0; // Authentication failed
}

void* threadFunc(void* arg) {
    Patient* head = (Patient*)arg;
    printf("***Tinnitus Management and Analysis System***\n");
    printf("\n");
    printf("Otolaryngologist's Record\n");
while (1) {
        printf("\nMenu:\n");
        printf("1. Add a patient\n");
        printf("2. Search for a patient\n");
        printf("3. Display all patients\n");
        printf("4. Manage sessions for a patient\n");
        printf("5. Display tinnitus tracks\n");
        printf("6. Save patients\n");
        printf("7. Load patients\n");
        printf("8. Log action\n");
        printf("9. Generate report for a patient\n");
        printf("10. Add reminder\n");
        printf("11. Display reminders\n");
        printf("12. Filter patients\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar();

        Patient* patient = NULL;
        char name[100], reminder[1000], criteria[100], value[100];

        switch (choice) {
            case 1:
                patient = createPatient();
                pthread_mutex_lock(&lock);
                addPatient(&head, patient);
pthread_mutex_unlock(&lock);
                logAction("Added a new patient");
                break;
            case 2:
                printf("Enter patient's name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                pthread_mutex_lock(&lock);
                patient = searchPatient(head, name);
                pthread_mutex_unlock(&lock);
                displayPatient(patient);
                logAction("Searched for a patient");
                break;
            case 3:
                printf("All patients:\n");
                pthread_mutex_lock(&lock);
                patient = head;
                while (patient != NULL) {
                    displayPatient(patient);
                    patient = patient->next;
                }
                pthread_mutex_unlock(&lock);
                logAction("Displayed all patients");
                break;
            case 4:
                printf("Enter patient's name to manage sessions: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                pthread_mutex_lock(&lock);
                patient = searchPatient(head, name);
                pthread_mutex_unlock(&lock);
                if (patient != NULL) {
                    manageSessions(patient);
                    logAction("Managed sessions for a patient");
                }
                break;
            case 5:
displayTinnitusTracks();
                logAction("Displayed tinnitus tracks");
                break;
            case 6:
                pthread_mutex_lock(&lock);
                savePatients(head);
                pthread_mutex_unlock(&lock);
                logAction("Saved patients");
                break;
            case 7:
                pthread_mutex_lock(&lock);
                head = loadPatients();
                pthread_mutex_unlock(&lock);
                logAction("Loaded patients");
                break;
            case 8:
                printf("Enter action to log: ");
                fgets(reminder, sizeof(reminder), stdin);
                reminder[strcspn(reminder, "\n")] = 0; // Remove newline
                logAction(reminder);
                break;
            case 9:
                printf("Enter patient's name to generate report: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                pthread_mutex_lock(&lock);
                patient = searchPatient(head, name);
                pthread_mutex_unlock(&lock);
                generateReport(patient);
                logAction("Generated report for a patient");
                break;
            case 10:
                printf("Enter reminder: ");
                fgets(reminder, sizeof(reminder), stdin);
                reminder[strcspn(reminder, "\n")] = 0; // Remove newline
                addReminder(reminder);
                logAction("Added a reminder");
break;
            case 11:
                displayReminders();
                logAction("Displayed reminders");
                break;
            case 12:
                printf("Enter criteria (age/sound levels/brain activity/symptoms): ");
                fgets(criteria, sizeof(criteria), stdin);
                criteria[strcspn(criteria, "\n")] = 0; // Remove newline
                printf("Enter value: ");
                fgets(value, sizeof(value), stdin);
                value[strcspn(value, "\n")] = 0; // Remove newline
                pthread_mutex_lock(&lock);
                filterPatients(head, criteria, value);
                pthread_mutex_unlock(&lock);
                logAction("Filtered patients");
                break;
            case 13:
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
}

int main() {
    if (!authenticateUser()) {
        printf("Authentication failed. Exiting...\n");
        return EXIT_FAILURE;
    }

    Patient* head = NULL;

    pthread_t thread;
    pthread_mutex_init(&lock, NULL);

    if (pthread_create(&thread, NULL, threadFunc, (void*)head) != 0) {
        handleError("Failed to create thread");
    }

    pthread_join(thread, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
