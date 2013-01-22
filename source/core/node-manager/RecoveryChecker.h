#ifndef SF1R_NODEMANAGER_RECOVERCHECKER_H
#define SF1R_NODEMANAGER_RECOVERCHECKER_H

#include "RequestLog.h"
#include <string>
#include <configuration-manager/CollectionPath.h>
#include <util/singleton.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace sf1r
{

class ReqLogMgr;
class SF1Config;
class RecoveryChecker
{
public:
    //typedef boost::function<bool(const std::string&, const std::string&)> StartColCBFuncT;
    //typedef boost::function<bool(const std::string&, bool)> StopColCBFuncT;
    typedef boost::function<void(const std::string&)> FlushColCBFuncT;
    typedef boost::function<bool(const std::string&)> ReopenColCBFuncT;

    static RecoveryChecker* get()
    {
        return ::izenelib::util::Singleton<RecoveryChecker>::get();
    }
    //RecoveryChecker(const CollectionPath& colpath);
    bool backup();
    bool setRollbackFlag(uint32_t inc_id);
    void clearRollbackFlag();
    bool rollbackLastFail();

    //void setRestartCallback(StartColCBFuncT start_col, StopColCBFuncT stop_col)
    //{
    //    start_col_ = start_col;
    //    stop_col_ = stop_col;
    //}

    void setColCallback(ReopenColCBFuncT reopen_cb, FlushColCBFuncT flush_cb)
    {
        reopen_col_ = reopen_cb;
        flush_col_ = flush_cb;
    }

    void init(const std::string& workdir);
    void addCollection(const std::string& colname, const CollectionPath& colpath, const std::string& configfile);
    void removeCollection(const std::string& colname);

    //void updateCollection(const SF1Config& sf1_config);
    boost::shared_ptr<ReqLogMgr> getReqLogMgr()
    {
        return reqlog_mgr_;
    }
    void onRecoverCallback();
    void onRecoverWaitPrimaryCallback();
    void onRecoverWaitReplicasCallback();
    void syncToNewestReqLog();
    void wait();
private:
    bool redoLog(ReqLogMgr* redolog, uint32_t start_id);
    //StartColCBFuncT start_col_;
    //StopColCBFuncT stop_col_;
    ReopenColCBFuncT reopen_col_;
    FlushColCBFuncT flush_col_;
    std::string backup_basepath_;
    std::string request_log_basepath_;
    std::string redo_log_basepath_;
    std::string rollback_file_;
    boost::shared_ptr<ReqLogMgr> reqlog_mgr_;
    typedef std::map<std::string, std::pair<CollectionPath, std::string> > CollInfoMapT;
    CollInfoMapT all_col_info_;
    boost::mutex mutex_;
};

}

#endif