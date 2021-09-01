#include <iostream>
#include <cmath>
#include <memory>

using namespace std;

//MODEL
class Sistema {
    private:
        float k, b, m, x0, v0, T;
    public:
        Sistema(float k_init, float b_init, float m_init, float x0_init, float v0_init, float T_init);
        float get_k();
        float get_b();
        float get_m();
        float get_x0();
        float get_v0();
        float get_T();
        void set_x0(float new_x0);
        void set_v0(float new_v0);
};

Sistema::Sistema(float k_init, float b_init, float m_init, float x0_init, float v0_init, float T_init) {
    k = k_init;
    b = b_init;
    m = m_init;
    x0 = x0_init;
    v0 = v0_init;
    T = T_init; 
}

float Sistema::get_k() {
    return k;
}

float Sistema::get_b() {
    return b;
}

float Sistema::get_m() {
    return m;
}

float Sistema::get_x0() {
    return x0;
}

float Sistema::get_v0() {
    return v0;
}

float Sistema::get_T() {
    return T;
}

void Sistema::set_x0(float new_x0) {
    x0 = new_x0;
}

void Sistema::set_v0(float new_v0) {
    v0 = new_v0;
}

//CONTROLLER
class Equacao {
    private:
        shared_ptr<Sistema> sis;

    public:
        Equacao(shared_ptr<Sistema> &sistema);
        void equacionar();
};    

Equacao::Equacao(shared_ptr<Sistema> &sistema) {
    sis = sistema;
}

void Equacao::equacionar() {
    float k = sis->get_k();
    float b = sis->get_b();
    float m = sis->get_m();
    float x0 = sis->get_x0();
    float v0 = sis->get_v0();
    float T = sis->get_T();

    float a, f;

    f = -x0*k - b*v0;
    a = f/m;
    v0 = v0 + a*T;
    x0 = x0 + v0*T;

    sis->set_x0(x0);
    sis->set_v0(v0);
}

//VIEW
class Imprime {
    private:
        shared_ptr<Sistema> sis;

    public:
        Imprime(shared_ptr<Sistema> sistema);
        void imprime_sistema();
};

Imprime::Imprime(shared_ptr<Sistema> sistema){
    sis = sistema;
}

void Imprime::imprime_sistema(){
    printf("X = %f    V = %f\n", sis->get_x0(), sis->get_v0());
}


int main() {

    float k = 1, b = 0, m = 1, x0 = 1, v0 = 0, T = 0.1;

    shared_ptr<Sistema> s (new Sistema(k, b, m, x0, v0, T));
    shared_ptr<Equacao> e (new Equacao(s));
    shared_ptr<Imprime> i (new Imprime(s));

    for(int n = 0; n < 100; n ++) {
        e->equacionar();
        i->imprime_sistema();
    }
    return 0;
};




