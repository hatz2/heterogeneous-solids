//
// Created by Alberto Elorza Rubio on 08/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_PROPS_H
#define HETEROGENEOUS_SOLIDS_PROPS_H

#include <string>

namespace hs {

    class DescriptionProp {
    public:
        [[nodiscard]] virtual const std::string& getDescription() const = 0;
        virtual void setDescription(std::string description) = 0;

        [[nodiscard]] virtual std::string getDefaultDescription() = 0;
        virtual void setDefaultDescription(std::string defaultDescription) = 0;

        [[nodiscard]] virtual const std::string& getDescriptionOrDefault() const = 0;

        virtual ~DescriptionProp() = default;
    };

    class VisibilityProp {
    public:
        [[nodiscard]] virtual bool isVisible() const = 0;
        virtual void setVisible(bool visible) = 0;

        virtual ~VisibilityProp() = default;
    };

    class DescriptionPropImpl: public DescriptionProp {
    public:
        DescriptionPropImpl() = default;
        explicit DescriptionPropImpl(std::string description);

        [[nodiscard]] const std::string& getDescription() const override;
        void setDescription(std::string description) override;

        [[nodiscard]] std::string getDefaultDescription() override;
        void setDefaultDescription(std::string defaultDescription) override;

        [[nodiscard]] const std::string& getDescriptionOrDefault() const override;
    private:
        std::string description;
        std::string defaultDescription;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_PROPS_H
