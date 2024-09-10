/**
* (basic description of the program or class)
*
* Completion time: 5.5 hours
*
* @author Hung-JU, Acuna
* @version Sep 9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_credits = 0;

enum Subject {
    CSE,
    EEE,
    EGR,
    SER,
};

struct CourseNode {
    enum Subject subject;
    int course_id;
    char teacher_name[1024];
    int credits_hours;
    struct CourseNode* next;
};

char menu() {
    printf("\nMenu Options:\n");
    printf("------------------------------\n");
    printf("a. Add a class\n");
    printf("d. Drop a class\n");
    printf("s. Show your classes\n");
    printf("q. Quit\n");
    printf("Total credits: %d\n", total_credits);
    printf("------------------------------\n");
    printf("Please enter a choice: ");

    char ch;
    scanf(" %c", &ch);  // ignore last \n
    return ch;
}

void course_insert(struct CourseNode** firstNode) {
    enum Subject subject;
    int course_id;
    char teacher_name[1024];
    int credits_hours;
    int input_subject;

    printf("What is the subject? (CSE=0, EEE=1, EGR=2, SER=3)\n");
    scanf("%d", &input_subject);
    printf("What is the course number? (e.g. 240)\n");
    scanf("%d", &course_id);
    printf("How many credits is the class? (e.g. 3)\n");
    scanf("%d", &credits_hours);
    getchar();
    printf("What is the name of the teacher?\n");
    fgets(teacher_name, sizeof(teacher_name), stdin);
    teacher_name[strcspn(teacher_name, "\n")] = '\0';

    struct CourseNode* course_node = (struct CourseNode*)malloc(sizeof(struct CourseNode));
    if (course_node == NULL) {
        printf("Memory allocation error\n");
        return;
    }

    if (input_subject >= 0 && input_subject <= 3) {
        course_node->subject = (enum Subject)input_subject;
    } else {
        printf("Invalid subject input.\n");
        free(course_node);
        return;
    }

    course_node->course_id = course_id;
    strcpy(course_node->teacher_name, teacher_name);
    course_node->credits_hours = credits_hours;
    course_node->next = *firstNode;
    *firstNode = course_node;

    printf("Inserted a new class!\n");
    total_credits += credits_hours;
}

void schedule_print(struct CourseNode* firstNode) {
    if (firstNode == NULL) {
        printf("Schedule is empty\n");
        return;
    }

    struct CourseNode* current_node = firstNode;
    printf("Class Schedule:\n");
    while (current_node != NULL) {
        const char* subject_str;
        switch (current_node->subject) {
            case CSE: subject_str = "CSE"; break;
            case EEE: subject_str = "EEE"; break;
            case EGR: subject_str = "EGR"; break;
            case SER: subject_str = "SER"; break;
            default: subject_str = "UNKNOWN"; break;
        }
        printf("%s %d\tCredits: %d\tTeacher: %s\n",
               subject_str,
               current_node->course_id,
               current_node->credits_hours,
               current_node->teacher_name);
        current_node = current_node->next;
    }
    printf("------END OF SCHEDULE-------\n");
}

void course_drop(struct CourseNode** firstNode) {
    if (*firstNode == NULL) {
        printf("Schedule is empty\n");
        return;
    }

    int drop_subject;
    int drop_course_id;
    printf("What is the subject you want to drop? (CSE=0, EEE=1, EGR=2, SER=3)\n");
    scanf("%d", &drop_subject);
    printf("What is the course number you want to drop? (e.g. 240)\n");
    scanf("%d", &drop_course_id);

    struct CourseNode *current_node = *firstNode;
    struct CourseNode *previous_node = NULL;

    while (current_node != NULL) {
        if (current_node->subject == drop_subject && current_node->course_id == drop_course_id) {
            if (previous_node == NULL) {
                *firstNode = current_node->next;
            } else {
                previous_node->next = current_node->next;
            }
            total_credits -= current_node->credits_hours;
            printf("Removed class: %d %d\n", current_node->subject, current_node->course_id);
            free(current_node);
            return;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }

    printf("Class not found.\n");
}

void schedule_load(struct CourseNode** firstNode, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);  // skip title line
    while (fgets(buffer, sizeof(buffer), file)) {
        struct CourseNode* new_node = (struct CourseNode*)malloc(sizeof(struct CourseNode));
        if (new_node == NULL) {
            printf("Memory allocation error\n");
            fclose(file);
            return;
        }

        int subject_int;
        int course_id, credits_hours;
        char teacher_name[1024];

        // Read the enum as an integer
        sscanf(buffer, "%d,%d,%d,%[^\n]", &subject_int, &course_id, &credits_hours, teacher_name);

        new_node->subject = (enum Subject)subject_int;  // Assign the integer to enum
        new_node->course_id = course_id;
        new_node->credits_hours = credits_hours;
        strcpy(new_node->teacher_name, teacher_name);
        new_node->next = *firstNode;
        *firstNode = new_node;

        total_credits += credits_hours;
    }

    fclose(file);
    printf("Schedule loaded from file: %s\n", filename);
}

void schedule_save(struct CourseNode* firstNode, const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    fprintf(file, "Subject,CourseID,Credits,TeacherName\n");

    struct CourseNode* current_node = firstNode;
    while (current_node != NULL) {
        fprintf(file, "%d,%d,%d,%s\n",
            current_node->subject,  // Save the enum as a number
            current_node->course_id,
            current_node->credits_hours,
            current_node->teacher_name);

        current_node = current_node->next;
    }
    fclose(file);
    printf("Schedule written to file: %s\n", file_name);
}

int main(void) {
    struct CourseNode* course_node = NULL;
    const char* save_file = "data.txt";
    schedule_load(&course_node, save_file);

    while (1) {
        const char choice = menu();
        if (choice == 'a') {
            course_insert(&course_node);
        } else if (choice == 'd') {
            course_drop(&course_node);
        } else if (choice == 's') {
            schedule_print(course_node);
        } else if (choice == 'q') {
            break;
        } else {
            printf("Input wrong choice, please enter a valid character.\n");
        }
    }
    schedule_save(course_node, save_file);

    struct CourseNode* current_node = course_node;
    while (current_node != NULL) {
        struct CourseNode* temp = current_node;
        current_node = current_node->next;
        free(temp);
    }

    printf("Goodbye!\n");
    return 0;
}