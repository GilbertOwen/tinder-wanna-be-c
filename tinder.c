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

void getbuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
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
} User;

int candidateIndex = 0;

User otherUsers[40] = {
    {"Alex", pria, {{18, 24}, {QualityTime, PhysicalTouch, ActOfService, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {Technology, Gaming, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 22},
    {"Jordan", wanita, {{20, 30}, {WordOfAffirmation, QualityTime, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Technology, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 25},
    {"Taylor", pria, {{18, 24}, {PhysicalTouch, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Gaming, Sport, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 23},
    {"Morgan", wanita, {{18, 24}, {QualityTime, PhysicalTouch, ActOfService, ReceivingGIft, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {CreativeArt, Sport, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 24},
    {"Jamie", pria, {{22, 32}, {QualityTime, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Technology, Gaming, Sport, Outdoor, INVALID_PREFERENCES}, {Undecided, Casual, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 28},
    {"Sam", wanita, {{20, 30}, {WordOfAffirmation, QualityTime, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Introverted, INVALID_PREFERENCES}, {Gaming, CreativeArt, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Undecided, INVALID_PREFERENCES}, {MorningPerson, NightOwl, INVALID_PREFERENCES}}, 27},
    {"Chris", pria, {{25, 35}, {ActOfService, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {Technology, Gaming, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {Flexible, NightOwl, INVALID_PREFERENCES}}, 30},
    {"Casey", wanita, {{18, 24}, {QualityTime, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {Sport, Outdoor, Technology, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {Flexible, NightOwl, INVALID_PREFERENCES}}, 22},
    {"Skyler", pria, {{18, 26}, {WordOfAffirmation, ActOfService, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Gaming, Technology, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 24},
    {"Drew", wanita, {{22, 30}, {QualityTime, ReceivingGIft, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Outdoor, Gaming, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 26},
    {"Riley", pria, {{20, 28}, {ActOfService, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {Sport, Outdoor, Technology, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 23},
    {"Quinn", wanita, {{18, 24}, {QualityTime, WordOfAffirmation, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Technology, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 21},
    {"Harper", pria, {{22, 32}, {ReceivingGIft, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {Gaming, Sport, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Undecided, Casual, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 29},
    {"Jamie", wanita, {{20, 28}, {QualityTime, PhysicalTouch, ActOfService, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Technology, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Undecided, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 24},
    {"Cameron", pria, {{18, 24}, {QualityTime, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Sport, Gaming, Technology, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 20},
    {"Reese", wanita, {{22, 32}, {ActOfService, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {Gaming, CreativeArt, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 28},
    {"Toby", pria, {{18, 26}, {WordOfAffirmation, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Technology, Gaming, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 24},
    {"Sydney", wanita, {{22, 30}, {QualityTime, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Introverted, INVALID_PREFERENCES}, {CreativeArt, Sport, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 27},
    {"Blake", pria, {{20, 30}, {ActOfService, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {Gaming, Technology, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {Flexible, NightOwl, INVALID_PREFERENCES}}, 29},
    {"Avery", wanita, {{22, 28}, {QualityTime, PhysicalTouch, ActOfService, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Sport, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 26},
    {"Peyton", pria, {{18, 24}, {ReceivingGIft, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Gaming, Sport, Technology, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 23},
    {"Robin", wanita, {{22, 32}, {QualityTime, WordOfAffirmation, ActOfService, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Outdoor, Gaming, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 27},
    {"Devon", pria, {{18, 24}, {QualityTime, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {Technology, Gaming, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 24},
    {"Dylan", wanita, {{22, 30}, {WordOfAffirmation, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Sport, Gaming, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 25},
    {"Kai", pria, {{18, 26}, {ActOfService, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Gaming, Technology, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 21},
    {"Toni", wanita, {{20, 28}, {QualityTime, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Introverted, INVALID_PREFERENCES}, {CreativeArt, Outdoor, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 24},
    {"Kendall", pria, {{22, 30}, {QualityTime, WordOfAffirmation, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Extroverted, INVALID_PREFERENCES}, {Technology, Gaming, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 26},
    {"Jules", wanita, {{18, 24}, {PhysicalTouch, ReceivingGIft, INVALID_PREFERENCES, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Ambivert, Introverted, INVALID_PREFERENCES}, {CreativeArt, Technology, Gaming, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, LongTerm, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 22},
    {"Rowan", pria, {{22, 30}, {WordOfAffirmation, QualityTime, ActOfService, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Extroverted, Ambivert, INVALID_PREFERENCES}, {Gaming, Technology, Outdoor, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Casual, Undecided, INVALID_PREFERENCES}, {NightOwl, Flexible, INVALID_PREFERENCES}}, 29},
    {"Taylor", wanita, {{20, 28}, {QualityTime, ReceivingGIft, PhysicalTouch, INVALID_PREFERENCES, INVALID_PREFERENCES}, {Introverted, Ambivert, INVALID_PREFERENCES}, {CreativeArt, Outdoor, Sport, INVALID_PREFERENCES, INVALID_PREFERENCES}, {LongTerm, Casual, INVALID_PREFERENCES}, {MorningPerson, Flexible, INVALID_PREFERENCES}}, 27},
};

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
void editUserCriteria(User *p);
void showCandidates(User *p);
void generateMenu(User *p);
void loginPage();
void registerUser(User *user, FILE *fp);
void loginUser(User *user, FILE *fp);

int main()
{
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
    loginPage(player, userDataFile);
    generateMenu(player);
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

void editUserCriteria(User *p)
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
}

void getCandidates(User *p, User *new[40])
{
    int count = 0;
    for (int i = 0; i < 40; i++)
    {
        int validatedPersonality = 0, validatedRelationShipGoal = 0, validateGender = 0;
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
        }
        if (p->jenis_kelamin != otherUsers[i].jenis_kelamin)
        {
            validateGender = 1;
        }
        if (validatedPersonality == 1 && validatedRelationShipGoal == 1 && validateGender == 1)
        {

            new[count] = &otherUsers[i];
            count++;
        }
    }
    for (int i = count; i < 40; i++)
    {
        new[i] = NULL;
    }
}

void showCandidates(User *p)
{
    User *userCandidate[40] = {0};
    getCandidates(p, userCandidate);

    for (int j = 0; j < 40; j++)
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
    printf("Tekan tombol apa saja untuk melanjutkan\n");
    getchar();
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
            SLEEP(250);
            showProfile(p);
            break;
        case 2:
            SLEEP(250);
            editUserCriteria(p);
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

void loginPage(User *user, FILE *fp)
{
    int choice;
    puts("1. Login");
    puts("2. Register");
    
    printf("Your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            loginUser(user, fp);
        case 2:
            registerUser(user, fp);
        default:
            puts("Masukin yang bener ya dek");
    }
}

void loginUser(User *user, FILE *fp)
{
    char tempUserName[100], tempPassword[100];
    printf("Enter your username: ");
    scanf("%s", tempUserName);

    printf("Enter your password: ");
    scanf("%s", tempPassword);
    
}

void registerUser(User *user, FILE *fp)
{
    char tempUserName[100], tempPassword[100];
    do
    {
        printf("Enter your username: ");
        scanf("%s", tempUserName);

        printf("Enter your password: ");
        scanf("%s", tempPassword);
        
        int passLen = strlen(tempPassword);
        
        if (passLen < 8)
            puts("Try again");
        else
            break;

    } while (1);
    
    strcpy(user->username, tempUserName);
    strcpy(user->password, tempPassword);

    askUser(user);

    fwrite(user, sizeof(User), 1, fp);
    fflush(fp);
}