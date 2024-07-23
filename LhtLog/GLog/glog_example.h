#ifndef GLOG_EXAMPLE_H
#define GLOG_EXAMPLE_H

#include <QCoreApplication>
#include <QObject>

// FLAGS_logtostderr = false; //是否将所有日志输出到stderr，而非文件
// FLAGS_alsologtostderr = false;//日志记录到文件的同时输出到strerr
// FLAGS_colorlogtostderr = false;//将彩色日志输出到stderr
// FLAGS_drop_log_memory = true; //日志写到文件的时候删除其在内存中的buf
// FLAGS_alsologtoemail = ""; //日志记录到文件的同时发送邮件到指定邮件地址
// FLAGS_log_prefix = true; //每行log加前缀
// FLAGS_minloglevel = google::INFO;//日志最低记录等级
// FLAGS_logbuflevel = google::INFO;//缓存日志的最低等级 , -1表示不缓存,0表示只缓存google::INFO
// FLAGS_logbufsecs = 30; //日志最多缓存的秒数
// FLAGS_logemaillevel = 999; //日志发送邮件的最低等级 , 0表示发送全部 , 3表示只发送google::FATAL
// FLAGS_logmailer = “/bin/mail” ; //邮件发送的用户
// FLAGS_log_dir = ""; //设置日志文件输出目录
// FLAGS_log_link = ""; //给日志目录的文件添加额外的链接
// FLAGS_max_log_size = 1800; //最大日志大小（MB）, 如果设置为0将默认为1
// FLAGS_stop_logging_if_full_disk = false;//磁盘满停止记录日志
// FLAGS_log_backtrace_at = ""; //当记录"文件名:行号"的日志的时候触发一个backtrace
// FLAGS_v = 0; //记录所有 VLOG(m)中 m <= 这个值的自定义log , 这个标签会被 FLAGS_vmodule 覆盖
// FLAGS_vmodule = ""; //分模块（文件）设置
class GLogExample
{
public:
    GLogExample();

    void GLogInit();
};

#endif // GLOG_EXAMPLE_H
