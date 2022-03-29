#include <stdio.h>
#include <string.h>

// for security reasons we moved the flag into flag.txt 
// #define FLAG "nflag{dummy-flag-for-testing}"

const char *courses[8] = {
    "Maths 1",
    "Maths 2",
    "Object Oriented Programming",
    "Computer Vision",
    "IT-Security",
    "Forensics",
    "Software Engineering",
    "Theoretical Computer Science",
};

int main() {
    printf("Courses [%p]:\n", printf);
    for(int i = 0; i < 8; i++) {
        printf("  - %s\n", courses[i]);
    }

    printf("\n");
    printf("Pick a name: ");
    fflush(stdout);

    char name[32];
    scanf("%s", name);

    printf("You picked: %s, course number: ", name);
    for(int i = 0; i < 8; i++) {
        if(strcmp(courses[i], name) == 0) {
            printf("%d\n", i);
        }
    }

    return 0;
}
