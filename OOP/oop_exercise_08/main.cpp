#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#include "factory.hpp"
#include "figure.hpp"
#include "publish-subscribe.hpp"

PublishSubscribe<std::vector<std::shared_ptr<Figure>>> message_queue; // Queue of figures to print in console and file
const std::string FILE_NAME = "result_file";
int number_file = 1; // To number each file for each buffer
std::ofstream file;

// Function for outputting figures to the console and to a file after filling the buffer
void ThreadFunction() {
    using function = std::function<void(std::shared_ptr<Figure> figure)>;
    function PrintOut = [](std::shared_ptr<Figure> figure) {
        figure->Print();
    };
    function WriteInFile = [](std::shared_ptr<Figure> figure) {
        figure->Write(file);
    };
    std::vector<function> functions({PrintOut, WriteInFile});
    bool message_not_empty = true;
    while (message_not_empty) {
        if (!message_queue.Empty()) {
            std::vector<std::shared_ptr<Figure>> message = message_queue.Front();
            if (message.empty()) {
                message_not_empty = false;
                break;
            }
            file.open(FILE_NAME + std::to_string(number_file));
            while (!message.empty()) {
                std::shared_ptr<Figure> figure_pointer = message.front();
                message.erase(message.begin());
                for (auto function: functions) {
                    function(figure_pointer);
                }
            } 
            file.close();
            number_file++;
            message_queue.Pop();
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "No enough parameters!\n";
        return -1;
    }
    size_t buffer_size;
    try {
        buffer_size = std::stoi(std::string(argv[1])); // Conversation the parameter to integer
    }
    catch (std::exception &exeption) {
        std::cout << exeption.what() << "\n";
        return -1;
    }
    std::thread thread(ThreadFunction);
    std::vector<std::shared_ptr<Figure>> figures;
    unsigned short figure_type;
    std::cout << "Number of figure type (1 - Rectangle; 2 - Trapeze; 3 - Rhombus)\n";
    while (std::cin >> figure_type) {
        if (figure_type == RECTANGLE_ID_TYPE) {
            figures.push_back(Factory<int, Rectangle<int>>::CreateFigure());
            std::cout << "Figure rectangle has been added\n";
        } else if (figure_type == TRAPEZE_ID_TYPE) {
            figures.push_back(Factory<int, Trapeze<int>>::CreateFigure());
            std::cout << "Figure trapeze has been added\n";
        } else if (figure_type == RHOMBUS_ID_TYPE) {
            figures.push_back(Factory<int, Rhombus<int>>::CreateFigure());
            std::cout << "Figure rhombus has been added\n";
        } else {
            std::cout << "Entered invalid type of figure!\n\n";
            continue;
        }
        if (figures.size() == buffer_size) { // Running the handler thread
            message_queue.Push(figures);
            bool thread_work_done = false;
            while (!thread_work_done) {
                if (message_queue.Empty()) {
                    thread_work_done = true;
                }
            }
            figures.clear();
        }
        std::cout << "\nNumber of figure type (1 - Rectangle; 2 - Trapeze; 3 - Rhombus)\n";
    }
    message_queue.Push(figures);
    figures.clear();
    message_queue.Push(figures);
    figures.clear();
    thread.join();
    return 0;
}