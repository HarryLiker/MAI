#include <iostream>
#include "figure.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapeze.hpp"
#include "document.hpp"

int main() {
    Document<int> document;
    std::string line;
    while (std::cin >> line) { // read command
        if (line == "new") {
            document.CreateNew();
            std::cout << "New document has been created\n";
        } else if (line == "open") {
            std::cout << "Write file name: ";
            std::cin >> line;
            FILE *file;
            file = fopen(line.c_str(), "rb");
            if (file == NULL) {
                std::cout << "File open error\n";
            } else {
                document.LoadFromFile(file); // Loading the figures from file
                std::cout << "Document has been uploaded\n";
            }
            fclose(file);
        } else if (line == "save") {
            std::cin >> line;
            FILE *file;
            file = fopen(line.c_str(), "wb");
            if (file == NULL) {
                std::cout << "File open error\n";
            } else {
                document.SaveInFile(file); // Saving the figure in file
                std::cout << "The file has been saved\n";
            }
            fclose(file);
        } else if (line == "add") {
            try {
                size_t position;
                unsigned short type;
                std::cout << "Enter the index of the figure type (1 - Rectangle, 2 - Trapeze, 3 - Rhombus): ";
                std::cin >> type;
                if (type < 1 || type > 3) {
                    throw ("Entered wrong index!");
                }
                std::cout << "Enter the position of the figure: ";
                std::cin >> position;
                document.Add(position, type); // Adding the figure in document by index
                std::cout << "The figure has been added\n";
            }
            catch(const char *error) {
                std::cout << error << "\n";
            }
        } else if (line == "remove") {
            size_t position;
            std::cout << "Enter the figure's position to remove: ";
            std::cin >> position;
            document.Delete(position); // Remove figure from the document by index
            std::cout << "The figure has been removed\n";
        } else if (line == "print") {
            std::cout << "Figures in document:\n";
            std::cout << document;
        } else if (line == "undo") {
            document.Undo(); // Cancel the previous action
        } else if (line == "help") {
            std::cout << "\'new\' - create new document\n";
            std::cout << "\'open\' - open document\n";
            std::cout << "\'save\' [Document name] - save document\n";
            std::cout << "\'add\' - add figure\n";
            std::cout << "\'remove\' - remove figure\n";
            std::cout << "\'print\' - print document\n";
            std::cout << "\'undo\' - undo changes\n";
            std::cout << "\'exit\' - exit the program\n";
            std::cout << "\'help\' - show all the commands\n";
        } else if (line == "exit") {
            std::cout << "Program has been completed";
            return 0;
        } else {
            std::cout << "Etered unknown command. Enter command \"help\" to print all the commands\n";
        }
        std::cout << "\n";
    }
    return 0;
}