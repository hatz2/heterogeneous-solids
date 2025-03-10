//
// Created by Alberto Elorza Rubio on 01/02/2024.
//

#include "Selector.h"

#include "../heterogeneous_solids/HeterogeneousSolid.h"
#include "../command/basic/AddObjectCommand.h"
#include "../command/basic/RemoveObjectCommand.h"
#include "../command/basic/CommandGroup.h"

namespace hs {
    Selector::Selector(Scene& scene, MaterialEditor& materialEditor, CommandHistory& commandHistory) :
        scene(scene), materialEditor(materialEditor), selected(scene.getRoot())
    {
        commandHistory.getExecutionSubject().attachObserver(this);
        scene.setSelectedObject(selected);
    }

    void Selector::select(SceneNode& sceneNode) {
        sceneNode.visitNode(*this);
    }

    SceneNode& Selector::getSelectedObject() const {
        return selected;
    }

    std::optional<std::reference_wrapper<GroupNode>> Selector::getGroupNode() const {
        return groupNode;
    }

    std::optional<std::reference_wrapper<HeterogeneousSolid>> Selector::getHeterogeneousSolid() const {
        return heterogeneousSolid;
    }

    std::optional<std::reference_wrapper<Cell>> Selector::getCell() const {
        return cell;
    }

    std::optional<std::reference_wrapper<TrimmedCell>> Selector::getTrimmedCell() const {
        return trimmedCell;
    }

    std::optional<std::reference_wrapper<CellCoef>> Selector::getCellCoef() const {
        return cellCoef;
    }

    void Selector::doSceneNode(SceneNode& object) {
        resetOptionals();
        selected = object;
        scene.setSelectedObject(selected);
    }

    void Selector::doGroupNode(GroupNode& object) {
        resetOptionals();
        selected = object;
        groupNode = object;
        scene.setSelectedObject(selected);
    }

    void Selector::doHeterogeneousSolid(HeterogeneousSolid& object) {
        resetOptionals();
        selected = object;
        heterogeneousSolid = object;
        if (object.getCells().size() == 1) {
            cell = **object.getCells().begin();
            if (cell.value().get().getTrimmedCells().size() == 1)
                trimmedCell = **cell.value().get().getTrimmedCells().begin();
        }
        scene.setSelectedObject(selected);
        materialEditor.setSelected(object.getMaterial());
    }

    void Selector::doCell(Cell& object) {
        resetOptionals();
        selected = object;
        heterogeneousSolid = object.getHeterogeneousSolidParent();
        cell = object;
        if (object.getTrimmedCells().size() == 1)
            trimmedCell = **object.getTrimmedCells().begin();
        scene.setSelectedObject(selected);
        if (heterogeneousSolid)
            materialEditor.setSelected(heterogeneousSolid->get().getMaterial());
    }

    void Selector::doTrimmedCell(TrimmedCell& object) {
        resetOptionals();
        selected = object;
        heterogeneousSolid = object.getMainCell().getHeterogeneousSolidParent();
        cell = object.getMainCell();
        trimmedCell = object;
        scene.setSelectedObject(selected);
    }

    void Selector::doCellCoef(CellCoef& object) {
        doCell(object.getCell());
        selected = object;
        Selector::cellCoef = object;
        scene.setSelectedObject(selected);
    }

    void Selector::doCellCoefGroup(CellCoefGroup& object) {
        doCell(object.getCell());
        selected = object;
        scene.setSelectedObject(selected);
    }

    void Selector::updateObserver(CommandHistoryEvent event, const Command& command) {
        if (&selected.get() == &scene.getRoot()) return;
        std::reference_wrapper<SceneNode> object = selected;
        std::optional<std::reference_wrapper<SceneNode>> parent = object.get().getParent();
        std::set<SceneNode*> visited;
        visited.insert(&object.get());
        // check if there is parent and we are not in a cycle

        bool ok = false;

        while (parent && visited.find(&parent->get()) == visited.end()) {
            // check if child is not one of the parent children
            if (
                auto child = parent->get().getChild(object.get().getIndexInParent());
                !child || &child->get() != &object.get()
            ) selected = *parent;

            // check if the parent is the root
            if (&parent.value().get() == &scene.getRoot()) {
                ok = true;
                break;
            }

            // repeat with the parent's parent
            object = parent.value();
            visited.insert(&object.get());
            parent = parent->get().getParent();
        }
        if (!ok) selected = scene.getRoot();
        scene.setSelectedObject(selected);
        select(selected);
    }

    void Selector::resetOptionals() {
        groupNode = std::nullopt;
        heterogeneousSolid = std::nullopt;
        cell = std::nullopt;
        trimmedCell = std::nullopt;
        cellCoef = std::nullopt;
    }
} // hs