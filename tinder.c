#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define CLEAR_SCREEN_REGEX "\e[1;1H\e[2J"
#define INVALID_PREFERENCES -1
#define USERDATA "userdata.dat"

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

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

void getbuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void clearScreen()
{
    printf(CLEAR_SCREEN_REGEX);
}

void header()
{
    clearScreen();
    printLogo();
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
    enum RelationShipGoal tipeRelationShipGoal[3];
    enum Lifestyle tipeLifestyle[3];
} Criteria;

typedef struct
{
    char username[100];
    char password[100];
    char nama[100];
    enum JenisKelamin jenis_kelamin;
    Criteria kriteria;
    int umur;
    int isAdmin;
} User;

int candidateIndex = 0;

void generateRandomUser(User *user, int index)
{
    const char *names[] = {"Alex", "Jordan", "Taylor", "Morgan", "Jamie", "Sam", "Chris", "Casey", "Skyler", "Drew",
                           "Riley", "Quinn", "Harper", "Cameron", "Reese", "Toby", "Sydney", "Blake", "Avery", "Peyton", "Robin", "Devon", "Dylan", "Kai", "Toni", "Kendall", "Jules", "Rowan"};
    size_t names_count = sizeof(names) / sizeof(names[0]);

    sprintf(user->username, "user%d", index);
    strcpy(user->password, "password");
    strcpy(user->nama, names[rand() % names_count]);
    user->jenis_kelamin = rand() % 2;
    user->umur = rand() % 15 + 18; // Age between 18 and 32
    user->isAdmin = 0;

    // Generate criteria
    user->kriteria.jarak_umur[0] = rand() % 10 + 18;                           // Minimum age preference
    user->kriteria.jarak_umur[1] = user->kriteria.jarak_umur[0] + rand() % 10; // Maximum age preference

    for (int i = 0; i < 5; i++)
    {
        user->kriteria.tipeLoveLanguage[i] = (i < 3) ? rand() % 5 : INVALID_PREFERENCES;
        user->kriteria.tipeHobby[i] = (i < 3) ? rand() % 5 : INVALID_PREFERENCES;
    }

    for (int i = 0; i < 3; i++)
    {
        user->kriteria.tipePersonality[i] = (i < 2) ? rand() % 3 : INVALID_PREFERENCES;
        user->kriteria.tipeRelationShipGoal[i] = (i < 2) ? rand() % 3 : INVALID_PREFERENCES;
        user->kriteria.tipeLifestyle[i] = (i < 2) ? rand() % 3 : INVALID_PREFERENCES;
    }
}

User otherUsers[100];

// Function Prototype

void clear_screen();
const char *getLoveLanguageString(enum LoveLanguage lang);
const char *getPersonalityTypeString(enum PersonalityType type);
const char *getHobbyString(enum Hobby hobby);
const char *getRelationShipGoalString(enum RelationShipGoal goal);
const char *getLifestyleString(enum Lifestyle lifestyle);
void resetCriteria(User *p);
void inputName(User *p);
void inputAge(User *p);
void inputGender(User *p);
void loveLanguageValidation(User *p, enum LoveLanguage temp);
void addLoveLanguagePreferences(User *p);
void personalityValidation(User *p, enum PersonalityType temp);
void addPersonalityPreferences(User *p);
void hobbyValidation(User *p, enum Hobby temp);
void addHobbyPreferences(User *p);
void relationshipGoalValidation(User *p, enum RelationShipGoal temp);
void addRelationshipGoalPreferences(User *p);
void lifeStyleValidation(User *p, enum Lifestyle temp);
void addLifeStylePreferences(User *p);
void addAgeRange(User *p);
void askUser(User *p);
void showProfile(User *p);
void resetPreferences(User *p, char choice);
void editUserCriteria(User *p, FILE *fp);
void sortByAge(User *users[100], char by);
// void sortByName(User *users[100], char by);
void showCandidates(User *p);
void generateMenu(User *p, FILE *fp);
void adminMenu(User *p, FILE *fp);
void loginPage(User *user, FILE *fp);
void registerUser(User *user, FILE *fp);
void loginUser(User *user, FILE *fp);

int main()
{
    for (int i = 0; i < 100; i++)
    {
        generateRandomUser(&otherUsers[i], i + 1);
    }

    // Check for user data file
    FILE *userDataFile = fopen(USERDATA, "ab+");
    if (userDataFile == NULL)
    {
        FILE *tempFile = fopen(USERDATA, "wb");
        if (tempFile != NULL)
        {
            fclose(tempFile);
        }
        userDataFile = fopen(USERDATA, "ab+");
    }

    User *player = (User *)malloc(sizeof(User));

    resetCriteria(player);
    header();
    loginPage(player, userDataFile);
    if (player->isAdmin == 1)
    {
        adminMenu(player, userDataFile);
        return 0;
    }
    generateMenu(player, userDataFile);
    free(player);
    return 0;
}

void clear_screen()
{
    printf("%s", CLEAR_SCREEN_REGEX);
}

// First phase component

void resetCriteria(User *p)
{
    for (int i = 0; i < 5; i++)
    {
        p->kriteria.tipeLoveLanguage[i] = -1;
    }
    for (int i = 0; i < 3; i++)
    {
        p->kriteria.tipePersonality[i] = -1;
    }
    for (int i = 0; i < 5; i++)
    {
        p->kriteria.tipeHobby[i] = -1;
    }
    for (int i = 0; i < 3; i++)
    {
        p->kriteria.tipeRelationShipGoal[i] = -1;
    }
    for (int i = 0; i < 3; i++)
    {
        p->kriteria.tipeLifestyle[i] = -1;
    }
}

const char *getLoveLanguageString(enum LoveLanguage lang)
{
    switch (lang)
    {
    case WordOfAffirmation:
        return "Word Of Affirmation";
    case QualityTime:
        return "Quality Time";
    case PhysicalTouch:
        return "Physical Touch";
    case ActOfService:
        return "Act Of Service";
    case ReceivingGIft:
        return "Receiving Gift";
    default:
        return "Unknown";
    }
}

const char *getPersonalityTypeString(enum PersonalityType type)
{
    switch (type)
    {
    case Introverted:
        return "Introverted";
    case Extroverted:
        return "Extroverted";
    case Ambivert:
        return "Ambivert";
    default:
        return "Unknown";
    }
}

const char *getHobbyString(enum Hobby hobby)
{
    switch (hobby)
    {
    case CreativeArt:
        return "Creative Art";
    case Technology:
        return "Technology";
    case Gaming:
        return "Gaming";
    case Sport:
        return "Sport";
    case Outdoor:
        return "Outdoor";
    default:
        return "Unknown";
    }
}

const char *getRelationShipGoalString(enum RelationShipGoal goal)
{
    switch (goal)
    {
    case LongTerm:
        return "Long Term";
    case Casual:
        return "Casual";
    case Undecided:
        return "Undecided";
    default:
        return "Unknown";
    }
}

const char *getLifestyleString(enum Lifestyle lifestyle)
{
    switch (lifestyle)
    {
    case MorningPerson:
        return "Morning Person";
    case NightOwl:
        return "Night Owl";
    case Flexible:
        return "Flexible";
    default:
        return "Unknown";
    }
}

void inputName(User *p)
{
    int validated = 0;
    do
    {
        clear_screen();
        printLogo();
        printf("Masukkan nama untuk melanjutkan : ");
        scanf("%[^\n]", p->nama);
        getchar();
        validated = 1;
    } while (validated == 0);
}

void inputAge(User *p)
{
    int validated = 0;
    do
    {
        clear_screen();
        printLogo();
        if (validated == 0)
        {
            printf("Please input the right age\n\n");
        }
        printf("Masukkan umur untuk melanjutkan : ");
        scanf("%d", &p->umur);
        if (p->umur > 0)
        {
            validated = 1;
            break;
        }
        else
        {
            continue;
        }
    } while (validated == 0);
    clear_screen();
}

void inputGender(User *p)
{
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

void loveLanguageValidation(User *p, enum LoveLanguage temp)
{
    int validated = 1;
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeLoveLanguage[i] == temp)
        {
            validated = 0;
        }
    }
    if (validated == 1)
    {
        printf("Successfully added!\n");
        for (int i = 0; i < 5; i++)
        {
            if (p->kriteria.tipeLoveLanguage[i] == -1)
            {
                p->kriteria.tipeLoveLanguage[i] = temp;
                break;
            }
        }
    }
    else
    {
        printf("Failed to add love language preference, seems like you've already added it\n");
    }
}

void addLoveLanguagePreferences(User *p)
{
    int addMore = 0;
    do
    {
        addMore = 0;

        int validated = 0;
        do
        {
            clear_screen();
            printLogo();
            printf("Your Chosen Love Languages: ");
            for (int i = 0; i < 5; i++)
            {
                if (p->kriteria.tipeLoveLanguage[i] != -1)
                {
                    printf("%s, ", getLoveLanguageString(p->kriteria.tipeLoveLanguage[i]));
                }
            }
            printf("\n\n\n");
            if (validated == 0)
            {
                printf("Please input the right choice that is given by the question\n\n");
            }
            int temp;
            printf("Love Language Preferences: \n");
            printf("1. Word of Affirmation\n");
            printf("2. Quality Time\n");
            printf("3. Physical Touch\n");
            printf("4. Act of Service\n");
            printf("5. Receiving Gift\n");
            printf("Masukkan preferensi untuk Love Language-mu: \n");
            scanf("%d", &temp);
            getbuffer();

            switch (temp)
            {
            case 1:
                loveLanguageValidation(p, WordOfAffirmation);
                validated = 1;
                break;
            case 2:
                loveLanguageValidation(p, QualityTime);
                validated = 1;
                break;

            case 3:
                loveLanguageValidation(p, PhysicalTouch);
                validated = 1;
                break;

            case 4:
                loveLanguageValidation(p, ActOfService);
                validated = 1;
                break;

            case 5:
                loveLanguageValidation(p, ReceivingGIft);
                validated = 1;
                break;
            default:
                validated = 0;
                continue;
            }
        } while (validated == 0);

        printf("Apakah ingin menambahkan love language lagi? ((Y)es/(N)o): ");
        if (tolower(getchar()) == 'y')
        {
            addMore = 1;
        }
        getchar();
    } while (addMore == 1);
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void personalityValidation(User *p, enum PersonalityType temp)
{
    int validated = 1;
    for (int i = 0; i < 3; i++)
    {
        if (p->kriteria.tipePersonality[i] == temp)
        {
            validated = 0;
        }
    }
    if (validated == 1)
    {
        printf("Successfully added!\n");
        for (int i = 0; i < 3; i++)
        {
            if (p->kriteria.tipePersonality[i] == -1)
            {
                p->kriteria.tipePersonality[i] = temp;
                break;
            }
        }
    }
    else
    {
        printf("Failed to add personality preference, seems like you've already added it\n");
    }
}

void addPersonalityPreferences(User *p)
{
    int addMore = 0;
    do
    {
        addMore = 0;
        int validated = 0;
        do
        {
            clear_screen();
            printLogo();
            printf("Your Chosen Personality Types: ");
            for (int i = 0; i < 3; i++)
            {
                if (p->kriteria.tipePersonality[i] != -1)
                {
                    printf("%s, ", getPersonalityTypeString(p->kriteria.tipePersonality[i]));
                }
            }
            printf("\n\n\n");
            if (validated == 0)
            {
                printf("Please input the right choice that is given by the question\n\n");
            }
            int temp;
            printf("Personality Preferences: \n");
            printf("1. Introvert\n");
            printf("2. Extrovert\n");
            printf("3. Ambivert\n");
            printf("Masukkan preferensi untuk Personality-mu: \n");
            scanf("%d", &temp);
            getbuffer();

            switch (temp)
            {
            case 1:
                personalityValidation(p, Introverted);
                validated = 1;
                break;
            case 2:
                personalityValidation(p, Extroverted);
                validated = 1;
                break;

            case 3:
                personalityValidation(p, Ambivert);
                validated = 1;
                break;
            default:
                validated = 0;
                continue;
            }
        } while (validated == 0);

        printf("Apakah ingin menambahkan personality lagi? ((Y)es/(N)o): ");
        if (tolower(getchar()) == 'y')
        {
            addMore = 1;
        }
        getchar();
    } while (addMore == 1);
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void hobbyValidation(User *p, enum Hobby temp)
{
    int validated = 1;
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeHobby[i] == temp)
        {
            validated = 0;
        }
    }
    if (validated == 1)
    {
        printf("Successfully added!\n");
        for (int i = 0; i < 5; i++)
        {
            if (p->kriteria.tipeHobby[i] == -1)
            {
                p->kriteria.tipeHobby[i] = temp;
                break;
            }
        }
    }
    else
    {
        printf("Failed to add hobby preference, seems like you've already added it\n");
    }
}

void addHobbyPreferences(User *p)
{
    int addMore = 0;
    do
    {
        addMore = 0;
        int validated = 0;
        do
        {
            clear_screen();
            printLogo();
            printf("Your Chosen Hobbies: ");
            for (int i = 0; i < 5; i++)
            {
                if (p->kriteria.tipeHobby[i] != -1)
                {
                    printf("%s, ", getHobbyString(p->kriteria.tipeHobby[i]));
                }
            }
            printf("\n\n\n");
            if (validated == 0)
            {
                printf("Please input the right choice that is given by the question\n\n");
            }
            int temp;
            printf("Hobby Preferences: \n");
            printf("1. Creative Art\n");
            printf("2. Technology\n");
            printf("3. Gaming\n");
            printf("4. Sport\n");
            printf("5. Outdoor\n");
            printf("Masukkan preferensi untuk Hobby-mu: \n");
            scanf("%d", &temp);
            getbuffer();

            switch (temp)
            {
            case 1:
                hobbyValidation(p, CreativeArt);
                validated = 1;
                break;
            case 2:
                hobbyValidation(p, Technology);
                validated = 1;
                break;

            case 3:
                hobbyValidation(p, Gaming);
                validated = 1;
                break;
            case 4:
                hobbyValidation(p, Sport);
                validated = 1;
                break;
            case 5:
                hobbyValidation(p, Outdoor);
                validated = 1;
                break;
            default:
                validated = 0;
                continue;
            }
        } while (validated == 0);

        printf("Apakah ingin menambahkan hobby lagi? ((Y)es/(N)o): ");
        if (tolower(getchar()) == 'y')
        {
            addMore = 1;
        }
        getchar();
    } while (addMore == 1);
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void lifeStyleValidation(User *p, enum Lifestyle temp)
{
    int validated = 1;
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeLifestyle[i] == temp)
        {
            validated = 0;
        }
    }
    if (validated == 1)
    {
        printf("Successfully added!\n");
        for (int i = 0; i < 5; i++)
        {
            if (p->kriteria.tipeLifestyle[i] == -1)
            {
                p->kriteria.tipeLifestyle[i] = temp;
                break;
            }
        }
    }
    else
    {
        printf("Failed to add lifestyle preference, seems like you've already added it\n");
    }
}

void addLifeStylePreferences(User *p)
{
    int addMore = 0;
    do
    {
        addMore = 0;
        int validated = 0;
        do
        {
            clear_screen();
            printLogo();
            printf("Your Chosen Lifestyle: ");
            for (int i = 0; i < 5; i++)
            {
                if (p->kriteria.tipeLifestyle[i] != -1)
                {
                    printf("%s, ", getLifestyleString(p->kriteria.tipeLifestyle[i]));
                }
            }
            printf("\n\n\n");
            if (validated == 0)
            {
                printf("Please input the right choice that is given by the question\n\n");
            }
            int temp;
            printf("Lifestyle Preferences: \n");
            printf("1. Morning Person\n");
            printf("2. Night Owl\n");
            printf("3. Flexible\n");
            printf("Masukkan preferensi untuk Lifestyle-mu: \n");
            scanf("%d", &temp);
            getbuffer();

            switch (temp)
            {
            case 1:
                lifeStyleValidation(p, MorningPerson);
                validated = 1;
                break;
            case 2:
                lifeStyleValidation(p, NightOwl);
                validated = 1;
                break;

            case 3:
                lifeStyleValidation(p, Flexible);
                validated = 1;
                break;
            default:
                validated = 0;
                continue;
            }
        } while (validated == 0);

        printf("Apakah ingin menambahkan lifestyle lagi? ((Y)es/(N)o): ");
        if (tolower(getchar()) == 'y')
        {
            addMore = 1;
        }
        getchar();
    } while (addMore == 1);
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void relationshipGoalValidation(User *p, enum RelationShipGoal temp)
{
    int validated = 1;
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeRelationShipGoal[i] == temp)
        {
            validated = 0;
        }
    }
    if (validated == 1)
    {
        printf("Successfully added!\n");
        for (int i = 0; i < 5; i++)
        {
            if (p->kriteria.tipeRelationShipGoal[i] == -1)
            {
                p->kriteria.tipeRelationShipGoal[i] = temp;
                break;
            }
        }
    }
    else
    {
        printf("Failed to add relationship preference, seems like you've already added it\n");
    }
}

void addRelationshipGoalPreferences(User *p)
{
    int addMore = 0;
    do
    {
        addMore = 0;
        int validated = 0;
        do
        {
            clear_screen();
            printLogo();
            printf("Your Chosen Relationship Goal: ");
            for (int i = 0; i < 5; i++)
            {
                if (p->kriteria.tipeRelationShipGoal[i] != -1)
                {
                    printf("%s, ", getRelationShipGoalString(p->kriteria.tipeRelationShipGoal[i]));
                }
            }
            printf("\n\n\n");
            if (validated == 0)
            {
                printf("Please input the right choice that is given by the question\n\n");
            }
            int temp;
            printf("Relationship Goal Preferences: \n");
            printf("1. Long Term Relationship\n");
            printf("2. Casual Relationship\n");
            printf("3. Undecided\n");
            printf("Masukkan preferensi untuk Relationship Goal-mu: \n");
            scanf("%d", &temp);
            getbuffer();

            switch (temp)
            {
            case 1:
                relationshipGoalValidation(p, LongTerm);
                validated = 1;
                break;
            case 2:
                relationshipGoalValidation(p, Casual);
                validated = 1;
                break;

            case 3:
                relationshipGoalValidation(p, Undecided);
                validated = 1;
                break;
            default:
                validated = 0;
                continue;
            }
        } while (validated == 0);

        printf("Apakah ingin menambahkan relationship goal lagi? ((Y)es/(N)o): ");
        if (tolower(getchar()) == 'y')
        {
            addMore = 1;
        }
        getchar();
    } while (addMore == 1);
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void addAgeRange(User *p)
{
    int validated = 0;
    do
    {
        clear_screen();
        printLogo();
        int input[2];
        printf("Masukkan range umur untuk pasangan ideal anda (contoh: 20 30): ");
        scanf("%d %d", &input[0], &input[1]);
        getbuffer();
        if (input[1] < input[0])
        {
            printf("Umur kedua tidak boleh lebih kecil dari umur pertama\n");
        }
        else
        {
            p->kriteria.jarak_umur[0] = input[0];
            p->kriteria.jarak_umur[1] = input[1];
            validated = 1;
            break;
        }
    } while (validated == 0);
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

// First phase component end

// First phase begin

void askUser(User *p)
{
    inputName(p);
    inputAge(p);
    inputGender(p);
    addLoveLanguagePreferences(p);
    addAgeRange(p);
    addPersonalityPreferences(p);
    addLifeStylePreferences(p);
    addHobbyPreferences(p);
    addRelationshipGoalPreferences(p);
    clear_screen();
}

// First phase end

// Menu

void showProfile(User *p)
{
    clear_screen();
    printLogo();
    printf("User's Profile\n");
    printf("Name : %s\n", p->nama);
    printf("Age : %d\n", p->umur);
    printf("Gender : %s\n\n", p->jenis_kelamin == pria ? "Pria" : "Wanita");
    printf("Your Chosen Love Languages: ");
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeLoveLanguage[i] != -1)
        {
            printf("%s, ", getLoveLanguageString(p->kriteria.tipeLoveLanguage[i]));
        }
    }
    printf("\n\n");
    printf("Your Chosen Age Range: %d - %d", p->kriteria.jarak_umur[0], p->kriteria.jarak_umur[1]);
    printf("\n\n");
    printf("Your Chosen Personality Types: ");
    for (int i = 0; i < 3; i++)
    {
        if (p->kriteria.tipePersonality[i] != -1)
        {
            printf("%s, ", getPersonalityTypeString(p->kriteria.tipePersonality[i]));
        }
    }
    printf("\n\n");
    printf("Your Chosen Lifestyle: ");
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeLifestyle[i] != -1)
        {
            printf("%s, ", getLifestyleString(p->kriteria.tipeLifestyle[i]));
        }
    }
    printf("\n\n");
    printf("Your Chosen Hobbies: ");
    for (int i = 0; i < 5; i++)
    {
        if (p->kriteria.tipeHobby[i] != -1)
        {
            printf("%s, ", getHobbyString(p->kriteria.tipeHobby[i]));
        }
    }
    printf("\n\n");
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}
void resetPreferences(User *p, char choice)
{
    switch (tolower(choice))
    {
    case 'l':
        for (int i = 0; i < 5; i++)
        {
            p->kriteria.tipeLoveLanguage[i] = -1;
        }
        break;
    case 'p':
        for (int i = 0; i < 3; i++)
        {
            p->kriteria.tipePersonality[i] = -1;
        }
        break;
    case 'h':
        for (int i = 0; i < 5; i++)
        {
            p->kriteria.tipeHobby[i] = -1;
        }
        break;
    case 'r':
        for (int i = 0; i < 3; i++)
        {
            p->kriteria.tipeRelationShipGoal[i] = -1;
        }
        break;
    case 's':
        for (int i = 0; i < 5; i++)
        {
            p->kriteria.tipeLifestyle[i] = -1;
        }
        break;
    default:
        break;
    }
}

void editUserCriteria(User *p, FILE *fp)
{
    int menu = 0;
    do
    {
        clear_screen();
        printLogo();
        printf("Edit User Criteria and Information\n");
        printf("1. Reset Love Language Preferences\n");
        printf("2. Reset Personality Preferences\n");
        printf("3. Reset Hobby Preferences\n");
        printf("4. Reset Relationship Goal Preferences\n");
        printf("5. Reset Lifestyle Preferences\n");
        printf("6. Reset Age Range Preferences\n");
        printf("7. Reset All Preferences\n");
        printf("8. Back\n");
        printf("Your choice : ");
        scanf("%d", &menu);
        getchar();
        switch (menu)
        {
        case 1:
            resetPreferences(p, 'l');
            addLoveLanguagePreferences(p);
            break;
        case 2:
            resetPreferences(p, 'p');
            addPersonalityPreferences(p);
            break;
        case 3:
            resetPreferences(p, 'h');
            addHobbyPreferences(p);
            break;
        case 4:
            resetPreferences(p, 'r');
            addRelationshipGoalPreferences(p);
            break;
        case 5:
            resetPreferences(p, 's');
            addLifeStylePreferences(p);
            break;
        case 6:
            addAgeRange(p);
            break;
        case 7:
            // Reset all the criteria from user
            resetPreferences(p, 'l');
            resetPreferences(p, 'p');
            resetPreferences(p, 'h');
            resetPreferences(p, 'r');
            resetPreferences(p, 's');
            // Then add all the preferences by the use  r input
            addLoveLanguagePreferences(p);
            addAgeRange(p);
            addPersonalityPreferences(p);
            addLifeStylePreferences(p);
            addHobbyPreferences(p);
            addRelationshipGoalPreferences(p);
            clear_screen();
            addAgeRange(p);
            break;
        case 8:
            break;
        default:
            break;
        }
    } while (menu != 8);
    User *users = (User *)malloc(40 * sizeof(User));
    User newUsers[40];
    int count = getUsers(fp, users);
    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].username, p->username) == 0)
        {
            newUsers[i] = *p;
        }
        else
        {
            newUsers[i] = users[i];
        }
    }
    freopen(USERDATA, "wb+", fp);
    for (int i = 0; i < count; i++)
    {
        fwrite(&newUsers[i], sizeof(User), 1, fp);
    }
    freopen(USERDATA, "ab+", fp);
    free(users);
    printf("Preferensi User %s berhasil diubah\n", p->username);
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
}

void getCandidates(User *p, User *new[100])
{
    int count = 0;
    for (int i = 0; i < 100; i++)
    {
        int validatedPersonality = 0, validatedRelationShipGoal = 0, validateGender = 0, validateAgePreference = 0, validateLifestylePreference = 0;
        for (int j = 0; j < 3; j++)
        {
            if (p->kriteria.tipePersonality[j] != -1)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (otherUsers[i].kriteria.tipePersonality[k] != -1)
                    {
                        if (p->kriteria.tipePersonality[j] == otherUsers[i].kriteria.tipePersonality[k])
                        {
                            validatedPersonality = 1;
                        }
                    }
                }
            }
        }
        for (int j = 0; j < 3; j++)
        {
            if (p->kriteria.tipeRelationShipGoal[j] != -1)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (otherUsers[i].kriteria.tipeRelationShipGoal[k] != -1)
                    {
                        if (p->kriteria.tipeRelationShipGoal[j] == otherUsers[i].kriteria.tipeRelationShipGoal[k])
                        {
                            validatedRelationShipGoal = 1;
                        }
                    }
                }
            }
            if (p->kriteria.tipeLifestyle[j] != -1)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (otherUsers[i].kriteria.tipeLifestyle[k] != -1)
                    {
                        if (p->kriteria.tipeLifestyle[j] == otherUsers[i].kriteria.tipeLifestyle[k])
                        {
                            validateLifestylePreference = 1;
                        }
                    }
                }
            }
        }
        if (p->jenis_kelamin != otherUsers[i].jenis_kelamin)
        {
            validateGender = 1;
        }
        if ((p->umur >= otherUsers[i].kriteria.jarak_umur[0] && p->umur <= otherUsers[i].kriteria.jarak_umur[1]) && (otherUsers[i].umur >= p->kriteria.jarak_umur[0] && otherUsers[i].umur <= p->kriteria.jarak_umur[1]))
        {
            validateAgePreference = 1;
        }
        if (validatedPersonality == 1 && validatedRelationShipGoal == 1 && validateGender == 1 && validateAgePreference == 1 && validateLifestylePreference == 1)
        {

            new[count] = &otherUsers[i];
            count++;
        }
    }
    for (int i = count; i < 100; i++)
    {
        new[i] = NULL;
    }
}
void sortByAge(User *userCandidate[100], char by)
{
    // This 'by' using bubble sort algorithm to do ascending
    if (by == 'a')
    {
        for (int i = 0; i < 100 && userCandidate[i] != NULL; i++)
        {
            int swapped = 0;
            for (int j = i + 1; j < 100 && userCandidate[j] != NULL; j++)
            {
                if (userCandidate[i]->umur > userCandidate[j]->umur)
                {
                    User *temp = userCandidate[i];
                    userCandidate[i] = userCandidate[j];
                    userCandidate[j] = temp;
                    swapped = 1;
                }
            }
            if (swapped == 0)
            {
                break;
            }
        }
    }
    else if (by == 'd')
    {
        // This sort using selection sort algorithm to do descending
        for (int i = 0; i < 100 && userCandidate[i] != NULL; i++)
        {
            int max_idx = i;
            for (int j = i + 1; j < 100 && userCandidate[j] != NULL; j++)
            {
                if (userCandidate[j]->umur > userCandidate[max_idx]->umur)
                {
                    max_idx = j;
                }
            }
            if (max_idx != i)
            {
                User *temp = userCandidate[i];
                userCandidate[i] = userCandidate[max_idx];
                userCandidate[max_idx] = temp;
            }
        }
    }
}

void merge(User *arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Allocate arrays for pointers
    User **L = (User **)malloc(n1 * sizeof(User *));
    User **R = (User **)malloc(n2 * sizeof(User *));

    // Copy pointers into temporary arrays
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the arrays
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i]->nama, R[j]->nama) < 0)
        { // Compare by name
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(User *arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void sortByName(User *userCandidate[100], char by)
{
    if (by == 'a')
    {
        // Insertion Sort (Ascending)
        for (int i = 1; i < 100 && userCandidate[i] != NULL; i++)
        {
            User *key = userCandidate[i];
            int j = i - 1;
            while (j >= 0 && strcmp(userCandidate[j]->nama, key->nama) > 0)
            {
                userCandidate[j + 1] = userCandidate[j];
                j--;
            }
            userCandidate[j + 1] = key;
        }
    }
    else
    {
        // Merge Sort (Descending)
        int lastIndex = 0;
        for (int i = 0; i < 100 && userCandidate[i] != NULL; i++)
        {
            lastIndex = i;
        }
        mergeSort(userCandidate, 0, lastIndex);
    }
}

User *binarySearch(User *userCandidate[100], char name[100], int low, int high)
{
    // We need to sort first
    sortByName(userCandidate, 'a');
    int lastItemAmount;
    for (int i = 0; i < 100 && userCandidate[i] != NULL; i++)
    {
        lastItemAmount = i;
    }
    if (lastItemAmount < high)
    {
        high = lastItemAmount;
    }
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (mid < low || mid > high || userCandidate[mid] == NULL)
        {
            return NULL;
        }

        if (userCandidate[mid]->nama != NULL && strcmp(userCandidate[mid]->nama, name) == 0)
        {
            return userCandidate[mid];
        }

        if (userCandidate[mid]->nama != NULL && strcmp(userCandidate[mid]->nama, name) < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return NULL;
}

User *interpolationSearch(User *userCandidate[100], char name[100], int low, int high)
{
    // We need to sort first
    sortByName(userCandidate, 'a');
    int lastItemAmount;
    for (int i = 0; i < 100 && userCandidate[i] != NULL; i++)
    {
        lastItemAmount = i;
    }
    if (lastItemAmount < high)
    {
        high = lastItemAmount;
    }
    while (low <= high)
    {
        // This uses interpolation algorithm to search by Name
        int mid = low + ((high - low) * (strcmp(name, userCandidate[low]->nama))) /
                            (strcmp(userCandidate[high]->nama, userCandidate[low]->nama));

        if (mid < low || mid > high || userCandidate[mid] == NULL)
        {
            return NULL;
        }

        if (userCandidate[mid]->nama != NULL && strcmp(userCandidate[mid]->nama, name) == 0)
        {
            return userCandidate[mid];
        }

        if (userCandidate[mid]->nama != NULL && strcmp(userCandidate[mid]->nama, name) < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return NULL;
}

void findCandidate(User *p, User *userCandidate[100])
{
    User *user = NULL;
    printf("Masukkan nama: ");
    char temp[100];
    int type = 0;
    scanf("%[^\n]", temp);
    getchar();
    printf("Jenis searching algorithm yang ingin kamu gunakan\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    printf("3. Interpolation Search\n");
    printf("Pilihan : ");
    scanf("%d", &type);
    getchar();
    int lastIndex = 0;

    if (type == 1)
    {
        // This uses linear search to search
        for (int i = 0; i < 100 && userCandidate[i] != NULL; i++)
        {
            if (strcmp(userCandidate[i]->nama, temp) == 0)
            {
                user = userCandidate[i];
                break;
            }
        }
    }
    else if (type == 2)
    {

        // This uses binary search to search
        user = binarySearch(userCandidate, temp, 0, 100);
    }
    else if (type == 3)
    {
        // This uses interpolation search to search
        user = interpolationSearch(userCandidate, temp, 0, 100);
    }
    if (user == NULL)
    {
        printf("Tidak ada yang cocok\n");
    }
    else
    {
        showProfile(user);
    }
}

void showCandidates(User *p)
{
    User *userCandidate[100] = {0};
    getCandidates(p, userCandidate);
    int menu = 0;
    if (userCandidate[0] != NULL)
    {

        do
        {
            header();
            printf("Pilih menu sortiran\n");
            printf("1. Umur terkecil\n");
            printf("2. Umur terbesar\n");
            printf("3. Nama terkecil\n");
            printf("4. Nama terbesar\n");
            printf("5. Cari kandidat sesuai nama\n");
            printf("6. Kembali\n");
            scanf("%d", &menu);
            getchar();
            header();
            switch (menu)
            {
            case 1:
                sortByAge(userCandidate, 'a');
                break;
            case 2:
                sortByAge(userCandidate, 'd');
                break;
            case 3:
                sortByName(userCandidate, 'a');
                break;
            case 4:
                sortByName(userCandidate, 'd');
                break;
            case 5:
                findCandidate(p, userCandidate);
                break;
            case 6:
                break;
            default:
                break;
            }
            if (menu != 5)
            {
                for (int j = 0; j < 100 && userCandidate[j] != NULL; j++)
                {
                    if (userCandidate[j] != NULL)
                    {
                        printf("User's Profile\n");
                        printf("Name : %s\n", userCandidate[j]->nama);
                        printf("Age : %d\n", userCandidate[j]->umur);
                        printf("Gender : %s\n\n", userCandidate[j]->jenis_kelamin == pria ? "Pria" : "Wanita");
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            printf("Tekan tombol apa saja untuk melanjutkan\n");
            getchar();
        } while (menu != 6);
    }
    else
    {
        printf("No user available\n");
        printf("Tekan tombol apa saja untuk melanjutkan\n");
        getchar();
        return;
    }
}

int getUsers(FILE *fp, User *users)
{
    User user;
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    while (fread(&user, sizeof(User), 1, fp) == 1 && i < 40)
    {
        users[i] = user;
        memcpy(&users[i], &user, sizeof(User));
        i++;
    }
    return i;
}

int compare(const void *a, const void *b)
{
    const User *UserA = (const User *)a;
    const User *UserB = (const User *)b;
    return strcmp(UserA->nama, UserB->nama);
}

// This function uses quick sort
void showUsers(FILE *fp)
{
    User *users = (User *)malloc(40 * sizeof(User));
    int count = getUsers(fp, users);
    if (count == 0)
    {
        printf("Data user tidak ada");
        free(users);
        printf("Tekan tombol apa saja untuk melanjutkan\n");
        getchar();
        return;
    }
    else
    {
        qsort(users, count, sizeof(User), compare);
        printf("+------+----------------+----------------+-----+---------+---------+\n");
        printf("| No.  | Username       | Name           | Age | Gender  | Admin   |\n");
        printf("+------+----------------+----------------+-----+---------+---------+\n");
        for (int i = 0; i < count; i++)
        {
            printf("| %-4d | %-14s | %-14s | %-3d | %-7s | %-7s |\n",
                   i + 1,
                   users[i].username,
                   users[i].nama,
                   users[i].umur,
                   users[i].jenis_kelamin == pria ? "Pria" : "Wanita",
                   users[i].isAdmin ? "Yes" : "No");
        }

        printf("+------+----------------+----------------+-----+---------+---------+\n\n");
        printf("Disclaimer: ");
        printf("Users are sorted by Name with Quick Sort\n");

        free(users);
        printf("Tekan tombol apa saja untuk melanjutkan\n");
        getchar();
    }
}

void generateMenu(User *p,FILE *fp)
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
            SLEEP(250);
            showProfile(p);
            break;
        case 2:
            SLEEP(250);
            editUserCriteria(p, fp);
            break;
        case 3:
            SLEEP(250);
            showCandidates(p);
            break;
        case 4:
            puts("Thanks for using our app!");
            SLEEP(250);
            break;
        default:
            SLEEP(250);
            break;
        }
    } while (menu != 4);
}
void deleteUser(FILE *fp)
{
    while (1)
    {
        User *users = (User *)malloc(40 * sizeof(User));
        User newUsers[40];
        showUsers(fp);
        int newUsersCount = 0;
        int count = getUsers(fp, users);
        char username[50];
        printf("Masukkan username yang ingin dihapus : ");
        scanf("%49[^\n]", username);
        getchar();
        int isExist = 0;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(users[i].username, username) != 0)
            {
                newUsers[newUsersCount++] = users[i];
            }
            else
            {
                isExist = 1;
            }
        }

        if (isExist == 0)
        {
            puts("Username tidak ditemukan");
            free(users);
            continue;
        }
        freopen(USERDATA, "wb+", fp);
        fseek(fp, 0, SEEK_SET);
        SLEEP(2000);
        for (int i = 0; i < newUsersCount; i++)
        {
            fwrite(&newUsers[i], sizeof(User), 1, fp);
        }
        freopen(USERDATA, "ab+", fp);
        free(users);
        printf("User %s berhasil dihapus\n", username);
        printf("Tekan tombol apa saja untuk melanjutkan\n");
        getchar();
        break;
    };
}

void adminMenu(User *p, FILE *fp)
{
    int menu;
    do
    {
        clear_screen();
        printLogo();
        printf("Menu of Admin :\n");
        printf("1. Show Users\n");
        printf("2. Delete User\n");
        printf("3. Exit\n");
        printf("Your choice : ");
        scanf("%d", &menu);
        getchar();

        switch (menu)
        {
        case 1:
            showUsers(fp);
            break;
        case 2:
            deleteUser(fp);
            break;
        case 3:
            puts("Thanks for using our app!");
            break;
        default:
            break;
        }
    } while (menu != 3);
}

void loginPage(User *user, FILE *fp)
{
    int choice;
    puts("1. Login");
    puts("2. Register");

    printf("Your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        loginUser(user, fp);
        break;
    case 2:
        registerUser(user, fp);
        break;
    default:
        puts("Masukin yang bener ya dek");
    }
}

void loginUser(User *user, FILE *fp)
{
    char tempUserName[100], tempPassword[100];
    int authenticated = 0;
    do
    {
        clear_screen();
        printf("Enter your username: ");
        scanf("%s", tempUserName);
        getchar();

        printf("Enter your password: ");
        scanf("%s", tempPassword);
        getchar();
        if (strcmp(tempUserName, "admin") == 0 || strcmp(tempPassword, "admin123") == 0)
        {
            user->isAdmin = 1;
            strcpy(user->nama, tempUserName);
            user->umur = 20;
            strcpy(user->password, tempPassword);
            user->jenis_kelamin = pria;
            break;
        }
        User *users = (User *)malloc(40 * sizeof(User));

        getUsers(fp, users);
        for (int i = 0; i < 40; i++)
        {
            if (strcmp(tempUserName, users[i].username) == 0 && strcmp(tempPassword, users[i].password) == 0)
            {
                *user = users[i];
                authenticated = 1;
                break;
            }
        }
        free(users);
    } while (authenticated != 1);
}

void registerUser(User *user, FILE *fp)
{
    char tempUserName[100], tempPassword[100];
    do
    {
        printf("Enter your username: ");
        scanf("%s", tempUserName);
        getchar();

        printf("Enter your password: ");
        scanf("%s", tempPassword);
        getchar();

        int passLen = strlen(tempPassword);

        if (passLen < 8)
            puts("Try again");
        else
            break;

    } while (1);

    strcpy(user->username, tempUserName);
    strcpy(user->password, tempPassword);
    user->isAdmin = 0;

    askUser(user);

    fwrite(user, sizeof(User), 1, fp);
    fflush(fp);
}