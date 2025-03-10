//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_SELECTOR_H
#define HETEROGENEOUS_SOLIDS_SELECTOR_H

#include "../utils/NodeVisitor.h"
#include "../scene/Scene.h"
#include "MaterialEditor.h"
#include "../command/CommandHistory.h"

namespace hs {

    class Selector: private NodeVisitor, private Observer<CommandHistoryEvent, const Command&> {
    public:
        Selector(Scene& scene, MaterialEditor& materialEditor, CommandHistory& commandHistory);
        Selector(const Selector&) = delete;

        void select(SceneNode& sceneNode);

        [[nodiscard]] SceneNode& getSelectedObject() const;
        [[nodiscard]] std::optional<std::reference_wrapper<GroupNode>> getGroupNode() const;
        [[nodiscard]] std::optional<std::reference_wrapper<HeterogeneousSolid>> getHeterogeneousSolid() const;
        [[nodiscard]] std::optional<std::reference_wrapper<Cell>> getCell() const;
        [[nodiscard]] std::optional<std::reference_wrapper<TrimmedCell>> getTrimmedCell() const;
        [[nodiscard]] std::optional<std::reference_wrapper<CellCoef>> getCellCoef() const;
    private:
        void doSceneNode(SceneNode& object) override;
        void doGroupNode(GroupNode& object) override;
        void doHeterogeneousSolid(HeterogeneousSolid& object) override;
        void doCell(Cell& object) override;
        void doTrimmedCell(TrimmedCell& object) override;
        void doCellCoef(hs::CellCoef& object) override;
        void doCellCoefGroup(hs::CellCoefGroup& object) override;

        void updateObserver(CommandHistoryEvent, const Command&) override;

        void resetOptionals();

        Scene& scene;
        MaterialEditor& materialEditor;
        std::reference_wrapper<SceneNode> selected;
        std::optional<std::reference_wrapper<GroupNode>> groupNode;
        std::optional<std::reference_wrapper<HeterogeneousSolid>> heterogeneousSolid;
        std::optional<std::reference_wrapper<Cell>> cell;
        std::optional<std::reference_wrapper<CellCoef>> cellCoef;
        std::optional<std::reference_wrapper<TrimmedCell>> trimmedCell;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SELECTOR_H
