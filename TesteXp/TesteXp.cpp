#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>

namespace program 
{
    void ModifyFile(std::string& file_path)
    {
        if (file_path.find("\"") != std::string::npos)
        {
            file_path = file_path.substr(1, file_path.length() - 2);
        }

        std::ifstream file_stream(file_path);
        if (file_stream.is_open()) {
            std::stringstream ss;

            std::string f_line;
            uint32_t alter_count = 0;

            while (std::getline(file_stream, f_line))
            {
                auto temp = f_line.find("G1Z");

                if (temp != std::string::npos)
                {
                    std::string g1z = f_line.substr(0, 3);
                    std::string rest = "1" + f_line.substr(3) + "M3";
                    alter_count++;
                    f_line = g1z + rest;
                }
                ss << f_line << "\n";
            }
            file_stream.close();

            std::cout << "Um total de " << alter_count << " serão afetadas. \n";
            std::cout << "Proseguir? (S/n)";
            std::string answer;
            std::getline(std::cin, answer);

            if (answer.find("s") != std::string::npos || answer.find("S") != std::string::npos)
            {
                std::ofstream out_file(file_path);
                out_file.write(ss.str().c_str(), ss.str().length());
                out_file.close();
            }
        }
        else
        {
            std::cout << "Não foi possivel abrir o arquivo \n";
            std::cin.get();
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Digite o caminho para o arquivo: \n";
        
        std::string file_path;
        std::getline(std::cin, file_path);
        
        program::ModifyFile(file_path);
        return 0;
    }
    
    std::string file_path = argv[1];
    program::ModifyFile(file_path);

    return 0;
}