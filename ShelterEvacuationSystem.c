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
    int structuralSafety;
    int medicalFacility;
    int resourceAvailability;
    int elevation;
    float score;
} Shelter;

Shelter shelters[MAX_SHELTERS];
int shelterCount = 0;
DisasterType selectedDisaster = NONE;

void addShelter() {
 if (shelterCount >= MAX_SHELTERS) {
        printf("\nShelter storage is full!\n");
        return;
    }

    Shelter *shelterPtr = &shelters[shelterCount];

    printf("\n=== ADD SHELTER ===\n");

    printf("Shelter name: ");
    scanf(" %[^\n]", (*shelterPtr).name);

    printf("Capacity: ");
    scanf("%d", &(*shelterPtr).capacity);

    printf("Current occupancy: ");
    scanf("%d", &(*shelterPtr).occupancy);

    printf("Accessibility score (0-100): ");
    scanf("%d", &(*shelterPtr).accessibility);

    printf("Structural safety score (0-100): ");
    scanf("%d", &(*shelterPtr).structuralSafety);

    printf("Medical facility available? (1 = Yes, 0 = No): ");
    scanf("%d", &(*shelterPtr).medicalFacility);

    printf("Resource availability score (0-100): ");
    scanf("%d", &(*shelterPtr).resourceAvailability);

    printf("Elevation level in meters: ");
    scanf("%d", &(*shelterPtr).elevation);

    (*shelterPtr).score = 0;
    shelterCount++;

    printf("\nShelter successfully added!\n");

}

void displayShelters() {
    if (shelterCount == 0) {
        printf("\nNo shelter data available.\n");
        return;
    }

    printf("\n=== SHELTER LIST ===\n");

    for (int i = 0; i < shelterCount; i++) {
        Shelter *shelterPtr = &shelters[i];
        int remaining = (*shelterPtr).capacity - (*shelterPtr).occupancy;

        printf("\n[%d] %s\n", i + 1, (*shelterPtr).name);
        printf("Capacity              : %d\n", (*shelterPtr).capacity);
        printf("Occupancy             : %d\n", (*shelterPtr).occupancy);
        printf("Remaining Capacity    : %d\n", remaining);
        printf("Accessibility         : %d/100\n", (*shelterPtr).accessibility);
        printf("Structural Safety     : %d/100\n", (*shelterPtr).structuralSafety);
        printf("Medical Facility      : %s\n", (*shelterPtr).medicalFacility ? "Available" : "Not Available");
        printf("Resource Availability : %d/100\n", (*shelterPtr).resourceAvailability);
        printf("Elevation             : %d m\n", (*shelterPtr).elevation);
    }
}

void selectDisasterType() {
    int choice;

    printf("\n=== SELECT DISASTER TYPE ===\n");
    printf("1. Flood\n");
    printf("2. Earthquake\n");
    printf("3. Fire\n");
    printf("4. Tornado\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 4) {
        selectedDisaster = (DisasterType) choice;
        printf("Disaster type selected successfully!\n");
    } else {
        printf("Invalid disaster type.\n");
    }
}

float getRemainingCapacityScore(Shelter *shelterPtr) {
    if ((*shelterPtr).capacity <= 0) return 0;

    int remaining = (*shelterPtr).capacity - (*shelterPtr).occupancy;
    if (remaining < 0) remaining = 0;

    return ((float) remaining / (*shelterPtr).capacity) * 100;
}

float getElevationScore(Shelter *shelterPtr) {
    if ((*shelterPtr).elevation >= 30) return 100;
    if ((*shelterPtr).elevation <= 0) return 0;

    return ((float) (*shelterPtr).elevation / 30) * 100;
}

float getElevationScore(Shelter *shelterPtr) {
    if ((*shelterPtr).elevation >= 30) return 100;
    if ((*shelterPtr).elevation <= 0) return 0;

    return ((float) (*shelterPtr).elevation / 30) * 100;
}

void calculateBestRecommendation() {
    



    const char* getStatus(float score) {
        if (score >= 80) {
            return "Recommended";
        
        } else if (score >= 60) {
            return "Safe";
        
        } else if (score >= 40) {
            return "Risky";
        
        } else {
            return "Not Recommended";
        }
    }

}

void sortSheltersByScore() {
    Shelter temp;

    for (int i = 0; i < shelterCount - 1; i++) {
        for (int j = 0; j < shelterCount - i - 1; j++) {
            if (shelters[j].score < shelters[j + 1].score) {
                temp = shelters[j];
                shelters[j] = shelters[j + 1];
                shelters[j + 1] = temp;
            }
        }
    }
}


void showShelterRanking() {
    if (shelterCount == 0) {
        printf("\nNo shelter data available.\n");
        return;
    }

    if (selectedDisaster == NONE) {
        printf("\nPlease select a disaster type first.\n");
        return;
    }

    calculateAllScores();
    sortSheltersByScore();

    printf("\n=== SHELTER RANKING ===\n");

    for (int i = 0; i < shelterCount; i++) {
        printf("\n%d. %s\n", i + 1, shelters[i].name);
        printf("Score : %.2f\n", shelters[i].score);
        printf("Status: %s\n", getStatus(shelters[i].score));
    }
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