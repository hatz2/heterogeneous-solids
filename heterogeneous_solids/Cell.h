//
// Created by Alberto Elorza Rubio on 02/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CELL_H
#define HETEROGENEOUS_SOLIDS_CELL_H

#include <string>
#include <vector>
#include <array>
#include <set>
#include "coefs/ShapeCoef.h"
#include "trimmed_cells/TrimmedCell.h"
#include "HSSharedData.h"
#include "coefs/CellCoefGroup.h"

namespace hs {

    class HeterogeneousSolid;

    class Cell: public SceneNode {
    public:
        explicit Cell(std::array<glm::vec3, 64> shapePositions);
        Cell();
        Cell(const Cell&) = delete;
        ~Cell() override;

        glm::vec3 evaluate(glm::vec3 coordinates);
        std::vector<glm::vec3> evaluate(const std::vector<glm::vec3>& points);

        PointAndTangentsUVW evaluatePointAndTangents(glm::vec3 coordinates);
        std::vector<PointAndTangentsUVW> evaluatePointAndTangents(const std::vector<glm::vec3>& coordinates);

        void needRecalculation(bool U, bool R);

        [[nodiscard]] std::set<TrimmedCell*>& getTrimmedCells();
        [[nodiscard]] CellCoefGroup*& getCellCoefGroup();

        [[nodiscard]] std::optional<std::reference_wrapper<HeterogeneousSolid>> getHeterogeneousSolidParent() const;

        [[nodiscard]] glm::vec3 getPerlinPeriod() const;
        void setPerlinPeriod(glm::vec3 perlinPeriod);

        [[nodiscard]] HSSharedData& getSharedData() const;

        [[nodiscard]] SceneNodeState& getState() override;
        [[nodiscard]] const char* getIcon() const override;

        void visitNode(NodeVisitor &visitor) override;

        Decorator<void, RenderContext&>& getRenderer() override;

        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getParent() const override;
        [[nodiscard]] size_t getIndexInParent() const override;
        [[nodiscard]] bool acceptsParent(SceneNode &parent) const override;
        bool bindParent(SceneNode& parent, size_t index) override;
        bool unbindParent() override;

        [[nodiscard]] size_t childCount() const override;
        [[nodiscard]] std::optional<std::reference_wrapper<SceneNode>> getChild(size_t index) const override;
    private:
        MutableSceneNodeState state;

        std::shared_ptr<HSSharedData> sharedData;

        std::array<glm::vec3, 64> coefPositions;
        std::array<glm::vec3, 64> p;
        std::array<float, 64> a0;

        glm::ivec3 perlinPeriod;

        CellCoefGroup* cellCoefGroup;
        std::set<TrimmedCell*> trimmedCells;
        std::vector<std::unique_ptr<SceneNode>> children;
        std::optional<std::reference_wrapper<HeterogeneousSolid>> parentSolid;
        size_t indexInParent;

        DecoratorStack<void, RenderContext&> renderDecorator;

        void renderCell(RenderContext& renderContext);
    };
} // hs

#include "HeterogeneousSolid.h"

#endif //HETEROGENEOUS_SOLIDS_CELL_H
