//
// Created by djang on 2019-01-29.
//

#include "Hitable.h"

HitInfo::HitInfo()
        : time { 0.0f }, position { 0.0f }, normal { 0.0f }, pMaterial { nullptr } {
}

HitInfo::HitInfo(float time, const Vec3<float> &position, const Vec3<float> &normal, Material *pMaterial)
        : time { time }, position { position }, normal { normal }, pMaterial { pMaterial } {
}

HitInfo &HitInfo::setTime(float time) {
    this->time = time;
    return *this;
}

HitInfo &HitInfo::setPosition(const Vec3<float> &position) {
    this->position = position;
    return *this;
}

HitInfo &HitInfo::setNormal(const Vec3<float> &normal) {
    this->normal = normal;
    return *this;
}

HitInfo &HitInfo::setMaterial(Material *pMaterial) {
    this->pMaterial = pMaterial;
    return *this;
}
