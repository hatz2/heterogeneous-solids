//
// Created by Alberto Elorza Rubio on 15/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_TRIMMINGNODE_H
#define HETEROGENEOUS_SOLIDS_TRIMMINGNODE_H

#include <list>
#include "../machining/MachiningOperation.h"
#include "../../scene/objects/SceneNodeState.h"
#include "../../utils/ItemSet.h"
#include "../../utils/Observer.h"

namespace hs {

    class TrimmingNode: public Subject<> {
    public:
        TrimmingNode();
        ~TrimmingNode() override = default;
        TrimmingNode(const TrimmingNode&);
        TrimmingNode& operator=(TrimmingNode&) = delete;

        [[nodiscard]] std::shared_ptr<TrimmingNode> getOrCreate(size_t index);
        void clear();
        [[nodiscard]] MachiningOperation& getOperation();
        [[nodiscard]] MutableSceneNodeState& getState();

        void swapContentWith(TrimmingNode& other);

        void notifyRefresh();
    private:
        static const char* DescriptionPrefix;

        std::unique_ptr<MutableSceneNodeState> state;
        std::unique_ptr<MachiningOperation> operation;
        std::vector<std::shared_ptr<TrimmingNode>> children;

        friend class TrimmedCell;
    };

    using MacroSet = ItemSet<TrimmingNode>;

} // hs

#endif //HETEROGENEOUS_SOLIDS_TRIMMINGNODE_H
