
/*  file NQueenschecker.c
*
* Author Jim Smith 16-10-14
*/



#include "NQueenschecker.h"





/*
 * void CalculateNumberOfVulnerableQueensForWorkijgCandidate()
 * this functions tells us how many vulnerable queens there are in the current working candidate
 * no return value as the number is written into the structure that holds our candidae solution
 */
int numberOfCallsMade =0;
void CalculateNumberOfVulnerableQueensForWorkingCandidate()
{
    int howManyAreVulnerable = 0; //counter to store the number of vulnerable queens in this solution
    int attackingQueen; //loop variable - we will consider the queens one by one
    int defendingQueen; // the queens being attacked
    int row ; //loop variable

	extern candidateSolution workingCandidate;


    //lets make a copy of the relevant bits of the solution we are concerned with
	// we don;t really need ot do this but it is faster thn repeatedly referring back via a pointer
	// and avoids the risk of accidntally changing one of the values
    int columnPositions[N];
    int numberToConsider = workingCandidate.numberOfDefinedValues;
    for ( row=0;row < numberToConsider;row++)
        columnPositions[row] = workingCandidate.variableValues[row];
    
    
    //start by considering the queen in row 0 against all the other defined queens
    // remember that not all queens may be defined, and that if , say 5 are,
    // then the last comparison we want to do is whether 4th can take the 5th, or we'll be double counting
    for (attackingQueen=0;  attackingQueen < numberToConsider -1; attackingQueen++)
      {
        // so we need to consider the next queen, up to the number defined in this solution
        for(defendingQueen = attackingQueen+1; defendingQueen < numberToConsider; defendingQueen++)
          {
            //are the queens in the same column?
            if( columnPositions[attackingQueen] == columnPositions[defendingQueen])
                howManyAreVulnerable ++;
            // are they on a diagonal running from top left to bottom right?
            if (( attackingQueen - defendingQueen) == (columnPositions[attackingQueen] - columnPositions[defendingQueen]))
                howManyAreVulnerable ++;
            // are they on a diagonal running from top right to bottom left?
            if (( attackingQueen - defendingQueen ) == (  columnPositions[defendingQueen] - columnPositions[attackingQueen]))
                howManyAreVulnerable ++;
          }
      }
    
    //we'e looped through all the queens so now we can store the value
    workingCandidate.score = howManyAreVulnerable;
    
    
    //finally increment the numberof soltions that have bene tested
    numberOfCallsMade++;
}



/* void PrintCandidateSolution (candidateSolution *solution)
 * generic function to print to screen any candidate solution we choose
 *
 * first parameter is the address of the candidate
 * all the error handling happens within the function so there is no return
 */
void PrintCandidateSolution (candidateSolution * solution)
{
    int column, row;
    
    //check it exists
    if (solution == (candidateSolution *) NULL )
        //exit if it does not
        PrintThisMessageAndExit("tried to print a solution %d which is a non-valid index\n ");
    
    else
        //print something if it exists
      {
        //what we print depends on the solution
        if (solution->score >0)
          {
            //print a message about how invalid it was
            printf(" solution  has %d  queens, of which the number vulnerable is %d \n",
                   solution->numberOfDefinedValues,
                   solution->score);
          }
        
        else
          {
            //print out its details
            printf("  printing valid partial solution, Number of Queens is %d\n", solution->numberOfDefinedValues);
            
            //top of board
            for (column=0; column < N; column ++)
                printf("----");
            printf("\n");
            
            //now each row with a line underneath
            for (row=0;row < N; row++)
              {
                //contents - with left hand cell edge
                for (column=0; column < N; column ++)
                    if(solution->variableValues[row]== column)
                        printf("| Q ");
                    else
                        printf("|   ");
                
                //right hand edge
                printf("|\n");
                //then line underneath
                for (column=0; column < N; column ++)
                    printf("----");
                printf("\n");
                
              }//end of row
          }//end of printing partial solution
      }//end of else statement block for test dealing with valid/invalid soltuion
    
}




// simple wrappera to make the code clearer
void AddQueenToNextRowInColumn(int col)
{
    if(col< N)
        ExtendWorkingCandidateByAddingValue(col);
    else
        PrintThisMessageAndExit("tried to add a queen with column number too high");
    
}




void MoveQueenInRowToNewCol(int row, int col)
{
    
    if(col <N)
        ChangeWorkingCandidateByReplaceValueinPlaceParam1_WithValueParam2(row, col);
    else
           PrintThisMessageAndExit("tried to move a queen with column number too high");
    
}


//this isthe function we call when the goal is found
void PrintFinalSolutionAndExit(void)
{
    //make sure we can access the proposed solution
    extern candidateSolution workingCandidate;
    int position;
    extern int numberOfSolutionsTested;
    //check that working candidate has all colours correct
    if ( workingCandidate.numberOfDefinedValues!=N)
        PrintThisMessageAndExit("Error, working candidate does not have every piece defined");
    if(workingCandidate.score!=0)
        PrintThisMessageAndExit("error, working candiate has vulnerable queens");
    
    
    //print the solution
    PrintWorkingCandidate();
    
    
    //else //print in format to be automatically checked
  {
    printf("success: after %d attemptss \n", numberOfCallsMade);
    
#ifndef FINALTEST
    for(position=0;position < 3200000; position++)
        ;
#endif
  }
    exit(0);
    
}


