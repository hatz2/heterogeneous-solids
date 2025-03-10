//
// Created by Alberto Elorza Rubio on 07/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_NODEVISITOR_H
#define HETEROGENEOUS_SOLIDS_NODEVISITOR_H

namespace hs {

    class SceneNode;
    class GroupNode;
    class HeterogeneousSolid;
    class Cell;
    class TrimmedCell;
    class CellCoef;
    class CellCoefGroup;

    class NodeVisitor {
    public:
        virtual void doSceneNode(SceneNode& sceneNode) { }
        virtual void doGroupNode(GroupNode& groupNode) { }
        virtual void doHeterogeneousSolid(HeterogeneousSolid& heterogeneousSolid) { }
        virtual void doCell(Cell& cell) { }
        virtual void doTrimmedCell(TrimmedCell& trimmedCell) { }
        virtual void doCellCoef(CellCoef& cellCoef) { }
        virtual void doCellCoefGroup(CellCoefGroup& cellCoefGroup) { }

        virtual ~NodeVisitor() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_NODEVISITOR_H
