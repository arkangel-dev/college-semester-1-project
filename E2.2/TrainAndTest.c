//
//  TrainAndTest.c
//  MLCoursework
//
//  This is a fairly inefficient implentation that does not use any dynamic memory allocation
// because that wouldnot be safe on the DEWIS marking system
//
//  Created by Jim Smith on 06/02/2017.
//  Copyright © 2017 Jim SmithJim Smith. All rights reserved.
//

#include "TrainAndTest.h"



//declare this array as static but make it available to any function in this file
//in case we want to store the training examples  and use them later
static    double myModel[NUM_TRAINING_SAMPLES][ NUM_FEATURES];
//even if each item in the training set is from a diffferent class we know how many there are
static char myModelLabels[NUM_TRAINING_SAMPLES];

static int trainingSetSize=0;

int  train( double **trainingSamples, char *trainingLabels, int numSamples, int numFeatures)
{
    int returnval = 1;
    int sample, feature;
    
  
    
    //clean the model because C leaves whatever is in the memory
    for (sample=0; sample < NUM_TRAINING_SAMPLES; sample++) {
        for (feature=0; feature<NUM_FEATURES; feature++) {
            myModel[sample][feature] = 0.0;
        }
    }
    
    //sanity checking
    if ( numFeatures > NUM_FEATURES || numSamples > NUM_TRAINING_SAMPLES) {
        fprintf(stdout,"error: called train with data set larger than spaced allocated to store it");
        returnval=0;
    }
    

    
    
    //make a simple copy of the data we are being passed but don't do anything with it
    //I'm just giving you this for the sake of people less familiar with pointers etc.
    
     
     if(returnval==1) {
        //store the labels and the feature values
        trainingSetSize = numSamples;
        int index,feature;
        for (index=0; index < numSamples; index++) {
            myModelLabels[index] = trainingLabels[index];
            for (feature=0; feature < numFeatures; feature++) {
                myModel[index][feature] = trainingSamples[index][feature];
            }
        }
        fprintf(stdout,"data stored locally \n");
    }//end else
    
    
    //now you could do whatever you like with the data
    //for example,  you could populate some rules etc.
    //you were given pseudocode in semester 1 to do this
    // you could also normalise the data to remove scaling effects if you want to use something like a MLP or kNN
    //just remember that anything that you want to acess in your predictLabel() function
    //needs to be declared static at the top of this file - as I have done for the "myModel"  and myModelLabels data .
    
    
    
    return returnval;
}

char  predictLabel(double *sample, int numFeatures)
{

	// alright, So Im fucking annoyed because we procasinated for a better part of two whole months.
	// so lets into it, because I have a ton of shows I need to finish watching...

	// first we define the floating point value variables
	char prediction = 'c';
	float currentdist, result, sum, wcomponent, xcomponent, ycomponent, zcomponent;
	float nearestDistance = 9999e45;
	
	// then we define the int variables
	int currentTest, BestIndex, feature = 0;
	
	// then we are going to loop trought all the values of the of the
	// dataset.. 
	for (currentTest = 0; currentTest < trainingSetSize; currentTest++){
		
		// this sum variable will store the distance the
		// current dataset has scored and will be reset to zero, because why the hell not?
		sum = 0;
		result = 0;
		
		
			
			// this part is a bit complicated so its a bit difficult to explain and I really dont want to
			// so I won't...
			for (feature = 0; feature < numFeatures; feature++){
				sum = sum + pow(myModel[currentTest][feature] - sample[feature], 2);
			}
			
			sum = sqrt(sum);

		// then we check if we got the lowest value that the
		// the system has gotten so far and if so we update the lowest value to that value
		// also we update the index with the best performing node and shiit
		if (sum < nearestDistance) {
            nearestDistance = sum;
            BestIndex = currentTest;
        }

	}
	
	// now we are going to use that best index value and 
	// get the model label for that BestIndex index and return
	// that shit and get the system to return our results...
    prediction = myModelLabels[BestIndex];
    return prediction;
    
}


