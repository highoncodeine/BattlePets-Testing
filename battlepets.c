/******************************************************************************
 *  Description     : A program made in C that features a battleship x pokemon game that runs in the terminal.
 *  Author/s        : GARCIA, Hadjj
 *                    CUSTODIO, Justin
 *  Section         : S19B
 *  Last Modified   : 03/30/25
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* standard preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* custom preprocessor directives */
#include "defs.h"

/* other definitions (i.e., constants, typedefs, structs) */

/* function implementations */


/**
 * Clears the terminal/console screen
 * @param None
 * @return None
 * @pre System must support either the "cls" command (Windows) or "clear" command (Unix/Linux/macOS)
 */
void clrscr()
{
    system("@cls || clear");
}

/**
 * Displays the ASCII art title screen for the "BattlePets" game
 * @param play An integer flag indicating whether to show the message at the boot up of the program or when the program is closing
 * @return None
 * @pre None
 */
void displayLanding(int play)
{	
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf(" __________     _____    ___________ ___________ .____      ___________ __________  ___________ ___________   _________ \n");
    printf(" \\______   \\   /  _  \\   \\__    ___/ \\__    ___/ |    |     \\_   _____/ \\______   \\ \\_   _____/ \\__    ___/  /   _____/ \n");
    printf("  |    |  _/  /  /_\\  \\    |    |      |    |    |    |      |    __)_   |     ___/  |    __)_    |    |     \\_____  \\  \n");
    printf("  |    |   \\ /    |    \\   |    |      |    |    |    |___   |        \\  |    |      |        \\   |    |     /        \\ \n");
    printf("  |______  / \\____|__  /   |____|      |____|    |_______ \\ /_______  /  |____|     /_______  /   |____|    /_______  / \n");
    printf("         \\/          \\/                                  \\/         \\/                      \\/                      \\/ \n");
    printf("\n");
    printf("\033[1;33m                                                   BY HADJJ AND JUSTIN                                                                            \033[0m\n");
    if(play == 1){
    printf("                                                 Press Enter to Continue");
	} else {
	printf("                                                  Thank you for Playing");
	}
	getchar();
	clrscr();
}

/**
 * Displays the main menu of the game with options for the player to select
 * @param None
 * @return None
 * @pre None
 */
void displayStartMenu()
{
    printf("=========================\n");
    printf("\033[1;33m        MAIN MENU       \033[0m\n");
    printf("=========================\n");
    printf("[1] Battle!\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistics\n");
    printf("[4] How To Play?\n");
    printf("[5] Exit\n");
    printf("=========================\n");
    printf("Select your input: ");
}

/**
 * Displays the battle menu of the game with player-related options
 * @param None
 * @return None
 * @pre None
 */
void displayBattleMenu()
{
	clrscr();
    printf("=========================\n");
    printf("\033[1;33m       BATTLE MENU       \033[0m\n");
    printf("=========================\n");
    printf("[1] Create New Player\n");
    printf("[2] Select Player\n");
    printf("[3] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

/**
 * Displays the header for the player selection screen
 * @param None
 * @return None
 * @pre None
 */
void displaySelect()
{
	printf("=========================\n");
    printf("\033[1;33m     PLAYER SELECTION       \033[0m\n");
    printf("=========================\n");
}

/**
 * Manages the battle menu interactions including player creation, selection, and battle simulation
 * @param back Pointer to an integer that controls the active menu state
 * @param playerCount The current number of players in the system
 * @param maxPets The maximum number of available battle pets
 * @param players Array containing all registered player data
 * @param fileName String containing the path to the file with battle pet data
 * @return None
 * @pre 'players' array must be initialized, 'fileName' must point to a valid file
 */
void battleMenu(int *back, int playerCount, int maxPets, Player players[], const char *fileName)
{
    int nInput;
    Player player1, player2;
    bpet battlePets[MAX_PETS];
    bpet roster1[9], roster2[9];
    int results[3][3];
	
	// Load battle pet data from file
    loadBattlePets(fileName, battlePets);
    countBattlePets(fileName, &maxPets);
	
	// Display battle menu and get user input
    displayBattleMenu();
    scanf("%d", &nInput);

    switch (nInput) {
    case 1:
    	// Create a new player profile
        clrscr();
        createNewPlayer();
        break;
    case 2:
        clrscr();
        
        // Load all player data
        loadPlayers(players, &playerCount);

        // Player 1 selection process
        displaySelect();
        selectPlayer(players, playerCount, &player1, 1, NULL);
        clrscr();
        printf("Player 1: %s, select your roster.\n", player1.username);
        selectRoster(&player1, battlePets, maxPets, roster1);

        // Player 2 selection process
        displaySelect();
        selectPlayer(players, playerCount, &player2, 2, &player1);
        clrscr();
        printf("Player 2: %s, select your roster.\n", player2.username);
        selectRoster(&player2, battlePets, maxPets, roster2);

        clrscr();
        printf("Both players have selected their players and rosters. Ready to battle!\n");

        // Execute the battle simulation
        simulateFight(&player1, &player2, roster1, roster2, results);

        // Display match results and save them
        showMatchResults(&player1, &player2, roster1, roster2, results, fileName);
        break;
    case 3:
    	// Return to the main menu
        clrscr();
        *back = START_MENU;
        break;
    default:
    	// Handle invalid input
        clrscr();
        printf("Invalid Input.\n\n");
        break;
    }
}

/**
 * Displays the Competdium menu
 * @param None
 * @return None
 * @pre None
 */
void displayCompetdium()
{
    printf("=========================\n");
    printf("\033[1;33m     THE COMPETDIUM        \033[0m\n");
    printf("=========================\n");
    printf("[1] View BattlePets!\n");
    printf("[2] Add Battlepet\n");
    printf("[3] Edit BattlePet\n");
    printf("[4] Delete Battlepet\n");
    printf("[5] Save a Roster\n");
    printf("[6] Import BattlePets\n");
    printf("[7] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

/**
 * Displays a list of all available BattlePets
 * @param battlePets Array that stores the loaded BattlePet data
 * @param maxPets The maximum number of BattlePets to display
 * @param fileName The file path containing BattlePet data to be loaded
 * @return None
 * @pre 'fileName' must point to a valid file with BattlePet data
 */
void displayBattlePets(bpet battlePets[], int maxPets, const char *fileName)
{
	// Load BattlePet data 
	loadBattlePets(fileName, battlePets);
	countBattlePets(fileName, &maxPets);
	
	// Display each BattlePet with its index number
	printf("=========================\n");
    printf("\033[1;33m     BATTLEPET LIST      \033[0m\n");
    printf("=========================\n\n");
    for (int i = 0; i < maxPets; i++){
    	// Adjust formatting for single vs. double digit indices to maintain alignment
    	if(i < 10){
    		
        	printf(" [%d]  Name: %s\n", i, battlePets[i].name);
        } else {
        	 
        	printf("[%d]  Name: %s\n", i, battlePets[i].name);
		}
    }
}

/**
 * Accesses and displays detailed information about a specific BattlePet.
 * @param battlePets Array that stores the loaded BattlePet data.
 * @param index Index of the BattlePet to access in the array.
 * @return None
 * @pre The index must be within the bounds of the `battlePets` array.
 */
void accessBattlePets(bpet battlePets[], int index)
{
	// Retrieve the elemental type of the selected BattlePet
	char* elementalType = checkElement(battlePets[index].element);
	
	// Display details of the selected BattlePet
	printf("BattlePet Name: \033[1;33m%s\033[0m\n", battlePets[index].name);
	printf("Elemental Type: %s\n", elementalType);
	printf("Description: %s\n", battlePets[index].desc);
	printf("Matches: %d\n\n\n", battlePets[index].matches);
}

/**
 * Displays the BattlePets menu, loads data from a file, and allows the user to view details of a specific BattlePet.
 * @param battlePets Array that stores the loaded BattlePet data.
 * @param nInput Pointer to an integer that stores user input.
 * @param maxPets Maximum number of BattlePets.
 * @param fileName The file path containing BattlePet data to be loaded.
 * @return None
 * @pre 'fileName' must point to a valid file, and 'battlePets' must have sufficient capacity for 'maxPets'.
 */
void viewBattlePetsMenu(bpet battlePets[], int *nInput, int maxPets, const char *fileName)
{
    clrscr();
    
    // Load battlepet data
    loadBattlePets(fileName, battlePets);
    countBattlePets(fileName, &maxPets);
    
    // Display the list of battlepets available
    displayBattlePets(battlePets, maxPets, fileName);
    printf("\n\033[1;33mTo view the details of a Battlepet, enter its index, Otherwise ");
	printf("Input 0 to go Back: \033[0m\n\n");
    scanf("%d", nInput);
    
	if(*nInput > 0 && *nInput < maxPets){
		
		clrscr();
		accessBattlePets(battlePets, *nInput);
		
		printf("\033[1;33mPress 0 to go Back: \033[0m");
		scanf("%d", nInput);
		if(*nInput != 0){
		}
		
	} else {
		
		printf("Invalid Input\n");
	}
}

/**
 * Displays a menu for deleting a specific BattlePet and performs the deletion.
 * @param battlePets Array that stores the loaded BattlePet data.
 * @param maxPets Maximum number of BattlePets.
 * @param fileName The file path containing BattlePet data to be loaded.
 * @return None
 * @pre 'fileName' must point to a valid file with BattlePet data, and 'battlePets' must contain valid BattlePet data.
 */
void displayDeleteMenu(bpet battlePets[], int maxPets, const char *fileName)
{
	int bpetIndex;
	
	// Load and display the battlepets
	loadBattlePets(fileName, battlePets);
    displayBattlePets(battlePets, maxPets, fileName);
    
    // Prompt the user to select a BattlePet to delete
    printf("\n\033[1;33m Which BattlePet should be deleted:  \033[0m");
    scanf("%d", &bpetIndex);
    
    // Delete the selected BattlePet from the file
    deleteBattlePet(battlePets[bpetIndex].name, fileName);
}

/**
 * Manages the Competdium menu interactions, including viewing, adding, editing, deleting, and importing BattlePets, as well as saving rosters and navigating back to the start menu.
 * @param back Pointer to an integer that controls the active menu state.
 * @param battlePets Array that stores the loaded BattlePet data.
 * @param maxPets Maximum number of BattlePets.
 * @param fileName The file path containing BattlePet data to be loaded or modified.
 * @param players Array containing all registered player data.
 * @param playerCount The current number of players in the system.
 * @return None
 * @pre 'fileName' must point to a valid file, and 'battlePets' must have sufficient capacity for 'maxPets'.
 */
void competdiumMenu(int *back, bpet battlePets[], int maxPets, char *fileName, Player players[], int playerCount)
{
    int nInput = 0; // Variable to store user input for menu options

    clrscr();
    displayCompetdium(); // Display the Competdium menu options
    scanf("%d", &nInput);

    switch (nInput) {
        case 1: // View BattlePets
            clrscr();
            do {
                viewBattlePetsMenu(battlePets, &nInput, maxPets, fileName);
            } while (nInput != 0);
            break;
        case 2: // Add a new BattlePet
            clrscr();
            addBattlePet(battlePets, fileName);
            break;
        case 3: // Edit an existing BattlePet
            clrscr();
            editBattlePets(battlePets, maxPets, fileName);
            break;
        case 4: // Delete a BattlePet
            clrscr();
            displayDeleteMenu(battlePets, maxPets, fileName);
            break;
        case 5: // Save a roster of BattlePets
            clrscr();
            bpet roster[9]; // Array to store selected BattlePets for the roster
            saveRoster(players, playerCount, battlePets, maxPets, roster); 
            break;
        case 6: // Import BattlePets
            clrscr();
            importBattlePets(battlePets, maxPets, fileName);
            break;
        case 7: // Return to the start menu
            clrscr();
            *back = START_MENU;
            break;
        default:
            clrscr();
            printf("Invalid Input.\n\n");
    }
}

/**
 * Displays the Statistics menu for viewing top players and top BattlePets.
 * @param None
 * @return None
 * @pre None
 */
void displayStatistics()
{
    printf("=========================\n");
    printf("\033[1;33m        STATISTICS        \033[0m\n");
    printf("=========================\n");
    printf("[1] View Top Players\n");
    printf("[2] View Top Battlepets\n");
    printf("[3] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

/**
 * Handles the Statistics menu interactions, including viewing top players and top BattlePets.
 * @param back Pointer to an integer controlling the menu state.
 * @param players Array containing all player data.
 * @param battlePets Array containing all BattlePet data.
 * @param maxPets Maximum number of BattlePets.
 * @param playerCount Current number of players.
 * @param fileName File path to the BattlePet data file.
 * @return None
 * @pre `players` and `battlePets` arrays must be initialized, `fileName` must point to a valid file.
 */
void statisticsMenu(int *back, Player players[], bpet battlePets[], int maxPets, int playerCount, const char *fileName)
{
    int nInput = 0; // Variable to store user input

    displayStatistics(); // Display the statistics menu
    scanf("%d", &nInput);

    switch (nInput) {
        case 1: // View top players
            clrscr();
            loadPlayers(players, &playerCount);
            printTopPlayers(players, playerCount);
            clrscr();
            break;
        case 2: // View top BattlePets
            clrscr();
            countBattlePets(fileName, &maxPets);
            loadBattlePets(fileName, battlePets);
            printTopBattlePets(battlePets, maxPets);
            clrscr();
            break;
        case 3: // Return to the start menu
            clrscr();
            *back = START_MENU;
            break;
        default: // Handle invalid input
            clrscr();
            printf("Invalid Input. \n\n");
            break;
    }
}

/**
 * Displays and manages the Start Menu
 * @param battlePets Array containing all BattlePet data.
 * @param players Array containing all player data.
 * @param maxPets Maximum number of BattlePets.
 * @param playerCount Current number of players.
 * @param fileName File path to the BattlePet data file.
 * @return None
 * @pre `players` and `battlePets` arrays must be initialized, `fileName` must point to a valid file.
 */
void startMenu(bpet battlePets[], Player players[], int maxPets, int playerCount, char *fileName)
{
    int exit = 0; // Flag to determine when to exit the menu
    int input = 0; // Variable to store user input

    do {
        displayStartMenu(); // Display the Start Menu
        scanf("%d", &input);

        switch (input) {
            case 1: // Battle Menu
                clrscr();
                do {
                    battleMenu(&input, playerCount, maxPets, players, fileName);
                } while (input != START_MENU);
                break;
            case 2: // Competdium Menu
                clrscr();
                do {
                    competdiumMenu(&input, battlePets, maxPets, fileName, players, playerCount);
                } while (input != START_MENU);
                break;
            case 3:  // Statistics Menu
                clrscr();
                do {
                    statisticsMenu(&input, players, battlePets, maxPets, playerCount, fileName);
                } while (input != START_MENU);
                break;
            case 4: // How to Play Menu
            	clrscr();
            	howToPlay();
            	getchar();
            	clrscr();
            	break;
            case 5: // Exit to Landing
                clrscr();
                getchar();
                displayLanding(0);
                exit = 1;
                break;
            default: // Handle invalid input
                clrscr();
                printf("Invalid Input.\n\n");
        }
    } while (exit == 0);
}

/**
 * Validates a username based on specific rules for length, allowed characters, and format.
 * @param username A string representing the username to be validated.
 * @return An integer indicating the validity of the username (1 if valid, 0 if invalid).
 * @pre `username` must be a null-terminated string.
 */
int validateUsername(char *username)
{
    int length = strlen(username);
    int validity = 1; // Initialize as valid
    
    // Check if username is within the allowed length
    if (length == 0 || length > MAX_USERNAME_LENGTH) {
        validity = 0;
    }
    
    // Check if username is valid
    for (int i = 0; i < length; i++) {
        char c = username[i];
        
        // Check if character is alphanumeric
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            // Valid character
        } else if (c == '@' || c == '_' || c == '-' || c == '+' || c == '#' || c == '$' || c == '!' || c == '.') {
            // Valid special character
        } else {
            // Invalid character
            validity = 0;
        }
    }
    
    // Check if username contains spaces
    for (int i = 0; i < length; i++) {
        if (username[i] == ' ') {
            validity = 0;
        }
    }
    
    return validity;
}

/**
 * Creates a new player with a unique username and saves the player data to a file.
 * @param None
 * @return None
 * @pre `PLAYER_FILE` must be defined and point to a writable file.
 */
void createNewPlayer()
{
	// Display player creation header
    Player player;
    printf("=========================\n");
    printf("\033[1;33m    CREATE NEW PLAYER       \033[0m\n");
    printf("=========================\n\n");
    
    // Prompt for new player username
    printf("New Player Username: ");
    scanf("%s", player.username);
    
    // Validate the provided username
    if (validateUsername(player.username) == 1)
    {
    	 // Initialize player statistics
        player.wins = 0;
        player.losses = 0;
        player.draws = 0;

        // Save player data to a text file
        FILE *file = fopen(PLAYER_FILE, "a");
        if (!file) { // Error handling
            printf("Error opening file.\n");
            return;
        }
        
        // Save the new player's data
        fprintf(file, "%s\n%d\n%d\n%d\n\n", player.username, player.wins, player.losses, player.draws);
        fclose(file);
		
		// Confirmation screen for successful save
        clrscr();
        printf("=========================\n");
    	printf("\033[1;33m    CREATE NEW PLAYER       \033[0m\n");
    	printf("=========================\n\n");
    	printf("New Player: %s\n", player.username);
        printf("\n[Player saved successfully]\n\n");
        printf("Press Enter to Continue...");
        getchar();
        getchar();
    }
    else // Display error message for invalid username
    {
        clrscr();
        printf("Invalid username. Player not saved.\n");
        return;
    }
}

/**
 * Loads player data from a file into an array of Player structures.
 * @param players Array of Player structures where the loaded data will be stored.
 * @param playerCount Pointer to an integer to store the number of loaded players.
 * @return None
 * @pre `PLAYER_FILE` must be defined and point to a readable file. 
 *      `players` array must have enough capacity to store up to `MAX_PLAYERS` entries.
 */
void loadPlayers(Player players[], int *playerCount)
{
    clrscr();
    
    // Open the player file for reading
    FILE *file = fopen(PLAYER_FILE, "r");
    if (!file){
        printf("Error opening file.\n"); // Error handling for file opening issues
    } else {
    	// Reset player count before loading
        *playerCount = 0;
        char buffer[256];
        
        // Read player data from the file until end or maximum player count
        while (fgets(buffer, sizeof(buffer), file) && *playerCount < MAX_PLAYERS) {
        	
            // Read username and remove trailing newline
            strcpy(players[*playerCount].username, strtok(buffer, "\n"));

            // wins
            fgets(buffer, sizeof(buffer), file);
            players[*playerCount].wins = atoi(buffer);

            // losses
            fgets(buffer, sizeof(buffer), file);
            players[*playerCount].losses = atoi(buffer);

            // draws
            fgets(buffer, sizeof(buffer), file);
            players[*playerCount].draws = atoi(buffer);

            // Skip the empty line separating player entries
            fgets(buffer, sizeof(buffer), file);
			
			// Increment the player count
            (*playerCount)++;
        }
		
		// Close the file after loading all players
        fclose(file);
    }
}

/**
 * Allows a player to select a player profile from a list of available players.
 * @param players Array of Player structures containing all available players.
 * @param playerCount The total number of players in the array.
 * @param selectedPlayer Pointer to the Player structure to store the selected player's data.
 * @param playerNumber The number of the player making the selection (e.g., Player 1 or Player 2).
 * @param alreadySelectedPlayer Pointer to the Player structure already selected by another player (optional).
 * @return None
 * @pre `players` must be populated with valid data, and `playerCount` must be greater than 0.
 */
void selectPlayer(Player players[], int playerCount, Player *selectedPlayer, int playerNumber, Player *alreadySelectedPlayer)
{
    int valid = 0; // Flag that tracks whether a valid selection has been made

    while (!valid) {
        // Handle the case where there are no players available
        if (playerCount == 0) {
            printf("No players available.\n");
            valid = 1; // Exit the loop
        } else {
            printf("\033[1;33mPlayer %d, select a player: \033[0m\n", playerNumber);
            
            // Display the list of available players
            for (int i = 0; i < playerCount; i++) {
                // Skip the player already selected by Player 1
                if (alreadySelectedPlayer != NULL && strcmp(players[i].username, alreadySelectedPlayer->username) == 0) {
                }
                else 
                printf("[%d] %s\n", i + 1, players[i].username);
            }

            int choice;
            
            printf(">> ");
            scanf("%d", &choice);

            // Check if the choice is valid and not the already selected player
            if (choice < 1 || choice > playerCount || 
                (alreadySelectedPlayer != NULL && strcmp(players[choice - 1].username, alreadySelectedPlayer->username) == 0)) {
                clrscr();
                printf("Invalid choice. Please try again.\n");
            } else {
            	// Display the selected player's information
                *selectedPlayer = players[choice - 1];
                clrscr();
                printf("Player %d has selected: \033[1;33m%s\033[0m\n", playerNumber, selectedPlayer->username);
                printf("Wins: %d\n", selectedPlayer->wins);
                printf("Losses: %d\n", selectedPlayer->losses);
                printf("Draws: %d\n", selectedPlayer->draws);

                // Wait for user input before clearing the screen
                printf("Press Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
                valid = 1;
            }
        }
    }
}

/**
 * Loads a saved roster for a specific player from a file.
 * @param username The username of the player whose roster is to be loaded.
 * @param roster Array to store the loaded roster of BattlePets.
 * @param battlePets Array of all available BattlePets in the ComPetDium.
 * @param maxPets The total number of BattlePets in the ComPetDium.
 * @return 1 if the roster is loaded successfully, 0 otherwise.
 * @pre `battlePets` must be populated with valid BattlePet data, and `maxPets` must represent its size.
 */
int loadSavedRoster(char *username, bpet roster[], bpet battlePets[], int maxPets)
{
    char filename[100];
    snprintf(filename, sizeof(filename), "saved_roster/%s.txt", username); // Construct the filename
    
    // Open the roster file in read mode
    FILE *file = fopen(filename, "r");
    int error = 0; // Error flag to track issues
    int i = 0;     // Counter for roster entries

    if (file == NULL) {
        printf("\033[1;91mError: Could not load saved roster for %s.\033[0m\n", username);
        error = 1; // Set error flag
        
    } else {
        char line[50]; // Buffer to hold BattlePet names
        while (i < 9 && error == 0) {
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = 0; // Remove the newline character

                // Find the BattlePet in the battlePets array by name
                int found = 0;
                for (int j = 0; j < maxPets; j++) {
                    if (strcmp(line, battlePets[j].name) == 0) {
                        roster[i] = battlePets[j]; // Copy the full BattlePet details to the roster
                        found = 1;
                    }
                }

                if (found == 0) {
                	// Handle missing BattlePet in the ComPetDium
                    printf("\033[1;91mError: BattlePet '%s' not found in ComPetDium.\033[0m\n", line);
                    error = 1; // Set error flag
                } else {
                    i++;
                }
            } else {
                error = 1; // Set error flag if fewer than 9 lines are read
            }
        }

        fclose(file);

        if (i < 9 && error == 0) {
            printf("Error: Saved roster for %s is incomplete or corrupted.\n", username);
            error = 1; // Set error flag
        }
    }

    if (error == 0) {
    	 // Clear the screen and display success message
    	clrscr();
    	
        printf("\033[1;32m[Loaded saved roster for %s successfully]\033[0m\n\n", username);

        // Display the final match roster
        printf("\n\033[1;33mFinal Match Roster:\033[0m\n");
        for (int i = 0; i < 9; i++) {
            printf("<%s> ", roster[i].name);
            if ((i + 1) % 3 == 0) printf("\n");
        }
    }

    return error == 0; // Return 1 for success, 0 for failure
}

/**
 * Allows the user to create a match roster by selecting 9 unique BattlePets from the ComPetDium.
 * @param battlePets Array of all available BattlePets in the ComPetDium.
 * @param maxPets The total number of BattlePets in the ComPetDium.
 * @param roster Array to store the selected BattlePets for the match roster.
 * @pre `battlePets` must be populated with valid BattlePet data, and `maxPets` must represent its size.
 */
void createRoster(bpet battlePets[], int maxPets, bpet roster[])
{
    int count = 0; // Counter for selected BattlePets
	
	// Loop until 9 BattlePets have been selected
    while (count < 9) {
        clrscr(); 
        
        // Display the current match roster
        printf("\033[1;33mMatch Roster:\033[0m\n");
        for (int i = 0; i < 9; i++) {
            printf("<%s> ", count > i ? roster[i].name : "?"); // Show selected pets or placeholders
            if ((i + 1) % 3 == 0) printf("\n"); // Format into rows of 3
        }
		
		// Display the available BattlePets in the ComPetDium
        printf("\n\033[1;33mComPetDium: \033[0m\n");
        for (int i = 0; i < maxPets; i++) {
            int alreadySelected = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(battlePets[i].name, roster[j].name) == 0) {
                    alreadySelected = 1;
                }
            }
            if (!alreadySelected) {
                printf("[%d] %s\n", i + 1, battlePets[i].name); // Display unselected pets
            }
        }
		
		// Prompt the user to make a selection
        printf(">> ");
        int choice;
        scanf("%d", &choice);
		
		// Validate the user's choice
        if (choice < 1 || choice > maxPets){
        	// Handle invalid selection
            printf("\033[1;91mInvalid choice. Try again. \033[0m\n");
            printf("Press Enter to continue...");
            getchar(); // Consume the newline character left by scanf
            getchar(); // Wait for the user to press Enter
        } else {
        	// Check if the selected BattlePet is already in the roster
            int alreadySelected = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(battlePets[choice - 1].name, roster[j].name) == 0) {
                    alreadySelected = 1;
                }
            }

            if (alreadySelected){
            	// Notify the user about the duplicate selection
                printf("\033[1;91mBattlePet already selected. Choose another.\033[0m\n");
                printf("Press Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
            } else {
            	 // Add the selected BattlePet to the roster
                roster[count] = battlePets[choice - 1];
                count++;
            }
        }
    }

    // Final display of the completed roster
    clrscr();
    printf("\033[1;33mFinal Match Roster:\033[0m\n");
    for (int i = 0; i < 9; i++) {
        printf("<%s> ", roster[i].name);
        if ((i + 1) % 3 == 0) printf("\n");
    }

}

/**
 * Allows a player to select their roster for a match by either loading a saved roster or creating a new one.
 * @param player Pointer to the Player structure for the player making the selection.
 * @param battlePets Array of all available BattlePets in the ComPetDium.
 * @param maxPets The total number of BattlePets in the ComPetDium.
 * @param roster Array to store the selected BattlePets for the match roster.
 * @pre `battlePets` must be populated with valid BattlePet data, and `maxPets` must represent its size.
 *      `player` must point to a valid Player structure.
 */
void selectRoster(Player *player, bpet battlePets[], int maxPets, bpet roster[])
{
    int valid = 0; // Flag to track whether a valid roster has been selected
    
    while (!valid) {
        clrscr();
        
        // Display roster selection options
        printf("Player \033[1;33m%s\033[0m Roster\n", player->username);
        printf("[1] Load saved roster\n");
        printf("[2] Create roster for this match\n");
        printf(">> ");
        
        
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
        	 // Attempt to load the saved roster for the player
            if (loadSavedRoster(player->username, roster, battlePets, maxPets)) {
                printf("\nPress Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
                clrscr(); // Clear the screen after the user presses Enter
                valid = 1; // Exit the loop if loading was successful
            } else {
            // If loading fails, notify the user and allow re-selection
                printf("Returning to roster selection...\n");
                printf("\nPress Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
            }
        } else if (choice == 2) {
        	// Allow the user to create a new roster
            createRoster(battlePets, maxPets, roster);
            printf("\nPress Enter to continue...");
            getchar();
            getchar(); 
            clrscr(); 
            valid = 1; // Exit the loop after creating the roster
        } else {
        	// Handle invalid menu choices
            printf("\n\033[1;91mInvalid choice. Please try again. \033[0m\n");
            printf("Press Enter to continue...");
            getchar(); 
            getchar(); 
        }
    } 
}

/**
 * Determines the result of a battle between two elements.
 * @param element1 The index of the first element (attacker).
 * @param element2 The index of the second element (defender).
 * @return 1 if element1 wins, -1 if element2 wins, 0 if it's a draw.
 * @pre Both element1 and element2 must be between 0 and 7 inclusive.
 */
int getBattleResult(int element1, int element2)
{
    int affinity[8][8] = {
        //            Fire Water Grass Earth Air Electric Ice Metal
        /*Fire*/    {  0,   -1,    1,    1,    0,    0,    1,   -1 },
        /*Water*/   {  1,    0,   -1,    0,    0,    1,   -1,    1 },
        /*Grass*/   { -1,    1,    0,    1,   -1,    1,   -1,    0 },
        /*Earth*/   { -1,    0,   -1,    0,    1,   -1,    0,    1 },
        /*Air*/     {  0,    0,    1,   -1,    0,    1,   -1,   -1 },
        /*Electric*/{  0,   -1,   -1,    1,   -1,    0,   -1,    1 },
        /*Ice*/     { -1,    1,    1,    0,    1,    1,    0,   -1 },
        /*Metal*/   {  1,   -1,    0,   -1,    1,   -1,    1,    0 }
    };
    
    return affinity[element1][element2]; // return 1 if element 1 wins, -1 if element 2 wins, 0 if it is a draw.
}

/**
 * Simulates a fight between two players' BattlePet rosters.
 * @param player1 Pointer to Player 1 structure.
 * @param player2 Pointer to Player 2 structure.
 * @param roster1 Array of BattlePets selected by Player 1.
 * @param roster2 Array of BattlePets selected by Player 2.
 * @param results A 3x3 integer array to store the battle results.
 *                - `1`: Player 1 wins
 *                - `2`: Player 2 wins
 *                - `0`: Draw
 * @pre Both rosters should contain exactly 9 BattlePets.
 */
void simulateFight(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3])
{
    clrscr();
    
    // Display the match-up
    printf("\033[1;33m%s\033[0m (Player 1) vs \033[1;32m%s\033[0m (Player 2)\n\n", player1->username, player2->username);
    printf("BattlePets, Fight!\n");
    
    // Simulate fights between BattlePets in both rosters
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
         int index = i * 3 + j; // Index in the flat roster array
         int result = getBattleResult(roster1[index].element, roster2[index].element); // Get the result of the battle
         
         // Display grid index and battlePets
         printf("[%d][%d] \033[1;33m%s\033[0m vs. \033[1;32m%s\033[0m\n", i, j, roster1[index].name, roster2[index].name); 
        
        // Store the result in the 2D results array
        if (result == 1)
        results[i][j] = 1; // player 1 wins
        else if (result == -1)
        results[i][j] = 2; // player 2 wins
        else
        results[i][j] = 0; // draw
        
    	}
	}
	
	// Prompt user to continue after battle simulation
    printf("\nPress Enter to continue... ");
    getchar();
}

/**
 * Displays the match results grid and calculates the win counts for two players.
 * @param player1 Pointer to the first player's structure containing player details.
 * @param player2 Pointer to the second player's structure containing player details.
 * @param results A 3x3 integer array where each element represents the outcome of a match:
 *                - 1: Player 1 wins
 *                - 2: Player 2 wins
 *                - 0: Draw
 * @param player1Wins Pointer to an integer to store the total wins of Player 1.
 * @param player2Wins Pointer to an integer to store the total wins of Player 2.
 * @return None
 * @pre The `results` array must be a 3x3 matrix with values 0, 1, or 2.
 *      The `player1Wins` and `player2Wins` pointers must be initialized to 0 before calling.
 */
void displayMatchResultsGrid(Player *player1, Player *player2, int results[3][3], int *player1Wins, int *player2Wins)
{
	// Display header with player names
    printf("\033[1;33m%s\033[0m (Player 1) vs \033[1;32m%s\033[0m (Player 2)\n\n", player1->username, player2->username);
    
     // Display the grid header
    printf("\033[1;33mMatch Results\033[0m\n");
    
    // Iterate through the 3x3 match results grid
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
        	// Increment Player 1's win count if result is 1
            if (results[i][j] == 1) (*player1Wins)++;
            // Increment Player 2's win count if result is 2
            if (results[i][j] == 2) (*player2Wins)++;

            // Print the match result based on the value in the grid
            if (results[i][j] == 1) {
                printf("[1] ");
            } else if (results[i][j] == 2) {
                printf("[2] ");
            } else {
                printf("[D] ");
            }
        }
        printf("\n");
    }
}

/**
 * Determines the winner of a series of matches based on the results grid and win counts.
 * It evaluates whether the winner has achieved a "Lucky Win" or a "Majority Win."
 * @param player1 Pointer to the first player's structure containing player details.
 * @param player2 Pointer to the second player's structure containing player details.
 * @param results A 3x3 integer array where each element represents the outcome of a match:
 *                - 1: Player 1 wins
 *                - 2: Player 2 wins
 *                - 0: Draw
 * @param player1Wins Total number of matches won by Player 1.
 * @param player2Wins Total number of matches won by Player 2.
 * @param winType A string to store the type of win (e.g., "Lucky Win", "Majority Win", or "Draw").
 * @param winner A string to store the name of the winning player, or "None" if it's a draw.
 * @return None
 * @pre The `results` array must be a 3x3 matrix with values 0, 1, or 2.
 *      The `winType` and `winner` strings must have sufficient space for storing their respective values.
 */
void determineWinner(Player *player1, Player *player2, int results[3][3], int player1Wins, int player2Wins, char *winType, char *winner)
{
    int luckyWin = 0; // Variable to store if there's a "Lucky Win" based on row, column, or diagonal alignment
    
    // Check for a "Lucky Win" in rows or columns
    for (int i = 0; i < 3; i++) {
        if ((results[i][0] == results[i][1] && results[i][1] == results[i][2] && results[i][0] != 0) || // Row check
            (results[0][i] == results[1][i] && results[1][i] == results[2][i] && results[0][i] != 0)) { // Column check
            luckyWin = results[i][i];
        }
    }

    // Check for a "Lucky Win" in diagonals
    if ((results[0][0] == results[1][1] && results[1][1] == results[2][2] && results[0][0] != 0) ||
        (results[0][2] == results[1][1] && results[1][1] == results[2][0] && results[0][2] != 0)) {
        luckyWin = results[1][1];
    }

    // Determine the winner based on the type of win
    if (luckyWin == 1) {
        printf("\n\033[1;33mWinner: %s (Player 1) [Lucky Win]\033[0m\n", player1->username);
        strcpy(winType, "Lucky Win");
        strcpy(winner, player1->username); // Set the winner to Player 1's username
    } else if (luckyWin == 2) {
        printf("\n\033[1;33mWinner: %s (Player 2) [Lucky Win]\033[0m\n", player2->username);
        strcpy(winType, "Lucky Win");
        strcpy(winner, player2->username);
    } else if (player1Wins > player2Wins) {
        printf("\n\033[1;33mWinner: %s (Player 1) [Majority Win]\033[0m\n", player1->username);
        strcpy(winType, "Majority Win");
        strcpy(winner, player1->username);
    } else if (player2Wins > player1Wins) {
        printf("\n\033[1;33mWinner: %s (Player 2) [Majority Win]\033[0m\n", player2->username);
        strcpy(winType, "Majority Win");
        strcpy(winner, player2->username);
    } else {
        printf("\n\033[1;93mThe match is a draw!\033[0m\n");
        strcpy(winType, "Draw");
        strcpy(winner, "None");
    }
}

/**
 * Displays match results, determines the winner, updates player and battle pet stats, and saves the match results to a file.
 * @param player1 Pointer to the first player's structure containing player details.
 * @param player2 Pointer to the second player's structure containing player details.
 * @param roster1 Array of battle pets for Player 1.
 * @param roster2 Array of battle pets for Player 2.
 * @param results A 3x3 integer array where each element represents the outcome of a match:
 *                - 1: Player 1 wins
 *                - 2: Player 2 wins
 *                - 0: Draw
 * @param fileName The name of the file where match results will be saved.
 * @return None
 * @pre The `results` array must be a 3x3 matrix with values 0, 1, or 2.
 */
void showMatchResults(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3], const char *fileName)
{
    clrscr();
    
    // Initialize win counts and result variables
    int player1Wins = 0, player2Wins = 0; // Track the number of wins for each player
    char winType[20]; // String to store the type of win
    char winner[50]; // String to store the name of the winner
    
    // Display the match results grid and calculate the win counts
    displayMatchResultsGrid(player1, player2, results, &player1Wins, &player2Wins);

	// Determine the winner and the type of win
    determineWinner(player1, player2, results, player1Wins, player2Wins, winType, winner);
	
	// Update player statistics based on the match results and save them to the specified file
    updatePlayerStats(player1, player2, results);
    
    // Update battle pet statistics and save them to the specified file
    updateBattlePetStats(roster1, roster2, fileName);
	
	// Save the match results to a file
    saveMatchResults(player1, player2, roster1, roster2, results, winType, winner);

	// Prompt the user to press Enter to play again
    printf("Press Enter to play again... ");
    getchar();
    clrscr();
}

/**
 * Updates the player statistics after a match.
 * @param player1 Pointer to the first player's structure containing player details.
 * @param player2 Pointer to the second player's structure containing player details.
 * @param results A 3x3 integer array where each element represents the outcome of a match:
 *                - 1: Player 1 wins
 *                - 2: Player 2 wins
 *                - 0: Draw
 * @return None
 * @pre The `results` array must be a 3x3 matrix with values 0, 1, or 2.
 *      The file `players.txt` must exist and contain valid player data in the expected format.
 */
void updatePlayerStats(Player *player1, Player *player2, int results[3][3])
{
    Player players[MAX_PLAYERS]; // Array to store the list of players
    int playerCount = 0; // Variable to track the number of players

    // Load existing player data from the file
    loadPlayers(players, &playerCount);

    // Calculate the number of wins for each player
    int player1Wins = 0, player2Wins = 0;
    displayMatchResultsGrid(player1, player2, results, &player1Wins, &player2Wins);

    // Determine the match winner and type of win
    char winType[20]; // String to store the type of win
    char winner[50]; // String to store the name of the winner
    determineWinner(player1, player2, results, player1Wins, player2Wins, winType, winner);

    // Update the statistics for each player
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].username, player1->username) == 0){ // Check for Player 1
            if (strcmp(winner, player1->username) == 0) {
                players[i].wins++; // Increment wins for Player 1
            } else if (strcmp(winner, player2->username) == 0) {
                players[i].losses++; // Increment losses for Player 1
            } else {
                players[i].draws++; // Increment draws for Player 1
            }
        } else if (strcmp(players[i].username, player2->username) == 0){ // Check for Player 2
            if (strcmp(winner, player2->username) == 0) {
                players[i].wins++; 
            } else if (strcmp(winner, player1->username) == 0) {
                players[i].losses++;
            } else {
                players[i].draws++;
            }
        }
    }

    // Save updated player statistics back to the file
    FILE *file = fopen("players.txt", "w"); // Open file in write mode
    if (!file) {
        printf("Error: Could not open players.txt for writing.\n");
        return;
    }
	
	// Write updated player data to the file
    for (int i = 0; i < playerCount; i++) {
        fprintf(file, "%s\n%d\n%d\n%d\n\n", players[i].username, players[i].wins, players[i].losses, players[i].draws);
    }
    fclose(file);
}

/**
 * Updates the battlepet statistics by incrementing the number of matches each battle pet has participated in.
 * @param roster1 Array of battle pets belonging to Player 1.
 * @param roster2 Array of battle pets belonging to Player 2.
 * @param fileName The name of the file where battle pet statistics are stored.
 * @return None
 * @pre The `roster1` and `roster2` arrays must each contain exactly 9 battle pets.
 *      The `fileName` must point to a valid file containing battle pet statistics.
 */
void updateBattlePetStats(bpet roster1[], bpet roster2[], const char *fileName)
{
	// Loop through each battle pet in Player 1's roster
	for(int i = 0; i < 9; i++){
		
		incrementBattlePetMatches(roster1[i].name, fileName); // Increment match count for each battle pet
	}
	
	// Loop through each battle pet in Player 2's roster
	for(int j = 0; j < 9; j++){
		
		incrementBattlePetMatches(roster2[j].name, fileName); // Increment match count for each battle pet
	}
}

/**
 * Saves the match results, including player details, rosters, and match outcomes, to a player named file.
 * @param player1 Pointer to the first player's structure containing player details.
 * @param player2 Pointer to the second player's structure containing player details.
 * @param roster1 Array of battle pets belonging to Player 1.
 * @param roster2 Array of battle pets belonging to Player 2.
 * @param results A 3x3 integer array where each element represents the outcome of a match:
 *                - 1: Player 1 wins
 *                - 2: Player 2 wins
 *                - 0: Draw
 * @param winType A string describing the type of win (e.g., "Lucky Win" or "Majority Win").
 * @param winner A string containing the username of the winning player, or "None" in case of a draw.
 * @return None
 * @pre The `roster1` and `roster2` arrays must each contain exactly 9 battle pets.
 *      The `results` array must be a 3x3 matrix with values 0, 1, or 2.
 */
void saveMatchResults(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3], const char *winType, const char *winner)
{
	int matchNumber = 1; // Used to generate unique filenames for each match result
    char filename[100]; // String to store the filename
    
    FILE *file;
    
    // Generate a unique filename by incrementing the match number
    do {
        snprintf(filename, sizeof(filename), "results/match_%d.txt", matchNumber);
        file = fopen(filename, "r");
        if (file) {
            fclose(file);
            matchNumber++; // Increment match number for the next check
        }
    } while (file != NULL);
	
	// Open the file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not save match results.\n"); // Print an error message if the file cannot be opened
        
    } 
    
    // Write player details
    else {
        fprintf(file, "Player1: %s\n", player1->username);
        fprintf(file, "Player2: %s\n\n", player2->username);
    
        // Write battle pet rosters
        fprintf(file, "P1 Roster vs. P2 Roster\n");
        for (int i = 0; i < 9; i++) {
            fprintf(file, "%s vs. %s\n", roster1[i].name, roster2[i].name);
        }
        fprintf(file, "\n");
    
        // Write match results grid
        fprintf(file, "Match Results\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fprintf(file, "%c ", results[i][j] == 1 ? '1' : (results[i][j] == 2 ? '2' : 'D'));
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    
        // Write match outcome
        fprintf(file, "Winner: %s\n", winner);
        fprintf(file, "Type of Win: %s\n", winType);
    
        fclose(file);
        
    	// Print confirmation message
        printf("[Match results saved successfully to %s]\n\n", filename);
    }
}

/**
 * Returns the name of the element corresponding to the given index.
 * @param element An integer representing the index of the element.
 *                Valid indices range from 0 to 7, corresponding to:
 *                0: Fire, 1: Water, 2: Grass, 3: Earth,
 *                4: Air, 5: Electric, 6: Ice, 7: Metal.
 * @return A pointer to a string representing the name of the element.
 * @pre The `element` parameter must be in the range [0, 7].
 */
char *checkElement(int element)
{
	char *elements[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"}; // Array of element names
	
	return elements[element];
}

/**
 * Finds the index of a given element name in the predefined list of elements.
 * @param element A string representing the name of the element.
 *                Valid element names are: "Fire", "Water", "Grass", "Earth",
 *                "Air", "Electric", "Ice", "Metal".
 * @return The index of the element in the list (0 to 7), or -1 if the element is not found.
 * @pre The input string `element` must not be NULL.
 */
int checkElementIndex(char* element)
{
	int index = 0;
	
	// Array of predefined element names
	char *elements[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
	
	// Loop through the list of elements to find a match
	for(int i = 0; i < 8; i++){
		
		if(strcmp(element, elements[i]) == 0){
			
			index = i;
		}
	}
	
	return index;
}

/**
 * Counts the number of battle pets stored in a file.
 * Each battle pet entry spans 5 lines in the file.
 * 
 * @param filename The name of the file containing the battle pet data.
 * @param maxPets A pointer to an integer where the total number of battle pets will be stored.
 * @return None
 * @pre The `filename` must point to a valid file, and `maxPets` must be a valid pointer.
 */
void countBattlePets(const char *filename, int* maxPets)
{
	char line[500]; // Buffer for reading lines from the file
	int lineCount = 0; // Tracks the total number of lines read
	int battlePetCount = 0; // Tracks the number of battle pets
	
	FILE *file = fopen(filename, "r"); // Open the file for reading
	 
	// Check if the file was successfully opened
	if (!file) {
        perror("Error opening file");
        return;
    }
	
	// Read the file line by line
	while(fgets(line, sizeof(line), file)){
		
		lineCount++;
		
		// Every 5th line corresponds to a complete battle pet entry
		if(lineCount % 5 == 0){
			
			battlePetCount++;
		}
	}
	
	fclose(file); // Close the file after reading
	
	*maxPets = battlePetCount; // Update the output parameter with the total count
}

/**
 * Loads battle pets from a file and populates the provided array of `bpet` structures.
 * @param filename The name of the file containing battle pet data.
 *                 Each battle pet entry is expected to have the following structure in the file:
 *                 - Line 1: Battle pet name
 *                 - Line 2: Element 
 *                 - Line 3: Description of the battle pet
 *                 - Line 4: Number of matches participated
 *                 - Line 5: (Empty line as a separator)
 * @param battlePets An array of `bpet` structures where the loaded data will be stored.
 *                   The array must have sufficient capacity to store all battle pets in the file.
 * @return None
 * @pre The `filename` must point to a valid file containing battle pet data in the expected format.
 *      The `battlePets` array must be properly initialized and large enough to hold the data.
 */
void loadBattlePets(const char *filename, bpet battlePets[])
{
	char temp[50]; // Temporary buffer for storing strings
	
	FILE *file = fopen(filename, "r"); // Open the file for reading
	
	if (!file) {
        perror("Error opening file");
        return;
    }

    char line[400]; // Buffer for reading lines from the file
    int index = 0; // Index for the battlePets array
	
	// Read the file line by line
    while (fgets(line, sizeof(line), file)){
        
        // Skip empty lines
        if (strlen(line) <= 1) continue;  
        
        // Line 1: Battle pet name
        strcpy(battlePets[index].name, strtok(line, "\n"));

        // Line 2: Element name (converted to index)
        fgets(line, sizeof(line), file);
        strcpy(temp, strtok(line, "\n"));
        battlePets[index].element = checkElementIndex(temp);

        // Line 3: Battle pet description
        fgets(line, sizeof(line), file);
        strcpy(battlePets[index].desc, strtok(line, "\n"));

        // Line 4: Number of matches participated
        fgets(line, sizeof(line), file);
        battlePets[index].matches = atoi(line);

        index++;
    }
    
    fclose(file);
}

/**
 * Displays a header for the "Add BattlePet" section in the console.
 * @return None
 * @pre None
 */
void displayCreateBattlePetHeader()
{
	printf("=========================\n");
    printf("\033[1;33m  CREATE YOUR BATTLEPET\033[0m\n");
    printf("=========================\n");
    printf("\n");
}

/**
 * Adds a new battle pet to the specified file and updates the battlePets array.
 * @param battlePets An array of `bpet` structures where the newly created battle pet will be added.
 * @param fileName The name of the file where the new battle pet's data will be appended.
 * @return None
 * @pre The `fileName` must be a valid, writable file. The `battlePets` array must be initialized.
 */
void addBattlePet(bpet battlePets[], const char *fileName)
{
	FILE *file = fopen(fileName, "a"); // Open file in append mode to add new battle pet
	
	char name[50], desc[300];
	int element;
	int confirm = 0;
	
	do{
		clrscr();
    	displayCreateBattlePetHeader(); // Display header for battle pet creation
    	
    	// Prompt for battle pet name
		printf("\033[1;33mInput the name of your Battlepet: \033[0m");
		scanf("%49s", name);
		getchar();
		
		clrscr();
		
		displayCreateBattlePetHeader();
		printf("Name: %s\n\n", name);
		
		// Prompt for battle pet element
		printf("\033[1;33mInput the element of your Battlepet:\033[0m\n[0]Fire\n[1]Water\n[2]Grass\n[3]Earth\n[4]Air\n[5]Electric\n[6]Ice\n[7]Metal\n\n");
		scanf("Select your Input: %d", &element);
		getchar();
		getchar();
		
		clrscr();
		displayCreateBattlePetHeader();
		printf("Name: %s\n", name);
		printf("Element: %s\n\n", checkElement(element));
		
		// Prompt for battle pet description
		printf("\033[1;33mWrite a short description for your Battlepet: \033[0m");
		fgets(desc, sizeof(desc), stdin);
		desc[strcspn(desc, "\n")] = 0;
		
		clrscr();
		displayCreateBattlePetHeader();
		printf("Name: %s\n", name);
		printf("Element: %s\n", checkElement(element));
		printf("Description: %s\n\n", desc);
		
		// Confirm the entered details
		printf("\033[1;33mIs the battlepets info correct?\n[1] Yes\n[0] No\n>> \033[0m");
		scanf("%d", &confirm);
	
	} while(confirm == 0);
	
	// Save the new battle pet to the file
	fprintf(file, "%s\n%s\n%s\n0\n\n", name, checkElement(element), desc);
	
	clrscr();
	displayCreateBattlePetHeader();
	printf("Name: %s\n", name);
	printf("Element: %s\n", checkElement(element));
	printf("Description: %s\n", desc);
	
	// Reload battle pets to update the array with the newly added pet
    loadBattlePets(fileName, battlePets);
    
	printf("\n\033[1;32m[Battlepet saved succesfully]\033[0m\n\n");
	printf("Press Enter to continue...");
    getchar(); 
	getchar(); 
	
	clrscr();
	
	fclose(file); // Close the file after writing
	 
}

/**
 * Edits the name of a specific battle pet in the specified file.
 * @param newName The new name to assign to the battle pet.
 * @param battlePetName The current name of the battle pet to be updated.
 * @param fileName The name of the file containing the battle pets' data.
 * @return None
 * @pre The `fileName` must exist and be readable/writable. `newName` and `battlePetName` must be valid strings.
 */
void editBattlePetName(const char *newName, const char *battlePetName, const char *fileName)
{
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	char line[256];
	int foundName = 0;
	int nameUpdated = 0;
	
	while(fgets(line, sizeof(line), file)){
		// Check if the current line matches the battle pet's name
	    if (strncmp(line, battlePetName, strlen(battlePetName)) == 0 && line[strlen(battlePetName)] == '\n'){
	    	
	        fprintf(tempFile, "%s", newName); 
	        nameUpdated = 1;
	        
	    } else {
	        fprintf(tempFile, "%s", line);
	    }
	}
	
	fclose(file);
	fclose(tempFile);
	
	if (nameUpdated){
		
		// Replace the original file with the updated temp file
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        printf("\n\n\033[1;32m[Name updated successfully] \033[0m\n\n");
        
    } else {
        printf("Name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temporary file
    }
}

/**
 * Edits the element of a specific battle pet in the specified file.
 * @param newElementCode The new element code to assign to the battle pet.
 * @param battlePetName The current name of the battle pet whose element needs to be updated.
 * @param fileName The name of the file containing the battle pets' data.
 * @return None
 * @pre The `fileName` must exist and be readable/writable. `battlePetName` must be a valid string.
 */
void editBattlePetElement(int newElementCode, const char *battlePetName, const char *fileName)
{
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	char line[256];
	int foundElement = 0;
	int elementUpdated = 0;
	char newElement[30];
	
	// Get the new element name based on the provided code
	strcpy(newElement, checkElement(newElementCode));
	
	while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0'; // Remove trailing newline character
        }

        if (foundElement){
        	// Replace the element with the new element
            fprintf(tempFile, "%s\n", newElement);
            elementUpdated = 1;
            foundElement = 0; // Reset the flag after updating
            
        } else if (strcmp(line, battlePetName) == 0) {
        	// Match the battle pet name
            fprintf(tempFile, "%s\n", line); 
            foundElement = 1; // Set the flag to update the next line
            
        } else {
            // Write the line as-is
            fprintf(tempFile, "%s\n", line);
        }
    }
	
	fclose(file);
	fclose(tempFile);
	
	if(elementUpdated){
		// Replace the original file with the updated temp file
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        printf("\n\n\033[1;32m[Element updated successfully] \033[0m\n\n");
        
    } else {
        printf("Name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temporary file
    }
}

/**
 * Edits the description of a specific battle pet in the specified file.
 * @param newDesc The new description to assign to the battle pet.
 * @param battlePetName The current name of the battle pet whose description needs to be updated.
 * @param fileName The name of the file containing the battle pets' data.
 * @return None
 * @pre The `fileName` must exist and be readable/writable. `battlePetName` must be a valid string.
 */
void editBattlePetDesc(const char *newDesc, const char *battlePetName, const char *fileName)
{
	FILE *file = fopen(fileName, "r");
    FILE *tempFile = fopen(TEMP_FILE, "w");
    
    char line[256];
    int foundName = 0;
    int lineCounter = 0;
    int descUpdated = 0;

    while (fgets(line, sizeof(line), file)){
    	
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0'; // Remove trailing newline character
        }

        if(foundName && lineCounter == 1){
        	
            fprintf(tempFile, "%s", newDesc);
            descUpdated = 1;
            foundName = 0; // Reset the flag after updating
            lineCounter = 0;
            
        } else if (foundName){
        	 // Update the description on the next line after the name
            fprintf(tempFile, "%s\n", line);
            lineCounter++;
            
        } else if (strcmp(line, battlePetName) == 0){
        	// Match the battle pet name
            fprintf(tempFile, "%s\n", line);
            foundName = 1;
            lineCounter = 0;
            
        } else {
        	// Write the line as-is
            fprintf(tempFile, "%s\n", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (descUpdated) {
    	// Replace the original file with the updated temp file
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
        	
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        
        printf("\n\033[1;32m[Description updated successfully]\033[0m\n\n");
        
    } else {
    	
        printf("Battle pet name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temp file if no updates were made
    }
}

/**
 * Increments the match count of a specified battle pet in the file.
 * @param battlePetName The name of the battle pet whose matches need to be incremented.
 * @param fileName The name of the file containing the battle pets' data.
 * @return None
 * @pre The file specified by `fileName` must exist and be accessible.
 */
void incrementBattlePetMatches(char *battlePetName, const char *fileName)
{	
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	
	char line[256];
    int foundBattlePet = 0;
    int lineCounter = 0; // To track the line offset for matches

    while (fgets(line, sizeof(line), file)) {
        if (foundBattlePet) {
            lineCounter++;
            if (lineCounter == 3) {
                // This is the matches line to increment
                int matches = atoi(line);  // Convert to integer
                matches++; // Increment match count
                fprintf(tempFile, "%d\n", matches); // Write updated value
                foundBattlePet = 0;        // Reset the flag
                lineCounter = 0;
            } else {
                fprintf(tempFile, "%s", line); // Write as-is
            }
        } else {
            char *lineWithoutNewline = strtok(line, "\n"); // Remove newline from the read line
            fprintf(tempFile, "%s\n", lineWithoutNewline ? lineWithoutNewline : "");
            
            // Check if this line matches the battle pet name
            if (strcmp(line, battlePetName) == 0) {
                foundBattlePet = 1;   // Set the flag to track the next 4 lines
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated file
    if (remove(fileName) != 0) {
        perror("Error removing original file");
        return;
    }

    if (rename(TEMP_FILE, fileName) != 0) {
        perror("Error renaming temporary file");
        return;
    }
}

/**
 * Deletes a BattlePet entry from a file if the given name matches.
 * @param battlePetName Pointer to a string containing the name of the BattlePet to be deleted.
 * @param fileName Pointer to a string representing the file name containing the BattlePet records.
 * @return None
 * @pre The file specified by `fileName` must exist and be accessible for reading and writing.
 *      The BattlePet name to delete must be terminated with a newline character in the file.
 */
void deleteBattlePet(char *battlePetName, const char *fileName)
{
	FILE *file = fopen(fileName, "r"); // Open the file in read mode
	FILE *tempFile = fopen(TEMP_FILE, "w");
	char line[256]; // Buffer to hold each line read from the file
	int foundName = 0; // Flag to track if the BattlePet name has been found
	
	// Read each line from the original file
	while (fgets(line, sizeof(line), file)){
		
		// If the name was found, skip the next 4 lines
        if (foundName > 0 && foundName < 5) {
            foundName++; // Increment counter to track skipped lines
        } else if (strncmp(line, battlePetName, strlen(battlePetName)) == 0 && line[strlen(battlePetName)] == '\n') { // Check if the current line matches the BattlePet name
            foundName = 1;
        } else { // Otherwise, write the line to the temporary file
            fputs(line, tempFile);
        }
    }
	
	fclose(file);
	fclose(tempFile);
	
	// If the BattlePet name was found, update the original file
	if (foundName > 0){
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        printf("\n\033[1;32mDeleted BattlePet Successfully.\033[0m\n");
        printf("Press Enter to Continue");
        getchar();
        getchar();
        
    } else {
        printf("Name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temporary file
    }
}

/**
 * Allows the user to edit attributes of BattlePets from a given file.
 * The user can modify the name, element, or description of a selected BattlePet.
 * @param battlePets Array of BattlePet structures to hold the loaded BattlePet data.
 * @param maxPets Maximum number of BattlePets allowed in the array.
 * @param fileName Pointer to a string representing the file name containing BattlePet records.
 * @return None
 * @pre The `battlePets` array must have sufficient memory allocated to hold `maxPets` BattlePets.
 *      The `fileName` must point to a valid file containing BattlePet data.
 */
void editBattlePets(bpet battlePets[], int maxPets, const char *fileName)
{
	int nInput; // Index of the BattlePet to edit
	int modifyInput; // Option for the attribute to modify
	char newName[50]; // Buffer for the new name
	char newDesc[300]; // Buffer for the new description
	int newElement; // New element value
	int mainLoop = 1;
	
	do{
		clrscr();
		loadBattlePets(fileName, battlePets); // Load BattlePets data from file
		displayBattlePets(battlePets, maxPets, fileName); // Display the current BattlePets 
		printf("\n\033[1;33mWhich Battlepet would you like to edit?\033[0m\n>> ");
		scanf("%d", &nInput); // Get user input for BattlePet index
		getchar();
		
		if(nInput >= 0 && nInput < maxPets){
			
			int loop = 1;
			int nInvalid = 1;
			
			do{
				clrscr();
				accessBattlePets(battlePets, nInput); // Access details of the selected BattlePet
				printf("\033[1;33mWhat would you like to modify?\n[1] Name\n[2] Element\n[3] Description\033[0m\n>> ");
				scanf("%d", &modifyInput);
				
				clrscr();
				accessBattlePets(battlePets, nInput);
			
				switch(modifyInput) {
					case 1: // Modify the name
						printf("\033[1;33mInput New Name (MAX OF 50 CHARACTERS): \033[0m");
						getchar();
						fgets(newName, sizeof(newName), stdin);
						
						editBattlePetName(newName, battlePets[nInput].name, fileName); // Update the name in the file

						printf("Press Enter to continue...");
   						getchar(); 
						
						loop = 0;
						mainLoop = 0;
						break;
						
					case 2:	// Modify the element
						do{
							printf("[0] Fire  [1] Water  [2] Grass  [3] Earth  [4] Air  [5] Electric  [6] Ice  [7] Metal\n\n");
							printf("\033[1;33mInput New Element: \033[0m");
							scanf("%d", &newElement); // Get new element value
							getchar();
							
							if(newElement >= 0 && newElement <= 7){
								
								nInvalid = 0;
								editBattlePetElement(newElement, battlePets[nInput].name, fileName); // Update element in the file
								printf("Press Enter to continue...");
   								getchar(); 
   								
							} else {
								clrscr();
								printf("\033[1;91mInvalid Input.\033[0m\n\n");
							}
							
							loop = 0;
							mainLoop = 0;
							
						} while(nInvalid);
						break;
						
					case 3: // Modify the description
						printf("\033[1;33mInput New Description (MAX OF 300 CHARACTERS): \033[0m");
						getchar();
						fgets(newDesc, sizeof(newDesc), stdin);
						
						editBattlePetDesc(newDesc, battlePets[nInput].name, fileName); // Update description in the file
						printf("Press Enter to continue...");
   						getchar(); 
						
						loop = 0;
						mainLoop = 0;
						break;
						
					default:
						printf("Invalid Input.\n");
						break;
				}
				
			} while (loop);
			
		} else {
			clrscr();
			printf("\033[1;91m[WARNING: INVALID INPUT]\033[0m\n\n");
			mainLoop = 1;
		}
	} while(mainLoop);
}

/**
 * Retrieves the password associated with a player's name from a file.
 * @param playerName Pointer to a string containing the player's name to search for in the file.
 * @return Pointer to a static character array containing the password if found, "none" if not found,
 *         or an error message if the file could not be opened.
 * @pre The file "passwords.txt" must exist in the working directory and contain player names
 *      followed by their corresponding passwords on separate lines.
 */
char* getPassword(const char* playerName)
{
    static char password[256]; // Static to ensure memory stays valid after return
    char line[256];
    
    FILE* file = fopen("passwords.txt", "r"); // Open the file in read mode
    int foundPlayer = 0;

    if (file == NULL) {
        strcpy(password, "Error: Unable to open file.");
    } else {
        while (fgets(line, sizeof(line), file) != NULL) {
            // Remove newline character from the line
            line[strcspn(line, "\n")] = '\0';
			
			// If the previous line matched the player name, this line is the password
            if (foundPlayer) {
                strcpy(password, line);
                foundPlayer = 0;
            } else if (strcmp(line, playerName) == 0) {
                foundPlayer = 1;
            }
        }

        if (!foundPlayer && password[0] == '\0') {
        	 // If player name was not found and no password was set, return "none"
            strcpy(password, "none");
        }

        fclose(file);
    }

    return password;
}

/**
 * Adds a new player name and password to the passwords file.
 * @param playerName Pointer to a string containing the player's name to add to the file.
 * @param newPassword Pointer to a string containing the password to associate with the player name.
 * @return None
 * @pre The file "passwords.txt" must be accessible for appending. Both `playerName` and `newPassword`
 *      must be valid non-empty strings.
 */
void addNewPassword(const char *playerName, const char *newPassword){
	
	FILE* file = fopen("passwords.txt", "a"); // Open the file in append mode

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "\n%s\n%s\n", playerName, newPassword); // Append player name and password
    fclose(file);
    
    printf("\033[1;32m[Password has been added successfully]\033[0m");
}

/**
 * Handles password input and validation for a given player.
 * If the player has not set a password, prompts them to create one.
 * @param playerName Pointer to a string containing the player's name.
 * @param playerAccess Pointer to an integer that will be set to 1 if access is granted, 0 otherwise.
 * @return None
 * @pre The `playerName` must be a valid string. The `playerAccess` pointer must point to a valid integer.
 *      The password file should be accessible by the `getPassword` function.
 */
void inputPassword(const char* playerName, int *playerAccess){
	
	char* password = getPassword(playerName); // Retrieve the password for the player
	char inputPass[50]; // Buffer for the user's entered password
	
	if(strcmp("none", password) == 0){ // Check if no password is set for the player

		char newPassword[50];
		clrscr();
		
		printf("=========================\n");
	    printf("\033[1;33m      SAVE A ROSTER       \033[0m\n");
	    printf("=========================\n\n");
		
		// Prompt the player to set a new password
		printf("[Player %s has not set their password]\n\n", playerName);
		printf("Input New Password (Must be alphanumeric characters only): ");
		scanf("%30s", newPassword);
		addNewPassword(playerName, newPassword);
		*playerAccess = 1;  // Grant access
		
	} else {
		
		int count = 0; // Tracks the number of failed attempts
		
		do{
			clrscr();
			printf("=========================\n");
		    printf("\033[1;33m      SAVE A ROSTER       \033[0m\n");
		    printf("=========================\n\n");
			
			printf("Player: %s\n\n", playerName);
			printf("Input Password: ");
			scanf("%s", &inputPass); // Read the entered password
			
			if(strcmp(inputPass, password) == 0){ // Check if the entered password is correct
				*playerAccess = 1; // Grant access
				
			} else {
				
				count++; // Increment failed attempt counter
				printf("\n\n\033[1;91mIncorrect Password %d tries remaining\033[0m\n", 4 - count);
				printf("Press Enter to Continue...");
				getchar();
				getchar();
			}
			
		} while(count < 4 && *playerAccess != 1);  // Allow up to 4 attempts
	}
}

/**
 * Saves a player's roster to a file after verifying their password.
 * @param players Array of Player structures representing the available players.
 * @param playerCount Number of players in the `players` array.
 * @param battlePets Array of bpet structures representing all available battle pets.
 * @param maxPets Maximum number of battle pets available.
 * @param roster Array of bpet structures representing the player's selected roster.
 * @return None
 * @pre The `players` array must contain at least one player. The `battlePets` array must be properly initialized.
 *      The directory "saved_roster" must exist in the working directory.
 *      The `inputPassword` and `createRoster` functions must be implemented and operational.
 */
void saveRoster(Player players[], int playerCount, bpet battlePets[], int maxPets, bpet roster[])
{
    int selectedPlayerIndex = -1; // Stores the selected player's index
    char filePath[100]; // Buffer to hold the file path
    FILE *file;

    clrscr();
    
    printf("=========================\n");
    printf("\033[1;33m      SAVE A ROSTER       \033[0m\n");
    printf("=========================\n\n");
    printf("Select a player to save a roster for:\n");

    
    for (int i = 0; i < playerCount; i++) {
        printf("[%d] %s\n", i + 1, players[i].username);
    }

    printf("\n>> ");
    scanf("%d", &selectedPlayerIndex);
    getchar(); 

    
    if (selectedPlayerIndex < 1 || selectedPlayerIndex > playerCount){
    	// Validate the selection
        printf("\033[1;91mInvalid selection. Press Enter to continue...\033[0m");
        getchar();
    } else {
    	
    	clrscr();
    	int playerAccess = 0; // Tracks whether the player has granted access

        selectedPlayerIndex--; // Adjust for zero-based indexing
        
		inputPassword(players[selectedPlayerIndex].username, &playerAccess); // Verify player password
		
		if(playerAccess == 1){  // If access is granted
       		// Generate the file path for saving the roster
	        snprintf(filePath, sizeof(filePath), "saved_roster/%s.txt", players[selectedPlayerIndex].username);
	
	        createRoster(battlePets, maxPets, roster); // Generate the player's roster
	
	        file = fopen(filePath, "w"); // Open the file for writing
	        if (!file) {
	            printf("Error: Could not save roster.\n");
	        } else {
	            for (int i = 0; i < 9; i++){
	            	 // Write the roster to the file
	                fprintf(file, "%s\n", roster[i].name);
	            }
	            fclose(file);
	
	            // Confirm success to the user
	            printf("\n\n\033[1;32m[Roster saved successfully for %s to %s]\033[0m\n\n", players[selectedPlayerIndex].username, filePath);
	            printf("Press Enter to continue...");
	            getchar(); 
	            getchar(); 
	        }
	    }
    
	}

    clrscr(); 
}

/**
 * Imports battle pets data from a specified file and updates the battle pets array and count.
 * @param battlePets Array of bpet structures to store the imported battle pets.
 * @param maxPets Maximum number of battle pets allowed (updated based on the imported file).
 * @param fileName Pointer to a string where the name of the imported file will be stored.
 * @return None
 * @pre The `battlePets` array must be initialized with enough capacity to store up to `maxPets` battle pets.
 *      The file specified by the user must exist and contain valid battle pet data.
 */
void importBattlePets(bpet battlePets[], int maxPets, char *fileName)
{
	char tempFileName[50];
	
    FILE *file;
    int fileExists = 0; // Flag to track if the file exists
    
    printf("=========================\n");
    printf("\033[1;33m    IMPORT BATTLEPETS       \033[0m\n");
    printf("=========================\n\n");
    
    printf("Input the name of the txt file you want to import\n");
    printf("\033[1;91m[WARNING] You must include the .txt extension\033[0m\n\n");
    printf(">> ");
    scanf("%49s", tempFileName); // Get the file name from the user

        
    file = fopen(tempFileName, "r"); // Attempt to open the file
    
    	if (file) {
            fclose(file);  // File exists, close it
            fileExists = 1; // Set flag to true
        } else {
            printf("\033[1;91mError: File '%s' does not exist\033[0m\n\n", tempFileName);
        }
    
	if(fileExists == 1){ // If the file exists
	    strcpy(fileName, tempFileName);  // Update the fileName with the valid file name

	    loadBattlePets(fileName, battlePets); // Load battle pets data from the file
	    countBattlePets(fileName, &maxPets); // Update the count of battle pets
	    
	    printf("\033[1;32m'%s' has been loaded.\033[0m\n\n", fileName);
	}
	
    printf("\nPress Enter to Continue");
    getchar();
    getchar();
}

/**
 * Sorts and displays the top players based on their win/loss/draw records and usernames.
 * @param players Array of Player structures representing the players.
 * @param playerCount Number of players in the `players` array.
 * @return None
 * @pre The `players` array must be properly initialized with valid player data. 
 *      The `displayTopPlayers` function must be implemented to handle the display of sorted players.
 */
void printTopPlayers(Player players[], int playerCount)
{	
	Player sortedPlayers[playerCount]; // Array to hold the sorted players
	
	// Copy players to the sortedPlayers array
	for(int i = 0; i < playerCount; i++){
		
		sortedPlayers[i] = players[i];	
	}
	
	// Selection sort algorithm to sort players
	for (int j = 0; j < playerCount - 1; j++){
	 	
    	int best = j; // Index of the best player so far
        
        for (int k = j + 1; k < playerCount; k++) {
            
            if (sortedPlayers[k].wins > sortedPlayers[best].wins){
            	// Update best if a player with more wins is found
                best = k;
            } 
            
            else if (sortedPlayers[k].wins == sortedPlayers[best].wins){
                if (sortedPlayers[k].losses < sortedPlayers[best].losses){
                	// If wins are equal, compare losses
                    best = k; 
                } 
                
                else if (sortedPlayers[k].losses == sortedPlayers[best].losses){
                	// If losses are also equal, compare draws
                    if (sortedPlayers[k].draws < sortedPlayers[best].draws){
                        best = k;
                    } 
                    
                    else if (sortedPlayers[k].draws == sortedPlayers[best].draws){
                    	// If losses are also equal, compare draws (lower draws are better)
                        if (sortedPlayers[k].username < sortedPlayers[best].username){
                            best = k;
                        }
                    }
                }
            }
        }
        
        // Swap the current player with the best player found in this iteration
        if (j != best) {
            Player temp = sortedPlayers[j];
            sortedPlayers[j] = sortedPlayers[best];
            sortedPlayers[best] = temp;
        }
    }

    displayTopPlayers(sortedPlayers);
}

/**
 * Displays the top 5 players from a sorted list of players.
 * @param sortedPlayers Array of Player structures sorted by ranking criteria (wins, losses, draws, username).
 * @return None
 * @pre The `sortedPlayers` array must contain at least 5 valid Player structures.
 */
void displayTopPlayers(Player sortedPlayers[])
{
	int wins, losses, draws; // Variables to store player stats temporarily
	
	// Loop through the top 5 players in the sorted array
	printf("\033[1;33mTop 5 Players \033[0m\n");
	for(int i = 0; i < 5; i++){
		// Extract stats for clarity in printin
		wins = sortedPlayers[i].wins;
		losses = sortedPlayers[i].losses;
		draws = sortedPlayers[i].draws;
		// Print player rank, username, and stats
		printf("[%d] %s (W: \033[1;32m%d\033[0m, L: %d, D: %d)\n", i + 1, sortedPlayers[i].username, wins, losses, draws);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	getchar();
}

/**
 * Sorts and displays the top battle pets based on the number of matches played.
 * @param battlePets Array of bpet structures representing the battle pets.
 * @param maxPets Number of battle pets in the `battlePets` array.
 * @return None
 * @pre The `battlePets` array must be properly initialized with valid battle pet data. 
 *      The `displayTopPets` function must be implemented to handle the display of sorted battle pets.
 */
void printTopBattlePets(bpet battlePets[], int maxPets)
{
	bpet sortedPets[maxPets]; // Array to hold the sorted battle pets
	
	// Copy battle pets to the sortedPets array
	for(int i = 0; i < maxPets; i++){
		
		sortedPets[i] = battlePets[i];
	}
	
	// Selection sort algorithm to sort pets based on matches played
	for(int j = 0; j < maxPets - 1; j++){
		
		int min = j;
		
		for(int k = j + 1; k < maxPets; k++){
			
			if(sortedPets[min].matches < sortedPets[k].matches){
				
				min = k;
			}
			
		}
		
		// Swap the current pet with the pet having the highest matches in this iteration
		if(j != min){
			
			bpet temp = sortedPets[j];
			sortedPets[j] = sortedPets[min];
			sortedPets[min] = temp;
		}
	}
	
	displayTopPets(sortedPets);
}

/**
 * Displays the top 5 battle pets from a sorted list.
 * @param sortedPets Array of bpet structures sorted by the number of matches played in descending order.
 * @return None
 * @pre The `sortedPets` array must contain at least 5 valid bpet structures with initialized fields.
 */
void displayTopPets(bpet sortedPets[])
{
	printf("\033[1;33mTop 5 BattlePets:\033[0m\n");
	
	// Loop through the top 5 pets in the sorted array
	for(int i = 0; i < 5; i++){
		
		printf("[%d] %s (%d matches)\n", i + 1, sortedPets[i].name, sortedPets[i].matches);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	getchar();
}

void howToPlay(){
	
	printf("\033[1;33mAbout BattlePets \033[0m\n\n");
	printf("BattlePets is a text-based game that draws inspiration from Battleship, Pokemon, and Tic-Tac-Toe mechanics. Players\n");
	printf("are to form a 3x3 BattlePet roster wherein the arrangement is secret to the other player (inspired by Battleship).\n");
	printf("Each BattlePet fights its counterpart in the same grid position (inspired by Pokemon). The overall match winner \n");
	printf("is determined based on who has the most BattlePet wins out of the nine battles. However, a lucky win may be declared \n");
	printf("if the arrangement of a player's BattlePet wins is horizontal, vertical, or diagonal (inspired by Tic-Tac-Toe), \n");
	printf("regardless of whether the opposing player has the most wins in total for that match.\n\n");
	printf("Press Enter to Continue..");
	getchar();
	
}

int main()
{
	int maxPets = 0; // Variable to store the total number of battle pets
	int playerCount = 0; // Variable to store the total number of players
	char fileName[50] = "competdium.txt"; // Default file name for battle pets
	
	Player players[MAX_PLAYERS]; // Array to store player data
	bpet battlePets[30]; // Array to store battle pet data

	// Count the number of battle pets in the file and load them into the array
	countBattlePets(fileName, &maxPets);
	loadBattlePets(fileName, battlePets);
	
	// Load player data from the respective file
	loadPlayers(players, &playerCount);
	clrscr();
 
	displayLanding(1); // Display the landing page of the application
	
    startMenu(battlePets, players, maxPets, playerCount, fileName); // Start the main menu of the application

  return 0;
}

/**
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/we have not copied in part or whole or otherwise plagiarized the work of
 * other students and/or persons.
 *
 * GARCIA, Hadjj (DLSU ID# <12411620>)
 * CUSTODIO, Justin Miguel (DLSU ID# <12410454>)
 */
