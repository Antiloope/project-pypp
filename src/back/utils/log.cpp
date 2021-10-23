#include <sys/stat.h>
#include <fstream>
#include "log.h"

using namespace pypp;
using namespace std;

const char* LOG_FILE_NAME = "pypp.log";
const char* LOG_FOLDER_PATH = "/tmp/pypp/";

void Log::initLogFile() {
    struct stat info {};
    stat( LOG_FOLDER_PATH, &info );

    if(info.st_mode & S_IFDIR)
        return;

    mkdir(LOG_FOLDER_PATH,0777);
}

string Log::getLogFilePath() {
    return string(LOG_FOLDER_PATH) + string(LOG_FILE_NAME);
}

void Log::write(const char * text, LogType type) {
    _write(text, type);
}

void Log::write(const string& text, LogType type) {
    _write(text, type);
}

void Log::write(const exception& e, LogType type) {
    _write(e.what(),type);
}

void Log::_write(const string& text, LogType type) {
    ofstream file(getLogFilePath(), ofstream::app);

    time_t t = time( nullptr );

    string time = asctime( localtime(&t));

    time.pop_back();
    time = time.substr(11,8);

    file << time;

    switch ( type ) {
        case error_t:
            file << ": [ERROR] ";
            break;
        case warning_t:
            file << ": [WARNING] ";
            break;
        case info_t:
            file << ": [INFO] ";
            break;
    }

    file << text << endl;

    file.close();
}
