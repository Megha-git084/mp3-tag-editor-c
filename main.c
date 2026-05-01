#include "header.h"  // gives access to function declarations

int main(int argc, char *argv[])//argc stores the number of command line arguments,argv stores the actual arguments as strings
{
    
    if (argc < 2)
    {
        printf("ERROR : INVALID ARGUMENTS\n");
        print_help();
        return FAILURE;
    }

    // ask help option 
    if (strcmp(argv[1], "--help") == 0)
    {
        print_help();
        return SUCCESS;
    }

    // view  
    if (strcmp(argv[1], "-v") == 0)
    {
        if (argc != 3) // because  view operation needs exactly 3 arguments that is ./a.out, -v,sample.mp3
        {
            printf("ERROR : Invalid arguments for view\n");
            return FAILURE;
        }
        return view_tags(argv[2]);//argv[0] - ./a.out, argv[1] - v, argv[2] - sample.mp3
    }

    // edit 
    if (strcmp(argv[1], "-e") == 0)
    {
        return edit_tags(argc, argv);
    }
    printf("ERROR : Unknown option\n");
    print_help();
    return FAILURE;
}
void print_help(void)
{
    printf("-------------------------------- HELP MENU --------------------------------\n");
    printf("1. -v mp3file              : View MP3 tag contents\n");
    printf("2. -e -t text mp3file      : Edit song title\n");
    printf("3. -e -a text mp3file      : Edit artist name\n");
    printf("4. -e -A text mp3file      : Edit album name\n");
    printf("5. -e -y text mp3file      : Edit year\n");
    printf("6. -e -m text mp3file      : Edit music\n");
    printf("7. -e -c text mp3file      : Edit comment\n");
    printf("--------------------------------------------------------------------------\n");
}
