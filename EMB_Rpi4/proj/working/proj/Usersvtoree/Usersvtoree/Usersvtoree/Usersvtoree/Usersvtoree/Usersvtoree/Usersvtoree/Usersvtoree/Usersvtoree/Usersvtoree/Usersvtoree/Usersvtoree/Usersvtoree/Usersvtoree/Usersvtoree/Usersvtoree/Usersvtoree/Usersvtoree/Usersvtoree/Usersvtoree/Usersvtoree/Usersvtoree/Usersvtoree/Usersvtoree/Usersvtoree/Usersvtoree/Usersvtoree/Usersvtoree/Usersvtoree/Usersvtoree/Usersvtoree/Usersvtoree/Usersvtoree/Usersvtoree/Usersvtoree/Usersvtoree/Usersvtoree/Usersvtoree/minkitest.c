#include <stdio.h>

int main() {
    char buffer[3];

    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("%s", buffer);
	buffer == NULL;
    }

    return 0;
}

