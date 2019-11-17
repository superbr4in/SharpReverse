#pragma once

#include <string_view>

namespace grev
{
    struct pe_optional_header
    {
        std::uint32_t relative_start_address;
        std::uint64_t base_address;
        std::uint32_t relative_import_address;

        static pe_optional_header inspect_32(std::u8string_view* data_view);
        static pe_optional_header inspect_64(std::u8string_view* data_view);
    };
}
