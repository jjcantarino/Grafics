#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Cube.h"
#include "Light.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "Camera.h"
#include "Metal.h"
#include "Transparent.h"

class Scene: public Hitable
{
public:
    Scene();
    virtual ~Scene();

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth );
    vec3 ambientLight;
    int MAXDEPTH;


    // Vector d'objectes continguts a l'escena
    std::vector<Object*> objects;

    //Vector de llums continguts a l'escena
    std::vector<Light*> lights;

    // Camera: on está l'observador
    Camera *cam;

    vec3 blinnPhong(vec3 point,vec3 normal,const Material *material,bool ombra);
    void setAmbientLight(vec3);

private:
    void RandomScene();

};

#endif // SCENE_H
