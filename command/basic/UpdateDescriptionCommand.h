//
// Created by Alberto Elorza Rubio on 07/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_UPDATEDESCRIPTIONCOMMAND_H
#define HETEROGENEOUS_SOLIDS_UPDATEDESCRIPTIONCOMMAND_H

#include "../Command.h"
#include "../../utils/props.h"

namespace hs {

    class UpdateDescriptionCommand: public Command, public MergeCommand<UpdateDescriptionCommand> {
    public:
        UpdateDescriptionCommand(std::string newDescription, DescriptionProp& descriptionProp);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;

        bool doDiscard() override;

        bool merge(UpdateDescriptionCommand& other) override;
    private:
        static const std::string description;
        DescriptionProp& descriptionProp;
        std::string before;
        std::string after;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_UPDATEDESCRIPTIONCOMMAND_H
