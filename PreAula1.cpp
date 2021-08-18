#include <iostream>

class Coord {
    private:
        int x,y;
    public:
        void set_coord(int new_x, int new_y);    
};

void Coord::set_coord(int new_x, int new_y) {
    x = new_x;
    y = new_y;
};

class Cube {
    private:
        int x, y, z;
    public:
        void set_cube(int new_x, int new_y, int new_z);
        int get_x();    
        int get_y();
        int get_z();
};

void Cube::set_cube(int new_x, int new_y, int new_z){
    x = new_x;
    y = new_y;
    z = new_z;
};

int Cube::get_x(){
    return x;
};

int Cube::get_y(){
    return y;
};

int Cube::get_z(){
    return z;
};

void cube_print_volume(Cube *c) {
    std::cout << (c->get_x() * c->get_y() * c->get_z()) << std::endl;
}

int main() {
    Coord *c1   = new Coord();
    Cube *c2 = new Cube();

    c1->set_coord(50, 10);
    c2->set_cube(10, 20, 30);

    cube_print_volume(c2);

  return 0;
}