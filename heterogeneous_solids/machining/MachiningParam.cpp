//
// Created by Alberto Elorza Rubio on 16/12/2023.
//

#include "MachiningParam.h"
#include "../exceptions/MachiningParamBoundsError.h"

namespace hs {
    MachiningParam::MachiningParam(float value, const MachiningParamFloat& param) : value(value),
        std::variant<MachiningParamFloat, MachiningParamInt, MachiningParamEnum>(param)
    {
        if (value < param.min || value > param.max)
            throw MachiningParamBoundsError(value, param.min, param.max);
    }

    MachiningParam::MachiningParam(int value, const MachiningParamInt& param) : value((float)value),
        std::variant<MachiningParamFloat, MachiningParamInt, MachiningParamEnum>(param)
    {
        if (value < param.min || value > param.max)
            throw MachiningParamBoundsError(value, param.min, param.max);
    }

    MachiningParam::MachiningParam(int value, const MachiningParamEnum& param) : value((float)value),
        std::variant<MachiningParamFloat, MachiningParamInt, MachiningParamEnum>(param)
    {
        if (value < 0 || value >= param.options.size())
            throw MachiningParamBoundsError(value, 0, param.options.size() - 1);
    }

    float MachiningParam::getValue() const {
        return value;
    }

    void MachiningParam::set(float value) {
        switch (index()) {
            case 0: {
                auto& item = std::get<0>(*this);
                if (value < item.min || value > item.max)
                    throw MachiningParamBoundsError(value, item.min, item.max);
                MachiningParam::value = value;
                break;
            }
            case 1: {
                auto& item = std::get<1>(*this);
                int intValue = (int)value;
                if (intValue < item.min || intValue > item.max)
                    throw MachiningParamBoundsError(intValue, item.min, item.max);
                MachiningParam::value = value;
                break;
            }
            case 2:{
                auto& item = std::get<2>(*this);
                int intValue = (int)value;
                if (intValue < 0 || intValue >= item.options.size())
                    throw MachiningParamBoundsError(intValue, 0, item.options.size()-1);
                MachiningParam::value = value;
                break;
            }
        }
    }

    MachiningParam::operator float() const {
        return value;
    }

    MachiningParam::operator int() const {
        return (int)value;
    }
} // hs