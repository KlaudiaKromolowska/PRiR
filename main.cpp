#include <stdio.h>
#include <omp.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Dany zbiór liczb całkowitych przynajmniej 5 cyfrowych
// Oblicz średnią arytmetyczną liczb spełniających warunki:
//      liczba nalezy do przedzialu <x, y>
//      suma cyfr > ustalona wartość

// OpenMP, MPI i hybrydowe MPI + OpenMP

int* read_data(int amount_of_data) {

    int* data = new int[amount_of_data];
    ifstream newfile;
    
    newfile.open("Numbers.txt"); //open a file to perform read operation using file object
    if (newfile.is_open())
    {
        string tp;
        int i = 0;
        for(i=0; i < amount_of_data; i++)
        {
            getline(newfile, tp);
            data[i] = stoi(tp);
        }
        newfile.close(); //close the file object.
    }
    return data;
}

int sum_of_digits(int num){
    int result = 0;
    do {
        result = result + num%10;
        num=num/10;
    }
    while(num!=0);
    return result;
}

bool is_more_than(int number, int minimum)
{
    return (number > minimum);
}


int main()
{
    int *numbers;
    int amount_of_numbers = 10;
    int lower_bound = 10000, upper_bound = 99999;
    int min_sum_of_num = 20;

    numbers = read_data(amount_of_numbers);
    double accepted_numbers = 0;
    long int sum_of_accepted_numbers = 0;
    
    for(int i = 0; i < amount_of_numbers; i++)
    {      
        int suma_cyfr = sum_of_digits(numbers[i]);
        bool result = is_more_than(suma_cyfr, min_sum_of_num);
        std::cout << "Number " << numbers[i] << " is ";
        if (result == false)
            std::cout << "not ";
        else
        {
            accepted_numbers++;
            sum_of_accepted_numbers += numbers[i];
        }
        std::cout << "accepted!" << endl;

        // if result
        // {
        //     // list.push_back()
        // }
        // else
        // {
        //     // actual_list.pop()
        // }
        
    }

    double average = sum_of_accepted_numbers/(double)accepted_numbers;
    std::cout << "Ilosc liczb: " << accepted_numbers << std::endl;
    std::cout << "Suma: " << sum_of_accepted_numbers << std::endl;
    std::cout << "Srednia: " << average << std::endl;
    return 0;
}
