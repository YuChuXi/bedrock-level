//
// Created by xhy on 2023/6/18.
//

#ifndef BEDROCK_LEVEL_COLOR_H
#define BEDROCK_LEVEL_COLOR_H
#include <string>

#include "data_3d.h"
namespace bl {
    struct color {
        uint8_t r{255};
        uint8_t g{255};
        uint8_t b{255};
    };

    //    std::array<color, biome::LEN> biome_color_palette();
    [[maybe_unused]] color get_biome_color(biome b);

    bool init_biome_color_palette_from_file(const std::string& filename);

    [[maybe_unused]] void export_image(const std::vector<std::vector<color>>& c, int ppi,
                                       const std::string& name);

}  // namespace bl

#endif  // BEDROCK_LEVEL_COLOR_H
