#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <mpi.h>

#define TABLE_SIZE 10000

using namespace std;

int* read_data();
int sum_of_digits(int num);
bool is_more_than(int number, int minimum);

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int lower_bound = 10000, upper_bound = 99999;
    int min_sum_of_num = 20;

    double accepted_numbers, tmp_accepted_numbers, average;
    long long sum_of_accepted_numbers, tmp_sum_of_accepted_numbers;
    int* data = read_data();
    int batch_size = TABLE_SIZE / (size - 1);
    accepted_numbers = 0;
    sum_of_accepted_numbers = 0;
    tmp_accepted_numbers = 0;
    tmp_sum_of_accepted_numbers = 0;

    double start = MPI_Wtime();
    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            std::cout << "[Proces " << rank << "] Wysylam tablice do procesu nr " << i << std::endl;
            std::cout << "[Proces " << rank << "] Pierwszy element tablicy ma adres "  << &data[0] << " " << data[0] << std::endl;
            MPI_Send(&data, TABLE_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&data, TABLE_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        std::cout << "[Proces " << rank << "] Odebralem tablice. "<< std::endl;

        int first_index = batch_size * (rank - 1);
        int last_index = first_index + batch_size;
        std::cout << "[Proces " << rank << "] Biore zakres [" << first_index << ";" << last_index << "]" << std::endl;
        std::cout << "[Proces " << rank << "] Ostatni index " << last_index << " zawiera element o wartosci " << data[last_index] << std::endl;

        for (int j = first_index; j < last_index; j++)
        {
            int suma_cyfr = sum_of_digits(data[j]);
            if (is_more_than(suma_cyfr, min_sum_of_num))
            {
                tmp_accepted_numbers++;
                tmp_sum_of_accepted_numbers += data[j];
            }

        }
        std::cout << "[Proces " << rank << "] Juz wszystko policzylem" << std::endl;
    }
    MPI_Reduce(&tmp_accepted_numbers, &accepted_numbers, batch_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&tmp_sum_of_accepted_numbers, &sum_of_accepted_numbers, batch_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        double end = MPI_Wtime();
        average = sum_of_accepted_numbers / (double)accepted_numbers;

        std::cout << "Ilosc liczb: " << accepted_numbers << std::endl;
        std::cout << "Czas obliczen: " << end - start << std::endl;
        std::cout << "Suma: " << sum_of_accepted_numbers << std::endl;
        std::cout << "Srednia: " << average << std::endl;

        std::cout << std::endl;
    }
    free(data);

    MPI_Finalize();
    return 0;
}

int* read_data() {
    int i = 0;
    int* data = (int*)malloc(TABLE_SIZE * sizeof(int));
    ifstream newfile;
    newfile.open("Numbers" + std::to_string(TABLE_SIZE) +".txt");
    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {   
            if (data[i])
            {
                data[i] = stoi(tp);
                i++;
            }
        }
        newfile.close();
    }
    else
    {
        std::cout << "File is not existing" << std::endl;
    }
    return data;
}

int sum_of_digits(int num) {
    int result = 0;
    do {
        result = result + num % 10;
        num = num / 10;
    } while (num != 0);
    return result;
}

bool is_more_than(int number, int minimum)
{
    return (number > minimum);
}