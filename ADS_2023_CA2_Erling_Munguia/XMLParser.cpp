#include "XMLParser.h"
#include "Tree.h"

int main() {
    const std::string xmlFileName = "C:/Users/User/source/repos/ADS_2023_CA2_Erling_Munguia/ADS_2023_CA2_Erling_Munguia/Example.xml";
    XMLParser xmlParser(xmlFileName); 
    xmlParser.parse(); 
   
    return 0;
}
