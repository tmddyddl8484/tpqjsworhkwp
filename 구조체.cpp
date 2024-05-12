#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
    char name[20];  // Name (up to 20 characters)
    int id;         // Student ID
    int score1;     // Score for subject 1
    int score2;     // Score for subject 2
} Student;

int main() {

    // Saving student information to sj.txt file
    FILE *fp = fopen("sj.txt", "wb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    Student students[4] = {
        {"Kim", 20230001, 90, 85},
        {"Lee", 20230002, 85, 92},
        {"Park", 20230003, 78, 83},
        {"Choi", 20230004, 95, 88}, // Added a new student
    };

    for (int i = 0; i < 4; i++) {
        fwrite(&students[i], sizeof(Student), 1, fp);
    }

    fclose(fp);
    printf("Student information saved (sj.txt)\n");

    // Reading and calculating average scores from the file
    fp = fopen("sj.txt", "rb");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    printf("Student information and averages:\n");
    printf("===================================\n");

    float total_score1 = 0, total_score2 = 0;
    while (fread(&students[0], sizeof(Student), 1, fp)) {
        float individual_average = (students[0].score1 + students[0].score2) / 2.0;
        total_score1 += students[0].score1;
        total_score2 += students[0].score2;
        printf("Name: %s, ID: %d, Score1: %d, Score2: %d, Individual Average: %.2f\n", students[0].name, students[0].id, students[0].score1, students[0].score2, individual_average);
    }
    fclose(fp);

    float subject1_average = total_score1 / 4.0;
    float subject2_average = total_score2 / 4.0;
    printf("===================================\n");
    printf("Average scores:\n");
    printf("Subject 1: %.2f\n", subject1_average);
    printf("Subject 2: %.2f\n", subject2_average);
    return 0;
}