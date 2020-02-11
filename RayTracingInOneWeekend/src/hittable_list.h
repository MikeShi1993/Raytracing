#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public hittable
{
public:
    hittable_list() = default;
    hittable_list(const hittable_list &) = delete;
    hittable_list(std::vector<std::unique_ptr<hittable>> &&l) noexcept : list(std::move(l)) {}
    template <typename T>
    void push_back(T &&lhs);
    virtual bool hit(const ray &ry, float t_min, float t_max, hit_record &rec) const override;

private:
    std::vector<std::unique_ptr<hittable>> list;
};

template <typename T>
void hittable_list::push_back(T &&lhs)
{
    list.push_back(std::make_unique<T>(std::forward<T>(lhs)));
}
