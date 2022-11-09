#include <fstream>
#include <string>
#include <vector>
#include "openmp.cpp"

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

int main()
{
    int lower_bound = 10000, upper_bound = 99999;
    int min_sum_of_num = 20;

    std::vector<int> numbers = read_data();

    open_mpi(numbers, lower_bound, upper_bound, min_sum_of_num);

    return 0;
}
