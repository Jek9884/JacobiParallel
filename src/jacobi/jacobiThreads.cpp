#include "../../include/jacobi.hpp"

void jacobiThrs(mv::Matrix A, mv::Vector b, mv::Vector& sol, int maxIter,  const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol, int nw){

    auto computeRow = [&](mv::Vector &res, int startIdx, int endIdx){

        for(int i=startIdx; i<endIdx+1; i++){
            mv::Vector vec = A[i];
            int dim = static_cast<int>(vec.size());
            double sigma = 0;

            for(int j=0; j<dim; j++){
                if(i != j){
                    sigma = sigma + vec[j]*sol[j];
                }
            }
            res[i] = (1 / vec[i]) * (b[i] - sigma);
        }

    };

    std::string message = "Jacobi threads with " + std::to_string(maxIter) + " steps";

    #if defined(OVERHEAD)
        std::string sepOver = ",";
        std::string headerOver = "thread"+sepOver+std::to_string(nw)+sepOver+std::to_string(maxIter)+sepOver+std::to_string(b.size())+";";
        writeOnFile(headerOver, RESULTS_FOLDER, OVERHEAD_IN_FILENAME);
        utimer* overheadTimer = new utimer("Map creation overhead", overhead);
    #endif

    Map map(static_cast<int>(A.size()), mapMode::Chunk, nw, computeRow);

    #if defined(OVERHEAD)
        delete overheadTimer;
    #endif

    map.execute(maxIter, sol, stoppingCriteria, tol);
    
    #if defined(OVERHEAD)
        writeOnFile("\n", RESULTS_FOLDER, OVERHEAD_IN_FILENAME);
        extractTime(RESULTS_FOLDER, OVERHEAD_IN_FILENAME, OVERHEAD_OUT_FILENAME);
    #endif
}