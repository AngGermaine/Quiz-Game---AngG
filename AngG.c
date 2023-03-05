#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_SIZE 100

void inputString(char aString[]);
int inputPassword();

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
	                            
	                            break;
	                        case 2:
	                            
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
	char aPassword[MAX_SIZE];
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

void inputString(char aString[])
{
	char ch;
	int i = 0;
	
	do
	{
		scanf("%c", &ch);
		if (ch != '\n')
		{
			aString[i] = ch;
			i++;
			aString[i] = '\0';
		}
	} while (i < MAX_SIZE && ch != '\n');
}
