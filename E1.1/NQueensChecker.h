/*
* file NQueensChecker.h
* declares the function that checks the number of vulnerable queens in a candidate solution
*
* Author Jim Smith 16-10-14
*/


#include <stdio.h>
#include <stdlib.h>
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
/**
 @file
 @brief the "test function for NQueens
 */


/**
 @brief The test function for NQueens.
 
 Assumes the presence of a variable: candidateSolution  workingCandidate.
 This functions tells us how many vulnerable queens there are in the current working candidate.
  No return value as the number is written into workingCandidate.numberOfVulnerableQueens,
  and errors are dealt with via calls to PrintThisMessageAndExit()
 */
void CalculateNumberOfVulnerableQueensForWorkingCandidate();


/*!
 @brief  Problem-specific function to print candidate solution to screen.
 
 @param solution pointer to solution to be printed
 */
void PrintCandidateSolution (candidateSolution * solution);

/*!
 @brief check and printsout final solution and how long it took to find
*/
void PrintFinalSolutionAndExit(void);



/**
@brief NQueensfunction to add a new queen on board in the working candidate
@param col: intger vslue between 0 and N-1 - column to put next queen in
 
 Calls the generic function void ExtendWorkingCandidateByAddingValue(int newValue);
 
 Errors (e.g. col >N) are dealt with via PrintThisMesageAndExit()
 */
void AddQueenToNextRowInColumn(int col);


/**
 @brief NQueens function to move a queen to a new position
 @param row  row index of queen to be moved
 @param col   new column inde to place queen
 
 Calls the generic function void ChangeWorkingCandidateByReplaceValueinPlaceParam1_WithValueParam2(int positionToChange, int newValue);
 Error Handling dealt with by printing message and exiting
 */
void MoveQueenInRowToNewCol(int row, int col);
