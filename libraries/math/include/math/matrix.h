#include <concepts>
#include <array>

#include "types/deep_concepts.h"

template<deep::concepts::Numeric Data, const std::size_t Rows, const std::size_t Columns>
class Matrix
{
  public:
    constexpr explicit Matrix(const std::array<Data, Rows * Columns> &data) noexcept
    : data_(data) {};

    static constexpr auto size() {
        return Rows * Columns;
    };

    [[nodiscard]] constexpr auto data() const noexcept
    {
        return data_.data();
    }

  private:
    std::array<Data, Rows * Columns> data_;
};

template<deep::concepts::Numeric Data>
using Vector2D = Matrix<Data, 1, 2>;

template<deep::concepts::Numeric Data>
using Vector3D = Matrix<Data, 1, 3>;
