#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    char name[50];
    int age;
    char gender[10];
    int id;
    struct Patient* next;
};


struct Reservation {
    int slot;
    int patientId;
    struct Reservation* next;
};

int availableSlots[5] = {1, 1, 1, 1, 1};


int isIdExists(struct Patient* head, int id) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void addPatient(struct Patient** head) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    printf("Enter patient name: ");
    scanf("%s", newPatient->name);
    printf("Enter patient age: ");
    scanf("%d", &(newPatient->age));
    printf("Enter patient gender: ");
    scanf("%s", newPatient->gender);
    printf("Enter patient ID: ");
    scanf("%d", &(newPatient->id));

    if (isIdExists(*head, newPatient->id)) {
        printf("Error: ID already exists.\n");
        free(newPatient);
        return;
    }

    newPatient->next = NULL;

    if (*head == NULL) {
        *head = newPatient;
    } else {
        struct Patient* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPatient;
    }

    printf("\nNew patient record added successfully.\n");
}

void editPatient(struct Patient* head, int id) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Enter new name: ");
            scanf("%s", current->name);
            printf("Enter new age: ");
            scanf("%d", &(current->age));
            printf("Enter new gender: ");
            scanf("%s", current->gender);
            printf("Patient record updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Error: Incorrect ID. Patient record not found.\n");
}


void reserveSlot(struct Reservation** reservations, struct Patient* head) {
    int slot;
    printf("Available Slots:\n");
    for (int i = 0; i < 5; i++) {
        if (availableSlots[i] == 1) {
            printf("%d. ", i);
            switch (i) {
                case 0:
                    printf("2pm to 2:30pm\n");
                    break;
                case 1:
                    printf("2:30pm to 3pm\n");
                    break;
                case 2:
                    printf("3pm to 3:30pm\n");
                    break;
                case 3:
                    printf("4pm to 4:30pm\n");
                    break;
                case 4:
                    printf("4:30pm to 5pm\n");
                    break;
                default:
                    break;
            }
        }
    }

    printf("Enter patient ID: ");
    int id;
    scanf("%d", &id);

    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Enter slot number: ");
            scanf("%d", &slot);

            if (slot < 0 || slot >= 5) {
                printf("Error: Invalid slot number.\n");
                return;
            }

            if (availableSlots[slot] == 0) {
                printf("Error: Slot already reserved.\n");
                return;
            }

            availableSlots[slot] = 0;

            struct Reservation* newReservation = (struct Reservation*)malloc(sizeof(struct Reservation));
            newReservation->slot = slot;
            newReservation->patientId = id;
            newReservation->next = NULL;

            if (*reservations == NULL) {
                *reservations = newReservation;
            } else {
                struct Reservation* currentReservation = *reservations;
                while (currentReservation->next != NULL) {
                    currentReservation = currentReservation->next;
                }
                currentReservation->next = newReservation;
            }

            printf("Slot reserved successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Error: Incorrect ID. Patient record not found.\n");
}

void cancelReservation(struct Reservation** reservations) {
    printf("Enter patient ID: ");
    int id;
    scanf("%d", &id);

    struct Reservation* current = *reservations;
    struct Reservation* previous = NULL;

    while (current != NULL) {
        if (current->patientId == id) {
            int slot = current->slot;
            availableSlots[slot] = 1;

            if (previous == NULL) {
                *reservations = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            printf("Reservation canceled successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Error: Reservation not found.\n");
}

void viewPatientRecord(struct Patient* head, int id) {
    struct Patient* current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("Name: %s\n", current->name);
            printf("Age: %d\n", current->age);
            printf("Gender: %s\n", current->gender);
            return;
        }
        current = current->next;
    }

    printf("Error: Incorrect ID. Patient record not found.\n");
}

void viewReservations(struct Reservation* reservations) {
    printf("Today's Reservations:\n");
    struct Reservation* current = reservations;
    while (current != NULL) {
        printf("Slot: %d, Patient ID: %d\n", current->slot, current->patientId);
        current = current->next;
    }
}

int main() {
    int isAdmin;
    printf("============================\n");
    printf("Clinic Management System\n");
    printf("============================\n");
    printf("If you are admin enter 1\n");
    printf("If you are user enter 0\nEnter : ");
    scanf("%d", &isAdmin);
    printf("\n============================\n");

    if (isAdmin)
     {
        int passwordAttempts = 0;
        int password;
        while (passwordAttempts < 3)
         {

            printf("Please enter password: ");
            scanf("%d", &password);

            if (password == 1234) {
                break;
            }

            passwordAttempts++;
            printf("Incorrect password. Attempts remaining: %d\n", 3 - passwordAttempts);
        }

        if (passwordAttempts == 3) {
            printf("Too many incorrect password attempts. Exiting.\n");
            return 0;
        }

        struct Patient* patientList = NULL;
        struct Reservation* reservationList = NULL;

        int choice;
        do {
            printf("============================\n");
            printf("Admin Login Successfully\n");
            printf("\nAdmin Menu:\n");
            printf("1. Add new patient record\n");
            printf("2. Edit patient record\n");
            printf("3. Reserve a slot with the doctor\n");
            printf("4. Cancel reservation\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
             {
                case 1:
                    addPatient(&patientList);
                    break;
                case 2:
                    printf("Enter patient ID: ");
                    int id;
                    scanf("%d", &id);
                    editPatient(patientList, id);
                    break;
                case 3:
                    reserveSlot(&reservationList, patientList);
                    break;
                case 4:
                    cancelReservation(&reservationList);
                    break;
                case 0:
                    ////
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
        } while (choice != 0);
    } else {
        struct Patient* patientList = NULL;
        struct Reservation* reservationList = NULL;

        int choice;
        do {
            printf("\nUser Menu:\n");
            printf("1. View patient record\n");
            printf("2. View today's reservations\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter patient ID: ");
                    int id;
                    scanf("%d", &id);
                    viewPatientRecord(patientList, id);
                    break;
                case 2:
                    viewReservations(reservationList);
                    break;
                case 0:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
        } while (choice != 0);
    }

    return 0;
}