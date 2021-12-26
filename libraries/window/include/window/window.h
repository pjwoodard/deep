#pragma once

class Window {
  public:
    template<typename T>
    Window(T t, const int32_t width, const int32_t height) noexcept
    : self_{std::make_unique<Model<T>>(std::move(t))} { }

    void display() const {
        self_->display();
    }

  private:
    struct Concept {
            virtual ~Concept() = default;
            virtual void display() const = 0;

            Concept(const Concept &c) = delete;
            Concept(Concept &&c) = delete;
            Concept & operator=(const Concept &c) = delete;
            Concept & operator=(Concept &&c) = delete;
        };

    template<typename T>
    struct Model : Concept {
        explicit Model(T s) noexcept : self_{std::move(s)} {}
        void display() const override { self_.display(); }
      private:
        T self_;
    };


    std::unique_ptr<const concept_t> self_{};
};
