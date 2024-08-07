/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Germaine Richie Chua Ang, DLSU ID# 12275328
*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define MAX_SIZE 200
#define MAX_RECORDS 30
#define MAX_QUESTION_LENGTH 150
#define MAX_ANSWER_LENGTH 30
#define MAX_TOPIC_LENGTH 20
#define MAX_CHOICE_LENGTH 30

typedef char string30[30];

struct record {
    char sQuestion[MAX_QUESTION_LENGTH];
    char sAnswer[MAX_ANSWER_LENGTH];
    char sTopic[MAX_TOPIC_LENGTH];
    char sUniqueTopics[MAX_TOPIC_LENGTH];
    char sChoicesOne[MAX_CHOICE_LENGTH];
    char sChoicesTwo[MAX_CHOICE_LENGTH];
    char sChoicesThree[MAX_CHOICE_LENGTH];
    int nQuestionNum;
}; 

struct players {
	string30 sName;
	int nGameScore;
};

int inputPassword();
void getInput(struct record *record, int nRecords);
int addRecord(struct record *record, int nRecords);
int getUniqueTopic(struct record *record, int nRecords, int nUniqueTopicNum);
void updateQuestionNumber(struct record *record, int nRecords);
void editRecord(struct record *record, int nRecords, int nUniqueTopicNum);
int deleteRecord(struct record *record, int nRecords, int nUniqueTopicNum);
int stringToInt(char *str);
int importRecord(struct record *record, int nRecords);
char *exportRecord(struct record *record, int nRecords);
int saveRecord(struct record *record, int nRecords, string30 sFilename);
int countPlayers(struct players *player, int nPlayers);
int playGame(struct record *record, struct players *player, int nRecords, int nPlayers, int nUniqueTopicNum);
void viewScores(struct players *player, int nPlayers);
int importScores(struct players *player, int nPlayers);
void exportScores(struct players *player, int nPlayers);

int main() 
{
	int i;
	int nMMChoice, nMDMChoice, nGMChoice, nPassCheck, nUniqueTopicNum, nRecord = 0, nPlayerCount = 0;
	int bEditRecordOption, bEndEdit = 0, bSavedRecord = 0;
	struct record aRecords[MAX_RECORDS];
	struct players aPlayers[MAX_SIZE];
	string30 sFileName;
	srand(time(NULL));
	
	do 
	{
		bSavedRecord = 0; //so that if in the next manage data loop, if they do not select Export, it will not save the record arrray.
		system("cls");
    	printf("\n-MAIN MENU-\n");
    	printf("[1] Manage Data\n");
    	printf("[2] Play\n");
    	printf("[3] Exit\n");

        printf("||| Enter your choice: ");
        scanf("%d", &nMMChoice);

        switch (nMMChoice) 
		{
            case 1:
            	//ask for password first
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
						system("cls");
	                    printf("\n-MANAGE DATA-\n");
	                    printf("Number of Records: %d\n", nRecord);
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
	                            nRecord = addRecord(aRecords, nRecord);
	                            printf("\n");
	                            system("pause");
	                            break;
	                        case 2:
	                        	do
	                        	{
	                        		system("cls");
	                        		nUniqueTopicNum = 0;
	                        		for (i = 0; i < nRecord; i++)
	                        		{
	                        			strcpy((aRecords+i)->sUniqueTopics,"");
									}
		                        	nUniqueTopicNum = getUniqueTopic(aRecords, nRecord, nUniqueTopicNum);
		                        	editRecord(aRecords, nRecord, nUniqueTopicNum);
			                        do
									{
										printf("\n||| Would you still like to [1] Edit other records or [2] Return to Manage Data Menu? ");
										scanf(" %d", &bEditRecordOption);
										system("cls");
										if (bEditRecordOption == 1)
										{
											nUniqueTopicNum = 0;
											for (i = 0; i < nRecord; i++)
			                        		{
			                        			strcpy((aRecords+i)->sUniqueTopics,"");
											}
											bEndEdit = 0;
										}
										
										else
										{
											bEndEdit = 1;
										}
											
									} while (bEditRecordOption < 1 || bEditRecordOption > 2);
					
								} while (bEndEdit == 0);
	                        	
	                            break;
	                        case 3:
	                        	do
	                        	{
	                        		system("cls");
	                        		nUniqueTopicNum = 0;
	                        		for (i = 0; i < nRecord; i++)
	                        		{
	                        			strcpy((aRecords+i)->sUniqueTopics,"");
									}
		                        	nUniqueTopicNum = getUniqueTopic(aRecords, nRecord, nUniqueTopicNum);
		                        	nRecord = deleteRecord(aRecords, nRecord, nUniqueTopicNum);
		                        	
			                        do
									{
										printf("\n||| Would you still like to [1] Delete other records or [2] Return to Manage Data Menu? ");
										scanf(" %d", &bEditRecordOption);
										system("cls");
										if (bEditRecordOption == 1)
										{
											nUniqueTopicNum = 0;
											for (i = 0; i < nRecord; i++)
			                        		{
			                        			strcpy((aRecords+i)->sUniqueTopics,"");
											}
											bEndEdit = 0;
										}
										
										else
										{
											bEndEdit = 1;
										}
											
									} while (bEditRecordOption < 1 || bEditRecordOption > 2);
					
								} while (bEndEdit == 0);
	                            
	                            break;
	                        case 4:
	                            nRecord = importRecord(aRecords, nRecord);
	                            updateQuestionNumber(aRecords, nRecord);
	                            printf("\n");
	                            system("pause");
	                            break;
	                        case 5:
	                            strcpy(sFileName, exportRecord(aRecords, nRecord));
	                            bSavedRecord = 1;
	                            break;
	                        case 6:
	                        	if (bSavedRecord)
	                        	{
	                        		nRecord = saveRecord(aRecords, nRecord, sFileName);
								}
								
								else
								{
									printf("\n||| Deleting unsaved records. (Tip: Save with export.)");
									for (i = 0; i < nRecord; i++)
			                        	{
			                        		strcpy((aRecords+i)->sTopic, "");
											(aRecords+i)->nQuestionNum = 0;
											strcpy((aRecords+i)->sQuestion, "");
											strcpy((aRecords+i)->sChoicesOne, "");
											strcpy((aRecords+i)->sChoicesTwo, "");
											strcpy((aRecords+i)->sChoicesThree, "");
											strcpy((aRecords+i)->sAnswer, "");	
										}
									nRecord = 0;
								}
	                        	
	                            printf("\n||| Going back to Main Menu...\n\n");
	                            system("pause");
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
					system("cls");
                    printf("\n-QUIZ GAME-\n");
                    printf("[1] Play\n");
                    printf("[2] View Scores\n");
                    printf("[3] Back to Main Menu\n");

                    printf("||| Enter your choice: ");
                    scanf("%d", &nGMChoice);

                    switch (nGMChoice) 
					{
                        case 1:
                        	system("cls");
                        	printf("\n-QUIZ GAME-\n");
                        	if (nRecord > 0)
                        	{
	                        	fflush(stdin);
	                        	nPlayerCount = countPlayers(aPlayers, nPlayerCount);
								printf("||| Enter your name: ");
								fgets((aPlayers+nPlayerCount)->sName, 30, stdin);
								(aPlayers+nPlayerCount)->sName[strlen((aPlayers+nPlayerCount)->sName)-1] = '\0';
	                        	do
	                        	{
		                        	system("cls");
		                            nUniqueTopicNum = 0;
			                        for (i = 0; i < nRecord; i++)
			                        {
			                        	strcpy((aRecords+i)->sUniqueTopics,"");
									}
				                    nUniqueTopicNum = getUniqueTopic(aRecords, nRecord, nUniqueTopicNum);
				                    nRecord = playGame(aRecords, aPlayers, nRecord, nPlayerCount, nUniqueTopicNum);	
				                    do
				                    {
				            			printf("\n||| Would you still like to [1] Play game or [2] Return to Game Menu? ");
										scanf(" %d", &bEditRecordOption);
										if (bEditRecordOption == 1)
										{
											system("cls");
											nUniqueTopicNum = 0;
											for (i = 0; i < nRecord; i++)
				                        	{
				                        		strcpy((aRecords+i)->sUniqueTopics,"");
											}
											bEndEdit = 0;
										}
											
										else
										{
											nRecord = saveRecord(aRecords, nRecord, sFileName);
											printf("\n||| %s's SCORE is: %d\n\n", (aPlayers+nPlayerCount)->sName, (aPlayers+nPlayerCount)->nGameScore);
											nPlayerCount = countPlayers(aPlayers, nPlayerCount);
											system("pause");
											bEndEdit = 1;
										}    	
									} while (bEditRecordOption < 1 || bEditRecordOption > 2);
	                        		
								} while (bEndEdit == 0);	
							}
                        	else
                        	{
                        		printf("||| There are no records.\n");
                        		printf("\n||| Going back to Quiz Game Menu...\n\n");
                            	system("pause");
							}
                        	
                            break;
                        case 2:
                            system("cls");
                        	printf("\n-QUIZ GAME-\n");
                        	nPlayerCount = importScores(aPlayers, nPlayerCount);
                        	viewScores(aPlayers, nPlayerCount);
                        	system("pause");
                            break;
                        case 3:
                        	if (nPlayerCount > 0)
                        	{
	                        	exportScores(aPlayers, nPlayerCount);
	                            for (i = 0; i < nPlayerCount; i++)
				                {
				                    strcpy((aPlayers+i)->sName, "");
									(aPlayers+i)->nGameScore = 0;
								}
								nPlayerCount = 0;	
							}
                			else
                			{
                				printf("||| There are no players.\n");
							}
							printf("\n||| Going back to Main Menu...\n\n");
                            system("pause");
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

/* inputPassword asks for password input and returns two values that help it lead the user to different menus.
@return bIsPass = 1 if the password is correct so it leads them to manage data
@return bIsPass = 6 if they want to go back to main menu
*/

int 
inputPassword()
{
	string30 sPassword;
	strcpy(sPassword, "password"); //setting of password
	strcat(sPassword, "");
	
	char aInputPass[MAX_SIZE];
	char ch; //take a string input
	int i = 0, nLen1, nLen2; 
	int bIsPass = 0;//boolean for checking if correct password
	int nMMreturn; //taking int input for options
	
	printf("\n-LOGIN-");
	do
	{
		printf("\n||| Hello, please input the password: ");
		
		do //ask for string input
		{
			ch = getch();
			if (ch == 8)
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");
				}
			}
			else if (ch != 13)
			{
				printf("*");
				aInputPass[i] = ch;
				i++;
			}
		} while (i < MAX_SIZE && ch != 13);
		
		aInputPass[i] = '\0';
		
		nLen1 = strlen(sPassword);
		nLen2 = strlen(aInputPass);
		
		if (nLen1 == nLen2 && strcmp(sPassword, aInputPass) == 0)
        {
            bIsPass = 1;
        }
        
		else 
		{
			printf("\n||| Wrong password.\n"	);
			bIsPass = 0;
			
			do
			{
				printf("\n||| Would you like to try again [1] or go back to Main Menu [2]? ");
				scanf("%d", &nMMreturn);
				
				if (nMMreturn == 1)
				{
					i = 0; //for input taking reset
				}
					
				if (nMMreturn == 2)
				{
					bIsPass = 6; //so in main, manage data menu's value is 6 which brings it back to the main menu
				}	
			} while (nMMreturn < 1 || nMMreturn > 2);
			
		}
	} while (bIsPass == 0);	
	return bIsPass;
}

/* getInput is a void function that acts as a way for user to input the fields of the record. Used in addRecord. 
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
Pre-condition: Input only contains letters in the alphabet
*/

void 
getInput(struct record *record, 
	     int nRecords)
{
	int i, j;
	int nTopicNum = 1, nCurrent = nRecords - 1; 
	int bFound = 0, bFoundUniqueTopic = 0;
	
	if (((record+nCurrent)->sQuestion) != '\0') //check if there is a record, so now we check if question and answer is same
	{
		fflush(stdin);
		
		printf("||| Enter question: ");
		fgets(((record+nRecords)->sQuestion), MAX_QUESTION_LENGTH, stdin);
		(record+nRecords)->sQuestion[strlen((record+nRecords)->sQuestion)-1] = '\0'; 
				
		printf("||| Enter answer: ");
		fgets(((record+nRecords)->sAnswer), MAX_ANSWER_LENGTH, stdin);
		(record+nRecords)->sAnswer[strlen((record+nRecords)->sAnswer)-1] = '\0'; 
						
		for (i = 0; i < nRecords && bFound == 0; i++)
		{
			if (strcmp((record+nRecords)->sQuestion,(record+i)->sQuestion) == 0 &&
			    strcmp((record+nRecords)->sAnswer,(record+i)->sAnswer) == 0)
			{
				bFound = 1;
			} 
		}
		
		if (bFound != 1)
		{
			printf("||| Enter topic: ");
			fgets(((record+nRecords)->sTopic), MAX_TOPIC_LENGTH, stdin);
			(record+nRecords)->sTopic[strlen((record+nRecords)->sTopic)-1] = '\0';  
				
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if (strcmp((record+nRecords)->sTopic, (record+j)->sUniqueTopics) == 0)
				{
					bFoundUniqueTopic = 1;
				}
			}
			
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if((bFoundUniqueTopic == 0) && ((record+j)->sUniqueTopics == '\0'))
				{
					strcpy((record+nTopicNum)->sUniqueTopics,"\0");
					strcpy((record+nTopicNum)->sUniqueTopics, (record+nRecords)->sTopic);
					bFoundUniqueTopic = 1;
				} 
			}
			
			for (j = 0; j < nRecords; j++)
			{
				if (strcmp((record+nRecords)->sTopic, (record+j)->sTopic) == 0)
				{
					nTopicNum++;
				}
			}
							
			(record+nRecords)->nQuestionNum = nTopicNum;

			do
			{	
				printf("\n||| Enter choice 1: ");
				fgets(((record+nRecords)->sChoicesOne), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->sChoicesOne[strlen((record+nRecords)->sChoicesOne)-1] = '\0';  
						
				printf("||| Enter choice 2: ");
				fgets(((record+nRecords)->sChoicesTwo), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->sChoicesTwo[strlen((record+nRecords)->sChoicesTwo)-1] = '\0';  
						
				printf("||| Enter choice 3: ");
				fgets(((record+nRecords)->sChoicesThree), MAX_CHOICE_LENGTH, stdin);
				(record+nRecords)->sChoicesThree[strlen((record+nRecords)->sChoicesThree)-1] = '\0';  	

			}while((strcmp((record+nRecords)->sAnswer,(record+nRecords)->sChoicesOne) != 0 &&
			 	    strcmp((record+nRecords)->sAnswer,(record+nRecords)->sChoicesTwo) != 0 &&
			        strcmp((record+nRecords)->sAnswer,(record+nRecords)->sChoicesThree) != 0) ||
				   (strcmp((record+nRecords)->sChoicesOne,(record+nRecords)->sChoicesTwo) == 0 ||
				    strcmp((record+nRecords)->sChoicesTwo,(record+nRecords)->sChoicesThree) == 0 ||
				    strcmp((record+nRecords)->sChoicesOne,(record+nRecords)->sChoicesThree) == 0));
		}	
		
	}
	
	else
	{
		for (i = 0; i < nRecords; i++) // for the first record, so no need to check same question and answer
		{
			fflush(stdin);
			
			printf("||| Enter question: ");
			fgets(((record+i)->sQuestion), MAX_QUESTION_LENGTH, stdin);
			(record+i)->sQuestion[strlen((record+i)->sQuestion)-1] = '\0'; 
				
			printf("\n||| Enter answer: ");
			fgets(((record+i)->sAnswer), MAX_ANSWER_LENGTH, stdin);
			(record+i)->sAnswer[strlen((record+i)->sAnswer)-1] = '\0';  
			
			printf("\n||| Enter topic: ");
			fgets(((record+i)->sTopic), MAX_TOPIC_LENGTH, stdin);
			(record+i)->sTopic[strlen((record+i)->sTopic)-1] = '\0'; 
			
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if (strcmp((record+i)->sTopic, (record+j)->sUniqueTopics) == 0)
				{
					bFoundUniqueTopic = 1;
				}
			}
			
			for (j = 0; j < nRecords && bFoundUniqueTopic == 0; j++)
			{
				if((bFoundUniqueTopic == 0) && ((record+j)->sUniqueTopics == '\0'))
				{
					strcpy((record+nTopicNum)->sUniqueTopics,"\0");
					strcpy((record+nTopicNum)->sUniqueTopics, (record+i)->sTopic);
					bFoundUniqueTopic = 1;
				} 
			}
			
			for (j = 0; j < nRecords; j++)
			{
				if (strcmp((record+i)->sTopic, (record+j)->sTopic) == 0)
				{
					nTopicNum++;
				}
			}
							
			(record+i)->nQuestionNum = nTopicNum;				
			
			do
			{
				printf("\n||| Enter choice 1: ");
				fgets(((record+i)->sChoicesOne), MAX_CHOICE_LENGTH, stdin);
				(record+i)->sChoicesOne[strlen((record+i)->sChoicesOne)-1] = '\0'; 
							
				printf("||| Enter choice 2: ");
				fgets(((record+i)->sChoicesTwo), MAX_CHOICE_LENGTH, stdin);
				(record+i)->sChoicesTwo[strlen((record+i)->sChoicesTwo)-1] = '\0';  
							
				printf("||| Enter choice 3: ");
				fgets(((record+i)->sChoicesThree), MAX_CHOICE_LENGTH, stdin);
				(record+i)->sChoicesThree[strlen((record+i)->sChoicesThree)-1] = '\0';  
					
			}while((strcmp((record+i)->sAnswer,(record+i)->sChoicesOne) != 0 &&
				    strcmp((record+i)->sAnswer,(record+i)->sChoicesTwo) != 0 &&
					strcmp((record+i)->sAnswer,(record+i)->sChoicesThree) != 0) ||
				   (strcmp((record+i)->sChoicesOne,(record+i)->sChoicesTwo) == 0 ||
					strcmp((record+i)->sChoicesTwo,(record+i)->sChoicesThree) == 0 ||
					strcmp((record+i)->sChoicesOne,(record+i)->sChoicesThree) == 0));
					
		}		
	}
	
} 

/* addRecord returns the number of records present in the aRecord array.
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@return nRecords, it will keep incrementing nRecords as long as there is space and the record is currently nonexisting. 
*/

int 
addRecord(struct record *record, 
		  int nRecords)
{
	int i;
	int bFound = 0;
	
    if (nRecords >= MAX_RECORDS) 
	{
        printf("\n||| The records database is full. Please delete some records to continue.\n");
        return nRecords;
    }
    
	printf("\n-ADD RECORD-\n");
    getInput(record, nRecords);

    for (i = 0; i < nRecords && bFound == 0; i++)
	{
		if (strcmp((record+nRecords)->sQuestion,(record+i)->sQuestion) == 0 &&
		    strcmp((record+nRecords)->sAnswer,(record+i)->sAnswer) == 0)
		{
			bFound = 1;
			printf("\n||| Record already exists.\n");
			return nRecords;
		} 
	}

    printf("\n||| Record successfully added.\n");
	
    return nRecords + 1;
}

/* getUniqueTopic returns the number of Unique Topics found and copies those Unique Topics into a member of struct record for Unique Topics.
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@param int nUniqueTopicNum - set as 0 but updates as long as this function is called
@return nUniqueTopicNum, acts as the number for the amount of Unique Topics present
Pre-condition: The members of the Unique Topics must be reset to null/zero in order for getUniqueTopic to read the current array. 
The reset acts as a buffer for functions that want to get the accurate and updated list of Unique Topics. 
*/

int 
getUniqueTopic(struct record *record, 
               int nRecords, 
			   int nUniqueTopicNum)
{
    int h, k;
    int bFound;
    
    for (h = 0; h < nRecords; h++)
    {
        // Add an additional check to only add sTopic to sUniqueTopics if nQuestionNum is 1
        if ((record+h)->nQuestionNum == 1)
        {
            // Check if sTopic is already in sUniqueTopics
            bFound = 0;
            for (k = 0; k < nRecords; k++)
            {
                if (strcmp((record+h)->sTopic, (record+k)->sUniqueTopics) == 0)
                {
                    bFound++; 
                }
            }
            
            // Add sTopic to sUniqueTopics if it's not found
            if (bFound == 0)
            {
                strcpy((record+nUniqueTopicNum)->sUniqueTopics, (record+h)->sTopic);
                nUniqueTopicNum++;
            }
        }
    } 
    
    return nUniqueTopicNum;
}

/* updateQuestionNumber, when called, updates the aRecords array's question numbers for each topic.
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
*/

void 
updateQuestionNumber(struct record *record, 
                     int nRecords)
{
    int i, j, nTopicNum;
    
    for (i = 0; i < nRecords; i++)
    {
        (record+i)->nQuestionNum = 0;
    }
    
    for (i = 0; i < nRecords; i++) 
    {
        if ((record+i)->nQuestionNum == 0) // Only update question number if not already assigned
        {
            nTopicNum = 1;
            for (j = i+1; j < nRecords; j++) 
            {
                if (strcmp((record+i)->sTopic, (record+j)->sTopic) == 0) 
                {
                    (record+j)->nQuestionNum = nTopicNum;
                    nTopicNum++;
                }
            }
            (record+i)->nQuestionNum = nTopicNum;
        }
    }
}

/* editRecord edits a field in the record
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@param int nUniqueTopicNum - acts as the number for the amount of Unique Topics present, 
							so that it indexes the through the current stored Unique Topics
Pre-condition: Must have at least one record in aRecords array to edit. 
*/

void 
editRecord(struct record *record, 
           int nRecords, 
		   int nUniqueTopicNum)
{
    int h, i, j, k, nEditSelect, nRecordSelect = 0, nFoundQuestion = 0, nRecordIndex = 0, nQuestionIndex[MAX_RECORDS];
    int bFound = 0, bEnd = 0, bTopicTrue = 1, bQuestionTrue = 1, bSkipQuestion = 1, bSameInput = 0, bDuplicate = 0, bEditChoice = 0;
    char sEditInput[MAX_SIZE], ch, ch1, cAnswer;
    
    printf("\n-EDIT RECORD-\n");

    if (nRecords == 0)
    {
    	printf("||| There are no records.\n");
    	bEnd = 1;
	}
	
	while (bEnd == 0)
	{
		printf("~|| Here are the unique topics.\n");
		for (h = 0; h < nRecords; h++)
		{
			if (strcmp((record+h)->sUniqueTopics, "\0") != 0 && h != nUniqueTopicNum)
			{
				printf("TOPIC: '%s'\n", (record+h)->sUniqueTopics);
			}		
		}
		
		i = 0;
		
		do //gets the index i based on the amount of nUniqueTopics and assigns that to nRecordSelect so that in the function, it knows what topic you chose
		{
			if (i == nUniqueTopicNum && bTopicTrue == 1)
			{
				i = 0;
			}
			
			if (strcmp((record+i)->sUniqueTopics, "\0") != 0)
			{
			printf("||| Choose TOPIC: '%s' [y/n]? ", (record+i)->sUniqueTopics);
			scanf(" %c", &ch);
			}
				
			if (ch == 'y' || ch == 'Y')
			{
				bTopicTrue = 0;
			}
			else
			{
				i++;
				bTopicTrue = 1;
			}
		} while (i <= nUniqueTopicNum && bTopicTrue == 1);
			
		nRecordSelect = i; 
		
			
		printf("\n~|| Here are the questions under TOPIC: '%s'.\n", (record+nRecordSelect)->sUniqueTopics);
		
		for (j = 0; j < nRecords; j++) //index through the records and compare sTopic to chosen UniqueTopic name, if it finds the same on any index of record add it to the nQuestionIndex array. If it isnt add 0 instead of the value of j.
		{
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0)
			{
				printf("%d. %s\n", (record+j)->nQuestionNum, (record+j)->sQuestion);
				nQuestionIndex[nFoundQuestion++] = j; 
			}
			else
			{
				nQuestionIndex[nFoundQuestion++] = 0; 
			}
			
		}
			
		do //ask for input if that is the question they want to edit 
		{		
			if (j == nFoundQuestion && bQuestionTrue == 1)
			{
				j = 0;
			}
				
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0 && bQuestionTrue == 1) //if current index's sTopic is same with sUniqueTopics then carry on
			{
				bSkipQuestion = 0;
			}
			
			else //skip current iteration
			{
				bSkipQuestion = 1;
			}
					
			if (bSkipQuestion == 0)
			{
				printf("||| Choose '%d. %s' [y/n]? ", (record+nQuestionIndex[j])->nQuestionNum, (record+nQuestionIndex[j])->sQuestion);
				scanf(" %c", &ch1);
				
				if (ch1 == 'y' || ch1 == 'Y')
				{
					bQuestionTrue = 0;
						
				}
					
				else
				{
					j++;
					bQuestionTrue = 1;
				}
			}
				
			else //skip current iteration and increment j so it goes to the next question
			{
				j++;
				bQuestionTrue = 1;
			}
				
		} while (j <= nFoundQuestion && bQuestionTrue == 1);
			
		nRecordIndex = j; 
		system("cls");	    
	    printf("\n-EDITING RECORD-\n");
		printf("Topic: %s\n", (record+nRecordIndex)->sTopic);
		printf("Question Number: %d\n", (record+nRecordIndex)->nQuestionNum);
		printf("Question: %s\n", (record+nRecordIndex)->sQuestion);
		printf("Choices:\n");
		printf("1. %s\n", (record+nRecordIndex)->sChoicesOne);
		printf("2. %s\n", (record+nRecordIndex)->sChoicesTwo);
		printf("3. %s\n", (record+nRecordIndex)->sChoicesThree);
		printf("Answer: %s\n", (record+nRecordIndex)->sAnswer);
	    printf("\n~|| Choose an option\n");
		printf("[1] Topic\n");
		printf("[2] Question\n");
		printf("[3] Choice 1\n");
		printf("[4] Choice 2\n");
		printf("[5] Choice 3\n");
		printf("[6] Answer\n");
		printf("[7] Exit\n");
		printf("||| Enter an option: ");
		scanf("%d", &nEditSelect);
			    
		switch(nEditSelect)
		{
		    case 1:
				do 
				{
				    fflush(stdin);
				    printf("\n||| Edit topic: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0'; 
				    
				    if (strcmp(sEditInput, (record+nRecordIndex)->sTopic) != 0) 
					{
						
				        strcpy((record+nRecordIndex)->sTopic, sEditInput);
				        updateQuestionNumber(record, nRecords);
				        bSameInput = 0;
				    } 
					
					else 
					{
				        printf("||| Please enter a different topic name.\n");
				        bSameInput = 1;
				    }
				} while (strcmp(sEditInput, (record+nRecordIndex)->sTopic) == 0 && bSameInput == 1);	
				printf("||| Edit successful.\n");
				bEnd = 1;
			   	break;
			case 2:
			   	do 
				{
				    fflush(stdin);
				    printf("||| Edit question: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sQuestion) == 0 || 
				                 strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0;
				    bDuplicate = 0;
				
				    if (bSameInput) 
					{
				        printf("||| Please enter a different question.\n");
				    } 
					
					else 
					{
				        for (k = 0; k < nRecords; k++) 
						{
				            if (strcmp(sEditInput, (record+k)->sQuestion) == 0 && k != nRecordIndex) 
							{
				                printf("||| Matches existing record. Please try again.\n");
				                bDuplicate = 1;
				        	}
				    	}
				
				        if (!bDuplicate) 
						{
				            strcpy((record+nRecordIndex)->sQuestion, sEditInput);
				            bFound = 1;
				        }
				    }
				} while (!bFound && (bSameInput || bDuplicate));
				printf("||| Edit successful.\n");		 
				bEnd = 1;		
			   	break;
			case 3:
				do 
				{
				    fflush(stdin);
				    printf("||| Edit choice one: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sChoicesOne) == 0;
				    bDuplicate = 0;
				
				    if ((strcmp(sEditInput, (record+nRecordIndex)->sChoicesTwo) == 0 || 
				            strcmp(sEditInput, (record+nRecordIndex)->sChoicesThree) == 0) &&
							strcmp(sEditInput, (record+nRecordIndex)->sAnswer) != 0 &&
							!bEditChoice) 
				    {
				        printf("||| Matches existing choice. Please try again.\n");
				        bDuplicate = 1;
				    }
				    else 
				    {
				        if (strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0) 
				        {
				            bEditChoice = 0;
				            do
				            {
				                printf("||| Warning: The choice is the current record's answer.\n");
				                printf("||| Do you still want to edit [y/n]? ");
				                scanf(" %c", &cAnswer);
				
				                if (cAnswer == 'y' || cAnswer == 'Y')
				                {
				                    bEditChoice = 1;
				                    bFound = 1;
				                }
				                else if (cAnswer == 'n' || cAnswer == 'N')
				                {
				                    bEditChoice = 0;
				                    bFound = 1;
				                }
				                else
				                {
				                    printf("||| Invalid input. Please try again.\n");
				                }
				            } while (!bFound);
				        }
				            
				        else 
				        {
				            bEditChoice = 1;
				            bFound = 1;
				        }
				    }
				    
				} while (!bFound && bDuplicate && !bEditChoice); 
				
				if (bEditChoice)
				{
				    strcpy((record+nRecordIndex)->sChoicesOne, sEditInput);
				}
				if (bEditChoice && (cAnswer == 'y' || cAnswer == 'Y'))
				{
					printf("||| Warning: You have saved the current record's answer. I suggest you edit again.\n");
				}
				
				if (bSameInput)
				{
				    	printf("||| Edit unsuccessful, nothing was changed.\n");
				    	bEnd = 1;
				}	
				else
				{
					printf("||| Edit successful.\n");
					bEnd = 1;	
				}
			   	break;
			case 4:
			   	do 
				{
				    fflush(stdin);
				    printf("||| Edit choice two: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sChoicesTwo) == 0;
				    bDuplicate = 0;
				    
				    if ((strcmp(sEditInput, (record+nRecordIndex)->sChoicesOne) == 0 || 
				         strcmp(sEditInput, (record+nRecordIndex)->sChoicesThree) == 0) &&
						 strcmp(sEditInput, (record+nRecordIndex)->sAnswer) != 0 &&
						 !bEditChoice) 
				    {
				        printf("||| Matches existing choice. Please try again.\n");
				        bDuplicate = 1;
				    }
				    else 
				    {
				        if (strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0) 
				        {
				            bEditChoice = 0;
				            do
				            {
				                printf("||| Warning: The choice is the current record's answer.\n");
				                printf("||| Do you still want to edit [y/n]? ");
				                scanf(" %c", &cAnswer);
				
				                if (cAnswer == 'y' || cAnswer == 'Y')
				                {
				                    bEditChoice = 1;
				                    bFound = 1;
				                }
				                else if (cAnswer == 'n' || cAnswer == 'N')
				                {
				                    bEditChoice = 0;
				                    bFound = 1;
				                }
				                else
				                {
				                    printf("||| Invalid input. Please try again.\n");
				                }
				            } while (!bFound);
				        }
				        else 
				        {
				            bEditChoice = 1;
				            bFound = 1;
				        }
				    }
				    
				} while (!bFound && bDuplicate && !bEditChoice); 
				
				if (bEditChoice)
				{
				    strcpy((record+nRecordIndex)->sChoicesTwo, sEditInput);
				}
			   	if (bEditChoice && (cAnswer == 'y' || cAnswer == 'Y'))
				{
					printf("||| Warning: You have saved the current record's answer. I suggest you edit again.\n");
				}
				
				if (bSameInput)
				{
				    	printf("||| Edit unsuccessful, nothing was changed.\n");
				    	bEnd = 1;
				}	
				else
				{
					printf("||| Edit successful.\n");
					bEnd = 1;	
				}
				
			   	break;
			case 5:
				do 
				{
				    fflush(stdin);
				    printf("||| Edit choice three: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sChoicesThree) == 0;
				    bDuplicate = 0;
				
				    if ((strcmp(sEditInput, (record+nRecordIndex)->sChoicesOne) == 0 || 
				         strcmp(sEditInput, (record+nRecordIndex)->sChoicesTwo) == 0) &&
					     strcmp(sEditInput, (record+nRecordIndex)->sAnswer) != 0 &&
						 !bEditChoice) 
				    {
				        printf("||| Matches existing choice. Please try again.\n");
				        bDuplicate = 1;
				    }
				    else 
				    {
				        if (strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0) 
				        {
				            bEditChoice = 0;
				            do
				            {
				                printf("||| Warning: The choice is the current record's answer.\n");
				                printf("||| Do you still want to edit [y/n]? ");
				                scanf(" %c", &cAnswer);
				
				                if (cAnswer == 'y' || cAnswer == 'Y')
				                {
				                    bEditChoice = 1;
				                    bFound = 1;
				                }
				                else if (cAnswer == 'n' || cAnswer == 'N')
				                {
				                    bEditChoice = 0;
				                    bFound = 1;
				                }
				                else
				                {
				                        printf("||| Invalid input. Please try again.\n");
				                    }
				            } while (!bFound);
				        }
				        else 
				        {
				                bEditChoice = 1;
				                bFound = 1;
				        }
				    }
				    
				} while (!bFound && bDuplicate && !bEditChoice); 
				
				if (bEditChoice)
				{
				    strcpy((record+nRecordIndex)->sChoicesThree, sEditInput);
				}
			   	if (bEditChoice && (cAnswer == 'y' || cAnswer == 'Y'))
				{
					printf("||| Warning: You have saved the current record's answer. I suggest you edit again.\n");
				}
				
				if (bSameInput)
				{
				    	printf("||| Edit unsuccessful, nothing was changed.\n");
				    	bEnd = 1;
				}	
				else
				{
					printf("||| Edit successful.\n");
					bEnd = 1;	
				}
			   	break;
			case 6:
			   	do 
				{
				    fflush(stdin);
				    printf("||| Edit answer: ");
				    fgets(sEditInput, MAX_SIZE, stdin);
				    sEditInput[strlen(sEditInput)-1] = '\0';
					
				    bSameInput = strcmp(sEditInput, (record+nRecordIndex)->sAnswer) == 0;
					
				    if (bSameInput) 
					{
						bFound = 0;
				        printf("||| This is the current answer, please enter a different answer.\n");
				    } 
				    
					else 
					{
				        strcpy((record+nRecordIndex)->sAnswer, sEditInput);
				        bFound = 1;
				    }
				    
				} while (!bFound && bSameInput);
				printf("||| Edit successful.\n");
			  	bEnd = 1;
			   	break;
			case 7:
				bEnd = 1;
				break;
			default:
			   	printf("||| Invalid choice. Please try again.\n");
				break;
		}
	}
}

/* deleteRecord deletes a record in the aRecords array
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@param int nUniqueTopicNum - acts as the number for the amount of Unique Topics present, 
							so that it indexes the through the current stored Unique Topics
@return nRecords, decrements nRecords to accurately reflect the amount of current records after deletion.
Pre-condition: Must have at least one record in aRecord array to delete. 
*/

int 
deleteRecord(struct record *record, 
             int nRecords, 
			 int nUniqueTopicNum)
{
	int h, i, j, k, nRecordSelect = 0, nFoundQuestion = 0, nRecordIndex = 0, nQuestionIndex[MAX_RECORDS];
    int bEnd = 0, bTopicTrue = 1, bQuestionTrue = 1, bSkipQuestion = 1, bDeleteRecord = 0;
    char ch, ch1, cDelete;
    
    printf("\n-DELETE RECORD-\n");

    if (nRecords == 0)
    {
    	printf("||| There are no records.\n");
    	bEnd = 1;
	}
	
	while (bEnd == 0)
	{
		printf("~|| Here are the unique topics.\n");
		for (h = 0; h < nRecords; h++)
		{
			if (strcmp((record+h)->sUniqueTopics, "\0") != 0)
			{
				printf("TOPIC: '%s'\n", (record+h)->sUniqueTopics);
			}		
		}
		
		i = 0;
		
		do //gets the index i based on the amount of nUniqueTopics and assigns that to nRecordSelect so that in the function, it knows what topic you chose
		{
			if (i == nUniqueTopicNum && bTopicTrue == 1)
			{
				i = 0;
			}
			
			if (strcmp((record+i)->sUniqueTopics, "\0") != 0)
			{
			printf("||| Choose TOPIC: '%s' [y/n]? ", (record+i)->sUniqueTopics);
			scanf(" %c", &ch);
			}
				
			if (ch == 'y' || ch == 'Y')
			{
				bTopicTrue = 0;
			}
			else
			{
				i++;
				bTopicTrue = 1;
			}
		} while (i <= nUniqueTopicNum && bTopicTrue == 1);
			
		nRecordSelect = i; 
		
			
		printf("\n~|| Here are the questions under TOPIC: '%s'.\n", (record+nRecordSelect)->sUniqueTopics);
		
		for (j = 0; j < nRecords; j++) //index through the records and compare sTopic to chosen UniqueTopic name, if it finds the same on any index of record add it to the nQuestionIndex array. If it isnt add 0 instead of the value of j.
		{
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0)
			{
				printf("%d. %s\n", (record+j)->nQuestionNum, (record+j)->sQuestion);
				nQuestionIndex[nFoundQuestion++] = j; 
			}
			else
			{
				nQuestionIndex[nFoundQuestion++] = 0; 
			}
			
		}
			
		do //ask for input if that is the question they want to edit 
		{		
			if (j == nFoundQuestion && bQuestionTrue == 1)
			{
				j = 0;
			}
				
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0 && bQuestionTrue == 1) //if current index's sTopic is same with sUniqueTopics then carry on
			{
				bSkipQuestion = 0;
			}
			
			else //skip current iteration
			{
				bSkipQuestion = 1;
			}
					
			if (bSkipQuestion == 0)
			{
				printf("||| Delete '%d. %s' [y/n]? ", (record+nQuestionIndex[j])->nQuestionNum, (record+nQuestionIndex[j])->sQuestion);
				scanf(" %c", &ch1);
				
				if (ch1 == 'y' || ch1 == 'Y')
				{
					bQuestionTrue = 0;
						
				}
					
				else
				{
					j++;
					bQuestionTrue = 1;
				}
			}
				
			else //skip current iteration and increment j so it goes to the next question
			{
				j++;
				bQuestionTrue = 1;
			}
				
		} while (j <= nFoundQuestion && bQuestionTrue == 1);
			
		nRecordIndex = j; 	
		k = 0;

		do
		{
			printf("||| Are you sure you want to delete '%d. %s' [y/n]? ", (record+nQuestionIndex[nRecordIndex])->nQuestionNum, (record+nQuestionIndex[nRecordIndex])->sQuestion);
			scanf(" %c", &cDelete);
			if (cDelete == 'y' || cDelete == 'Y')
			{
				for (k = nRecordIndex; k < nRecords; k++)
				{
					strcpy((record+k)->sTopic,(record+(k+1))->sTopic);
					(record+k)->nQuestionNum = (record+(k+1))->nQuestionNum;
					strcpy((record+k)->sQuestion,(record+(k+1))->sQuestion);
					strcpy((record+k)->sChoicesOne,(record+(k+1))->sChoicesOne);
					strcpy((record+k)->sChoicesTwo,(record+(k+1))->sChoicesTwo);
					strcpy((record+k)->sChoicesThree,(record+(k+1))->sChoicesThree);
					strcpy((record+k)->sAnswer,(record+(k+1))->sAnswer);
				}
				
				strcpy((record+nRecords-1)->sTopic, "");
				(record+nRecords-1)->nQuestionNum = 0;
				strcpy((record+nRecords-1)->sQuestion, "");
				strcpy((record+nRecords-1)->sChoicesOne, "");
				strcpy((record+nRecords-1)->sChoicesTwo, "");
				strcpy((record+nRecords-1)->sChoicesThree, "");
				strcpy((record+nRecords-1)->sAnswer, "");	
		
				updateQuestionNumber(record, nRecords);
				
				bDeleteRecord = 1;
				nRecords--;
				bEnd = 1;
			}
			else if (cDelete == 'n' || cDelete == 'N')
			{
				printf("||| Cancelling deletion...\n");
				bEnd = 1;
			}
			
			else
			{
				printf("||| Invalid choice. Please try again.\n");
				bEnd = 0;
			}
			
		} while (!bDeleteRecord && !bEnd) ;
	}
	
	return nRecords;
}

/* stringToInt returns an int after converting it from a string.
@param char *str- string containing number characters
@return integer nResult after subtracting it from a character in a string
Pre-condition: *str must be positive. 
*/

int 
stringToInt(char *str)
{
    int nResult = 0;
    int i = 0;

    /* Convert string to integer by comparing ascii values and subtracting them with 0. 
		Assigning the result to nResult. The i is acts as the counter for which element it is at in the string array.
    */
    while (str[i] != '\0') {
        nResult = nResult * 10 + str[i] - '0';
        i++;
    }

    return nResult;
}

/* importRecord returns the number of added records from the import so long as they arent existing in the aRecords array.
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@return nRecords, it will keep incrementing nRecords as long as there is space and the record is currently nonexisting. 
				 it will keep adding records so long as it has not reached over the max amount of records. 
*/

int 
importRecord(struct record *record, 
             int nRecords)
{
	string30 sFileName;
	int i, j, nCurrentIndex = nRecords;
	int bFoundDuplicate = 0;
	char sReadText[150];
	FILE *fp;
	printf("\n-IMPORT RECORD-\n");
	
	do
	{
		fflush(stdin);
		printf("||| Input filename: ");
		fgets(sFileName, 30, stdin);
		sFileName[strlen(sFileName)-1] = '\0';
		
		fp = fopen(sFileName, "r");
		if (fp == NULL)
		{
			printf("||| File not found. Please try again.\n\n");
		}
	} while (fp == NULL);
	
	i = 0;
	
	while (fgets(sReadText, sizeof(sReadText), fp) != NULL && nCurrentIndex < MAX_RECORDS) 
	{
	    int nLength = strlen(sReadText);
			
	    if (nLength > 0 && sReadText[nLength-1] == '\n') 
		{
	        sReadText[nLength-1] = '\0';
	    }
			
	    switch(i) 
		{
	        case 0:
	            strcpy((record+nCurrentIndex)->sTopic, sReadText);
	            break;
	        case 1:
	            (record+nCurrentIndex)->nQuestionNum = stringToInt(sReadText);
	            break;
	        case 2:
	            strcpy((record+nCurrentIndex)->sQuestion, sReadText);
	            break;
	        case 3:
	            strcpy((record+nCurrentIndex)->sChoicesOne, sReadText);
	            break;
	        case 4:
	            strcpy((record+nCurrentIndex)->sChoicesTwo, sReadText);
	            break;
	        case 5:
	            strcpy((record+nCurrentIndex)->sChoicesThree, sReadText);
	            break;
	        case 6:
	            strcpy((record+nCurrentIndex)->sAnswer, sReadText);
	            break;
	        case 7:
	        	bFoundDuplicate = 0;
	        	for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	        	{
	        		if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
					    strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
					{
						bFoundDuplicate = 1;
					}
				}
				if (!bFoundDuplicate)
				{
					nCurrentIndex++;	
				}
	        	break;
	    }
			
	    i++;
			
	    if (i == 8) 
		{
	        i = 0;
	    }
	}
	/*
	//Conditions these cover, if it is at the end of the file so ignores newline, if there is only one record. 
	The previous block of code at case 7 does have the same purpose, but it does not cover if there is only one record.
	*/
	if (i == 7 && nCurrentIndex < MAX_RECORDS && feof(fp)) 
	{
	    bFoundDuplicate = 0;
	    for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	    {
	        if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
				strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
			{
				bFoundDuplicate = 1;
			}
		}
		if (!bFoundDuplicate)
		{
			nCurrentIndex++;	
		}
	}
		
	if (nCurrentIndex == nRecords)
	{
		printf("||| No records imported.\n");
	}
	else
	{
		printf("||| %d records have been imported.\n", nCurrentIndex - nRecords);
		nRecords = nCurrentIndex;
	}
	
	fclose(fp);
	return nRecords;
}

/* exportRecord returns the name of the record chosen to export so that it can be used in saveRecord. 
				It also exports the record to the chosen filename. 
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@return char* sSavedFileName, this is the inputted filename.
*/

char*
exportRecord(struct record *record, 
             int nRecords)
{
	char *sFileName = (char *)malloc(30 * sizeof(char)); //allocate space to store both strings 
	char *sSavedFileName = (char *)malloc(30 * sizeof(char));
	int i;
	FILE *fp;
	printf("\n-EXPORT RECORD-\n");
	
	if (nRecords == 0)
	{
		printf("||| There are no records.\n");
		printf("||| Returning to Manage Data Menu...\n\n");
		strcpy(sSavedFileName, "");
		system("pause");
	}
	
	else
	{
		do
		{
			fflush(stdin);
			printf("||| Input filename: ");
			fgets(sFileName, 30, stdin);
			sFileName[strlen(sFileName)-1] = '\0';
			strcpy(sSavedFileName, sFileName);
			fp = fopen(sFileName, "w");
			if (fp == NULL)
			{
				printf("||| File not found. Please try again.\n\n");
				strcpy(sSavedFileName, "");
			}
		} while (fp == NULL);	
		
		for (i = 0; i < nRecords; i++)
		{
			fprintf(fp, "%s\n", (record+i)->sTopic);
			fprintf(fp, "%d\n", (record+i)->nQuestionNum);
			fprintf(fp, "%s\n", (record+i)->sQuestion);
			fprintf(fp, "%s\n", (record+i)->sChoicesOne);
			fprintf(fp, "%s\n", (record+i)->sChoicesTwo);
			fprintf(fp, "%s\n", (record+i)->sChoicesThree);
			fprintf(fp, "%s\n", (record+i)->sAnswer);
			
			if (i < nRecords - 1)
			{
				fprintf(fp, "\n");
			}
		}
		fclose(fp);
		printf("||| Records have been exported to %s.\n\n", sFileName);
		system("pause");
		
	}
	free(sFileName); //returns memory that was allocated 
	return sSavedFileName;
}

/* saveRecord imports the contents of char *sSavedFileName to the aRecords array
@param struct record *record - pointer to struct aRecords in main
@param int nRecords - amount of records currently present
@param char* sSavedFileName, receives the saved filename from exportRecord.
@return nRecords, so it stores all the records.
Pre-condition: Must have exported a record at any point of the manage data menu to call this function. 
*/

int 
saveRecord(struct record *record, 
           int nRecords, 
		   char *sSavedFileName)
{
	int i, j, nCurrentIndex = nRecords;
	int bFoundDuplicate = 0;
	char sReadText[150];
	FILE *fp;
	
	fp = fopen(sSavedFileName, "r");
	
	while (fgets(sReadText, sizeof(sReadText), fp) != NULL && nCurrentIndex < MAX_RECORDS) 
	{
	    int nLength = strlen(sReadText);
			
	    if (nLength > 0 && sReadText[nLength-1] == '\n') 
		{
	        sReadText[nLength-1] = '\0';
	    }
			
	    switch(i) 
		{
	        case 0:
	            strcpy((record+nCurrentIndex)->sTopic, sReadText);
	            break;
	        case 1:
	            (record+nCurrentIndex)->nQuestionNum = stringToInt(sReadText);
	            break;
	        case 2:
	            strcpy((record+nCurrentIndex)->sQuestion, sReadText);
	            break;
	        case 3:
	            strcpy((record+nCurrentIndex)->sChoicesOne, sReadText);
	            break;
	        case 4:
	            strcpy((record+nCurrentIndex)->sChoicesTwo, sReadText);
	            break;
	        case 5:
	            strcpy((record+nCurrentIndex)->sChoicesThree, sReadText);
	            break;
	        case 6:
	            strcpy((record+nCurrentIndex)->sAnswer, sReadText);
	            break;
	        case 7:
	        	bFoundDuplicate = 0;
	        	for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	        	{
	        		if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
					    strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
					{
						bFoundDuplicate = 1;
					}
				}
				if (!bFoundDuplicate)
				{
					nCurrentIndex++;	
				}
	        	break;
	    }
			
	    i++;
			
	    if (i == 8) 
		{
	        i = 0;
	    }
	}
	/*
	//Conditions these cover, if it is at the end of the file so ignores newline, if there is only one record. 
	The previous block of code at case 7 does have the same purpose, but it does not cover if there is only one record.
	*/
	if (i == 7 && nCurrentIndex < MAX_RECORDS && feof(fp)) 
	{
	    bFoundDuplicate = 0;
	    for (j = 0; (j < nCurrentIndex && !bFoundDuplicate); j++)
	    {
	        if (strcmp((record+nCurrentIndex)->sQuestion,(record+j)->sQuestion) == 0 &&
				strcmp((record+nCurrentIndex)->sAnswer,(record+j)->sAnswer) == 0)
			{
				bFoundDuplicate = 1;
			}
		}
		if (!bFoundDuplicate)
		{
			nCurrentIndex++;	
		}
	}
	
	nRecords = nCurrentIndex;
	printf("\n||| Records saved successfully.\n");
	
	return nRecords;	
}

/* countPlayers returns the number of players in the game
@param struct players *player - pointer to struct aPlayers in main
@param int nPlayers - amount of players currently present
@return nPlayers, to update the amount of players currently present
Pre-condition: As long as there are players in the aPlayers array
*/

int 
countPlayers(struct players *player, 
             int nPlayers)
{
	int i;
	
	for(i = 0; i < MAX_SIZE; i++)
	{
		if (strlen((player+nPlayers)->sName) > 0)
		{
			return nPlayers + 1;
		}
	}
	
	return nPlayers;
} 

/* playGame is the quiz game, asks for unique topics then displays a question within those topics. 
			Gives a score if question is right. 
@param struct record *record - pointer to struct aRecords in main
@param struct players *player - pointer to struct aPlayers in main
@param int nRecords - amount of records currently present
@param int nPlayers - amount of players currently present
@param int nUniqueTopicNum - acts as the number for the amount of Unique Topics present, 
							so that it indexes the through the current stored Unique Topics
@return nRecords, decrements if a record is removed from the pool of questions to answer. 
Pre-condition: player name must be input in main before starting so as to initialize nPlayers
*/

int 
playGame(struct record *record, 
         struct players *player, 
		 int nRecords, int nPlayers, 
		 int nUniqueTopicNum)
{
	int h, i, j, k, nRecordSelect = 0, nFoundQuestion = 0, nQuestionIndex[MAX_RECORDS];
	int bEnd = 0, bTopicTrue = 1, bQuestionTrue = 1, bSkipQuestion = 1;
	char ch, sChoose[MAX_ANSWER_LENGTH];
	
	system("cls");
	printf("\n-QUIZ GAME-\n");
	if (nRecords == 0)
    {
    	printf("||| There are no records.\n");
    	bEnd = 1;
	}
	
	while (!bEnd)
	{	
		printf("~|| Here are the unique topics.\n");
		for (h = 0; h < nRecords; h++)
		{
			if (strcmp((record+h)->sUniqueTopics, "\0") != 0 && h != nUniqueTopicNum)
			{
				printf("TOPIC: '%s'\n", (record+h)->sUniqueTopics);
			}		
		}
		
		i = 0;
		
		do //gets the index i based on the amount of nUniqueTopics and assigns that to nRecordSelect so that in the function, it knows what topic you chose
		{
			if (i == nUniqueTopicNum && bTopicTrue == 1)
			{
				i = 0;
			}
			
			if (strcmp((record+i)->sUniqueTopics, "\0") != 0)
			{
			printf("||| Choose TOPIC: '%s' [y/n]? ", (record+i)->sUniqueTopics);
			scanf(" %c", &ch);
			}
				
			if (ch == 'y' || ch == 'Y')
			{
				bTopicTrue = 0;
			}
			else
			{
				i++;
				bTopicTrue = 1;
			}
		} while (i <= nUniqueTopicNum && bTopicTrue == 1);
			
		nRecordSelect = i; 
		
		for (j = 0; j < nRecords; j++) //index through the records and compare sTopic to chosen UniqueTopic name, if it finds the same on any index of record add it to the nQuestionIndex array. If it isnt add 0 instead of the value of j.
		{
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+j)->sTopic) == 0)
			{
				nQuestionIndex[nFoundQuestion++] = j; 
			}
			else
			{
				nQuestionIndex[nFoundQuestion++] = 0; 
			}
		}

		do
		{
			int nRandomIndex = rand() % nFoundQuestion; // generate random number between 0 and nFoundQuestion-1
			int nChosenIndex = nQuestionIndex[nRandomIndex]; // get the index of the chosen question
			if (strcmp((record+nRecordSelect)->sUniqueTopics,(record+nChosenIndex)->sTopic) == 0 && bQuestionTrue == 1)
			{
				bSkipQuestion = 0;
			}
			else
			{
				bSkipQuestion = 1;
			}
			if (bSkipQuestion == 0)
			{
				printf("\n-QUIZ GAME-\n");
				printf("~||Question: %s\n", (record+nChosenIndex)->sQuestion);
				printf("Choice one: %s\n", (record+nChosenIndex)->sChoicesOne);
				printf("Choice two: %s\n", (record+nChosenIndex)->sChoicesTwo);
				printf("Choice three: %s\n", (record+nChosenIndex)->sChoicesThree);
				printf("||| What is your answer: ");
				fflush(stdin);
				fgets(sChoose, MAX_ANSWER_LENGTH, stdin);
				sChoose[strlen(sChoose)-1] = '\0';
					
				if (strcmp(sChoose, (record+nChosenIndex)->sAnswer) == 0)
				{
					printf("\n||| Answer correct, you get a point!\n");
					(player+nPlayers)->nGameScore++;
				}
					
				else
				{
					printf("\n||| Wrong answer.\n");
				}
					
				nQuestionIndex[nRandomIndex] = nQuestionIndex[nFoundQuestion-1]; // replace the chosen index with the last index in the array
				nFoundQuestion--; // decrement the size of the array
					
				for (k = nChosenIndex; k < nRecords; k++)
				{
					strcpy((record+k)->sTopic,(record+(k+1))->sTopic);
					(record+k)->nQuestionNum = (record+(k+1))->nQuestionNum;
					strcpy((record+k)->sQuestion,(record+(k+1))->sQuestion);
					strcpy((record+k)->sChoicesOne,(record+(k+1))->sChoicesOne);
					strcpy((record+k)->sChoicesTwo,(record+(k+1))->sChoicesTwo);
					strcpy((record+k)->sChoicesThree,(record+(k+1))->sChoicesThree);
					strcpy((record+k)->sAnswer,(record+(k+1))->sAnswer);
				}
					
				strcpy((record+nRecords-1)->sTopic, "");
				(record+nRecords-1)->nQuestionNum = 0;
				strcpy((record+nRecords-1)->sQuestion, "");
				strcpy((record+nRecords-1)->sChoicesOne, "");
				strcpy((record+nRecords-1)->sChoicesTwo, "");
				strcpy((record+nRecords-1)->sChoicesThree, "");
				strcpy((record+nRecords-1)->sAnswer, "");	
			
				updateQuestionNumber(record, nRecords);	
				nRecords--;
				bQuestionTrue = 0;
				bEnd = 1;
			}
		} while (bQuestionTrue == 1);

		if (nFoundQuestion == 0)
		{
			printf("\n||| No more questions found.");
			bEnd = 1;
		}	
	}
	
	return nRecords;
}

/* viewScores shows a leaderboard ranked from highest to lowest scores,
			  if the player scores the same score as their existing one, their duplicate score wont be shown. 
@param struct players *player - pointer to struct aPlayers in main
@param int nPlayers - amount of players currently present
*/

void 
viewScores(struct players *player, 
           int nPlayers)
{
    int i, j, k;
    int nTempGameScore;
    int bEnd = 0;
    string30 sTempName;

    printf("~|| Leaderboard: \n");

    if (nPlayers == 0)
    {
        printf("||| There are no players yet.\n\n");
        bEnd = 1;
    }

    while (!bEnd)
    {
        // Remove duplicate scores and names
        for (i = 0; i < nPlayers; i++)
        {
            for (j = i + 1; j < nPlayers;)
            {
                if (strcmp((player+i)->sName, (player+j)->sName) == 0 && 
				    (player+i)->nGameScore == (player+j)->nGameScore)
                {
                    for (k = j; k < nPlayers - 1; k++)
                    {
                        strcpy((player+k)->sName, (player+k+1)->sName);
                        (player+k)->nGameScore = (player+k+1)->nGameScore;
                    }
                    nPlayers--;
                }
                else
                {
                    j++;
                }
            }
        }

        // Bubble sort name and score
        for (i = 0; i < nPlayers ; i++)
        {
            for (j = 0; j < nPlayers - i - 1; j++)
            {
                if ((player+j)->nGameScore < (player+(j+1))->nGameScore)
                {
                    nTempGameScore = (player+j)->nGameScore;
                    (player+j)->nGameScore = (player+(j+1))->nGameScore;
                    (player+(j+1))->nGameScore = nTempGameScore;

                    strcpy(sTempName, (player+j)->sName);
                    strcpy((player+j)->sName, (player+(j+1))->sName);
                    strcpy((player+(j+1))->sName ,sTempName);
                }
            }
        }

        for (i = 0; i < nPlayers; i++)
        {
            printf("%d. %s - SCORE: %d\n", i+1, (player+i)->sName, (player+i)->nGameScore);
        }

        printf("\n");
        bEnd = 1;
    }
}

/* importScores imports the names and scores of previous runs.
@param struct players *player - pointer to struct aPlayers in main
@param int nPlayers - amount of players currently present
@return nPlayers so that view scores looks at all the imported players stored in the aPlayers array. 
Pre-condition: score.txt must exist 
*/

int 
importScores(struct players *player, 
             int nPlayers)
{
	string30 sReadName;
    int i, nReadScore, nCurrentIndex = nPlayers;
    int bExists;
    FILE *fp;
    fp = fopen("score.txt", "r");
    
    while ( fscanf(fp, "%s%d", sReadName, &nReadScore) == 2)
    {
        bExists = 0;
        
        for (i = 0; i < nCurrentIndex && !bExists; i++)
        {
            if ((strcmp((player+i)->sName, sReadName) == 0) && 
			    ((player+i)->nGameScore == nReadScore))
            {
                bExists = 1;
            }
        }
        
        if (!bExists)
        {
            strcpy((player+nCurrentIndex)->sName, sReadName);
            (player+nCurrentIndex)->nGameScore = nReadScore;
            nCurrentIndex++;
        }
    }
    
    nPlayers = nCurrentIndex;
    fclose(fp);
    return nPlayers;
}

/* exportScores exports the names and scores of the current run. Does not write duplicates.
@param struct players *player - pointer to struct aPlayers in main
@param int nPlayers - amount of players currently present
Pre-condition: score.txt must exist 
*/

void 
exportScores(struct players *player, 
             int nPlayers)
{
	int i, j;
	int bExported;
	FILE *fp;
	fp = fopen("score.txt", "w");
		
	for (i = 0; i < nPlayers && !bExported; i++)
	{
		// Check if this name and score have already been exported
		bExported = 0;
		for (j = 0; j < i; j++) 
		{
			if (strcmp((player+i)->sName, (player+j)->sName) == 0 &&
			    (player+i)->nGameScore == (player+j)->nGameScore) 
			{
				bExported = 1;
			}
		}
		
		if (!bExported) 
		{
			fprintf(fp, "%s\n", (player+i)->sName);
			fprintf(fp, "%d\n", (player+i)->nGameScore);
			if (i < nPlayers - 1) 
	        {
	            fprintf(fp, "\n");
	        }
		}
	}
	fclose(fp);
}
