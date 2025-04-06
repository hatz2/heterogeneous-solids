//
// Created by Alberto Elorza Rubio on 05/12/2023.
//

#include "RenderProfile.h"

namespace hs {
    RenderProfile::RenderProfile():
        backgroundColor(0.2),

        showSurfaces(true),
        detailedSurfaces(true),

        showMainLines(false),
        mainLinesColor(0, 0, 0, 0.2),
        mainLinesThickness(4),

        showDetailedLines(false),
        detailedLinesColor(0, 0, 0, 0.2),
        detailedLinesThickness(2),

        showNormalField(false),
        normalFieldColor(0.3, 0.3, 0.3, 0.4),
        normalFieldThickness(1),

        showVertices(false),
        vertexColor(0, 0, 1, 0.7),
        vertexRadius(1),

        highlightSelection(true),
        selectionTint(0, 1, 0, 1),
        selectionDrawDepth(false),

        showGridGizmo(false),
        showLightsGizmo(false),

        antialiasing(true),

        usePbr(true)
    {
        // TODO: Put back default parameters that have been changed
    }

    const glm::vec4& RenderProfile::getBackgroundColor() const {
        return backgroundColor;
    }

    void RenderProfile::setBackgroundColor(const glm::vec4& backgroundColor) {
        RenderProfile::backgroundColor = backgroundColor;
    }

    bool RenderProfile::isShowSurfaces() const {
        return showSurfaces;
    }

    void RenderProfile::setShowSurfaces(bool showSurfaces) {
        RenderProfile::showSurfaces = showSurfaces;
    }

    bool RenderProfile::isDetailedSurfaces() const {
        return detailedSurfaces;
    }

    void RenderProfile::setDetailedSurfaces(bool detailedSurfaces) {
        RenderProfile::detailedSurfaces = detailedSurfaces;
    }

    bool RenderProfile::isShowMainLines() const {
        return showMainLines;
    }

    void RenderProfile::setShowMainLines(bool showMainLines) {
        RenderProfile::showMainLines = showMainLines;
    }

    const glm::vec4& RenderProfile::getMainLinesColor() const {
        return mainLinesColor;
    }

    void RenderProfile::setMainLinesColor(const glm::vec4& mainLinesColor) {
        RenderProfile::mainLinesColor = mainLinesColor;
    }

    float RenderProfile::getMainLinesThickness() const {
        return mainLinesThickness;
    }

    void RenderProfile::setMainLinesThickness(float mainLinesThickness) {
        RenderProfile::mainLinesThickness = mainLinesThickness;
    }

    bool RenderProfile::isShowDetailedLines() const {
        return showDetailedLines;
    }

    void RenderProfile::setShowDetailedLines(bool showDetailedLines) {
        RenderProfile::showDetailedLines = showDetailedLines;
    }

    const glm::vec4& RenderProfile::getDetailedLinesColor() const {
        return detailedLinesColor;
    }

    void RenderProfile::setDetailedLinesColor(const glm::vec4& detailedLinesColor) {
        RenderProfile::detailedLinesColor = detailedLinesColor;
    }

    float RenderProfile::getDetailedLinesThickness() const {
        return detailedLinesThickness;
    }

    void RenderProfile::setDetailedLinesThickness(float detailedLinesThickness) {
        RenderProfile::detailedLinesThickness = detailedLinesThickness;
    }

    bool RenderProfile::isShowNormalField() const {
        return showNormalField;
    }

    void RenderProfile::setShowNormalField(bool showNormalField) {
        RenderProfile::showNormalField = showNormalField;
    }

    const glm::vec4& RenderProfile::getNormalFieldColor() const {
        return normalFieldColor;
    }

    void RenderProfile::setNormalFieldColor(const glm::vec4& normalFieldColor) {
        RenderProfile::normalFieldColor = normalFieldColor;
    }

    float RenderProfile::getNormalFieldThickness() const {
        return normalFieldThickness;
    }

    void RenderProfile::setNormalFieldThickness(float normalFieldThickness) {
        RenderProfile::normalFieldThickness = normalFieldThickness;
    }

    bool RenderProfile::isHighlightSelection() const {
        return highlightSelection;
    }

    void RenderProfile::setHighlightSelection(bool highlightSelection) {
        RenderProfile::highlightSelection = highlightSelection;
    }

    bool RenderProfile::isShowVertices() const {
        return showVertices;
    }

    void RenderProfile::setShowVertices(bool showVertices) {
        RenderProfile::showVertices = showVertices;
    }

    const glm::vec4& RenderProfile::getVertexColor() const {
        return vertexColor;
    }

    void RenderProfile::setVertexColor(const glm::vec4& vertexColor) {
        RenderProfile::vertexColor = vertexColor;
    }

    float RenderProfile::getVertexRadius() const {
        return vertexRadius;
    }

    void RenderProfile::setVertexRadius(float vertexRadius) {
        RenderProfile::vertexRadius = vertexRadius;
    }

    const glm::vec4& RenderProfile::getSelectionTint() const {
        return selectionTint;
    }

    void RenderProfile::setSelectionTint(const glm::vec4& selectionTint) {
        RenderProfile::selectionTint = selectionTint;
    }

    bool RenderProfile::isSelectionDrawDepth() const {
        return selectionDrawDepth;
    }

    void RenderProfile::setSelectionDrawDepth(bool selectionDrawDepth) {
        RenderProfile::selectionDrawDepth = selectionDrawDepth;
    }

    bool RenderProfile::isShowGridGizmo() const {
        return showGridGizmo;
    }

    void RenderProfile::setShowGridGizmo(bool showGridGizmo) {
        RenderProfile::showGridGizmo = showGridGizmo;
    }

    bool RenderProfile::isShowLightsGizmo() const {
        return showLightsGizmo;
    }

    void RenderProfile::setShowLightsGizmo(bool showLightsGizmo) {
        RenderProfile::showLightsGizmo = showLightsGizmo;
    }

    bool RenderProfile::isAntialiasing() const {
        return antialiasing;
    }

    void RenderProfile::setAntialiasing(bool antialiasing) {
        RenderProfile::antialiasing = antialiasing;
    }

    bool RenderProfile::isUsePbr() const
    {
        return usePbr;
    }

    void RenderProfile::setUsePbr(bool usePbr)
    {
        this->usePbr = usePbr;
    }
} // hs