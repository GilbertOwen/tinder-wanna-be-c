#include <stdlib.h>
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

enum JenisKelamin
{
    pria,
    wanita
};

enum LoveLanguage
{
    WordOfAffirmation,
    QualityTime,
    PhysicalTouch,
    ActOfService,
    ReceivingGIft
};

enum PersonalityType
{
    Introverted,
    Extroverted,
    Ambivert
};

enum Hobby
{
    CreativeArt,
    Technology,
    Gaming,
    Sport,
    Outdoor
};

enum RelationShipGoal
{
    LongTerm,
    Casual,
    Undecided
};

enum Lifestyle
{
    MorningPerson,
    NightOwl,
    Flexible
};

typedef struct
{
    int jarak_umur[2];
    enum LoveLanguage tipeLoveLanguage[5];
    enum PersonalityType tipePersonality[3];
    enum Hobby tipeHobby[5];
    enum RelationShipGoal tipeRelationShip[3];
    enum Lifestyle tipeLifestyle[3];
} Criteria;

typedef struct
{
    char nama[100];
    enum JenisKelamin jenis_kelamin;
    Criteria kriteria;
    int umur;
} User;

// Function Prototype

void clear_screen();
void askUser(User *p);
void editUserCriteria(User *p);
void showCandidates(User *p);
void generateMenu(User *p);

// int generateOtherUserWithPreference(enum TipePreferensi preference[])
// {
//     for (int i = 0;)
// }

int main()
{
    User *player = (User *)malloc(sizeof(User));
    askUser(player);
    generateMenu(player);
    return 0;
}

void clear_screen()
{
    printf("%s", CLEAR_SCREEN_REGEX);
}

void askUser(User *p)
{
    clear_screen();
    printLogo();
    printf("Masukkan nama untuk melanjutkan : ");
    scanf("%[^\n]", p->nama);
    getchar();
    clear_screen();
    printLogo();
    printf("Masukkan umur untuk melanjutkan : ");
    scanf("%d", &p->umur);
    getchar();
    clear_screen();
    int validated = 0;
    do
    {
        clear_screen();
        printLogo();
        if (validated == 0)
        {
            printf("Please input the right choice ((P)ria/(W)anita)\n\n");
        }
        char temp;
        printf("Masukkan jenis kelamin untuk melanjutkan ((P)ria/(W)anita): ");
        scanf("%c", &temp);
        if (tolower(temp) == 'p' || tolower(temp) == 'w')
        {
            p->jenis_kelamin = tolower(temp) == 'p' ? pria : wanita;
            validated = 1;
            break;
        }
        else
        {
            continue;
        }
    } while (validated == 0);
}

void showProfile(User *p)
{
    clear_screen();
    printLogo();
    printf("User's Profile\n");
    printf("Name : %s\n", p->nama);
    printf("Age : %d\n", p->umur);
    printf("Gender : %s\n\n", p->jenis_kelamin == pria ? "Pria" : "Wanita");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void editUserCriteria(User *p)
{
}

void showCandidates(User *p)
{
}

void generateMenu(User *p)
{
    int menu;
    do
    {
        clear_screen();
        printLogo();
        printf("Menu of Cinder :\n");
        printf("1. Show Profile\n");
        printf("2. Change Criteria\n");
        printf("3. Show Candidates\n");
        printf("4. Exit\n");
        printf("Your choice : ");
        scanf("%d", &menu);
        getchar();

        switch (menu)
        {
        case 1:
            showProfile(p);
            break;
        case 2:
            editUserCriteria(p);
            break;
        case 3:
            showCandidates(p);
            break;
        case 4:
            break;
        default:
            break;
        }
    } while (menu != 4);
}
