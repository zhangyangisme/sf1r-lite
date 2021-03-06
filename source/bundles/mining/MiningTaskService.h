#ifndef MINING_BUNDLE_TASK_SERVICE_H
#define MINING_BUNDLE_TASK_SERVICE_H

#include <util/osgi/IService.h>
#include <util/cronexpression.h>

#include <mining-manager/MiningManager.h>
#include "MiningBundleConfiguration.h"

namespace sf1r
{
class MiningTaskService : public ::izenelib::osgi::IService
{
public:
    MiningTaskService(MiningBundleConfiguration* bundleConfig);

    ~MiningTaskService();

    void DoMiningCollection(int64_t timestamp);
    bool DoMiningCollectionFromAPI();

    void DoContinue();

    void EnsureHasDeletedDocDuringMining() { miningManager_->EnsureHasDeletedDocDuringMining(); }

    MiningBundleConfiguration* getMiningBundleConfig(){ return bundleConfig_; }

    void flush();

private:
    void cronJob_(int calltype);

private:
    boost::shared_ptr<MiningManager> miningManager_;

    MiningBundleConfiguration* bundleConfig_;

    izenelib::util::CronExpression cronExpression_;

    const std::string cronJobName_;

    friend class MiningBundleActivator;
};

}

#endif

