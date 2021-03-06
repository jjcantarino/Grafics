#include "Lambertian.h"

Lambertian::Lambertian(const vec3& diffuse, const vec3& ambient, const vec3& specular, float shiness)
{
    this->diffuse=diffuse;
    this->specular=specular;
    this->ambient=ambient;
    this->opacity=1;
    this->shiness=shiness;
}

Lambertian::~Lambertian()
{}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    scattered = Ray(rec.p, target-rec.p);
    color = diffuse;
    return true;
}

