#pragma once

#include "core/color.h"
#include "core/material.h"
#include "core/texture.h"

class Isotropic : public Material
{
public:
    Isotropic(const Color &albedo) :
        tex(MakeSptr<SolidColor>(albedo)) {}
    Isotropic(Sptr<Texture> tex) : tex(tex) {}
    
    bool Scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& rOut) const override
    {
        rOut = Ray(rec.P, Random::UnitVector3(), rIn.Time());
        attenuation = tex->Value(rec.u, rec.v, rec.P);
        return true;
    }

private:
    Sptr<Texture> tex;
};