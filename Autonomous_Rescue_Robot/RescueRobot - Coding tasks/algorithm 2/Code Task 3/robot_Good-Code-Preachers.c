#include <stdio.h>
#include "robot_Good-Code-Preachers.h"

// IMPLEMENT THIS FUNCTION
// ALLOWED RETURN VALUES:
// 1: North, 2: East, 3: South, 4: West, 5: Toggle watern/land mode
int c = 0;

int move(char* world) {
    int width = 21;
    int robot_index = 0;
    int target_index = 0;
    int initial_postion = 0;
    int base = 0;


    for (int i = 0; i < 200; i++) {
        if (world[i] == 'R') { robot_index = i; }
        if (world[i] == 'T') { target_index = i; }
        if (world[i] == 'X') { base = i; }
    }

    if (target_index != 0) {

        int rx = robot_index;
        int tx = target_index;
        int ry = robot_index;
        int ty = target_index;
        int robox, roboy, tarx, tary;
        robox = rx % width;
        roboy = ry / width;
        tarx = tx % width;
        tary = ty / width;
        printf("robot coordinate =  (%d %d)\n", robox, roboy);
        printf("target coordinate =  (%d %d)\n", tarx, tary);
        //printf("robotindex targetindex (%d %d)\n", robot_index, target_index);
        int step_n, step_s, step_e, step_w, step_nw, step_ne, step_sw, step_se;
        step_n = robot_index - (width);
        step_s = robot_index + (width);
        step_e = robot_index + 1;
        step_w = robot_index - 1;
        step_nw = step_n - 1;
        step_ne = step_n + 1;
        step_sw = step_s - 1;
        step_se = step_s + 1;

        if (driving_mode != 1) {

            if (world[step_n] == 'O' || world[step_n] == 'T' || world[step_n] == 'X') {

                if (world[step_nw] == 'O' || world[step_nw] == world[step_ne]) {
                    if (robox > tarx && roboy > tary || robox == tarx && roboy > tary || robox < tarx && roboy > tary) {
                        return 1;
                    }
                }

            }
            if (world[step_n] == '~') {
                if (robox > tarx && roboy > tary || robox == tarx && roboy > tary || robox < tarx && roboy > tary) {
                    return 5;
                }
            }
            if (world[step_s] == 'O' || world[step_s] == 'T' || world[step_s] == 'X') {

                if (world[step_se] == 'O' || world[step_sw] == world[step_se]) {
                    if (robox < tarx && roboy < tary || robox == tarx && roboy < tary || robox > tarx && roboy < tary) {
                        return 3;
                    }
                }
            }
            if (world[step_s] == '~') {
                if (robox < tarx && roboy < tary || robox == tarx && roboy < tary || robox > tarx && roboy < tary) {
                    return 5;
                }
            }
            if (world[step_w] == 'O' || world[step_w] == 'T' || world[step_w] == 'X') {
                if (world[step_se] == 'O') {
                    if (robox > tarx && roboy == tary) {
                        return 4;
                    }
                }
                if (world[step_se] == '#' && world[step_sw] == '#') {

                    if (robox > tarx && roboy == tary) {
                        return 4;
                    }
                }

            }
            if (world[step_w] == '~') {
                if (robox > tarx && roboy == tary) {
                    return 5;
                }
            }
            if (world[step_e] == 'O' || world[step_e] == 'T' || world[step_e] == 'X') {
                if (robox < tarx && roboy == tary) {
                    return 2;
                }
            }
            if (world[step_e] == '~') {
                if (robox < tarx && roboy == tary) {
                    return 5;
                }
            }
            if (world[step_w] == '#' || world[step_w] == '*') {
                return 3;
            }
            if (world[step_s] == '#' || world[step_s] == '*') {
                return 2;
            }
            if (world[step_nw] == '#' || world[step_nw] == '*') {
                return 4;
            }
            if (world[step_e] == '#' || world[step_e] == '*') {
                return 1;
            }
            if (world[step_se] == '#' || world[step_se] == '*') {
                return 2;
            }
            if (world[step_n] == '#' || world[step_n] == '*') {
                return 4;
            }
        }
        if (driving_mode != 0) {

            if (world[step_n] == '~' || world[step_n] == 'T') {
                if (robox > tarx && roboy > tary || robox == tarx && roboy > tary || robox < tarx && roboy > tary) {
                    return 1;
                }

            }
            if (world[step_s] == '~' || world[step_s] == 'T') {
                if (robox < tarx && roboy < tary || robox == tarx && roboy < tary || robox > tarx && roboy < tary) {
                    return 3;
                }
            }
            if (world[step_w] == '~' || world[step_w] == 'T') {
                if (robox > tarx && roboy == tary) {
                    return 4;
                }
            }
            if (world[step_e] == '~' || world[step_e] == 'T') {
                if (robox < tarx && roboy == tary) {
                    return 2;
                }
            }
            if (world[step_n] == 'O') {
                return 5;
            }
            if (world[step_s] == 'O') {
                return 5;
            }
            if (world[step_e] == 'O') {
                return 5;
            }
            if (world[step_w] == 'O') {
                return 5;
            }

        }


    }
    else {
        int rx = robot_index;
        int tx = base;
        int ry = robot_index;
        int ty = base;
        int robox, roboy, tarx, tary;
        robox = rx % width;
        roboy = ry / width;
        tarx = tx % width;
        tary = ty / width;
        printf("robot coordinate =  (%d %d)\n", robox, roboy);
        printf("base coordinate =  (%d %d)\n", tarx, tary);
        //printf("robotindex targetindex (%d %d)\n", robot_index, target_index);
        int step_n, step_s, step_e, step_w, step_nw, step_ne, step_sw, step_se;
        step_n = robot_index - (width);
        step_s = robot_index + (width);
        step_e = robot_index + 1;
        step_w = robot_index - 1;
        step_nw = step_n - 1;
        step_ne = step_n + 1;
        step_sw = step_s - 1;
        step_se = step_s + 1;

        if (driving_mode != 1) {

            if (world[step_n] == 'O' || world[step_n] == 'T' || world[step_n] == 'X') {
                if (world[step_nw] == 'O' || world[step_nw] == world[step_ne]) {
                    if (robox > tarx && roboy > tary || robox == tarx && roboy > tary || robox < tarx && roboy > tary) {
                        return 1;
                    }
                }
            }
            if (world[step_n] == '~') {
                if (robox > tarx && roboy > tary || robox == tarx && roboy > tary || robox < tarx && roboy > tary) {
                    return 5;
                }
            }
            if (world[step_s] == 'O' || world[step_s] == 'T' || world[step_s] == 'X') {
                if (world[step_sw] == world[step_se]) {
                    if (robox < tarx && roboy < tary || robox == tarx && roboy < tary || robox > tarx && roboy < tary) {
                        return 3;
                    }
                }
            }
            if (world[step_s] == '~') {
                if (robox < tarx && roboy < tary || robox == tarx && roboy < tary || robox > tarx && roboy < tary) {
                    return 5;
                }
            }
            if (world[step_w] == 'O' || world[step_w] == 'T' || world[step_w] == 'X') {

                if (world[step_se] == 'O') {
                    if (robox > tarx && roboy == tary) {
                        return 4;
                    }
                }
                if (world[step_se] == '#' && world[step_sw] == '#') {
                    if (robox > tarx && roboy == tary) {
                        return 4;
                    }
                }
            }
            if (world[step_w] == '~') {
                if (robox > tarx && roboy == tary) {
                    return 5;
                }
            }
            if (world[step_e] == 'O' || world[step_e] == 'T' || world[step_e] == 'X') {
                if (robox < tarx && roboy == tary) {
                    return 2;
                }
                if (world[step_s] == '#' && world[step_n] == '#' && world[step_w] == '#')
                {
                    return 2;
                }
                if (world[step_s] == '#' && world[step_n] == '#') {
                    return 2;
                }
            }
            if (world[step_e] == '~') {
                if (robox < tarx && roboy == tary) {
                    return 5;
                }
            }

            if (world[step_w] == '#' || world[step_w] == '*') {
                return 3;
            }
            if (world[step_s] == '#' || world[step_s] == '*') {
                return 2;
            }
            if (world[step_nw] == '#' || world[step_nw] == '*') {
                return 4;
            }
            if (world[step_e] == '#' || world[step_e] == '*') {
                return 1;
            }
            if (world[step_se] == '#' || world[step_se] == '*') {
                return 2;
            }
            if (world[step_n] == '#' || world[step_n] == '*') {
                return 4;
            }
        }
        if (driving_mode != 0) {

            if (world[step_n] == '~') {
                if (robox > tarx && roboy > tary || robox == tarx && roboy > tary || robox < tarx && roboy > tary) {
                    return 1;
                }

            }
            if (world[step_s] == '~') {
                if (robox < tarx && roboy < tary || robox == tarx && roboy < tary || robox > tarx && roboy < tary) {
                    return 3;
                }
            }
            if (world[step_w] == '~') {
                if (robox > tarx && roboy == tary) {
                    return 4;
                }
            }
            if (world[step_e] == '~') {
                if (robox < tarx && roboy == tary) {
                    return 2;
                }
            }
            if (world[step_n] == 'O') {
                return 5;
            }
            if (world[step_s] == 'O') {
                return 5;
            }
            if (world[step_e] == 'O') {
                return 5;
            }
            if (world[step_w] == 'O') {
                return 5;
            }

        }

    }
}