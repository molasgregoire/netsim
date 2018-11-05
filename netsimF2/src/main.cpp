#include "network.h"
#include "random.h"
#include "simulation.h"
#include <iostream>

RandomNumbers RNG;

int main(int argc, char **argv) {
    Network net;
    Simulation sim(&net);
    int errcode = 0;
    try {
		std::cout << "TEST1" << std::endl;
        sim.initialize(argc, argv);
        std::cout << "TEST2" << std::endl;
        sim.run();
        std::cout << "TEST3" << std::endl;
    } catch(TCLAP::ArgException &e) {
        std::cerr << "Error: " + e.error() + " " + e.argId();
        errcode = 2;
    }
    return errcode;
}
