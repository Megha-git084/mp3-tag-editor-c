#include "header.h"

unsigned int convert_to_int(unsigned char size[4])
{//this combines 4 bytes into single integer value
    return (size[0] << 21) |
           (size[1] << 14) |
           (size[2] << 7)  |
           (size[3]);
}


void read_text_frame(FILE *fptr, unsigned int size, const char *label)//fptr-filepointer,size-sizeof the file,label -name to print(TITLE, ARTIST)
{
    unsigned char encoding;//ID3 text frame start with 1 byte encodind info
    fread(&encoding, 1, 1, fptr);   // text encoding byte

    char *data = malloc(size);//allocates memory dynamically stores in heap
    fread(data, 1, size - 1, fptr); //size -1 because already 1 byte used for encoding
    data[size - 1] = '\0'; // converts raw bytes into c string

    printf("%-8s : %s\n", label, data);//-8s for proper alginment

    free(data);//prevention of memory leak
}

int view_tags(char *mp3_file)
{
    FILE *fptr = fopen(mp3_file, "rb");//read in binary mode
    if (!fptr)
    {
        printf("ERROR : Unable to open file %s\n", mp3_file);
        return FAILURE;
    }

    char id[3];
    fread(id, 1, 3, fptr);//read first 3 byte of file

    if (strncmp(id, "ID3", 3) != 0)//checks weather file have ID3 tag
    {
        printf("ERROR : No ID3 tag found\n");
        fclose(fptr);
        return FAILURE;
    }

    fseek(fptr, 3, SEEK_CUR);   // version + flags skip

    unsigned char tag_size_bytes[4];
    fread(tag_size_bytes, 1, 4, fptr);//read tag size
    unsigned int tag_size = convert_to_int(tag_size_bytes);

    printf("---------------------------------------------\n");
    printf(" MP3 TAG READER AND EDITOR (ID3v2)\n");
    printf("---------------------------------------------\n");

    unsigned int bytes_read = 0;//tracks how many bytes processesd

    while (bytes_read < tag_size)//loop untill entire ID3 tag is read
    {
        char frame_id[5] = {0};
        fread(frame_id, 1, 4, fptr);

        if (frame_id[0] == '\0')
            break;

        unsigned char frame_size_bytes[4];
        fread(frame_size_bytes, 1, 4, fptr);//read frame ID 
        unsigned int frame_size = convert_to_int(frame_size_bytes);

        fseek(fptr, 2, SEEK_CUR); // skip flags

        if (strcmp(frame_id, "TIT2") == 0)
            read_text_frame(fptr, frame_size, "TITLE");
        else if (strcmp(frame_id, "TPE1") == 0)
            read_text_frame(fptr, frame_size, "ARTIST");
        else if (strcmp(frame_id, "TALB") == 0)
            read_text_frame(fptr, frame_size, "ALBUM");
        else if (strcmp(frame_id, "TYER") == 0 || strcmp(frame_id, "TDRC") == 0)
            read_text_frame(fptr, frame_size, "YEAR");
        else if (strcmp(frame_id, "COMM") == 0)
            read_text_frame(fptr, frame_size, "COMMENT");
        else
            fseek(fptr, frame_size, SEEK_CUR);//skip unwanted frame data

        bytes_read += 10 + frame_size;//each frame has 10 bytes header + frame data
    }

    printf("---------------------------------------------\n");
    printf("DETAILS DISPLAYED SUCCESSFULLY\n");

    fclose(fptr);
    return SUCCESS;
}
