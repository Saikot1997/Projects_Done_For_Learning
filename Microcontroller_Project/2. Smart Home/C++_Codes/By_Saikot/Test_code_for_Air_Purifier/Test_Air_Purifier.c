#include <stdio.h>
#include <stdlib.h>


int sensorData[]={45,65,98,87,58,30,156,-456};
int outputTest[];
int expectedOutput[]={1,1,0,0,1,1,0,1};

void validationTestRun();
void printTestResult();


int main(void) {
	validationTestRun();
	printTestResult();

	return EXIT_SUCCESS;
}



void validationTestRun(){

 int ExpectedQuality = 75;
 for(int i = 0;i<8;i++)
 {
    if(sensorData[i]<ExpectedQuality)
   {
    outputTest[i]=1;
   }


   else
   {
    outputTest[i]=0;

   }
 }

}

void printTestResult(){


	for(int j=0;j<8;j++)
    {
       if(outputTest[j]==expectedOutput[j])
       {
        printf("test Successful & result is valid for event %d\n ",sensorData[j]);
       }

       else
       {
           printf("expected output didn't match with test Output for sensor data input  = %d\n",sensorData[j]);
       }

    }

}
