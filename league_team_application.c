//Importing Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Defining Constants
#define NUM_TEAMS 3
#define SQUAD_SIZE 3

// Structure to Store Player Attributes
struct Player_Attributes {
    char name[50];
    int kit_number;
    char club[50];     
    char position[50];
    //Nested Structure to Store Birthday and Calculates Age using Birthday and Stores It
    struct Age{
        int birth_date;
        int birth_month;
        int birth_year;
        int age;
    } age;            
};      

// Structure to store Team Attributes
struct Team_Attributes {
    char team_name[20];                           //Team Name
    struct Player_Attributes players[SQUAD_SIZE]; //Nested Structure of Player Attributes
    int active_size;                              //No. of enrolled players in the squad
};
struct Team_Attributes teams[NUM_TEAMS];


//Function Prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error();
int get_curr_year();
void print_search(int i, int j);
void update_player(int i, int j);


//Defining Global Variables
int curr_enrolled_teams;

//Main Loop
int main(){
    //Defining Local Variables in the Main Loop
    int user_choice;

    //Initialize the Active Size to be 0
    for (int i = 0; i < NUM_TEAMS; i++) {
        teams[i].active_size = 0;
    }

    //Infinite Loop for the Main Menu
    while (1) {
        printf("\n______________________________________________\n\n");
        display_menu();
        printf("Enter your choice: ");
        scanf("%d",&user_choice);
        getchar();
        printf("\n______________________________________________\n\n");

        switch (user_choice){
            case 1:
                enroll_club();
                break;
            case 2:
                add_player();
                break;
            case 3:
                search_update();
                break;
            case 4:
                display_club_statistics();
                break;
            case 5:
                printf("Thank you for Applying.\n");
                return 0;
            default:
                handle_error();
        }
    }
}

//______________________________________________________________________________

//FUNCTION DEFINITIONS

//Main Menu Function
void display_menu(){
    printf("\nWelcome to League Team Application Main Menu\n");
    printf("1. Add a new Club\n");
    printf("2. Add a Player into the Club\n");
    printf("3. Search and Update Player Data\n");
    printf("4. Display Club Statistics\n");
    printf("5. Exit\n");
}

//Enroll into A New Team Function
void enroll_club(){
    //Printing the Function
    printf("*Enroll into A New Team*\n\n");

    //Checking if the maximum number of teams is reached
    if (curr_enrolled_teams >= NUM_TEAMS){
        printf("Maximum Teams Already Joined. You Cannot Join More.\n");
        return;
    }
    else{
        //Taking Input for Team Name
        char club_name[20];
        printf("Enter the name of the team: ");
        fgets(club_name, 20, stdin);
        club_name[strcspn(club_name, "\n")] = 0;

        //Checking if the Team Exists
        for (int i = 0; i < curr_enrolled_teams; i++) {
            if (strcasecmp(teams[i].team_name, club_name) == 0) {
                printf("Team Exists.\n");
                return;
            }
        }
        //Otherwise Create a New Team
        strcpy(teams[curr_enrolled_teams].team_name, club_name);
        teams[curr_enrolled_teams].active_size = 0;
        curr_enrolled_teams++;
        printf("Team %s has been enrolled successfully.\n", club_name);
    }
}

//Add New Player to A Team Function
void add_player(){
     //Printing the Function
    printf("*Add A New Player To The Team*\n\n");

    //Initializing Local Variables
    int np_kit, i, np_bday_date, np_bday_month, np_bday_year, np_age;
    char np_name[50], np_position[50];

    //Getting Current Year
    int curr_month, curr_year = get_curr_year();

    //Printing All Teams Available
    printf("Available Teams: \n");
    for (int i = 0; i < curr_enrolled_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].team_name);
    }
    printf("Select a team: ");
    scanf("%d",&i);
    getchar();

    // Validate Team Selection
    if (i < 1 || i > curr_enrolled_teams) {
        handle_error();  // Calling Handling Error Function
        return;
    }

    //Checking the Availability of the Team
    if (teams[i-1].active_size >= SQUAD_SIZE){
        printf("Can't Join this Team. Maximum Capacity Reached.");
        return;
    }

    while(1){
        //Take Player Details as Inputs
        printf("Enter player's name: ");
        fgets(np_name, sizeof(np_name), stdin);
        np_name[strcspn(np_name, "\n")] = '\0';

        printf("Enter player's kit number: ");
        scanf("%d",&np_kit);

        //Check if Player Already in Team
        bool member_exists = false;
        for (int i = 0; i < teams[i-1].active_size; i++) {
            if ((strcasecmp(teams[i-1].players[i].name, np_name) == 0) || (np_kit==teams[i-1].players[i].kit_number)) {
                member_exists = true;
                break;
            }
        }

        if (member_exists){
            printf("%s with kit number %d already enrolled in the team\n");
            printf("Enter new player. \n");
        }
        else{
            break;
        }
    }

    printf("Enter Date of Birth (DD MM YYYY): ");
    scanf("%d %d %d",&np_bday_date, &np_bday_month, &np_bday_year);
    getchar();
    printf("Enter position: ");
    fgets(np_position, sizeof(np_position), stdin);
    np_position[strcspn(np_position, "\n")] = '\0';

    //Calculate Age of Player
    if (np_bday_month <= curr_month){
        np_age = curr_year - np_bday_year;
    }
    else{
        np_age = curr_year - np_bday_year - 1;
    }

    //Add the Acquired Details to the Player Attributes Structure
    struct Player_Attributes new_player;
    strcpy(new_player.name, np_name);
    new_player.kit_number = np_kit;
    new_player.age.birth_date = np_bday_date;
    new_player.age.birth_month = np_bday_month;
    new_player.age.birth_year = np_bday_year;
    strcpy(new_player.position, np_position);
    new_player.age.age = np_age;

    //Add the Player to the Team
    teams[i-1].players[teams[i-1].active_size] = new_player;

    //Increase the Team Size by 1
    teams[i-1].active_size++;

    //Print Confirmation Message
    printf("Player %s has been added to the team %s.\n", np_name, teams[i-1].team_name);
}

//Search and Update Information Function
void search_update() {
     //Printing the Function
    printf("*Search and Update Information*\n\n");

    //Defining Local Variables
    char search_name[50];
    int i, j, search_kit, kit_or_name;
    bool find_status = false;

    //Taking User Input for Searching by Kit Number or Name
    printf("Search By:\n");
    printf("1. Player Name\n");
    printf("2. Player Kit Number\n");
    printf("Choice: ");
    scanf("%d",&kit_or_name);
    printf("\n");
    getchar();

    if (kit_or_name == 1){
        printf("Enter player name: ");
        fgets(search_name, sizeof(search_name), stdin);
        search_name[strcspn(search_name, "\n")] = '\0';
        
        //Comparing Each Player's Name in Player Structure in Teams Structure with User Input Name
        for (int i = 0; i < curr_enrolled_teams; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (strcasecmp(teams[i].players[j].name, search_name) == 0) {
                    i = i;
                    j = j;
                    print_search(i,j);
                    find_status = true;
                }
            }
        }
        if (find_status==false){
            printf("No Player Found!");
        }
    }
    else if (kit_or_name == 2){
        printf("Enter player kit number: ");
        scanf("%d",&search_kit);
        printf("\n");
        
        //Comparing Each Player's Kit Number in Player Structure in Teams Structure with User Input Name
        for (int i = 0; i < curr_enrolled_teams; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (teams[i].players[j].kit_number == search_kit) {
                    i = i;
                    j = j;
                    printf("Player Found!\n");
                    print_search(i,j);
                    find_status = true;
                }
            }
        }
        if (find_status==false){
            printf("No Player Found!");
        }
    }
    else{
        handle_error();
    }
}

//Club Statistics Function
void display_club_statistics() {
    int total_players = 0 ;
    int sum_age = 0 ;

    printf("\n*Club Statistics*\n\n");
    printf("Total No. of Teams: %d\n",curr_enrolled_teams);
    for (int i = 0; i < curr_enrolled_teams; i++) {
        printf("\nTeam %s:\n", teams[i].team_name);
        printf("Number of Players: %d\n", teams[i].active_size);
        printf("Players:\n");
        for (int j = 0; j < teams[i].active_size; j++) {
            printf("Name: %s, Age: %d, Kit Number: %d, Position: %s, Date of Birth: %.2d/%.2d/%4d\n", 
                    teams[i].players[j].name, teams[i].players[j].age.age,   
                    teams[i].players[j].kit_number, teams[i].players[j].position,
                    teams[i].players[j].age.birth_date, teams[i].players[j].age.birth_month, teams[i].players[j].age.birth_year);
            total_players++;
            sum_age+=teams[i].players[j].age.age;
        }
    }
    float avg_age = sum_age/total_players;
    printf("The average age of the players is: %.2f",avg_age);
}

//Handing Error Function
void handle_error() {
    printf("Invalid input. Please try again.\n");
}

//Getting Current Year Function
int get_curr_year(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int curr_year = tm.tm_year + 1900;      //Year is calculated only from 1990
    int curr_month = tm.tm_mon + 1;         //Months are from 0-11
    return curr_month, curr_year;
}

//Check Name Function
bool check_name(char *check_name){
    for (int i = 0; i < teams[i-1].active_size; i++) {
        if (strcasecmp(teams[i-1].players[i].name, check_name) == 0){
            return false;
        }
    }
    return true;
}

//Check Kit Number Function
bool check_kit(int check_kit){
    for (int i = 0; i < teams[i-1].active_size; i++) {
        if (teams[i-1].players[i].name, check_kit == 0){
            return false;
        }
    }
    return true;
}

//Printing the Search Function
void print_search(int i, int j){
    int update_conf;

    //Printing Player Information
    printf("Team: %s\n", teams[i].team_name);
    printf("Player Name: %s\n", teams[i].players[j].name);
    printf("Kit Number: %d\n", teams[i].players[j].kit_number);
    printf("Position: %s\n", teams[i].players[j].position);
    printf("Date of Birth: %d/%d/%d\n\n", teams[i].players[j].age.birth_date,teams[i].players[j].age.birth_month,teams[i].players[j].age.birth_year);
    printf("Would you Like to Update Player's Information?\n Press 1 to Proceed and 0 to Cancel: ");
    scanf("%d",&update_conf);
    printf("\n");
    switch(update_conf){
        case 1: 
            update_player(i,j);
            break;
        case 0: return;
    }
}

//Updating Player Information Function
void update_player(int i, int j){
    int update_choice;
    int curr_month, curr_year = get_curr_year();

    while (1){
        printf("Choose the Information to be Updated:\n");
        printf("1. Name\n");
        printf("2. Kit Number\n");
        printf("3. Date of Birth\n");
        printf("4. Position\n");
        printf("0. Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&update_choice);
        printf("\n");
        
        getchar();

        switch (update_choice) {
            case 1:
                //Getting Updated Name
                char u_name[50];
                printf("Enter Updated Name: ");
                fgets(u_name, sizeof(u_name), stdin);
                //Checking if Entry is Empty
                if (u_name == NULL) {
                    printf("Error reading name.\n");
                    return;
                }
                u_name[strcspn(u_name, "\n")] = '\0';

                // Check for Duplicate Player with Same Name
                if (check_name(u_name)==false) {
                    printf("A player with the name %s already exists in this team.\n", u_name);
                    return;
                }
                strcpy(teams[i].players[j].name, u_name);
                printf("Player Name Updated Successfully.\n\n");
                break;
                
                // teams[i].players[j].name[strcspn(teams[i].players[j].name, "\n")] = '\0';
                // printf("Player Name Updated Successfully.\n\n");
                // break;

            case 2:
                //Getting Updated Kit Number
                printf("Enter Updated Kit Number: ");
                int new_kit;
                scanf("%d", &new_kit);
                getchar();
                if (check_kit(new_kit)==false) {
                    printf("Invalid or Duplicate Kit Number.\n\n");
                    return; // Exit if Invalid or Duplicate Kit Number
                }
                teams[i].players[j].kit_number = new_kit; // Update Kit Number
                printf("Kit Number Updated Successfully.\n\n");
                break;

            case 3:
                //Getting Updated Birthday
                printf("Enter new Date of Birth (DD MM YYYY): ");
                int day, month, year;
                scanf("%d %d %d", &day, &month, &year);
                getchar();

                //Store the new Date of Birth
                teams[i].players[j].age.birth_date = day;
                teams[i].players[j].age.birth_month = month;
                teams[i].players[j].age.birth_year = year;

                //Calculating and Updating Age
                if (month <= curr_month){
                    teams[i].players[j].age.age = curr_year - year;
                }
                else{
                    teams[i].players[j].age.age = curr_year - year - 1;
                }

                printf("Date of Birth Updated Successfully\n\n");
                break;

            case 4:
                //Getting Updated Position
                printf("Enter Updated Position: ");
                if (fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin) == NULL) { // Read new position
                    printf("Error reading position.\n");
                    return;
                }
                teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = '\0'; // Remove newline character
                printf("Position updated successfully.\n\n");
                break;
            case 0:
                //Exiting Option
                print_search(i,j);
                return;
            default:
                handle_error();
                break;
        }
    }
}
