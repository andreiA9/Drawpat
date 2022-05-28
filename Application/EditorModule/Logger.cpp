#include "Logger.h"



Logger s_globalLoggerInstance;

// AICI sunt PARAMETRII < context.file, context.line, context.function, context.category
// Q_DECL_CONSTEXPR QMessageLogger(const char *file, int line, const char *function, const char *category)
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    const char *category = context.category ? context.category : "";
    QFileInfo info(file);
    const char *fileName = info.fileName().toStdString().c_str();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "%s Debug: %s | %s:%u, %s\n", category, localMsg.constData(), fileName, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "%s Info: %s | %s:%u, %s\n", category, localMsg.constData(), fileName, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s Warning: %s | %s:%u, %s\n", category, localMsg.constData(), fileName, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "%s Critical: %s | %s:%u, %s\n", category, localMsg.constData(), fileName, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "%s Fatal: %s | %s:%u, %s\n", category, localMsg.constData(), fileName, context.line, function);
        break;
    }
}


Logger::Logger()
    : m_logLevels{LOG_LEVEL_OFF}
{
    setLevelsToDefault();
//    std::function<QtMessageHandler(QtMsgType, const QMessageLogContext &, const QString &)> func = &Logger::myMessageOutput;
//    typedef void(Logger::*MessageHandler)(QtMsgType, const QMessageLogContext &, const QString &);
//    MessageHandler handlerPtr = &Logger::myMessageOutput;
    qInstallMessageHandler(myMessageOutput);
}

Logger::~Logger()
{

}

void Logger::setLevelsToDefault()
{
    // set levels to info by default
    for (int i = 0; i < value_of(LOG_CATEGORY_COUNT); ++i) {
        m_logLevels[i] = LOG_LEVEL_DEBUG;
    }
}

Logger &Logger::getInstance()
{
    return s_globalLoggerInstance;
}

const char *Logger::toCategoryCharString(const LogCategory &category)
{
    return s_logCategoryAsciiStrings.at(value_of(category)).constData();
}

bool Logger::isLogCategoryValid(const LogCategory &category) const
{
    return category < LOG_CATEGORY_COUNT;
}

bool Logger::isLogLevelValid(const LogLevel &level)
{
    return level < LOG_LEVEL_COUNT;
}

Logger::LogLevel Logger::getLogLevel(const LogCategory &category) const
{
    if (isLogCategoryValid(category)) {
        return m_logLevels[category];
    } else {
        Q_ASSERT_X(false, __func__, "invalid log category");
        return LOG_LEVEL_OFF;
    }
}

bool Logger::setLogLevel(const LogCategory &category, const LogLevel &logLevel)
{
    // using assert to force fail under debug build
    // validation of category value is done to avoid any risk of memory corruption
    Q_ASSERT(isLogCategoryValid(category));
    Q_ASSERT(isLogLevelValid(logLevel));
    if (isLogCategoryValid(category) && isLogLevelValid(logLevel)) {
        if (m_logLevels[category] != logLevel) {
            // log on info only when the log level is changed
            // this way we will know from the log the current level for each component
            loggerInfo() << "Logger category" << s_logCategoryStrings[category]
                         << "changed to log level:" << s_logLevelStrings[logLevel];
        }
        m_logLevels[category] = logLevel;
        loggerDebug() << "Logger category" << s_logCategoryStrings[category]
                      << "set to log level:" << s_logLevelStrings[logLevel];
        return true;
    } else {
        return false;
    }
}

// use values in same order as in LogCategory enum
QVector<QByteArray> generateLogCategoryAsciiStrings()
{
    return QVector<QByteArray>() << "Sample"
                                 << "Logger"
                                 << "Editor"
                                 << "ApplicationWindow"
                                 << "sync"
                                 << "storage"
                                 << "wifi"
                                 << "map"
                                 << "skobbler"
                                 << "realreach";
}

// use values in same order as in LogLevel enum
QVector<QByteArray> generateLogLevelAsciiStrings()
{
    return QVector<QByteArray>() << "off"
                                 << "fatal"
                                 << "critical"
                                 << "warning"
                                 << "info"
                                 << "debug";
}

// internal functions used for string array constants generation
QStringList toUnicodeStrings(const QVector<QByteArray> &asciiStrings)
{
    QStringList strings;
    for (const QByteArray &asciiString : asciiStrings) {
        strings.append(QString::fromLatin1(asciiString));
    }

    return strings;
}

QStringList generateLogCategoryStrings()
{
    const QStringList categories = toUnicodeStrings(generateLogCategoryAsciiStrings());

    // assert that the enums are in sync with string values
    Q_ASSERT(categories.size() == Logger::LogCategory::LOG_CATEGORY_COUNT);

    return categories;
}

QStringList generateLogLevelStrings()
{
    const QStringList levels = toUnicodeStrings(generateLogLevelAsciiStrings());

    // assert that the enums are in sync with string values
    Q_ASSERT(levels.size() == Logger::LogLevel::LOG_LEVEL_COUNT);

    return levels;
}

const QStringList Logger::s_logLevelStrings = generateLogLevelStrings();
const QVector<QByteArray> Logger::s_logLevelAsciiStrings = generateLogLevelAsciiStrings();

const QStringList Logger::s_logCategoryStrings = generateLogCategoryStrings();
const QVector<QByteArray> Logger::s_logCategoryAsciiStrings = generateLogCategoryAsciiStrings();
