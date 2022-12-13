#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <mpi.h>
#include <omp.h>
#define TABLE_SIZE 10000

using namespace std;

int* read_data();
int sum_of_digits(int num);
bool is_more_than(int number, int minimum);

typedef struct {
    int accepted_numbers;
    long long sum_of_accepted_numbers;
} Data;

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Status status;

    MPI_Datatype new_type;
    MPI_Datatype type[2] = { MPI_INT, MPI_LONG_LONG };
    int blen[2] = { 1, 1 };
    MPI_Aint disp[2];
    MPI_Aint base, addr;
    Data tab_record, tab_received;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Get_address(&tab_record, &base);
    MPI_Get_address(&(tab_record.accepted_numbers), &addr);
    disp[0] = addr - base;
    MPI_Get_address(&(tab_record.sum_of_accepted_numbers), &addr);
    disp[1] = addr - base;

    MPI_Type_create_struct(2, blen, disp, type, &new_type);
    MPI_Type_commit(&new_type);

    int lower_bound = 10000, upper_bound = 99999;
    int min_sum_of_num = 20;

    int accepted_numbers = 0;
    long long sum_of_accepted_numbers = 0;
    double average;
    int* data = read_data();
    int batch_size = TABLE_SIZE / (size - 1);

    double start = MPI_Wtime();

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Send(data, TABLE_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        std::vector<Data> clients;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&tab_received, 1, new_type, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            clients.push_back(tab_received);
        }

        for (Data client : clients)
        {
            accepted_numbers += client.accepted_numbers;
            sum_of_accepted_numbers += client.sum_of_accepted_numbers;
        }

        double end = MPI_Wtime();
        average = accepted_numbers ? sum_of_accepted_numbers / (double)accepted_numbers : 0;

        std::cout << "Ilosc liczb spelniajacych kryteria: " << accepted_numbers << "/" << TABLE_SIZE << std::endl;
        std::cout << "Czas obliczen: " << end - start << std::endl;
        std::cout << "Suma: " << sum_of_accepted_numbers << std::endl;
        std::cout << "Srednia: " << average << std::endl;
        std::cout << std::endl;

    }
    else
    {
        MPI_Recv(data, TABLE_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        int first_index = batch_size * (rank - 1);
        int last_index = (rank != size - 1) ? first_index + batch_size : TABLE_SIZE;
        tab_record.accepted_numbers = 0;
        tab_record.sum_of_accepted_numbers = 0;

        #pragma omp parallel for num_threads(8) schedule(static) reduction(+:tab_record.sum_of_accepted_numbers, tab_record.accepted_numbers)
        for (int j = first_index; j < last_index; j++)
        {
            int suma_cyfr = sum_of_digits(data[j]);
            if (is_more_than(suma_cyfr, min_sum_of_num))
            {
                tab_record.accepted_numbers++;
                tab_record.sum_of_accepted_numbers += data[j];
            }

        }
        MPI_Send(&tab_record, 1, new_type, 0, 0, MPI_COMM_WORLD);

    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}

int* read_data() {
    int i = 0;
    int* data = (int*)malloc(TABLE_SIZE * sizeof(int));
    ifstream newfile;
    newfile.open("Numbers" + std::to_string(TABLE_SIZE) + ".txt");
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