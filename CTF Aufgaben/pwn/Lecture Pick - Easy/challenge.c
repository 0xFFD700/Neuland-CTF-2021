#include <stdio.h>

#define FLAG "nflag{dummy-flag-for-testing}"

int main() {
    const char *flag = FLAG;
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

    printf("Courses:\n");
    for(int i = 0; i < 8; i++) {
        printf("  - %s\n", courses[i]);
    }

    printf("\n");
    printf("Pick one: ");
    fflush(stdout);

    long x = 0;
    scanf("%ld", &x);
    printf("You picked %s\n", courses[x]);

    return 0;
}
