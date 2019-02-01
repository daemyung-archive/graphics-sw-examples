//
// Created by djang on 2019-01-29.
//

#include "HitableList.h"

#include <algorithm>

HitableList::HitableList()
        : m_pHitables { } {
}

HitableList::HitableList(std::vector<std::unique_ptr<Hitable>> &&pHitables)
        : m_pHitables { std::move(pHitables) } {
}

std::optional<HitInfo> HitableList::hit(const Ray &ray, float minTime, float maxTime) const {
    HitInfo hitInfo = { };
    float newMaxTime = maxTime;
    bool isAnythingHit = false;

    for (auto &hitable : m_pHitables) {
        auto result = hitable->hit(ray, minTime, newMaxTime);
        if (result.has_value()) {
            hitInfo = result.value();
            newMaxTime = hitInfo.time;
            isAnythingHit = true;
        }
    }

    if (isAnythingHit)
        return hitInfo;
    else
        return std::nullopt;
}

void HitableList::add(std::unique_ptr<Hitable> &&pHitable) {
    if (std::end(m_pHitables) == std::find(std::begin(m_pHitables), std::end(m_pHitables), pHitable))
        m_pHitables.push_back(std::move(pHitable));
}
