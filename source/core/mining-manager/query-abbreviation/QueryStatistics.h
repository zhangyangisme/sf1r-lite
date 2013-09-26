/** QueryStatistics.h
 * Anthor Kevin Lin
 * Date 2013.08.26
 */
#ifndef QUERY_STATISTICS_H
#define QUERY_STATISTICS_H

#include <boost/unordered_map.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <util/singleton.h>
#include <util/cronexpression.h>

namespace sf1r
{
typedef boost::unordered_map<std::string, unsigned long> FreqType;
class MiningManager;

class QueryStatistics
{
public:
    //static QueryStatistics* getInstance()
    //{
    //   return izenelib::util::Singleton<QueryStatistics>::get(); 
    //}
    
    QueryStatistics(MiningManager* mining, std::string& collection);
    ~QueryStatistics();
public:
    double frequency(std::string word);
    bool isCombine(const std::string& lv, const std::string& rv);
    void init();
private:
    void serialize_(std::ostream& out);
    void deserialize_(std::istream& in);
    bool statistics_();
    void cronJob_(int callType);
private:
    MiningManager* miningManager_;
    std::string lastTimeStr_;
    std::string collectionName_;
    unsigned long totalWords_;
    FreqType* wordsFreq_;
    boost::shared_mutex mtx_;
    std::string cronJobName_;

    izenelib::util::CronExpression cronExpression_;
};
}
#endif
