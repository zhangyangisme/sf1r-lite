#ifndef CORE_SEARCH_MANAGER_SEARCH_MANAGER_H
#define CORE_SEARCH_MANAGER_SEARCH_MANAGER_H

#include "QueryBuilder.h"
#include "SearchManagerPreProcessor.h"
#include "SearchThreadWorker.h"
#include "SearchThreadMaster.h"
#include "TopKReranker.h"
#include "FuzzySearchRanker.h"
#include <configuration-manager/PropertyConfig.h>
#include <ir/id_manager/IDManager.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

using izenelib::ir::idmanager::IDManager;

namespace sf1r
{
class IndexBundleConfiguration;
class SearchKeywordOperation;
class KeywordSearchResult;
class DocumentManager;
class RankingManager;
class IndexManager;
class MiningManager;

class SearchManager
{
public:
    SearchManager(
        const IndexBundleSchema& indexSchema,
        const boost::shared_ptr<IDManager>& idManager,
        const boost::shared_ptr<DocumentManager>& documentManager,
        const boost::shared_ptr<IndexManager>& indexManager,
        const boost::shared_ptr<RankingManager>& rankingManager,
        IndexBundleConfiguration* config);

    /**
     * get search results.
     *
     * @param actionOperation the search parameters
     * @param searchResult it stores the search results
     * @param limit at most how many docs to return. Generally it's TOP_K_NUM.
     * @param offset the index offset of the first returned doc in all candidate
     *        docs, start from 0. Generally it's a multiple of TOP_K_NUM.
     *
     * @note in SF1R driver API documents/search(), there are also such
     *       parameters as "offset" and "limit", which are used for pagination.
     *
     *       While the @p offset and @p limit of this method have different
     *       meanings, they are used to get a batch of docs.
     *
     *       By putting the batch into cache, there is no need to call this
     *       method again as long as the cache is hit.
     */
    bool search(
        const SearchKeywordOperation& actionOperation,
        KeywordSearchResult& searchResult,
        std::size_t limit,
        std::size_t offset);

    void reset_filter_cache();

    void setMiningManager(
        const boost::shared_ptr<MiningManager>& miningManager);

    QueryBuilder* getQueryBuilder()
    {
        return queryBuilder_.get();
    }

private:
    SearchManagerPreProcessor preprocessor_;

    boost::scoped_ptr<QueryBuilder> queryBuilder_;
    boost::scoped_ptr<SearchThreadWorker> searchThreadWorker_;
    boost::scoped_ptr<SearchThreadMaster> searchThreadMaster_;

public:
    TopKReranker topKReranker_;

    FuzzySearchRanker fuzzySearchRanker_;
};

} // end - namespace sf1r

#endif // CORE_SEARCH_MANAGER_SEARCH_MANAGER_H
