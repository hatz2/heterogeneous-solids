//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_TRIMMEDCELL_H
#define HETEROGENEOUS_SOLIDS_TRIMMEDCELL_H

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "IsoCurve.h"
#include "IsoSurface.h"
#include "../machining/MachiningOperation.h"
#include "TrimmingNode.h"

namespace hs {

    class Cell;

    class TrimmedCell: public SceneNode, private Observer<> {
    public:
        TrimmedCell(
            const std::array<glm::vec3, 64>& coefs,
            Cell& mainCell,
            size_t index,
            std::optional<std::reference_wrapper<TrimmedCell>> parentTrimmedCell = std::nullopt,
            std::shared_ptr<TrimmingNode> machiningNode = nullptr
        );
        TrimmedCell(const TrimmedCell&) = delete;
        ~TrimmedCell() override;


        [[nodiscard]] Cell& getMainCell() const;
        [[nodiscard]] std::optional<std::reference_wrapper<TrimmedCell>> getParentTrimmedCell() const;

        [[nodiscard]] std::shared_ptr<TrimmingNode> getCanonicalNode() const;
        [[nodiscard]] std::shared_ptr<TrimmingNode> getActiveNode() const;
        [[nodiscard]] bool usingCanonicalNode() const;
        void resetActiveNode();
        void setActiveNode(std::shared_ptr<TrimmingNode> node);

        glm::vec3 evaluate(glm::vec3 coordinates);
        std::vector<glm::vec3> evaluate(const std::vector<glm::vec3>& points);

        PointAndTangentsST evaluatePointsAndTangents(PointAndTangentsST ptAndTgs);
        std::vector<PointAndTangentsST> evaluatePointsAndTangents(const std::vector<PointAndTangentsST>& ptAndTgsVec);

        void needRecalculation(bool U, bool R);

        [[nodiscard]] const std::array<glm::vec3, 64>& getTrimmedCoefs() const;

        std::vector<std::unique_ptr<TrimmedCell>>& getSubTrimmedCells();

        [[nodiscard]] SceneNodeState& getState() override;
        [[nodiscard]] const char* getIcon() const override;

        void visitNode(NodeVisitor& visitor) override;

        Decorator<void, RenderContext&>& getRenderer() override;

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getParent() const override;
        [[nodiscard]] size_t getIndexInParent() const override;

        [[nodiscard]] size_t childCount() const override;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getChild(size_t index) const override;

        void reserve(size_t cellsCount);
    private:
        std::array<glm::vec3, 64> trimmedCoefs;
        Cell& mainCell;
        std::optional<std::reference_wrapper<TrimmedCell>> parentTrimmedCell;
        size_t indexInParent;
        std::vector<std::unique_ptr<TrimmedCell>> subTrimmedCells;
        size_t subTrimmedCellsCount;

        std::vector<std::unique_ptr<IsoCurve>> isoCurves;
        std::vector<std::unique_ptr<IsoSurface>> isoSurfaces;

        std::shared_ptr<TrimmingNode> canonicalNode;
        std::shared_ptr<TrimmingNode> activeNode;

        bool needRecalcSubCells;

        DecoratorStack<void, RenderContext&> renderDecorator;

        void updateObserver() override;

        void renderTrimmedCell(RenderContext& renderContext);

        void setTrimmedCoefs(const std::array<glm::vec3, 64>& trimmedCoefs);
        void setCanonicalNode(std::shared_ptr<TrimmingNode> node);
    };

} // hs

#include "../Cell.h"

#endif //HETEROGENEOUS_SOLIDS_TRIMMEDCELL_H
