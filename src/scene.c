
#include "scene.h"

struct scene scene_create()
{
    struct scene scn;
    scn.entities = list_create(struct entity);
    scn.materials = list_create(struct material);
    return scn;
}

void scene_destroy(struct scene *scn)
{
    list_destroy(&scn->entities);
}

void scene_add_sphere(struct scene *scn, v3 orig, scl radius, int mat_id)
{
    struct entity ent;
    ent.type = ET_SPHERE;
    ent.mat_id = mat_id;
    ent.sphere.orig = orig;
    ent.sphere.radius = radius;
    list_append(&scn->entities, ent);
}

void scene_add_plane(struct scene *scn, v3 normal, scl dist, int mat_id)
{
    struct entity ent;
    ent.type = ET_PLANE;
    ent.mat_id = mat_id;
    ent.plane.normal = normalize(normal);
    ent.plane.dist = dist;
    list_append(&scn->entities, ent);
}

int scene_add_diffuse(struct scene *scn, v3 color)
{
    struct material mat;
    mat.type = MT_DIFFUSE;
    mat.diffuse.color = color;
    list_append(&scn->materials, mat);
    return scn->materials.count - 1;
}

int scene_add_metallic(struct scene *scn, v3 color, scl fuzz)
{
    struct material mat;
    mat.type = MT_METALLIC;
    mat.metallic.color = color;
    mat.metallic.fuzz = fuzz;
    list_append(&scn->materials, mat);
    return scn->materials.count - 1;
}
