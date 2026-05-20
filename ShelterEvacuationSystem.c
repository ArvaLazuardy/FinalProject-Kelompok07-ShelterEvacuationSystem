#include <stdio.h>
#include <string.h>

#define MAX_SHELTERS 100

// Bagian Jovan
//-----------------------------------------------------
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

//-----------------------------------------------------
// Bagian Arva
//-----------------------------------------------------
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

float calculateScore(Shelter *shelterPtr) {
    float remainingCapacity = getRemainingCapacityScore(shelterPtr);
    float medical = (*shelterPtr).medicalFacility ? 100 : 0;
    float elevationScore = getElevationScore(shelterPtr);

    switch (selectedDisaster) {
        case FLOOD:
            return (elevationScore * 0.30) +
                   ((*shelterPtr).resourceAvailability * 0.20) +
                   (remainingCapacity * 0.20) +
                   ((*shelterPtr).accessibility * 0.15) +
                   (medical * 0.10) +
                   ((*shelterPtr).structuralSafety * 0.05);

        case EARTHQUAKE:
            return ((*shelterPtr).structuralSafety * 0.35) +
                   (medical * 0.20) +
                   (remainingCapacity * 0.20) +
                   ((*shelterPtr).resourceAvailability * 0.15) +
                   ((*shelterPtr).accessibility * 0.10);

        case FIRE:
            return ((*shelterPtr).accessibility * 0.30) +
                   ((*shelterPtr).structuralSafety * 0.25) +
                   (medical * 0.20) +
                   (remainingCapacity * 0.15) +
                   ((*shelterPtr).resourceAvailability * 0.10);

        case TORNADO:
            return ((*shelterPtr).structuralSafety * 0.40) +
                   (remainingCapacity * 0.20) +
                   ((*shelterPtr).resourceAvailability * 0.15) +
                   (medical * 0.15) +
                   ((*shelterPtr).accessibility * 0.10);

        default:
            return 0;
    }
}

void calculateAllScores() {
    for (int i = 0; i < shelterCount; i++) {
        Shelter *shelterPtr = &shelters[i];
        (*shelterPtr).score = calculateScore(shelterPtr);
    }
}

void printScoreBreakdown(Shelter *shelterPtr) {
    float remainingCapacity = getRemainingCapacityScore(shelterPtr);
    float medical = (*shelterPtr).medicalFacility ? 100 : 0;
    float elevationScore = getElevationScore(shelterPtr);

    printf("\n=== SCORE BREAKDOWN ===\n");

    switch (selectedDisaster) {
        case FLOOD:
            printf("Flood Score Formula:\n");
            printf("(Elevation %.2f x 0.30) = %.2f\n", elevationScore, elevationScore * 0.30);
            printf("(Resources %d x 0.20) = %.2f\n", (*shelterPtr).resourceAvailability, (*shelterPtr).resourceAvailability * 0.20);
            printf("(Remaining Capacity %.2f x 0.20) = %.2f\n", remainingCapacity, remainingCapacity * 0.20);
            printf("(Accessibility %d x 0.15) = %.2f\n", (*shelterPtr).accessibility, (*shelterPtr).accessibility * 0.15);
            printf("(Medical Facility %.2f x 0.10) = %.2f\n", medical, medical * 0.10);
            printf("(Structural Safety %d x 0.05) = %.2f\n", (*shelterPtr).structuralSafety, (*shelterPtr).structuralSafety * 0.05);
            break;

        case EARTHQUAKE:
            printf("Earthquake Score Formula:\n");
            printf("(Structural Safety %d x 0.35) = %.2f\n", (*shelterPtr).structuralSafety, (*shelterPtr).structuralSafety * 0.35);
            printf("(Medical Facility %.2f x 0.20) = %.2f\n", medical, medical * 0.20);
            printf("(Remaining Capacity %.2f x 0.20) = %.2f\n", remainingCapacity, remainingCapacity * 0.20);
            printf("(Resources %d x 0.15) = %.2f\n", (*shelterPtr).resourceAvailability, (*shelterPtr).resourceAvailability * 0.15);
            printf("(Accessibility %d x 0.10) = %.2f\n", (*shelterPtr).accessibility, (*shelterPtr).accessibility * 0.10);
            break;

        case FIRE:
            printf("Fire Score Formula:\n");
            printf("(Accessibility %d x 0.30) = %.2f\n", (*shelterPtr).accessibility, (*shelterPtr).accessibility * 0.30);
            printf("(Structural Safety %d x 0.25) = %.2f\n", (*shelterPtr).structuralSafety, (*shelterPtr).structuralSafety * 0.25);
            printf("(Medical Facility %.2f x 0.20) = %.2f\n", medical, medical * 0.20);
            printf("(Remaining Capacity %.2f x 0.15) = %.2f\n", remainingCapacity, remainingCapacity * 0.15);
            printf("(Resources %d x 0.10) = %.2f\n", (*shelterPtr).resourceAvailability, (*shelterPtr).resourceAvailability * 0.10);
            break;

        case TORNADO:
            printf("Tornado Score Formula:\n");
            printf("(Structural Safety %d x 0.40) = %.2f\n", (*shelterPtr).structuralSafety, (*shelterPtr).structuralSafety * 0.40);
            printf("(Remaining Capacity %.2f x 0.20) = %.2f\n", remainingCapacity, remainingCapacity * 0.20);
            printf("(Resources %d x 0.15) = %.2f\n", (*shelterPtr).resourceAvailability, (*shelterPtr).resourceAvailability * 0.15);
            printf("(Medical Facility %.2f x 0.15) = %.2f\n", medical, medical * 0.15);
            printf("(Accessibility %d x 0.10) = %.2f\n", (*shelterPtr).accessibility, (*shelterPtr).accessibility * 0.10);
            break;

        default:
            printf("No disaster type selected.\n");
    }

    printf("--------------------------------\n");
    printf("Final Score = %.2f\n", (*shelterPtr).score);
}

void calculateBestRecommendation() {
    if (shelterCount == 0) {
        printf("\nNo shelter data available.\n");
        return;
    }

    if (selectedDisaster == NONE) {
        printf("\nPlease select a disaster type first.\n");
        return;
    }

    calculateAllScores();

    Shelter *bestShelter = &shelters[0];

    for (int i = 1; i < shelterCount; i++) {
        Shelter *currentShelter = &shelters[i];

        if ((*currentShelter).score > (*bestShelter).score) {
            bestShelter = currentShelter;
        }
    }

    printf("\n=== BEST SHELTER RECOMMENDATION ===\n");
    printf("Recommended Shelter: %s\n", (*bestShelter).name);
    printf("Final Score        : %.2f\n", (*bestShelter).score);

    printScoreBreakdown(bestShelter);
}

//-----------------------------------------------------
// Bagian Sentanu
//-----------------------------------------------------
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

void sortSheltersByScore() {
    Shelter temp;

    for (int i = 0; i < shelterCount - 1; i++) {
        for (int j = 0; j < shelterCount - i - 1; j++) {
            Shelter *currentShelter = &shelters[j];
            Shelter *nextShelter = &shelters[j + 1];

            if ((*currentShelter).score < (*nextShelter).score) {
                temp = *currentShelter;
                *currentShelter = *nextShelter;
                *nextShelter = temp;
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
        Shelter *shelterPtr = &shelters[i];

        printf("\n%d. %s\n", i + 1, (*shelterPtr).name);
        printf("Score : %.2f\n", (*shelterPtr).score);
        printf("Status: %s\n", getStatus((*shelterPtr).score));
    }
}

// Bagian Arva
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