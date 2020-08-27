#pragma once

#include <exception>
#include <memory>
#include <optional>
#include <string>

namespace lf::helpers {

// struct Exception : public std::exception {
//     Exception(std::string file, unsigned line) : file{std::move(file)}, line{line} {}

//     Exception(std::string file, unsigned line, std::unique_ptr<Exception>)
//         : file{std::move(file)}, line{line}, child{std::move(child)}
//     {
//     }

//     std::optional<std::unique_ptr<Exception>> child;
//     unsigned line;
//     std::string file;
// };

// struct NarrowingException

} // namespace lf::helpers
