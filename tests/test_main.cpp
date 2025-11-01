#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../Console.h"
#include "../Laberinto.h"
using namespace std;
using namespace std::chrono;

//CENTRO DE TESTEO UNITARIO


using namespace std;
using namespace std::chrono;

class LaberintoPerformanceTest : public ::testing::Test {};

void runLaberintoTest(int filas, int columnas) {
    Laberinto laberinto;

    auto start = high_resolution_clock::now();

    EXPECT_NO_THROW({
        laberinto.inicializarEspacios(filas, columnas);
        laberinto.rellenarEspacio();
        //laberinto.imprimirMalla();
    });

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "\n ● Laberinto " << filas << "x" << columnas 
         << " se generó en: " << duration << " ms\n";
}

TEST_F(LaberintoPerformanceTest, Size_10000x10000) {
    runLaberintoTest(10000, 10000);
}






int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
