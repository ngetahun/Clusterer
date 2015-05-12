#include <iostream>
#include <atomic>
#include "include/ClusteringService.hpp"
#include "include/GlobalFileLogger.hpp"
#include "include/ConcurrentLockingQueue.hpp"
#include "include/MovieLensGraphReader.hpp"


using namespace clc;
using namespace clb;


int main()
{
    GlobalFileLogger::init();
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Exe Version: ", CLUSTERER_VERSION);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Exe Version FUll: ", CLUSTERER_VERSION_FULL);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Lib Version: ", CLUSTERER_LIB_VERSION);
    GlobalFileLogger::instance()->log(SeverityType::INFO, "Definition Lib Version FUll: ", CLUSTERER_LIB_VERSION_FULL);


    ClusteringService service;
    bool running = true;
    static std::atomic<bool> flag;
    flag = true;
    clc::ConcurrentLockingQueue<std::pair<PopulationMember<IntegerVectorEncoding, double>, uint64_t>>* queue;
    int option;
    while (running)
    {
        std::cout << "1) Load Configuration from file.\n";
        std::cout << "2) Save Configuration to file.\n";
        std::cout << "3) Load Graph (Pair type) from file.\n";
        std::cout << "4) Load Graph (Movie Lens type) from file.\n";
        std::cout << "5) Load Zachary data set.\n";
        std::cout << "6) Load Movie Lens data set.\n";
        std::cout << "7) Save Graph to file.\n";
        std::cout << "8) Import Population from file.\n";
        std::cout << "9) Export Population to file.\n";
        std::cout << "10) Run Algorithm.\n";
        std::cout << "11) Run Algorithm(reset population).\n";
        std::cout << "12) Exit.\n";
        std::cout << std::flush;
        std::cin >> option;
        std::cin.get();
        switch (option)
        {
            case 1:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.loadConfiguration(filename))
                    {
                        std::cout << "\tLoaded configuration parameters succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading configuration parameters failed." << std::endl;
                    }
                }
                break;
            case 2:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.saveConfiguration(filename))
                    {
                        std::cout << "\tSaved configuration parameters succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tSaving configuration parameters failed." << std::endl;
                    }
                }
                break;
            case 3:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.loadGraphTypeVertexPairWeight(filename))
                    {
                        std::cout << "\tLoaded graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading graph failed." << std::endl;
                    }
                }
                break;
            case 4:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.loadGraphTypeMovieLens(filename))
                    {
                        std::cout << "\tLoaded graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading graph failed." << std::endl;
                    }
                }
                break;
            case 5:
                {
                    std::string filename = "../test_files/out.ucidata-zachary";
                    if (service.loadGraphTypeVertexPairWeight(filename))
                    {
                        std::cout << "\tLoaded zachary graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading zachary graph failed." << std::endl;
                    }
                }
                break;
            case 6:
                {
                    std::string filename = "../test_files/u.data";
                    if (service.loadGraphTypeMovieLens(filename))
                    {
                        std::cout << "\tLoaded movie lens graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoading movie lens graph failed." << std::endl;
                    }
                }
                break;
            case 7:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.saveGraphToFile(filename))
                    {
                        std::cout << "\tSaved graph succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tSaved graph failed." << std::endl;
                    }
                }
                break;
            case 8:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.loadPopulation(filename))
                    {
                        std::cout << "\tLoaded population succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tLoaded population failed." << std::endl;
                    }
                }
                break;
            case 9:
                {
                    std::string filename;
                    std::cout << "Provide a a filename: ";
                    std::getline(std::cin, filename);
                    if (service.savePopulation(filename))
                    {
                        std::cout << "\tSaved population succesfully." << std::endl;
                    }
                    else
                    {
                        std::cout << "\tSaved population failed." << std::endl;
                    }
                }
                break;
            case 10:
                {
                    queue = service.getOutQueue();
                    std::thread t([=]
                    {
                        while (flag.load())
                        {
                            auto res = queue->pop();
                            std::string buffer;
                            std::cout << "Current fitness: " << res.first.fitnessValue << std::endl;
                            std::cout << "Encoding: " << std::endl;
                            for (auto& e : res.first.populationEncoding.getEncoding())
                            {
                                std::cout << e << " ";
                                buffer.append(std::to_string(e) + " ");
                            }
                            std::cout << std::endl;
                            GlobalFileLogger::instance()->log(SeverityType::INFO, "Current population: \n",buffer);
                        }
                    });
                    if (service.runAlgorithm(false))
                    {
                        std::cout << "\tAlgorithm run was succesful." << std::endl;
                        flag = false;
                        std::cout << "Dummy encoding for this demo only" << std::endl;
                        queue->push(std::make_pair(PopulationMember<IntegerVectorEncoding, double>(), 0));
                    }
                    else
                    {
                        std::cout << "\tAlgorithm run failed." << std::endl;
                        flag = false;
                        std::cout << "Dummy encoding for this demo only" << std::endl;
                        queue->push(std::make_pair(PopulationMember<IntegerVectorEncoding, double>(), 0));
                    }
                    t.join();
                    flag = true;
                }
                break;
            case 11:
                {
                    queue = service.getOutQueue();
                    std::thread t([=]
                    {
                        while (flag.load())
                        {
                            auto res = queue->pop();
                            std::cout << "Current fitness: " << res.first.fitnessValue << std::endl;
                            std::cout << "Encoding: " << std::endl;
                            for (auto& e : res.first.populationEncoding.getEncoding())
                            {
                                std::cout << e << " ";
                            }
                            std::cout << std::endl;
                        }
                    });
                    if (service.runAlgorithm(true))
                    {
                        std::cout << "\tAlgorithm run was succesful." << std::endl;
                        flag = false;
                        std::cout << "Dummy encoding for this demo only" << std::endl;
                        queue->push(std::make_pair(PopulationMember<IntegerVectorEncoding, double>(), 0));
                    }
                    else
                    {
                        std::cout << "\tAlgorithm run failed." << std::endl;
                        flag = false;
                        std::cout << "Dummy encoding for this demo only" << std::endl;
                        queue->push(std::make_pair(PopulationMember<IntegerVectorEncoding, double>(), 0));
                    }
                    t.join();
                    flag = true;
                }
                break;
            case 12:
                {
                    running = false;
                }
                break;
            default:
                std::cout << "Please use a valid option, between 1 and 12!" << std::endl;
                break;
        }
        std::cout << "\n\n";
    }

    return 0;
}