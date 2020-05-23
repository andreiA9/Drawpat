#ifndef LOGGER_H
#define LOGGER_H


#include <QVector>
#include <type_traits>
#include <QDebug>
#include <QFileInfo>



template <typename T>
struct underlying_type {
    typedef typename std::conditional<T(-1) < T(0), typename std::make_signed<T>::type,
                                      typename std::make_unsigned<T>::type>::type type;
};

// Extracts the numeric value of an enum class value
template <typename T>
inline constexpr typename underlying_type<T>::type value_of(const T &value)
{
    return static_cast<typename underlying_type<T>::type>(value);
}


class Logger
{
public:
    // enum values must be in sync with list of strings (see cpp)
    enum LogCategory {
        LOG_CATEGORY_SAMPLE = 0,
        LOG_CATEGORY_LOGGER,
        LOG_CATEGORY_EDITOR,
        LOG_CATEGORY_ACTIVITY,
        LOG_CATEGORY_SYNC,
        LOG_CATEGORY_STORAGE,
        LOG_CATEGORY_WIFI,
        LOG_CATEGORY_MAP,
        LOG_CATEGORY_SKOBBLER,
        LOG_CATEGORY_REAL_REACH,

        // add other categories here
        // when adding other categories do not forget to also add debug statement macros
        // and also to update list of strings (see cpp)

        LOG_CATEGORY_COUNT
    };

    // enum values must be in sync with list of strings (see cpp)
    enum LogLevel {
        LOG_LEVEL_OFF = 0,
        LOG_LEVEL_FATAL,
        LOG_LEVEL_CRITICAL,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG,

        LOG_LEVEL_COUNT
    };

public:
    Logger();
    ~Logger();

    void setLevelsToDefault();

    static Logger &getInstance();

    static const char * toCategoryCharString(const LogCategory &category);

    bool isLogCategoryValid(const LogCategory &category) const;

    bool isLogLevelValid(const LogLevel &level);

    LogLevel getLogLevel(const LogCategory &category) const;

    /**
     * @brief Set the log level manually for a category (useful in unit tests)
     * @param category: the category for which log level is changed
     * @param logLevel: the desired log level
     * @return true if success, false on error
     * NOTE: Nothing will be done if provided category is not valid
     */
    bool setLogLevel(const LogCategory &category, const LogLevel &logLevel);

private:
    static const QVector<QByteArray> s_logCategoryAsciiStrings;
    static const QStringList s_logLevelStrings;
    static const QVector<QByteArray> s_logLevelAsciiStrings;
    static const QStringList s_logCategoryStrings;
    volatile LogLevel m_logLevels[LOG_CATEGORY_COUNT];
    LogCategory m_category;
};



//#define qWarning QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).warning


// we should output statements with level <= set level
// going to reverse condition and use else block to avoid surprises
#define loggerMacro(STATEMENT_LEVEL, CATEGORY)                                  \
    if (STATEMENT_LEVEL > Logger::getInstance().getLogLevel(CATEGORY)) { \
    } else                                                                      \
    QMessageLogger(__FILE__, __LINE__, __func__, Logger::toCategoryCharString(CATEGORY))
    // Q_DECL_CONSTEXPR QMessageLogger(const char *file, int line, const char *function, const char *category)

#define editorDebug loggerMacro(Logger::LOG_LEVEL_DEBUG, Logger::LOG_CATEGORY_EDITOR).debug
#define editorInfo loggerMacro(Logger::LOG_LEVEL_INFO, Logger::LOG_CATEGORY_EDITOR).info
#define editorWarning loggerMacro(Logger::LOG_LEVEL_WARNING, Logger::LOG_CATEGORY_EDITOR).warning
#define editorCritical loggerMacro(Logger::LOG_LEVEL_CRITICAL, Logger::LOG_CATEGORY_EDITOR).critical
#define editorFatal loggerMacro(Logger::LOG_LEVEL_VERBOSE, Logger::LOG_CATEGORY_EDITOR).fatal

#define loggerDebug loggerMacro(Logger::LOG_LEVEL_DEBUG, Logger::LOG_CATEGORY_LOGGER).debug
#define loggerInfo loggerMacro(Logger::LOG_LEVEL_INFO, Logger::LOG_CATEGORY_LOGGER).info
#define loggerWarning loggerMacro(Logger::LOG_LEVEL_WARNING, Logger::LOG_CATEGORY_LOGGER).warning
#define loggerCritical loggerMacro(Logger::LOG_LEVEL_CRITICAL, Logger::LOG_CATEGORY_LOGGER).critical
#define loggerFatal loggerMacro(Logger::LOG_LEVEL_VERBOSE, Logger::LOG_CATEGORY_LOGGER).fatal

#endif
