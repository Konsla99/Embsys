#include <stdio.h>
#include <stdlib.h>
#include <mpg123.h>
#include <unistd.h>
void process_mp3_file(const char* filename) {
    mpg123_handle* mh;
    unsigned char* buffer;
    size_t buffer_size;
    size_t done;
    int err;

    // Initialize mpg123 library
    if (mpg123_init() != MPG123_OK) {
        fprintf(stderr, "Unable to initialize mpg123 library\n");
        return;
    }

    // Check if the file exists and is readable
    if (access(filename, R_OK) != 0) {
        perror("Error accessing file");
        mpg123_exit();
        return;
    }

    mh = mpg123_new(NULL, &err);
    if (mh == NULL) {
        fprintf(stderr, "Unable to create mpg123 handle: %s\n", mpg123_plain_strerror(err));
        mpg123_exit();
        return;
    }

    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));
    if (buffer == NULL) {
        fprintf(stderr, "Unable to allocate buffer\n");
        mpg123_delete(mh);
        mpg123_exit();
        return;
    }

    if (mpg123_open(mh, filename) != MPG123_OK) {
        fprintf(stderr, "Unable to open MP3 file: %s\n", mpg123_strerror(mh));
        free(buffer);
        mpg123_delete(mh);
        mpg123_exit();
        return;
    }

    while ((err = mpg123_read(mh, buffer, buffer_size, &done)) == MPG123_OK) {
        printf("Decoded %zu bytes\n", done);
        // Process the decoded audio data in 'buffer'
    }

    if (err != MPG123_DONE) {
        fprintf(stderr, "Decoding error: %s\n", mpg123_strerror(mh));
    }

    free(buffer);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
}


int main() {
    int input;
    char filename[256]; // Assuming filenames are no longer than 255 characters

    while (1) {
        printf("Enter 1 to open and process an MP3 file, -1 to exit: ");
        scanf("%d", &input);

        if (input == 1) {
            printf("Enter filename: ");
            scanf("%255s", filename); // Limiting input to 255 characters for safety
            process_mp3_file(filename);
        }
        else if (input == -1) {
            printf("Exiting program.\n");
            break;
        }
    }

    return 0;
}
