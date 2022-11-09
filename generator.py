import random
import argparse


def fillFile(amount_of_numbers, min_number, max_number, fileName):
    file = open(fileName + str(args.amount) + ".txt", "w")
    for i in range(amount_of_numbers):
        value = random.randint(min_number, max_number)
        file.write(f"{value}\n")

if __name__ == "__main__":
    # Instantiate the parser
    parser = argparse.ArgumentParser(description='Optional app description')

    parser.add_argument('amount', type=int,
                        help='A number of generated numbers')

    parser.add_argument('min', type=int,
                        help=' Minimum value of generated number')

    parser.add_argument('max', type=int,
                        help='Maximum value of generated number')

    args = parser.parse_args()

    fillFile(args.amount, args.min, args.max, "Numbers")
