//
// Created by Alberto Elorza Rubio on 26/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SAMPLECOMMANDPROP_H
#define HETEROGENEOUS_SOLIDS_SAMPLECOMMANDPROP_H

#include "../Command.h"

namespace hs {

    template <size_t i>
    class SampleCommandProp: public Command, public MergeCommand<SampleCommandProp<i>> {
    public:
        SampleCommandProp();

        const std::string& getDescription() override;
        void execute() override;
        void undo() override;

        bool merge(SampleCommandProp<i>& other) override;
    private:
        std::string description;

        static int count;

        int prevVal;
        int newVal;
    };

    template<size_t i>
    int SampleCommandProp<i>::count = 0;

    template<size_t i>
    SampleCommandProp<i>::SampleCommandProp() : prevVal(count), newVal(count+1), description() {

    }

    template<size_t i>
    void SampleCommandProp<i>::undo() {
        count = prevVal;
    }

    template<size_t i>
    void SampleCommandProp<i>::execute() {
        count = newVal;
    }

    template<size_t i>
    const std::string& SampleCommandProp<i>::getDescription() {
        description = "Prop: " + std::to_string(i) + ": " + std::to_string(prevVal) + " -> " + std::to_string(newVal);
        return description;
    }

    template<size_t i>
    bool SampleCommandProp<i>::merge(SampleCommandProp<i>& other) {
        newVal = other.newVal;
        return true;
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_SAMPLECOMMANDPROP_H
