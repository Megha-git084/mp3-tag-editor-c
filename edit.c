#include "header.h"

int edit_tags(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf("ERROR : Invalid arguments for edit\n");
        return FAILURE;
    }

    char *option = argv[2];
    char *new_text = argv[3];
    char *file = argv[4];

    // Frame mapping
    char frame[5];

    if (strcmp(option, "-t") == 0)
        strcpy(frame, "TIT2");
    else if (strcmp(option, "-a") == 0)
        strcpy(frame, "TPE1");
    else if (strcmp(option, "-A") == 0)
        strcpy(frame, "TALB");
    else if (strcmp(option, "-y") == 0)
        strcpy(frame, "TYER");
    else if (strcmp(option, "-m") == 0)
        strcpy(frame, "TCON");
    else if (strcmp(option, "-c") == 0)
        strcpy(frame, "COMM");
    else
    {
        printf("ERROR : Invalid option\n");
        return FAILURE;
    }

    // Year validation
    if (strcmp(option, "-y") == 0 && strlen(new_text) != 4)
    {
        printf("ERROR : Year must be exactly 4 digits\n");
        return FAILURE;
    }

    FILE *fptr = fopen(file, "rb+");
    if (!fptr)
    {
        printf("ERROR : Unable to open file\n");
        return FAILURE;
    }

    char id[3];
    fread(id, 1, 3, fptr);

    if (strncmp(id, "ID3", 3) != 0)
    {
        printf("ERROR : No ID3 tag found\n");
        fclose(fptr);
        return FAILURE;
    }

    fseek(fptr, 7, SEEK_CUR); // skip header

    while (!feof(fptr))
    {
        char frame_id[5] = {0};

        if (fread(frame_id, 1, 4, fptr) != 4)
            break;

        unsigned char size_bytes[4];
        fread(size_bytes, 1, 4, fptr);

        int size = (size_bytes[0] << 21) |
                   (size_bytes[1] << 14) |
                   (size_bytes[2] << 7)  |
                   (size_bytes[3]);

        fseek(fptr, 2, SEEK_CUR); // skip flags

        // Check frame
        if (strcmp(frame_id, frame) == 0 ||
            (strcmp(option, "-y") == 0 && strcmp(frame_id, "TDRC") == 0))
        {
            unsigned char encoding;
            fread(&encoding, 1, 1, fptr);

            int max = size - 1;
            int len = strlen(new_text);

            if (len > max)
            {
                printf("ERROR : Data too large\n");
                fclose(fptr);
                return FAILURE;
            }

            // Write new text
            fwrite(new_text, 1, len, fptr);

            // Clear remaining old data
            for (int i = len; i < max; i++)
            {
                fputc('\0', fptr);
            }

            printf("TAG UPDATED SUCCESSFULLY\n");
            fclose(fptr);
            return SUCCESS;
        }

        // Move to next frame
        fseek(fptr, size, SEEK_CUR);
    }

    printf("ERROR : Requested frame not found\n");
    fclose(fptr);
    return FAILURE;
}