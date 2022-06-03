#include "loadtmx.hpp"

int main (int argc, char **argv){
  FILE * file;

  if((file = fopen("file.tmx", "r")) == NULL){
    std::cerr << "Could not open file.\n";
    return EXIT_FAILURE;
  }

  auto loadtmx = std::make_shared<LoadTmx>(file); 
  loadtmx->run();

  fclose(file);
  return EXIT_SUCCESS;
}
