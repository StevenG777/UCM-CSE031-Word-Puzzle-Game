#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
	

    // --------------------------------------------------------------------------------------------------
    // Test 1: Upper and Lower case number comparison
    /*
    if('A' == ('a' - 32)){
        printf("This works\n");
    }
    else{
        printf("Not working\n");
    }*/
	

	// Testing 2: Actual Length of a string and Display it
    /*
    printf("Printing list of words:\n");
	for(i = 0; i < 50; i++) {
		printf("%s          ", *(words + i));
        printf("%lu\n",strlen(*(words + i)));		
	}
	printf("\n");*/


    // Testing 3: Verify Letter from words and letter from block
    /*
    printf("%s compares to %s \n",words[15],"kAnSaS");
    if(words[15][0] == 'k' || words[15][0] == 'K')
        printf("%c ", 'K');
    if(words[15][1] == 'A' || words[15][1] == 'a')
        printf("%c ", 'A');
    if(words[15][2] == 'n' || words[15][2] == 'N') 
        printf("%c ", 'N');
    if(words[15][3] == 'S' || words[15][3] == 's')
        printf("%c ", 'S');
    if(words[15][4] == 'a' || words[15][4] == 'A')
        printf("%c ", 'A');
    if(words[15][5] == 'S' || words[15][5] == 's')
        printf("%c ", 'S');
    printf("\n");
    */


    // Testing 4: ASCII Decimal Number of a character 
    /*
    if('Z' == 90){
        printf("This method works!\n");
    } */


    // Testing 5: Creating Puzzle test layout
    /*
    for(i = 0; i < bSize; i++){
        for(j = 0; j < bSize; j++){
            printf("%c ",'X');
        }
        printf("\n");
    }
    printf("\n\n"); */


    // Testing 6: Searching words algorithm (all directions)
    
    int c,w, tem_i, tem_j;
    bool P;

    unsigned long Match = 0; 
    c = 0;
    tem_i = 0;
    tem_j = 0;
    for(w = 0; w < 50; w++){
        P = false;
        for(i = 0; i < bSize; i++){
            for(j = 0; j < bSize; j++){
                // **************************************************************************

                // Horizontal Left to Right
                
                tem_j = j;
                while((*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == (*(*(block+i)+j) - 32) || *(*(words+w)+c) == *(*(block+i)+j))
                && (c < strlen(*(words + w))-1) && (j < bSize-1)){
                    Match++;
                    j++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(words + w)) - 1) || (j == bSize - 1))  
                && (*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == *(*(block+i)+j)))
                    Match++;

                if(Match == strlen(*(words + w))){
                    printf("Word Found: %s\n", *(words+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(words + w)); k++){
                        if(block[i][j] <= 90){
                            block[i][j] = block[i][j] + 32;
                            j--;
                        }
                        else
                        {
                            j--;
                        }
                    }
                    // Restore the index
                    for(k = 0; k < strlen(*(words + w)); k++){
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
                while((*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == (*(*(block+i)+j) - 32) || *(*(words+w)+c) == *(*(block+i)+j))
                && (c < strlen(*(words + w))-1) && (i < bSize-1) && (P == false)){
                    Match++;
                    i++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(words + w)) - 1) || (i == bSize - 1))
                && (*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == *(*(block+i)+j)))
                    Match++;

                if(Match == strlen(*(words + w))){
                    printf("Word Found: %s\n", *(words+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(words + w)); k++){
                        if(block[i][j] <= 90){
                            block[i][j] = block[i][j] + 32;
                            i--;
                        }
                        else{
                            i--;
                        }
                    }
                    // Restore index
                    for(k = 0; k < strlen(*(words + w)); k++){
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
                while((*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == (*(*(block+i)+j) - 32) || *(*(words+w)+c) == *(*(block+i)+j))
                    && (c < strlen(*(words+w))-1) && (i > 0) && (P == false)){
                    Match++;
                    i--;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(words+w))-1) || (i == 0))
                && (*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == *(*(block+i)+j)))
                    Match++;

                if(Match == strlen(*(words + w))){
                    printf("Word Found: %s\n", *(words+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(words + w)); k++){
                        if(block[i][j] <= 90){
                            block[i][j] = block[i][j] + 32;
                            i++;
                        }
                        else{
                            i++;
                        }
                    }
                    // Restore Index
                    for(k = 0; k < strlen(*(words + w)); k++){
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
                
                
                while((*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == (*(*(block+i)+j) - 32) || *(*(words+w)+c) == *(*(block+i)+j))
                && (c < strlen(*(words+w))-1) && (i < bSize-1) && (j < bSize-1) && (P == false)){ 
                    Match++;
                    i++;
                    j++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(words + w)) - 1) || (j == bSize - 1) || (i == bSize - 1))
                && (*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == *(*(block+i)+j)))
                    Match++;

                if(Match == strlen(*(words + w))){
                    printf("Word Found: %s\n", *(words+w));
                    
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(words + w)); k++){
                        if(block[i][j] <= 90){
                            block[i][j] = block[i][j] + 32;
                            i--;
                            j--;
                        }
                        else{
                            i--;
                            j--;
                        }
                    } 
                    // Restore Index
                    for(k = 0; k < strlen(*(words + w)); k++){
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

                while((*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == (*(*(block+i)+j) - 32) || *(*(words+w)+c) == *(*(block+i)+j))
                && (c < strlen(*(words+w))-1) && (i > 0) && (j < bSize-1) && (P == false)){ 
                    Match++;
                    i--;
                    j++;
                    c++;
                }

                // Prevent words and block segmentation fault
                if(((c == strlen(*(words+w))-1) || (j == bSize - 1) || (i == 0))
                && (*(*(words+w)+c) == (*(*(block+i)+j) + 32) || *(*(words+w)+c) == *(*(block+i)+j)))
                    Match++;

                if(Match == strlen(*(words + w))){
                    printf("Word Found: %s\n", *(words+w));
                    // Setting Puzzle to lower case
                    int k;
                    for(k = 0; k < strlen(*(words + w)); k++){
                        if(block[i][j] <= 90){
                            block[i][j] = block[i][j] + 32;
                            i++;
                            j--;
                        }
                        else{
                            i++;
                            j--;
                        }
                    }
                    // Restore Index
                    for(k = 0; k < strlen(*(words + w)); k++){
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

    printf("\n");
    for(i = 0; i < bSize; i++){
    	for(j = 0; j < bSize; j++){
      		printf("%c ",*(*(block+i)+j));
    	}
    	printf("\n");
 	}
    printf("\n");
    
    return 0;
}