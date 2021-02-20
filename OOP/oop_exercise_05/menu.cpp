#include <iostream>
#include <memory>
#include <algorithm>
#include "triangle.hpp"
#include "queue.hpp"

int menu() {
    Queue<Triangle<int>> queue;
    while (1) {
        int variant;
        std::cout << "1 - Add figure in collection as queue\n";
        std::cout << "2 - Add figure in collection by index\n";
        std::cout <<"3 - Delete an element from the collection as from queue\n";
        std::cout <<"4 - Delete an element from the collection by index\n";
        std::cout << "5 - Print figures from the collection\n";
        std::cout << "6 - Print figures, with less square\n";
        std::cout << "7 - End the program\n";
        std::cout << "Enter an action: ";
        std::cin >> variant;

        switch (variant) {
        case 1:
        {
            int x, y;
            int side;
            std::cout << "Write the center coordinates: ";
            std::cin >> x >> y;
            std::cout << "Write size of the side of triangle: ";
            std::cin >> side;
            queue.Push(Triangle<int>(std::pair<int,int> {x, y}, side));
            std::cout << "The figure has been added\n";
            break;
        }
        case 2:
        {
            int x, y;
            int side;
            int index;
            std::cout << "Write the center coordinates: ";
            std::cin >> x >> y;
            std::cout << "Write size of the side of triangle: ";
            std::cin >> side;
            std::cout << "Enter the position of the new item in the queue: ";
            std::cin >> index;
            try {
                if (queue.FindSize() + 1 < index) {
                    // if the index is outside the collection or negative
                    throw std::invalid_argument("Entered the wrong index!\n");
                }
                else {
                    auto iterator = queue.begin();
                    while (--index) {
                        ++iterator;
                    }
                    queue.Insert(iterator, Triangle<int>(std::pair<int,int> {x, y}, side));
                    std::cout << "The figure has been added\n";
                }
            }
            // If an excenpion occurs
            catch (std::invalid_argument &argument) {
                std::terminate();
            }
            break;
        }
        case 3:
        {
            queue.Pop();
            std::cout << "The figure has been removed\n";
            break;
        }
        case 4:
        {
            int index;
            std::cout << "Enter the position of the element to remove: ";
            std::cin >> index;
            try {
                auto iterator = queue.begin();
                while (--index) {
                    ++iterator;
                }
                queue.Erase(iterator);
                std::cout << "The figure has been removed\n";
            }
            catch (std::runtime_error &error) {
                std::cout << error.what() << "\n";
            }
            break;
        }
        case 5:
        {
            auto print_queue = [](const Node<Triangle<int>> &figure) {
                std::cout << figure << "\n";
            };
            std::cout << "All figures:\n";
            std::for_each(queue.begin(), queue.end(), print_queue);
            break;
        }
        case 6:
        {
            double minimal_suare;
            std::cout << "Enter the minimal square: ";
            std::cin >> minimal_suare;
            auto figures_less_squre = [&minimal_suare](const Node<Triangle<int>> &figure) {
                return figure.Data.Square() < minimal_suare;
            };
            std::cout << "Triangles with square less than the specified area: " << std::count_if(queue.begin(), queue.end(), figures_less_squre) << "\n";
            break;
        }
        case 7:
        {
            std::cout << "The program has been completed.\n";
            return 0;
            break;
        }
        default:
        {
            std::cout << "Entered invalid action!\n";
            break;
        }
        }
        std::cout << "\n";
    }
}