#include <sstream>
#include <iostream>

std::ostringstream tdbg;

void tdbg_report_failure(const char * file, unsigned int line) {
    tdbg.flush();
    const std::string & str = tdbg.str();
    if(!str.empty()) {
        std::cerr << "[Failed with] " << str << std::endl;
    }
    tdbg.str(std::string());
}

void tdbg_clear_output(const char * file, unsigned int line) {
    tdbg.str(std::string());
}

bool tdbg_empty() {
    return tdbg.str().empty();
}