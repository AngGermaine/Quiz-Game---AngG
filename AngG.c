#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_SIZE 200
#define MAX_RECORDS 25
#define MAX_QUESTION_LENGTH 150
#define MAX_ANSWER_LENGTH 30
#define MAX_TOPIC_LENGTH 20
#define MAX_CHOICE_LENGTH 30

typedef char aString[MAX_SIZE];

struct record {
    char aQuestion[MAX_QUESTION_LENGTH];
    char aAnswer[MAX_ANSWER_LENGTH];
    char aTopic[MAX_TOPIC_LENGTH];
    char aChoices[3][MAX_CHOICE_LENGTH];
    int nQuestionNumber;
}; 

int inputPassword();
void getString(aString *ptr);
void getInput(struct record *record, int nRecords);
void displayRecord();
void addRecord();
//void editRecord();
//void deleteRecord();
//void importRecord();
//void exportRecord();

int main() 
{
	int nMMChoice;
	int nMDMChoice;
	int nGMChoice;
	int nPassCheck;

	do 
	{
    	printf("\n-MAIN MENU-\n");
    	printf("[1] Manage Data\n");
    	printf("[2] Play\n");
    	printf("[3] Exit\n");

        printf("||| Enter your choice: ");
        scanf("%d", &nMMChoice);

        switch (nMMChoice) 
		{
            case 1:
            	//Ask for password first
            	nPassCheck = inputPassword();
            	if (nPassCheck == 6)
            	{
            		printf("\n||| Going back to Main Menu...\n");
            		nMDMChoice = nPassCheck; //giving nMDMChoice value of 6 which returns it back to main menu
				}
            	// Manage Data menu
            	else
            	{
            		do 
					{
	                    printf("\n-MANAGE DATA-\n");
	                    printf("[1] Add record\n");
	                    printf("[2] Edit record\n");
	                    printf("[3] Delete record\n");
	                    printf("[4] Import record\n");
	                    printf("[5] Export record\n");
	                    printf("[6] Back to Main Menu\n");
	
	                    printf("||| Enter your choice: ");
	                    scanf("%d", &nMDMChoice);
	
	                    switch (nMDMChoice) 
						{
	                        case 1:
	                            //addRecord();
	                            break;
	                        case 2:
	                            //editRecord();
	                            break;
	                        case 3:
	                            //deleteRecord();
	                            break;
	                        case 4:
	                            //importRecord();
	                            break;
	                        case 5:
	                            //exportRecord();
	                            break;
	                        case 6:
	                            printf("\n||| Going back to Main Menu...\n");
	                            break;
	                        default:
	                            printf("||| Invalid choice. Please try again.\n");
	                            break;
	                    }
	                } while (nMDMChoice != 6);
				}
            	
                break;
                
            case 2:
                // Play Game menu
                do 
				{
                    printf("\nQUIZ GAME\n");
                    printf("[1] \n");
                    printf("[2] \n");
                    printf("[3] Back to Main Menu\n");

                    printf("||| Enter your choice: ");
                    scanf("%d", &nGMChoice);

                    switch (nGMChoice) 
					{
                        case 1:
                            
                            break;
                        case 2:
                            
                            break;
                        case 3:
                            printf("\n||| Going back to Main Menu...\n");
                            break;
                        default:
                            printf("||| Invalid choice. Please try again.\n");
                            break;
                    }
                } while (nGMChoice != 3);
                break;
            case 3:
                printf("\n||| Exiting program...\n");
                break;
            default:
                printf("||| Invalid choice. Please try again.\n");
                break;
        }
    } while (nMMChoice != 3);

    return 0;
}

int inputPassword()
{
	aString aPassword;
	strcpy(aPassword, "password");
	strcat(aPassword, "");
	
	char aInputPass[MAX_SIZE];
	char ch; //take a string input
	int i = 0; //counter for input
	int isPass = 0; //boolean for checking if correct password
	int nMMreturn; //taking int input for options
	
	
	printf("\n-LOGIN-");
	do
	{
		printf("\n||| Hello, please input the password: ");
		
		do //ask for string input
		{
			ch = getch();
			if (ch != 13)
			{
				printf("*");
				aInputPass[i] = ch;
				i++;
				aInputPass[i] = '\0';
			}
		} while (i < MAX_SIZE && ch != 13);
		
		if (strcmp(aPassword, aInputPass) == 0)
		{
			printf("\n\n||| Welcome, Admin.\n");
			isPass = 1;
		}	
		else 
		{
			printf("\n\n||| Wrong password. Please try again.\n");
			isPass = 0;
			
			printf("||| Would you like to try again [1] or go back to Main Menu [2]? ");
			scanf("%d", &nMMreturn);
			
			if (nMMreturn == 1)
			{
				i = 0; //for input taking reset
			}
				
			if (nMMreturn == 2)
			{
				isPass = 6; //so in main, manage data menu's value is 6 which brings it back to the main menu
			}
		}
	} while (isPass == 0);	
	return isPass;
}

void getString(aString *ptr)
{
	char ch;
	int i = 0;
	aString characters;
	
	do
	{
		scanf("%c", &ch);
		
		if (ch != '\n')
		{
			characters[i] = ch;
			i++;
			characters[i] = '\0';
		}
	} while (i < MAX_SIZE && ch != '\n');
	
	strcpy(*ptr, characters);
}

void getInput(struct record *record, int nRecords)
{
	int i, x, j;
	
	
	if 
	
	
}


void addRecord(struct record *record, int nRecords)
{
	
}


/*
void displayRecord(struct record *record) 
{	
    printf("Topic: %s\n", record->aTopic);
    printf("Question Number: %d\n", r->nQuestionNumber);
    printf("Question: %s\n", record->aQuestion);
   
    printf("Choices:\n");
    printf("1. %s\n", record->aChoices[0]);
    printf("2. %s\n", record->aChoices[1]);
    printf("3. %s\n", record->aChoices[2]);
    
    printf("Answer: %s\n", record->aAnswer);
} */



