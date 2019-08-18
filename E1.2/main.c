#include <stdio.h>
#include <stdlib.h>
#include "PathFindingSpecificDefinitions.h"
#include "StructureDefinitions.h"
#include "SolutionListOperations.h"
#include "PathFindingSpecificSolutionOperations.h"
#include  "worlds.h"

candidateSolution workingCandidate;
candidateList  currentListOfCandidates; 
candidateList listOfExaminedCandidates; 
                                        
char currentMap[MAXX][MAXY];

int main(int argc, const char * argv[])
{
    
    int indexOfSolutionWeAreLookingAt;
    int closestSoFar;
    int closestEstimatedDistance; 
    int x,y;

    CleanListsOfSolutionsToStart();
    CleanWorkingCandidate();
    ReadComandLineAndSetMap(argc,argv);
    
	 for(x=MINX; x<MAXX;x++){
        for(y=MINY;y<MAXY;y++){
            if(currentMap[x][y] != (char)OBSTACLE){
                workingCandidate.variableValues[XCOORD] = workingCandidate.variableValues[PARENTXCOORD] = x;
                workingCandidate.variableValues[YCOORD] = workingCandidate.variableValues[PARENTYCOORD] =  y;
                workingCandidate.numberOfDefinedValues=4;
                if ( x == STARTX && y == STARTY){
					workingCandidate.score = 0;
				} else {
					workingCandidate.score = BIGDIST;
				}
                AddWorkingCandidateToCurrentList();
                currentMap[x][y] = OPEN;
              }
		}
	 }
    workingCandidate.variableValues[XCOORD] = workingCandidate.variableValues[PARENTXCOORD] = STARTX;
    workingCandidate.variableValues[YCOORD] = workingCandidate.variableValues[PARENTYCOORD] =  STARTY;
    workingCandidate.score = 0;
    while( IsSolutionAtCoordinates(workingCandidate, ENDX, ENDY) == 0) {
        closestSoFar = 0;
        closestEstimatedDistance = currentListOfCandidates.listEntries[0].score;
        for(indexOfSolutionWeAreLookingAt=1;indexOfSolutionWeAreLookingAt <= currentListOfCandidates.indexOfLastEntryAdded;indexOfSolutionWeAreLookingAt++) {
            if (currentListOfCandidates.listEntries[indexOfSolutionWeAreLookingAt].score < closestEstimatedDistance) {
				closestSoFar = indexOfSolutionWeAreLookingAt;
                closestEstimatedDistance = currentListOfCandidates.listEntries[indexOfSolutionWeAreLookingAt].score;
              }
		}
        indexOfSolutionWeAreLookingAt = closestSoFar;
        CopySolutionFromCurrentListIntoWorkingCandidate(indexOfSolutionWeAreLookingAt);
        RemoveSolutionFromCurrentList(indexOfSolutionWeAreLookingAt);
        currentMap[workingCandidate.variableValues[XCOORD]][workingCandidate.variableValues[YCOORD]] = OCCUPIED;
        if (IsSolutionAtCoordinates(workingCandidate, ENDX, ENDY) == 0) {
            AddWorkingCandidateToExaminedList();
            currentMap[workingCandidate.variableValues[XCOORD]][workingCandidate.variableValues[YCOORD]] = CLOSED;
            UpdateDistancesOfUnvisitedNeighboursOfWorkingCandidate(); 
		} else {
			PrintFinalSolutionAndExit();
        }
      }
    return 0;
}



