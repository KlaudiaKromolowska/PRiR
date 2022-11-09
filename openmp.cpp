#include <omp.h>
#include <iostream>
#include <time.h>       /* time */
#include "helpers.cpp"

void open_mpi(std::vector<int> numbers, int lower_bound = 10000, int upper_bound = 99999, int min_sum_of_num = 20)
{
    double start, end;
    
    double accepted_numbers, average;
    long long sum_of_accepted_numbers;

    std::cout << "[OpenMP] [static, default]" << std::endl;
    start = omp_get_wtime(); 

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;
    #pragma omp parallel for num_threads(8) schedule(static) reduction(+:sum_of_accepted_numbers, accepted_numbers)
    for(auto & num : numbers)
    {      
        int suma_cyfr = helpers::sum_of_digits(num);
        if (helpers::is_more_than(suma_cyfr, min_sum_of_num))
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
        int suma_cyfr = helpers::sum_of_digits(num);
        if (helpers::is_more_than(suma_cyfr, min_sum_of_num))
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
    start = omp_get_wtime(); 

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;
    #pragma omp parallel for num_threads(8) schedule(dynamic) reduction(+:sum_of_accepted_numbers, accepted_numbers)
    for(auto & num : numbers)
    {      
        int suma_cyfr = helpers::sum_of_digits(num);
        if (helpers::is_more_than(suma_cyfr, min_sum_of_num))
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
        int suma_cyfr = helpers::sum_of_digits(num);
        if (helpers::is_more_than(suma_cyfr, min_sum_of_num))
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