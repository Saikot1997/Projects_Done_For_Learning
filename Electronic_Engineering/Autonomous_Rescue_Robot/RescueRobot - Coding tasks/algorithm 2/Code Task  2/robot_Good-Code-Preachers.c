#include "robot_Good-Code-Preachers.h"

// IMPLEMET THIS FUNCTION
// ALLOWED RETURN VALUES:
// 1: North, 2: East, 3: South, 4: West, 5: Toggle watern/land mode
int move(char* world, int robot_index, int target_index) {

    int width = 21;


    for (int i = 0; i < 200; ++i) {
        if (world[i] == 'R') {
            robot_index = i;
            break;
        }
    }
    for (int i = 0; i < 200; ++i) {
        if (world[i] == 'T') {
            target_index = i;
            break;
        }
    }
    int rx = robot_index;
    int tx = target_index;
    int robox, roboy, tarx, tary;
    robox = rx % width;
    roboy = robot_index / width;
    tarx = tx % width;
    tary = target_index / width;
    printf("robot coordinate =  (%d %d)\n", robox, roboy);
    printf("target coordinate =  (%d %d)\n", tarx, tary);
    //printf("robotindex targetindex (%d %d)\n", robot_index, target_index);

    int step_n, step_s, step_e, step_w;
    step_n = robot_index - (width + 1);
    step_s = robot_index + (width + 1);
    step_e = robot_index + 1;
    step_w = robot_index - 1;
    if (tarx > robox)
    {
        //if (step_e == 'O') 
        return 2;



    }
    else if (tarx < robox)
    {
        //if (step_w == 'O')

        return 4;


    }
    else if (tarx = robox && tary > roboy)
    {
        //if (step_s == 'O')

        return 3;


    }
    else if (tarx = robox && tary < roboy)
    {
        return 1;
    }
}