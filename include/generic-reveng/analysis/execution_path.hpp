#pragma once

#include <forward_list>

#include <generic-reveng/analysis/execution_update.hpp>

namespace grev
{
    class execution_path : std::unordered_map<z3::expression, z3::expression const*>
    {
        const_iterator start_jump_;

        execution_state current_state_; // TODO Collect updates
        iterator current_jump_;

        z3::expression condition_;

    public:

        explicit execution_path(std::uint32_t start_address);
        ~execution_path();

        execution_path(execution_path const& other);
        execution_path(execution_path&& other) noexcept;

        execution_path& operator=(execution_path other) noexcept;

        std::forward_list<execution_path> proceed(execution_update update, execution_state const& memory_patch);

        std::optional<z3::expression> current_jump() const;

        // >>-----
        std::vector<std::uint32_t> addresses() const; // Testing seam TODO
        // -----<<

    private:

        void step(z3::expression jump);
    };
}
