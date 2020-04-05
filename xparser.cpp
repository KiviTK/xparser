#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
    std::string prefix = "$XC";

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-p")
            prefix = argv[++i];
    }

    std::vector<std::string> lookup;
    std::vector<std::string> special;

    lookup.resize(16);
    special.resize(3);

    system("touch tmp_xdb_dump");

    system("xgetres *.foreground >> tmp_xdb_dump");
    system("xgetres *.background >> tmp_xdb_dump");
    system("xgetres *.cursorColor >> tmp_xdb_dump");

    for (int i = 0; i < 16; i++) {
        std::string comm = "xgetres *.color";
        comm += std::to_string(i);
        comm += " >> tmp_xdb_dump";

        system(comm.c_str());
    }

    std::ifstream xdb("tmp_xdb_dump");

    for (int i = 0; i < 3; i++) {
        std::string col;
        xdb >> col;
        special[i] = col;
    }

    for (int i = 0; i < 16; i++) {
        std::string col;
        xdb >> col;
        lookup[i] = col;
    }
    xdb.close();
    system("rm tmp_xdb_dump");

    std::string line; 

    while (std::getline(std::cin, line)) {
        std::istringstream stream(line);

        std::string word;
        bool color_flag = false;

        while (stream >> word) {
            if (color_flag) {
                bool done = false;


                if (word == "fg") {
                    done = true;
                    word = special[0];
                }
                if (word == "bg") {
                    done = true;
                    word = special[1];
                }
                
                if (word == "cur") {
                    done = true;
                    word = special[2];
                }

                if (!done)
                    word = lookup[std::stoi(word)];

                color_flag = false;
            }
                
            if (word == prefix) {
                word = ""; 
                color_flag = true;
            }
           
            if (word != "")
                std::cout << word << " ";
        }
        std::cout << "\n";
    } 
    return 0;
}
