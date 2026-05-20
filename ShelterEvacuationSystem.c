#include <stdio.h>
#include <string.h>

#define MAX_SHELTERS 100

typedef enum{
    NONE = 0,
    FLOOD = 1,
    EARTHQUAKE = 2,
    FIRE = 3, 
    TORNADO = 4,

}DisasterType;

typedef struct{
    char name[50];
    int capacity;
    int occupancy;
    int accessibility;
    int structuralsafety;
    int medicalfacility;
    int resourceavailability;
    int elevation;
    float score;
} Shelter;

Shelter shelters[MAX_SHELTERS];
int shelterCount = 0;
DisasterType selectDisaster = NONE;

void addShelter() {
    if (shelterCount >= MAX_SHELTERS) {
        printf("\nShelter storage is full!\n");
        return;
    }

    printf("==== ADD SHELTER ====\n");

    printf("Shelter name: ");
    scanf(" %[^\n]", shelters[shelterCount].name);

    printf("Capacity: ");
    scanf("%d", &shelters[shelterCount].capacity);

    printf("Current occupancy: ");
    scanf("%d", &shelters[shelterCount].occupancy);

    printf("Accessibility score [0-100]: ");
    scanf("%d", &shelters[shelterCount].accessibility);

    printf("Structural safety score [0-100]: ");
    scanf("%d", &shelters[shelterCount].structuralsafety);

    printf("Medical facility available? [1 = Yes / 0 = No]: ");
    scanf("%d", &shelters[shelterCount].medicalfacility);

    printf("Resource availability score [0-100]: ");
    scanf("%d", &shelters[shelterCount].resourceavailability);

    printf("Elevation level in meters: ");
    scanf("%d", &shelters[shelterCount].elevation);

    shelters[shelterCount].score = 0;
    shelterCount++;

    printf("\nShelter successfully added!\n");
}

void displayShelters() {
  if (shelterCount == 0) {
        printf("\nNo shelter data available.\n");
        return;
    }

    printf("\n==== SHELTER LIST ====\n");

    for (int i = 0; i < shelterCount; i++) {
        int remaining = shelters[i].capacity - shelters[i].occupancy;

        printf("\n[%d] %s\n", i + 1, shelters[i].name);
        printf("Capacity              : %d\n", shelters[i].capacity);
        printf("Occupancy             : %d\n", shelters[i].occupancy);
        printf("Remaining Capacity    : %d\n", remaining);
        printf("Accessibility         : %d/100\n", shelters[i].accessibility);
        printf("Structural Safety     : %d/100\n", shelters[i].structuralsafety);
        printf("Medical Facility      : %s\n", shelters[i].medicalfacility ? "Available" : "Not Available");
        printf("Resource Availability : %d/100\n", shelters[i].resourceavailability);
        printf("Elevation             : %d m\n", shelters[i].elevation);
    }
}

void selectDisasterType() {

}

void calculateBestRecommendation() {

}

void showShelterRanking() {

}


int main() {
    int choice;

    do {
        printf("\n========================================\n");
        printf(" DISASTER EVACUATION SHELTER SYSTEM\n");
        printf("========================================\n");
        printf("1. Add Shelter\n");
        printf("2. Display Shelters\n");
        printf("3. Select Disaster Type\n");
        printf("4. Calculate Best Recommendation\n");
        printf("5. Show Shelter Ranking\n");
        printf("6. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addShelter();
                break;
            case 2:
                displayShelters();
                break;
            case 3:
                selectDisasterType();
                break;
            case 4:
                calculateBestRecommendation();
                break;
            case 5:
                showShelterRanking();
                break;
            case 6:
                printf("\nExiting program. Stay safe!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}