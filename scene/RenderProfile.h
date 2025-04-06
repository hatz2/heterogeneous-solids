//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_RENDERPROFILE_H
#define HETEROGENEOUS_SOLIDS_RENDERPROFILE_H

#include <glm/vec4.hpp>

namespace hs {

    class RenderProfile {
    private:
        glm::vec4 backgroundColor;

        bool showSurfaces;
        bool detailedSurfaces;

        bool showMainLines;
        glm::vec4 mainLinesColor;
        float mainLinesThickness;

        bool showDetailedLines;
        glm::vec4 detailedLinesColor;
        float detailedLinesThickness;

        bool showNormalField;
        glm::vec4 normalFieldColor;
        float normalFieldThickness;

        bool showVertices;
        glm::vec4 vertexColor;
        float vertexRadius;

        bool highlightSelection;
        glm::vec4 selectionTint;
        bool selectionDrawDepth;

        bool showGridGizmo;
        bool showLightsGizmo;

        bool antialiasing;

        bool usePbr;
    public:
        RenderProfile();

        [[nodiscard]] const glm::vec4& getBackgroundColor() const;
        void setBackgroundColor(const glm::vec4& backgroundColor);

        [[nodiscard]] bool isShowSurfaces() const;
        void setShowSurfaces(bool showSurfaces);

        [[nodiscard]] bool isDetailedSurfaces() const;
        void setDetailedSurfaces(bool detailedSurfaces);

        [[nodiscard]] bool isShowMainLines() const;
        void setShowMainLines(bool showMainLines);

        [[nodiscard]] const glm::vec4& getMainLinesColor() const;
        void setMainLinesColor(const glm::vec4& mainLinesColor);

        [[nodiscard]] float getMainLinesThickness() const;
        void setMainLinesThickness(float mainLinesThickness);

        [[nodiscard]] bool isShowDetailedLines() const;
        void setShowDetailedLines(bool showDetailedLines);

        [[nodiscard]] const glm::vec4& getDetailedLinesColor() const;
        void setDetailedLinesColor(const glm::vec4& detailedLinesColor);

        [[nodiscard]] float getDetailedLinesThickness() const;
        void setDetailedLinesThickness(float detailedLinesThickness);

        [[nodiscard]] bool isShowNormalField() const;
        void setShowNormalField(bool showNormalField);

        [[nodiscard]] const glm::vec4& getNormalFieldColor() const;
        void setNormalFieldColor(const glm::vec4& normalFieldColor);

        [[nodiscard]] float getNormalFieldThickness() const;
        void setNormalFieldThickness(float normalFieldThickness);

        [[nodiscard]] bool isHighlightSelection() const;
        void setHighlightSelection(bool highlightSelection);

        [[nodiscard]] bool isShowVertices() const;
        void setShowVertices(bool showVertices);

        [[nodiscard]] const glm::vec4& getVertexColor() const;
        void setVertexColor(const glm::vec4& vertexColor);

        [[nodiscard]] float getVertexRadius() const;
        void setVertexRadius(float vertexRadius);

        [[nodiscard]] const glm::vec4& getSelectionTint() const;
        void setSelectionTint(const glm::vec4& selectionTint);

        [[nodiscard]] bool isSelectionDrawDepth() const;
        void setSelectionDrawDepth(bool selectionDrawDepth);

        [[nodiscard]] bool isShowGridGizmo() const;
        void setShowGridGizmo(bool showGridGizmo);

        [[nodiscard]] bool isShowLightsGizmo() const;
        void setShowLightsGizmo(bool showLightsGizmo);

        [[nodiscard]] bool isAntialiasing() const;
        void setAntialiasing(bool antialiasing);

        [[nodiscard]] bool isUsePbr() const;
        void setUsePbr(bool usePbr);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RENDERPROFILE_H
