#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "DoubleList.h"
#include <string>

class FileHandler
{
public:
    // Listeyi dosyaya yazar
    static void saveToFile(DoubleList *list, const std::string &filename);

    // Dosyadan okuyup listeyi doldurur
    static void readFromFile(DoubleList *list, const std::string &filename);
};

#endif