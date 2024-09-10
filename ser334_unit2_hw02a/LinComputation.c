/**
* (basic description of the program or class)
*
* Completion time: 0.5 hrs
*
* @author Hung-ju, Acuna
* @version 2024-09-01
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>

int main(void)
{
	//Add a prompt for the number of cylinders to sum. Make sure to use the control
	//symbol for integers. [2 points]
    int num_cylinders;
    float radius, height, volume, sum_volume;
	printf("Enter the number of cylinders:");
    scanf("%d", &num_cylinders);

	//Create a loop based on the number of cylinders the user enters. [2 points]
	for(int i=0; i<num_cylinders; i++){
		//    Within the loop, prompt for height and radius parameters (allow floating
		//    point numbers), and calculate the volume for that particular cylinder.
		//    [4 points]
          printf("How is the height of cylinder %d:\n", i+1);
          scanf("%f", &height);
          printf("How is the radius of cylinder %d:\n", i+1);
          scanf("%f", &radius);

          volume = 3.14159 * height * radius * radius;
          sum_volume = sum_volume + volume;
	}

	//Display the total volume sum back to the user. Make sure to use the right control
	//symbol. [2 points]
    printf("The sum of all volumes is %f\n", sum_volume);

	return 0;
}