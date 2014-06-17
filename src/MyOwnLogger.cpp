#include "../include/MyOwnLogger.h"

//constructor who gets the file and console priority, and the file name of the logger
MyOwnLogger::MyOwnLogger(int filePriority, int consolePriority, const std::string& fileName) : mLoggers() {
    mLoggers.push_back(&Poco::Logger::create("Log.Console", Poco::LoggingFactory::defaultFactory().createChannel("ConsoleChannel"), consolePriority));
    mLoggers.push_back(&Poco::Logger::create("Log.File", Poco::LoggingFactory::defaultFactory().createChannel("FileChannel"), filePriority));
    mLoggers.at(1)->getChannel()->setProperty("path", fileName);
    int size= mLoggers.size();
    for (int i= 0; i < size; i++){
        if (i != 0)
        	mLoggers.at(i)->getChannel()->open();
    }
}

/*** Logger Destructor ***/
MyOwnLogger::~MyOwnLogger()
{
	int size= mLoggers.size();
    for (int i= 0; i < size; i++){
        	mLoggers[i]->getChannel()->close();
        	mLoggers[i]->getChannel()->release();
    }
}

/*** Logger Message ***/
void MyOwnLogger::Log(const std::string& inLogString, Poco::Message::Priority inPriority) {
    Poco::Message msg;
    msg.setPriority(inPriority);
    msg.setText(inLogString);
    int size= mLoggers.size();
    for (int i= 0; i < size; i++){
        mLoggers[i]->log(msg);
    }
}

void MyOwnLogger::Log(const std::ostringstream& inLogString, Poco::Message::Priority inPriority) {
    Log(inLogString.str(), inPriority);
}
