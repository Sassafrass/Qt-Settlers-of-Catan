#include "qout.h"

Logger* Logger::instance_ = 0;

Logger* Logger::getLogger()
{
    if( !instance_ )
        instance_ = new Logger();
    return instance_;
}


const QString logLevelEnumToString(LogLevelEnum m)
{
        switch(m)
        {
        case DEBUG_LOG_LEVEL:
            return "DEBUG";
        case INFO_LOG_LEVEL:
            return "INFO";
        case WARN_LOG_LEVEL:
            return "WARN";
        case NOTICE_LOG_LEVEL:
            return "NOTICE";
        case ERROR_LOG_LEVEL:
            return "ERROR";
        case FATAL_LOG_LEVEL:
            return "FATAL";
        default:
            return "";
        }
}
void Logger::log(LogLevelEnum l, QTextStream& os) const
{
    QTextStream qout(stdout);
    qout << "[" << logLevelEnumToString(l) << "]" << " " << *os.string();
    *str_ = "";
    qout.flush();
}
