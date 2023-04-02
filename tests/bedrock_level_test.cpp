//
// Created by xhy on 2023/4/1.
//
#include <gtest/gtest.h>
#include "bedrock_level.h"
#include "bedrock_key.h"
#include "sub_chunk.h"
#include "utils.h"
#include "chunk.h"

TEST(BedrockLevel, TraverseKey) {
    using namespace bl;
    bl::bedrock_level level;
    EXPECT_TRUE(level.open("./sample"));
    level.for_each_chunk_pos([&](const chunk_pos &cp) {
        std::cout << cp.to_string() << std::endl;
        auto *ch = level.get_chunk(cp);
        EXPECT_TRUE(ch);
    });

    //-1, -1, 2
}


TEST(BedrockLevel, ZeroChunkTest) {
    using namespace bl;
    bl::bedrock_level level;
    EXPECT_TRUE(level.open("./sample"));
    // auto *ch = level.get_chunk({-1, -1, 2});
    auto cp = chunk_pos{-1, -1, 2};
    auto key = chunk_key{chunk_key::SubChunkTerrain, cp, 3}.to_raw();
    std::string data;
    level.db()->Get(leveldb::ReadOptions(), key, &data);

    utils::write_file("a.subchunk", data.data(), data.size());

    // sub_chunk c;
    // c.load(reinterpret_cast<uint8_t *>(data.data()), data.size());
}

TEST(BedrockLevel, ReadChunk) {
    using namespace bl;
    bl::bedrock_level level;
    EXPECT_TRUE(level.open("./sample"));
    auto *ch = level.get_chunk({6, 0, 2});
    EXPECT_TRUE(ch);
    if (ch) {
        for (int i = 0; i < 64; i++) {
            auto block = ch->get_block(0, i, 0);
            std::cout << block.name << std::endl;
        }
    } else {
        BL_LOGGER("Can not find chunk");
    }
}

TEST(BedrockLevel, ReadBlock) {
    using namespace bl;
    bl::bedrock_level level;
    EXPECT_TRUE(level.open("./sample"));
    for (int y = 63; y < 70; y++) {
        for (int x = -245; x < -237; x++) {
            for (int z = 719; z < 727; z++) {
                auto b = level.get_block(block_pos(x, y, z), 0);
                printf("%s ", b.name.c_str());
            }
            printf("\n");
        }
        printf("======================================\n");

    }
}