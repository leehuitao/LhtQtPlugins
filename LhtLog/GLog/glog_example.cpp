#include "glog_example.h"
#include "glog/logging.h"

GLogExample::GLogExample() {
}

void GLogExample::GLogInit()
{
    FLAGS_stderrthreshold=google::INFO;
    FLAGS_colorlogtostderr=true;

    LOG(INFO) << "file";
    // Most flags work immediately after updating values.
    FLAGS_logtostderr = true;
    LOG(INFO) << "stderr";
    FLAGS_logtostderr = false;
    // This won't change the log destination. If you want to set this
    // value, you should do this before google::InitGoogleLogging .
    FLAGS_log_dir = "/some/log/directory";
    LOG(INFO) << "the same file";

}
