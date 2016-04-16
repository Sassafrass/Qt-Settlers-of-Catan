/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** Debug logger class
****************************************************************************/

#ifndef QOUT_H
#define QOUT_H

#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <sstream>

using std::endl;

enum LogLevelEnum {
        DEBUG_LOG_LEVEL,
        INFO_LOG_LEVEL,
        WARN_LOG_LEVEL,
        ERROR_LOG_LEVEL,
        NOTICE_LOG_LEVEL,
        FATAL_LOG_LEVEL
};

/// Implements a simple logging facility.
class Logger
{
public:
        static Logger* getLogger();
        void log(LogLevelEnum l, QTextStream& os) const;
        QTextStream& getStream()
        { return os_; }
private:
        Logger() : str_(new QString()) { os_.setString(str_, QIODevice::WriteOnly); }
        Logger(const Logger &); // hide copy constructor
        Logger& operator=(const Logger &); // hide assign op
        QTextStream os_;
        QString* str_;
        static Logger* instance_;
};
#define LOG_common(level, cptext) do {\
        Logger::getLogger()->getStream() << cptext; \
        Logger::getLogger()->log(level, Logger::getLogger()->getStream());  \
} while(0)


#define LOG_DEBUG(cptext)    LOG_common(DEBUG_LOG_LEVEL, cptext)
#define LOG_INFO(cptext)     LOG_common(INFO_LOG_LEVEL , cptext)
#define LOG_WARN(cptext)     LOG_common(WARN_LOG_LEVEL , cptext)
#define LOG_ERROR(cptext)    LOG_common(ERROR_LOG_LEVEL, cptext)
#define LOG_NOTICE(cptext)   LOG_common(NOTICE_LOG_LEVEL, cptext)
#define LOG_FATAL(cptext)    LOG_common(FATAL_LOG_LEVEL, cptext)


#endif // QOUT_H
