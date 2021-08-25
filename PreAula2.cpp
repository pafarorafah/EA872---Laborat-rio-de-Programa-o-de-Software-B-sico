#include <iostream>
#include <cmath>
#include <memory>

using namespace std;

class Sistema {
    private:
        float k , b , m , x0, v0;     //Coeficiente elastico, coeficiente de amortecimento, massa, posicao inicial e velocidade inicial
    
    public:
        float get_k();
        float get_b();
        float get_m();
        float get_x0();
        float get_v0();
        void set_sis(float new_k, float new_b, float new_m, float new_x0, float new_v0);
};

float Sistema::get_k() {
    return k;
};

float Sistema::get_b() {
    return b;
};

float Sistema::get_m() {
    return m;
};

float Sistema::get_x0() {
    return x0;
};

float Sistema::get_v0() {
    return v0;
};

void Sistema::set_sis(float new_k, float new_b, float new_m, float new_x0, float new_v0) {
    k = new_k;
    b = new_b;
    m = new_m;
    x0 = new_x0;
    v0 = new_v0;
}

class Equacao {
    private:
        Sistema *sis = new Sistema();
        void super(float s1, float s2, float T, float x0, float v0);
        void critico(float s, float T, float x0, float v0);
        void sub(float wd, float alfa, float T, float x0, float v0);

    public:
        void equacionar();
        void set_sistema(float new_k, float new_b, float new_m, float new_x0, float new_v0);
};

void Equacao::set_sistema(float new_k, float new_b, float new_m, float new_x0, float new_v0) {
    sis->set_sis(new_k, new_b, new_m, new_x0, new_v0);
};

void Equacao::super(float s1, float s2, float T, float x0, float v0) {
    float A = x0 - (v0 - x0*s1)/(s1 - s2);
    float B = (v0 - x0*s1)/(s1 - s2);
    
    float xis = 0;
    float vel = 0;

    printf("Sistema Superamortecido\n");

    for(int n = 0; n < 100 ; n++) {
        xis += A*exp(-s1*T) + B*exp(-s2*T);
        vel += -A*s1*exp(-s1*T) - B*s2*exp(-s2*T);
        printf("X: %f, V: %f\n", xis, vel);
    }
};

void Equacao::critico(float s, float T, float x0, float v0) {
    float A = x0;
    float B = v0 + x0*s;

    float xis = 0;
    float vel = 0;

    printf("Sistema Critico\n");

    for(int n = 0; n < 100 ; n++) {
        xis += A*exp(-s*T) + B*T*exp(-s*T);
        vel += exp(-s*T)*(-A*s -s*B*T + B);
        printf("X: %f, V: %f\n", xis, vel);
    }
};

void Equacao::sub(float wd, float alfa, float T, float x0, float v0) {
    float A = x0;
    float B = (v0 - alfa*x0)/wd;

    float xis = 0;
    float vel = 0;

    printf("Sistema Subamortercido\n");

    for(int n = 0; n < 100 ; n++) {
        xis += exp(-alfa*T)*(A*sin(wd*T) + B*cos(wd*T));
        vel += exp(-alfa*T)*( cos(wd*T)*(A*wd - alfa*B) - sin(wd*T)*(alfa*A + B*wd) );
        printf("X: %f, V: %f\n", xis, vel);   
    }
};

void Equacao::equacionar() {
    float k =  sis->get_k();
    float b = sis->get_b();
    float m = sis->get_m();
    float x0 = sis->get_x0();
    float v0 = sis->get_v0();

    float T = 0.01;

    float omega = sqrt(k/m);
    float alfa = b/(2*m);

    float omega_2 = k/m;
    float alfa_2 = pow(alfa, 2);

    if(alfa_2 > omega_2) {
        float s1 = -alfa + sqrt(alfa_2 - omega_2);
        float s2 = -alfa - sqrt(alfa_2 - omega_2);
        super(s1, s2, T, x0, v0);
    }

    if(alfa_2 == omega_2) {
        float s = -alfa;
        critico(s, T, x0, v0);
    }

    if(alfa_2 < omega_2) {
        float wd = sqrt(omega_2 - alfa_2); 
        printf("Sub : %f %f %f %f %f\n", wd, alfa, T, x0, v0);
        sub(wd, alfa, T, x0, v0);
    }
};


int main() {
    Equacao *e = new Equacao();
    e->set_sistema(0.50, 10, 20, 0, 5);
    e->equacionar();
return 0;

};