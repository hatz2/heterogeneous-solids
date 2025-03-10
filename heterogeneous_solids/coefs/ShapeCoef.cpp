//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#include "ShapeCoef.h"

namespace hs {
    ShapeCoef::ShapeCoef(glm::vec3 position, unsigned int gridIndex) :
        cornerCoef(this), type(typeFromGridIndex(gridIndex)), gridIndex(gridIndex),
        position(position), alreadyRendered(false)
    {
        transform.translate(position);
        transform.attachObserver(this);
    }

    ShapeCoef::~ShapeCoef() {
        transform.detachObserver(this);
    }

    Transform& ShapeCoef::getTransform() {
        return transform;
    }

    const glm::vec3& ShapeCoef::getPosition() const {
        return position;
    }

    void ShapeCoef::setPosition(glm::vec3 position) {
        if (glm::any(glm::epsilonNotEqual(ShapeCoef::position, position, glm::epsilon<float>()))) {
            internalSetPosition(position);
            transform.setTranslation(position);
        }
    }

    ShapeCoefType ShapeCoef::getType() const {
        return type;
    }

    unsigned int ShapeCoef::getGridIndex() const {
        return gridIndex;
    }

    bool ShapeCoef::isAlreadyRendered() const {
        return alreadyRendered;
    }

    void ShapeCoef::setAlreadyRendered(bool alreadyRendered) {
        ShapeCoef::alreadyRendered = alreadyRendered;
    }

    ShapeCoef* ShapeCoef::getCornerCoef() const {
        return cornerCoef;
    }

    void ShapeCoef::setCornerCoef(ShapeCoef* cornerCoef) {
        removeCornerCoef();
        if (cornerCoef && cornerCoef != this) {
            ShapeCoef::cornerCoef = cornerCoef;
            cornerCoef->attachObserver(this);
        }
    }

    void ShapeCoef::removeCornerCoef() {
        if (cornerCoef) {
            cornerCoef->detachObserver(this);
            cornerCoef = this;
        }
    }

    const std::set<CellCoef*>& ShapeCoef::getSharedCoefs() const {
        return sharedCoefs;
    }

    void ShapeCoef::attachSharedCoef(CellCoef* sharedCoef) {
        sharedCoefs.insert(sharedCoef);
    }

    void ShapeCoef::detachSharedCoef(CellCoef* sharedCoef) {
        sharedCoefs.erase(sharedCoef);
    }

    unsigned int ShapeCoef::cornerIndexFromGridIndex(unsigned int index) {
        return 3 * (index % 4 >= 2) + 12 * (index % 16 >= 8) + 48 * (index >= 32);
    }

    ShapeCoefType ShapeCoef::typeFromGridIndex(unsigned int index) {
        unsigned int ii = index / 16, jj = (index % 16) / 4, kk = (index % 16) % 4;
        unsigned int nBorders = (ii % 3 == 0) + (jj % 3 == 0) + (kk % 3 == 0);
        return static_cast<ShapeCoefType>(nBorders);
    }

    const char* ShapeCoef::getNameFromType(ShapeCoefType type) {
        switch (type) {
            case ShapeCoefType::Vertex: return "Vertex";
            case ShapeCoefType::Edge: return "Edge";
            case ShapeCoefType::Surface: return "Surface";
            case ShapeCoefType::Corner: return "Corner";
        }
    }

    void ShapeCoef::internalSetPosition(glm::vec3 position) {
        if (glm::all(glm::epsilonEqual(position, ShapeCoef::position, glm::epsilon<float>()))) return;

        auto relative = position - ShapeCoef::position;
        ShapeCoef::position = position;
        updateSubject(ShapeCoefSubjectData {
            this,
            ShapeCoef::position,
            relative,
        });
    }

    void ShapeCoef::updateObserver(Transform& transform) {
        internalSetPosition(transform.getTranslation());
    }

    void ShapeCoef::updateObserver(ShapeCoefSubjectData payload) {
        if (payload.origin == cornerCoef) {
            transform.translate(payload.relativePosition);
        }
    }
} // hs