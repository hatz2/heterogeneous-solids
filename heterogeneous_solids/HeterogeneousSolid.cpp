//
// Created by Alberto Elorza Rubio on 28/11/2023.
//

#include "HeterogeneousSolid.h"
#include "../utils/vector.h"

#include <utility>

namespace hs {
    HeterogeneousSolid::HeterogeneousSolid() :
        sharedData(std::make_shared<HSSharedData>()),
        state("Heterogeneous Solid"),
        material(std::make_shared<HeterogeneousMaterial>(MaterialType::Composite)),

        parentObject(std::nullopt),
        indexInParent(0),

        renderDecorator([this](RenderContext& renderContext) { renderHeterogeneousSolid(renderContext); })
    {

    }

    HeterogeneousSolid::HeterogeneousSolid(std::string name) : HeterogeneousSolid() {
        state.setDescription(std::move(name));
    }

    void HeterogeneousSolid::needRecalculation(bool U, bool R) {
        for (auto& cell : cells) cell->needRecalculation(U, R);
    }

    void HeterogeneousSolid::addCell(Cell* cell) {
        std::array<ShapeCoef*, 64> gridShapeCoefs{};
        int idx = 0;
        for (auto& coef : cell->getCellCoefGroup()->getCoefs()) {
            auto& positionCoef = coef->getPositionCoef();
            auto& shapePosition = positionCoef.getShapePosition();
            for (const std::unique_ptr<ShapeCoef>& shapeCoef : shapeCoefs) {
                if (glm::all(glm::epsilonEqual(shapeCoef->getPosition(), shapePosition, glm::epsilon<float>()))) {
                    if (shapeCoef->getType() != coef->getPositionCoef().getShapeCoefType()) {
                        spdlog::warn("Shared ShapeCoef does not match expected grid type");
                    }
                    coef->setAttachedShapeCoef(shapeCoef.get());
                    break;
                }
            }

            if (!coef->getAttachedShapeCoef()) {
                auto shapeCoef = std::make_unique<ShapeCoef>(shapePosition, coef->getPositionCoef().getGridIndex());
                shapeCoef->getTransform().setParent(transform);
                coef->setAttachedShapeCoef(shapeCoef.get());
                shapeCoefs.push_back(std::move(shapeCoef));
            }

            gridShapeCoefs[idx++] = *coef->getAttachedShapeCoef(); // Here must have a coefficient already assigned
        }
        for (unsigned int idx = 0; idx < 64; idx++) {
            gridShapeCoefs[idx]->setCornerCoef(gridShapeCoefs[ShapeCoef::cornerIndexFromGridIndex(idx)]);
        }
        cells.insert(cell);
    }

    void HeterogeneousSolid::removeCell(Cell* cell) {
        for (auto& coef : cell->getCellCoefGroup()->getCoefs()) coef->detachShapeCoef();
        cells.erase(cell);
    }

    std::set<Cell*>& HeterogeneousSolid::getCells() {
        return cells;
    }

    std::shared_ptr<HSSharedData> HeterogeneousSolid::getSharedData() {
        return sharedData;
    }

    SceneNodeState& HeterogeneousSolid::getState() {
        return state;
    }

    const char* HeterogeneousSolid::getIcon() const {
        return ICON_MD_GRID_3X3;
    }

    std::shared_ptr<HeterogeneousMaterial> HeterogeneousSolid::getMaterial() const {
        return material;
    }

    void HeterogeneousSolid::setMaterial(std::shared_ptr<HeterogeneousMaterial> material) {
        HeterogeneousSolid::material = std::move(material);
    }

    void HeterogeneousSolid::visitNode(NodeVisitor& visitor) {
        visitor.doHeterogeneousSolid(*this);
    }

    void HeterogeneousSolid::renderHeterogeneousSolid(RenderContext& renderContext) {
        if (!state.isVisible()) return;

        renderContext.setModelMatrix(transform);

        switch (renderContext.getRenderMode()) {
            case RenderMode::VertexSelectColor:
            case RenderMode::Vertices:
                for (const auto& shapeCoef : shapeCoefs) shapeCoef->setAlreadyRendered(false);
                for (auto& cell : cells) cell->getRenderer()(renderContext);
                for (const auto& shapeCoef : shapeCoefs) shapeCoef->setAlreadyRendered(false);
                break;
            case RenderMode::Surfaces:
                material->apply(renderContext);
            default:
                for (auto& cell : cells) cell->getRenderer()(renderContext);
                break;
        }
    }

    Decorator<void, RenderContext&>& HeterogeneousSolid::getRenderer() {
        return renderDecorator;
    }

    std::optional<std::reference_wrapper<SceneNode>> HeterogeneousSolid::getParent() const {
        return parentObject;
    }

    size_t HeterogeneousSolid::getIndexInParent() const {
        return indexInParent;
    }

    bool HeterogeneousSolid::acceptsParent(SceneNode& parent) const {
        return true;
    }

    bool HeterogeneousSolid::bindParent(SceneNode& parent, size_t index) {
        indexInParent = index;

        if (!parentObject || &parentObject->get() != &parent) {
            parentObject = parent;

            if (auto transformParent = parent.getImmediateTransform()) transform.setParent(transformParent->get());
            else transform.removeParent();
        }
        return true;
    }

    bool HeterogeneousSolid::unbindParent() {
        parentObject = std::nullopt;
        indexInParent = 0;
        transform.removeParent();
        return true;
    }

    size_t HeterogeneousSolid::childCount() const {
        return children.size();
    }

    std::optional<std::reference_wrapper<SceneNode>> HeterogeneousSolid::getChild(size_t index) const {
        return ext::tryGet(children, index);
    }

    std::optional<size_t> HeterogeneousSolid::addChild(std::unique_ptr<SceneNode>& child) {
        size_t index = children.size();
        if (child->bindParent(*this, index)) {
            children.push_back(std::move(child));
            return index;
        }
        return std::nullopt;
    }

    std::optional<size_t> HeterogeneousSolid::moveChild(SceneNode& child) {
        if (!child.acceptsParent(*this)) return std::nullopt;

        if (auto object = child.getObjectOwnership()) {
            auto index = addChild(object.value());
            if (!index) spdlog::warn("Object finally did not accept parent");
            return index;
        } else spdlog::warn("Got no object ownership");

        return std::nullopt;
    }

    std::optional<std::unique_ptr<SceneNode>> HeterogeneousSolid::removeChild(size_t index) {
        auto removed = ext::tryRemove(children, index);
        if (removed) {
            int idx = 0;
            for (auto& child : children)
                child->bindParent(*this, idx++);
        }
        return removed;
    }

    std::optional<std::reference_wrapper<Transform>> HeterogeneousSolid::getImmediateTransform() {
        return transform;
    }

    std::optional<std::reference_wrapper<Transform>> HeterogeneousSolid::getOwnedTransform() {
        return transform;
    }
} // hs