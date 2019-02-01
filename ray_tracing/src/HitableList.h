//
// Created by djang on 2019-01-29.
//

#ifndef RAY_TRACING_HITABLE_LIST_H
#define RAY_TRACING_HITABLE_LIST_H


#include <memory>
#include <vector>

#include "Hitable.h"

class HitableList : public Hitable {
public:
    HitableList();

    HitableList(std::vector<std::unique_ptr<Hitable>> &&pHitables);

    virtual std::optional<HitInfo> hit(const Ray &ray, float minTime, float maxTime) const;

    void add(std::unique_ptr<Hitable> &&pHitable);

private:
    std::vector<std::unique_ptr<Hitable>> m_pHitables;

};


#endif //RAY_TRACING_HITABLE_LIST_H
