//Shan Jin sjin911

#include <stdio.h>
#include <string.h>

void make_new_name(char *new_name, char *original_name);
int is_alpha(char c);
int is_digit(char c);
int is_valid_password(char *password);
void perform_XOR(char *input_filename, char *output_filename, char *password);
void print_first_five(char *filename);

int main(int argc, char *argv[]) {
    char filename[20], password[20], new_name[20];
    if (argc != 3) {
        printf("Usage: %s filename password\n", argv[0]);
    } else {
        int i = 0, j = 0;
        while (*(argv[1] + i) != '\0') {
            filename[i] = *(argv[1] + i);
            i++;
        }
        while (*(argv[2] + j) != '\0') {
            password[j] = *(argv[2] + j);
            j++;
        }
        filename[i] = '\0';
        password[j] = '\0';
        make_new_name(new_name, filename);
        if (is_valid_password(password) == 0)
        return 0;
        perform_XOR(filename, new_name, password);
        print_first_five(new_name);
    }
    return 0;
}

void make_new_name(char *new_name, char *original_name) {
    new_name[0] = 'n';
    new_name[1] = 'e';
    new_name[2] = 'w';
    new_name[3] = '-';
    int i = 0;
    while (original_name[i] != '\0') {
        new_name[4 + i] = original_name[i];
        i++;
    }
    new_name[4 + i] = '\0';
    printf("New filename = %s\n", new_name);
}

int is_alpha(char c) {
    if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
    return 1;
    else
    return 0;
}

int is_digit(char c) {
    if ('0' <= c && c <= '9')
    return 1;
    else
    return 0;
}

int is_valid_password(char *password) {
    int alpha = 0, num = 0, i = 0;
    while (password[i] != '\0') {
        if (is_alpha(password[i]))
        alpha = 1;
        else if (is_digit(password[i]))
        num = 1;
        i++;
    }
    printf("Password length = %d\n", i);
    if (i < 8) 
    printf("The password needs to have at least 8 characters.\n");
    if (alpha == 0)
    printf("The password needs to contain at least 1 alphabetical character.\n");
    if (num == 0)
    printf("The password needs to contain at least 1 digit.\n");
    return alpha && num && (i >= 8);
}

void perform_XOR(char *input_filename, char *output_filename, char *password) {
    int blocksize = 0;
    while (password[blocksize] != '\0') {
        blocksize++;
    }
    int i, numBytes;
    FILE *input_file, *output_file;
    char block[blocksize];
    input_file = fopen(input_filename, "rb");
    output_file = fopen(output_filename, "wb");
    do {
        numBytes = fread(block, 1, blocksize, input_file);
        for (i = 0; i<numBytes; i++)
            block[i] = block[i] ^ password[i];
        fwrite(block, 1, numBytes, output_file);
    } while (numBytes > 0);
    fclose(output_file);
    fclose(input_file);
}

void print_first_five(char *filename) {
    FILE *file;
    file = fopen(filename, "rb");
    unsigned char blocks[5];
    int numBytes = fread(blocks, 1, 5, file);
    for (int i = 0; i < numBytes; i++)
        printf("%x\n", blocks[i]);
    fclose(file);
}
