#include <stdio.h>
#include <ctype.h>

#define CLEAR_SCREEN_REGEX "\e[1;1H\e[2J"

void printLogo()
{
    const char *LOGO = "    ___________   ______  __________     \n"
                      "   / ____/  _/ | / / __ \\/ ____/ __ \\  \n"
                      "  / /    / //  |/ / / / / __/ / /_/ /    \n"
                      " / /____/ // /|  / /_/ / /___/ _, _/     \n"
                      " \\____/___/_/ |_/_____/_____/_/ |_|     \n";

    printf("%s\n", LOGO);
    puts("Cinder, a Tinder-like dating app\n");
}

void clearScreen()
{
    printf(CLEAR_SCREEN_REGEX);
}

int main() 
{
    printLogo();
    char userChoice;

    do 
    {
        puts("What do you want to do?\n");
        puts("(F)ind partner\n"
             "(E)xit");

        printf("Enter your choice: ");
        scanf(" %c", &userChoice);
        switch (tolower(userChoice)) {
        case 'f':
            clearScreen();
            break;
        case 'e':
            puts("Thanks for using our app!");
            return 0;
        default:
            clearScreen();
            puts("Invalid choice!");
        }
    } while (tolower(userChoice) != 'e');

    return 0;
}