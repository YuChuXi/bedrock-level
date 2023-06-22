//
// Created by xhy on 2023/3/30.
//

#ifndef BEDROCK_LEVEL_BEDROCK_LEVEL_H
#define BEDROCK_LEVEL_BEDROCK_LEVEL_H
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <tuple>

#include "bedrock_key.h"
#include "chunk.h"
#include "level_dat.h"
#include "leveldb/db.h"
#include "nbt-cpp/nbt.hpp"

namespace bl {

    class bedrock_level {
       public:
        // for users

        [[nodiscard]] bool is_open() const { return this->is_open_; }

        bool open(const std::string &root);

        leveldb::DB *&db() { return this->db_; }

        inline void close() {}

        ~bedrock_level();

        chunk *get_chunk(const chunk_pos &cp);

        block_info get_block(const bl::block_pos &pos, int dim);

        [[nodiscard]] std::tuple<chunk_pos, chunk_pos> get_range(int dim) const;

        [[nodiscard]] inline size_t cached_chunk_size() const {
            return this->chunk_data_cache_.size();
        };

        level_dat &dat() { return this->dat_; }

       private:
        bool is_open_{false};

        level_dat dat_;

        leveldb::DB *db_{nullptr};

        std::string root_name_;

        std::map<chunk_pos, chunk *> chunk_data_cache_;

        void cache_keys();

       private:
        bool read_db();

        static const std::string LEVEL_DATA;
        static const std::string LEVEL_DB;
    };

}  // namespace bl

#endif  // BEDROCK_LEVEL_BEDROCK_LEVEL_H
