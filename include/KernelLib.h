#ifndef KERNELLIB_H
#define KERNELLIB_H

#include <string>

#ifdef _WIN32
    #ifdef KERNELLIB_EXPORT
        #define KERNELLIB_API __declspec(dllexport)
    #else
        #define KERNELLIB_API __declspec(dllimport)
    #endif
#else
    #define KERNELLIB_API
#endif

namespace KernelLib {

    KERNELLIB_API std::string getVersion();

    KERNELLIB_API std::string readFile(const std::string& filename);

} // namespace KernelLib

#endif // KERNELLIB_H