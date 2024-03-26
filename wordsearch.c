#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

// Main function, DO NOT MODIFY (except line 52 if your output is not as expected -- see the comment there)!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i = 0; i < 50; i++) {
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i = 0; i < 49; i++) {
		*(*(words+i) + strlen(*(words+i))-2) = '\0'; // Change -2 to -1 if line 58 outputs words with the last character missing
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i = 0; i < 50; i++) {
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n) {
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
    int i, j;
    for(i = 0; i < n; i++){
    	for(j = 0; j < n; j++){
      		printf("%c ",*(*(arr+i)+j));
    	}
    	printf("\n");
 	}
}

void searchPuzzle(char** arr, int n, char** list, int listSize) {
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here

	// Declare for row and column index of arr and list
	int i,j,c,w; 
	// Declare for temporary variables for i and j
	int  tem_i, tem_j;
	// Declare for a correct-words-verification variable
    bool P;
	// Declare for #-of-correct-letter-match variable
    unsigned long Match;

	// Initialize for row of words 
    c = 0;
	// Initialize for temporary variables 
    tem_i = 0;
    tem_j = 0;
	// Initialize for Match variable
	Match = 0;


    for(w = 0; w < listSize; w++){
        P = false;
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                // **************************************************************************

                // Horizontal Left to Right
                
                tem_j = j;
				//Check if word equals to the puzzle letters
                while((*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == (*(*(arr+i)+j) - 32) || *(*(list+w)+c) == *(*(arr+i)+j))
                && (c < strlen(*(list + w))-1) && (j < n-1)){
                    Match++;
                    j++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(list + w)) - 1) || (j == n - 1))  
                && (*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == *(*(arr+i)+j)))
                    Match++;

                if(Match == strlen(*(list + w))){
                    printf("Word Found: %s\n", *(list+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(list + w)); k++){
                        if(arr[i][j] <= 90){
                            arr[i][j] = arr[i][j] + 32;
                            j--;
                        }
                        else
                        {
                            j--;
                        }
                    }
                    // Restore the index
                    for(k = 0; k < strlen(*(list + w)); k++){
                        j++;
                    }
                    
                    Match = 0;
                    c = 0;
                    P = true;
                }
                else{
                    Match = 0;
                    c = 0;
                    j = tem_j;
                } 
                // **************************************************************************

                // Vertical Top to Bottom
                
                tem_i = i;
				//Check if word equals to the puzzle letters
                while((*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == (*(*(arr+i)+j) - 32) || *(*(list+w)+c) == *(*(arr+i)+j))
                && (c < strlen(*(list + w))-1) && (i < n-1) && (P == false)){
                    Match++;
                    i++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(list + w)) - 1) || (i == n - 1))
                && (*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == *(*(arr+i)+j)))
                    Match++;

                if(Match == strlen(*(list + w))){
                    printf("Word Found: %s\n", *(list+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(list + w)); k++){
                        if(arr[i][j] <= 90){
                            arr[i][j] = arr[i][j] + 32;
                            i--;
                        }
                        else{
                            i--;
                        }
                    }
                    // Restore index
                    for(k = 0; k < strlen(*(list + w)); k++){
                        i++;
                    }
            
                    Match = 0;
                    c = 0;
                    P = true;
                }   
                else{
                    Match = 0;
                    c = 0;
                    i = tem_i;
                } 
                // **************************************************************************

                // Vertical Bottom to Top
                
                tem_i = i;
				//Check if word equals to the puzzle letters
                while((*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == (*(*(arr+i)+j) - 32) || *(*(list+w)+c) == *(*(arr+i)+j))
                    && (c < strlen(*(list+w))-1) && (i > 0) && (P == false)){
                    Match++;
                    i--;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(list+w))-1) || (i == 0))
                && (*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == *(*(arr+i)+j)))
                    Match++;

                if(Match == strlen(*(list + w))){
                    printf("Word Found: %s\n", *(list+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(list + w)); k++){
                        if(arr[i][j] <= 90){
                            arr[i][j] = arr[i][j] + 32;
                            i++;
                        }
                        else{
                            i++;
                        }
                    }
                    // Restore Index
                    for(k = 0; k < strlen(*(list + w)); k++){
                        i--;
                    }
                    
                    Match = 0;
                    c = 0;
                    P = true;
                }
                else{
                    Match = 0;
                    c = 0;
                    i = tem_i;
                } 
                // **************************************************************************
                
                // Diagonal Top Left to Bottom Right
                
                tem_i = i;
                tem_j = j;
                
                
                while((*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == (*(*(arr+i)+j) - 32) || *(*(list+w)+c) == *(*(arr+i)+j))
                && (c < strlen(*(list+w))-1) && (i < n-1) && (j < n-1) && (P == false)){ 
                    Match++;
                    i++;
                    j++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(list + w)) - 1) || (j == n - 1) || (i == n - 1))
                && (*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == *(*(arr+i)+j)))
                    Match++;

                if(Match == strlen(*(list + w))){
                    printf("Word Found: %s\n", *(list+w));
                    
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(list + w)); k++){
                        if(arr[i][j] <= 90){
                            arr[i][j] = arr[i][j] + 32;
                            i--;
                            j--;
                        }
                        else{
                            i--;
                            j--;
                        }
                    } 
                    // Restore Index
                    for(k = 0; k < strlen(*(list + w)); k++){
                        i++;
                        j++;
                    } 
                    
                    Match = 0;
                    c = 0;
                    P = true;
                }
                else{
                    Match = 0;
                    c = 0;
                    i = tem_i;
                    j = tem_j;
                } 
                // **************************************************************************

                // Diagonal Bottom Left to Top Right
                
                tem_i = i;
                tem_j = j;
				
				//Check if word equals to the puzzle letters
                while((*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == (*(*(arr+i)+j) - 32) || *(*(list+w)+c) == *(*(arr+i)+j))
                && (c < strlen(*(list+w))-1) && (i > 0) && (j < n-1) && (P == false)){ 
                    Match++;
                    i--;
                    j++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(list+w))-1) || (j == n - 1) || (i == 0))
                && (*(*(list+w)+c) == (*(*(arr+i)+j) + 32) || *(*(list+w)+c) == *(*(arr+i)+j)))
                    Match++;

                if(Match == strlen(*(list + w))){
                    printf("Word Found: %s\n", *(list+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(list + w)); k++){
                        if(arr[i][j] <= 90){
                            arr[i][j] = arr[i][j] + 32;
                            i++;
                            j--;
                        }
                        else{
                            i++;
                            j--;
                        }
                    }
                    // Restore Index
                    for(k = 0; k < strlen(*(list + w)); k++){
                        i--;
                        j++;
                    }
                    
                    Match = 0;
                    c = 0;
                    P = true;
                }
                else{
                    Match = 0;
                    c = 0;
                    i = tem_i;
                    j = tem_j;
                } 
                // **************************************************************************

                if(P == true)
                    break;
            }            
            if(P == true)
            	break;
        }
    }
}
