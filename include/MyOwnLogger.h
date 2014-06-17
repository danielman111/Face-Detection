#ifndef LoggerHeader_H_
#define LoggerHeader_H_

#include "Poco/LoggingFactory.h"
#include "Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"
#include <string>
#include <sstream>
#include <vector>

class MyOwnLogger {
  
private:

	std::vector<Poco::Logger*> mLoggers;

public:

    MyOwnLogger(int filePriority, int consolePriority, const std::string& fileName);

    virtual ~MyOwnLogger();

    void Log(const std::string& inLogString, Poco::Message::Priority inPriority);

    void Log(const std::ostringstream& inLogString, Poco::Message::Priority inPriority);
};
#endif
