#include <cstdio>

struct Animal {
    virtual void make_noise() {puts("Animal noise");}
    void eat() {puts("Animal eat");}
    void sleep() {puts("Animal sleep");}
    void roam() {puts("Animal roam");}
};

struct Canine : public Animal {
    void roam() {puts("Canine roam");}
    void eat() {puts("Canine eat");}
};


struct Wolf : public Canine {
    void make_noise() {puts("Wolf noise");}
    void eat() {puts("Wolf eat");}
};

void call (Animal& a) {
    a.make_noise();
    a.roam();
    a.eat();
    a.sleep();
}

int main () {
    Wolf w;

    // "Wolf noise"; "Animal roam"; "Animal eat"; "Animal sleep"
    call(w);
}

