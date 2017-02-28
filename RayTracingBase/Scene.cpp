#include "Scene.h"

Scene::Scene()
{
    // creacio de la camera
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(1,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = 600;
    int pixelsY = 400;
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

   // TODO: Cal crear els objectes de l'escena
    RandomScene();

    // TODO: Cal afegir llums a l'escena (Fase 2)
}

Scene::~Scene()
{
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            if (dynamic_cast<Sphere*>(objects[i]))
                    delete (Sphere *)(objects[i]);
        }
    }
    delete cam;
}

// TODO: Metode que genera una escena random de numObjects de tipus esfera, a diferents posicions,
// amb diferents radis i diferents materials. S'usa drand48 per generar numeros random

void Scene::RandomScene() {

    objects.push_back(new Sphere(vec3(0, 0, 0.75), 0.5, new Lambertian(vec3(0.5, 0.2, 0.7))));


    /*objects.push_back(new Sphere(vec3(0,-1,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5))));
    objects.push_back(new Sphere(vec3(1,-1,-1), 0.5, new Lambertian(vec3(0.8, 0.6, 0.2))));
    objects.push_back(new Sphere(vec3(-1,-1,-1), 0.5, new Lambertian(vec3(0.6, 0.8, 0.2))));
    objects.push_back(new Sphere(vec3(-1,0,-1), -0.45, new Lambertian(vec3(0.2, 0.6, 0.8))));*/
    objects.push_back(new Plane(vec3(1,0,0),vec3(0,0,0),new Lambertian(vec3(0.1, 0.2, 0.5))));
    objects.push_back(new Plane(vec3(0,1,0),vec3(0,0,0),new Lambertian(vec3(0.1, 0.2, 0.5))));
    objects.push_back(new Plane(vec3(0,0,1),vec3(0,0,0),new Lambertian(vec3(0.1, 0.2, 0.5))));
    //objects.push_back(new Cube(vec3(0,1,1),vec3(1,0,0),new Lambertian(vec3(0.1, 0.2, 0.5))));

    objects.push_back(new Triangle(vec3(1,0,0),vec3(0,1,0),vec3(0,0,1),new Lambertian(vec3(0.1, 0.2, 0.5))));

//    objects.push_back(new BoundaryObject("../RayTracingBase/resources/peo1K.obj", new Lambertian(vec3(0.2, 0.6, 0.8))));

}

/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena (Fase 1)
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    HitInfo temp;
    for(int i=0;i<objects.size();i++){
        if(objects[i]->hit(raig,t_min,t_max,temp)){
            if(info.t>temp.t){
                info=temp;
            }
        }
    }
    return info.t<std::numeric_limits<float>::infinity();

}

/*
** TODO: Funcio ComputeColor es la funcio recursiva del RayTracing.
** A modificar en la Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en la Fase 2 per a tractar reflexions
**
*/


vec3 Scene::ComputeColor (Ray &ray, int depth ) {
    vec3 white=vec3(1,1,1);
    vec3 blue=vec3(0.5,0.7,1);
    vec3 red=vec3(1,0,0);
    float t=0.5f*(ray.direction.y+1);
    HitInfo h;

    vec3 color;


    /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
     * el material de l'objecte i les llums per la fase 2 de la practica
     * En aquestesta fase 2,  cal fer que tambe es tinguin en compte els rebots de les reflexions.

       Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
       hitInfo ha d'anar tenint el color actualitzat segons els rebots.
    */
     if(!this->hit(ray,0,1000,h)){
        color = t*blue+(1-t)*white;
     }else{
         color=0.5f*(h.normal+vec3(1,1,1));
     }

     return color;
}

