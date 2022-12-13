#include <fstream>
#include <string>
#include <vector>
#include <omp.h>
#include <iostream>
#include <time.h>       /* time */
#include <chrono>

using namespace std;
// Dany zbiór liczb całkowitych przynajmniej 5 cyfrowych
// Oblicz średnią arytmetyczną liczb spełniających warunki:
//      liczba nalezy do przedzialu <x, y>
//      suma cyfr > 20

// OpenMP, MPI i hybrydowe MPI + OpenMP

bool is_more_than(int, int);
int sum_of_digits(int);
void open_mp(std::vector<int>, int, int, int);
std::vector<int> read_data();


int main()
{
    int lower_bound = 10000, upper_bound = 99999;
    int min_sum_of_num = 20;

    std::vector<int> numbers = read_data();
    open_mp(numbers, lower_bound, upper_bound, min_sum_of_num);
    return 0;
}

std::vector<int> read_data() {

    std::vector<int> data = {};
    ifstream newfile;
    
    newfile.open("Numbers1000000.txt");
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

void open_mp(std::vector<int> numbers, int lower_bound = 10000, int upper_bound = 99999, int min_sum_of_num = 20)
{
    double accepted_numbers, average;
    long long sum_of_accepted_numbers;

    std::cout << "[Bez zrownoleglania]" << std::endl;

    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;

    auto start = std::chrono::high_resolution_clock::now();
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

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Ilosc liczb spelniajacyc kryteria: " << accepted_numbers << "/" << numbers.size() << std::endl;
    std::cout << "Czas obliczen: " << elapsed.count() << std::endl;
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