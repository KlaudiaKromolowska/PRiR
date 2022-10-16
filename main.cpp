#include <stdio.h>
#include <omp.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;
// Dany zbiór liczb całkowitych przynajmniej 5 cyfrowych
// Oblicz średnią arytmetyczną liczb spełniających warunki:
//      liczba nalezy do przedzialu <x, y>
//      suma cyfr > ustalona wartość

// OpenMP, MPI i hybrydowe MPI + OpenMP

int* generate_data(int n, int low, int high) {

    int* data = new int[n];
    for (int i = 0; i < n; i++) {
        data[i] = rand()%(high - low) + low;
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

    numbers = generate_data(amount_of_numbers, lower_bound, upper_bound);

    for(int i; i < amount_of_numbers; i++)
    {      
        int suma_cyfr = sum_of_digits(numbers[i]);
        bool result = is_more_than(suma_cyfr, min_sum_of_num);
        cout << "Number " << numbers[i] << " is ";
        if (result == false)
            cout << "not ";
        cout << "accepted!" << endl;

        if result
        {
            // list.push_back()
        }
        else
        {
            // actual_list.pop()
        }
        
    }

    // obliczyc sumę z pasujących liczb
    // podzielic przez liczbę pasujących liczb
    return 0;
}