#include <sstream>
#include <iostream>
#include <string>
#include "HashMap.hpp"


int main()
{
    std::string input, input1, input2, input3;
    HashMap hashMap;
    bool debugStatus = false;

    do {
        input1 = "";
        input2 = "";
        input3 = "";

        std::getline(std::cin, input);
        std::istringstream parse_input(input);
        parse_input >> input1 >> input2 >> input3;

        if (input1 == "CREATE" && input2 != "" && input3 != ""){
            if (hashMap.contains(input2))
                std::cout << "EXISTS" << std::endl;
            
            else {
                hashMap.add(input2, input3);
                std::cout << "CREATED" <<std::endl;
            }
        }
        else if(input1 == "LOGIN" && input2 != "" && input3 != "") {
            if (hashMap.contains(input2) && hashMap.value(input2) == input3)
                std::cout << "SUCCEEDED" << std::endl;
            
            else 
                std::cout << "FAILED" << std::endl;
        }
        else if (input1 == "REMOVE" && input2 != "" && input3 == ""){
            if (hashMap.contains(input2)){
                hashMap.remove(input2);
                std::cout << "REMOVED" << std::endl;
            }
            else 
                std::cout << "NONEXISTENT" << std::endl;
        }
        else if (input1 == "CLEAR" && input2 == "" && input3 == ""){
            hashMap.clear();
            std::cout << "CLEARED" << std::endl;
        }
        else if (input1 == "DEBUG" && input2 == "ON" && input3 == ""){
            if (!debugStatus){
                debugStatus = true;
                std::cout << "ON NOW" << std::endl;
            }
            else 
                std::cout << "ON ALREADY" << std::endl;
        }
        else if (input1 == "DEBUG" && input2 == "OFF" && input3 == ""){
            if(debugStatus){
                debugStatus = false;
                std::cout << "OFF NOW" << std::endl;
            }
            else 
                std::cout << "OFF ALREADY" << std::endl;
        }

        else if (input1 == "LOGIN" && input2 == "COUNT" && input3 == "" && debugStatus)
            std::cout << hashMap.size() << std::endl;
        else if (input1 == "BUCKET" && input2 == "COUNT" && input3 == "" && debugStatus)
            std::cout << hashMap.bucketCount() << std::endl;
        else if (input1 == "LOAD" && input2 == "FACTOR" && input3 == "" && debugStatus)
            std::cout << hashMap.loadFactor() << std::endl;
        else if (input1 == "MAX" && input2 == "BUCKET" && input3 == "SIZE" && debugStatus)
            std::cout << hashMap.maxBucketSize() << std::endl;
        else if (input1 == "QUIT")
            continue;
        else 
            std::cout << "INVALID" << std::endl;

    } while (input1 != "QUIT");

    std::cout << "GOODBYE" << std::endl;

    return 0;
}


