#include <stdio.h>
#include <string.h>


void addShelter() {

}

void displayShelters() {

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