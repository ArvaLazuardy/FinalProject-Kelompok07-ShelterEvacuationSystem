#include <stdio.h>
#include <string.h>


void addShelter() {

}

void displayShelters() {

}

void selectDisasterType() {

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