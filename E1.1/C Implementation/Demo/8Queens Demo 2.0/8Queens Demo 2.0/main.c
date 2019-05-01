/*
* File:   main.cpp
* Author: j4-smith
*N-Queens example in C
* First Created on 25 April 2014, 18:42
* Modified in light of student progress

* Rewritten Oct 2015 to use more generic solution structures
* and functions with NQueens-specific names that call the functions that modify the
*/


#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"


candidateSolution workingCandidate;//this one will hold the soltion we are currently considering
candidateList  currentListOfCandidates; // this list will store all the solution we've created but not examined yet
candidateList listOfExaminedCandidates; // this is where we will store all the ones we're done with

//workingCandidate
//currentListOfCandidates open list
//listOfExaminedCandidates closed list
										//************************ don't edit anything above this line***********************//


int main(int argc, const char * argv[])
{

	/* the next set of variables get used within our main function
	* but aren't declared globally becuase we don't want the other functions to change them inadvertently */
	int numberOfCompleteSolutionsFound = 0; //simple flag to let us know whether we have stopped
	int numberOfSolutionsExamined = 0; //simple counter
	int indexOfSolutionWeAreLookingAt; //index in list of current solution being examined
	int newLength, valueToAdd; // used when we extend the working candidate

	

	//start off by emptying the lists of candidate solutions
	CleanListsOfSolutionsToStart();
	CleanWorkingCandidate();

	/* So now let's start by creating our first solution
	* which we do by filling the values into the variable we declared as the workingCandidate
	* We'll begin by putting the first queen into column ), or specified from the command line
	*/
	valueToAdd = 0;
	if (argc == 2)
	{
		valueToAdd = atoi(argv[1]);
		if (valueToAdd >= N || valueToAdd <0)
			PrintThisMessageAndExit("Invalid Input");
	}

	//adding first queen
	AddQueenToNextRowInColumn(valueToAdd);
	CalculateNumberOfVulnerableQueensForWorkingCandidate(); //should return zero because there is only one queen:)
	numberOfSolutionsExamined = 1;

	//and we can put this as our first item in the list to start the process
	AddWorkingCandidateToCurrentList(); //closed list
	PrintWorkingCandidate();
	
	//Var
	int EnterHere = 0; // Used as a sort of boolean flag // SAM : BUT FOR WHAT!?!?

	CalculateNumberOfVulnerableQueensForWorkingCandidate();
	
	//Var
	//column counter is the column no. of queen
	int as = workingCandidate.numberOfDefinedValues - 1; int columnCounter = 0; 
	
	//Now we will go into a loop examining solutions until we find one that is full and has no vulnerable queens
	for (; workingCandidate.score != 0 || workingCandidate.numberOfDefinedValues != 8;) // SAM : Loop if score is not 0 or number of defined values is not 8... I think 
	{	
		//add queen if board is correct
		if (workingCandidate.score == 0 && EnterHere == 0) // SAM : If Vulnurble queens = 0 and there is no queen here
		{ 
			numberOfSolutionsExamined++; /// SAM : This is the counter... The one printed below
			AddWorkingCandidateToCurrentList(); // SAM : Add the solution to the openlist 
			columnCounter = 0; 
			AddQueenToNextRowInColumn(columnCounter); 
			CalculateNumberOfVulnerableQueensForWorkingCandidate();
		}
		
		//if the board is not correct and the queen cant move, remove queen and increment column of previous queen by 1
		else if (columnCounter == 7 && workingCandidate.score != 0 || EnterHere == 1)
		{	//resetting EnterHere as we have entered the loop
			EnterHere = 0;

			//remove current queen and backtrack to previous queen and erase the last board which was in open list. 
			CopySolutionFromCurrentListIntoWorkingCandidate(--numberOfSolutionsExamined);
			RemoveSolutionFromCurrentList(numberOfSolutionsExamined);

			//loading the last queen row(Queen no.) and column			
			int queenNo = workingCandidate.numberOfDefinedValues - 1;
			as = workingCandidate.numberOfDefinedValues - 1; //which queen it is
			columnCounter = workingCandidate.variableValues[queenNo]; //column queen is at
			
			//checking the queens column and moving if possible
			if (columnCounter != 7) 
			{
				MoveQueenInRowToNewCol(as, ++columnCounter); CalculateNumberOfVulnerableQueensForWorkingCandidate();
			}

			//if not backtracking by setting the boolean flag as true
			else if (columnCounter == 7) 
			{ 
				EnterHere = 1; 
			}

		}

		//move queen by a column 
		else if (workingCandidate.score != 0) 
		{
			MoveQueenInRowToNewCol(as, ++columnCounter); 
			CalculateNumberOfVulnerableQueensForWorkingCandidate();
		}
		
		//Update number of queens
		as = workingCandidate.numberOfDefinedValues - 1;
	}
	
	PrintFinalSolutionAndExit();
	return 0;
}
