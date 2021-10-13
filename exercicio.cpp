
#include <iostream>
#include <fstream>
#include <iostream>
#include "json.hpp"
using nlohmann::json;

class Contador {
  private:
    int contagem;

  public:
    Contador() { contagem=0; }

    void contar() { 
      json j, j2;
      j["contagem"] = 0;
      std::ifstream f2("contagem.json");

   
      if(!f2.is_open()) {
        std::ofstream f;
        f.open("contagem.json");
        f << j;
        f.close();
        std::cout << "Este programa executou: ";
        return; 
      }

      else{
        std::ifstream f3;
        f3.open("contagem.json");
        f3 >> j;
        contagem = j["contagem"];    
        contagem++;
        f3.close();

        std::ofstream f4;
        f4.open("contagem.json");
        j["contagem"] = contagem;
        f4 << j;
        f4.close();
      }
      
    }
    int get_contagem() { 
      contar();   
      return contagem; }
};

int main() {
  Contador c;

  std::cout << "Este programa executou: " << c.get_contagem()<< " vezes " << std::endl;

  return 0;
}
