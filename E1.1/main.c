
/*
 * File:   main.cpp
 * Author: j4-smith
 * N-Queens example in C
 * First Created on 25 April 2014, 18:42
 * Modified in light of student progress 
 
 * Rewritten Oct 2015 to use more generic solution structures 
 * and functions with NQueens-specific names that call the functions that modify the
 */

#pragma warning (disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "NQueensChecker.h"


candidateSolution workingCandidate;//this one will hold the soltion we arecurrently considering
candidateList  currentListOfCandidates; // this list will store all the soltion we;ve created but not examined yet
candidateList listOfExaminedCandidates; // this is where we will store all the ones we're done with

extern int numberOfCallsMade; // correction offset. 

//************************ don't edit anything above this line***********************//
int main(int argc, const char * argv[])
{
    /* the next set of variables get used within our main function
     * but aren't declared globally becuase we don't want the other functions to change them inadvertently */
    int numberOfCompleteSolutionsFound = 0; //simple flag to let us know whether we have stopped
    int valueToAdd; // used when we extend the working candidate
	
    //start off by emptying the lists of candidate solutions
    CleanListsOfSolutionsToStart();
	CleanWorkingCandidate();
    
    /* So now let's start by creating our first solution
     * which we do by filling the values into the variable we declared as the workingCandidate
     * We'll begin by putting the first queen into column ), or specified from the command line
   */
   valueToAdd = 0;
   int columnPos = 0;

   if (argc == 2)
   {
	   columnPos = atoi(argv[1]);
	   if (columnPos >= N || columnPos < 0)
		   PrintThisMessageAndExit("Invalid Input");
   }
    
    //and we can put this as our first item in the list to start the process
	AddQueenToNextRowInColumn(columnPos);
	AddWorkingCandidateToCurrentList();

  //Now we will go into a loop examining solutions until we find one that is full and has no vulnerable queens

  for (; numberOfCompleteSolutionsFound != 1;) {

    // Copy solution and remove it from current list
    CopySolutionFromCurrentListIntoWorkingCandidate(currentListOfCandidates.indexOfLastEntryAdded);
    RemoveFromListParam1_CandidateSolutionAtIndexParam2(&currentListOfCandidates, currentListOfCandidates.indexOfLastEntryAdded);
    
		// test the candidate.
		CalculateNumberOfVulnerableQueensForWorkingCandidate();

		if (workingCandidate.score == 0) {
			if (valueToAdd != N - 1) {
				// generate new solutions here using the copy system, and then clear the working candidate for testing. 
				valueToAdd++;

				// add one queen to board and then use loop to add solutions for all column postions and add solutions to current list. 
				AddQueenToNextRowInColumn(valueToAdd);
				
				int i;
				for (i = 0; i < N; i++) {
					MoveQueenInRowToNewCol(valueToAdd, i);
					AddWorkingCandidateToCurrentList();
				}

			} else { numberOfCompleteSolutionsFound = 1;}

		} else {
			// dump bad solutions into examined list for future refrence. And update search level when appropriate. 
      int ObjectIndexer = currentListOfCandidates.indexOfLastEntryAdded;
			if (workingCandidate.numberOfDefinedValues > currentListOfCandidates.listEntries[ObjectIndexer].numberOfDefinedValues) {
				valueToAdd = (currentListOfCandidates.listEntries[ObjectIndexer].numberOfDefinedValues - 1);
	    }
			AddWorkingCandidateToExaminedList();
		}
}

	PrintFinalSolutionAndExit();    
}



