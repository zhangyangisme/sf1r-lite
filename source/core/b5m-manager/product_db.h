#ifndef SF1R_B5MMANAGER_PRODUCTDB_H_
#define SF1R_B5MMANAGER_PRODUCTDB_H_

#include <string>
#include <vector>
#include <product-manager/product_price.h>
#include <document-manager/Document.h>
#include "b5m_types.h"
#include <am/tc/BTree.h>
#include <am/leveldb/Table.h>
#include <glog/logging.h>
#include <boost/unordered_set.hpp>

namespace sf1r {


    class ProductProperty
    {
    public:
        //typedef std::map<std::string, int32_t> SourceMap;
        typedef boost::unordered_set<std::string> SourceType;
        typedef izenelib::util::UString UString;

        UString pid;
        ProductPrice price;
        SourceType source;
        int64_t itemcount;
        UString oid;

        ProductProperty();

        bool Parse(const Document& doc);

        void Set(Document& doc) const;


        std::string GetSourceString() const;

        izenelib::util::UString GetSourceUString() const;

        ProductProperty& operator+=(const ProductProperty& other);

        //ProductProperty& operator-=(const ProductProperty& other);

        std::string ToString() const;
    };


}

#endif
