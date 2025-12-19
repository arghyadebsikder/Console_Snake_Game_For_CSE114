//   
//             ██████╗ ██████╗ ███╗   ██╗███████╗ ██████╗ ██╗     ███████╗
//            ██╔════╝██╔═══██╗████╗  ██║██╔════╝██╔═══██╗██║     ██╔════╝
//            ██║     ██║   ██║██╔██╗ ██║███████╗██║   ██║██║     █████╗
//            ██║     ██║   ██║██║╚██╗██║╚════██║██║   ██║██║     ██╔══╝
//            ╚██████╗╚██████╔╝██║ ╚████║███████║╚██████╔╝███████╗███████╗
//             ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚══════╝╚══════╝
// 
//  ███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗       ██████╗  █████╗ ███╗   ███╗███████╗  
//  ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝      ██╔════╝ ██╔══██╗████╗ ████║██╔════╝  
//  ███████╗██╔██╗ ██║███████║█████╔╝ █████╗        ██║  ███╗███████║██╔████╔██║█████╗    
//  ╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝        ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝    
//  ███████║██║ ╚████║██║  ██║██║  ██╗███████╗      ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗  
//  ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝       ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝  
// 
//                     C O N S O L E   S N A K E   G A M E
//
//   Language   : C (Console Application)
//   Platform   : Windows (WinAPI + ANSI)
//   Type       : Classic Snake Game
//
//   Description:
//   A fully interactive console-based Snake Game featuring
//   multiple difficulty levels, persistent high scores,
//   smooth cursor control, and real-time keyboard input.
//

#include <stdio.h>      // Standard input-output functions (printf, scanf)
#include <conio.h>      // Console I/O functions (_kbhit, _getch)
#include <stdlib.h>     // Standard utilities (rand, srand, exit)
#include <time.h>       // Time functions for random seed
#include <windows.h>    // Windows-specific APIs (Sleep, Beep, cursor control)
#include <string.h>     // String manipulation functions (strlen)
#include <stdbool.h>    // Boolean data type (true/false)

/* ========================= FUNCTION DECLARATIONS ========================= */
/* Declaring all functions before main so compiler knows they exist */

void setup();                       // Initializes game and UI
void welcomeMessage();              // Displays welcome screen
void printInGameScreen();            // Renders the game frame
void gameEngine();                  // Core game loop
void setCursor(short x, short y);   // Moves console cursor
void hideCursor();                  // Hides blinking cursor
void inGameInput();                 // Reads keyboard input
void title();                       // Displays game title and difficulty
void snakeMovement();               // Updates snake position
void scorePrint();                  // Displays score info
void levelChoose();                 // Difficulty selection menu
bool isGameOver();                  // Checks collision/game-over condition
void gameOverScreen();              // Game over menu
void food();                        // Handles food logic
void foodSetup();                   // Places initial food
bool overlapWithBody(int *x, int *y); // Checks food-body overlap
void pauseScreen();                 // Pause menu
void showCurrentHighScores();       // Displays stored high scores
void initializeFile();              // Loads high score file
void scoreSave();                   // Saves high scores

/* ========================= ANSI COLOR CODES ========================= */
/* Used to color console text output */

const char *RESET  = "\033[0m";     // Reset to default color
const char *PURPLE = "\033[1;36m";  // Purple-ish color
const char *CYAN   = "\033[1;36m";  // Cyan color
const char *YELLOW = "\033[1;33m";  // Yellow color
const char *GREEN  = "\033[1;32m";  // Green color
const char *RED    = "\033[1;31m";  // Red color
const char *BLUE   = "\033[1;34m";  // Blue color
const char *WHITE  = "\033[1;37m";  // White color

/* ========================= GAME BOUNDARIES ========================= */
/* Define playable area dimensions */

const int boundaryStartX = 0;
const int boundaryEndX   = 40;
const int boundaryStartY = 0;
const int boundaryEndY   = 20;

/* ========================= GAME OBJECT STRUCTURES ========================= */

// Snake head position
struct SnakeHead{
    int x;  // Horizontal position
    int y;  // Vertical position
};

// Snake tail/body segment
struct SnakeTail{
    int x;  // Body segment X
    int y;  // Body segment Y
};

// Food position
struct Food{
    int x;  // Food X
    int y;  // Food Y
};

/* ========================= GLOBAL GAME OBJECTS ========================= */

struct SnakeHead sh;        // Single snake head
struct SnakeTail st[200];   // Snake body (max length 200)
struct Food f;              // Food instance

/* ========================= GAME SYMBOLS ========================= */

char boundaryChar   = '#';  // Boundary wall
char snakeHeadChar  = '@';  // Snake head symbol
char snakeBodyChar  = '*';  // Snake body symbol
char foodChar       = '&';  // Food symbol
char spaceChar      = ' ';  // Empty space

/* ========================= GAME STATE VARIABLES ========================= */

char keyInput = 'w';        // Last movement key
int refreshRate = 500;      // Game speed (lower = faster)
int score;                  // Current score
int currentLevelArrow = 1;  // Selected difficulty
int gameOverArrow = 1;      // Game over menu selector
int maxScore[5] = {0};      // High scores for each level
int snakeLength = 3;        // Initial snake length
bool isPause;               // Pause state flag
bool isNewHighScore;        // High score flag


// -----------------------------
// start of main function
// -----------------------------
int main(){

    setup();    // initialize & start the game

    return 0;
}

/* setup()
   - Hides cursor, clears screen, loads scores, shows welcome screen,
     lets player choose level, then starts main game engine.
*/
void setup(){ //----------------------------------------------------------------------------------

    hideCursor(); // hide the blinking console cursor

    system("cls");          // clear screen (Windows)
    printf("%s", RESET);    // reset colors

    initializeFile();       // load/create high score file

    Sleep(200);             // small delay

    welcomeMessage();       // show welcome screen and wait for key

    levelChoose();          // choose difficulty level

    gameEngine();           // start the main game loop

}

/* initializeFile()
   - Reads high scores from "do_not_delete.arghya" if it exists.
   - If not, creates the file and writes default zeros.
*/
void initializeFile(){

    FILE *fp;
    fp = fopen("do_not_delete.arghya", "r");

    if(fp == NULL){
        fp = fopen("do_not_delete.arghya", "w");
        for(int i = 0; i < 5; i++){
            fprintf(fp, "%d\n", maxScore[i]); // write zeros initially
        }
        fclose(fp);
    }

    else{
        for(int i = 0; i < 5; i++){
            fscanf(fp, "%d", &maxScore[i]); // read 5 scores
        }
        // alternative reading method commented out
        // fscanf(fp, "%d%d%d%d%d", &maxScore[0], &maxScore[1], &maxScore[2], &maxScore[3], &maxScore[4]);
        fclose(fp);

    }

}

/* scoreSave()
   - Writes the maxScore[] array back to the file to persist high scores.
*/
void scoreSave(){

    FILE *fp;

    fp = fopen("do_not_delete.arghya", "w");
    for(int i = 0; i < 5; i++){
        fprintf(fp, "%d\n", maxScore[i]);
    }
    fclose(fp);
    
    // debug prints commented out
    // printf("Hello\n");
    // Sleep(1000);

}

/* welcomeMessage()
   - Draws a simple framed welcome screen and waits for user input.
   - Pressing 'h' opens the high score screen.
*/
void welcomeMessage(){ //--------------------------------------------------------------------------
    
    // strings to show on welcome screen
    char welcome[35] = "Welcome";
    char name[35] = "Console-Based Snake Game";
    char start[35] = "Press any key to start";
    char scoreShow[35] = "Press 'h' to see high score";

    // positions (used to center the strings)
    int firstLine = 7;
    int firstMargine = strlen(welcome) / 2 * -1;

    int secondLine = 8;
    int secondMargine = strlen(name) / 2 * -1;

    int thirdLine = 11;
    int thirdMargine = strlen(start) / 2 * -1;
    
    int forthLine = 13;
    int forthMargine = strlen(scoreShow) / 2 * -1;

    setCursor(boundaryStartX, boundaryStartY); // move cursor to top-left

    // draw frame + centered text
    for(int i = boundaryStartY; i <= boundaryEndY; i++){
        for(int j = boundaryStartX; j <= boundaryEndX; j++){

            // draw boundary
            if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                if(!(j & 1)){               // draw every other column to look nicer
                    printf("%s", BLUE);
                    printf("%c", boundaryChar);
                }
                else printf("%c", spaceChar);
            }

            // print welcome text lines at chosen rows/columns
            else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine){
                printf("%s", CYAN);
                printf("%s", welcome);
                j += strlen(welcome) - 1; // skip over printed chars
            }

            else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine){
                printf("%s", CYAN);
                printf("%s", name);
                j += strlen(name) - 1;
            }

            else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                printf("%s", CYAN);
                printf("%s", start);
                j += strlen(start) - 1;
            }

            else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 + forthMargine){
                printf("%s", CYAN);
                printf("%s", scoreShow);
                j += strlen(scoreShow) - 1;
            }

            else{
                printf("%c", spaceChar); // empty space inside frame
            }

        }
        printf("\n");
    }

    // wait for a key press, allow 'h' to show high scores
    while(1){

        Sleep(10);

        if(_kbhit()){
            int newInput = _getch();
            if(newInput == 0 || newInput == 224){
                newInput = _getch(); // handle special keys
            }
            
            if(newInput == 'h' || newInput == 'H'){
                showCurrentHighScores();
            }else break;

            Sleep(50);
        }
    }


}

/* showCurrentHighScores()
   - Draws high score screen for each difficulty and waits for a key to go back.
*/
void showCurrentHighScores(){

    char highScores[35] = "High Scores:";
    char easy[38] =      "Easy      :";
    char medium[38] =    "Medium    :";
    char hard[38] =      "Hard      :";
    char extreme[38] =   "Extreme   :";
    char legendary[38] = "Legendary :";
    char back[38] = "Press any key to back";

    int firstLine = 5;
    int firstMargine = strlen(highScores) / 2;

    int secondLine = 7;
    int secondMargine = strlen(easy) / 2 + 3;

    int thirdLine = 8;
    int thirdMargine = strlen(medium) / 2 + 3;
    
    int forthLine = 9;
    int forthMargine = strlen(hard) / 2 + 3;
    
    int fifthLine = 10;
    int fifthMargine = strlen(extreme) / 2 + 3;
    
    int sixthLine = 11;
    int sixthMargine = strlen(legendary) / 2 + 3;
    
    int seventhLine = 13;
    int seventhMargine = strlen(back) / 2;

    setCursor(boundaryStartX, boundaryStartY);

    // draw frame + scores
    for(int i = boundaryStartY; i <= boundaryEndY; i++){
        for(int j = boundaryStartX; j <= boundaryEndX; j++){

            if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                if(!(j & 1)){
                    printf("%s", BLUE);
                    printf("%c", boundaryChar);
                }
                else printf("%c", spaceChar);
            }

            else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 - firstMargine){
                printf("%s", CYAN);
                printf("%s", highScores);
                j += strlen(highScores) - 1;
            }

            else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 - secondMargine){
                printf("%s", CYAN);
                printf("%s %4d", easy, maxScore[0]); // Easy high score
                j += strlen(easy) + 4;
            }

            else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 - thirdMargine){
                printf("%s", CYAN);
                printf("%s %4d", medium, maxScore[1]); // Medium high score
                j += strlen(medium) + 4;
            }

            else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 - forthMargine){
                printf("%s", CYAN);
                printf("%s %4d", hard, maxScore[2]); // Hard high score
                j += strlen(hard) + 4;
            }
            
            else if(i == boundaryStartY + fifthLine && j == boundaryEndX / 2 - fifthMargine){
                printf("%s", CYAN);
                printf("%s %4d", extreme, maxScore[3]); // Extreme high score
                j += strlen(extreme) + 4;
            }
            
            else if(i == boundaryStartY + sixthLine && j == boundaryEndX / 2 - sixthMargine){
                printf("%s", CYAN);
                printf("%s %4d", legendary, maxScore[4]); // Legendary high score
                j += strlen(legendary) + 4;
            }
            
            else if(i == boundaryStartY + seventhLine && j == boundaryEndX / 2 - seventhMargine){
                printf("%s", CYAN);
                printf("%s", back);
                j += strlen(back) - 1;
            }

            else{
                printf("%c", spaceChar);
            }

        }
        printf("\n");
    }

    getch();             // wait for any key
    welcomeMessage();    // go back to welcome screen
}

/* gameEngine()
   - Main game loop. Initializes snake, places food, and repeats:
     check food, read input, move, draw, check game over.
*/
void gameEngine(){ //-------------------------------------------------------------------------------------
    
    sh.x = boundaryEndX / 2;  // start head in middle
    sh.y = boundaryEndY / 2;
    keyInput = 'w';           // initial direction (up)
    score = 0;
    snakeLength = 3;
    isPause = false;
    isNewHighScore = false;

    // initialize body segments right below the head
    for(int i = 0; i < snakeLength - 1; i++){
        st[i].x = sh.x;
        st[i].y = sh.y + i + 1;
    }

    foodSetup();            // place initial food
    printInGameScreen();    // draw first frame

    while(1){
        food();             // check if we found food and handle it
        inGameInput();      // read player input
        if(isPause) pauseScreen(); // handle pause if requested
        snakeMovement();    // move the snake
        printInGameScreen();// draw frame
        if(isGameOver()){   // check collision with wall or body
            scoreSave();    // persist high score if needed
            gameOverScreen();
            if(gameOverArrow == 1){
                setup();    // restart game
            } 
            else if(gameOverArrow == 2){
                exit(0);    // quit
            } 
        } 

        Sleep(refreshRate); // control game speed
    }
}

/* pauseScreen()
   - Displays a pause menu; resume with 'p', restart with 'r'.
*/
void pauseScreen(){

    char gamePausedString[35] = "Game Paused";
    char restart[38] = "Restart";
    char resume[38] = "Resume";

    int firstLine = 7;
    int firstMargine = strlen(gamePausedString) / 2 * -1;

    int secondLine = 10;
    int secondMargine = strlen(restart) / 2 * -1;

    int thirdLine = 9;
    int thirdMargine = strlen(resume) / 2 * -1;


    // system("cls");

    setCursor(boundaryStartX, boundaryStartY);

    while(1){

        Sleep(10);

        int currentInput = 0;

        if(_kbhit()){
            currentInput = _getch();

            if(currentInput == 'p' || currentInput == 'P'){
                system("cls");      // clear then resume
                isPause = false;
                return;
            }else if(currentInput == 'r' || currentInput == 'R'){
                setup();            // restart game entirely
            }

        }
        setCursor(boundaryStartY, boundaryStartX);

        title(); // show title line

        // draw pause menu frame & text
        for(int i = boundaryStartY; i <= boundaryEndY; i++){
            for(int j = boundaryStartX; j <= boundaryEndX; j++){

                if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                    if(!(j & 1)){
                        printf("%s", BLUE);
                        printf("%c", boundaryChar);
                    }
                    else printf("%c", spaceChar);
                }

                else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine){
                    printf("%s", CYAN);
                    printf("%s", gamePausedString);
                    j += strlen(gamePausedString) - 1;
                }

                else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine){
                    printf("%s", CYAN);
                    printf("%s", restart);
                    j += strlen(restart) - 1;
                }

                else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                    printf("%s", CYAN);
                    printf("%s", resume);
                    j += strlen(resume) - 1;
                }

                else{
                    printf("%c", spaceChar);
                }
            }

            printf("\n");
        }

    }
}

/* inGameInput()
   - Non-blocking input reader using _kbhit/_getch.
   - Accepts WASD or arrow keys. Prevents immediate reverse (invalid move).
   - 'p' sets pause flag.
*/
void inGameInput(){
    if(_kbhit()){
        int newInput = _getch();
        if(newInput == 0 || newInput == 224){
            newInput = _getch(); // handle arrow keys
        }
        
        // check allowed movement keys (w/a/s/d or arrow codes)
        if(newInput == 'w' || newInput == 72 || newInput == 'a' || newInput == 75 || newInput == 's' || newInput == 80 || newInput == 'd' || newInput == 77){
            // disallow 180-degree reversal (would hit own body)
            if((newInput == 'w' || newInput == 72) && (keyInput == 's' || keyInput == 80)) return;
            if((newInput == 's' || newInput == 80) && (keyInput == 'w' || keyInput == 72)) return;
            if((newInput == 'a' || newInput == 75) && (keyInput == 'd' || keyInput == 77)) return;
            if((newInput == 'd' || newInput == 77) && (keyInput == 'a' || keyInput == 75)) return;
            
            keyInput = newInput; // accept new direction
        }

        else if(newInput == 'p' || newInput == 'P') isPause = true; // pause request
    }
}

/* snakeMovement()
   - Move body segments to follow the head, then update head position based on keyInput.
   - Note: left/right use double increment/decrement to match console column spacing.
*/
void snakeMovement(){  //-------------------------------------------------------------------------------------
    
    // move body from tail to head: each segment takes previous segment's coord
    for(int i = snakeLength - 1; i > 0; i--){
        st[i].x = st[i - 1].x;
        st[i].y = st[i - 1].y;
    }

    // first body segment follows the head
    st[0].x = sh.x;
    st[0].y = sh.y;

    // update head position according to direction
    // arrow key codes: up=72, left=75, down=80, right=77
    if(keyInput == 'w' || keyInput == 72){
        sh.y--;            // move up
    }else if(keyInput == 'a' || keyInput == 75){
        sh.x--; sh.x--;    // move left (double step to match drawing spacing)
    }else if(keyInput == 's' || keyInput == 80){
        sh.y++;            // move down
    }else if(keyInput == 'd' || keyInput == 77){
        sh.x++; sh.x++;    // move right (double step)
    }

}

/* isGameOver()
   - Returns true if head hits the boundary or its own body.
*/
bool isGameOver(){
    // collision with walls
    if(sh.y == boundaryStartY || sh.y == boundaryEndY || sh.x == boundaryStartX || sh.x == boundaryEndX){
        return true;
    }
    
    // collision with body
    for(int i = 0; i < snakeLength - 1; i++){
        if(sh.x == st[i].x && sh.y == st[i].y){
            return true;
        }
    }
    
    return false;
}

/* gameOverScreen()
   - Shows game over menu, allows restart or exit.
   - Uses arrow keys to change selection and Enter to confirm.
*/
void gameOverScreen(){

    int inputArrow = 1;
    gameOverArrow = 1;

    char congo[36] = "Congratulation";
    char newHigh[36] = "New high score:";
    char gameOverString[35] = "Game Over";
    char restart[38] = "Restart";
    char exit[38] = "Exit";

    int firstLine = 7;
    int firstMargine = strlen(congo) / 2 * -1;

    int secondLine = 8;
    int secondMargine = strlen(newHigh) / 2 * -1 - 2;

    int thirdLine = 10;
    int thirdMargine = strlen(gameOverString) / 2 * -1;

    int forthLine = 12;
    int forthMargine = strlen(restart) / 2 * -1;

    int fifthLine = 13;
    int fifthMargine = strlen(exit) / 2 * -1;

    Sleep(100);
    system("cls");

    while(1){

        Sleep(10);

        if(_kbhit()){
            inputArrow = _getch();

            if(inputArrow == 0 || inputArrow == 224){
                inputArrow = _getch();
                // change selection with arrow keys
                if(inputArrow == 80 || inputArrow == 77) gameOverArrow++;
                else if(inputArrow == 72 || inputArrow == 75) gameOverArrow--;

                // wrap-around selection
                if(gameOverArrow == 0) gameOverArrow = 2;
                else if(gameOverArrow == 3) gameOverArrow = 1;
            }

            else if(inputArrow == 13){ // Enter pressed
                break;
            }
        }
        setCursor(boundaryStartY, boundaryStartX);

        // draw the game over screen
        for(int i = boundaryStartY; i <= boundaryEndY; i++){
            for(int j = boundaryStartX; j <= boundaryEndX; j++){

                if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                    if(!(j & 1)){
                        printf("%s", BLUE);
                        printf("%c", boundaryChar);
                    }
                    else printf("%c", spaceChar);
                }

                // if new high score, show congrats and score
                else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine && isNewHighScore){
                    printf("%s", CYAN);
                    printf("%s", congo);
                    j += strlen(congo) - 1;
                }
                
                else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine && isNewHighScore){
                    printf("%s", CYAN);
                    printf("%s %4d", newHigh, maxScore[currentLevelArrow - 1]);
                    j += strlen(newHigh) + 4;
                }
                
                else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                    printf("%s", CYAN);
                    printf("%s", gameOverString);
                    j += strlen(gameOverString) - 1;
                }

                // draw Restart option (with selection arrow)
                else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 + forthMargine){
                    if(gameOverArrow == 1){
                        printf("%s", GREEN);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", CYAN);
                    printf("%s", restart);
                    j += strlen(restart) - 1;
                }

                // draw Exit option (with selection arrow)
                else if(i == boundaryStartY + fifthLine && j == boundaryEndX / 2 + fifthMargine){
                    if(gameOverArrow == 2){
                        printf("%s", GREEN);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", CYAN);
                    printf("%s", exit);
                    j += strlen(exit) - 1;
                }

                else{
                    printf("%c", spaceChar);
                }
            }

            printf("\n");
        }

    }
}

/* title()
   - Prints the top info line: "Snake Game" and current difficulty.
*/
void title(){  //-------------------------------------------------------------------------------------

    printf("%s", RESET);
    printf("Snake Game"); 

    if(currentLevelArrow == 1){
        printf("%s", WHITE);
        char dificultyString[10] = "Easy";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 2){
        printf("%s", CYAN);
        char dificultyString[10] = "Medium";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 3){
        printf("%s", GREEN);
        char dificultyString[10] = "Hard";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 4){
        printf("%s", BLUE);
        char dificultyString[10] = "Extreme";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 
    else if(currentLevelArrow == 5){
        printf("%s", RED);
        char dificultyString[10] = "Legendary";
        for(int i = 0; i < boundaryEndX - 19 - strlen(dificultyString); i++) printf(" ");
        printf("Dificulty %s\n", dificultyString);
    } 

    
    
}

/* scorePrint()
   - Prints max score for the selected level and current score.
*/
void scorePrint(){  //-------------------------------------------------------------------------------------
    printf("%s", RESET);
    printf("Max Score: %3d", maxScore[currentLevelArrow - 1]); // show stored high score
    for(int i = 0; i < boundaryEndX - 31; i++) printf(" ");   // spacing
    printf("Current Score: %3d\n", score);                    // show current score
    printf("Press 'p' for pause and resume\n" );
    
}

/* levelChoose()
   - Lets user select difficulty with arrow keys. Sets refreshRate accordingly.
*/
void levelChoose(){  //-------------------------------------------------------------------------------------

    int pressedKey;
    currentLevelArrow = 1;
    refreshRate = 500;

    // menu text
    char level[38] = "Please choose a level";
    char level2nd[38] = "and press enter";
    char easy[38] = "Easy";
    char medium[38] = "Medium";
    char hard[38] = "Hard";
    char extreme[38] = "Extreme";
    char legendary[38] = "Legendary";

    // positions for text
    int firstLine = 5;
    int firstMargine = strlen(level) / 2 * -1;
    
    int first2Line = 6;
    int first2Margine = strlen(level2nd) / 2 * -1;

    int secondLine = 8;
    int secondMargine = strlen(easy) / 2 * -1;

    int thirdLine = 9;
    int thirdMargine = strlen(medium) / 2 * -1;

    int forthLine = 10;
    int forthMargine = strlen(hard) / 2 * -1;

    int fifthLine = 11;
    int fifthMargine = strlen(extreme) / 2 * -1;
    
    int sixthLine = 12;
    int sixthMargine = strlen(legendary) / 2 * -1;

    setCursor(boundaryStartX, boundaryStartY);

    while(1){

        Sleep(10);

        if(_kbhit()){

            pressedKey = _getch();

            if(pressedKey == 0 || pressedKey == 224){

                pressedKey = _getch();

                // change selection with arrow keys (wrap around)
                if(pressedKey == 80 || pressedKey == 77) currentLevelArrow++;
                else if(pressedKey == 72 || pressedKey == 75) currentLevelArrow--;

                if(currentLevelArrow == 0) currentLevelArrow = 5;
                else if(currentLevelArrow == 6) currentLevelArrow = 1;

                // set refreshRate (speed) for each difficulty
                switch(currentLevelArrow){
                    case 1:
                        refreshRate = 500; // easy (slow)
                        break;
                    case 2:
                        refreshRate = 250; // medium
                        break;
                    case 3:
                        refreshRate = 125; // hard
                        break;
                    case 4:
                        refreshRate = 62;  // extreme
                        break;
                    case 5:
                        refreshRate = 20;  // legendary (fast)
                        break;
                }
            }
            
            else if(pressedKey == 13){ // Enter key
                break;
            }
        }

        setCursor(boundaryStartY, boundaryStartX);
        // draw menu with current selection
        for(int i = boundaryStartY; i <= boundaryEndY; i++){
            for(int j = boundaryStartX; j <= boundaryEndX; j++){

                if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                    if(!(j & 1)){
                        printf("%s", BLUE);
                        printf("%c", boundaryChar);
                    }
                    else printf("%c", spaceChar);
                }

                else if(i == boundaryStartY + firstLine && j == boundaryEndX / 2 + firstMargine){
                    printf("%s", CYAN);
                    printf("%s", level);
                    j += strlen(level) - 1;
                }

                else if(i == boundaryStartY + first2Line && j == boundaryEndX / 2 + first2Margine){
                    printf("%s", CYAN);
                    printf("%s", level2nd);
                    j += strlen(level2nd) - 1;
                }

                else if(i == boundaryStartY + secondLine && j == boundaryEndX / 2 + secondMargine){
                    if(currentLevelArrow == 1){
                        printf("%s", RESET);
                        printf("> "); // selection arrow
                        j += 2;
                    }
                    printf("%s", WHITE);
                    printf("%s", easy);
                    j += strlen(easy) - 1;
                }

                else if(i == boundaryStartY + thirdLine && j == boundaryEndX / 2 + thirdMargine){
                    if(currentLevelArrow == 2){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", CYAN);
                    printf("%s", medium);
                    j += strlen(medium) - 1;
                }

                else if(i == boundaryStartY + forthLine && j == boundaryEndX / 2 + forthMargine){
                    if(currentLevelArrow == 3){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", GREEN);
                    printf("%s", hard);
                    j += strlen(hard) - 1;
                }

                else if(i == boundaryStartY + fifthLine && j == boundaryEndX / 2 + fifthMargine){
                    if(currentLevelArrow == 4){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", BLUE);
                    printf("%s", extreme);
                    j += strlen(extreme) - 1;
                }

                else if(i == boundaryStartY + sixthLine && j == boundaryEndX / 2 + sixthMargine){
                    if(currentLevelArrow == 5){
                        printf("%s", RESET);
                        printf("> ");
                        j += 2;
                    }
                    printf("%s", RED);
                    printf("%s", legendary);
                    j += strlen(legendary) - 1;
                }

                else{
                    printf("%c", spaceChar);
                }

            }
            printf("\n");
        }
    }
}

/* printInGameScreen()
   - Draw the full game frame: boundaries, snake head, body, and food.
*/
void printInGameScreen(){ //print every frame --------------------------------------------------------------

    setCursor(boundaryStartY, boundaryStartX);

    title(); // print top line

    for(int i = boundaryStartY; i <= boundaryEndY; i++){
        for(int j = boundaryStartX; j <= boundaryEndX; j++){

            // draw boundary
            if(i == boundaryStartY || i == boundaryEndY || j == boundaryStartX || j == boundaryEndX){
                if(!(j & 1)){
                    printf("%s", BLUE);
                    printf("%c", boundaryChar);
                }
                else printf("%c", spaceChar);
            }

            // draw snake head
            else if(i == sh.y && j == sh.x){
                printf("%s", CYAN);
                printf("%c", snakeHeadChar);
            }
            
            // draw food
            else if(i == f.y && j == f.x){
                printf("%s", RED);
                printf("%c", foodChar);
            }

            // draw body segments if any
            else{
                bool isPrinted = false;
                for(int k = 0; k < snakeLength - 1; k++){
                    if(st[k].y == i && st[k].x == j){
                        printf("%s", GREEN);
                        printf("%c", snakeBodyChar);
                        isPrinted = true;
                        break;
                    }
                }
                if(!isPrinted) printf("%c", spaceChar); // empty cell
            }
        }

        printf("\n");
    }
    scorePrint(); // print score line
    // snakeHeadY++;
}

/* foodSetup()
   - Place the first food at a random, valid location (not on the head).
   - Ensures x is on even columns (matching drawing spacing).
*/
void foodSetup(){

    f.x = 0;
    f.y = 0;

    while(1){

        srand(time(NULL));
        f.x = (rand() % (boundaryEndX - boundaryStartX - 3)) + 2;
        if(f.x & 1) f.x++; // force even column

        // srand(time(NULL));
        f.y = (rand() % (boundaryEndY - boundaryStartY - 3)) + 2;


        // avoid placing food directly on the head or immediate body below head
        if(!((f.x == sh.x) && (f.y == sh.y || f.y == sh.y + 1 || f.y == sh.y + 2))) break;
    }
}

/* food()
   - Called each frame in the loop. If snake head is on food:
     - increase score and length, play beep, update high score, and place new food.
   - Special handling for legendary level to ensure no overlap with body.
*/
void food(){

    if(!(sh.x == f.x && sh.y == f.y) && currentLevelArrow != 5){
        return; // not eaten (and not level 5 special)
    }
    else if((sh.x == f.x && sh.y == f.y) && currentLevelArrow == 5){
        score += 10;
        if(score > maxScore[currentLevelArrow - 1]){
            maxScore[currentLevelArrow - 1] = score;
            isNewHighScore = true;
        } 
        snakeLength++;
        Beep(750, 100);
    }

    if(currentLevelArrow == 5){
        // legendary: place new food avoiding body
        f.x = 0;
        f.y = 0;
        while(1){
            srand(time(NULL));
            f.x = (rand() % (boundaryEndX - boundaryStartX - 3)) + 2;
            if(f.x & 1) f.x++;
            // Sleep(3);
            srand(time(NULL));
            f.y = (rand() % (boundaryEndY - boundaryStartY - 3)) + 2;
            if(!(f.x == sh.x && f.y == sh.y) && !(overlapWithBody(&f.x, &f.y))) break;
        }
        return;
    }

    // normal levels: increase score, update high score if needed, grow snake
    score += 10;
    if(score > maxScore[currentLevelArrow - 1]){

        maxScore[currentLevelArrow - 1] = score;
        isNewHighScore = true;

    } 
    snakeLength++;
    Beep(750, 100);

    // place new food at a random free position (not head, not body)
    while(1){

        srand(time(NULL));
        f.x = (rand() % (boundaryEndX - boundaryStartX - 3)) + 2;
        if(f.x & 1) f.x++;

        Sleep(3);
        srand(time(NULL));
        f.y = (rand() % (boundaryEndY - boundaryStartY - 3)) + 2;

        if(!(f.x == sh.x && f.y == sh.y) && !(overlapWithBody(&f.x, &f.y))) break;
    }
}

/* overlapWithBody()
   - Returns true if given (x,y) overlaps any body segment.
*/
bool overlapWithBody(int *x, int *y){

    for(int i = 0; i < snakeLength; i++){
        if(st[i].x == *x && st[i].y == *y){
            return true;
        }
    }
    return false;

}

/* hideCursor()
   - Hides the console cursor to make the drawing cleaner.
*/
void hideCursor(){ //ChatGPT generated ----------------------------------------------------------------
    
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(out, &cursor);
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursor);

}

/* setCursor(x,y)
   - Move the console cursor to coordinate (x,y) so we can redraw from top-left.
*/
void setCursor(short x, short y){ //ChatGPT generated -------------------------------------------------------
    
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

}
