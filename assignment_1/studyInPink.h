/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2022
    * Author: Tran Huy
    * Date: 06.01.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

int firstMeet(int& EXP1, int& EXP2, const int& E1){
    
    if (E1 < 0 || E1 > 999){
        return -999;
    }
    // Cast float type for E1
    float E1_new = static_cast<float>(E1);
    
    if (E1 >= 0 && E1 <= 399){
        if (E1 >= 0 && E1 <= 49)
            EXP2 += 25;
        else if (E1 >= 50 && E1 <= 99)
            EXP2 += 50;
        else if (E1 >= 100 && E1 <= 149)
            EXP2 += 85;
        else if (E1 >= 150 && E1 <= 199)
            EXP2 += (25 + 50);
        else if (E1 >= 200 && E1 <= 249)
            EXP2 += (25 + 85);
        else if (E1 >= 250 && E1 <= 299)
            EXP2 += (50 + 85);
        else
            EXP2 += (25 + 50 + 85);

        if (E1 % 2 == 0){
            EXP1 -= floor(E1_new/5);
        }
    
        else{
            EXP1 += ceil(E1_new/10);
        }
    }

    if(E1 >= 400 && E1 <= 999){
        if (E1 >= 400 && E1 <= 499)
            EXP2 += ceil(E1_new/7 + 9);
        else if (E1 >= 500 && E1 <= 599)
            EXP2 += ceil(E1_new/9 + 11);
        else if (E1 >= 600 && E1 <= 699)
            EXP2 += ceil(E1_new/5 + 6);
        else if (E1 >= 700 && E1 <= 799){
            EXP2 += ceil(E1_new/7 + 9);
            if(EXP2 > 200){
                EXP2 += ceil(E1_new/9 + 11);
            }
        }
        else{
            EXP2 += ceil(E1_new/7 + 9 + E1_new/9 + 11);
            if(EXP2 > 600){
                EXP2 += ceil(E1_new/5 + 6);
                EXP2 += ceil(EXP2 * 0.15);
            }
        }

        EXP1 -= floor(E1 * 0.1);
    }

    if (EXP1 > 900)
        EXP1 = 900;
    else if (EXP1 < 0)
        EXP1 = 0;

    if (EXP2 > 900)
        EXP2 = 900;
    else if (EXP2 < 0)
        EXP2 = 0;

    int sumEXP = EXP1 + EXP2;
    return sumEXP;
}

int investigateScene(int& EXP1, int& EXP2, int& HP2, int& M2, const int& E2){
 
    if (E2 < 0 || E2 > 999){
        return -999;
    }
    
    float E2_new = static_cast<float>(E2);
    float d1 = E2_new/9 + 10;
    float d2 = E2_new * 0.35;

    if (E2 >= 0 && E2 <= 299){
        EXP2 += ceil(d1);
        EXP1 += ceil(d1/3);
    }

    if (E2 >= 300 && E2 <= 499){
        EXP2 += ceil(d1) + ceil(d2);
        EXP1 += ceil(d1/3) + ceil(d2/3);
    }

    

    if (E2 >= 500 && E2 <= 999){
        float d3 = (d1 + d2) * 0.17;
        EXP2 += ceil(d1) + ceil(d2) + ceil(d3);
        EXP1 += ceil(d1/3) + ceil(d2/3) + ceil(d3/3);
    }

    HP2 -= floor(pow(E2_new, 3)/pow(2, 23));

    if (E2 % 2 == 0)
        M2 += ceil((E2_new*E2_new) / 50);

    if (EXP1 > 900)
        EXP1 = 900;
    else if (EXP1 < 0)
        EXP1 = 0;

    if (EXP2 > 900)
        EXP2 = 900;
    else if (EXP2 < 0)
        EXP2 = 0;

    if (HP2 > 999)
        HP2 = 999;
    else if (HP2 < 0)
        HP2 = 0;

    if (M2 > 2000)
        M2 = 2000;
    else if (M2 < 0)
        M2 = 0;

    int sum = EXP2 + HP2 + M2 + EXP1;
    return sum;
}

int traceLuggage(int& HP1, int& EXP1, int& M1, const int& E3){

    if (E3 < 0 || E3 > 999){
        return -999;
    }

    // Checking whether the luggage is found or not
    bool check = false;
    // Count the numbers of time the luggage is found
    int count = 0;

    // Road 1
    int P1 [] = {1, 3, 5, 7, 9, 11, 13, 15, 17};

    // Number of element of P1
    int n1 = sizeof(P1) / sizeof(P1[0]);

    // Transformation
    for (int i = 0; i < n1; i++){
        P1[i] = (P1[i] + E3) % 26 + 65;
    }
    
    int k1 = 1;
    // Find the luggage
    for (int i = 0; i < n1; i++){
        if (P1[i] == 80){
            k1 += i;
            HP1 -= (P1[i] * k1 * 2);
            EXP1 += (1000 - P1[i] * k1) % 101;
            M1 -= floor(k1 * E3/9);
            check = true;
            count++;
            break;
        }
        else {
            check = false;
        } 
    }
    if (check == false)
        M1 -= floor(n1*n1*E3/9);

    // Road 2
    int P2 [] = {2, 3, 5, 7, 11, 13, 17};

    int n2 = sizeof(P2) / sizeof(P2[0]);

    // First transformation
    int s = 0;
    for (int i = 0; i < n2; i++){
        P2[i] = (P2[i] + E3) % 26;
        s += P2[i];
    }

    float s_new = static_cast<float>(s);
    int m = ceil(s_new/n2);

    // Second transformation
    for (int i = 0; i < n2; i++){
        P2[i] = (P2[i] + s + m) % 26 + 65;
    }
    
    int k2 = 1;
    // Find the luggage
    for (int i = 0; i < n2; i++){
        if (P2[i] == 80){
            if (check == false || check == true) {
                k2 += i;
                HP1 -= (P2[i] * k2 * 2);
                EXP1 += (1000 - P2[i] * k2) % 101;
                M1 -= floor(k2 * E3/9);
                check = true;
                count++;
                break;
            }
        }
        else {
            check = false;
        }
    }
    if (check == false)
        M1 -= floor(n2*n2*E3/9);

    // Road 3
    int P3 [] = {4, 16, 36, 64, 100, 144, 196, 256, 324, 400, 484, 576, 676, 784, 900, 1024, 1156, 1296, 1444, 1600};

    int n3 = sizeof(P3) / sizeof(P3[0]);

    // First transformation
    for (int i = 0; i < n3; i++){
        P3[i] = (P3[i] + E3*E3) % 113;
    }

    // Find max number in sequence
    int max = P3[0];
    for (int i = 1; i < n3; i++){
        if (P3[i] > max)
            max = P3[i];
    }
    
    // Second transformation
    for (int i = 0; i < n3; i++){
        P3[i] = (int(ceil((P3[i] + E3)/float(max)))) % 26 + 65;
    }
    
    int k3 = 1;
    // Find the luggage
    for (int i = n3 - 1; i >= 0; i--){
        if (P3[i] == 80){
            if (check == false || check == true) {
                HP1 -= floor(P3[i] * k3 * 3);
                EXP1 += (3500 - P3[i]*k3) % 300;
                M1 -= floor(k3 * E3/9);
                check = true;
                count++;
                break;
            }
        }
        else{
            check = false;
        } 
        k3++;
    }
    if (check == false)
        M1 -= floor(n3*n3*E3/9);

    // Road 4
    int P4[] = {31, 28, 31, 30, 31, 30 ,31, 31, 30, 31, 30 ,31};
    
    int n4 = sizeof(P4) / sizeof(P4[0]);

    // First transformation
    for (int i = 0; i < n4; i++){
        P4[i] = (P4[i] + int(pow(ceil(E3/float(29)), 3))) % 9;
    }

    float min = P4[0], min_idx;
    // Find max number in sequence
    for (int i = 1; i < n4; i++){
        if (P4[i] < min){
            min = P4[i];
            min_idx = i + 1;
        }
    }

    // Second transformation
    for (int i = 0; i < n4; i++){
        P4[i] = int((P4[i] + E3)*ceil((min/min_idx))) % 26 + 65;
    }
    
    int k4 = 1;
    // Find the luggage
    for (int i = (n4 - 1); i >= 0; i--){
        if (P4[i] == 80){
            if (check == false || check == true) {
                HP1 -= floor(P4[i] * k4 * 4);
                EXP1 += (4500 - P4[i] * k4) % 400;
                M1 -= floor(k4 * E3/9);
                check = true;
                count++;
                break;
            }
        }
        else {
            check = false;
        }
        k4++;
    }
    if (check == false)
        M1 -= floor(n4*n4*E3/9);
    

    if (EXP1 > 900)
        EXP1 = 900;
    else if (EXP1 < 0)
        EXP1 = 0;

    if (HP1 > 999)
        HP1 = 999;
    else if (HP1 < 0)
        HP1 = 0;

    if (M1 > 2000)
        M1 = 2000;
    else if (M1 < 0)
        M1 = 0;
    
    int sum = 0;
    if (count == 0){
        HP1 -= (59 * E3) % 900;
        EXP1 -= (79 * E3) % 300;

        if (HP1 > 999)
            HP1 = 999;
        else if (HP1 < 0)
            HP1 = 0;

        if (EXP1 > 900)
            EXP1 = 900;
        else if (EXP1 < 0)
            EXP1 = 0;

        return -1;
    }
    else {
        sum = HP1 + EXP1 + M1;
        return sum;
    }
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
