//
// Created by Alberto Elorza Rubio on 23/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_DECORATOR_H
#define HETEROGENEOUS_SOLIDS_DECORATOR_H

#include "memory"
#include <functional>
#include <algorithm>

namespace hs {

    template <typename R, typename ...Args>
    class Decorator {
    public:
        virtual void reset() = 0;

        virtual void decorate(const std::function<R(std::function<R(Args...)>&, Args...)>& fn) = 0;

        virtual void pop() = 0;

        virtual void popMany(size_t count) = 0;

        virtual R operator()(Args... args) = 0;

        virtual ~Decorator() = default;
    };

    template <typename R, typename ...Args>
    class NullDecorator: public Decorator<R, Args...> {
    public:
        NullDecorator() = default;
        NullDecorator(const NullDecorator& other) = default;

        void reset() override { }

        void decorate(const std::function<R(std::function<R(Args...)>&, Args...)>& fn) override { }

        void pop() override { }

        void popMany(size_t count) override { }

        R operator()(Args... args) override { }
    };

    template <typename R, typename ...Args>
    class StaticDecorator: public Decorator<R, Args...> {
    public:
        StaticDecorator() = delete;
        explicit StaticDecorator(std::function<R(Args...)> function) : function(function) {

        }
        StaticDecorator(const StaticDecorator& other) : function(other.function) {

        }

        void reset() override { }

        void decorate(const std::function<R(std::function<R(Args...)>&, Args...)>& fn) override { }

        void pop() override { }

        void popMany(size_t count) override { }

        R operator()(Args... args) override {
            return function(std::forward<Args>(args)...);
        }
    private:
        std::function<R(Args...)> function;
    };

    template <typename R, typename ...Args>
    class DecoratorStack: public Decorator<R, Args...> {
    public:
        DecoratorStack() = delete;
        explicit DecoratorStack(std::function<R(Args...)> function) : stack({ function }) {

        }
        DecoratorStack(const DecoratorStack& other) : stack(other.stack) {

        }

        void reset() override {
            stack.resize(1);
        }

        void decorate(const std::function<R(std::function<R(Args...)>&, Args...)>& fn) override {
            stack.push_back(std::bind(fn, stack.back(), std::placeholders::_1));
        }

        void pop() override {
            if (stack.size() > 1) stack.pop_back();
        }

        void popMany(size_t count) override {
            stack.resize(std::max((size_t)1, stack.size() - count));
        }

        R operator()(Args... args) override {
            return stack.back()(std::forward<Args>(args)...);
        }
    private:
        std::vector<std::function<R(Args...)>> stack;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_DECORATOR_H
