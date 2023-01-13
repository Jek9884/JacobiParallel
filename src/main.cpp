#include "../include/jacobi.hpp"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

void test_performance_jacobi(int nw, int dim, int threshold, int nRuns) {

    std::tuple data = mv::generateSystem(dim);
    mv::Matrix a = std::get<0>(data);
    mv::Vector b = std::get<1>(data);
    mv::Vector x = std::get<2>(data);
    mv::Vector expected = std::get<3>(data);

    for (int i = 0; i < nRuns; i++) {

        x = std::get<2>(data);
        x = jacobiSeq(a, b, x, mv::checkRes,threshold, 1e-8);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }


        x = std::get<2>(data);
        jacobiThrs(a, b, x, threshold, nw);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }

        x = std::get<2>(data);
        x = jacobiOpenmp(a, b, x, mv::checkRes, threshold, 1e-8, nw);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }

        x = std::get<2>(data);
        x = jacobiFF(a, b, x, mv::checkRes, threshold, 1e-8, nw);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }
}

void test_sequential_jacobi(int dim, int maxIter, int nRuns){
    
    std::tuple data = mv::generateSystem(dim);
    mv::Matrix a = std::get<0>(data);
    mv::Vector b = std::get<1>(data);
    mv::Vector expected = std::get<3>(data);

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "sequential"+sepPer+std::to_string(maxIter)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i = 0; i <nRuns; i++){
        mv::Vector x = std::get<2>(data);
        
        #if defined(PERFORMANCE)
            utimer* seqTimer = new utimer("Jacobi sequential performance", performance);
        #endif

        jacobiSeq(a, b, x, mv::checkRes, maxIter, 1e-8);
        
        #if defined(PERFORMANCE)
            delete seqTimer;
        #endif
        
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif
    
}

void test_thread_jacobi(int nw, int dim, int threshold, int nRuns){

    std::tuple data = mv::generateSystem(dim);
    mv::Matrix a = std::get<0>(data);
    mv::Vector b = std::get<1>(data);
    mv::Vector expected = std::get<3>(data);

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "thread"+sepPer+std::to_string(nw)+sepPer+std::to_string(threshold)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i=0; i<nRuns; i++){

        mv::Vector x = std::get<2>(data);

        #if defined(PERFORMANCE)
            utimer* performanceTimer = new utimer("Jacobi thread performance", performance);
        #endif

        jacobiThrs(a, b, x, threshold, nw);

        #if defined(PERFORMANCE)
            delete performanceTimer;
        #endif
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif
}

void test_openmp_jacobi(int nw, int dim, int threshold, int nRuns){

    std::tuple data = mv::generateSystem(dim);
    mv::Matrix a = std::get<0>(data);
    mv::Vector b = std::get<1>(data);
    mv::Vector expected = std::get<3>(data);

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "openmp"+sepPer+std::to_string(threshold)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i=0; i<nRuns; i++){
        mv::Vector x = std::get<2>(data);

        #if defined(PERFORMANCE)
            utimer* openmpTimer = new utimer("Jacobi openMP performance", performance);
        #endif

        jacobiOpenmp(a, b, x, mv::checkRes, threshold, 1e-8, nw);

        #if defined(PERFORMANCE)
            delete openmpTimer;
        #endif

        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif
}

void test_ff_jacobi(int nw, int dim, int threshold, int nRuns){

    std::tuple data = mv::generateSystem(dim);
    mv::Matrix a = std::get<0>(data);
    mv::Vector b = std::get<1>(data);
    mv::Vector expected = std::get<3>(data);

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "ff"+sepPer+std::to_string(threshold)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif
    
    for(int i=0; i<nRuns; i++){
        mv::Vector x = std::get<2>(data);

        #if defined(PERFORMANCE)
            utimer* ffTimer = new utimer("Jacobi FastFlow performance", performance);
        #endif

        jacobiFF(a, b, x, mv::checkRes, threshold, 1e-8, nw);
        
        #if defined(PERFORMANCE)
            delete ffTimer;
        #endif
        
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif

}

void eval_performance(){


}

int main(int argc, char *argv[]){

    assertm((argc == 5), "Number of workers, matrix dimension, number of runs and max iterations are required");

    int nw = (int) strtol(argv[1], nullptr, 10);
    int n = (int) strtol(argv[2], nullptr, 10);
    int nRuns = (int) strtol(argv[3], nullptr, 10);
    int maxIter = (int) strtol(argv[4], nullptr, 10);

    //test_performance_jacobi(nw, n, threshold, iter);
    //test_sequential_jacobi(n, maxIter, nRuns);
    test_thread_jacobi(nw, n, maxIter, nRuns);
    //test_openmp_jacobi(nw, n, maxIter, nRuns);
    //test_ff_jacobi(nw, n, maxIter, nRuns);


    return 0;
}
