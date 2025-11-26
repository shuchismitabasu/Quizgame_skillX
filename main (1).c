#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> // For srand()

// Define a structure to hold a single quiz question
typedef struct {
    char question[150];
    char options[250]; // Increased size for more detailed options
    char answer; // A, B, C, or D
    char topic[50]; // Added topic for context
} QuizItem;

// Define the user profile structure
typedef struct {
    char name[50];
    int bestScore;
} UserProfile;

// --- HELPER FUNCTIONS ---

// Function to clear the input buffer after scanf
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Function to shuffle the array of QuizItems (Fisher-Yates)
void shuffle(QuizItem arr[], int n) {
    // Seed the random number generator only once
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL)); 
        seeded = 1;
    }

    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            // Generate a random index j such that i <= j < n
            int j = i + (rand() % (n - i)); 
            
            // Swap arr[i] and arr[j]
            QuizItem temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

// --- MAIN GAME LOGIC ---

int main() {
    
    // --- User Profile Setup ---
    UserProfile player;
    strcpy(player.name, "Student"); 
    player.bestScore = 0;

    printf("==========================================\n");
    printf("   QUIZ-GAME \n");
    printf("==========================================\n");
    printf("Enter your name: ");
    
    // Read user name safely (max 49 characters)
    if (scanf("%49s", player.name) != 1) {
        clearBuffer();
    }
    clearBuffer(); 
    
    printf("\nWelcome, %s! Let's test your fundamental knowledge.\n", player.name);

    // --- Quiz Data (College Level Questions) ---
    QuizItem quizData[] = {
        // Topic: General Science / Biology
        {"Which organelle is responsible for generating the majority of ATP (Adenosine Triphosphate) in a eukaryotic cell?", 
         "A. Endoplasmic Reticulum\nB. Golgi Apparatus\nC. Mitochondrion\nD. Lysosome", 'C', "Biology"},
        
        // Topic: History / Political Science
        {"The concept of 'separation of powers' in modern governance is most closely associated with which Enlightenment philosopher?", 
         "A. Jean-Jacques Rousseau\nB. John Locke\nC. Montesquieu\nD. Thomas Hobbes", 'C', "PoliSci"},
        
        // Topic: Chemistry
        {"In a neutral atom, the number of protons must equal the number of which other subatomic particle?", 
         "A. Neutrons\nB. Electrons\nC. Ions\nD. Isotopes", 'B', "Chemistry"},
         
        // Topic: Computer Science / Logic
        {"What is the result of the boolean expression: (true AND false) OR (NOT false)?", 
         "A. True\nB. False\nC. Undefined\nD. Null", 'A', "Logic/CS"},
         
        // Topic: Mathematics
        {"Value of 20*5 is?", 
         "A. 1000\nB. 100\nC. 205\nD. 20", 'B', "Mathematics"}
    };

    int questionCount = sizeof(quizData) / sizeof(quizData[0]);
    shuffle(quizData, questionCount);
    
    char guess = '\0';
    int score = 0;

    for(int i = 0; i < questionCount; i++){
        
        printf("\n------------------------------------------\n");
        printf("Question %d of %d (Topic: %s)\n", i + 1, questionCount, quizData[i].topic);
        printf("Q: %s\n", quizData[i].question);
        printf("\n%s\n", quizData[i].options);
        
        int isValid = 0;
        
        do {
            printf("\nYour Answer (A/B/C/D): ");
            guess = '\0'; 
            
            if (scanf(" %c", &guess) != 1) {
                clearBuffer();
                printf("\n\t*** Input error. Please try again. ***\n");
                continue;
            }
            clearBuffer(); 

            // Input validation check
            guess = (char)toupper(guess);
            if (guess >= 'A' && guess <= 'D') {
                isValid = 1;
            } else {
                printf("\n\t*** Invalid choice! Please enter A, B, C, or D. ***\n");
            }

        } while (!isValid); 

        // Check the answer
        if (guess == quizData[i].answer) {
            printf("\n✅ CORRECT!\n");
            score++;
        } else {
            printf("\n❌ INCORRECT. The correct answer was %c.\n", quizData[i].answer);
        }
    }

    // --- Result Display ---
    printf("\n\n==========================================\n");
    printf("        %s'S QUIZ SUMMARY\n", player.name);
    printf("==========================================\n");
    printf("Total Questions: %d\n", questionCount);
    printf("Correct Answers: %d\n", score);
    printf("Percentage: %.2f%%\n", (float)score * 100 / questionCount);
    printf("==========================================\n");
    
    // Best Score Logic (Simple check since data isn't persisted)
    if (score > player.bestScore) {
        player.bestScore = score;
        printf("🌟 NEW HIGH SCORE for this session! Keep studying, %s.\n", player.name);
    }
    return 0;
}