#ifndef LOGGING_H
#define LOGGING_H

#include "logging/logger.h"
#include "services.h"

#define LOG_TRACE(log_format, ...) \
     Services::get<Logger>()->log(Logger::Level::LEVEL_TRACE, "[TRACE][%s - %s][%s:%d][%s] " log_format "\n", \
                            __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_DEBUG(log_format, ...) \
     Services::get<Logger>()->.log(Logger::Level::LEVEL_DEBUG, "[DEBUG][%s - %s][%s:%d][%s] " log_format "\n", \
                            __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_INFO(log_format,  ...) \
     Services::get<Logger>()->log(Logger::Level::LEVEL_INFO,  "[INFO ][%s - %s][%s:%d][%s] " log_format "\n", \
                            __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_WARN(log_format,  ...) \
     Services::get<Logger>()->log(Logger::Level::LEVEL_WARN,  "[WARN ][%s - %s][%s:%d][%s] " log_format "\n", \
                            __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_ERROR(log_format, ...) \
     Services::get<Logger>()->log(Logger::Level::LEVEL_ERROR, "[ERROR][%s - %s][%s:%d][%s] " log_format "\n", \
                            __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define LOG_FATAL(log_format, ...) \
     Services::get<Logger>()->log(Logger::Level::LEVEL_FATAL, "[FATAL][%s - %s][%s:%d][%s] " log_format "\n", \
                            __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

// OpenGL

#define GL_FLUSH_ERROR //while(glGetError() != GL_NO_ERROR)
#define GL_CHECK_ERROR //{ GLenum e_rro_r; while((e_rro_r = glGetError()) != GL_NO_ERROR) { LOG_ERROR("GLError: %d", e_rro_r); } }


#endif // LOGGING_H
