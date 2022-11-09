
#include <vector>

namespace helpers
{

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

void single(std::vector<int> numbers, int lower_bound = 10000, int upper_bound = 99999, int min_sum_of_num = 20)
{
    double start, end;
    
    double accepted_numbers, average;
    long long sum_of_accepted_numbers;

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;

    start = omp_get_wtime(); 
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
    
}

} // namespace helpers

