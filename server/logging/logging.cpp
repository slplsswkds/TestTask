#include "logging.h"

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

void init_logging() {
    logging::add_file_log
    (
        keywords::file_name = "server-logfile_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,            // 10MB
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), // every day
        keywords::max_size = 50 * 1024 * 1024,                 // 50MB
        keywords::min_free_space = 100 * 1024 * 1024,          // 100MB
        keywords::format = "[%TimeStamp%] [%Severity%]: %Message%",
        keywords::auto_flush = true
    );

    logging::add_common_attributes();
}
