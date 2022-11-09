#include <stdio.h>
#include <omp.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// Dany zbiór liczb całkowitych przynajmniej 5 cyfrowych
// Oblicz średnią arytmetyczną liczb spełniających warunki:
//      liczba nalezy do przedzialu <x, y>
//      suma cyfr > ustalona wartość

// OpenMP, MPI i hybrydowe MPI + OpenMP

std::vector<int> read_data() {

    std::vector<int> data = {};
    ifstream newfile;
    
    newfile.open("Numbers.txt");
    if (newfile.is_open())
    {
        string tp;
        while(getline(newfile, tp))
        {
            data.push_back(stoi(tp));
        }
        newfile.close();
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
    int lower_bound = 10000, upper_bound = 99999;
    int min_sum_of_num = 20;

    double start, end;
    
    double accepted_numbers, average;
    long long sum_of_accepted_numbers;
    std::vector<int> numbers = read_data();

    std::cout << "[OpenMP] [static, default]" << std::endl;
    start = omp_get_wtime(); 

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;
    #pragma omp parallel for num_threads(8) schedule(static) reduction(+:sum_of_accepted_numbers, accepted_numbers)
    for(auto & num : numbers)
    {      
        int suma_cyfr = sum_of_digits(num);
        if (is_more_than(suma_cyfr, min_sum_of_num))
        {
            accepted_numbers++;
            sum_of_accepted_numbers += num;
        }
    }
    average = sum_of_accepted_numbers/(double)accepted_numbers;

    end = omp_get_wtime(); 

    std::cout << "Czas obliczen: " << end-start << std::endl;
    std::cout << "Ilosc liczb: " << accepted_numbers << std::endl;
    std::cout << "Suma: " << sum_of_accepted_numbers << std::endl;
    std::cout << "Srednia: " << average << std::endl;

    std::cout << std::endl;


    std::cout << "[OpenMP] [static, 8]" << std::endl;
    start = omp_get_wtime(); 

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;
    #pragma omp parallel for num_threads(8) schedule(static,8) reduction(+:sum_of_accepted_numbers, accepted_numbers)
    for(auto & num : numbers)
    {      
        int suma_cyfr = sum_of_digits(num);
        if (is_more_than(suma_cyfr, min_sum_of_num))
        {
            accepted_numbers++;
            sum_of_accepted_numbers += num;
        }
    }
    average = sum_of_accepted_numbers/(double)accepted_numbers;

    end = omp_get_wtime(); 

    std::cout << "Czas obliczen: " << end-start << std::endl;
    std::cout << "Ilosc liczb: " << accepted_numbers << std::endl;
    std::cout << "Suma: " << sum_of_accepted_numbers << std::endl;
    std::cout << "Srednia: " << average << std::endl;

    std::cout << std::endl;

    std::cout << "[OpenMP] [dynamic, 8]" << std::endl;
    start = omp_get_wtime(); 

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;
    #pragma omp parallel for num_threads(8) schedule(dynamic,8) reduction(+:sum_of_accepted_numbers, accepted_numbers)
    for(auto & num : numbers)
    {      
        int suma_cyfr = sum_of_digits(num);
        if (is_more_than(suma_cyfr, min_sum_of_num))
        {
            accepted_numbers++;
            sum_of_accepted_numbers += num;
        }
    }
    average = sum_of_accepted_numbers/(double)accepted_numbers;

    end = omp_get_wtime(); 

    std::cout << "Czas obliczen: " << end-start << std::endl;
    std::cout << "Ilosc liczb: " << accepted_numbers << std::endl;
    std::cout << "Suma: " << sum_of_accepted_numbers << std::endl;
    std::cout << "Srednia: " << average << std::endl;

    return 0;
}
