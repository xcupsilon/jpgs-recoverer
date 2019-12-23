#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 2) // ensure proper usage
    {
        string userInput = argv[1]; // assign userinput
        bool check;
        for (int i = 0; i < strlen(userInput); i++) // check if all characters in the second string input are all alphabetic
        {
            check = isalpha(userInput[i]);
        }
        if (check == false)
        {
            fprintf(stderr, "Usage: ./recover file\n"); // gives user correct instruction for the input
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Usage: ./recover file\n"); // gives user correct instruction for the input
        return 1;
    }

    char *input = argv[1]; // remember filename
    FILE *file = fopen(input, "r"); // open input file for reading mode
    if (file == NULL) // check if there is an error in opening the file, if so, terminate the program
    {
        fprintf(stderr, "Could not open %s.\n", input);
        return 2;
    }

    unsigned char buffer[512]; // declare an array for storage of each chunk of 512 bytes
    int number = 0; // declare the variable to record the number of JPEGs encountered
    char *filename = malloc(3 * sizeof(char)); // declare a character pointer to store the name of the file
    while (!feof(file)) // copy all jpgs in the memory card into new separate files until the end of the memory card
    {
        fread(buffer, 512, 1, file); // read into the file and store a chunk of 512 bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0) // check if it is a beginning of a jpeg
        {
            sprintf(filename, "%03i.jpg", number); // create and store the new jpeg file with its corresponding number
            number++;
            FILE *img = fopen(filename, "w"); // open the file for writing

            do // keep copying bytes chunks until reach a new jpeg file
            {
                fwrite(buffer, 512, 1, img);
                fread(buffer, 512, 1, file);
            }
            while ((buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff || (buffer[3] & 0xf0) != 0xe0) && (!feof(file)));

            fclose(img);
            fseek(file, -512, SEEK_CUR); // move the file cursor back 512 bytes for next iteration
        }
    }
    free(filename);
    return 0;
}
