#include <omp.h>
#include <iostream>
#include <time.h>       /* time */

bool is_more_than(int number, int minimum);
int sum_of_digits(int num);

void open_mp(std::vector<int> numbers, int lower_bound = 10000, int upper_bound = 99999, int min_sum_of_num = 20)
{
    double start, end;
    
    double accepted_numbers, average;
    long long sum_of_accepted_numbers;

    std::cout << "[OpenMP] [static, default]" << std::endl;

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;

    start = omp_get_wtime(); 
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

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;

    start = omp_get_wtime(); 
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
    std::cout << "[OpenMP] [dynamic, default]]" << std::endl;

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;

    start = omp_get_wtime(); 
    #pragma omp parallel for num_threads(8) schedule(dynamic) reduction(+:sum_of_accepted_numbers, accepted_numbers)
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

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;

    start = omp_get_wtime();
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