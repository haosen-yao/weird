#include <fstream>
#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::string target = argv[2];
  std::string phony;
  phony = Result(target);
  std::cout << phony << std::endl;
  return 0;
}