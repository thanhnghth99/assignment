/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 10.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

string notebook1(string ntb1) {
    fstream fileNtb1;
    fileNtb1.open(ntb1, ios::in);
    string line1, line2;
    int n1;

    // Read line Freq/First/<n1>
    getline(fileNtb1, line1);

    int k = 0;
    string number;
    for (int i = (line1.length() - 3); i < line1.length(); i++){
        if (line1[i] < '0' || line1[i] > '9')
            return "000000000";
        else{
            // Insert the last 3 character into new string
            number.push_back(line1[i]);
            k++;
        }
    }
    
    // Convert string to int numbers
    n1 = atoi(number.c_str());
    string str;
    if(n1 >= 1 && n1 <= 999){
        getline(fileNtb1, line2);

        // Remove spaces  
        for (int i = 0; i < line2.length(); i++){
            if (line2[i] != ' ')
                str.push_back(line2[i]);
        }  

        // Take n1 first characters string
        str.erase(str.begin() + n1, str.end());

        // Sort characters (bubble sort)
        for(int i = 0; i < str.length() -  1; i++){
            for(int j = 0; j < str.length() - 1 - i; j++){
                if (str[j] > str[j + 1]){
                    char temp;
                    temp = str[j + 1];
                    str[j + 1] = str[j];
                    str[j] = temp;
                }
            }
        }
        string result;
        for (int i =  0; i < 10; i++){
            char temp = 48 + i;
            int count = 0;
            for (int j = 0; j < str.length(); j++){
                if (str[j] == temp)
                    count++;
            }

            if (count > 10)
                count /= 10;
            
            string s = to_string(count);
            result.insert(i, s);
        }
        return result;
    }
    else
        return "000000000";

    return "000000000";
}

string notebook2(string ntb2) {
    fstream fileNtb2;
    fileNtb2.open(ntb2, ios::in);
    string line1, line2;
    int n2;

    // Read line <n2>
    getline(fileNtb2, line1);

    for (int i = 0; i < line1.length(); i++){
        if (line1[i] < '0' || line1[i] > '9')
            return "1111111111";
    }

    if (line1.length() != 5)
        return "1111111111";
    
    // Convert string to int numbers
    n2 = atoi(line1.c_str());
    
    // Count cntP
    string str;
    string substr[2] = {"Pink", "pink"};
    int cntP = 0;
    if(n2 >= 5 && n2 <= 100){
        while(getline(fileNtb2, line2)){
            for (int i = 0; i < 2; i++){
                size_t nPos = line2.find(substr[i], 0); // first occurrence
                while(nPos != string::npos){
                    nPos = line2.find(substr[i], nPos + 1);
                    cntP++;
                }                
            }
        }         

        // Count number of digits
        int count = 0;
        int n = cntP;
        while(n){
            n /= 10;
            count++;
        }

        if(count < 5)
            cntP = pow(cntP, 2);
        
        // Convert int numbers to string
        string result;
        result = to_string(cntP);
        
        // Insert number 9
        int len = result.length();
        for (int i = len; i < 10; i++){
            result.insert(i, "9");
        }

        return result;
    }
    else
        return "000000000";
    
    return "000000000";
}

string notebook3(string ntb3) {
    fstream fileNtb3;
    fileNtb3.open(ntb3, ios::in);
    string data, temp;
    const int row = 10;
    const int col = 10;
    int arr[row][col];
    
    // Convert string data in file to 2D array
    int number = 0;                                                                                                                                                                        
    stringstream ss;        
    int m = 0, n = 0;
    while (getline(fileNtb3, data)){  // Gets entire line from fileNtb3 and stores in data                                                                                                             
        ss.str(data); // Puts the line into a stringstream
        while(ss >> number){
            // Handles our 2D array indexes.
            // When col reaches 10, set it back to 0 and increment the row.
            if(n == 10){
                m++;
                n = 0;
            }

            arr[m][n] = abs(number);
            n++;

            // Eliminate any commas and spaces between each number.
            while(ss.peek() == '|' || ss.peek() == ' ')
                ss.ignore();
        }
        ss.clear();
    }                                                                                                                                                                                       

    for(int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){

            // Elements above the principal diagonal
            // Find nearest prime number more than given number
            if((i + j) >  (2 * i)){
                // Check whether arr[i][j] is prime number or not
                bool isPrime = true;
                if (arr[i][j] < 2)
                    isPrime = false;
                for (int k = 2; k <= arr[i][j]/2; k++){
                    if (arr[i][j] % k == 0)
                        isPrime = false;
                }
                
                // Find next prime number
                if (isPrime == false){
                    if (arr[i][j] < 2)
                        arr[i][j] = 2;

                    for (int nextPrime = arr[i][j]; ; nextPrime++){
                        bool check = true;
                        for (int t = 2; t <= nextPrime/2; t++){
                            if (nextPrime % t == 0)
                                check = false;
                        }
                        if (check == true){
                            arr[i][j] = nextPrime;
                            break;
                        }
                    }
                }
            }

            // Elements below the principal diagonal
            // Find nearest Fibonacci number more than given number
            if((i + j) <  (2 * i)){
                // Check whether arr[i][j] is Fibonacci number or not
                bool isFibonacci = false;
                int a = 0, b = 1;
                if (arr[i][j] == a || arr[i][j] == b)
                    isFibonacci = true;

                int sum = a + b;
                while (sum <= arr[i][j]){
                    if (sum == arr[i][j])
                        isFibonacci == true;
                    
                    a = b;
                    b = sum;
                    sum = a + b;
                }

                // Find nearest Fibonacci number
                if (isFibonacci == false){
                    for(int nextFibonacci = arr[i][j]; ; nextFibonacci++){
                        bool check = false;
                        int a2 = 0, b2 = 1;
                        int sum2 = a2 + b2;
                        while (sum2 <= nextFibonacci){
                            if (sum2 == nextFibonacci){
                                check = true;
                                break;
                            }
                            
                            a2 = b2;
                            b2 = sum2;
                            sum2 = a2 + b2;
                        }
                        if (check == true){
                            arr[i][j] = nextFibonacci;  
                            break;
                        }                        
                    }
                }
            }
        }
    }

    // Sort the last 3 numbers each row in ascending order
    for(int i = 0; i < row; i++){
        // Start bubble sort
        for (int j = 0; j < col - 1; j++){
            for (int k = col - 3; k < col - j - 1; k++){
                if (arr[i][k] > arr[i][k + 1]){
                    int temp = arr[i][k + 1];
                    arr[i][k + 1] = arr[i][k];
                    arr[i][k] = temp;
                }
            } 
        }
    }

    int index[10];
    int nPos;
    for (int i = 0; i < row; i++){
        int max =  0;
        for (int j = 0; j < col; j++){
            if (arr[i][j] >= max){
                max = arr[i][j];
                nPos = j;
            }
        }
        index[i] = nPos;
    }   

    // Convert int array to string
    string result;
    for(int i = 0; i < 10; i++){
        string s = to_string(index[i]);
        result.insert(i, s);
    }
    return result;
}

string generateListPasswords(string pwd1, string pwd2, string pwd3) {
    
    const int size = 10;
    // Integer array pi = pwdi
    int p1[size], p2[size], p3[size];

    // Integer array pi_pj = (pwdi,pwdj)
    int p1_p2[size], p1_p3[size], p2_p3[size];
    string pwd1_pwd2, pwd2_pwd3, pwd1_pwd3;

    // Integer array pij_pk = (<g(pwdi,pwdj)>,pwdk)
    int p12_p3[size], p1_p23[size], p12_p13[size];
    string pwd12_pwd3, pwd1_pwd23, pwd12_pwd13;

    // <g(pwd1,pwd2)>
    int div1 = 0, mod1 = 0;
    for (int i = 0; i < size; i++){
        p1[i] = pwd1[i] - 48;
        p2[i] = pwd2[i] - 48;
        p1_p2[i] = p1[i] + p2[i] + div1;
        if(p1_p2[i] >= 10){
            div1 = p1_p2[i] / 10;
            mod1 = p1_p2[i] % 10;
            p1_p2[i] = mod1;
        }
        else
            div1 = 0;

        string s = to_string(p1_p2[i]);
        pwd1_pwd2.insert(i, s);
    }

    // <g(pwd1,pwd3)>
    int div2 = 0, mod2 = 0;
    for (int i = 0; i < size; i++){
        p3[i] = pwd3[i] - 48;
        p1_p3[i] = p1[i] + p3[i] + div2;
        if(p1_p3[i] >= 10){
            div2 = p1_p3[i] / 10;
            mod2 = p1_p3[i] % 10;
            p1_p3[i] = mod2;
        }
        else
            div2 = 0;

        string s = to_string(p1_p3[i]);
        pwd1_pwd3.insert(i, s);
    }

    // <g(pwd2,pwd3)>
    int div3 = 0, mod3 = 0;
    for (int i = 0; i < size; i++){
        p2_p3[i] = p2[i] + p3[i] + div3;
        if(p2_p3[i] >= 10){
            div3 = p2_p3[i] / 10;
            mod3 = p2_p3[i] % 10;
            p2_p3[i] = mod3;
        }
        else
            div3 = 0;

        string s = to_string(p2_p3[i]);
        pwd2_pwd3.insert(i, s);
    }

    // <g(<g(pwd1,pwd2)>,pwd3)>
    int div4 = 0, mod4 = 0;
    for (int i = 0; i < size; i++){
        p12_p3[i] = p1_p2[i] + p3[i] + div4;
        if(p12_p3[i] >= 10){
            div4 = p12_p3[i] / 10;
            mod4 = p12_p3[i] % 10;
            p12_p3[i] = mod4;
        }
        else
            div4 = 0;

        string s = to_string(p12_p3[i]);
        pwd12_pwd3.insert(i, s);
    }

    // <g(pwd1,<g(pwd2,pwd3)>)>
    int div5 = 0, mod5 = 0;
    for (int i = 0; i < size; i++){
        p1_p23[i] = p1[i] + p2_p3[i] + div5;
        if(p1_p23[i] >= 10){
            div5 = p1_p23[i] / 10;
            mod5 = p1_p23[i] % 10;
            p1_p23[i] = mod5;
        }
        else
            div5 = 0;

        string s = to_string(p1_p23[i]);
        pwd1_pwd23.insert(i, s);
    }

    int div6 = 0, mod6 = 0;
    for (int i = 0; i < size; i++){
        p12_p13[i] = p1_p2[i] + p1_p3[i] + div6;
        if(p12_p13[i] >= 10){
            div6 = p12_p13[i] / 10;
            mod6 = p12_p13[i] % 10;
            p12_p13[i] = mod6;
        }
        else
            div6 = 0;

        string s = to_string(p12_p13[i]);
        pwd12_pwd13.insert(i, s);
    }


    string result;
    result = pwd1 + ';' + pwd2 + ';' + pwd3 + ';' 
            + pwd1_pwd2 + ';' + pwd1_pwd3 + ';' + pwd2_pwd3 + ';' 
            + pwd12_pwd3 + ';' + pwd1_pwd23 + ';' + pwd12_pwd13;

    return result;    
}

bool chaseTaxi(
    int arr[100][100],
    string points,
    string moves,
    string & outTimes,
    string & outCatchUps
) {
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            arr[i][j] = -9;
        }
    }

    string str, data, p;
    int arrCoor[10];

    for (int i = 0; i < points.length(); i++){
        data += points[i];
    }

    // Read points
    int index = 0;
    for (int i = 0; i < data.length(); i++){
        int k = 1;
        while (data[i] == '(' || data[i] == ','){
            str.push_back(data[i + k]);
            k++;
            if (data[i + k] == ')' || data[i + k] == ',')
                break;
        }
        
        if(str != ""){
            arrCoor[index] = atoi(str.c_str());
            index++;
            str.erase(str.begin(), str.end());
        }
    }

    // Array of X and Y coordinates
    int size = index/2 + 1;
    int arrX[size], arrY[size];
    
    arrX[0] = arrY[0] = 0;
    int t1 = 0;
    for (int i = 1; i < size; i++){
        arrX[i] = arrCoor[t1];
        t1 += 2;
    }

    int t2 = 1;
    for (int i = 1; i < size; i++){
        arrY[i] = arrCoor[t2];
        t2 += 2;
    }

    // Taxi moving
    int row = 0, col = 0, taxi = 0;
    arr[0][0] = {0};
    for (int i = 0; i < moves.length(); i++){
        if (moves[i] == 'U' || moves[i] == 'D'){
            if(moves[i] == 'D'){
                row++;
                if (row > 99){
                    row = 99;
                    continue;
                }
                taxi += 9;
                arr[row][col] = taxi;
            }
            else{
                row--;
                if (row < 0){
                    row = 0;
                    continue;
                }
                taxi += 9;
                arr[row][col] = taxi;
            }
        }

        else if (moves[i] == 'R' || moves[i] == 'L'){
            if(moves[i] == 'R'){
                col++;
                if (col > 99){
                    col = 99;
                    continue;
                }
                taxi += 9;
                arr[row][col] = taxi;
            }
            else{
                col--;
                if (col < 0){
                    col = 0;
                    continue;
                }
                taxi += 9;
                arr[row][col] = taxi;
            }
        }
        
    }
    //  Check whether Sherlock can catch up taxi or not
    bool check = false;
    int d = 0, sh = 0, m = 0, n = 0;
    for(int i = 1; i < size; i++){
        d = abs(arrX[i - 1] - arrX[i]) + abs(arrY[i - 1] - arrY[i]);
        sh += d * 14;
        if (check == true){
            string s1 = "-";
            outTimes.insert(m, s1);
            outTimes.insert(m + s1.length(), ";");
            m += s1.length() + 1;
        }
        else{
            string s = to_string(sh);
            outTimes.insert(m, s);
            outTimes.insert(m + s.length(), ";");
            m += s.length() + 1;
        }    
        if (sh > arr[arrX[i]][arrY[i]]){
            if (check == true){
                string s1 = "-";
                outCatchUps.insert(n, s1);
                outCatchUps.insert(n + s1.length(), ";");
                n += s1.length() + 1;    
                continue;            
            }
            check = false;
            string N = "N";
            outCatchUps.insert(n, N);
            outCatchUps.insert(n + N.length(), ";");
            n += N.length() + 1;                
        }
        else{
            check = true;
            string Y = "Y";
            outCatchUps.insert(n, Y);
            outCatchUps.insert(n + Y.length(), ";");
            n += Y.length() + 1;                
        }
    
        
    }

    outTimes.erase(outTimes.end() - 1);
    outCatchUps.erase(outCatchUps.end() - 1);

    if (check == true)
        return true;

    return false;
}

string enterLaptop(string tag, string message) {
    
    fstream fileTag;
    fileTag.open(tag, ios::in);
    string line1, line2;
    int n3;

    // Read file tag and message
    getline(fileTag, line1);
    getline(fileTag, line2);

    // Find email from file tag
    string email;
    for (int i = 7; i < line1.length(); i++){
        email.push_back(line1[i]);
    } 

    // Find <n3> from file tag
    string number;
    for (int i = 9; i <= 10; i++){
        if (line2[i] >= '0' && line2[i] <= '9'){
            number.push_back(line2[i]);
        }
    }
    n3 = atoi(number.c_str());
   
    string result;
    result = email + ';';
    int i = 1;
    while(i <= n3){
        result.append(message);
        i++;
    }

    return result;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
